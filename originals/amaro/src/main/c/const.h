#include <math.h>

#if 0
#ifdef LONG_RAND
#define RAND_MAX		(2147483647.0)
#else
#define RAND_MAX		(32767.0)
#endif
#endif

#define PI						(3.1415926536)
#define RADIANS_PER_ROTATION	(2.0 * PI)

#ifndef TRUE
#define TRUE					(1)
#define FALSE					(0)
#endif

#define ECCENTRICITY_COEFF		(0.077)			/* Dole's was 0.077			*/
#define PROTOPLANET_MASS		(1.0E-15)		/* Units of solar masses	*/
#define CHANGE_IN_EARTH_ANG_VEL (-1.3E-15)		/* Units of radians/sec/year*/
#define SOLAR_MASS_IN_GRAMS		(1.98892E33)		/* Units of grams			*/
#define SOLAR_MASS_IN_KILOGRAMS	(1.98892E30)		/* Units of kg				*/
#define EARTH_MASS_IN_GRAMS		(5.9742E27)		/* Units of grams			*/
#define EARTH_RADIUS			(6.378137E8)		/* Units of cm				*/
#define EARTH_DENSITY			(5.515)			/* Units of g/cc			*/
#define KM_EARTH_RADIUS			(6378.137)		/* Units of km				*/
//      EARTH_ACCELERATION		(981.0)			/* Units of cm/sec2			*/
#define EARTH_ACCELERATION		(980.665)			/* Units of cm/sec2			*/
#define EARTH_AXIAL_TILT		(23.44)			/* Units of degrees			*/
#define EARTH_EXOSPHERE_TEMP	(1273.0)		/* Units of degrees Kelvin	*/
#define SUN_MASS_IN_EARTH_MASSES (332775.64)
#define ASTEROID_MASS_LIMIT		(0.001)			/* Units of Earth Masses	*/
#define EARTH_EFFECTIVE_TEMP	(250.0)			/* Units of degrees Kelvin (was 255)	*/
#define CLOUD_COVERAGE_FACTOR	(1.839E-8)		/* Km2/kg					*/
#define EARTH_WATER_MASS_PER_AREA	 (3.83E15)	/* grams per square km		*/
#define EARTH_SURF_PRES_IN_MILLIBARS (1013.25)
#define EARTH_SURF_PRES_IN_MMHG	(760.)			/* Dole p. 15				*/
#define EARTH_SURF_PRES_IN_PSI	(14.696)		/* Pounds per square inch	*/
#define MMHG_TO_MILLIBARS (EARTH_SURF_PRES_IN_MILLIBARS / EARTH_SURF_PRES_IN_MMHG)
#define PSI_TO_MILLIBARS (EARTH_SURF_PRES_IN_MILLIBARS / EARTH_SURF_PRES_IN_PSI)
#define H20_ASSUMED_PRESSURE	(47. * MMHG_TO_MILLIBARS) /* Dole p. 15      */
#define MIN_O2_IPP	(72. * MMHG_TO_MILLIBARS)	/* Dole, p. 15				*/
#define MAX_O2_IPP	(400. * MMHG_TO_MILLIBARS)	/* Dole, p. 15				*/
#define MAX_HE_IPP	(61000. * MMHG_TO_MILLIBARS)	/* Dole, p. 16			*/
#define MAX_NE_IPP	(3900. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
#define MAX_N2_IPP	(2330. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
#define MAX_AR_IPP	(1220. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
#define MAX_KR_IPP	(350. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
#define MAX_XE_IPP	(160. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
//#define MAX_CO2_IPP (7. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/
#define MAX_CO2_IPP (14. * MMHG_TO_MILLIBARS)	/* Dole, p. 16				*/ // SEB: FOR PELL
#define MAX_HABITABLE_PRESSURE (118 * PSI_TO_MILLIBARS)	/* Dole, p. 16		*/
// The next gases are listed as poisonous in parts per million by volume at 1 atm:
#define PPM_PRSSURE (EARTH_SURF_PRES_IN_MILLIBARS / 1000000.)
#define MAX_F_IPP	(0.1 * PPM_PRSSURE)			/* Dole, p. 18				*/
#define MAX_CL_IPP	(1.0 * PPM_PRSSURE)			/* Dole, p. 18				*/
#define MAX_NH3_IPP	(100. * PPM_PRSSURE)		/* Dole, p. 18				*/
#define MAX_O3_IPP	(0.1 * PPM_PRSSURE)		/* Dole, p. 18 umol/mol = 100 nmol/mol		*/
#define MAX_CH4_IPP	(50000. * PPM_PRSSURE)		/* Dole, p. 18				*/



#define EARTH_CONVECTION_FACTOR (0.43)			/* from Hart, eq.20			*/
//      FREEZING_POINT_OF_WATER (273.0)			/* Units of degrees Kelvin	*/
#define FREEZING_POINT_OF_WATER (273.15)		/* Units of degrees Kelvin	*/
//      EARTH_AVERAGE_CELSIUS   (15.5)			/* Average Earth Temperature */
#define EARTH_AVERAGE_CELSIUS   (14.0)			/* Average Earth Temperature */
#define EARTH_AVERAGE_KELVIN    (EARTH_AVERAGE_CELSIUS + FREEZING_POINT_OF_WATER)
#define DAYS_IN_A_YEAR			(365.256)		/* Earth days per Earth year*/
//		gas_retention_threshold = 5.0;  		/* ratio of esc vel to RMS vel */
#define GAS_RETENTION_THRESHOLD (6.0)			/* ratio of esc vel to RMS vel */

#define ICE_ALBEDO				(0.7)
#define CLOUD_ALBEDO			(0.52)
#define GAS_GIANT_ALBEDO		(0.5)			/* albedo of a gas giant	*/
#define CLASS_I_ALBEDO			(0.57)
#define CLASS_II_ALBEDO			(0.81)
#define CLASS_III_ALBEDO		(0.12)
#define CLASS_IV_ALBEDO			(0.03)
#define CLASS_V_ALBEDO			(0.55)
#define AIRLESS_ICE_ALBEDO		(0.5)
#define EARTH_ALBEDO			(0.3)			/* was .33 for a while */
#define GREENHOUSE_TRIGGER_ALBEDO (0.20)
#define ROCKY_ALBEDO			(0.15)
#define ROCKY_AIRLESS_ALBEDO	(0.07)
#define WATER_ALBEDO			(0.04)

#define SECONDS_PER_HOUR		(3600.0)
#define CM_PER_AU				(1.495978707E13)/* number of cm in an AU	*/
#define CM_PER_KM				(1.0E5)			/* number of cm in a km		*/
#define KM_PER_AU				(CM_PER_AU / CM_PER_KM)
#define CM_PER_METER			(100.0)
//#define MILLIBARS_PER_BAR		(1013.25)
#define MILLIBARS_PER_BAR		(1000.00)

#define GRAV_CONSTANT			(6.672E-8)		/* units of dyne cm2/gram2	*/
#define MOLAR_GAS_CONST			(8314.41)		/* units: g*m2/(sec2*K*mol) */
#define K						(50.0)			/* K = gas/dust ratio		*/
#define B						(1.2E-5)		/* Used in Crit_mass calc	*/
#define DUST_DENSITY_COEFF		(2.0E-3)		/* A in Dole's paper		*/
#define ALPHA					(5.0)			/* Used in density calcs	*/
#define N						(3.0)			/* Used in density calcs	*/
#define J						(1.46E-19)		/* Used in day-length calcs (cm2/sec2 g) */
#ifdef HUGE_VAL
#define INCREDIBLY_LARGE_NUMBER HUGE_VAL
#else
#define INCREDIBLY_LARGE_NUMBER (9.9999E37)
#endif

/*	Now for a few molecular weights (used for RMS velocity calcs):	   */
/*	This table is from Dole's book "Habitable Planets for Man", p. 38  */

#define ATOMIC_HYDROGEN			(1.0)	/* H   */
#define MOL_HYDROGEN			(2.0)	/* H2  */
#define HELIUM					(4.0)	/* He  */
#define ATOMIC_NITROGEN			(14.0)	/* N   */
#define ATOMIC_OXYGEN			(16.0)	/* O   */
#define METHANE					(16.0)	/* CH4 */
#define AMMONIA					(17.0)	/* NH3 */
#define WATER_VAPOR				(18.0)	/* H2O */
#define NEON					(20.2)	/* Ne  */
#define MOL_NITROGEN			(28.0)	/* N2  */
#define CARBON_MONOXIDE			(28.0)	/* CO  */
#define NITRIC_OXIDE			(30.0)	/* NO  */
#define MOL_OXYGEN				(32.0)	/* O2  */
#define HYDROGEN_SULPHIDE		(34.1)	/* H2S */
#define ARGON					(39.9)	/* Ar  */
#define CARBON_DIOXIDE			(44.0)	/* CO2 */
#define NITROUS_OXIDE			(44.0)	/* N2O */
#define NITROGEN_DIOXIDE		(46.0)	/* NO2 */
#define OZONE					(48.0)	/* O3  */
#define SULPH_DIOXIDE			(64.1)	/* SO2 */
#define SULPH_TRIOXIDE			(80.1)	/* SO3 */
#define KRYPTON					(83.8)	/* Kr  */
#define XENON					(131.3) /* Xe  */

//	And atomic numbers, for use in ChemTable indexes
#define AN_H	1
#define AN_HE	2
#define AN_N	7
#define AN_O	8
#define AN_F	9
#define AN_NE	10
#define AN_P	15
#define AN_CL	17
#define AN_AR	18
#define AN_BR	35
#define AN_KR	36
#define AN_I	53
#define AN_XE	54
#define AN_HG	80
#define AN_AT	85
#define AN_RN	86
#define AN_FR	87

#define AN_NH3	900
#define AN_H2O	901
#define AN_CO2	902
#define AN_O3	903
#define AN_CH4	904
#define AN_CH3CH2OH	905

/*	The following defines are used in the kothari_radius function in	*/
/*	file enviro.c.														*/
#define A1_20					(6.485E12)		/* All units are in cgs system.	 */
#define A2_20					(4.0032E-8)		/*	 ie: cm, g, dynes, etc.		 */
#define BETA_20					(5.71E12)

#define JIMS_FUDGE				(1.004)

#define SUNMAG 4.83	/* absolute magnitude of the sun */
#define N2 2.51188643150958	/* 5th root of 100 */

/*	 The following defines are used in determining the fraction of a planet	 */
/*	covered with clouds in function cloud_fraction in file enviro.c.		 */
#define Q1_36					(1.258E19)		/* grams	*/
#define Q2_36					(0.0698)		/* 1/Kelvin */

/* macros: */
#define pow2(a) ((a) * (a))
#define pow3(a) ((a) * (a) * (a))
#define pow4(a) ((a) * (a) * (a) * (a))
#define pow1_4(a)		sqrt(sqrt(a))
#define pow1_3(a)		pow(a,(1.0/3.0))
#define pow1_2(a)		sqrt(a)
/*define mass(a) pow(a, (1.0/3.5)) calculates mass based on luminosity (a) */
//define mass(a) (a <= (0.3815*pow(0.6224,2.5185))) ? ((log(a)/log(2.5185))/0.6224) : (a <= 1) ? (log(a)/log(4.551)) : (a <= pow(3.1623, 4.351)) ? (log(a)/log(4.351)) : (a <= (2.7563*pow(16,3.4704))) ? ((log(a)/log(3.4704))/2.7563) : ((log(a)/log(2.4853))/42.321) /* calculates mass based on luminosity (a) */
#define mass(a) (a <= (0.3815*pow(0.6224,2.5185))) ? (1.46613*pow(a,0.3970617431010522)) : (a <= 1) ? pow(a,0.2197319270490002) : (a <= pow(3.1623, 4.351)) ? pow(a,0.2298322224775914) : (a <= (2.7563*pow(16,3.4704))) ? (0.746654*pow(a,0.2881512217611803)) : (0.221579*pow(a,0.4023659115599726)) /* calculates mass based on luminosity (a) */
#define abs2luminosity(a) pow(N2,(SUNMAG-a)) /* calculates luminosity based on absolute magnitude (a) */

#define EM(x)		(x)/SUN_MASS_IN_EARTH_MASSES
#define AVE(x,y)	((x+y)/2.)
#define ADD(x,y)	(x+y)
#define DIVIDE(x,y)	(x/y)

#define JUPITER_MASS 317.8 /* mass of Jupiter in Earth Masses */
#define KM_JUPITER_RADIUS 71492.0 /* radius of Jupiter in km */

#define ICE_DENSITY 0.9167 /* Units of g/cc */
#define IRON_DENSITY 7.874 /* Units of g/cc */
#define ROCK_DENSITY 4.7825 /* Units of g/cc (derived from ((EARTH_DENSITY - (IRON_DENSITY / 3))/(2/3)) */
