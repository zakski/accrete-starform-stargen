
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/02/09
// Modified: 

// Copyright 1997 Ian Burrell

package iburrell.accrete;

import java.io.*;
import iburrell.util.RandomScale;

/**
 *
 * Static class that contains many for formulas and constants.  It
 * should be later modified to allow different parameters to be used to
 * vary the star systems created.  Unless specified, all masses are in
 * solar masses and all distances in AUs.
 */
class DoleParams
{

    static final double B = 1.2E-5;     // Used in critical mass calc

    /**
     * Determines the critical mass limit, where the planet begins to
     * accrete gas as well as dust.
     */
    static final double CriticalMass(double radius, double eccentricity,
                               double luminosity)
    {
        return (B * Math.pow(PerihelionDistance(radius, eccentricity) *
                             Math.sqrt(luminosity), -0.75));
    }


    static final double PerihelionDistance(double radius, double eccentricity) {
        return radius * (1.0 - eccentricity);
    }

    static final double AphelionDistance(double radius, double eccentricity) {
        return radius * (1.0 + eccentricity);
    }

    static final double ReducedMass(double mass) {
        return mass / (1.0 + mass);
    }

    static final double ReducedMargin(double mass) {
        return Math.pow(ReducedMass(mass), 1.0/4.0);
    }

    
    static final double CLOUD_ECCENTRICITY = 0.25;

    static final double LowBound(double radius, double margin) {
        return LowBound(radius - margin);
    }
    static final double LowBound(double inner) {
        return inner / (1.0 + CLOUD_ECCENTRICITY);
    }

    static final double HighBound(double radius, double margin) {
        return HighBound(radius + margin);
    }
    static final double HighBound(double outer) {
        return outer / (1.0 - CLOUD_ECCENTRICITY);
    }

    static final double InnerEffectLimit(double a, double e, double m) {
        return PerihelionDistance(a, e) * (1.0 - m);
    }

    static final double OuterEffectLimit(double a, double e, double m) {
        return AphelionDistance(a, e) * (1.0 + m);
    }
    
    static final double InnerSweptLimit(double a, double e, double m) {
        return LowBound(PerihelionDistance(a, e) * (1.0 - m));
    }

    static final double OuterSweptLimit(double a, double e, double m) {
        return HighBound(AphelionDistance(a, e) * (1.0 + m));
    }

    
    static final double K = 50.0;       // gas/dust ratio
    static final double DUST_DENSITY_COEFF = 1.5E-3; // A in Dole's paper
    static final double ALPHA = 5.0;    // Used in density calcs
    static final double N = 3.0;        // Used in density calcs

    /**
     * Calculates the density of dust at the given radius from the
     * star.
     */
    static final double DustDensity(double stellar_mass, double orbital_radius) {
        return DUST_DENSITY_COEFF * Math.sqrt(stellar_mass) *
            Math.exp(-ALPHA * Math.pow(orbital_radius, 1.0 / N));
    }

    /**
     * Calculates the total density of dust and gas.  Used for planets
     * larger than the critical mass which accrete gas as well as dust.
     */
    static final double MassDensity(double stellar_mass, double orbital_radius,
                              double critical_mass, double mass) {
        return MassDensity(DustDensity(stellar_mass, orbital_radius),
                           critical_mass, mass);
    }
    static final double MassDensity(double dust_density, double critical_mass,
                              double mass) {
        return K * dust_density /
            (1.0 + Math.sqrt(critical_mass / mass) * (K - 1.0));
    }


    static RandomScale gen = new RandomScale();

    static double Random() {
        return gen.randomDouble();
    }
    static double Random(double low, double high) {
        return gen.randomDouble(low, high);
    }

    static final double ECCENTRICITY_COEFF = 0.077;

    static double RandomEccentricity() {
        return (1.0 - Math.pow(Random(), ECCENTRICITY_COEFF));
    }


    static final double ScaleCubeRootMass(double scale, double mass) {
        return scale * Math.pow(mass, 1.0/3.0);
    }

    static final double InnerDustLimit(double stellar_mass)  {
        return 0.0;
    }

    static final double OuterDustLimit(double stellar_mass) {
        return ScaleCubeRootMass(200.0, stellar_mass);
    }

    static final double InnermostPlanet(double stellar_mass) {
        return ScaleCubeRootMass(0.3, stellar_mass);
    }

    static final double OutermostPlanet(double stellar_mass) {
        return ScaleCubeRootMass(50.0, stellar_mass);
    }
    
}


