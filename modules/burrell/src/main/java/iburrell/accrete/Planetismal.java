
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/02/09
// Modified: 

// Copyright 1997 Ian Burrell

package iburrell.accrete;

import java.io.*;

/**
 *
 * This class stores the data needed for a planetismal, which is
 * basically mass and the orbit parameters.  It also includes a
 * pointer to the next in the list.  Also, has some functions that
 * calls the main calculators in the DoleParams class with the proper
 * values for the nucleus.
 * 
 * The Accrete class manipulates the internals of this class directly.
 * Outside clients use the accessors.
 *
 */
public class Planetismal
{

    double axis;        // semi-major axis (AU)
    double eccn;        // eccentricity
    double mass;        // mass (solar mass)
    boolean gas_giant;
    Planetismal next;
    
    // Accessors

    public double getOrbitalAxis() { return axis; }
    public double getEccentricity() { return eccn; }
    public double getMassSolar() { return mass; }
    public double getMassEarth() { return mass*Astro.SOLAR_MASS_EARTH_MASS; }
    public boolean isGasGiant() { return gas_giant; }
    
    static final double PROTOPLANET_MASS = 1.0E-15; // units of solar masses
    
    Planetismal(double a, double e) {
        this(a, e, PROTOPLANET_MASS, false);
    }
    Planetismal(double a, double e, double m) {
        this(a, e, m, false);
    }
    Planetismal(double a, double e, double m, boolean giant) {
        axis = a;
        eccn = e;
        mass = m;
        gas_giant = giant;
        next = null;
    }

    static Planetismal RandomPlanetismal(double inner, double outer) {
        return new Planetismal(DoleParams.Random(inner, outer),
                               DoleParams.RandomEccentricity());
    }


    final double PerihelionDistance() {
        return DoleParams.PerihelionDistance(axis, eccn);
    }

    final double AphelionDistance() {
        return DoleParams.AphelionDistance(axis, eccn);
    }

    final double ReducedMass() {
        return DoleParams.ReducedMass(mass);
    }

    final double ReducedMargin() {
        return DoleParams.ReducedMargin(mass);
    }
    
    final double InnerEffectLimit() {
        return DoleParams.InnerEffectLimit(axis, eccn,
                                           DoleParams.ReducedMargin(mass));
    }

    final double OuterEffectLimit() {
        return DoleParams.OuterEffectLimit(axis, eccn,
                                           DoleParams.ReducedMargin(mass));
    }

    final double InnerSweptLimit() {
        return DoleParams.InnerSweptLimit(axis, eccn,
                                           DoleParams.ReducedMargin(mass));
    }

    final double OuterSweptLimit() {
        return DoleParams.OuterSweptLimit(axis, eccn,
                                           DoleParams.ReducedMargin(mass));
    }

    final double CriticalMass(double luminosity) {
        return DoleParams.CriticalMass(axis, eccn, luminosity);
    }


    public void Print(PrintStream out) {
        out.print(axis + " " + eccn + " " + mass);
        if (mass > 2e-15)
            out.print(" (" + mass * Astro.SOLAR_MASS_EARTH_MASS + ")");
        if (gas_giant)
            out.print(" giant");
        out.println();
    }

}
