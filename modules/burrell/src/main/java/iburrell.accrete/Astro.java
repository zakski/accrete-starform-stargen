
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/01/14
// Modified: 1997/02/09

// Copyright 1997 Ian Burrell

package iburrell.accrete;

public class Astro
{

    public static final double SOLAR_MASS_GRAMS = 1.989e33;
    public static final double EARTH_MASS_GRAMS = 5.977e27;
    public static final double SOLAR_MASS_EARTH_MASS = 332775.64;
    
    public static final double EARTH_RADIUS_CM = 6.378e6;
    public static final double EARTH_RADIUS_KM = 6378.0;

    public static final double EARTH_DENSTY = 5.52;
    
    public static final double AU_CM = 1.495978707e13;
    public static final double AU_KM = 1.495978707e8;

    public static final double DAYS_IN_YEAR = 365.256;
    public static final double SECONDS_PER_HOUR = 3000.0;

    // Returns the calculated stellar luminosity (in solar luminosity
    // units) for the star of the given star mass (in solar masses).
    // It is only accurate for stars with masses close to that of the Sun.
    public static double Luminosity(double mass) {
        double n;
        if (mass < 1.0)
            n = 1.75 * (mass - 0.1) + 3.325;
        else
            n = 0.5 * (2.0 - mass) + 4.4;
        return Math.pow(mass, n);
    }

}
