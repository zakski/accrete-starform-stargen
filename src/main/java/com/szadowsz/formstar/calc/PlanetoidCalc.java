package com.szadowsz.formstar.calc;

import com.szadowsz.utils.RandomUtil;

import java.util.Random;

/**
 * @author Zakski : 30/05/2015.
 */
public class PlanetoidCalc {


    /**
     * Method to calculate a planet's radius using volume in units of km
     *
     * @param mass    - the mass of the planet
     * @param density - the density of the planet
     * @return the equatorial radius of the planet
     */
    public static double volumeRadius(double mass, double density) {
        double volume;

        mass = mass * SolarConst.SOLAR_MASS_IN_GRAMS;
        volume = mass / density;
        return (Math.pow((3.0 * volume) / (4.0 * Math.PI), (1.0 / 3.0)) / SolarConst.CM_PER_KM);
    }

    /**
     * Method to calculate a planet's density using volume in units of grams/cc.
     *
     * @param mass         - the mass of the planet
     * @param equat_radius - the equatorial radius of the planet
     * @return the density of the planet
     */
    public static double volumeDensity(double mass, double equat_radius) {
        double volume;

        mass = mass * SolarConst.SOLAR_MASS_IN_GRAMS;
        equat_radius = equat_radius * SolarConst.CM_PER_KM;
        volume = (4.0 * Math.PI * Math.pow(equat_radius, 3)) / 3.0;
        return (mass / volume);
    }

    /**
     * This formula is listed as eq.9 in Fogg's article, although some typos crop up in that eq. See
     * "The Internal Constitution of Planets", by Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical
     * Society, vol 96 pp.833-843, 1936 for the derivation. Specifically, this is Kothari's eq.23, which
     * appears on page 840.
     *
     * @param mass  - the mass of the planet
     * @param giant - is the planet a gas giant
     * @param zone  - orbital zone of the planet
     * @return the equatorial radius of the planet
     */
    public static double kothariRadius(double mass, boolean giant, int zone) {
        double temp, temp2, atomic_weight, atomic_num;

        if (zone == 1) {
            if (giant) {
                atomic_weight = 9.5;
                atomic_num = 4.5;
            } else {
                atomic_weight = 15.0;
                atomic_num = 8.0;
            }
        } else if (zone == 2) {
            if (giant) {
                atomic_weight = 2.47;
                atomic_num = 2.0;
            } else {
                atomic_weight = 10.0;
                atomic_num = 5.0;
            }
        } else {
            if (giant) {
                atomic_weight = 7.0;
                atomic_num = 4.0;
            } else {
                atomic_weight = 10.0;
                atomic_num = 5.0;
            }
        }
        temp = atomic_weight * atomic_num;
        temp = (2.0 * SolarConst.BETA_20 * Math.pow(SolarConst.SOLAR_MASS_IN_GRAMS, (1.0 / 3.0)))
                / (SolarConst.A1_20 * Math.pow(temp, (1.0 / 3.0)));
        temp2 = SolarConst.A2_20 * Math.pow(atomic_weight, (4.0 / 3.0))
                * Math.pow(SolarConst.SOLAR_MASS_IN_GRAMS, (2.0 / 3.0));
        temp2 = temp2 * Math.pow(mass, (2.0 / 3.0));
        temp2 = temp2 / (SolarConst.A1_20 * Math.pow(atomic_num, 2));
        temp2 = 1.0 + temp2;
        temp = temp / temp2;
        temp = (temp * Math.pow(mass, (1.0 / 3.0))) / SolarConst.CM_PER_KM;
        return (temp);
    }

    /**
     * Method to calculate the Empirical Density in units of grams/cc
     *
     * @param axis      - semi-major axis of the planet
     * @param mass      - the mass of the planet
     * @param isGiant   - is the planet a gas giant
     * @param ecosphere - system's ecosphere radius
     * @return the density
     */
    public static double empiricalDensity(double axis, double mass, boolean isGiant, double ecosphere) {
        double density;

        density = Math.pow(mass * SolarConst.SUN_MASS_IN_EARTH_MASSES, (1.0 / 8.0));
        density = density * Math.pow(ecosphere / axis, 1 / 4);
        if (isGiant)
            return (density * 1.2);
        else
            return (density * 5.5);
    }


    public static double change_in_angular_velocity(double density, double equatorial_radius, double planetary_mass, double stell_mass, double orb_radius) {
        // convert values so they are in terms of earth values
        double d = (density / SolarConst.EARTH_DENSITY);
        double r = (equatorial_radius / SolarConst.EARTH_RADIUS);
        double m = SolarConst.EARTH_MASS_IN_GRAMS / planetary_mass;
        double stell_mas_sq = stell_mass * stell_mass;

        return SolarConst.CHANGE_IN_EARTH_ANG_VEL * d * r * m * stell_mas_sq * (1.0 / Math.pow(orb_radius, 6.0));
    }

    public static double angular_velocity(double density, double radius, double mass, double orb_radius, double stell_mass, double stell_age, boolean giant) {
        double k2 = (giant) ? 0.24 : 0.33;
        double planetary_mass = mass * SolarConst.EARTH_MASS_IN_GRAMS;
        double equatorial_radius = radius * SolarConst.CM_PER_KM;


        double base_angular_velocity = Math.sqrt(2.0 * SolarConst.J * (planetary_mass) / (k2 * equatorial_radius * equatorial_radius));
        //  This next calculation determines how much the Planet's rotation is
        //  slowed by the presence of the star.
        double change_in_angular = change_in_angular_velocity(density, equatorial_radius, planetary_mass, stell_mass, orb_radius);

        return base_angular_velocity + (change_in_angular * stell_age);
    }

    /**
     * Estimates planetary inclination (axial tilt).  Calibrated to Earth.
     *
     * @param orb_radius Semi-major axis of orbit in AU
     * @returns Tilt in degrees
     */
    public static int inclination(Random rand, double orb_radius) {
        int temp;
        temp = (int) (Math.pow(orb_radius, 0.2) * RandomUtil.variation(rand, SolarConst.EARTH_AXIAL_TILT, 0.4));
        return (temp % 360);
    }

    /**
     * Estimates length of the planet's day.
     * Fogg's information for this routine came from Dole "Habitable Planets
     * for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came
     * up with his eq.12, which is the equation for the 'base_angular_velocity'
     * below.  He then used an equation for the change in angular velocity per
     * time (dw/dt) from P. Goldreich and S. Soter's paper "Q in the Solar
     * System" in Icarus, vol 5, pp.375-389 (1966).  Using as a comparison the
     * change in angular velocity for the Earth, Fogg has come up with an
     * approximation for our new Planet (his eq.13) and take that into account.
     * This is used to find 'change_in_angular_velocity' below.
     *
     * @param mass   Mass in Earth masses.
     * @param radius Equatorial radius in kilometers.
     * @returns Length of day in Earth hours.
     */
    public static double day_length(double mass, double ecc, double radius, double ang_velocity, double year_in_hours) {
        if (mass == 0.0 || radius == 0.0) {
            return year_in_hours;
        }
        boolean stopped = false;

        double resonance = 0.0;

        double day_in_hours = year_in_hours;
        // Now we change from rad/sec to hours/rotation.
        if (ang_velocity > 0.0) {
            day_in_hours = Math.PI * 2 / (SolarConst.SECONDS_PER_HOUR * ang_velocity);
        }

        if ((day_in_hours >= year_in_hours) || stopped) {
            resonance = 1.0;  // had been only w/large eccentricity, but...
            if (ecc > 0.1) {
                double spin_resonance_factor = (1.0 - ecc) / (1.0 + ecc);
                return (spin_resonance_factor * year_in_hours);
            } else
                return (year_in_hours);
        }
        return (day_in_hours);
    }
}
