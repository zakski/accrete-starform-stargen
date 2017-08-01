
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/01/14
// Modified: 1997/02/09

// Copyright 1997 Ian Burrell

/*
 *
 * Simulates the creation of planetary systems using the Dole
 * accretion model.
 *
 * This program simulates the creation of a planetary system by
 * accretion of planetismals.  Individual planets sweep out dust and
 * gas until all of the dust is swept up.  Planets whose orbits are
 * close are coalesced.
 *
 * See http://www-leland.stanford.edu/~iburrell/create/accrete.html
 * for more history of this model and programs.
 *
 * References:
 *      Dole, Stephen H.  "Computer Simulation of the Formation of
 *          Planetary Systems."  _Icarus_.  13 (1970), pg 494-508.
 *      Isaacman & Sagan.  "Computer Simulations of Planetary Accretion
 *          Dynamics."  _Icarus_.  31 (1997), pg 510-533.
 *      Fogg, Martyn J.  "Extra-Solar Planetary Systems: A Microcomputer
 *          Simulation".  Journal of the British Interplanetary
 *          Society, vol 38, 501-514, 1985.
 *
 *
 */

package iburrell.accrete;

import java.io.*;
import java.util.*;

/**
 *
 * This class does the accretion process and returns a list of
 * Planetismals with the results.  It is constructed for a given star
 * size.  Multiple random systems can be created for the given star
 * using DistributePlanets.
 *
 */
public class Accrete
{

    double stellar_mass;        // in Solar masses
    double stellar_luminosity;  // in Solar luminsoities
    double inner_bound, outer_bound;    // in AU
    double inner_dust, outer_dust;      // in AU

    /**
     * Creates a Accretion class for the star of the given size.
     * Pre-calculates all of those values that depend on the size of
     * the star.  
     */
    public Accrete() { this(1.0, 1.0); }
    public Accrete(double stell_mass) {
        this(stell_mass, Astro.Luminosity(stell_mass));
    }
    public Accrete(double stell_mass, double stell_lum) {
        stellar_mass = stell_mass;
        stellar_luminosity = stell_lum;
        inner_bound = DoleParams.InnermostPlanet(stellar_mass);
        outer_bound = DoleParams.OutermostPlanet(stellar_mass);
        inner_dust = DoleParams.InnerDustLimit(stellar_mass);
        outer_dust = DoleParams.OuterDustLimit(stellar_mass);
    }

    // values that only depend on radius and are cached for each
    // nucleus 
    double crit_mass;   
    double dust_density;
    
    DustBand dust_head = null;          // head of the list of dust bands
    Planetismal planet_head = null;     // head of the list planetismals


    /**
     *
     * This function does the main work of creating the planets.  It
     * calls all of the other functions to create an entire system of
     * planetismals.  It returns a list of the Planetismals.
     *
     * @return Vector containing all of the planets written out.
     */
    public Vector DistributePlanets() 
    {
        dust_head = new DustBand(inner_dust, outer_dust);
        planet_head = null;
        
        boolean dust_left = true;
        while (dust_left) {
            Planetismal tsml = Planetismal.RandomPlanetismal(inner_bound,
                                                             outer_bound); 

            dust_density = DoleParams.DustDensity(stellar_mass, tsml.axis);
            crit_mass = tsml.CriticalMass(stellar_luminosity); 

            double mass = AccreteDust(tsml);

            if ((mass != 0.0) && (mass != Planetismal.PROTOPLANET_MASS)) {
                if (mass >= crit_mass) 
                    tsml.gas_giant = true;
                UpdateDustLanes(tsml.InnerSweptLimit(),
                                tsml.OuterSweptLimit(), tsml.gas_giant);
                dust_left = CheckDustLeft();
                CompressDustLanes();

                if (!CoalescePlanetismals(tsml))
                    InsertPlanet(tsml);

            }

        }

        return PlanetArray(planet_head);
        
    }

    
    /**
     * Steps through list of dust bands checking to see if any of
     * those that bands that overlap the given range have dust
     * present.  This was originally done as a quick check with the
     * swept limits using the full mass for newly injected nuclei.
     */
    boolean DustAvailable(double inside, double outside) {
        DustBand curr = dust_head;
        while ((curr != null) && (curr.outer < inside)) {
             curr = curr.next;
        }
        
        boolean dust_here = false;
        if (curr != null)
            dust_here = curr.dust;

        while ((curr != null) && (curr.inner < outside)) {
            curr = curr.next;
            dust_here = dust_here || curr.dust;
        }
        return dust_here;
    }


    /**
     * Repeatedly accretes dust and gas onto the new planetismal by
     * sweeping out gas lanes until the planetismal doesn't grow any
     * more.  Returns the new mass for the planetismal; also changes
     * the planetismal's mass.
     */
    double AccreteDust(Planetismal nucleus) {
        double new_mass = nucleus.mass;
        do {
            nucleus.mass = new_mass;
            new_mass = 0;
            for (DustBand  curr = dust_head; curr != null; curr = curr.next) {
                new_mass += CollectDust(nucleus, curr);
            }
        }
        while ((new_mass - nucleus.mass) > (0.0001 * nucleus.mass));
        nucleus.mass = new_mass;
        return nucleus.mass;
    }


    /**
     * Returns the amount of dust and gas collected from the single
     * dust band by the nucleus.  Returns 0.0 if no dust can be swept
     * from the band
     */
    double CollectDust(Planetismal nucleus, DustBand band)
    {
        if (band == null)
            return 0.0;

        double swept_inner = nucleus.InnerSweptLimit();
        double swept_outer = nucleus.OuterSweptLimit();

        if (swept_inner < 0.0)
            swept_inner = 0.0;
        if ((band.outer <= swept_inner) || (band.inner >= swept_outer))
            return 0.0;;
        if (!band.dust)
            return  0.0;

        double dust_density = this.dust_density;
        double mass_density = DoleParams.MassDensity(dust_density, crit_mass,
                                                      nucleus.mass); 
        double density = (!band.gas || (nucleus.mass < crit_mass))
            ? dust_density : mass_density;
        
        double swept_width = swept_outer - swept_inner;
        double outside = swept_outer - band.outer;
        if (outside < 0.0)
            outside = 0.0;
        double inside = band.inner - swept_inner;
        if (inside < 0.0)
            inside = 0.0;

        double width = swept_width - outside - inside;
        double term1 = 4.0 * Math.PI * nucleus.axis * nucleus.axis;
        double term2 = (1.0 - nucleus.eccn * (outside - inside) / swept_width);
        double volume = term1 * nucleus.ReducedMargin() * width * term2;

        return volume * density;

    }


    /**
     * Updates the dust lanes covered by the given range by splitting
     * if necessary and updating the dust and gas present fields.
     */
    void UpdateDustLanes(double min, double max, boolean used_gas) {
        for (DustBand curr = dust_head; curr != null; curr = curr.next) {
            boolean new_gas = curr.gas && !used_gas;
            DustBand first, second, next = curr;

            // Case 1: Wide
            if ((curr.inner < min) && (curr.outer > max)) {
                first = new DustBand(min, max, false, new_gas);
                second = new DustBand(max, curr.outer, curr.dust, curr.gas);
                first.next = second;
                second.next = curr.next;
                curr.next = first;
                curr.outer = min;
                next = second;
            }
            // Case 2: Out
            else if ((curr.inner < max) && (curr.outer > max)) {
                first = new DustBand(max, curr.outer, curr.dust, curr.gas);
                first.next = curr.next;
                curr.next = first;
                curr.outer = max;
                curr.dust = false;
                curr.gas = new_gas;
                next = first;
            }
            // Case 3: In
            else if ((curr.inner < min) && (curr.outer > min)) {
                first = new DustBand(min, curr.outer, false, new_gas);
                first.next = curr.next;
                curr.next = first;
                curr.outer = min;
                next = first;
            }
            // Case 4: Narrow
            else if ((curr.inner >= min) && (curr.outer <= max)) {
                curr.dust = false;
                curr.gas = new_gas;
                next = curr;
            }
            // Case 5: Not
            else if ((curr.inner > max) || (curr.outer < min)) {
                next = curr;
            }
            curr = next;
        }
    }

    
    /**
     * Checks if there is any dust remaining in any bands inside the
     * bounds where planets can form.
     */
    boolean CheckDustLeft() {
        boolean dust_left = false;
        for (DustBand curr = dust_head; curr != null; curr = curr.next) {
            // check if band has dust left
            if (curr.dust && (curr.outer >= inner_bound)
                && (curr.inner <= outer_bound)) {
                dust_left = true;
            }
        }
        return dust_left;
    }


    /**
     * Compresses adjacent lanes that have the same status.
     */
    void CompressDustLanes() {
        DustBand next;
        for (DustBand curr = dust_head; curr != null; curr = next) {
            next = curr.next;
            if (next != null && (curr.dust == next.dust)
                && (curr.gas == next.gas)) {
                curr.outer = next.outer;
                curr.next = next.next;
                next = curr;
            }
        }
    }
    

    /**
     * Searches the existing planet list for any that overlap with the
     * new planetismal.  If there is an overlap their effect radii,
     * the two planets are coalesced into one.
     */
    boolean CoalescePlanetismals(Planetismal tsml) {
        for (Planetismal curr = planet_head; curr != null; curr = curr.next) {
            double dist = curr.axis - tsml.axis;
            double dist1,  dist2;
            if (dist > 0.0) {
                dist1 = tsml.OuterEffectLimit() - tsml.axis;
                dist2 = curr.axis - curr.InnerEffectLimit();
            }
            else {
                dist1 = tsml.axis - tsml.InnerEffectLimit();
                dist2 = curr.OuterEffectLimit() - curr.axis;
            }

            if ((Math.abs(dist) <= dist1) || (Math.abs(dist) <= dist2)) {
                CoalesceTwoPlanets(curr, tsml);
                return true;
            }
        }
        return false;
    }


    /**
     * Coalesces two planet together.  The resulting planet is saved
     * back into the first one (which is assumed to be the one present
     * in the planet list).
     */
    void CoalesceTwoPlanets(Planetismal a, Planetismal b) {
        double new_mass = a.mass + b.mass;
        double new_axis = new_mass / ((a.mass / a.axis) + (b.mass / b.axis));
        double term1 = a.mass * Math.sqrt(a.axis * (1.0 - a.eccn*a.eccn));
        double term2 = b.mass * Math.sqrt(b.axis * (1.0 - b.eccn*b.eccn));
        double term3 = (term1 + term2) / (new_mass * Math.sqrt(new_axis)); 
        double term4 = 1.0 - term3*term3;
        double new_eccn = Math.sqrt(Math.abs(term4));
        a.mass =  new_mass;
        a.axis = new_axis;
        a.eccn = new_eccn;
        a.gas_giant = a.gas_giant || b.gas_giant;
        //AccreteDust(a);
    }
    

    /**
     * Inserts the given planetismal into the list of planets.  The
     * list is kept in sorted order based on the semi-major axis.
     */
    void InsertPlanet(Planetismal tsml) {
        if (planet_head == null)
            planet_head = tsml;
        else {
            if (tsml.axis < planet_head.axis) {
                tsml.next = planet_head;
                planet_head = tsml;
            }
            else {
                Planetismal prev = planet_head;
                Planetismal curr = planet_head.next;
                while ((curr != null) && (curr.axis < tsml.axis)) {
                    prev = curr;
                    curr = curr.next;
                }
                tsml.next = curr;
                prev.next = tsml;
            }
        }
    }
               

    public void PrintClass(PrintStream out) {
        out.println("stellar mass: " + stellar_mass);
        out.println("stellar luminosity: " + stellar_luminosity);
        out.println("bounds: " + inner_bound + "  " + outer_bound);
        out.println("dust: " + inner_dust + "  " + outer_dust);
    }

    public void PrintDusts(PrintStream out) {
        for (DustBand curr = dust_head; curr != null; curr = curr.next) {
            curr.Print(out);
        }
    }

    public void PrintPlanets(PrintStream out) {
        for (Planetismal curr = planet_head; curr != null; curr = curr.next) {
            curr.Print(out);
        }
    }

    public static void PrintPlanets(PrintStream out, Vector planets) {
        Enumeration e = planets.elements();
        while (e.hasMoreElements()) {
            Planetismal curr = (Planetismal)e.nextElement();
            curr.Print(out);
        }
    }
    
    // Converts a list of planets into a Vector.  The planets in the Vector
    // still contain the links but they aren't accessible to outside classes.
    static Vector PlanetArray(Planetismal head) {
        Vector planets = new Vector();
        for (Planetismal curr = head; curr != null; curr = curr.next) {
            planets.addElement(curr);
        }
        return planets;
    }
    
    public static void main(String[] args) {
        Accrete gen = new Accrete();
        Vector pl = gen.DistributePlanets();
        gen.PrintPlanets(System.out, pl);
    }

}

