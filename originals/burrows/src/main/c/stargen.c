/*
 *	StarGen API
 *
 *	This file provides the main program interface to StarGen.
 *	An example of calling it is the command-line interface defined in
 *	main.c.
 *
 *	$Id: stargen.c,v 1.30 2006/02/11 04:08:03 brons Exp $
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>
#include	<time.h>
#include	<ctype.h>

#include	"Dumas.h"

#ifdef THINK_C
#define macintosh 1
#endif

#ifdef macintosh
#include	<console.h>
#include	<unix.h>
#else
#include	<sys/types.h>
#endif

#ifdef MSDOS
#include	<stddef.h>
#include	<stdlib.h>
#include	<float.h>
#endif

#ifdef WIN32
#pragma warning (disable: 4048) // Hush compiler - don't complain about storing specific arrays in generic pointers
#endif

#include	"const.h"
#include	"structs.h"
#include 	"accrete.h"
#include	"enviro.h"
#include	"display.h"
#include	"stargen.h"
#include	"utils.h"

char *	stargen_revision = "$Revision: 1.30 $";

/*  These are the global variables used during accretion:  */
planet_pointer	innermost_planet;
long double		dust_density_coeff = DUST_DENSITY_COEFF;


int flag_verbose = 0;
// 0x0001			Earthlike count
// 0x0002			Trace Min/max
// 0x0004			List habitable
// 0x0008			List Earth-like (and Sphinx-line)

// 0x0010			List Gases
// 0x0020			Trace temp iterations
// 0x0040			Gas lifetimes
// 0x0080			List loss of accreted gas mass

// 0x0100			Injecting, collision
// 0x0200			Checking..., Failed...
// 0x0400			List binary info
// 0x0800			List Gas Dwarfs etc.

// 0x1000			Moons
// 0x2000			Oxygen poisoned
// 0x4000			Trace gas %ages (whoops)
// 0x8000			Jovians in habitable zone

long flag_seed		 = 0;

int earthlike		 = 0;
int habitable		 = 0;
int habitable_jovians= 0;
int total_habitable	 = 0;

long double	min_breathable_terrestrial_g = 1000.0;
long double	min_breathable_g			 = 1000.0;
long double	max_breathable_terrestrial_g = 0.0;
long double	max_breathable_g			 = 0.0;
long double	min_breathable_temp			 = 1000.0;
long double	max_breathable_temp			 = 0.0;
long double	min_breathable_p			 = 100000.0;
long double	max_breathable_p			 = 0.0;

int type_counts[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int	type_count = 0;
int max_type_count = 0;

/*	Define the solar system for comparisons, etc. */
#define ZEROES 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,NULL,tUnknown,NULL

#define EM(x)		(x)/SUN_MASS_IN_EARTH_MASSES
#define AVE(x,y)	((x+y)/2.)

			/*	No Orbit Eccen. Tilt   Mass    Gas Giant? Dust Mass   Gas */
planets pluto  ={10,39.529,0.248,122.5, EM(0.002),  FALSE, EM(0.002),    0, ZEROES, NULL};
planets neptune={ 9,30.061,0.010, 29.6, EM(17.14),  TRUE,  0,   EM(17.14),  ZEROES, &pluto};
planets uranus ={ 8,19.191,0.046, 97.9, EM(14.530), TRUE,  0,   EM(14.530), ZEROES, &neptune};
planets saturn ={ 7,9.539, 0.056, 26.7, EM(95.18),  TRUE,  0,   EM(95.18),  ZEROES, &uranus};
planets jupiter={ 6,5.203, 0.048,  3.1, EM(317.9),  TRUE,  0,   EM(317.9),  ZEROES, &saturn};
planets ceres  ={ 5,2.767, 0.079,  0, EM(0.000134), FALSE, EM(0.000134), 0, ZEROES, &jupiter};
planets mars   ={ 4,1.524, 0.093, 25.2, EM(0.1074), FALSE, EM(0.1074),   0, ZEROES, &ceres};
planets earth  ={ 3,1.000, 0.017, 23.5, EM(1.00),   FALSE, EM(1.00),     0, ZEROES, &mars};
planets venus  ={ 2,0.723, 0.007,177.3, EM(0.815),  FALSE, EM(0.815),    0, ZEROES, &earth};
planets mercury={ 1,0.387, 0.206,  2,   EM(0.055),  FALSE, EM(0.055),    0, ZEROES, &venus};
planet_pointer solar_system = &mercury;

planets	titan  ={ 7,9.539, 0.056, 26.7 , EM(0.02259), FALSE, EM(0.02259),EM(.001), ZEROES, &uranus};

/* Seeds for accreting the solar system */
			/*	 No Orbit  Eccen... */
planets pluto1  ={10,39.529,0.248, 0, 0, 0, 0, 0, ZEROES, NULL};
planets pluto2  ={10,39.529,0.15,  0, 0, 0, 0, 0, ZEROES, NULL};	// The real eccentricity 
planets mars1   ={ 4,1.524, 0.093, 0, 0, 0, 0, 0, ZEROES, &pluto2};	// collides Pluto+Neptune
planets ceres1  ={ 5,2.767, 0.079, 0, 0, 0, 0, 0, ZEROES, &mars1};
planets saturn1 ={ 7,9.539, 0.056, 0, 0, 0, 0, 0, ZEROES, &ceres1};
planets uranus1 ={ 8,19.191,0.046, 0, 0, 0, 0, 0, ZEROES, &saturn1};
planets neptune1={ 9,30.061,0.010, 0, 0, 0, 0, 0, ZEROES, &uranus1};
planets jupiter1={ 6,5.203, 0.048, 0, 0, 0, 0, 0, ZEROES, &neptune1};
planets mercury1={ 1,0.387, 0.206, 0, 0, 0, 0, 0, ZEROES, &jupiter1};
planets earth1  ={ 3,1.000, 0.017, 0, 0, 0, 0, 0, ZEROES, &mercury1};
planets venus1  ={ 2,0.723, 0.007, 0, 0, 0, 0, 0, ZEROES, &earth1};
planet_pointer solar_system1 = &venus1;

planets eriEpsI	={ 1,3.3,	0.608, 	0, 0, 0, 0, 0, ZEROES, NULL};
planets UMa47II	={ 2,3.73,	0,     	0, 0, 0, 0, 0, ZEROES, NULL};
planets UMa47I	={ 1,2.11, 	0.096, 	0, 0, 0, 0, 0, ZEROES, &UMa47II};
planets horIotI	={ 1,0.925,	0.161,	0, 0, 0, 0, 0, ZEROES, NULL};

			/*	No Orbit Eccen. Tilt   Mass    Gas Giant? Dust Mass   Gas */
planets	smallest={0, 0.0, 0.0,	20.0,	EM(0.4),   FALSE,  EM(0.4),   0.0, ZEROES, NULL};
planets	average	={0, 0.0, 0.0,	20.0,	EM(1.0),   FALSE,  EM(1.0),    0.0, ZEROES, NULL};
planets	largest	={0, 0.0, 0.0,	20.0,	EM(1.6),   FALSE,  EM(1.6),   0.0, ZEROES, NULL};
 
				/*    L  Mass	Mass2	Eccen.	SemiMajorAxis	Designation	Name	*/
star	perdole[] = {{0, 1.00,	0,		0,		0,				 &mercury,	"Sol",		 1, "The Solar System"},
					 {0, 1.08,	0.88,	0.52,	23.2,			 NULL,		"ALF Cen A", 1, "Alpha Centauri A"},
					 {0, 0.88,	1.08,	0.52,	23.2,			 NULL,		"ALF Cen B", 1, "Alpha Centauri B"},
					 {0, 0.80,	0,		0,		0,				 &eriEpsI,	"EPS Eri",	 1, "Epsilon Eridani"},
					 {0, 0.82,	0,		0,		0,				 NULL,		"TAU Cet",	 1, "Tau Ceti"},
					 {0, 0.90,	0.65,	0.50,	AVE(22.8,24.3),	 NULL,		"70 Oph",	 1, "70 Ophiuchi A"},
					 {0, 0.94,	0.58,	0.53,	AVE(69.,71.),	 NULL,		"ETA Cas",	 1, "Eta Cassiopeiae A"},
					 {0, 0.82,	0,		0,		0,				 NULL,		"SIG Dra",	 1, "Sigma Draconis"},
					 {0, 0.77,	0.76,	0,		22.,			 NULL,		"36 Oph",	 1, "36 Ophiuchi A"},
					 {0, 0.76,	0.77,	0,		22.,			 NULL,		"36 Oph B",	 0, "36 Ophiuchi B"},
/*					 {0, 0.76,	0,		0,		46.,			 NULL,		"HD 191408", 1, "HR7703 A"}, */
/* Fake up a B just to clip the distances -- need the real data */
					 {0, 0.76,	.5,		.5,		46.,			 NULL,		"HD 191408", 1, "HR7703 A"},
					 {0, 0.98,	0,		0,		0,				 NULL,		"DEL Pav",	 1, "Delta Pavonis"},
					 {0, 0.91,	0,		0,		0,				 NULL,		"82 Eri",	 1, "82 Eridani"},
					 {0, 1.23,	0,		0,		0,				 NULL,		"BET Hyi",	 1, "Beta Hydri"},
					 {0, 0.74,	0,		0,		0,				 NULL,		"HD 219134", 1, "HR8832"},
					 {0, 0.725,0,		0,		1100.,			 NULL,		"HD 16160",	 1, "HR753 A"}
					};

/*
 *	The following values were taken from: http://www.solstation.com/stars.htm
 */

star	web[] = 
// L			Mass			Mass2			Eccen.	SMAxis	 Planets	Designation	Name
{{1.00,			1.00,			0,				0,		0,		 &mercury,	"Sol",		 1, "The Solar System"},		// 0
 {1.60,			1.09,			0.90,			0.519,	23.7,	 NULL,		"ALF Cen A", 1, "Alpha Centauri A"},		// 4.4
 {0.45,			0.90,			1.09,			0.519,	23.7,	 NULL,		"ALF Cen B", 1, "Alpha Centauri B"},		// 4.4
 {0.34,			0.85,			0,				0,		0,		 &eriEpsI,	"EPS Eri",	 1, "Epsilon Eridani"},			// 10.5 
//{AVE(6.3,8.9),0.59,			0.5,			.48,	85.2,	 NULL,		"61 Cyg A",	 1, "61 Cygni A"},				// 11.4
 {0.085,		0.59,			0.5,			.48,	85.2,	 NULL,		"61 Cyg A",	 1, "61 Cygni A"},				// 11.4
 {0.59,			0.82,			0,				0,		0,		 NULL,		"TAU Cet",	 1, "Tau Ceti"},				// 11.9 
 {0.38,			0.75,			(0.16+0.43),	0,		418.,	 NULL,		"40 Eri",	 1, "40 Eridani A"},			// 16.5
 {AVE(.44,.47),	0.924,			0.701,			0.495,	23.3,	 NULL,		"70 Oph",	 1, "70 Ophiuchi A"},			// 16.6
 {0.39,			0.82,			0,				0,		0,		 NULL,		"SIG Dra",	 1, "Sigma Draconis"},			// 18.8 
 {0.156,		0.76,			(0.55+0.35),	0.20,	190.,	 NULL,		"33 g Lib",	 1, "HR 5568"},					// 19.3
 {AVE(1.0,1.29),0.91,			0.56,			0.497,	71.0,	 NULL,		"ETA Cas",	 1, "Eta Cassiopeiae A"},		// 19.4
 {0.23,			0.82,			0.20,			.5,		43.,	 NULL,		"HD 191408", 1, "HR 7703 (HJ 5173) A"},		// 19.7
 {0.65,			0.97,			0,				0,		0,		 NULL,		"82 Eri",	 1, "82 Eridani"},				// 19.8
 {1.2,			0.98,			0,				0,		0,		 NULL,		"DEL Pav",	 1, "Delta Pavonis"},			// 19.9
 {0,			0.74,			0,				0,		0,		 NULL,		"HD 219134", 1, "HR 8832"},					// 21.3
 {0.52,			0.90,			0.76,			0.51,	33.6,	 NULL,		"XI Boo",	 1, "Xi Bootis A"},				// 21.8
 {0.21,			0.81,			0.082,			.75,	15.,	 NULL,		"HD 16160",	 1, "HR 753 A"},				// 23.5
 {0.24,			0.83,			0,				0,		0,		 NULL,		"HD 4628",	 1, "BD+04 123 (HR 222)"},		// 24.3
 {3.6,			1.1,			0,				0,		0,		 NULL,		"BET Hyi",	 1, "Beta Hydri"},				// 24.4 
 {0.37,			0.89,			0,				0,		0,		 NULL,		"107 Psc",	 1, "107 Piscium"},				// 24.4 
														// 107 Psc p1 = Klotho in Celestia's imagined.ssc
 {3.,			1.3,			0,				0,		0,		 NULL,		"PI3 Ori",	 1, "Pi3 Orionis A"},			// 26.2
 {0.28,			0.88,			0.86,			0.534,	63.7,	 NULL,		"RHO1 Eri",	 1, "Rho Eridani A"},			// 26.6 
 {0.25,			0.86,			0.88,			0.534,	63.7,	 NULL,		"RHO2 Eri",	 1, "Rho Eridani B"},			// 26.6 
 {1.2,			1.07,			0,				0,		0,		 NULL,		"BET CVn",	 1, "Chara"},					// 27.3 
 {2.9,			.90,			1.45,			0.412,	21.2,	 NULL,		"XI UMa",	 1, "Xi Ursae Majoris Ba"},		// 27.3 
//																	Xi Urs Maj aka Alula Australis
//					55203:Alula Australis:XI UMa:53 UMa defined in Celestia starnames, but no data
 {0.80,			0.96,			0,				0,		0,		 NULL,		"61 Vir",	 1, "61 Virginis"},				// 27.8  
 {1.3,			0.98,			0,				0,		0,		 NULL,		"ZET Tuc",	 1, "Zeta Tucanae"},			// 28.0
 {1.08,			1.0,			.15,			0.45,	6.4,	 NULL,		"CHI1 Ori",	 1, "Chi1 Orionis A"},			// 28.3 
//					41 Arae masses are Wieth-Knudsen's 1957 estimates,
 {0.41,			0.9,			.6,				0.779,	91.5,	 NULL,		"41 Ari",	 1, "41 Arae A"},				// 28.7 
 {0.21,			0.845,			0,				0,		0,		 NULL,		"HR 1614",	 0, "BD-05 1123 (HR 1614) A"},	// 28.8 
 {0.33,			0.87,			0,				0,		0,		 NULL,		"HR 7722",	 0, "CD-27 14659 (HR 7722)"},	// 28.8 
 {2.6,			1.2,			.63,			.5,		864.,	 NULL,		"GAM Lep",	 1, "Gamma Leporis A"},			// 29.3 
 {1.4,			1.05,			0,				0,		0,		 NULL,		"BET Com",	 1, "Beta Comae Berenices"},	// 29.9   
 {0.85,			1.0,			0,				0,		0,		 NULL,		"KAP1 Cet",	 1, "Kappa Ceti"},				// 29.9   
 {1.5,			0.8,			0,				0,		0,		 NULL,		"GAM Pav",	 1, "Gamma Pavonis"},			// 30.1
 {0.82,			0.8,			0.07,			0.6,	235.,	 NULL,		"HD 102365", 1, "HR 4523"},					// 30.1
 {0.588,		0.81,			0,				0,		0,		 NULL,		"61 UMa",	 1, "61 Ursae Majoris"},		// 31.1  
 {0.31,			0.87,			0,				0.5,	80.5,	 NULL,		"HR 4458",	 0, "CD-32 8179 (HR 4458)"},	// 31.1 
 {AVE(.39,.41),	0.90,			0,				0,		0,		 NULL,		"12 Oph",	 1, "12 Ophiuchi"},				// 31.9
 {0.46,			0.92,			0,				0,		0,		 NULL,		"HR 511",	 0, "BD+63 238 (HR 511)"},		// 32.5
 {0.83,			0.87,			0,				0,		0,		 NULL,		"ALF Men",	 1, "Alpha Mensae"},			// 33.1
 {0.93,			0.79,			1.02,			0.5,	9000.,	 NULL,		"ZET1 Ret",	 1, "Zeta 1 Reticuli"},			// 39.4-39.5
 {0.99,			1.02,			0.79,			0.5,	9000.,	 NULL,		"ZET2 Ret",	 1, "Zeta 2 Reticuli"},			// 39.4-39.5
 {1.14,			1.05,			2.0,			0.55,	48.5,	 NULL,		"44 Boo",	 1, "44 Bootis A"},				// 41.6
 {1.7,			1.03,			0,				0,		0,		 &UMa47I,	"47 UMa",	 1, "47 Ursae Majoris"},		// 45.9
 {1.8,			1.03,			0,				0,		0,		 &horIotI,	"IOT Hor",	 1, "Iota Horologii"},			// 56.2


 {AVE(.13,.15),	AVE(.59,.71),	0,				0,		0,		 NULL,		"EPS Ind",	 1, "Epsilon Indi"},			// 11.8  
 {AVE(.083,.09),0.701,			0.924,			0.495,	23.3,	 NULL,		"70 Oph",	 1, "70 Ophiuchi B"},			// 16.6
 {0.28,			0.85,			0.85,			0.922,	88.,	 NULL,		"36 Oph",	 1, "36 Ophiuchi A"},			// 19.5
 {0.27,			0.85,			0.85,			0.922,	88.,	 NULL,		"36 Oph B",	 0, "36 Ophiuchi B"},			// 19.5
 {0.12,			0.75,			0.65,			0.58,	12.6,	 NULL,		"HR 6426",	 0, "MLO 4 (HR 6426) A"},		// 22.7
 {0.146,		0.80,			0.50,			0.5,	500.,	 NULL,		"BD-05 1844 A",0,"BD-05 1844 A"}			// 28.3 
};

// BD-05 1123 A:	 HR 1614, Gl 183 A, Hip 23311, HD 32147, SAO 131688, LHS 200, LTT 2412, LFT 382, and LPM 200. 
// CD-27 14659:		 HR 7722, Gl 785, Hip 99825, HD 192310, CP(D)-27 6972, SAO 189065, LHS 488, LTT 8009, LFT 1535, and LPM 731
// CD-32 8179 A:	 HR 4458, Gl 432 A, Hip 56452, HD 100623, CP(D)-32 3122, SAO 202583, LHS 308, LTT 4280, LFT 823, LPM 389, and E 439-246.  
// BD+63 238:		 HR 511*, Gl 75, Hip 8362, HD 10780, SAO 11983, LHS 1297, LTT 10619, and LFT 162. 
// 36 Ophiuchi B:	 HR 6401, Gl 663 B, HD 155885, SAO 185199, LHS 438, and ADS 10417 B. 
// MLO 4 A:			 HR 6426*, Gl 667 A, Hip 84709, HD 156384, CD-34 11626 A, CP-34 6803, SAO 208670, LHS 442, LTT 6888, LFT 1336, LPM 638, and UGPMF 433. 
// BD-05 1844 A:	 Gl 250 A, Hip 32984, HD 50281, SAO 133805, LHS 1875, LTT 2662, LFT 494, and LPM 244. 

// {.00006,		0.105,			0.1,			0.62,	5.5,	 NULL,		"",	"Luyten 726-8 A"},		// 8.7
// {0.039,		0.5,			0.59,			.48,	85.2,	 NULL,		"",	"61 Cygni B"},			// 11.4
// {0.05,		0.65,			0.75,			0.58,	12.6,	 NULL,		"",	"MLO 4 (HR 6426) B"},	// 22.7
// {1.1,		1.05,			0.4,			0.53,	0.6,	 NULL,		"",	"Xi Ursae Majoris Aa"},	// 27.3 
// {0,			0.4,			1.05,			0.53,	0.6,	 NULL,		"",	"Xi Ursae Majoris Ab"},	// 27.3
// {0.064,		0.76,			0.90,			0.51,	33.0,	 NULL,		"",	"Xi Bootis B"},			// 21.8

catalog	solstation	= {sizeof(web) / sizeof (star), &web};
catalog	dole		= {sizeof(perdole) / sizeof (star), &perdole};

ChemTable    gases[] =
{
//   An   sym   HTML symbol                      name                 Aw      melt    boil    dens       ABUNDe       ABUNDs         Rea	Max inspired pp
  {AN_H,  "H",  "H<SUB><SMALL>2</SMALL></SUB>",	 "Hydrogen",         1.0079,  14.06,  20.40,  8.99e-05,  0.00125893,  27925.4,       1,		0.0},
  {AN_HE, "He", "He",							 "Helium",           4.0026,   3.46,   4.20,  0.0001787, 7.94328e-09, 2722.7,        0,		MAX_HE_IPP},
  {AN_N,  "N",  "N<SUB><SMALL>2</SMALL></SUB>",	 "Nitrogen",        14.0067,  63.34,  77.40,  0.0012506, 1.99526e-05, 3.13329,       0,		MAX_N2_IPP},
  {AN_O,  "O",  "O<SUB><SMALL>2</SMALL></SUB>",	 "Oxygen",          15.9994,  54.80,  90.20,  0.001429,  0.501187,    23.8232,       10,	MAX_O2_IPP},
  {AN_NE, "Ne", "Ne",							 "Neon",            20.1700,  24.53,  27.10,  0.0009,    5.01187e-09, 3.4435e-5,     0,		MAX_NE_IPP},
  {AN_AR, "Ar", "Ar",							 "Argon",           39.9480,  84.00,  87.30,  0.0017824, 3.16228e-06, 0.100925,      0,		MAX_AR_IPP},
  {AN_KR, "Kr", "Kr",							 "Krypton",         83.8000, 116.60, 119.70,  0.003708,  1e-10,       4.4978e-05,    0,		MAX_KR_IPP},
  {AN_XE, "Xe", "Xe",							 "Xenon",          131.3000, 161.30, 165.00,  0.00588,   3.16228e-11, 4.69894e-06,   0,		MAX_XE_IPP},
//                                                                     from here down, these columns were originally: 0.001,         0
  {AN_NH3, "NH3", "NH<SUB><SMALL>3</SMALL></SUB>", "Ammonia",       17.0000, 195.46, 239.66,  0.001,     0.002,       0.0001,        1,		MAX_NH3_IPP},
  {AN_H2O, "H2O", "H<SUB><SMALL>2</SMALL></SUB>O", "Water",         18.0000, 273.16, 373.16,  1.000,     0.03,        0.001,         0,		0.0},
  {AN_CO2, "CO2", "CO<SUB><SMALL>2</SMALL></SUB>", "CarbonDioxide", 44.0000, 194.66, 194.66,  0.001,     0.01,        0.0005,        0,		MAX_CO2_IPP},
  {AN_O3,   "O3", "O<SUB><SMALL>3</SMALL></SUB>",  "Ozone",         48.0000,  80.16, 161.16,  0.001,     0.001,       0.000001,      2,		MAX_O3_IPP},
  {AN_CH4, "CH4", "CH<SUB><SMALL>4</SMALL></SUB>", "Methane",       16.0000,  90.16, 109.16,  0.010,     0.005,       0.0001,        1,		MAX_CH4_IPP},
  { 0, "", "", 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*
  {AN_NH3, "NH3", "NH<SUB><SMALL>3</SMALL></SUB>", "Ammonia",       17.0000, 195.46, 239.66,  0.001,     0.002,       0.001,         0.001,	MAX_NH3_IPP},
  {AN_H2O, "H2O", "H<SUB><SMALL>2</SMALL></SUB>O", "Water",         18.0000, 273.16, 373.16,  1.000,     0.03,        0.001,         0,		(9.9999E37)},
  {AN_CO2, "CO2", "CO<SUB><SMALL>2</SMALL></SUB>", "CarbonDioxide", 44.0000, 194.66, 194.66,  0.001,     0.01,        0.001,         0,		MAX_CO2_IPP},
  {AN_O3,   "O3", "O<SUB><SMALL>3</SMALL></SUB>",  "Ozone",         48.0000,  80.16, 161.16,  0.001,     0.001,       0.001,         0.001,	MAX_O3_IPP},
  {AN_CH4, "CH4", "CH<SUB><SMALL>4</SMALL></SUB>", "Methane",       16.0000,  90.16, 109.16,  0.010,     0.005,       0.001,         0,		MAX_CH4_IPP},

  {AN_F,  "F",  "F",							 "Fluorine",        18.9984,  53.58,  85.10,  0.001696,  0.000630957, 0.000843335,   50,	MAX_F_IPP},
  {AN_CL, "Cl", "Cl",							 "Chlorine",        35.4530, 172.22, 239.20,  0.003214,  0.000125893, 0.005236,      40,	MAX_CL_IPP},

  { 910, "H2", "H2",  2, 14.06, 20.40, 8.99e-05,  0.00125893, 27925.4  },
  { 911, "N2", "N2", 28, 63.34, 77.40, 0.0012506, 1.99526e-05,3.13329  },
  { 912, "O2", "O2", 32, 54.80, 90.20, 0.001429,  0.501187, 23.8232, 10},
  {AN_CH3CH2OH, 
           "CH3CH2OH", "Ethanol",  46.0000, 159.06, 351.66,  0.895,     0.001,       0.001,         0},
*/
int max_gas = (sizeof(gases)/sizeof(ChemTable))-1;

void init(void);
void generate_stellar_system(primary*, int, planet_pointer, char, int, char *, long double, int, int);
void calculate_gases(primary*, planet_pointer, char, int, int, char*);
void generate_planets(primary*, int, char, int, char *, int, int);
void usage(char *);
static int diminishing_abundance(const void *ap, const void *bp);
static int diminishing_pressure(const void *ap, const void *bp);

void init()
{
	if (!flag_seed)
	{
		time_t		temp_time;
		unsigned	seed = (unsigned)(time(&temp_time));

		(void)srand(seed);
		
		flag_seed = rand();
	}
	
	(void)srand(flag_seed);
}

void generate_stellar_system(primary*		sun,
							 int 			use_seed_system, 
							 planet_pointer seed_system,
							 char			flag_char,
							 int			sys_no,
							 char*			system_name,
							 long double 	outer_planet_limit,
							 int			do_gases,
							 int			do_moons)
{
	long double		outer_dust_limit;

	if ((sun->mass < 0.2) || (sun->mass > 1.5))
		sun->mass		 = random_number(0.7,1.4);

	outer_dust_limit	 = stellar_dust_limit(sun->mass);

	if (sun->luminosity == 0)
		sun->luminosity	 = luminosity(sun->mass);
	
	sun->r_ecosphere	 = sqrt(sun->luminosity);
	sun->life			 = 1.0E10 * (sun->mass / sun->luminosity);

	if (use_seed_system)
	{
		innermost_planet = seed_system;
		sun->age = 5.0E9;
	}
	else
	{
		long double min_age = 1.0E9;
		long double max_age = 6.0E9;
		
		if (sun->life < max_age)
			max_age = sun->life;
		
		innermost_planet = dist_planetary_masses(sun->mass,
												 sun->luminosity,
												 0.0,outer_dust_limit,
												 outer_planet_limit,
												 dust_density_coeff,
												 seed_system);

		sun->age = random_number(min_age, max_age);
	}

	generate_planets(sun,
					 !use_seed_system, 
					 flag_char,
					 sys_no,
					 system_name,
					 do_gases,
					 do_moons);
}

void calculate_gases(primary*		sun,
					 planet_pointer	planet,
					 char			flag_char,
					 int			sys_no,
					 int			planet_no,
					 char*			system_name)
{
	if (planet->surf_pressure > 0)
	{
		long double	*amount = (long double*)calloc((max_gas+1), sizeof(long double));
		long double	totamount = 0;
		long double pressure  = planet->surf_pressure/MILLIBARS_PER_BAR;
		int			n         = 0;
		int			i;

		for (i = 0; i < max_gas; i++)
		{
			long double bp = gases[i].boil /
							 (373. * ((log((pressure) + 0.001) / -5050.5) + 
									 (1.0 / 373.)));
			
			if ((bp >= 0 && bp < planet->low_temp)
			 && (gases[i].weight >= planet->molec_weight))
			{
				long double	vrms	= rms_vel(gases[i].weight, planet->a);
				long double	pvrms	= pow(1 / (1 + vrms / planet->esc_velocity), sun->age / 1e9);
				long double	abund	= gases[i].abunds; 				/* gases[i].abunde */
				long double react	= 1.0;
				long double fract	= 1.0;
				long double pres2	= 1.0;
				
				if (strcmp(gases[i].symbol, "Ar") == 0)
				{
					react = .19 * sun->age/4e9;
				}
				else if (strcmp(gases[i].symbol, "He") == 0)
				{
					abund = abund * (0.001 + (planet->gas_mass / planet->mass));
					pres2 = (0.75 + pressure);
					react = pow(1 / (1 + gases[i].reactivity), 
								sun->age/2e9 * pres2);
				}
				else if ((strcmp(gases[i].symbol, "O") == 0 ||
						  strcmp(gases[i].symbol, "O2") == 0) && 
						 sun->age > 2e9 &&
						 planet->surf_temp > 270 && planet->surf_temp < 400)
				{
				/*	pres2 = (0.65 + pressure/2);			Breathable - M: .55-1.4 	*/
					pres2 = (0.89 + pressure/4);		/*	Breathable - M: .6 -1.8 	*/
					react = pow(1 / (1 + gases[i].reactivity), 
								pow(sun->age/2e9, 0.25) * pres2);
				}
				else if (strcmp(gases[i].symbol, "CO2") == 0 && 
						 sun->age > 2e9 &&
						 planet->surf_temp > 270 && planet->surf_temp < 400)
				{
					pres2 = (0.75 + pressure);
					react = pow(1 / (1 + gases[i].reactivity), 
								pow(sun->age/2e9, 0.5) * pres2);
					react *= 1.5;
				}
				else 
				{
					pres2 = (0.75 + pressure);
					react = pow(1 / (1 + gases[i].reactivity), 
								sun->age/2e9 * pres2);
				}
				
				fract = (1 - (planet->molec_weight / gases[i].weight));
				
				amount[i] = abund * pvrms * react * fract;

				if ((flag_verbose & 0x4000) &&
					(strcmp(gases[i].symbol, "O") == 0 ||
					 strcmp(gases[i].symbol, "N") == 0 ||
					 strcmp(gases[i].symbol, "Ar") == 0 ||
					 strcmp(gases[i].symbol, "He") == 0 ||
					 strcmp(gases[i].symbol, "CO2") == 0))
				{
					fprintf (stderr, "%-5.2Lf %-3.3s, %-5.2Lf = a %-5.2Lf * p %-5.2Lf * r %-5.2Lf * p2 %-5.2Lf * f %-5.2Lf\t(%.3Lf%%)\n",
							  planet->mass * SUN_MASS_IN_EARTH_MASSES,
							  gases[i].symbol,
							  amount[i],
							  abund,
							  pvrms,
							  react,
							  pres2,
							  fract,
							  100.0 * (planet->gas_mass / planet->mass)
							 );
				}

				totamount += amount[i];
				if (amount[i] > 0.0)
					n++;
			}
			else
				amount[i] = 0.0;
		}

		if (n > 0)
		{
			planet->gases = n;
			planet->atmosphere = (gas*)calloc(n, sizeof(gas));
			
			for (i = 0, n = 0; i < max_gas; i++)
			{
				if (amount[i] > 0.0)
				{
					planet->atmosphere[n].num = gases[i].num;
					planet->atmosphere[n].surf_pressure = planet->surf_pressure 
														* amount[i] / totamount;

					if (flag_verbose & 0x2000)
					{
						if ((planet->atmosphere[n].num == AN_O) &&
							inspired_partial_pressure (planet->surf_pressure,
													   planet->atmosphere[n].surf_pressure)
							> gases[i].max_ipp)
						{
							fprintf (stderr, "%s (-s%ld -%c%d) %d\t Poisoned by O2\n",
									 system_name,
									 flag_seed, flag_char, sys_no,
									 planet_no
									 );
						}
					}
					
					n++;
				}
			}

			qsort(planet->atmosphere, 
				  planet->gases, 
				  sizeof(gas), 
				  diminishing_pressure);

			if (flag_verbose & 0x0010)
			{
				fprintf (stderr, "\nPlanet %d (%5.1Lf AU) gases:\n",
						planet_no, planet->a);
				
				for (i = 0; i < planet->gases; i++)
				{
					fprintf (stderr, "%3d: %6.1Lf, %11.7Lf%%\n",
							planet->atmosphere[i].num,
							planet->atmosphere[i].surf_pressure,
							100. * (planet->atmosphere[i].surf_pressure /
									planet->surf_pressure)
							);
				}
			}
		}
		
		free(amount);
	}
}

void generate_planets(primary*		sun,
					  int 			random_tilt, 
					  char			flag_char,
					  int			sys_no,
					  char*			system_name,
					  int			do_gases,
					  int			do_moons)
{
	planet_pointer	planet;
	int				planet_no = 0;

	for (planet = innermost_planet, planet_no = 1; 
		 planet != NULL; 
		 planet = planet->next_planet, planet_no++)
	{
		planet->first_moon		= NULL;
		planet->atmosphere		= NULL;
		planet->gases			= 0;
		planet->high_temp		= 0;
		planet->low_temp		= 0;
		planet->max_temp		= 0;
		planet->min_temp		= 0;
		planet->greenhs_rise	= 0;
		planet->planet_no		= planet_no;
		planet->primary			= sun;
		planet->resonant_period = FALSE;

#ifdef MOONS
		if (do_moons)
		{
			long double m1 = planet->mass;
			long double m2 = sun->mass;
			long double mu = m2 / (m1 + m2);
			long double e = planet->e;
			long double a = planet->a;
			long double outer_limit = (0.464 + (-0.380 * mu) + (-0.631 * e) +
									   (0.586 * mu * e) + (0.150 * pow2(e)) +
									   (-0.198 * mu * pow2(e))) * a;
//			long double farthest = farthest_planet(planet->mass);
			long double outer_dust = stellar_dust_limit(planet->mass);

//			if (outer_limit > farthest)
//				outer_limit = farthest;
			
		    planet->first_moon = dist_moon_masses (planet->mass,
												   sun->luminosity,
												   planet->a, 
												   planet->e,
												   0.0, 
												   outer_dust,
												   1.0,
												   outer_limit);
			if (planet->first_moon)
			{
				int 			n;
				planet_pointer	ptr;
				for (n=0, ptr=planet->first_moon;
					 ptr != NULL;
					 ptr=ptr->next_planet)
				{
					if (ptr->mass * SUN_MASS_IN_EARTH_MASSES > .0001)
					{
						n++;
						fprintf (stderr, "%d: %d %6.3Lg %6.3Lg\n",	
								planet_no,
								n,
								ptr->mass * SUN_MASS_IN_EARTH_MASSES,
								ptr->mass / planet->mass);
					}
				}
			}
		}
#endif

		planet->orbit_zone 		= orb_zone(sun->luminosity, planet->a);

		planet->orb_period		= period(planet->a,planet->mass,sun->mass);
		if (random_tilt)
			planet->axial_tilt 	= inclination(planet->a);
		planet->exospheric_temp = EARTH_EXOSPHERE_TEMP / pow2(planet->a / sun->r_ecosphere);
		planet->rms_velocity 	= rms_vel(MOL_NITROGEN,planet->exospheric_temp);
		planet->core_radius 	= kothari_radius(planet->dust_mass,FALSE,planet->orbit_zone);

		// Calculate the radius as a gas giant, to verify it will retain gas.
		// Then if mass > Earth, it's at least 5% gas and retains He, it's
		// some flavor of gas giant.
		
		planet->density 		= empirical_density(planet->mass,planet->a, sun->r_ecosphere, TRUE);
		planet->radius 			= volume_radius(planet->mass,planet->density);
		
		planet->surf_accel   	= acceleration(planet->mass,planet->radius);
		planet->surf_grav 	 	= gravity(planet->surf_accel);

		planet->molec_weight	= min_molec_weight(planet);

		if (((planet->mass * SUN_MASS_IN_EARTH_MASSES) > 1.0)
		  && ((planet->gas_mass / planet->mass)        > 0.05)
		  && (min_molec_weight(planet)				  <= 4.0))
		{
			if ((planet->gas_mass / planet->mass) < 0.20)
				planet->type = tSubSubGasGiant;
			else if ((planet->mass * SUN_MASS_IN_EARTH_MASSES) < 20.0)
				planet->type = tSubGasGiant;
			else
				planet->type = tGasGiant;
		}
		else // If not, it's rocky.
		{
			planet->radius 		= kothari_radius(planet->mass,FALSE,planet->orbit_zone);
			planet->density 	= volume_density(planet->mass,planet->radius);

			planet->surf_accel  = acceleration(planet->mass,planet->radius);
			planet->surf_grav 	= gravity(planet->surf_accel);
			
			if ((planet->gas_mass / planet->mass)        > 0.000001)
			{
				long double h2_mass = planet->gas_mass * 0.85;
				long double he_mass = (planet->gas_mass - h2_mass) * 0.999;
				
				long double h2_loss = 0.0;
				long double he_loss = 0.0;
				
							 
				long double h2_life = gas_life(MOL_HYDROGEN, planet);
				long double he_life = gas_life(HELIUM, planet);
								
				if (h2_life < sun->age)
				{
					h2_loss = ((1.0 - (1.0 / exp(sun->age / h2_life))) * h2_mass);
					
					planet->gas_mass -= h2_loss;
					planet->mass     -= h2_loss;
					
					planet->surf_accel  = acceleration(planet->mass,planet->radius);
					planet->surf_grav 	= gravity(planet->surf_accel);
				}
				
				if (he_life < sun->age)
				{
					he_loss = ((1.0 - (1.0 / exp(sun->age / he_life))) * he_mass);
					
					planet->gas_mass -= he_loss;
					planet->mass     -= he_loss;
					
					planet->surf_accel  = acceleration(planet->mass,planet->radius);
					planet->surf_grav 	= gravity(planet->surf_accel);
				}
				
				if (((h2_loss + he_loss) > .000001) && (flag_verbose & 0x0080))
					fprintf (stderr, "%s (-s%ld -%c%d) %d\tLosing gas: H2: %5.3Lf EM, He: %5.3Lf EM\n",
							 system_name,
							 flag_seed, flag_char, sys_no,
							 planet_no,
							 h2_loss * SUN_MASS_IN_EARTH_MASSES, he_loss * SUN_MASS_IN_EARTH_MASSES);
			}
		}

		planet->day = day_length(planet);	/* Modifies planet->resonant_period */
		planet->esc_velocity 	= escape_vel(planet->mass,planet->radius);

		if ((planet->type == tGasGiant)
		 || (planet->type == tSubGasGiant) 
		 || (planet->type == tSubSubGasGiant))
		{
			planet->greenhouse_effect 		= FALSE;
			planet->volatile_gas_inventory 	= INCREDIBLY_LARGE_NUMBER;
			planet->surf_pressure 			= INCREDIBLY_LARGE_NUMBER;
			
			planet->boil_point 				= INCREDIBLY_LARGE_NUMBER;
			
			planet->surf_temp				= INCREDIBLY_LARGE_NUMBER;
			planet->greenhs_rise 			= 0;
			planet->albedo 					= about(GAS_GIANT_ALBEDO,0.1);
			planet->hydrosphere 			= 1.0;
			planet->cloud_cover	 			= 1.0;
			planet->ice_cover	 			= 0.0;
			planet->surf_grav			 	= gravity(planet->surf_accel);
			planet->molec_weight			= min_molec_weight(planet);
			planet->surf_grav 				= INCREDIBLY_LARGE_NUMBER;
 			planet->estimated_temp			= est_temp(sun->r_ecosphere, planet->a,  planet->albedo);
			planet->estimated_terr_temp		= est_temp(sun->r_ecosphere, planet->a,  EARTH_ALBEDO);
 			
			{
				long double temp = planet->estimated_terr_temp;

				if ((temp >= FREEZING_POINT_OF_WATER)
				 && (temp <= EARTH_AVERAGE_KELVIN + 10.)
				 && (sun->age > 2.0E9))
				{
					habitable_jovians++;
				
					if (flag_verbose & 0x8000)
					{
						fprintf (stderr, "%s (-s%ld -%c%d) %d\t%s (%4.2LfEM %5.3Lf By) with earth-like temperature (%.1Lf C, %.1Lf F, %+.1Lf C Earth).\n",
								 system_name,
								 flag_seed, flag_char, sys_no,
								 planet_no,
								 planet->type == tGasGiant ? "Jovian" :
								 planet->type == tSubGasGiant ? "Sub-Jovian" :
								 planet->type == tSubSubGasGiant ? "Gas Dwarf" :
								 "Big",
								 planet->mass * SUN_MASS_IN_EARTH_MASSES,
								 sun->age /1.0E9,
								 temp - FREEZING_POINT_OF_WATER,
								 32 + ((temp - FREEZING_POINT_OF_WATER) * 1.8),
								 temp - EARTH_AVERAGE_KELVIN);
					}
				}
			}
		}
		else
		{
			planet->estimated_temp			= est_temp(sun->r_ecosphere, planet->a,  EARTH_ALBEDO);
			planet->estimated_terr_temp		= est_temp(sun->r_ecosphere, planet->a,  EARTH_ALBEDO);

			planet->surf_grav 				= gravity(planet->surf_accel);
			planet->molec_weight			= min_molec_weight(planet);
	
			planet->greenhouse_effect 		= grnhouse(sun->r_ecosphere, planet->a);
			planet->volatile_gas_inventory 	= vol_inventory(planet->mass,
														    planet->esc_velocity,
														    planet->rms_velocity,
														    sun->mass,
														    planet->orbit_zone,
														    planet->greenhouse_effect,
														    (planet->gas_mass
														     / planet->mass) > 0.000001);
			planet->surf_pressure 			= pressure(planet->volatile_gas_inventory,
													   planet->radius,
													   planet->surf_grav);

			if ((planet->surf_pressure == 0.0))
				planet->boil_point 			= 0.0;
			else 
				planet->boil_point 			= boiling_point(planet->surf_pressure);
			
			iterate_surface_temp(planet);		/*	Sets:
												 *		planet->surf_temp
												 *		planet->greenhs_rise
												 *		planet->albedo
												 *		planet->hydrosphere
												 *		planet->cloud_cover
												 *		planet->ice_cover
												 */

			if (do_gases &&
				(planet->max_temp >= FREEZING_POINT_OF_WATER) &&
				(planet->min_temp <= planet->boil_point))
				calculate_gases(sun, planet, flag_char, sys_no, planet_no, system_name);
			
			/*
			 *	Next we assign a type to the planet.
			 */
			 
			if (planet->surf_pressure < 1.0)
			{
				if ((planet->mass * SUN_MASS_IN_EARTH_MASSES) < ASTEROID_MASS_LIMIT)
					planet->type 			= tAsteroids;
				else
					planet->type 			= tRock;
			}
			else if ((planet->surf_pressure > 6000.0) &&
					 (planet->molec_weight <= 2.0))	// Retains Hydrogen
			{
				planet->type = tSubSubGasGiant;
				planet->gases = 0;
				free(planet->atmosphere);
				planet->atmosphere = NULL;
			}
			else 
			{										// Atmospheres:
				if (((int)planet->day == (int)(planet->orb_period * 24.0) || 
										 (planet->resonant_period)))
					planet->type = t1Face;
				else if (planet->hydrosphere >= 0.95)
					planet->type = tWater;				// >95% water
				else if (planet->ice_cover >= 0.95)
					planet->type = tIce;				// >95% ice
				else if (planet->hydrosphere > 0.05)
					planet->type = tTerrestrial;		// Terrestrial
														// else <5% water
				else if (planet->max_temp > planet->boil_point)
					planet->type = tVenusian;			// Hot = Venusian
				else if ((planet->gas_mass / planet->mass) > 0.0001)
				{										// Accreted gas
					planet->type = tIce;				// But no Greenhouse
					planet->ice_cover = 1.0;			// or liquid water
				}										// Make it an Ice World
				else if (planet->surf_pressure <= 250.0)// Thin air = Martian
					planet->type = tMartian;
				else if (planet->surf_temp < FREEZING_POINT_OF_WATER)
					planet->type = tIce;
				else
				{
					planet->type = tUnknown;
					
					if (flag_verbose & 0x0001)
						fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t-s%ld -%c%d\t%s %d\t Unknown %s\n", 
										type_string (planet->type),
										planet->surf_pressure,
										planet->mass * SUN_MASS_IN_EARTH_MASSES,
										planet->surf_grav,
										planet->surf_temp  - EARTH_AVERAGE_KELVIN,
										flag_seed, 
										flag_char,
										sys_no,
										system_name,
										planet_no,
										((int)planet->day == (int)(planet->orb_period * 24.0) || 
										 (planet->resonant_period)) ? "(1-Face)" : ""
								 );
				}
			}
		}
		
		/*
		 *	Now we're ready to test for habitable planets,
		 *	so we can count and log them and such
		 */
{
	int tIndex = 0;

	switch (planet->type)
	{
		case tUnknown:			tIndex = 0;		break;
		case tRock:				tIndex = 1;		break;
		case tVenusian:			tIndex = 2;		break;
		case tTerrestrial:		tIndex = 3;		break;
		case tSubSubGasGiant:	tIndex = 4;		break;
		case tSubGasGiant:		tIndex = 5;		break;
		case tGasGiant:			tIndex = 6;		break;
		case tMartian:			tIndex = 7;		break;
		case tWater:			tIndex = 8;		break;
		case tIce:				tIndex = 9;		break;
		case tAsteroids: 		tIndex = 10;	break;
		case t1Face:			tIndex = 11;	break;
	}
	
	if (type_counts[tIndex] == 0)
		++type_count;
	
	++type_counts[tIndex];
	
}
		{
			unsigned int breathe = breathability (planet);
			
			if ((breathe == BREATHABLE) &&
				(!planet->resonant_period) &&		// Option needed?
				((int)planet->day != (int)(planet->orb_period * 24.0)))
			{
				int	list_it	= FALSE;
				
				habitable++;
				
				if (min_breathable_temp > planet->surf_temp)
				{
					min_breathable_temp = planet->surf_temp;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}

				if (max_breathable_temp < planet->surf_temp)
				{
					max_breathable_temp = planet->surf_temp;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}
			
				if (min_breathable_g > planet->surf_grav)
				{
					min_breathable_g = planet->surf_grav;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}
				
				if (max_breathable_g < planet->surf_grav)
				{
					max_breathable_g = planet->surf_grav;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}
				
				if (planet->type == tTerrestrial)
				{
					if (min_breathable_terrestrial_g > planet->surf_grav)
					{
						min_breathable_terrestrial_g = planet->surf_grav;

						if (flag_verbose & 0x0002)
							list_it = TRUE;
					}

					if (max_breathable_terrestrial_g < planet->surf_grav)
					{
						max_breathable_terrestrial_g = planet->surf_grav;

						if (flag_verbose & 0x0002)
							list_it = TRUE;
					}
				}

				if (min_breathable_p > planet->surf_pressure)
				{
					min_breathable_p = planet->surf_pressure;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}
				
				if (max_breathable_p < planet->surf_pressure)
				{
					max_breathable_p = planet->surf_pressure;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}
									
				if (flag_verbose & 0x0004)
					list_it = TRUE;
				
				if (list_it)
					fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t-s%ld -%c%d\t%s %d\n", 
							type_string (planet->type),
							planet->surf_pressure,
							planet->mass * SUN_MASS_IN_EARTH_MASSES,
							planet->surf_grav,
							planet->surf_temp  - EARTH_AVERAGE_KELVIN,
							flag_seed, 
							flag_char,
							sys_no,
							system_name,
							planet_no);
			}
		}


		if ((flag_verbose & 0x0800)
		 && (planet->dust_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
		 && (planet->gas_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
		 && (planet->type != tGasGiant) 
		 && (planet->type != tSubGasGiant)
		   )
		{
			int core_size = (int)((50. * planet->core_radius) / planet->radius);
			
			if (core_size <= 49)
			{
				fprintf (stderr, "%12s\tp=%4.2Lf\tr=%4.2Lf\tm=%4.2Lf\t-s%ld -%c%d\t%d\t%s %d\n", 
						type_string (planet->type),
						planet->core_radius,
						planet->radius,
						planet->mass * SUN_MASS_IN_EARTH_MASSES,
						flag_seed, 
						flag_char,
						sys_no,
						50-core_size,
						system_name,
						planet_no);
			}
		}
		
		{
			long double  rel_temp   = (planet->surf_temp -  FREEZING_POINT_OF_WATER) - 
						 			   EARTH_AVERAGE_CELSIUS;
			long double	 seas       = (planet->hydrosphere * 100.0);
			long double	 clouds     = (planet->cloud_cover * 100.0);
			long double	 pressure   = (planet->surf_pressure / 
									   EARTH_SURF_PRES_IN_MILLIBARS);
			long double	 ice        = (planet->ice_cover * 100.0);
			long double	 gravity    = planet->surf_grav;
			unsigned int breathe    = breathability (planet);
		
			if ((gravity 	>= .8) &&
				(gravity 	<= 1.2) &&
				(rel_temp 	>= -2.0) &&
				(rel_temp 	<= 3.0) &&
				(ice 		<= 10.) &&
				(pressure   >= 0.5) &&
				(pressure   <= 2.0) &&
				(clouds		>= 40.) &&
				(clouds		<= 80.) &&
				(seas 		>= 50.) &&
				(seas 		<= 80.) &&
				(planet->type != tWater) &&
				(breathe    == BREATHABLE))
			{
				earthlike++;
				
				if (flag_verbose & 0x0008)
					fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%d -s%ld -%c%d\t%s %d\tEarth-like\n", 
									type_string (planet->type),
									planet->surf_pressure,
									planet->mass * SUN_MASS_IN_EARTH_MASSES,
									planet->surf_grav,
									planet->surf_temp  - EARTH_AVERAGE_KELVIN,
									habitable,
									flag_seed, 
									flag_char,
									sys_no,
									system_name,
									planet_no);
			} else if ((flag_verbose & 0x0008) &&
					 (breathe   == BREATHABLE) &&
					 (gravity	 > 1.3) &&
					 (habitable	 > 1) &&
					 ((rel_temp  < -2.0) ||
					  (ice		 > 10.))
					)
			{
				fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%d -s%ld -%c%d\t%s %d\tSphinx-like\n", 
						type_string (planet->type),
						planet->surf_pressure,
						planet->mass * SUN_MASS_IN_EARTH_MASSES,
						planet->surf_grav,
						planet->surf_temp  - EARTH_AVERAGE_KELVIN,
						habitable,
						flag_seed, 
						flag_char,
						sys_no,
						system_name,
						planet_no);
			}
		}
	}
}

/*
 *  Sort a ChemTable by decreasing abundance.
 */

static int diminishing_abundance(const void *ap, const void *bp)
{
	const ChemTable *a = (ChemTable *) ap;
	const ChemTable *b = (ChemTable *) bp;
	long double    aa = a->abunds * a->abunde;
	long double    bb = b->abunds * b->abunde;

	if (aa < bb)
		return +1;
	return (aa > bb ? -1 : 0);
}

/*
 *  Sort a ChemTable by decreasing pressure.
 */

static int diminishing_pressure(const void *ap, const void *bp)
{
	const gas *a = (gas *) ap;
	const gas *b = (gas *) bp;

	if (a->surf_pressure < b->surf_pressure)
		return +1;
	return (a->surf_pressure > b->surf_pressure ? -1 : 0);
}

int stargen (actions		action,
			 char			flag_char,
			 char *			path,
			 char *			url_path_arg,
			 char *			filename_arg,
			 char *			sys_name_arg,
			 
			 FILE *			sgOut,
			 FILE *			sgErr,
			 char *			prognam,
			 long double	mass_arg,
			 long			seed_arg,
			 int			count_arg,
			 int			incr_arg,
			 catalog *		cat_arg,
			 int			sys_no_arg,
			 
			 long double	ratio_arg,
			 
			 int			flags_arg,
			 int			out_format
			 )
{
	primary			sun					= {0.0, 0.0, 0.0, 0.0, 0.0, ""};
	long double		min_mass 			= 0.4;
	long double		inc_mass 			= 0.05;
	long double		max_mass 			= 2.35;
	int				system_count		= 1;
	int				seed_increment		= 1;
	
	char			default_path[]		= SUBDIR;
	char			thumbnail_file[300]	= "Thumbnails.html";
	char 			file_name[300]		= "StarGen.html";
	char			subdir[300]			= "";

	FILE 			*html_file			= NULL;
	FILE 			*thumbnails			= NULL; 

	int  			index				= 0;
	int				do_catalog			= ((cat_arg != NULL) && (sys_no_arg == 0));
	int				catalog_count		= 0;
	int				do_gases			= (flags_arg & fDoGases) != 0;
	int 			use_solar_system	= (flags_arg & fUseSolarsystem) != 0;
	int				reuse_solar_system	= (flags_arg & fReuseSolarsystem) != 0;
	int				use_known_planets	= (flags_arg & fUseKnownPlanets) != 0;
	int				no_generate			= (flags_arg & fNoGenerate) != 0;
	int				do_moons			= (flags_arg & fDoMoons) != 0;
	int				only_habitable		= (flags_arg & fOnlyHabitable) != 0;
	int				only_multi_habitable= (flags_arg & fOnlyMultiHabitable) != 0;
	int				only_jovian_habitable=(flags_arg & fOnlyJovianHabitable) != 0;

	if (do_catalog)
		catalog_count = cat_arg->count;

	if (only_habitable && only_multi_habitable)
		only_habitable = FALSE;

	if (sgErr == NULL)
		sgErr = stderr;
	
	if ((prognam == NULL) || (prognam[0] == '\0'))
		prognam = "StarGen";

	if ((path == NULL) || (path[0] == '\0'))
		path 		= default_path;
	
	if ((url_path_arg != NULL) && (url_path_arg[0] != '\0'))
		url_path	= url_path_arg;
	//else defaulted in display.c

	{									// Find the last sub-dir in the path:
		int		l = strlen(DIRSEP);
		char*	s = path;
		char*	e = s + strlen(s) - l;
		
		if (e < s || (strcmp(e, DIRSEP) != 0))
		{
			fprintf (stderr, "Invalid path: '%s'\n", path);
			return 1;
		}
	
		for (;;)
		{
			char*	p = strstr(s, DIRSEP);
			
			if (p >= e)
				break;
			
			s = p + l;
		}
				
		strncpy (subdir, s, strlen(s) - l);
		strncat (subdir, "/", 80-strlen(subdir));
	}
	
	for (index = 0; index < max_gas; index++)
		if (gases[index].max_ipp == 0.0)
			gases[index].max_ipp = INCREDIBLY_LARGE_NUMBER;
			
	qsort(gases, (sizeof(gases) / sizeof(ChemTable)) - 1, 
				  sizeof(*gases), 
				  diminishing_abundance);

	switch (action)
	{
		case aListGases:
		{
			long double	total = 0.0;
			
			if (sgOut == NULL)
				sgOut = stdout;
			
			for (index = 0; index < max_gas; index++)
			{
				if (gases[index].weight >= AN_N
				 && gases[index].max_ipp < 1E9)
					total += gases[index].max_ipp;
				
				fprintf (sgOut, " %2d: %4s - %-13s %3.0f mb - %5.0Lf mb\n",
						index,
						gases[index].symbol,
						gases[index].name,
						gases[index].num == AN_O ? MIN_O2_IPP : 0.0,
						gases[index].max_ipp);
			}
			fprintf (sgOut, "Total Max ipp: %5.0Lf\n", total);
			fprintf (sgOut, "Max pressure: %5.0f atm\n", MAX_HABITABLE_PRESSURE);
			
			return (1);
		}
		case aListCatalog:
			if (sgOut == NULL)
				sgOut = stdout;
			
			for (index = 0; index < catalog_count; index++)
			{
				fprintf (sgOut, "%3d: %-30.30s M: %4.2LG L: %4.2LG\n",
						index,
						(*(cat_arg->stars))[index].name,
						(*(cat_arg->stars))[index].mass,
						(*(cat_arg->stars))[index].luminosity);
			}

			return (1);
		
		case aListCatalogAsHTML:
			if (sgOut == NULL)
				sgOut = stdout;
			
			for (index = 0; index < catalog_count; index++)
			{
				fprintf (sgOut, "\t<option value=%d>%s</option>\n",
						index,
						(*(cat_arg->stars))[index].name);
			}

			return (1);
		
		case aSizeCheck:
		{
			long double	temp = est_temp(1.0, 1.0,  EARTH_ALBEDO);
			
			if (sgOut == NULL)
				sgOut = stdout;
			
			fprintf (sgOut, "Size of float: %ld\n",
					 sizeof(float));
			fprintf (sgOut, "Size of doubles: %ld\n",
					 sizeof(double));
			fprintf (sgOut, "Size of long doubles: %ld\n\n",
					 sizeof(long double));
			fprintf (sgOut, "Earth Eff Temp: %5.1Lf K, %5.1Lf C, Earth rel: %5.1Lf C\n\n",
					 temp,
					 temp - FREEZING_POINT_OF_WATER,
					 temp - EARTH_AVERAGE_KELVIN);

			return (1);
		}
		
		case aListVerbosity:
			if (sgOut == NULL)
				sgOut = stdout;
			
			fprintf (sgOut, 
					"Verbosity flags are hexidecimal numbers:\n"
					"\t0001\tEarthlike count\n"
					"\t0002\tTrace Min/Max\n"
					"\t0004\tList Earthlike\n"
					"\t\n"
					"\t0010\tList Gases\n"
					"\t0020\tTrace temp iterations\n"
					"\t0040\tGas lifetimes\n"
					"\t0080\tList loss of accreted gas mass\n"
					"\t\n"
					"\t0100\tInjecting, collision\n"
					"\t0200\tChecking..., Failed...\n"
					"\t0800\tList accreted atmospheres\n"
					"\t\n"
					"\t1000\tMoons (experimental)\n"
					"\t2000\tOxygen poisoned (experimental)\n"
					"\t4000\tTrace gas percentages\n"
					"\t8000\tList Jovians in the ecosphere\n"
					);
			return (1);
		case aGenerate:
		
			break;
	}

	flag_seed		= seed_arg;
	sun.mass 		= mass_arg;
	system_count	= count_arg;
	seed_increment	= incr_arg;
	
	if (ratio_arg > 0.0)
		dust_density_coeff *= ratio_arg;
	
	if (reuse_solar_system)
	{
		system_count = 1 + (int) ((max_mass - min_mass) / inc_mass);
		
		earth.mass = (EM(min_mass));
		
		sun.luminosity 	= 1.0;
		sun.mass 		= 1.0;
		sun.life 		= 1.0E10;
		sun.age 		= 5.0E9;
		sun.r_ecosphere	= 1.0;
		
		use_solar_system = TRUE;
	}
	else if (do_catalog)
	{
		system_count = catalog_count + ((system_count - 1) * (catalog_count - 1));
		use_solar_system = TRUE;
	}
	
	if ((system_count > 1) ||
	    ((strlen(filename_arg) > 0) && (sgOut != NULL)))
	{
		if (strlen(filename_arg) > 0)
			strcpy(thumbnail_file, filename_arg);

		thumbnails = open_html_file ("Thumbnails", flag_seed, path, thumbnail_file, 
									 prognam, sgOut);
		if (thumbnails == NULL)
		{
			fprintf(sgErr, "Could not open file %s%s\n",
					path, thumbnail_file);
			exit(0);
		}
	}
	
	for (index = 0; index < system_count; index++)
	{	
		char			system_name[80];
		char			designation[80];
		char			*cp;
		long double		outer_limit			= 0.0;
		int 			sys_no 				= 0;
		int				has_known_planets 	= FALSE;
		planet_pointer	seed_planets 		= NULL;
		int				use_seed_system		= FALSE;
		int				in_celestia 		= 0;
		
		init();

		if (do_catalog || sys_no_arg)
		{
			if (sys_no_arg)
				sys_no = sys_no_arg - 1;
			else 
			{
				if (index >= catalog_count)
					sys_no = ((index - 1) % (catalog_count - 1)) + 1 ;
				else
					sys_no = index;
			}

			if ((*(cat_arg->stars))[sys_no].known_planets != NULL)
				has_known_planets = TRUE;

			if (use_known_planets || no_generate)  
			{
				seed_planets = (*(cat_arg->stars))[sys_no].known_planets;
				
				use_seed_system	= no_generate;
			}
			else
			{
				seed_planets = NULL;
			}
			
			in_celestia = (*(cat_arg->stars))[sys_no].in_celestia;
			
			sun.mass = (*(cat_arg->stars))[sys_no].mass;
			sun.luminosity = (*(cat_arg->stars))[sys_no].luminosity;

			if (do_catalog || sys_name_arg[0] == '\0')
			{
				sprintf (&system_name[0], "%s", (*(cat_arg->stars))[sys_no].name);
				sprintf (&designation[0], "%s", (*(cat_arg->stars))[sys_no].desig);
				
			}
			else
			{
				sprintf (&system_name[0], "%s", sys_name_arg);
				sprintf (&designation[0], "%s", sys_name_arg);
			}
			
			sprintf (&file_name[0], "%s-%ld.html", designation, flag_seed);
			
			if ((*(cat_arg->stars))[sys_no].m2 > .001)
			{
				/*
				 *	The following is Holman & Wiegert's equation 1 from
				 *	Long-Term Stability of Planets in Binary Systems
				 *	The Astronomical Journal, 117:621-628, Jan 1999
				 */
				long double m1 = sun.mass;
				long double m2 = (*(cat_arg->stars))[sys_no].m2;
				long double mu = m2 / (m1 + m2);
				long double e = (*(cat_arg->stars))[sys_no].e;
				long double a = (*(cat_arg->stars))[sys_no].a;
				
				outer_limit = (0.464 + (-0.380 * mu) + (-0.631 * e) +
							   (0.586 * mu * e) + (0.150 * pow2(e)) +
							   (-0.198 * mu * pow2(e))) * a;
			}
			else
				outer_limit = 0.0;
		}
		else if (reuse_solar_system)
		{
			sprintf (&system_name[0], "Earth-M%LG", earth.mass * SUN_MASS_IN_EARTH_MASSES);
			sprintf (&designation[0], "Earth-M%LG", earth.mass * SUN_MASS_IN_EARTH_MASSES);
			sprintf (&file_name[0], "Earth-M%LG.html", earth.mass * SUN_MASS_IN_EARTH_MASSES);

			outer_limit = 0.0;
		}
		else
		{
			if (sys_name_arg[0])
			{
				sprintf (&system_name[0], "%s", sys_name_arg);
				sprintf (&designation[0], "%s", sys_name_arg);
			}
			else
			{
				sprintf (&system_name[0], "%s %ld-%LG", prognam, flag_seed, sun.mass);
				sprintf (&designation[0], "%s", prognam);
			}
			
			sprintf (&file_name[0], "%s-%ld-%LG.html", designation, flag_seed, sun.mass);
			outer_limit = 0;
		}
		
		sun.name = system_name;
		
		if ((flag_verbose & 0x0400) && (outer_limit > 0.0))
		{
			fprintf (sgErr, "%s, Outer Limit: %LG\n", system_name, outer_limit);
		}

		if ((system_count == 1) && (strlen(filename_arg) > 0))
			strcpy(file_name, filename_arg);

		while ((cp = strchr(file_name,' ')) != 0)
			*cp = '-';
		
		while ((cp = strchr(file_name,'\'')) != 0)
			*cp = '-';
		
		habitable			 = 0;
		habitable_jovians	 = 0;
		
		if (reuse_solar_system)
		{
			seed_planets	= solar_system;
			use_seed_system	= TRUE;
		}
		else if (use_solar_system)
		{
			if  (index == 0)
			{
				seed_planets	= solar_system;
				use_seed_system	= TRUE;
			}
			else
			{
				use_seed_system	= FALSE;

				if (!use_known_planets)
					seed_planets = NULL;
			}
		}
		
{
	int	i;
	
	for (i = 0; i < 12; i++)
		type_counts[i] = 0;
	
	type_count = 0;
}
		
		generate_stellar_system(&sun,
								use_seed_system, 
								seed_planets,	// solar_system
								flag_char,
								sys_no,
								system_name,
								outer_limit,
								do_gases,
								do_moons);

{
	planet_pointer	planet;
	int 			counter; 
	int				wt_type_count = type_count;
	int				norm_type_count = 0;

	if (type_counts[3] > 0)		wt_type_count += 20;		// Terrestrial
	if (type_counts[8] > 0)		wt_type_count += 18;		// Water
	if (type_counts[2] > 0)		wt_type_count += 16;		// Venusian
	if (type_counts[7] > 0)		wt_type_count += 15;		// Martian
	if (type_counts[9] > 0)		wt_type_count += 14;		// Ice
	if (type_counts[10] > 0)	wt_type_count += 13;		// Asteroids
	if (type_counts[4] > 0)		wt_type_count += 12;		// Gas Dwarf
	if (type_counts[5] > 0)		wt_type_count += 11;		// Sub_Jovian
	if (type_counts[11] > 0)	wt_type_count += 10;		// 1-Face
	if (type_counts[1] > 0)		wt_type_count += 3;		// Rock
	if (type_counts[6] > 0)		wt_type_count += 2;		// Jovian
	if (type_counts[0] > 0)		wt_type_count += 1;		// Unknown

	for (planet=innermost_planet, counter=0;
		planet != NULL;
		planet=planet->next_planet, counter++)
		;
	
	norm_type_count = wt_type_count - (counter - type_count);
	
	if (max_type_count < norm_type_count)
	{
		max_type_count = norm_type_count;

		if (flag_verbose & 0x010000)
			fprintf (sgErr, "System %ld - %s (-s%ld -%c%d) has %d types out of %d planets. [%d]\n",
					flag_seed,
					system_name,
					flag_seed, 
					flag_char,
					sys_no,
					type_count,
					counter,
					norm_type_count);
	}
}

		total_habitable += habitable;
		
		if ((!(only_habitable || only_multi_habitable || only_jovian_habitable))
		 || (only_habitable && (habitable > 0))
		 || (only_multi_habitable && (habitable > 1))
		 || (only_jovian_habitable && (habitable_jovians > 0)) 
		 )
		{
			switch (out_format)
			{
				case ffHTML:
					if (thumbnails != NULL)
						html_thumbnails(innermost_planet, thumbnails, system_name, subdir, file_name, FALSE, TRUE);

					html_file = open_html_file (system_name, flag_seed, path, file_name, 
												prognam, NULL);
					
					if (NULL != html_file)
					{
						html_thumbnails(innermost_planet, html_file, system_name, "", "", TRUE, FALSE);
						html_describe_system(innermost_planet, do_gases, html_file);
						close_html_file(html_file);
					}
					else
					{
						fprintf(sgErr, "Could not open file %s%s\n",
								path, file_name);
						exit(0);
					}
				break;
				
				case ffTEXT:
					text_describe_system(innermost_planet, do_gases, flag_seed);
				break;
				
				case ffCELESTIA:
					if (in_celestia != 0)
					{
						if (has_known_planets && !use_known_planets)
							fprintf (sgErr, "Skipping %s -- Has planets in Celestia already\n", 
									designation);
						else
							celestia_describe_system(innermost_planet, designation);
					}
				break;			
			}
			if ((habitable > 1) &&
				(flag_verbose & 0x0001))
				fprintf (sgErr, "System %ld - %s (-s%ld -%c%d) has %d planets with breathable atmospheres.\n",
						flag_seed,
						system_name,
						flag_seed, 
						flag_char,
						sys_no,
						habitable);
		}

		if (! ((use_solar_system) && (index == 0)))
			flag_seed += seed_increment;
			
		if (reuse_solar_system)
			earth.mass += (EM(inc_mass));
		
		free_atmosphere (innermost_planet);
		
		// Free the dust and planets created by accrete:
		free_generations ();
		
#if MEMORY_CHECK
		dumasVerifyHoard();
		dumasDumpHoard ();
#endif
	}
	
	if (flag_verbose & 0x0001)
	{
		fprintf (sgErr, "Earthlike planets: %d\n", earthlike);
		fprintf (sgErr, "Breathable atmospheres: %d\n", total_habitable);
		fprintf (sgErr, "Breathable g range: %4.2Lf -  %4.2Lf\n", 
				 min_breathable_g, 
				 max_breathable_g);
		fprintf (sgErr, "Terrestrial g range: %4.2Lf -  %4.2Lf\n", 
				 min_breathable_terrestrial_g,
				 max_breathable_terrestrial_g);
		fprintf (sgErr, "Breathable pressure range: %4.2Lf -  %4.2Lf\n", 
				 min_breathable_p, 
				 max_breathable_p);
		fprintf (sgErr, "Breathable temp range: %+.1Lf C -  %+.1Lf C\n", 
				 min_breathable_temp - EARTH_AVERAGE_KELVIN, 
				 max_breathable_temp - EARTH_AVERAGE_KELVIN);
	}
		
	if (system_count > 1)
	{
		if (do_gases)
			html_thumbnail_totals(thumbnails);

		close_html_file(thumbnails);
	}

	return(0);
}
