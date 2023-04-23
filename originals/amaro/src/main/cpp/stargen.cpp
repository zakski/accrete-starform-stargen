/*
 *	StarGen API
 *
 *	This file provides the main program interface to StarGen.
 *	An example of calling it is the command-line interface defined in
 *	main.c.
 *
 *	$Id: stargen.c,v 1.47 2009/03/17 19:03:00 brons Exp $
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
#include 	"ring_universe.h"

char *	stargen_revision = "$Revision: 1.47+seb $";

/*  These are the global variables used during accretion:  */
planet_pointer	innermost_planet;
long double		dust_density_coeff = DUST_DENSITY_COEFF;


int flag_verbose = 0;
// 0x0001			Earthlike count
// 0x0002			Trace Min/max
// 0x0004			List habitable
// 0x0008			List Earth-like (and Sphinx-like)

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

// 0x10000			List type diversity
// 0x20000			Trace Surface temp interations
// 0x40000			Lunar orbits

long flag_seed		 = 0;

int earthlike		 = 0;
int total_earthlike	 = 0;
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
long double	min_breathable_terrestrial_l = 1000.0;
long double	min_breathable_l			 = 1000.0;
long double	max_breathable_terrestrial_l = 0.0;
long double	max_breathable_l			 = 0.0;
long double max_moon_mass				 = 0.0;


int type_counts[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; //seb
int	type_count = 0;
int max_type_count = 0;

/*	          No Orbit   Eccen. Tilt Mass    Gas Giant? Dust Mass   Gas */
planets luna     ={1,2.571e-3,0.055,1.53, EM(.01229), FALSE, EM(.01229), 0, ZEROES,0,NULL, NULL};
planets callisto ={4,1.259e-2,0    ,0   , EM(1.62e-2),FALSE,EM(1.62e-2 ), 0, ZEROES,0,NULL, NULL};
planets ganymede ={3,7.16e-3,0.0796,0   , EM(2.6e-2 ),FALSE,EM(2.6e-2 ), 0, ZEROES,0,NULL, &callisto};
planets europa   ={2,4.49e-3,0.0075,0   , EM(7.9e-3 ),FALSE,EM(7.9e-3 ), 0, ZEROES,0,NULL, &ganymede};
planets io       ={1,2.82e-3,0.0006,0   , EM(1.21e-2),FALSE,EM(1.21e-2), 0, ZEROES,0,NULL, &europa};
planets iapetus  ={6,2.38e-2,0.029, 0   , EM(8.4e-4 ),FALSE,EM(8.4e-4 ), 0, ZEROES,0,NULL, NULL};
planets hyperion ={5,9.89e-3,0.110, 0   , EM(1.82e-5),FALSE,EM(1.82e-5), 0, ZEROES,0,NULL, &iapetus};
planets titan    ={4,8.17e-3,0.0289,0   , EM(2.3e-2 ),FALSE,EM(2.3e-2 ), 0, ZEROES,0,NULL, &hyperion};
planets rhea     ={3,3.52e-3,0.0009,0   , EM(3.85e-4),FALSE,EM(3.85e-4), 0, ZEROES,0,NULL, &titan};
planets dione    ={2,2.52e-3,0.0021,0   , EM(1.74e-4),FALSE,EM(1.74e-4), 0, ZEROES,0,NULL, &rhea};
planets tethys   ={1,1.97e-3,0.000, 0   , EM(1.09e-4),FALSE,EM(1.09e-4), 0, ZEROES,0,NULL, &dione};
planets triton   ={1,2.36e-3,0.000, 0   , EM(2.31e-2),FALSE,EM(2.31e-2), 0, ZEROES,0,NULL, NULL};
planets charon   ={1,1.31e-4,0.000, 0   , EM(2.54e-4),FALSE,EM(2.54e-4), 0, ZEROES,0,NULL, NULL};

planets eris   ={11,67.6681,0.44177,0   , EM(.0025),FALSE, EM(.0025),    0, ZEROES,0,NULL,    NULL};
planets pluto  ={10,39.529,0.248,122.5, EM(0.002),  FALSE, EM(0.002),    0, ZEROES,0,&charon, &eris};
planets neptune={ 9,30.061,0.010, 29.6, EM(17.14),  TRUE,  0,   EM(17.14),  ZEROES,0,&triton, &pluto};
planets uranus ={ 8,19.191,0.046, 97.9, EM(14.530), TRUE,  0,   EM(14.530), ZEROES,0,NULL,    &neptune};
planets saturn ={ 7,9.539, 0.056, 26.7, EM(95.18),  TRUE,  0,   EM(95.18),  ZEROES,0,&tethys, &uranus};
planets jupiter={ 6,5.203, 0.048,  3.1, EM(317.9),  TRUE,  0,   EM(317.9),  ZEROES,0,&io,     &saturn};
planets ceres  ={ 5,2.766, 0.080,  0,   EM(0.00015),FALSE, EM(0.00015),  0, ZEROES,0,NULL,    &jupiter};
planets mars   ={ 4,1.524, 0.093, 25.2, EM(0.1074), FALSE, EM(0.1074),   0, ZEROES,0,NULL,    &ceres};
planets earth  ={ 3,1.000, 0.017, 23.5, EM(1.00),   FALSE, EM(1.00),     0, ZEROES,0,&luna,   &mars};
planets venus  ={ 2,0.723, 0.007,177.3, EM(0.815),  FALSE, EM(0.815),    0, ZEROES,0,NULL,    &earth};
planets mercury={ 1,0.387, 0.206,  2,   EM(0.055),  FALSE, EM(0.055),    0, ZEROES,0,NULL,    &venus};
planet_pointer solar_system = &mercury;

/* planets ceres  ={ 5,2.767, 0.079,  0, EM(0.000134), FALSE, EM(0.000134), 0, ZEROES,0,NULL , &jupiter}; */

/* planets	titan2 ={ 7,9.539, 0.056, 26.7 , EM(0.02259), FALSE, EM(0.02259),EM(.001), ZEROES,0,NULL, &uranus}; */

/* Seeds for accreting the solar system */
			/*	 No Orbit  Eccen... */
planets pluto1  ={10,39.529,0.248, 0, 0, 0, 0, 0, ZEROES,0,NULL, NULL};
planets pluto2  ={10,39.529,0.15,  0, 0, 0, 0, 0, ZEROES,0,NULL, NULL};	// The real eccentricity 
planets mars1   ={ 4,1.524, 0.093, 0, 0, 0, 0, 0, ZEROES,0,NULL, &pluto2};	// collides Pluto+Neptune
planets ceres1  ={ 5,2.767, 0.079, 0, 0, 0, 0, 0, ZEROES,0,NULL, &mars1};
planets saturn1 ={ 7,9.539, 0.056, 0, 0, 0, 0, 0, ZEROES,0,NULL, &ceres1};
planets uranus1 ={ 8,19.191,0.046, 0, 0, 0, 0, 0, ZEROES,0,NULL, &saturn1};
planets neptune1={ 9,30.061,0.010, 0, 0, 0, 0, 0, ZEROES,0,NULL, &uranus1};
planets jupiter1={ 6,5.203, 0.048, 0, 0, 0, 0, 0, ZEROES,0,NULL, &neptune1};
planets mercury1={ 1,0.387, 0.206, 0, 0, 0, 0, 0, ZEROES,0,NULL, &jupiter1};
planets earth1  ={ 3,1.000, 0.017, 0, 0, 0, 0, 0, ZEROES,0,NULL, &mercury1};
planets venus1  ={ 2,0.723, 0.007, 0, 0, 0, 0, 0, ZEROES,0,NULL, &earth1};
planet_pointer solar_system1 = &venus1;

planets eriEpsI	={ 1,3.3,	0.608, 	0, 0, 0, 0, 0, ZEROES,0,NULL, NULL};
planets UMa47III={ 2,11.6,	0.16,  	0, EM(1.64 * 317.9), TRUE, EM(1.64 * 317.9)/4, EM(1.64 * 317.9) - (EM(1.64 * 317.9)/4), ZEROES,0,NULL, NULL};
planets UMa47II	={ 2,3.73,	0.098, 	0, EM(0.540 * 317.9), TRUE, EM(0.540 * 317.9)/4, EM(0.540 * 317.9) - (EM(0.540 * 317.9)/4), ZEROES,0,NULL, &UMa47III};
planets UMa47I	={ 1,2.11, 	0.032,	0, EM(2.53 * 317.9), TRUE, EM(2.53 * 317.9)/4, EM(2.53 * 317.9) - (EM(2.53 * 317.9)/4), ZEROES,0,NULL, &UMa47II};
planets horIotI	={ 1,0.925,	0.161,	0, 0, 0, 0, 0, ZEROES,0,NULL, NULL};

planets Bellerophon = {1, 0.0527, 0.013, 0, EM(150), TRUE, EM(150)/4, EM(150) - (EM(150)/4),ZEROES,0,NULL, NULL};

			/*	No Orbit Eccen. Tilt   Mass    Gas Giant? Dust Mass   Gas */
planets	smallest={0, 0.0, 0.0,	20.0,	EM(0.4),   FALSE,  EM(0.4),   0.0, ZEROES,0,NULL, NULL};
planets	average	={0, 0.0, 0.0,	20.0,	EM(1.0),   FALSE,  EM(1.0),    0.0, ZEROES,0,NULL, NULL};
planets	largest	={0, 0.0, 0.0,	20.0,	EM(1.6),   FALSE,  EM(1.6),   0.0, ZEROES,0,NULL, NULL};

// L			Mass			Mass2			Eccen.	SMAxis	 	Planets		Designation	InCel Name
star perdole[] = 
{{0,			1.00,			0,			0,	0,		0,0,&mercury,		"Sol",		1, "The Solar System"},
 {0,			1.08,			0.88,			0.52,	23.2,		0,0,NULL,		"ALF Cen A",	1, "Alpha Centauri A"},
 {0,			0.88,			1.08,			0.52,	23.2,		0,0,NULL,		"ALF Cen B",	1, "Alpha Centauri B"},
 {0,			0.80,			0,			0,	0,		0,0,&eriEpsI,		"EPS Eri",	1, "Epsilon Eridani"},
 {0,			0.82,			0,			0,	0,		0,0,NULL,		"TAU Cet",	1, "Tau Ceti"},
 {0,			0.90,			0.65,			0.50,	AVE(22.8,24.3),	0,0,NULL,		"70 Oph",	1, "70 Ophiuchi A"},
 {0,			0.94,			0.58,			0.53,	AVE(69.0,71.0),	0,0,NULL,		"ETA Cas",	1, "Eta Cassiopeiae A"},
 {0,			0.82,			0,			0,	0,		0,0,NULL,		"SIG Dra",	1, "Sigma Draconis"},
 {0,			0.77,			0.76,			0,	22.,		0,0,NULL,		"36 Oph",	1, "36 Ophiuchi A"},
 {0,			0.76,			0.77,			0,	22.,		0,0,NULL,		"36 Oph B",	0, "36 Ophiuchi B"},
 {0,			0.76,			.5,			5,	46.,		0,0,NULL,		"HD 191408",	1, "HR7703 A"},
 {0,			0.98,			0,			0,	0,		0,0,NULL,		"DEL Pav",	1, "Delta Pavonis"},
 {0,			0.91,			0,			0,	0,		0,0,NULL,		"82 Eri",	1, "82 Eridani"},
 {0,			1.23,			0,			0,	0,		0,0,NULL,		"BET Hyi",	1, "Beta Hydri"},
 {0,			0.74,			0,			0,	0,		0,0,NULL,		"HD 219134",	1, "HR8832"},
 {0,			0.725,			0,			0,	1100.,		0,0,NULL,		"HD 16160",	1, "HR753 A"}
};

/*
 *	The following values were taken from: http://www.solstation.com/stars.htm
 */
planets GamLepA80662XII = {12, 115.445, 0.046, 0, EM(0.000468681999), FALSE, EM(0.000468681999), 0,ZEROES,0,NULL, NULL};
planets GamLepA80662XI = {11, 99.581, 0.045, 0, EM(0.005), FALSE, EM(0.005), 0,ZEROES,0,NULL, &GamLepA80662XII};
planets GamLepA80662X = {10, 61.534, 0.123, 0, EM(0.035), FALSE, EM(0.035), 0,ZEROES,0,NULL, &GamLepA80662XI};
planets GamLepA80662IX = {9, 39.195, 0.097, 0, EM(5.474), TRUE, EM(1.115), EM(4.359),ZEROES,0,NULL, &GamLepA80662X};
planets GamLepA80662VIII = {8, 22.374, 0.007, 0, EM(39.447), TRUE, EM(4.003), EM(35.444),ZEROES,0,NULL, &GamLepA80662IX};
planets GamLepA80662VII = {7, 10.385, 0.256, 0, EM(1118.420), TRUE, EM(47.800), EM(1070.620),ZEROES,0,NULL, &GamLepA80662VIII};
planets GamLepA80662VI = {6, 5.466, 0.000, 0, EM(1.273), FALSE, EM(1.273), 0,ZEROES,0,NULL, &GamLepA80662VII};
planets GamLepA80662V = {5, 2.541, 0.043, 0, EM(233.147), TRUE, EM(22.577), EM(210.569),ZEROES,0,NULL, &GamLepA80662VI};
planets GamLepA80662IV = {4, 1.553, 0.195, 0, EM(2.177), FALSE, EM(2.177), 0,ZEROES,0,NULL, &GamLepA80662V};
planets GamLepA80662III = {3, 0.799, 0.177, 0, EM(1.036), FALSE, EM(1.036), 0,ZEROES,0,NULL, &GamLepA80662IV};
planets GamLepA80662II = {2, 0.583, 0.068, 0, EM(0.083), FALSE, EM(0.083), 0,ZEROES,0,NULL, &GamLepA80662III};
planets GamLepA80662I = {1, 0.443, 0.231, 0, EM(0.146), FALSE, EM(0.146), 0,ZEROES,0,NULL, &GamLepA80662II};

planets Eri40A128424XV = {15, 119.973, 0.020, 0, EM(2.00863714E-5), FALSE, EM(2.00863714E-5), 0, ZEROES,0,NULL, NULL};
planets Eri40A128424XIV = {14, 113.514, 0.092, 0, EM(0.000786716213), FALSE, EM(0.000786716213), 0, ZEROES,0,NULL, &Eri40A128424XV};
planets Eri40A128424XIII = {13, 67.170, 0.062, 0, EM(0.055), FALSE, EM(0.055), 0, ZEROES,0,NULL, &Eri40A128424XIV};
planets Eri40A128424XII = {12, 54.254, 0.048, 0, EM(0.00786716213), FALSE, EM(0.00786716213), 0, ZEROES,0,NULL, &Eri40A128424XIII};
planets Eri40A128424XI = {11, 29.462, 0.109, 0, EM(6.689), TRUE, EM(1.917), EM(4.772), ZEROES,0,NULL, &Eri40A128424XII};
planets Eri40A128424X = {10, 15.025, 0.080, 0, EM(0.730), FALSE, EM(0.730), 0, ZEROES,0,NULL, &Eri40A128424XI};
planets Eri40A128424IX = {9, 11.715, 0.050, 0, EM(231.555), TRUE, EM(19.154), EM(212.401), ZEROES,0,NULL, &Eri40A128424X};
planets Eri40A128424VIII = {8, 3.846, 0.217, 0, EM(130.079), TRUE, EM(21.913), EM(108.166), ZEROES,0,NULL, &Eri40A128424IX};
planets Eri40A128424VII = {7, 2.568, 0.017, 0, EM(12.174), TRUE, EM(6.265), EM(5.909), ZEROES,0,NULL, &Eri40A128424VIII};
planets Eri40A128424VI = {6, 1.636, 0.078, 0, EM(1.149), FALSE, EM(1.149), 0, ZEROES,0,NULL, &Eri40A128424VII};
planets Eri40A128424V = {5, 1.227, 0.079, 0, EM(0.508), FALSE, EM(0.508), 0, ZEROES,0,NULL, &Eri40A128424VI};
planets Eri40A128424IV = {4, 0.746, 0.017, 0, EM(0.184), FALSE, EM(0.184), 0, ZEROES,0,NULL, &Eri40A128424V};
planets Eri40A128424III = {3, 0.580+0.00025, 0.006, 0, EM(0.346+0.0004), FALSE, EM(0.346+0.0004), 0, ZEROES,0,NULL, &Eri40A128424IV};
planets Eri40A128424II = {2, 0.482, 0.118, 0, EM(0.043), FALSE, EM(0.043), 0, ZEROES,0,NULL, &Eri40A128424III};
planets Eri40A128424I = {1, 0.305, 0.010, 0, EM(0.075), FALSE, EM(0.75), 0, ZEROES,0,NULL, &Eri40A128424II};

planets can55d = {5, 5.77, 0.025, 0, EM(1557), TRUE, EM(1557/5), EM(1557) - EM(1557/5), ZEROES, 0, NULL, NULL};
planets can55f = {4, 0.71, 0.4, 0, EM(57), TRUE, EM(57/5), EM(57) - EM(57/5), ZEROES,0, NULL, &can55d};
planets can55c = {3, 0.24, 0.086, 0, EM(66.7), TRUE, EM(66.7/5), EM(66.7) - EM(66.7/5), ZEROES,0, NULL, &can55f};
planets can55b = {2, 0.115, 0.014, 0, EM(323), TRUE, EM(323/5), EM(323) - EM(323/5), ZEROES,0, NULL, &can55c};
planets can55e = {1, 0.016, 0.057, 0, EM(8.6), FALSE, EM(8.6), 0, ZEROES, 0, NULL, &can55b};

planets UPSAndAe = {4, 5.2456, 0.00536, 0, EM(1.059*317.8), TRUE, EM(1.059*317.8)/5, EM(1.059*317.8)-(EM(1.059*317.8)/5), ZEROES, 0, NULL, NULL};
planets UPSAndAd = {3, 2.53, 0.267, 0, EM(10.25*317.8), TRUE, EM(10.25*317.8)/5, EM(10.25*317.8)-(EM(10.25*317.8)/5), ZEROES, 0, NULL, &UPSAndAe};
planets UPSAndAc = {2, 0.832, 0.224, 0, EM(13.98*317.8), TRUE, EM(13.98*317.8)/5, EM(13.98*317.8)-(EM(13.98*317.8)/5), ZEROES, 0, NULL, &UPSAndAd};
planets UPSAndAb = {1, 0.0595, 0.013, 0, EM(1.4*317.8), TRUE, EM(1.4*317.8)/5, EM(1.4*317.8)-(EM(1.4*317.8)/5), ZEROES, 0, NULL, &UPSAndAc};


planets fictional3 = {3, 0.245, 0.0010014786819031, 0, EM(0.9834234324), FALSE, EM(0.9834234324), 0, ZEROES, 0, NULL, NULL};
planets fictional2 = {2, 0.121402, 0.0020784029810, 0, EM(2.0021308939), FALSE, EM(2.0021308939), 0, ZEROES, 0, NULL, &fictional3};
planets fictional = {1, 0.0503258, 0.0002889782043, 0, EM(11.03289), TRUE, EM(2.206578), EM(8.826312), ZEROES, 0, NULL, &fictional2};

planets hd10180h = {9, 3.49, 0.18, 0, EM(65.8), TRUE, EM(65.8/5.0), EM((65.8/5.0)*4.0), ZEROES, 0, NULL, NULL};
planets hd10180g = {8, 1.415, 0.03, 0, EM(21.4), TRUE, EM(21.4/5.0), EM((21.4/5.0)*4.0), ZEROES, 0, NULL, &hd10180h};
planets hd10180f = {7, 0.4929, 0.13, 0, EM(23.9), TRUE, EM(23.9/5.0), EM((23.9/5.0)*4.0), ZEROES, 0, NULL, &hd10180g};
planets hd10180j = {6, 0.330, 0.07, 0, EM(5.1), TRUE, EM((5.1/5.0)*4.0), EM(5.1/5.0), ZEROES, 0, NULL, &hd10180f};
planets hd10180e = {5, 0.270, 0.001, 0, EM(25.0), TRUE, EM(25.0/5), EM((25.0/5)*4), ZEROES, 0, NULL, &hd10180j};
planets hd10180d = {4, 0.1284, 0.011, 0, EM(11.9), TRUE, EM(11.9/5.0), EM((11.9/5.0)*4.0), ZEROES, 0, NULL, &hd10180e};
planets hd10180i = {3, 0.0904, 0.05, 0, EM(1.9), FALSE, EM(1.9), 0, ZEROES, 0, NULL, &hd10180d};
planets hd10180c = {2, 0.0641, 0.07, 0, EM(13.0), TRUE, EM(13.0/5.0), EM((13.0/5.0)*4.0), ZEROES, 0, NULL, &hd10180i};
planets hd10180b = {1, 0.02222, 0.0005, 0, EM(1.3), FALSE, EM(1.3), 0, ZEROES, 0, NULL, &hd10180c};

planets gliese581f = {6, 0.758, 0, 0, EM(7.0), FALSE, EM(7.0), 0, ZEROES, 0, NULL, NULL};
planets gliese581d = {5, 0.21847, 0, 0, EM(5.94), FALSE, EM(5.94), 0, ZEROES, 0, NULL, &gliese581f};
planets gliese581g = {4, 0.14601, 0, 0, EM(2.24), FALSE, EM(2.24), 0, ZEROES, 0, NULL, &gliese581d};
planets gliese581c = {3, 0.072993, 0, 0, EM(5.3), FALSE, EM(5.3), 0, ZEROES, 0, NULL, &gliese581g};
planets gliese581b = {2, 0.0406163, 0, 0, EM(16), TRUE, EM(16 / 5), EM((16 / 5) * 4), ZEROES, 0, NULL, &gliese581c};
planets gliese581e = {1, 0.0284533, 0, 0, EM(1.86), FALSE, EM(1.86), 0, ZEROES, 0, NULL, &gliese581b};

planets hd10647b = {1, 2.03, 0.16, 0, EM(0.93*JUPITER_MASS), TRUE, EM((0.93 *JUPITER_MASS)/5), EM(((0.93*JUPITER_MASS)/5)*4), ZEROES, 0, NULL, NULL};

planets fictionalk = {11, 50.191203, 0, 0, EM(0.736062), TRUE, EM(0.295), EM(0.736062-0.295), ZEROES, 0, NULL, NULL};
planets fictionalj = {10, 42.075003, 0, 0, EM(0.028276), FALSE, EM(0.028276), 0, ZEROES, 0, NULL, &fictionalk};
planets fictionali = {9, 22.916998, 0.020474, 0, EM(498.622731), TRUE, EM(17.169), EM(498.622731-17.169), ZEROES, 0, NULL, &fictionalj};
planets fictionalh = {8, 12.811632, 0.015692, 0, EM(414.490095), TRUE, EM(16.436), EM(414.490095-16.436), ZEROES, 0, NULL, &fictionali};
planets fictionalg = {7, 5.424729, 0.0302880, 0, EM(7577.874209), TRUE, EM(211.124), EM(7577.874209-211.124), ZEROES, 0, NULL, &fictionalh};
planets fictionalf = {6, 1.373711, 0.206417, 0, EM(1.848580), FALSE, EM(1.848580), 0, ZEROES, 0, NULL, &fictionalg};
planets fictionale = {5, 1.001873, 0.004431, 0, EM(0.083739), FALSE, EM(0.083739), 0, ZEROES, 0, NULL, &fictionalf};
planets fictionald = {4, 0.718046, 0.022336, 0, EM(0.059651), FALSE, EM(0.059651), 0, ZEROES, 0, NULL, &fictionale};
planets fictionalc = {3, 0.585048, 0.031666, 0, EM(0.106608), FALSE, EM(0.106608), 0, ZEROES, 0, NULL, &fictionald};
planets fictionalb = {2, 0.480459, 0.127780, 0, EM(0.825301), FALSE, EM(0.825301), 0, ZEROES, 0, NULL, &fictionalc};
planets fictionala = {1, 0.390205, 0.185172, 0, EM(0.066659), FALSE, EM(0.066659), 0, ZEROES, 0, NULL, &fictionalb};

planets leo83Bb = {2, 5.4, 0.1, 0, EM(0.36*JUPITER_MASS), TRUE, EM((0.36*JUPITER_MASS)/5), EM(((0.36*JUPITER_MASS)/5)*4), ZEROES, 0, NULL, NULL};
planets leo83Ba = {1, 0.12186, 0.13, 0, EM(0.087*JUPITER_MASS), TRUE, EM((0.087*JUPITER_MASS)/5), EM(((0.087*JUPITER_MASS)/5)*4), ZEROES, 0, NULL, &leo83Bb};

planets fictional2d = {4, 1.643167673, 0.013543533143421, 0, EM(1012.35423452), TRUE, EM(1012.35423452/5.0), EM((1012.35423452/5.0)*4), ZEROES, 0, NULL, NULL};
planets fictional2c = {3, 0.2551544543, 0.003254433232422, 0, EM(50.24532211), TRUE, EM(50.24532211/5.0), EM((50.24532211/5.0)*4), ZEROES, 0, NULL, &fictional2d};
planets fictional2b = {2, 0.1270135436, 0.000421432453452, 0, EM(52.21434254), TRUE, EM(52.21434254/5.0), EM((52.21434254/5.0)*4), ZEROES, 0, NULL, &fictional2c};
planets fictional2a = {1, 0.0422134534, 0.000421432453452, 0, EM(55.14645532), TRUE, EM(55.14645532/5.0), EM((55.14645532/5.0)*4), ZEROES, 0, NULL, &fictional2b};

planets xiumaab = {1, 0.8, 0.513, 0, 0.4, TRUE, 0.4/5.0, (0.4/5.0)*4.0, ZEROES, 0, NULL, NULL};
planets xiumabb = {1, 0.06, 0, 0, EM(37.0*JUPITER_MASS), TRUE, EM((37.0*JUPITER_MASS)/5.0), EM(((37.0*JUPITER_MASS)/5.0)*4.0), ZEROES, 0, NULL, NULL};

planets alfcentbb = {1, 0.04, 0, 0, EM(0.934), FALSE, EM(0.934), 0, ZEROES, 0, NULL, NULL};

star web[] = 
// L			Mass			Mass2			Eccen.	SMAxis	 Planets		Designation	InCel Name
{{1.00,			1.00,			0,			0,	0,	 0,0,&mercury,		"Sol",		 1, "The Solar System"},		// 0
 {1.60,			1.09,			0.90,			0.519,	23.7,	 0,0,NULL,		"ALF Cen A",     1, "Alpha Centauri A"},		// 4.4
 {0.45,			0.90,			1.09,			0.519,	23.7,	 0,0,&alfcentbb,	"ALF Cen B",     1, "Alpha Centauri B"},		// 4.4
 {0.34,			0.85,			0,			0,	0,	 0,0,&eriEpsI,		"EPS Eri",	 1, "Epsilon Eridani"},			// 10.5 
//{AVE(6.3,8.9),        0.59,			0.5,			.48,	85.2,	 0,0,NULL,		"61 Cyg A",	 1, "61 Cygni A"},				// 11.4
 {0.085,		0.59,			0.5,			.48,	85.2,	 0,0,NULL,		"61 Cyg A",	 1, "61 Cygni A"},				// 11.4
 {0.59,			0.82,			0,			0,	0,	 0,0,NULL,		"TAU Cet",	 1, "Tau Ceti"},				// 11.9 
 {0.38,			0.75,			(0.16+0.43),    	0,	418.,	 0,0,NULL,		"40 Eri",	 1, "40 Eridani A"},			// 16.5
 {AVE(.44,.47), 	0.924,			0.701,			0.495,	23.3,	 0,0,NULL,		"70 Oph",	 1, "70 Ophiuchi A"},			// 16.6
 {0.39,			0.82,			0,			0,	0,	 0,0,NULL,		"SIG Dra",	 1, "Sigma Draconis"},			// 18.8 
 {0.156,		0.76,			(0.55+0.35),    	0.20,	190.,	 0,0,NULL,		"33 g Lib",	 1, "HR 5568"},					// 19.3
 {AVE(1.0,1.29),        0.91,		       	0.56,		        0.497,	71.0,	 0,0,NULL,		"ETA Cas",	 1, "Eta Cassiopeiae A"},		// 19.4
 {0.23,			0.82,			0.20,			.5,	43.,	 0,0,NULL,		"HD 191408",     1, "HR 7703 (HJ 5173) A"},		// 19.7
 {0.65,			0.97,			0,			0,	0,	 0,0,NULL,		"82 Eri",	 1, "82 Eridani"},				// 19.8
 {1.2,			0.98,			0,			0,	0,	 0,0,NULL,		"DEL Pav",	 1, "Delta Pavonis"},			// 19.9
 {0.21,			0.74,			0,			0,	0,	 0,0,NULL,		"HD 219134",     1, "HR 8832"},					// 21.3
 {0.52,			0.90,			0.76,			0.51,	33.6,	 0,0,NULL,		"XI Boo",	 1, "Xi Bootis A"},				// 21.8
 {0.21,			0.81,			0.082,			.75,	15.,     0,0,NULL,		"HD 16160",	 1, "HR 753 A"},				// 23.5
 {0.24,			0.83,			0,			0,	0,	 0,0,NULL,		"HD 4628",	 1, "BD+04 123 (HR 222)"},		// 24.3
 {3.6,			1.1,			0,			0,	0,	 0,0,NULL,		"BET Hyi",	 1, "Beta Hydri"},				// 24.4 
 {0.37,			0.89,			0,			0,	0,	 0,0,NULL,		"107 Psc",	 1, "107 Piscium"},				// 24.4 
														// 107 Psc p1 = Klotho in Celestia's imagined.ssc
 {3.,			1.3,			0,			0,	0,	 0,0,NULL,		"PI3 Ori",	 1, "Pi3 Orionis A"},			// 26.2
 {0.28,			0.88,			0.86,			0.534,	63.7,	 0,0,NULL,		"RHO1 Eri",	 1, "Rho Eridani A"},			// 26.6 
 {0.25,			0.86,			0.88,			0.534,	63.7,	 0,0,NULL,		"RHO2 Eri",	 1, "Rho Eridani B"},			// 26.6 
 {1.2,			1.07,			0,			0,	0,	 0,0,NULL,		"BET CVn",	 1, "Chara"},					// 27.3 
 {1.11,			1.45,			0.9,			0.412,	21.2,	 0,0,NULL,		"XI UMa A",	 1, "Xi Ursae Majoris Aa"},
 {0.67,			.90,			1.45,			0.412,	21.2,	 0,0,&xiumabb,		"XI UMa B",	 1, "Xi Ursae Majoris Ba"},		// 27.3 
//													  		     Xi Urs Maj aka Alula Australis
//					55203:Alula Australis:XI UMa:53 UMa defined in Celestia starnames, but no data
 {0.80,			0.96,			0,			0,	0,	 0,0,NULL,		"61 Vir",	 1, "61 Virginis"},				// 27.8  
 {1.3,			0.98,			0,			0,	0,	 0,0,NULL,		"ZET Tuc",	 1, "Zeta Tucanae"},			// 28.0
 {1.08,			1.0,			.15,			0.45,	6.4,	 0,0,NULL,		"CHI1 Ori",	 1, "Chi1 Orionis A"},			// 28.3 
 {0,			.15,			1.0,			0.45,	6.4,	 0,0,NULL,		"CHI1 Ori B",	 1, "Chi1 Orionis B"},
 //					41 Arae masses are Wieth-Knudsen's 1957 estimates,
 {0.41,			0.9,			.6,			0.779,	91.5,	 0,0,NULL,		"41 Ari",	 1, "41 Arae A"},				// 28.7 
 {0.21,			0.845,			0,			0,	0,	 0,0,NULL,		"HR 1614",	 0, "BD-05 1123 (HR 1614) A"},	// 28.8 
 {0.33,			0.87,			0,			0,	0,	 0,0,NULL,		"HR 7722",	 0, "CD-27 14659 (HR 7722)"},	// 28.8 
 //{2.6,			1.2,			.63,		       .5,	864.,	 0,0,NULL,	"GAM Lep",	 1, "Gamma Leporis A"},			// 29.3 
// {0.25,			0.63,			1.2,			.5,	864.,	 0,0,NULL,	"GAM Lep B",	 0, "Gamma Leporis B"},
 {abs2luminosity(3.83),mass(abs2luminosity(3.83)),mass(abs2luminosity(6.37)),	0.5,    864.0,	 0,0,NULL,	"GAM Lep",	 1, "Gamma Leporis A"},
 {abs2luminosity(6.37),mass(abs2luminosity(6.37)),mass(abs2luminosity(3.83)),	0.5,	864.0,	 0,0,NULL,	"GAM Lep B",	 0, "Gamma Leporis B"},
 {1.4,			1.05,			0,			0,	0,	 0,0,NULL,		"BET Com",	 1, "Beta Comae Berenices"},	// 29.9   
 {0.85,			1.0,			0,			0,	0,	 0,0,NULL,		"KAP1 Cet",	 1, "Kappa Ceti"},				// 29.9   
 {1.5,			0.8,			0,			0,	0,	 0,0,NULL,		"GAM Pav",	 1, "Gamma Pavonis"},			// 30.1
 {0.82,			0.8,			0.07,			0.6,	235.,	 0,0,NULL,		"HD 102365",     1, "HR 4523"},					// 30.1
 {0.588,		0.81,			0,			0,	0,	 0,0,NULL,		"61 UMa",	 1, "61 Ursae Majoris"},		// 31.1  
 {0.31,			0.87,			0.08,			0.5,	80.5,	 0,0,NULL,		"HR 4458",	 0, "CD-32 8179 (HR 4458)"},	// 31.1 
 {AVE(.39,.41),	        0.90,		        0,			0,	0,	 0,0,NULL,		"12 Oph",	 1, "12 Ophiuchi"},				// 31.9
 {0.46,			0.92,			0,			0,	0,	 0,0,NULL,		"HR 511",	 0, "BD+63 238 (HR 511)"},		// 32.5
 {0.83,			0.87,			0,			0,	0,	 0,0,NULL,		"ALF Men",	 1, "Alpha Mensae"},			// 33.1
 {0.93,			0.79,			1.02,			0.5,	9000.,	 0,0,NULL,		"ZET1 Ret",	 1, "Zeta 1 Reticuli"},			// 39.4-39.5
 {0.99,			1.02,			0.79,			0.5,	9000.,	 0,0,NULL,		"ZET2 Ret",	 1, "Zeta 2 Reticuli"},			// 39.4-39.5
 {1.14,			1.05,			2.0,			0.55,	48.5,	 0,0,NULL,		"44 Boo",	 1, "44 Bootis A"},				// 41.6
 {1.7,			1.03,			0,			0,	0,	 0,0,&UMa47I,		"47 UMa",	 1, "47 Ursae Majoris"},		// 45.9
 {1.8,			1.03,			0,			0,	0,	 0,0,&horIotI,		"IOT Hor",	 1, "Iota Horologii"},			// 56.2
 {0.22,          	0.762,			(0.066+0.047),		0,	1500,	 0,0,NULL,		"EPS Ind",	 1, "Epsilon Indi"},			// 11.8  
 {AVE(.083,.09),        0.701,	        	0.924,			0.495,	23.3,	 0,0,NULL,		"70 Oph",	 1, "70 Ophiuchi B"},			// 16.6
 {0.28,			0.85,			0.85,			0.922,	88.,	 0,0,NULL,		"36 Oph",	 1, "36 Ophiuchi A"},			// 19.5
 {0.27,			0.85,			0.85,			0.922,	88.,	 0,0,NULL,		"36 Oph B",	 0, "36 Ophiuchi B"},			// 19.5
 {0.12,			0.75,			0.65,			0.58,	12.6,	 0,0,NULL,		"HR 6426",	 0, "MLO 4 (HR 6426) A"},		// 22.7
 {0.146,		0.80,			0.50,			0.5,	500.,	 0,0,NULL,		"BD-05 1844 A",  0, "BD-05 1844 A"},			// 28.3 
// {5500,			2,			.1,			0,	74.161984871,	 0,0,NULL,	"BA23",		 0, "BA23"}
 {1.3,			1.11,			0,			0,	0,	 0,0,&Bellerophon,	"51 Peg",	 1, "51 Pegasi"},
/* {2.6,			1.2,			.63,		       .5,	864.,	 0,0,&GamLepA80662I,	"Fictional 1",   0, "Fictional 1"},
 {0.38,			0.75,			(0.16+0.43),    	0,	418.,	 0,0,&Eri40A128424I,	"Fictional 2",	 0, "Fictional 2"},			// 16.5
*/
 {0.6,			0.905,			0.13,			0,	1100,	 0,0,&can55e,		"55 Can A",	1,	"55 Cancri A"},
 {0.0076,		0.13,			0.905,			0,	1100,	 0,0,NULL,		"55 Can B",	1,	"55 Cancri B"},
 {3.57,			1.27,			mass(0.00163),		0,	750,	 0,0,&UPSAndAb,		"UPS And A",	1,	"Upsilon Andromedae A"},
 {0.00163,		mass(0.00163),		1.27,			0,	750,	 0,0,NULL,		"UPS And B",	1,	"Upsilon Andromedae B"},
 {1.29,			0.972,			0.66,			0.497,  71.4,	 0,0,NULL,		"ETA Cas A",	1,	"Eta Cassiopeiae A"},
 {0.06,			0.66,			0.972,			0.497,	71.4,	 0,0,&fictional,	"ETA Cas B",	1,	"Eta Cassiopeiae B"},
 {1.49,			1.062,			0,			0,	0,	 0,0,&hd10180b,		"HD 10180",	1,	"HIP 7599"},
// {1.005714286,		1.33333333333333333333,	0,			0,	0,	 0,0,NULL,		"Kepler-47",	1,	"Kepler-47"},
 {0.0135,		0.31,			0,			0,	0,	 0,0,&gliese581e,	"Gliese 581",	1,	"Gliese 581"},
 {1.6,			1.1,			0,			0,	0,	 0,0,&hd10647b,		"HD 10647",	1,	"HR 506"},
// {30,			2.15,			0,			0,	0,	 0,0,&fictionala,	"Fictional 1",	1,	"Fictional 1"},
 {0.66,			0.95,			0.83,			0,	515,	 0,0,NULL,		"83 Leo A",	1,	"83 Leonis A"},
 {0.24,			0.83,			0.95,			0,	515,	 0,0,&leo83Ba,		"83 Leo B",	1,	"83 Leonis B"},
 {(0.840 + 0.014),	(1.043 + 0.362),	0,			0,	0,	 0,0,NULL,		"Kepler-47",	1,	"Kepler-47"}, 
// {2.7,			1.2,			0,			0,	0,	 0,0,&fictional2a,	"Fictional 2",	1,	"Fictional 2"},
// {4,			2.215012275,		0.98061764102115,	0.1,	20,	 0,0,NULL,		"Talax A",	0,	"Talax A (fictional)"},
// {0.93378943579204,	0.98061764102115,	2.215012275,		0.1,	20,	 0,0,NULL,		"Talax B",	0,	"Talax B (fictional)"},
};

// BD-05 1123 A:	 HR 1614, Gl 183 A, Hip 23311, HD 32147, SAO 131688, LHS 200, LTT 2412, LFT 382, and LPM 200. 
// CD-27 14659:		 HR 7722, Gl 785, Hip 99825, HD 192310, CP(D)-27 6972, SAO 189065, LHS 488, LTT 8009, LFT 1535, and LPM 731
// CD-32 8179 A:	 HR 4458, Gl 432 A, Hip 56452, HD 100623, CP(D)-32 3122, SAO 202583, LHS 308, LTT 4280, LFT 823, LPM 389, and E 439-246.  
// BD+63 238:		 HR 511*, Gl 75, Hip 8362, HD 10780, SAO 11983, LHS 1297, LTT 10619, and LFT 162. 
// 36 Ophiuchi B:	 HR 6401, Gl 663 B, HD 155885, SAO 185199, LHS 438, and ADS 10417 B. 
// MLO 4 A:			 HR 6426*, Gl 667 A, Hip 84709, HD 156384, CD-34 11626 A, CP-34 6803, SAO 208670, LHS 442, LTT 6888, LFT 1336, LPM 638, and UGPMF 433. 
// BD-05 1844 A:	 Gl 250 A, Hip 32984, HD 50281, SAO 133805, LHS 1875, LTT 2662, LFT 494, and LPM 244. 

// {.00006,		0.105,			0.1,			0.62,	5.5,	 0,0,NULL,		"",	"Luyten 726-8 A"},		// 8.7
// {0.039,		0.5,			0.59,			.48,	85.2,	 0,0,NULL,		"",	"61 Cygni B"},			// 11.4
// {0.05,		0.65,			0.75,			0.58,	12.6,	 0,0,NULL,		"",	"MLO 4 (HR 6426) B"},	// 22.7
// {1.1,		1.05,			0.4,			0.53,	0.6,	 0,0,NULL,		"",	"Xi Ursae Majoris Aa"},	// 27.3 
// {0,			0.4,			1.05,			0.53,	0.6,	 0,0,NULL,		"",	"Xi Ursae Majoris Ab"},	// 27.3
// {0.064,		0.76,			0.90,			0.51,	33.0,	 0,0,NULL,		"",	"Xi Bootis B"},			// 21.8

//seb: known exoplanets in A/U systems (specify -k to use)
/*	     No,    SMA,  Eccen., Axial Tilt,  Mass, Gas Giant?,  Dust Mass, Gas Mass, moon a,...000..., minor moons,Pointer-to-Moons, Pointer-to-next-planet*/

planets EPSErib  ={ 2,3.39, 0.702, 0, EM(490),   TRUE, EM(490),     0, ZEROES,0,NULL,   NULL};
planets EPSEric  ={ 1,40.0, 0.3, 0, EM(30),   TRUE, EM(30),     0, ZEROES,0,NULL,   &EPSErib};

//seb: not enough dust that close to star for it to auto-gen :(
//planets cyteen  ={ 1,0.07884, 0.01, 18.5, EM(0.7),   FALSE, EM(0.7),     0, ZEROES,0,NULL,   NULL};
planets cyteen  ={ 1,0.098, 0.01, 18.5, EM(0.7),   FALSE, EM(0.7),     0, ZEROES,0,NULL,   NULL};

planets GL849b  ={ 1,2.35, 0.07, 0.0, EM(260),   TRUE, EM(260),     0, ZEROES,0,NULL,   NULL};

planets ILAqrb	={ 3, 0.208317,0.0324,0.0,    EM(720.0), TRUE,EM(720.0),0,ZEROES,0,NULL,NULL};
planets ILAqrc	={ 2, 0.12959, 0.25591,0.0,   EM(230.0), TRUE,EM(230.0),0,ZEROES,0,NULL,&ILAqrb};
planets ILAqrd	={ 1, 0.020807,0.207,0.0,       EM(7.0), FALSE,EM(7.0),0,ZEROES,0,NULL,&ILAqrc};

planets HD20794d  ={ 3,0.3499, 0, 0.0, EM(5),   FALSE, EM(5),     0, ZEROES,0,NULL,   NULL};
planets HD20794c  ={ 2,0.2036, 0, 0.0, EM(2),   FALSE, EM(2),     0, ZEROES,0,NULL,   &HD20794d};
planets HD20794b  ={ 1,0.1207, 0, 0.0, EM(3),   FALSE, EM(3),     0, ZEROES,0,NULL,   &HD20794c};

planets BETHyib  ={ 1,8, 0, 0.0, EM(1100),   TRUE, EM(1100),     0, ZEROES,0,NULL,   NULL};

star	various[] = 
{
// seb: stars of a-u stations; data from SolStation or Celestia nearstars.stc
// L	Mass	Mass2	Eccen. SMAxis	 Inc, AN, Planets  Designation   InCel Name
{0.000427,0.17, 0,0,0,0,0,NULL,"HIP 87937", 0, "Alpha SS1:Barnard's Star::BY Dra:BY Draconis"}, 
{1.52,1.105,0.934,0.519,10.9,82.22,67.30,NULL,"ALF Cen A", 0, "Beta SS2:Rigel Kentaurus A:Alpha Centauri A"},
{0.446,0.934,1.105,0.519,12.8,82.22,67.30,NULL,"ALF Cen B", 0, "Beta SS2:Rigel Kentaurus B:Alpha Centauri B",},
{0.0859,0.70,0.63,0.40,39.6,132,165,NULL,"HIP 104214", 0, "Bryant's Star SS3:61 Cyg A:61 Cygni A:Gl 820 A"},
{0.0405,0.63,0.70,0.40,46.8,132,165,NULL,"HIP 104217", 0, "Bryant's Star SS3:61 Cyg B:61 Cygni A:Gl 820 A"},
{0.000501,0.2,0,0,0,0,0,NULL,"Ross 154", 0, "Glory SS4:Ross 154:Gl 729:V1216 Sgr"},
{0.001969,0.447,0,0,30,34.04,120.09,NULL,"Kruger 60", 0, "Venture SS5:HD 239960A:HIP 110893"},
{0.00159,0.271,0.176,0.410,3.53,34.04,120.09,NULL,"Kruger 60 A", 0, "Venture SS5:Gl 860 A:Kruger 60 A:HD 239960 A:HIP 110893 A"},
{0.000379,0.176,0.271,0.410,6.23,34.04,120.09,NULL,"Kruger 60 B", 0, "Venture SS5:Gl 860 A:D0 Cephei:Kruger 60 B:HD 239960 B:HIP 110893 B"},
{0.00178,0.29,0,0,0,0,0,NULL,"EV Lac", 0, "Galileo SS6:EV Lacertae"},
{0.000104,0.12,0,0,0,0,0,NULL,"Ross 248", 0, "Thule SS7:Ross 248:HH Andromedae"},
{0.0064,0.40,0.08,0,26.5,67.9,308.4,NULL,"Groombridge 34 A", 0, "Olympus SS8:GX And:GX Andromedae:ADS 246 A"},
{0.000411,0.08,0.40,0,121.3,67.9,308.4,NULL,"Groombridge 34 B", 0, "Olympus SS8:GQ And:GQ Andromedae:ADS 246 B"},
{0.0000908,0.21,0,0,16.5,101.3,159.5,NULL,"Luyten 726-8", 0,"Eldorado SS9:Gliese 65"},
{0.0000553,0.11,0.10,0.62,2.5,101.3,159.5,NULL,"Luyten 726-8 A", 0,"Eldorado SS9:BL Ceti:Gliese 65 A"},
{0.0000355,0.10,0.11,0.62,3.0,101.3,159.5,NULL,"Luyten 726-8 B", 0,"Eldorado SS9:UV Ceti:Gliese 65 B"},
{0.458,0.783,0,0,0,0,0,NULL,"HIP 8102", 0, "Pell SS10:TAU Cet:Tau Ceti:52 Cet:Gliese 71:HD 10700"},
{0.284,0.83,0,0,0,0,0,&EPSEric,"HIP 16537", 1, "Viking SS11:EPS Eri:Epsilon Eridani"}, // 2-3P,2as.b.,comets},
{0.000173,0.63,0,0,4.0,0,0,NULL,"HIP 3829", 0, "Mariner SS12:Van Maanen's Star:Gliese 35:Wolf 28"}, // WD }, p=1.57
{0.00775,0.51,0,0,0,0,0,&cyteen,"HIP 117473", 1, "Cyteen SS13:Lalande 46650:BR Psc"}, // ; L=0.00775?},
{0.132,0.75,0,0,0,0,0,NULL,"HIP 108296", 0, "Esperance:HR 8372:BD+20 5046:HD 209527"},
{0.241,0.83,0,0,0,0,0,NULL,"HIP 3765", 0, "Fargone:Gliese 33:Wolf 25:BD+04 123"}, //  10yr jovian? wikipedia},
{0.000915,0.3,0,0,0,0,0,NULL,"GJ 1243", 0, "Paradise:GJ 1243:G 208-42"},  //flare rot:0.593 days},
{0.00486,0.36,0,0,0,0,0,&GL849b,"HIP 109388", 1, "Wyatts:Gl 849"}, // HIP 109388 pl: 2.35au;1890 lowecc wikip},
{0.00157,0.32,0,0,0,0,0,&ILAqrd,"IL Aqr", 1, "Russell's:Ross 780:HIP 113020:IL Aquarii"}, // HIP 113020 4 pl rot:40d},

// L	Mass	Mass2	Eccen. SMAxis	 Inc, AN, Planets  Designation   InCel Name
{0.0000330,0.272,0,0.024,21.42,43.34,341.84,NULL,"GJ 2005", 0, "Voyager:GJ 2005:LHS 1070"},
{0.000017,0.115,0.157,0.05,12.74,43.34,341.84,NULL,"GJ 2005 A", 0, "Voyager:GJ 2005 A:LHS 1070 A"}, 
{0.0000165,0.0785,0.0785,0.024,3.57,43.34,341.84,NULL,"GJ 2005 B", 0, "Voyager:GJ 2005 B:LHS 1070 B"},
{0.000015,0.0785,0.0785,0.024,3.57,43.34,341.84,NULL,"GJ 2005 C", 0, "Voyager:GJ 2005 C:LHS 1070 C"}, 

{0.00292,0.43,0,0,0.6,0,0,NULL,"Ross 775", 0, "Pan-Paris:GL 829:HIP 106106"},
{0.00146,0.26,0.26,0,0.083,0,0,NULL,"Ross 775 A", 0, "Pan-Paris:GL 829 A:HIP 106106 A"}, // HIP 106106},
{0.00146,0.26,0.26,0,0.083,0,0,NULL,"Ross 775 B", 0, "Pan-Paris:GL 829 B:HIP 106106 B"}, // HIP 106106},
{0.991,0.998,0,0,0,0,0,NULL,"ZET Ret", 0, "Gehenna:Zeta2 Reticuli"}, // Zeta 2 Ret},
{29.6,2.0,0,0,0,0,0,NULL,"BET Cas", 0, "[Union st]:Beta Cassopeiae"},
{0.617,0.97,0,0,0.667,0,0,&HD20794b,"82 Eri", 1, "[Union st]:82 Eridani:HIP 15510:HD 20794"}, // HIP 15510; 3 hot superE},
{0.00377,0.34,0,0,0,0,0,NULL,"Kapteyn's Star", 0,  "[Union st]:VZ Pictoris:HIP 24186"},
{3.55,1.1,0,0,0,0,0,&BETHyib,"HIP 2021", 1, "Istra:BET Hyi:Beta Hydri II"}, // 4au gas giant? 45 day gas giant?}
{0.359,0.89,0,0,0.667,0,0,NULL,"40 Eri A", 0, "Endeavor:40 Eridani A:Keid A:HIP 19849 A:HD 26965 A"}, // ignore B&C -- 418 au away
//seb: end of au stars
//seb: JimB's systems omitted
// L			Mass			Mass2			Eccen.	SMAxis	 Planets	Designation	Name
// {1.00,			1.00,			0,			0,	0,	 0,0,&mercury,	"Sol",		 1, "The Solar System"},		// 0
// {14800.,		8,			0,			0,	0,	 0,0,NULL,		"ALF Car",	 1, "Canopus"}*/
};

catalog	solstation	= {sizeof(web) / sizeof (star),		"w", 	&web};
catalog	dole		= {sizeof(perdole) / sizeof (star),     "d",	&perdole};
catalog jimb	        = {sizeof(various) / sizeof (star),     "F",	&various};

ChemTable    gases[] =
{
//   An		sym		HTML symbol                     				 name			Aw		melt		boil		dens		ABUNDe		ABUNDs		Rea	Max inspired pp
  {AN_H,	"H",		"H<SUB><SMALL>2</SMALL></SUB>",	 				"Hydrogen",		1.0079,		14.06,		20.40,		8.99e-05,	0.00125893,	27925.4,	1,	0.0},
  {AN_HE,	"He",		"He",				 				"Helium",		4.0026,		3.46,		4.20,		0.0001787,	7.94328e-09,	2722.7,		0,	MAX_HE_IPP},
/*  {3,		"Li",		"Li",								"Lithium",		6.9400,		453.74,		1620.00,	0.53,		1.99526e-05,	5.71479e-05,	1,	0.0},
  {4,		"Be",		"Be",								"Beryllium",		9.0122,		1551.20,	2773.00,	1.848,		2.51189e-06,	7.29458e-07,    0,	0.0},
  {5,		"B",		"B",								"Boron",		10.8100,	2352.20,	3923.20,	2.34,		1e-05,		2.11836e-05,    0,	0.0},
  {6,		"C",		"C",								"Carbon",		12.0110,	3823.20,	5103.00,	2.62,		0.000199526,	10.0925,	0,	0.0},
*/  {AN_N,	"N",		"N<SUB><SMALL>2</SMALL></SUB>",					"Nitrogen",		14.0067,	63.34,		77.40,		0.0012506,	1.99526e-05,	3.13329,	0,	MAX_N2_IPP},
  {AN_O,	"O",		"O<SUB><SMALL>2</SMALL></SUB>",					"Oxygen",		15.9994,	54.80,		90.20,		0.001429,	0.501187,	23.8232,	10,	MAX_O2_IPP},
/*  {9,		"F",		"F",								"Fluorine",		18.9984,	53.58,		85.10,		0.001696,	0.000630957,	0.000843335,	40,	MAX_F_IPP},
*/  {AN_NE,	"Ne",		"Ne",								"Neon",			20.1700,	24.53,		27.10,		0.0009,		5.01187e-09,	3.4435e-5,	0,	MAX_NE_IPP},
/*  {11,		"Na",		"Na",								"Sodium",		22.9898,	371.01,		1154.60,	0.971,		0.0251189,	0.0574116,	5,	0.0},
  {12,		"Mg",		"Mg",								"Magnesium",		24.3050,	922.00,		1378.00,	1.738,		0.0251189,	1.07399,	2,	0.0},
  {13,		"Al",		"Al",								"Aluminum",		26.9815,	933.57,		2740.00,	2.702,		0.0794328,	0.084918,	0,	0.0},
  {14,		"Si",		"Si",								"Silicon",		28.0855,	1683.20,	3553.00,	2.33,		0.316228,	1,		0,	0.0},
  {15,		"P",		"P",								"Phosphorus",		30.9738,	317.30,		553.70,		1.82,		0.001,		0.0103992,	0,	0.0},
  {16,		"S",		"S",								"Sulfur",		32.0600,	386.00,		717.90,		2.07,		0.000251189,	0.515229,	0,	0.0},
  {17,		"Cl",		"Cl",								"Chlorine",		35.4530,	172.22,		239.20,		0.003214,	0.000125893,	0.005236,	30,	MAX_CL_IPP},
*/  {AN_AR,	"Ar",		"Ar",								"Argon",		39.9480,	84.00,		87.30,		0.0017824,	3.16228e-06,	0.100925,	0,	MAX_AR_IPP},
/*  {19,		"K",		"K",								"Potassium",		39.0983,	336.50,		1038.70,	0.862,		0.0199526,	0.00376704,     0,	0.0},
  {20,		"Ca",		"Ca",								"Calcium",		40.0800,	1112.20,	1767.00,	1.55,		0.0446684,	0.0610942,      0,	0.0},
  {21,		"Sc",		"Sc",								"Scandium",		44.9559,	1812.20,	3021.00,	3,		1.99526e-05,	3.41979e-05,	0,	0.0},
  {22,		"Ti",		"Ti",								"Titanium",		47.9000,	1933.20,	3558.00,	4.5,		0.00630957,	0.00239883,	0,	0.0},
  {23,		"V",		"V",								"Vanadium",		50.9415,	2163.20,	3623.00,	5.8,		0.000125893,	0.000293089,    0,	0.0},
  {24,		"Cr",		"Cr",								"Chromium",		51.9960,	2130.20,	2963.00,	7.19,		0.0001,		0.0134896,	0,	0.0},
  {25,		"Mn",		"Mn",								"Manganese",		54.9380,	1517.20,	2333.00,	7.43,		0.001,		0.00954993,	0,	0.0},
  {26,		"Fe",		"Fe",								"Iron",			55.8470,	1808.20,	3023.00,	7.86,		0.0630957,	0.899498,	0,	0.0},
  {27,		"Co",		"Co",								"Cobalt",		58.9332,	1768.20,	3373.00,	8.9,		2.51189e-05,	0.00224905,	0,	0.0},
  {28,		"Ni",		"Ni",								"Nickel",		58.7100,	1726.20,	3193.00,	8.9,		7.94328e-05,	0.0493174,	0,	0.0},
  {29,		"Cu",		"Cu",								"Copper",		63.5460,	1356.60,	2843.00,	8.96,		5.01187e-05,	0.000522396,	0,	0.0},
  {30,		"Zn",		"Zn",								"Zinc",			65.3800,	692.78,		1180.00,	7.14,		6.16595e-05,	0.00125893,	0,	0.0},
  {31,		"Ga",		"Ga",								"Gallium",		69.7230,	302.98,		2676.00,	5.907,		1.58489e-05,	3.77572e-05,	1,	0.0},
  {32,		"Ge",		"Ge",								"Germanium",		72.5900,	1210.60,	3123.00,	5.323,		5.01187e-06,	0.000119124,	0,	0.0},
  {33,		"As",		"As",								"Arsenic",		74.9216,	886.00,		886.16,		5.72,		1.99526e-06,	6.56145e-06,	0,	0.0},
  {34,		"Se",		"Se",								"Selenium",		78.9600,	490.20,		958.00,		4.79,		5.01187e-08,	6.20869e-05,	0,	0.0},
  {35,		"Br",		"Br",								"Bromine",		79.9040,	266.00,		332.70,		3.119,		2.51189e-06,	1.18032e-05,	2,	0.0},
*/  {AN_KR,	"Kr",		"Kr",								"Krypton",		83.8000,	116.60,		119.70,		0.003708,	1e-10,		4.4978e-05,	0,	MAX_KR_IPP},
/*  {37,		"Rb",		"Rb",								"Rubidium",		85.4670,	312.09,		961.00,		1.53,		0.0001,		7.09578e-06,	1,	0.0},
  {38,		"Sr",		"Sr",								"Strontium",		87.6200,	1042.20,	1654.00,	2.6,		0.000398107,	2.34963e-05,	0,	0.0},
  {39,		"Y",		"Y",								"Yttrium",		88.9059,	1796.20,	3537.00,	4.47,		3.23594e-05,	4.64515e-06,	0,	0.0},
  {40,		"Zr",		"Zr",								"Zirconium",		91.2200,	2125.20,	4473.00,	6.4,		0.00017378,	1.14025e-05,	0,	0.0},
  {41,		"Nb",		"Nb",								"Niobium",		92.9064,	2741.20,	5031.00,	8.57,		1.99526e-05,	6.98232e-07,	0,	0.0},
  {42,		"Mo",		"Mo",								"Molybdenum",		95.9400,	2890.20,	4923.00,	10.2,		1.58489e-06,	2.5527e-06,	0,	0.0},
  {43,		"Tc",		"Tc",								"Technetium",		98.9062,	2445.20,	4840.00,	11.5,		0,		0,		0,	0.0},
  {44,		"Ru",		"Ru",								"Ruthenium",		101.0700,	2583.20,	4323.00,	12.2,		1e-09,		1.86209e-06,	0,	0.0},
  {45,		"Rh",		"Rh",								"Rhodium",		102.9055,	2238.20,	4033.00,	12.4,		1e-09,		3.4435e-07,	0,	0.0},
  {46,		"Pd",		"Pd",								"Palladium",		106.4000,	1827.20,	3213.00,	12.02,		1e-08,		1.38995e-06,	0,	0.0},
  {47,		"Ag",		"Ag",								"Silver",		107.8680,	1235.10,	2428.00,	10.5,		6.30957e-08,	4.86407e-07,	0,	0.0},
  {48,		"Cd",		"Cd",								"Cadmium",		112.4100,	594.10,		1038.00,	8.65,		1.99526e-07,	1.61065e-06,	0,	0.0},
  {49,		"In",		"In",								"Indium",		114.8200,	429.81,		2353.00,	7.31,		1e-07,		1.84077e-07,	0,	0.0},
  {50,		"Sn",		"Sn",								"Tin",			118.6900,	505.17,		2896.00,	7.3,		1.99526e-06,	3.81944e-06,	0,	0.0},
  {51,		"Sb",		"Sb",								"Antimony",		121.7500,	903.94,		1860.00,	6.684,		1.99526e-07,	3.0903e-07,	0,	0.0},
  {52,		"Te",		"Te",								"Tellurium",		127.6000,	722.70,		1263.00,	6.24,		1e-09,		4.80839e-06,	0,	0.0},
  {53,		"I",		"I",								"Iodine",		126.9045,	386.70,		458.40,		4.93,		5.01187e-07,	8.99498e-07,	0,	0.0},
*/  {AN_XE,	"Xe",		"Xe",								"Xenon",		131.3000,	161.30,		165.00,		0.00588,	3.16228e-11,	4.69894e-06,	0,	MAX_XE_IPP},
/*  {55,		"Cs",		"Cs",								"Cesium",		132.9054,	301.60,		978.00,		1.873,		1e-06,		3.72392e-07,	1,	0.0},
  {56,		"Ba",		"Ba",								"Barium",		137.3300,	998.20,		2123.00,	3.51,		0.000398107,	4.48745e-06,	0,	0.0},
  {57,		"La",		"La",								"Lanthanum",		138.9055,	1193.20,	3693.00,	6.7,		3.16228e-05,	4.45656e-07,	0,	0.0},
  {58,		"Ce",		"Ce",								"Cerium",		140.1200,	1071.20,	3743.00,	6.78,		6.30957e-05,	1.13501e-06,	0,	0.0},
  {59,		"Pr",		"Pr",								"Praseodymium",		140.9077,	1204.20,	3293.00,	6.77,		7.94328e-06,	1.66725e-07,	0,	0.0},
  {60,		"Nd",		"Nd",								"Neodymium",		144.2400,	1283.20,	3300.00,	7,		2.51189e-05,	8.27942e-07,	0,	0.0},
  {61,		"Pm",		"Pm",								"Promethium",		145.0000,	1353.20,	3273.00,	6.475,		5.01187e-26,	0,		0,	0.0},
  {62,		"Sm",		"Sm",								"Samarium",		150.4000,	1345.20,	2073.00,	7.54,		6.30957e-06,	2.58226e-07,	0,	0.0},
  {63,		"Eu",		"Eu",								"Europium",		151.9600,	1095.20,	1712.00,	5.259,		1.25893e-06,	9.72747e-08,	0,	0.0},
  {64,		"Gd",		"Gd",								"Gadolinium",		157.2500,	1584.20,	3273.00,	7.895,		5.01187e-06,	3.3037e-07,	0,	0.0},
  {65,		"Tb",		"Tb",								"Terbium",		158.9254,	1633.20,	3073.00,	8.27,		1e-06,		6.0256e-08,	0,	0.0},
  {66,		"Dy",		"Dy",								"Dysprosium",		162.5000,	1682.20,	2873.00,	8.536,		3.16228e-06,	3.94457e-07,	0,	0.0},
  {67,		"Ho",		"Ho",								"Holmium",		164.9304,	1743.20,	2873.00,	8.8,		1.25893e-06,	8.89201e-08,	0,	0.0},
  {68,		"Er",		"Er",								"Erbium",		167.2600,	1795.20,	3173.00,	9.05,		2.51189e-06,	2.50611e-07,	0,	0.0},
  {69,		"Tm",		"Tm",								"Thulium",		168.9342,	1818.20,	2000.00,	9.33,		5.01187e-07,	3.77572e-08,	0,	0.0},
  {70,		"Yb",		"Yb",								"Ytterbium",		173.0400,	1097.20,	1700.00,	6.98,		3.16228e-06,	2.47742e-07,	0,	0.0},
  {71,		"Lu",		"Lu",								"Lutetium",		174.9600,	1929.20,	3600.00,	9.85,		5.01187e-07,	3.67282e-08,	0,	0.0},
  {72,		"Hf",		"Hf",								"Hafnium",		178.4900,	2495.20,	4723.00,	13.2,		2.51189e-06,	1.5417e-07,	0,	0.0},
  {73,		"Ta",		"Ta",								"Tantalum",		180.9470,	3269.20,	5807.00,	16.6,		1.99526e-06,	2.07014e-08,	0,	0.0},
  {74,		"W",		"W",								"Tungsten",		183.8500,	3683.20,	5773.00,	19.3,		1.58489e-06,	1.33045e-07,	0,	0.0},
  {75,		"Re",		"Re",								"Rhenium",		186.2070,	3453.20,	5923.00,	21,		5.01187e-09,	5.16416e-08,	0,	0.0},
  {76,		"Os",		"Os",								"Osmium",		190.2000,	3318.20,	5298.00,	22.4,		1.58489e-09,	6.74528e-07,	0,	0.0},
  {77,		"Ir",		"Ir",								"Iridium",		192.2200,	2683.20,	4823.00,	22.42,		1e-09,		6.60693e-07,	0,	0.0},
  {78,		"Pt",		"Pt",								"Platinum",		195.0900,	2045.20,	4443.00,	21.45,		5.01187e-09,	1.33968e-06,	0,	0.0},
  {79,		"Au",		"Au",								"Gold",			196.9665,	1337.63,	3081.00,	19.32,		3.98107e-09,	1.87068e-07,	0,	0.0},
  {80,		"Hg",		"Hg",								"Mercury",		200.5900,	234.33,		630.00,		13.546,		7.94328e-08,	3.39625e-07,	0,	0.0},
  {81,		"Tl",		"Tl",								"Thallium",		204.3700,	576.70,		1730.00,	11.85,		5.01187e-07,	1.84077e-07,	0,	0.0},
  {82,		"Pb",		"Pb",								"Lead",			207.2000,	600.70,		2024.00,	11.34,		1.25893e-05,	3.14775e-06,	0,	0.0},
  {83,		"Bi",		"Bi",								"Bismuth",		208.9804,	544.50,		1837.00,	9.8,		1.58489e-07,	1.4388e-07,	0,	0.0},
  {84,		"Po",		"Po",								"Polonium",		209.0000,	527.20,		1235.00,	9.4,		1.99526e-16,	0,		0,	0.0},
  {85,		"At",		"At",								"Astatine",		210.0000,	575.20,		610.16,		0,		0,		0,		0,	0.0},
  {86,		"Rn",		"Rn",								"Radon",		222.0000,	202.20,		211.00,		0.00973,	3.98107e-19,	0,		0,	0.0},
  {87,		"Fr",		"Fr",								"Francium",		223.0000,	300.20,		950.00,		0,		0,		0,		0,	0.0},
  {88,		"Ra",		"Ra",								"Radium",		226.0254,	973.20,		1973.00,	5,		1e-12,		0,		0,	0.0},
  {89,		"Ac",		"Ac",								"Actinium",		227.0000,	1323.20,	2743.00,	0.07,		5.01187e-16,	0,		0,	0.0},
  {90, 		"Th",		"Th",								"Thorium",		232.0381,	2023.20,	5123.00,	11.7,		1e-05,		3.34965e-08,	0,	0.0},
  {91,		"Pa",		"Pa",								"Protactinium",		231.0359,	1873.20,	4500.00,	15.4,		1.25893e-12,	0,		0,	0.0},
  {92,		"U",		"U",								"Uranium",		238.0290,	1405.20,	4203.00,	18.9,		2.51189e-06,	8.99498e-09,	0,	0.0},
*///                                                                     from here down, these columns were originally: 0.001,         0
  {AN_NH3,	"NH3",		"NH<SUB><SMALL>3</SMALL></SUB>",				"Ammonia",		17.0000,	195.46,		239.66,		0.001,		0.002,		0.0001,		1,	MAX_NH3_IPP},
  {AN_H2O,	"H2O",		"H<SUB><SMALL>2</SMALL></SUB>O",				"Water",		18.0000,	273.16,		373.16,		1.000,		0.03,		0.001,		0,	0.0},
  {AN_CO2,	"CO2",		"CO<SUB><SMALL>2</SMALL></SUB>",				"CarbonDioxide",	44.0000,	194.66,		194.66,		0.001,		0.01,		0.0005,		0,	MAX_CO2_IPP},
  {AN_O3,	"O3",		"O<SUB><SMALL>3</SMALL></SUB>",					"Ozone",		48.0000,	80.16,		161.16,		0.001,		0.001,		0.000001,	2,	MAX_O3_IPP},
  {AN_CH4,	"CH4",		"CH<SUB><SMALL>4</SMALL></SUB>",				"Methane",		16.0000,	90.16,		109.16,		0.010,		0.005,		0.0001,		1,	MAX_CH4_IPP},
  {905,		"CH3CH2OH",	"CH<sub><small>3</small></sub>CH<sub><small>2</small></sub>OH",	"Ethanol",		46,		159.06,		351.66,		0.895,		0.001,		0.001,		0,	0.0},
  
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
void generate_stellar_system(sun*, int, planet_pointer, char, int, char *, long double, long double, long double, long double, int, int); // seb add inner dust limit& ecc_coef, inner_planet_factor
void calculate_gases(sun*, planet_pointer, char*);
void generate_planet(planet_pointer, int, sun*, int, char*, int, int, int, long double);
void generate_planets(sun*, int, char, int, char *, int, int);
void usage(char *);
static int diminishing_abundance(const void *xp, const void *yp);
static int diminishing_pressure(const void *xp, const void *yp);
long double get_accreated_gas_pressure(planet_pointer);
int is_gas_giant(planet_pointer);

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

void generate_stellar_system(sun* sun,
			     int 			use_seed_system, 
			     planet_pointer seed_system,
			     char			flag_char,
			     int			sys_no,
			     char*			system_name,
			     long double 	inner_dust_limit, // seb
			     long double 	outer_planet_limit,
			     long double 	ecc_coef, // seb
			     long double 	inner_planet_factor, // seb
			     int			do_gases,
			     int			do_moons)
{
	long double		outer_dust_limit;

	/* seb: allow whatever star mass user wants to specify
	if ((sun->mass < 0.2) || (sun->mass > 1.5))
		sun->mass		 = random_number(0.7,1.4);
	*/

	outer_dust_limit	 = stellar_dust_limit(sun->mass);

	if (sun->luminosity == 0.0)
		sun->luminosity	 = luminosity(sun->mass);
	if (sun->mass == 0.0)
		sun->mass = luminosity_to_mass(sun->luminosity);
	
	sun->r_ecosphere	 = sqrt(sun->luminosity);
	sun->life			 = 1.0E10 * (sun->mass / sun->luminosity);

	if (use_seed_system)
	{
		innermost_planet = seed_system;
		
		//if (system_name == "Fictional 1"
		  /*long double min_age = 1.0E9;
		  long double max_age = 6.0E9;
		
		if (sun->life < max_age)
			max_age = sun->life;*/
		long double min_age = 1.0E9;
		long double max_age = sun->life;
		
		if (strcmp(system_name, "Fictional 1") == 0)
		{
		  sun->life = max_age = 7.54345734950E9;
		}
	
		sun->age = random_number(min_age, max_age);
	}
	else
	{
		/*long double min_age = 1.0E9;
		long double max_age = 6.0E9;
		
		if (sun->life < max_age)
			max_age = sun->life;*/
		long double min_age = 1.0E9;
		long double max_age = sun->life;
		
		if (strcmp(system_name, "Fictional 1") == 0)
		{
		  sun->life = max_age = 7.54345734950E9;
		}
		
		innermost_planet = dist_planetary_masses(sun->mass,
					      		 sun->luminosity,
							 inner_dust_limit,// seb
		                                         outer_dust_limit,
							 outer_planet_limit,
							 dust_density_coeff,
							 ecc_coef,
							 inner_planet_factor,
							 seed_system,
							 do_moons);
		/*if (strcmp(system_name, "Gliese 581") == 0)
		{
		  sun->age = random_number(7.0E9, 11.E9);
		}
		else*/
		{
		  sun->age = random_number(min_age, max_age);
		}
	}

	generate_planets(sun,
					 !use_seed_system, 
					 flag_char,
					 sys_no,
					 system_name,
					 do_gases,
					 do_moons);
}

void calculate_gases(sun* sun, planet_pointer planet, char* planet_id)
{
  if (planet->surf_pressure > 0 || planet->gas_giant)
  {
    long double *amount = (long double*)calloc((max_gas+1), sizeof(long double));
    long double totamount = 0;
    long double pressure  = planet->surf_pressure/MILLIBARS_PER_BAR;
    int n = 0;
    int			i;
    
    if (is_gas_giant(planet) && planet->surf_pressure == 0)
    {
      planet->surf_pressure = planet->surf_pressure + get_accreated_gas_pressure(planet);
      iterate_surface_temp(planet);
      pressure = planet->surf_pressure / MILLIBARS_PER_BAR;
    }
    
    for (i = 0; i < max_gas; i++)
    {
      long double yp = gases[i].boil / (373. * ((log((pressure) + 0.001) / -5050.5) + (1.0 / 373.)));
      
      if (((yp >= 0 && yp < planet->low_temp) || is_gas_giant(planet)) && (gases[i].weight >= planet->molec_weight))
      {
	long double	vrms	= rms_vel(gases[i].weight, planet->exospheric_temp);
	long double	pvrms	= pow(1 / (1 + vrms / planet->esc_velocity), sun->age / 1e9);
	long double	abund	= gases[i].abunds; 				/* gases[i].abunde */
	long double	react	= 1.0;
	long double	fract	= 1.0;
	long double	pres2	= 1.0;
	
	if (strcmp(gases[i].symbol, "Ar") == 0)
	{
	  react = .15 * sun->age/4e9;
	}
	else if (strcmp(gases[i].symbol, "He") == 0)
	{
	  abund = abund * (0.001 + (planet->gas_mass / planet->mass));
	  pres2 = (0.75 + pressure);
	  react = pow(1 / (1 + gases[i].reactivity), sun->age/2e9 * pres2);
	}
	else if ((strcmp(gases[i].symbol, "O") == 0 || strcmp(gases[i].symbol, "O2") == 0) && sun->age > 2e9 &&  (planet->gas_giant || (planet->surf_temp > 270 && planet->surf_temp < 400)))
	{
	  /*	pres2 = (0.65 + pressure/2);			Breathable - M: .55-1.4 	*/
	  pres2 = (0.89 + pressure/4);		/*	Breathable - M: .6 -1.8 	*/
	  react = pow(1 / (1 + gases[i].reactivity), pow(sun->age/2e9, 0.25) * pres2);
	}
	else if (strcmp(gases[i].symbol, "CO2") == 0 && sun->age > 2e9 && (planet->gas_giant || (planet->surf_temp > 270 && planet->surf_temp < 400)))
	{
	  pres2 = (0.75 + pressure);
	  react = pow(1 / (1 + gases[i].reactivity), pow(sun->age/2e9, 0.5) * pres2);
	  react *= 1.5;
	}
	else if (strcmp(sun->name, "Fictional 2") == 0 && (strcmp(gases[i].symbol, "F") == 0 || strcmp(gases[i].symbol, "Cl") == 0))
	{
	  abund = 0;
	}
	else 
	{
	  pres2 = (0.75 + pressure);
	  react = pow(1 / (1 + gases[i].reactivity), sun->age/2e9 * pres2);
	}
	
	fract = (1 - (planet->molec_weight / gases[i].weight));
	
	amount[i] = abund * pvrms * react * fract;
	
	if ((flag_verbose & 0x4000) && (strcmp(gases[i].symbol, "O") == 0 || strcmp(gases[i].symbol, "N") == 0 || strcmp(gases[i].symbol, "Ar") == 0 || strcmp(gases[i].symbol, "He") == 0 || strcmp(gases[i].symbol, "CO2") == 0))
	{
	  fprintf (stderr, "%-5.2Lf %-3.3s, %-5.2Lf = a %-5.2Lf * p %-5.2Lf * r %-5.2Lf * p2 %-5.2Lf * f %-5.2Lf\t(%.3Lf%%)\n", planet->mass * SUN_MASS_IN_EARTH_MASSES, gases[i].symbol, amount[i], abund, pvrms, react, pres2, fract, 100.0 * (planet->gas_mass / planet->mass));
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
	  planet->atmosphere[n].surf_pressure = planet->surf_pressure * amount[i] / totamount;
	  
	  if (flag_verbose & 0x2000)
	  {
	    if ((planet->atmosphere[n].num == AN_O) && inspired_partial_pressure (planet->surf_pressure, planet->atmosphere[n].surf_pressure) > gases[i].max_ipp)
	    {
	      fprintf (stderr, "%s\t Poisoned by O2\n", planet_id);
	    }
	  }
	  
	  n++;
	}
      }
      
      qsort(planet->atmosphere, planet->gases, sizeof(gas), diminishing_pressure);
      
      if (flag_verbose & 0x0010)
      {
	fprintf (stderr, "\n%s (%5.1Lf AU) gases:\n", planet_id, planet->a);
	
	for (i = 0; i < planet->gases; i++)
	{
	  fprintf (stderr, "%3d: %6.1Lf, %11.7Lf%%\n", planet->atmosphere[i].num, planet->atmosphere[i].surf_pressure, 100. * (planet->atmosphere[i].surf_pressure / planet->surf_pressure));
	}
      }
    }
    
    free(amount);
  }
}

void calculate_gases_old(sun*			sun,
					 planet_pointer	planet,
					 char*			planet_id)
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
			long double yp = gases[i].boil /
							 (373. * ((log((pressure) + 0.001) / -5050.5) + 
									 (1.0 / 373.)));
			
			if ((yp >= 0 && yp < planet->low_temp)
			 && (gases[i].weight >= planet->molec_weight))
			{
				long double	vrms	= rms_vel(gases[i].weight, planet->exospheric_temp);
				long double	pvrms	= pow(1 / (1 + vrms / planet->esc_velocity), sun->age / 1e9);
				long double	abund	= gases[i].abunds; 				/* gases[i].abunde */
				long double react	= 1.0;
				long double fract	= 1.0;
				long double pres2	= 1.0;
			
				if (strcmp(gases[i].symbol, "Ar") == 0)
				{
					react = .15 * sun->age/4e9;
				}
				else if (strcmp(gases[i].symbol, "He") == 0)
				{
					abund = abund * (0.001 + (planet->gas_mass / planet->mass));
					pres2 = (0.75 + pressure);
					react = pow(1 / (1 + gases[i].reactivity), 
								sun->age/2e9 * pres2);
				}
				else if ((strcmp(gases[i].symbol, "O") == 0 ||
					  strcmp(gases[i].symbol, "O3") == 0) && //seb: typo? O2 --> O3
						 sun->age > 2e9 &&
						 planet->surf_temp > 270 && planet->surf_temp < 400)
				{
				//	pres2 = (0.65 + pressure/2);		/*	Breathable - M: .55-1.4 	*/
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
							fprintf (stderr, "%s\t Poisoned by O2\n",
									 planet_id);
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
				fprintf (stderr, "\n%s (%5.1Lf AU) gases:\n",
						planet_id, planet->a);
				
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

void generate_planet(planet_pointer	planet,
					 int			planet_no,
					 sun*			sun,
					 int 			random_tilt, 
					 char*			planet_id,
					 int			do_gases,
					 int			do_moons,
					 int			is_moon,
					 long double		parent_mass
		    )
{
  if (planet->a == 0.131833228 && strcmp(sun->name, "RU M0V 30014") == 0)
    planet->gas_giant = FALSE;
  long double tmp;
  long double ecc_coef;
  ecc_coef = 0.077; // seb: use dole value for now for moons
		planet->type = tUnknown;
		planet->atmosphere		= NULL;
		planet->gases			= 0;
		planet->surf_temp		= 0;
		planet->high_temp		= 0;
		planet->low_temp		= 0;
		planet->max_temp		= 0;
		planet->min_temp		= 0;
		planet->greenhs_rise	= 0;
		planet->planet_no		= planet_no;
		planet->sun				= sun;
		planet->resonant_period = FALSE;

		planet->orbit_zone 		= orb_zone(sun->luminosity, planet->a);
		if (planet->imf == 0 && planet->rmf == 0)
		{
		  if (planet->orbit_zone == 1)
		  {
		    planet->imf = 0.0;
		    planet->rmf = random_number(0.0, 1.0);
		  }
		  else if (planet->orbit_zone == 2)
		  {
		    planet->imf = random_number(0.0, 0.5);
		    planet->rmf = random_number(0.0, 1.0 - planet->imf);
		  }
		  else
		  {
		    planet->imf = random_number(0.0, 1.0);
		    planet->rmf = 0.0;
		  }
		}
		if (planet->imf < 0.0)
		{
		  planet->imf *= -1.0;
		}
		else if (planet->imf > 1)
		{
		  planet->imf = 1.0;
		}
		if (planet->rmf < 0.0)
		{
		  planet->rmf *= -1.0;
		}
		else if (planet->rmf > 1.0)
		{
		  planet->rmf = 1.0;
		}

		if (!is_moon)
		{
		  planet->orb_period		= period(planet->a,planet->mass,parent_mass);
		  if (random_tilt || planet->axial_tilt == 0)
		  {
		    planet->axial_tilt 	= inclination(planet->a, parent_mass);
		  }
		}
		else
		{
		  planet->orb_period		= period(planet->moon_a,planet->mass,parent_mass);
		  if (random_tilt || planet->axial_tilt == 0)
		  {
		    planet->axial_tilt 	= inclination(planet->moon_a, parent_mass);
		  }
		}
		planet->exospheric_temp = EARTH_EXOSPHERE_TEMP / pow2(planet->a / sun->r_ecosphere);
		planet->rms_velocity 	= rms_vel(MOL_NITROGEN,planet->exospheric_temp);
		//planet->core_radius 	= kothari_radius(planet->dust_mass,FALSE,planet->orbit_zone);
		planet->core_radius = radius_improved(planet->dust_mass, (long double)planet->imf, (long double)planet->rmf, FALSE, planet->orbit_zone);

		// Calculate the radius as a gas giant, to verify it will retain gas.
		// Then if mass > Earth, it's at least 5% gas and retains He, it's
		// some flavor of gas giant.
		
		planet->density 		= empirical_density(planet->mass,planet->a, sun->r_ecosphere, TRUE);
		planet->radius 			= volume_radius(planet->mass,planet->density);
		//planet->radius = gas_radius(planet->a, planet->dust_mass, planet->mass, sun->age);
		//planet->density = volume_density(planet->mass,planet->radius);
		
		planet->surf_accel   	= acceleration(planet->mass,planet->radius);
		planet->surf_grav 	 	= gravity(planet->surf_accel);

		planet->molec_weight	= min_molec_weight(planet);

		// seb jup = 317.83 earth masses
		// 6xJup = star
		// arbitrarily 4xJup = BrownDwarf = 1271.32 --> 1200

		int force_gas_giant = FALSE;
		if ((planet->gas_mass / planet->mass) > 0.05 && (planet->mass * SUN_MASS_IN_EARTH_MASSES) > 10.0)
		{
		  force_gas_giant = TRUE;
		}
		//if (((planet->mass * SUN_MASS_IN_EARTH_MASSES) > 1.0) && ((planet->gas_mass / planet->mass) > 0.05) && (min_molec_weight(planet) <= 4.0))
		if ((((planet->mass * SUN_MASS_IN_EARTH_MASSES) > 1.0) && ((planet->gas_mass / planet->mass) > 0.05) && (min_molec_weight(planet) <= 4.0)) || (planet->gas_mass && planet->a < 0.8) || force_gas_giant == TRUE)
		{
			//printf("test %d\n", planet->planet_no);
			if ((planet->gas_mass / planet->mass) < 0.20)
				planet->type = tSubSubGasGiant;
			else if ((planet->mass * SUN_MASS_IN_EARTH_MASSES) < 20.0)
				planet->type = tSubGasGiant;
			else if ((planet->mass * SUN_MASS_IN_EARTH_MASSES) > 1200.0) //seb
			        planet->type = tBrownDwarf;  //seb
			else
				planet->type = tGasGiant;
		}
		else // If not, it's rocky.
		{
			//planet->radius 		= kothari_radius(planet->mass,FALSE,planet->orbit_zone);
			planet->radius		= radius_improved(planet->mass, (long double)planet->imf, (long double)planet->rmf, FALSE, planet->orbit_zone);
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
					fprintf (stderr, "%s\tLosing gas: H2: %5.3Lf EM, He: %5.3Lf EM\n",
							 planet_id,
							 h2_loss * SUN_MASS_IN_EARTH_MASSES, he_loss * SUN_MASS_IN_EARTH_MASSES);
			}
		}
/*
		//seb: recalculate planet radius for largest categories
		// formulae taken from Fig 4 in Fortney et al. (2009)
		// Rjup = 71492.0 km

		tmp = (planet->mass * SUN_MASS_IN_EARTH_MASSES)/317.82; // mass as frac of Mj
		if ( ((planet->type == tGasGiant) || (planet->type == tBrownDwarf)) && (tmp >0.22) )
		{ if (tmp < 1.65) { planet->radius = ( pow(tmp,0.1)*71492.0); }         // planet
		    else if (tmp < 6.04) { planet->radius = ( pow(tmp,-0.125)*71492.0); } // brown dwarf
		    else { planet->radius = ( 0.799*71492.0 + (tmp-6.04)*71492.0); }      // star
		  // omega13a's version (old)
		  if (tmp < 10) { planet->radius = ( pow(tmp,0.1)*71492.0); }         // planet
		  //else if (tmp < 75) { planet->radius = ( pow(tmp,-0.125)*71492.0); } // brown dwarf
		  else if (tmp >= 75) { planet->radius = ( 0.799*71492.0 + (tmp-6.04)*71492.0); }      // star
		  planet->density = volume_density(planet->mass,planet->radius);
		}
		// recalculate planet radius for realy hot neptunians and jovians (not very scientific. don't take seriously)
		long double hot_limit = sqrt(sun->luminosity * 0.49);
		if ((planet->type == tSubSubGasGiant || planet->type == tSubGasGiant || planet->type == tGasGiant || planet->type == tBrownDwarf) && planet->a < hot_limit)
		{
		  long double tmp2, tmp_density, dist_from_hot_limit, factor;
		  tmp = planet->radius - planet->core_radius;
		  tmp_density = volume_density(planet->gas_mass, tmp);
		  dist_from_hot_limit = hot_limit - planet->a;
		  factor = dist_from_hot_limit / planet->a;
		  tmp_density = tmp_density / factor;
		  tmp2 = volume_radius(planet->gas_mass, tmp_density);
		  planet->radius -= tmp;
		  planet->radius += tmp2;
		  planet->density = volume_density(planet->mass, planet->radius);
		  if (planet->density < 0.25)
		  {
		    planet->density = about(0.25, 0.01);
		    planet->radius = volume_radius(planet->mass, planet->density);
		  }
		}*/

		planet->day = day_length(planet, parent_mass, is_moon);	/* Modifies planet->resonant_period */
		// seb: tidally locked by definition has 0 tilt
		/*if ((int)planet->day == (int)(planet->orb_period * 24.0))
		  {
		    planet->axial_tilt = 0.0;
		  }*/

		planet->esc_velocity 	= escape_vel(planet->mass,planet->radius);

		if ((planet->type == tGasGiant)
		    || (planet->type == tBrownDwarf) //seb
		 || (planet->type == tSubGasGiant) 
		 || (planet->type == tSubSubGasGiant))
		{
			planet->greenhouse_effect 		= FALSE;
			planet->volatile_gas_inventory 	= INCREDIBLY_LARGE_NUMBER;
			planet->surf_pressure 			= INCREDIBLY_LARGE_NUMBER;
			
			planet->boil_point 				= INCREDIBLY_LARGE_NUMBER;
			
			//seb need temp for surface texture (compare to est.temp)
			// planet->surf_temp				= INCREDIBLY_LARGE_NUMBER;
			planet->greenhs_rise 			= 0;
			//planet->albedo 					= about(GAS_GIANT_ALBEDO,0.1);
			if (planet->a < sqrt(sun->luminosity * 0.0001))
			  planet->albedo = about(CLASS_V_ALBEDO, 0.1);
			else if (planet->a < sqrt(sun->luminosity * 0.09))
			  planet->albedo = about(CLASS_IV_ALBEDO, 0.1);
			else if (planet->a < sqrt(sun->luminosity * 0.49))
			  planet->albedo = about(CLASS_III_ALBEDO, 0.1);
			else if (planet->a < sqrt(sun->luminosity * 9))
			  planet->albedo = about(CLASS_II_ALBEDO, 0.1);
			else
			  planet->albedo = about(CLASS_I_ALBEDO, 0.1);
			planet->hydrosphere 			= 1.0;
			planet->cloud_cover	 			= 1.0;
			planet->ice_cover	 			= 0.0;
			planet->surf_grav			 	= gravity(planet->surf_accel);
			if (force_gas_giant == TRUE)
			{
			  planet->molec_weight = about(0.5, 0.1);
			}
			else
			{
			  planet->molec_weight			= min_molec_weight(planet);
			}
 			//planet->estimated_temp			= est_temp(sun->r_ecosphere, planet->a,  planet->albedo);
			long double temp1, temp2, new_albedo;
			temp1 = est_temp(sun->r_ecosphere, planet->a,  planet->albedo);
			while (TRUE)
			{
			  if (temp1 > 1400)
			    new_albedo = about(CLASS_V_ALBEDO, 0.1);
			  else if (temp1 > 900)
			    new_albedo = about(CLASS_IV_ALBEDO, 0.1);
			  else if (temp1 > 350)
			    new_albedo = about(CLASS_III_ALBEDO, 0.1);
			  else if (temp1 > 150)
			    new_albedo = about(CLASS_II_ALBEDO, 0.1);
			  else
			    new_albedo = about(CLASS_I_ALBEDO, 0.1);
			  planet->albedo = (new_albedo + (planet->albedo * 2)) / 3;
			  temp2 = est_temp(sun->r_ecosphere, planet->a,  planet->albedo);
			  temp1 = (temp2 + (temp1 * 2)) / 3;
			  if ((temp1 - temp2) < 0.25)
			    break;
			}
			planet->estimated_temp = temp1;
			
			if (planet->type == tSubSubGasGiant || planet->type == tSubGasGiant)
			{
			  planet->radius = gas_dwarf_radius(planet, sun);
			}
			else
			{
			  planet->radius = gas_radius(planet->estimated_temp, planet->dust_mass, planet->mass, sun->age, planet);
			}
			planet->density = volume_density(planet->mass, planet->radius);
			
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
						fprintf (stderr, "%s\t%s (%4.2LfEM %5.3Lf By)%s with earth-like temperature (%.1Lf C, %.1Lf F, %+.1Lf C Earth).\n",
								 planet_id,
							         planet->type == tBrownDwarf ? "Brown Dwarf" : //seb
								 planet->type == tGasGiant ? "Jovian" :
								 planet->type == tSubGasGiant ? "Sub-Jovian" :
								 planet->type == tSubSubGasGiant ? "Gas Dwarf" :
								 "Big",
								 planet->mass * SUN_MASS_IN_EARTH_MASSES,
								 sun->age /1.0E9,
								 planet->first_moon == NULL ? "" : " WITH MOON",
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
			if (strcmp(sun->name, "RU G0V 90004-C") == 0 && planet->planet_no == 1)
			{
			    //planet->volatile_gas_inventory = about(1000, 0.7);
			    planet->volatile_gas_inventory = 1000;
			}
			if (planet->a == 0.131833228 && strcmp(sun->name, "RU M0V 30014") == 0)
			  planet->volatile_gas_inventory = 1000;
			if (planet->gas_giant || (planet->gas_mass / planet->mass) > 0.000001)
			{
			  planet->surf_pressure = pressure(planet->volatile_gas_inventory, planet->core_radius, planet->surf_grav);
			  planet->surf_pressure = planet->surf_pressure + get_accreated_gas_pressure(planet);
			}
			else
			{
			  planet->surf_pressure = pressure(planet->volatile_gas_inventory, planet->radius, planet->surf_grav);
			}
			
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

			//seb: always want atmospheric composition, especially for cold planets
			    //&&
			    //				(planet->max_temp >= FREEZING_POINT_OF_WATER) &&
			    //				(planet->min_temp <= planet->boil_point))
			if (do_gases 
			    && planet->surf_pressure > 0.05) //seb: but only if there's some air
				calculate_gases(sun, planet, planet_id);
			
			/*
			 *	Next we assign a type to the planet.
			 */
			 if (!planet->type)
			 {
			if (planet->surf_pressure < 1.0)
			{
				if (!is_moon
				 && ((planet->mass * SUN_MASS_IN_EARTH_MASSES) < ASTEROID_MASS_LIMIT))
				  {
					planet->type 			= tAsteroids;
				  }
				else
					planet->type 			= tRock;
			}
			else if ((planet->surf_pressure > 6000.0) && (planet->molec_weight <= 2.0) && planet->gas_giant && planet->ice_cover == 0 && planet->hydrosphere == 0)	// Retains Hydrogen
			{
				planet->type = tSubSubGasGiant;
				//seb: want gas damit				planet->gases = 0;
				//				free(planet->atmosphere);
				//				planet->atmosphere = NULL;
			}
			else 
			{										// Atmospheres:
				if (((int)planet->day == (int)(planet->orb_period * 24.0) || (planet->resonant_period)) && planet->moon_a == 0)
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
						fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%s\t Unknown %s\n", 
							 type_string (planet->type),
							 planet->surf_pressure,
							 planet->mass * SUN_MASS_IN_EARTH_MASSES,
							 planet->surf_grav,
							 planet->surf_temp  - EARTH_AVERAGE_KELVIN,
							 planet_id,
							 ((int)planet->day == (int)(planet->orb_period * 24.0) || 
							  (planet->resonant_period)) ? "(1-Face)" : ""
							 );
				}
			}
		}
		}

		if (do_moons && !is_moon)
		{
		  if (strcmp(sun->name, "RU M0V 30014") == 0)
		  {
		    if (planet->a == 0.131833228 && planet->first_moon == NULL)
		    {
		      planet_pointer	the_moon = (planets *)malloc(sizeof(planets));
		      the_moon->moon_a = 0.000356288186;
		      the_moon->moon_e = 0.0001;
		      the_moon->type 			= tUnknown;
	/*	      the_moon->a 			= a; */
	/*	      the_moon->e 			= e; */
		      the_moon->mass 			= EM(.99);
		      the_moon->dust_mass 	= EM(.99);
		      the_moon->gas_mass 		= 0;
		      the_moon->atmosphere 	= NULL;
		      the_moon->next_planet 	= NULL;
		      the_moon->first_moon 	= NULL;
		      the_moon->gas_giant 	= FALSE;
		      the_moon->atmosphere	= NULL;
		      the_moon->albedo		= 0;
		      the_moon->gases			= 0;
		      the_moon->surf_temp		= 0;
		      the_moon->high_temp		= 0;
		      the_moon->low_temp		= 0;
		      the_moon->max_temp		= 0;
		      the_moon->min_temp		= 0;
		      the_moon->greenhs_rise	= 0;
		      the_moon->minor_moons 	= 0;
		      planet->first_moon = the_moon;
		    }
		  }
		  long double moon_mass;
			if (planet->first_moon != NULL)
			{
				int 			n;
				planet_pointer	ptr;

				for (n=0, ptr=planet->first_moon;
					 ptr != NULL;
					 ptr=ptr->next_planet)
				{
					moon_mass += ptr->mass;
					if ((ptr->mass * SUN_MASS_IN_EARTH_MASSES) > .000001)
					{
						char	moon_id[80];
						long double	roche_limit = 0.0;
						long double	hill_sphere = 0.0;
						
						ptr->a = planet->a;
						ptr->e = planet->e;
						ptr->imf = planet->imf;
						ptr->rmf = planet->rmf;
						ptr->orbit_zone = planet->orbit_zone;
						n++;
						
						sprintf(moon_id,
								"%s.%d",
								planet_id, n);
						
						generate_planet(ptr, n,
								sun, random_tilt, 
								moon_id,
								do_gases, 
								do_moons, TRUE, planet->mass);	// Adjusts ptr->density
						
						//if (ptr->moon_a == 0)
						{
						roche_limit = 2.44 * planet->radius * pow((planet->density / ptr->density), (1.0 / 3.0));
						hill_sphere = planet->a * KM_PER_AU * pow((planet->mass / (3.0 * sun->mass)), (1.0 / 3.0));
						
						if ((roche_limit * 3.0) < hill_sphere)
						{
							ptr->moon_a = random_number(roche_limit * 1.5, hill_sphere / 2.0) / KM_PER_AU;
							ptr->moon_e = random_eccentricity (ecc_coef);
						}
						else
						{
							ptr->moon_a = 0;
							ptr->moon_e = 0;
						}
						ptr->orb_period = period(ptr->moon_a, ptr->mass, planet->mass);
						ptr->type = tUnknown;
						generate_planet(ptr, n,
								sun, random_tilt, 
								moon_id,
								do_gases, 
								do_moons, TRUE, planet->mass);	// Adjusts ptr->density
						}
						if (flag_verbose & 0x40000)
						{
							fprintf (stderr, 
								 "   Roche limit: R = %4.2Lg, rM = %4.2Lg, rm = %4.2Lg -> %.0Lf km\n"
								 "   Hill Sphere: a = %4.2Lg, m = %4.2Lg, M = %4.2Lg -> %.0Lf km\n"
								 "%s Moon orbit: a = %.0Lf km, e = %.0Lg\n",
								 planet->radius, planet->density, ptr->density,
								 roche_limit,
								 planet->a * KM_PER_AU, planet->mass * SOLAR_MASS_IN_KILOGRAMS, sun->mass * SOLAR_MASS_IN_KILOGRAMS,
								 hill_sphere,
								 moon_id,
								 ptr->moon_a * KM_PER_AU, ptr->moon_e
								 );
						}
						
						if (flag_verbose & 0x1000)
						{
							fprintf (stderr, "  %s: (%7.2LfEM) %d %4.2LgEM\n",	
								planet_id,
								planet->mass * SUN_MASS_IN_EARTH_MASSES,
								n,
								ptr->mass * SUN_MASS_IN_EARTH_MASSES);
						}
					}
				}
			}
			
			tmp = Poisson((planet->mass + moon_mass ) * SUN_MASS_IN_EARTH_MASSES/30.0);
			
		}

}

void check_planet(planet_pointer	planet,
	      	  char*				planet_id,
		  int				is_moon)
{
	{
		int tIndex = 0;
	
		switch (planet->type)
		{
			case tUnknown:			tIndex = 0;		break;
			case tRock:			tIndex = 1;		break;
			case tVenusian:			tIndex = 2;		break;
			case tTerrestrial:		tIndex = 3;		break;
	        	case tSubSubGasGiant:	        tIndex = 4;		break;
			case tSubGasGiant:		tIndex = 5;		break;
			case tGasGiant:			tIndex = 6;		break;
			case tMartian:			tIndex = 7;		break;
			case tWater:			tIndex = 8;		break;
			case tIce:			tIndex = 9;		break;
			case tAsteroids: 		tIndex = 10;	break;
			case t1Face:			tIndex = 11;	break;
		        case tBrownDwarf:		tIndex = 12;	break; //seb
		}
		
		if (type_counts[tIndex] == 0)
			++type_count;
		
		++type_counts[tIndex];
		
	}
	
	/* Check for and list planets with breathable atmospheres */
	
	{
		unsigned int breathe = breathability (planet);
		
		if ((breathe == BREATHABLE) &&
			((!planet->resonant_period &&		// Option needed?
			(int)planet->day != (int)(planet->orb_period * 24.0)) || is_moon))
		{
			int	list_it	= FALSE;
			long double illumination = pow2 (1.0 / planet->a) 
										* (planet->sun)->luminosity;
			
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
			
			if (min_breathable_l > illumination)
			{
				min_breathable_l = illumination;

				if (flag_verbose & 0x0002)
					list_it = TRUE;
			}
			
			if (max_breathable_l < illumination)
			{
				max_breathable_l = illumination;

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

				if (min_breathable_terrestrial_l > illumination)
				{
					min_breathable_terrestrial_l = illumination;

					if (flag_verbose & 0x0002)
						list_it = TRUE;
				}

				if (max_breathable_terrestrial_l < illumination)
				{
					max_breathable_terrestrial_l = illumination;

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
			fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\tl=%4.2Lf\t%s\n", 
						type_string (planet->type),
						planet->surf_pressure,
						planet->mass * SUN_MASS_IN_EARTH_MASSES,
						planet->surf_grav,
						planet->surf_temp  - EARTH_AVERAGE_KELVIN,
						illumination,
						planet_id);
		}
	}

	if (is_moon
	 && max_moon_mass < planet->mass)
	{
		max_moon_mass = planet->mass;

		if (flag_verbose & 0x0002)
			fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%s Moon Mass\n", 
					type_string (planet->type),
					planet->surf_pressure,
					planet->mass * SUN_MASS_IN_EARTH_MASSES,
					planet->surf_grav,
					planet->surf_temp  - EARTH_AVERAGE_KELVIN,
					planet_id);
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
			fprintf (stderr, "%12s\tp=%4.2Lf\tr=%4.2Lf\tm=%4.2Lf\t%s\t%d\n", 
					type_string (planet->type),
					planet->core_radius,
					planet->radius,
					planet->mass * SUN_MASS_IN_EARTH_MASSES,
					planet_id,
					50-core_size);
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
			(planet->max_temp < planet->boil_point) &&
			(breathe    == BREATHABLE))
		{
			earthlike++;

			if (flag_verbose & 0x0008)
				fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%d %s\tEarth-like\n", 
								type_string (planet->type),
								planet->surf_pressure,
								planet->mass * SUN_MASS_IN_EARTH_MASSES,
								planet->surf_grav,
								planet->surf_temp  - EARTH_AVERAGE_KELVIN,
								habitable,
								planet_id);
		} else if ((flag_verbose & 0x0008) &&
				 (breathe   == BREATHABLE) &&
				 (gravity	 > 1.3) &&
				 (habitable	 > 1) &&
				 ((rel_temp  < -2.0) ||
				  (ice		 > 10.))
				)
		{
			fprintf (stderr, "%12s\tp=%4.2Lf\tm=%4.2Lf\tg=%4.2Lf\tt=%+.1Lf\t%s\tSphinx-like\n", 
					type_string (planet->type),
					planet->surf_pressure,
					planet->mass * SUN_MASS_IN_EARTH_MASSES,
					planet->surf_grav,
					planet->surf_temp  - EARTH_AVERAGE_KELVIN,
					planet_id);
		}
	}
}

void generate_planets(sun*			sun,
					  int 			random_tilt, 
					  char			flag_char,
					  int			sys_no,
					  char*			system_name,
					  int			do_gases,
					  int			do_moons)
{
	planet_pointer	planet;
	int				planet_no = 0;
	planet_pointer 	moon;
	int 			moons = 0; 

	for (planet = innermost_planet, planet_no = 1; 
		 planet != NULL; 
		 planet = planet->next_planet, planet_no++)
	{
		char	planet_id[80];
		
		sprintf(planet_id, "%s (-s%ld -%c%d) %d", system_name, flag_seed, flag_char, sys_no, planet_no);
		planet->imf = 0.0;
		planet->rmf = 0.0;
				
		generate_planet(planet, planet_no,
						sun, random_tilt, 
						planet_id,
						do_gases, do_moons, FALSE, sun->mass);
		
		/*
		 *	Now we're ready to test for habitable planets,
		 *	so we can count and log them and such
		 */
		 
		 check_planet(planet, planet_id, FALSE);
						
		for (moon=planet->first_moon, moons=1;
			moon != NULL;
			moon=moon->next_planet, moons++)
		{
			char	moon_id[80];
			
			sprintf(moon_id,
					"%s.%d",
					planet_id, moons);
			check_planet(moon, moon_id, TRUE);
		}
	}
}

/*
 *  Sort a ChemTable by decreasing abundance.
 */

static int diminishing_abundance(const void *xp, const void *yp)
{
	const ChemTable *x = (ChemTable *) xp;
	const ChemTable *y = (ChemTable *) yp;
	long double    xx = x->abunds * x->abunde;
	long double    yy = y->abunds * y->abunde;

	if (xx < yy)
		return +1;
	return (xx > yy ? -1 : 0);
}

/*
 *  Sort a ChemTable by decreasing pressure.
 */

static int diminishing_pressure(const void *xp, const void *yp)
{
	const gas *x = (gas *) xp;
	const gas *y = (gas *) yp;

	if (x->surf_pressure < y->surf_pressure)
		return +1;
	return (x->surf_pressure > y->surf_pressure ? -1 : 0);
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
			 long double    luminosity_arg,
			 long			seed_arg,
			 int			count_arg,
			 int			incr_arg,
			 catalog *		cat_arg,
			 int			sys_no_arg,
			 
			 long double	ratio_arg,
			 long double	ecc_coef_arg,
                         long double	inner_planet_factor_arg,
			 
			 int			flags_arg,
			 int			out_format,
			 int			graphic_format
			 )
{
	sun				sun					= {0.0, 0.0, 0.0, 0.0, 0.0, ""};
	long double		min_mass 			= 0.4;
	long double		inc_mass 			= 0.05;
	long double		max_mass 			= 2.35;
	long double             sys_inc                         = 0.0; //seb
	long double             sys_an                          = 0.0; //seb
	int				system_count		= 1;
	int				seed_increment		= 1;
	
	char			default_path[]		= SUBDIR;			/* OS specific */
	char 			default_url_path[]	= "../";
	char 			*url_path			= default_url_path;
	char			thumbnail_file[300]	= "Thumbnails";
	char 			file_name[300]		= "StarGen";
	char			subdir[300]			= "";
	char			csv_file_name[300]	= "StarGen.csv";

	FILE 			*html_file			= NULL;
	FILE 			*thumbnails			= NULL; 
	FILE			*csv_file			= NULL;

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
	int				only_three_habitable= (flags_arg & fOnlyThreeHabitable) != 0;
	int				only_jovian_habitable=(flags_arg & fOnlyJovianHabitable) != 0;
	int				only_earthlike		= (flags_arg & fOnlyEarthlike) != 0;

	if (do_catalog)
		catalog_count = cat_arg->count;

	if (only_habitable && only_multi_habitable)
		only_habitable = FALSE;

	if (only_habitable && only_earthlike)
		only_habitable = FALSE;
	
	if (only_three_habitable)
	{
	  only_habitable = FALSE;
	  only_earthlike = FALSE;
	  only_multi_habitable = FALSE;
	}

	if (sgErr == NULL)
		sgErr = stderr;
	
	if ((prognam == NULL) || (prognam[0] == '\0'))
		prognam = "StarGen";

	if ((path == NULL) || (path[0] == '\0'))
		path 		= default_path;
	
	if (graphic_format == 0)
		graphic_format = gfGIF;
	
	if ((url_path_arg != NULL) && (url_path_arg[0] != '\0'))
		url_path	= url_path_arg;

	{									// Find the last sub-dir in the path:
		size_t	l = strlen(DIRSEP);
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
			  //seb: note if any planets defined
			  char* pl = "  ";
			  int bodies = 0;
			  bodies = (*(cat_arg->stars))[index].in_celestia;
			  if (bodies != 0 ) pl = "+P";
			  
			  fprintf (sgOut, "%3d: %-30.30s %-2.2s M: %4.2LG L: %4.2LG\n",
				   index,
				   (*(cat_arg->stars))[index].name,
				   pl,
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
			long double	tempE = est_temp(1.0,  1.0,  EARTH_ALBEDO);
			long double	tempJ = est_temp(1.0,  5.2034,  GAS_GIANT_ALBEDO);
			long double	tempS = est_temp(1.0,  9.5371,  GAS_GIANT_ALBEDO);
			long double	tempU = est_temp(1.0, 19.1913,  GAS_GIANT_ALBEDO);
			long double	tempN = est_temp(1.0, 30.0690,  GAS_GIANT_ALBEDO);
			
			if (sgOut == NULL)
				sgOut = stdout;
			
			fprintf (sgOut, "Size of float: %d\n",
					 sizeof(float));
			fprintf (sgOut, "Size of doubles: %d\n",
					 sizeof(double));
			fprintf (sgOut, "Size of long doubles: %d\n\n",
					 sizeof(long double));
			fprintf (sgOut, "Earth Eff Temp: %5.1Lf K, %5.1Lf C, Earth rel: %5.1Lf C\n\n",
					 tempE,
					 tempE - FREEZING_POINT_OF_WATER,
					 tempE - EARTH_AVERAGE_KELVIN);
			fprintf (sgOut, "Jupiter Eff Temp: %5.1Lf K\n", tempJ);
			fprintf (sgOut, "Saturn  Eff Temp: %5.1Lf K\n", tempS);
			fprintf (sgOut, "Uranus  Eff Temp: %5.1Lf K\n", tempU);
			fprintf (sgOut, "Neptune Eff Temp: %5.1Lf K\n", tempN);

			return (1);
		}
		
		case aListVerbosity:
			if (sgOut == NULL)
				sgOut = stdout;
			fprintf(sgOut,"Stargen %s\n", stargen_revision);
			
			fprintf (sgOut, 
					"Verbosity flags are hexidecimal numbers:\n"
					"\t0001\tEarthlike count\n"
					"\t0002\tTrace Min/Max\n"
					"\t0004\tList Habitable\n"
				        "\t0008\tList Earthlike & Sphinxlike\n"
					"\t\n"
					"\t0010\tList Gases\n"
					"\t0020\tTrace temp iterations\n"
					"\t0040\tGas lifetimes\n"
					"\t0080\tList loss of accreted gas mass\n"
					"\t\n"
					"\t0100\tInjecting, collision\n"
					"\t0200\tChecking..., Failed...\n"
					"\t0400\tList binary info\n"
					"\t0800\tList accreted atmospheres\n"
					"\t\n"
					"\t1000\tMoons (experimental)\n"
					"\t2000\tOxygen poisoned (experimental)\n"
					"\t4000\tTrace gas percentages\n"
					"\t8000\tList Jovians in the ecosphere\n"
					"\t\n"
					"\t10000\tList type diversity\n"
					"\t20000\tTrace Surface temp interations\n"
					);
			return (1);
		case aGenerate:
		
			break;
	}

	flag_seed		= seed_arg;
	sun.mass 		= mass_arg;
	sun.luminosity		= luminosity_arg;
	if (sun.mass == 0.0 && sun.luminosity != 0.0)
	{
		sun.mass = luminosity_to_mass(sun.luminosity);
	}
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
	
	if ((system_count > 1)
	 && !(out_format == ffCSVdl))
	{
		if (strlen(filename_arg) > 0)
			strcpy(thumbnail_file, filename_arg);
		
		thumbnails = open_html_file ("Thumbnails", flag_seed, path, url_path, thumbnail_file, ".html",
									 prognam, sgOut);
		if (thumbnails == NULL)
		{
			fprintf(sgErr, "Could not open file %s%s\n",
					path, thumbnail_file);
			exit(0);
		}
	}
	
	if ((out_format == ffCSV) || (out_format == ffCSVdl))
	{
		char	csv_url[300]	= "";

		if ((sgOut != NULL))
		{
			char sys_no[10] = "x";
			
			if (!do_catalog)
				sprintf(&sys_no[0], "%d", sys_no_arg-1);
			
			if (out_format == ffCSVdl)
				csv_file = sgOut;

			sprintf (&csv_url[0],
					 "/cgi-bin/StarGen.pl?Catalog=%s&Dole=%s&SolStation=%s&Mass=%LG&Output=%s&Seed=%ld&Count=%d&Incr=%d&Gas=%s&Moon=%s&SVG=%s&DoIt=CSV",
					 (cat_arg == NULL) ? "none" : cat_arg->arg,
					 sys_no,
					 sys_no,
					 sun.mass,
					 (only_earthlike) ? "E"
					 : (only_multi_habitable) ? "2"
					 : (only_habitable) ? "H"
					 : "all",
					 flag_seed,
					 count_arg,
					 incr_arg,
					 (do_gases)					? "on" : "off",	// one of ("on", "off")
					 (do_moons)					? "on" : "off",	// one of ("on", "off")
					 (graphic_format == gfSVG)	? "on" : "off"	// one of ("on", "off")
					);
		}
		else
		{
			char cleaned_arg[300] = "StarGen";
			
			if (strlen(filename_arg) > 0)
			{
				char *ptr;
				
				strcpy (cleaned_arg, filename_arg);
				
				ptr = strrchr(cleaned_arg, '.');
				
				if ((ptr != NULL)
				 && (strcmp(ptr, ".html") == 0))
					*ptr = '\0';
			}
			
			if (thumbnails != NULL)
			{
				sprintf (&csv_file_name[0], 
						 "%s-%ld.csv", 
						 cleaned_arg,
						 flag_seed);
			}
			else
			{
				sprintf (&csv_file_name[0], 
						 "%s.csv", 
						 cleaned_arg);
			}

			sprintf (&csv_url[0],
					 "%s%s%s",
					 url_path,
					 subdir,
					 csv_file_name);

			csv_file = open_csv_file (path, csv_file_name);
		}

		if ((csv_file == NULL) && 
			!((out_format == ffCSV) && (sgOut != NULL)))
		{
			fprintf(sgErr, "Could not open file %s%s\n",
				path, csv_file_name);
			exit(0);
		}
	
		if (thumbnails != NULL)
			csv_thumbnails(thumbnails, url_path, subdir, csv_file_name, csv_url);
	}
	
	for (index = 0; index < system_count; index++)
	{
		char			system_name[80];
		char			designation[80];
		char			*cp;
		long double		outer_limit			= 0.0;
		long double		inner_dust_limit		= 0.0; // seb
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

			//seb use orbital inclination from catalog entry
			sys_inc =  (*(cat_arg->stars))[sys_no].inc;  // seb
			sys_an  =  (*(cat_arg->stars))[sys_no].an ;  //seb

			if ((*(cat_arg->stars))[sys_no].known_planets != NULL)
				has_known_planets = TRUE;

			if ((use_known_planets || no_generate) && has_known_planets) //seb: no point if no planets
			{

			  seed_planets = (*(cat_arg->stars))[sys_no].known_planets;
			  use_seed_system	= no_generate;
			  //				if (no_generate) use_seed_system	= no_generate;
			  //				else use_seed_system = TRUE;

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
			
			sprintf (&file_name[0], "%s-%ld", designation, flag_seed);


			// seb: use a as approximate inner limit for planetary formation
			// if no second star mass has been specified
			// e.g. as inner stable orbit of a double star system
			// it's up to the person defining the star system
			// to set it to an appropriate value

			if ((*(cat_arg->stars))[sys_no].m2 == 0)
			{
			  inner_dust_limit = (*(cat_arg->stars))[sys_no].a;
			}
			else
			{
			  inner_dust_limit = 0.0;
			}

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
			sprintf (&file_name[0], "Earth-M%LG", earth.mass * SUN_MASS_IN_EARTH_MASSES);

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
			
			sprintf (&file_name[0], "%s-%ld-%LG", designation, flag_seed, sun.mass);
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
		
		earthlike			 = 0;
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
					inner_dust_limit, // seb
					outer_limit,
					ecc_coef_arg, //seb
					inner_planet_factor_arg, //seb
					do_gases,
					do_moons);

{
		 planet_pointer	planet;
		 int 			counter; 
		 int				wt_type_count = type_count;
		 int				norm_type_count = 0;
		 
		 if (type_counts[3]  > 0)	wt_type_count += 20;	// Terrestrial
		 if (type_counts[8]  > 0)	wt_type_count += 18;	// Water
		 if (type_counts[2]  > 0)	wt_type_count += 16;	// Venusian
		 if (type_counts[7]  > 0)	wt_type_count += 15;	// Martian
		 if (type_counts[9]  > 0)	wt_type_count += 14;	// Ice
		 if (type_counts[10] > 0)	wt_type_count += 13;	// Asteroids
		 if (type_counts[4]  > 0)	wt_type_count += 12;	// Gas Dwarf
		 if (type_counts[5]  > 0)	wt_type_count += 11;	// Sub_Jovian
		 if (type_counts[11] > 0)	wt_type_count += 10;	// 1-Face
		 if (type_counts[1]  > 0)	wt_type_count += 3;		// Rock
		 if (type_counts[6]  > 0)	wt_type_count += 2;		// Jovian
		 if (type_counts[0]  > 0)	wt_type_count += 1;		// Unknown
		 
		 for (planet=innermost_planet, counter=0;
		      planet != NULL;
		      planet=planet->next_planet, counter++) ;
		 
		 norm_type_count = wt_type_count - (counter - type_count);
		 
		 if (max_type_count < norm_type_count)
		   {
		     max_type_count = norm_type_count;
		 
		   }
		 // seb: when want type diversity info, want it for all systems, not just some.
		 if (flag_verbose & 0x10000)
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

		total_habitable += habitable;
		total_earthlike += earthlike;

		if ((!(only_habitable || only_multi_habitable || only_jovian_habitable || only_earthlike || only_three_habitable))
		 || (only_habitable && (habitable > 0) && !only_jovian_habitable)
		 || (only_habitable && only_jovian_habitable && habitable > 0 && habitable_jovians > 0) // added by omega13a (Jun 27, 2012)
		 || (only_multi_habitable && (habitable > 1) && !only_jovian_habitable)
		 || (only_multi_habitable && only_jovian_habitable && habitable > 1 && habitable_jovians > 0) // added by omega13a (Jun 27, 2012)
		 || (only_earthlike && (earthlike > 0) && !only_jovian_habitable)
		 || (only_earthlike && only_jovian_habitable && earthlike > 0 && habitable_jovians > 0) // added by omega13a (Jun 27, 2012)
		 || (only_jovian_habitable && (habitable_jovians > 0) && !(only_earthlike || only_multi_habitable || only_habitable)) 
		 || (only_three_habitable && (habitable > 2))
		 )
		{
			char	system_url[300] = "";
			char	svg_url[300]	= "";
			
			if (sgOut == NULL)
			{
				sprintf (system_url,
						 "%s%s%s%s",
						 url_path,
						 subdir,
						 file_name,
						 ".html");

				sprintf (svg_url,
						 "%s%s%s%s",
						 url_path,
						 subdir,
						 file_name,
						 ".svg");
			}
			else if (use_solar_system && sys_no == 0)
			{
				sprintf (system_url,
						 "/cgi-bin/StarGen.pl?Catalog=x&Output=all&Seed=%ld&Count=1&Incr=1&Gas=%s&Moon=%s&SVG=%s",
						 flag_seed,
						 (do_gases)					? "on" : "off",	// one of ("on", "off")
						 (do_moons)					? "on" : "off",	// one of ("on", "off")
						 (graphic_format == gfSVG)	? "on" : "off"	// one of ("on", "off")
						);

				sprintf (svg_url,
						 "/cgi-bin/StarGen.pl?Catalog=x&Output=all&Seed=%ld&Count=1&Incr=1&Gas=%s&Moon=%s&SVG=%s&DoIt=SVG",
						 flag_seed,
						 (do_gases)					? "on" : "off",	// one of ("on", "off")
						 (do_moons)					? "on" : "off",	// one of ("on", "off")
						 (graphic_format == gfSVG)	? "on" : "off"	// one of ("on", "off")
						);
			}
			else
			{

				sprintf (system_url,
						 "/cgi-bin/StarGen.pl?Catalog=%s&Dole=%d&SolStation=%d&Mass=%LG&Output=all&Seed=%ld&Count=1&Incr=1&Gas=%s&Moon=%s&SVG=%s",
						 (cat_arg == NULL) ? "none" : cat_arg->arg,
						 sys_no,
						 sys_no,
						 sun.mass,
						 flag_seed,
						 (do_gases)					? "on" : "off",	// one of ("on", "off")
						 (do_moons)					? "on" : "off",	// one of ("on", "off")
						 (graphic_format == gfSVG)	? "on" : "off"	// one of ("on", "off")
						);

				sprintf (svg_url,
						 "/cgi-bin/StarGen.pl?Catalog=%s&Dole=%d&SolStation=%d&Mass=%LG&Output=all&Seed=%ld&Count=1&Incr=1&Gas=%s&Moon=%s&SVG=%s&DoIt=SVG",
						 (cat_arg == NULL) ? "none" : cat_arg->arg,
						 sys_no,
						 sys_no,
						 sun.mass,
						 flag_seed,
						 (do_gases)					? "on" : "off",	// one of ("on", "off")
						 (do_moons)					? "on" : "off",	// one of ("on", "off")
						 (graphic_format == gfSVG)	? "on" : "off"	// one of ("on", "off")
						);
			}

			switch (out_format)
			{
				case ffSVG:
					create_svg_file (sgOut, innermost_planet, path, file_name, ".svg", prognam);
				break;
				
				case ffHTML:
					if ((graphic_format == gfSVG) && (sgOut == NULL))
					{
						create_svg_file (NULL, innermost_planet, path, file_name, ".svg", prognam);
					}
					
					if (thumbnails != NULL)
						html_thumbnails(innermost_planet, thumbnails, 
										system_name, 
										url_path, system_url, svg_url, file_name,
										FALSE, TRUE, FALSE, do_moons, graphic_format);

 					if ((system_count == 1) || (sgOut == NULL))
 					{
						if ((system_count == 1) && (sgOut != NULL))
							html_file = open_html_file (system_name, flag_seed, path, url_path, file_name, ".html",
														prognam, sgOut);
						else
							html_file = open_html_file (system_name, flag_seed, path, url_path, file_name, ".html",
														prognam, NULL);
						
						if (NULL != html_file)
						{
							html_thumbnails(innermost_planet, html_file, 
											system_name, 
											url_path, system_url, svg_url, file_name,
											TRUE, FALSE, TRUE, do_moons, graphic_format);
							html_describe_system(innermost_planet, do_gases, url_path, html_file);
							close_html_file(html_file);
						}
						else
						{
							fprintf(sgErr, "Could not open file %s%s%s\n",
									path, file_name, ".html");
							exit(0);
						}
					}
				break;
				
				case ffTEXT:
					text_describe_system(innermost_planet, do_gases, flag_seed);
				break;
				
				case ffCSV:
				case ffCSVdl:
					if (csv_file != NULL)
						csv_describe_system(csv_file, innermost_planet, do_gases, flag_seed);
				break;
				
				case ffCELESTIA:
				  celestia_describe_system(innermost_planet, designation, system_name, flag_seed, 
							   sys_inc,  // seb
							   sys_an,   // seb
							   sgErr);   // seb
				  break;
				case ffMOONGEN:
				  moongen_describe_system(innermost_planet, designation, system_name, flag_seed, 
							  sgErr); // seb
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
	
	if ((flag_verbose & 0x0001) || (flag_verbose & 0x0002))
	{
		fprintf (sgErr, "Earthlike planets: %d\n", total_earthlike);
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
		fprintf (sgErr, "Breathable illumination range: %4.2Lf -  %4.2Lf\n", 
				 min_breathable_l, 
				 max_breathable_l);
		fprintf (sgErr, "Terrestrial illumination range: %4.2Lf -  %4.2Lf\n", 
				 min_breathable_terrestrial_l,
				 max_breathable_terrestrial_l);
		fprintf (sgErr, "Max moon mass: %4.2Lf\n", 
				 max_moon_mass * SUN_MASS_IN_EARTH_MASSES);
	}
		
	if (system_count > 1)
	{
		if (thumbnails != NULL)
		{
			if (do_gases)
				html_thumbnail_totals(thumbnails);
	
			close_html_file(thumbnails);
		}
	}
	
	if (csv_file != NULL)
	{
		fflush (csv_file);
		fclose (csv_file);
	}

	return(0);
}

long double get_accreated_gas_pressure(planet_pointer planet)
{
  long double atmosphere_height = planet->radius - planet->core_radius;
  long double times_that_of_earth = atmosphere_height / 11;
  long double pressure = times_that_of_earth * EARTH_SURF_PRES_IN_MILLIBARS; // this is a horrible guess. don't take seriously.
  pressure += 100; // just in case the pressure is still 0;
  return pressure;
}

int is_gas_giant(planet_pointer planet)
{
  if (planet->type == tGasGiant || planet->type == tSubGasGiant || planet->type == tSubSubGasGiant || planet->type == tBrownDwarf)
  {
    return TRUE;
  }
  return FALSE;
}
