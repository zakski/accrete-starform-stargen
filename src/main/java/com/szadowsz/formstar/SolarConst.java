package com.szadowsz.formstar;

public class SolarConst {

	/* Star Age & Main Sequence Lifespan */
	public static final double SUN_MS_LIFESPAN = 1.0E10; // the lifespan of our own sun on the ms.

	//////////////////////////////////////////////////////
	//												    //
	//         Star Calculation Constants               //
	//												    //
	//////////////////////////////////////////////////////
	public static final double AGE_OUTER_LIMIT = 6.0E9;
	public static final double AGE_INNER_LIMIT = 1.0E9;
	/* Habitable Zones */
	public static final double GREENHOUSE_EFFECT_CONST = 0.93; /* affects inner radius.. */
	/* Temperature */
	public static final double SUN_SURFACE_TEMP = 5650; // in kelvins
	/* Accretion */
	public static final double PROTOPLANET_MASS = 1.0E-15; /* Starting Mass in solar mass */
	
	
	//////////////////////////////////////////////////////
	//												    //
	//      Accrete Calculation Constants               //
	//												    //
	//////////////////////////////////////////////////////
	/* Orbits */
	public static final double ECCENTRICITY_COEFF = 0.077; /* Dole's was 0.077 */
	/* Critical Mass */
	public static final double B = 1.2E-5; /* Used in Crit_mass calc */
	/* Dust Density */
	public static final double DUST_DENSITY_COEFF = 2.0E-3; /* A in Dole's paper */
	public static final double N = 3.0; /* Used in density calcs */
	public static final double ALPHA = 5.0; /* Used in density calcs */
	/* Mass Density */
	public static final double K = 50.0; // gas/dust ratio
	public static final double CLOUD_ECCENTRICITY = 0.2; // 0.25; - Burdick's code calls for 0.2, Burrell's for 0.25
	/* Kothari Radius */
	public static final double A1_20 = 6.485E12; /* All units are in cgs system. */
	public static final double A2_20 = 4.0032E-8; /* ie: cm, g, dynes, etc. */
	public static final double BETA_20 = 5.71E12;
	/* Mass */
	public static final double EARTH_MASS_IN_GRAMS = 5.977E27; /* Units of grams */


	
	//////////////////////////////////////////////////////
	//												    //
	//     General Constants                            //
	//												    //
	//////////////////////////////////////////////////////
	public static final double SOLAR_MASS_IN_GRAMS = 1.989E33; /* Units of grams */
	public static final double SUN_MASS_IN_EARTH_MASSES = 332775.64;
	/* Distance */
	public static final double CM_PER_METER = 100.0;
	public static final double CM_PER_AU = 1.495978707E13;/* number of cm in an AU */
	public static final double CM_PER_KM = 1.0E5; /* number of cm in a km */
	public static final double KM_PER_AU = CM_PER_AU / CM_PER_KM;
	/* Time */
	public static final double SECONDS_PER_HOUR = 3600.0;
	public static final double DAYS_IN_A_YEAR = 365.256; /* Earth days per Earth year */

	/**
	 * Constructor Not Needed
	 */
	private SolarConst() {
	}


}
