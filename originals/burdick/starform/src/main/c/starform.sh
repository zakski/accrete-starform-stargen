#---------------------------------- cut here ----------------------------------
# This is a shell archive.  Remove anything before this line,
# then unpack it by saving it in a file and typing "sh file".
#
# Wrapped by Matt Burdick <burdick@hpindzb> on Wed Nov 16 07:49:58 1988
#
# This archive contains:
#	README		starform.mak	Makefile	starform.c	
#	accrete.c	enviro.c	display.c	utils.c		
#	const.h		structs.h	
#
# Error checking via wc(1) will be performed.
# Error checking via sum(1) will be performed.

LANG=""; export LANG

if sum -r </dev/null >/dev/null 2>&1
then
	sumopt='-r'
else
	sumopt=''
fi

echo x - README
cat >README <<'@EOF'
This program is based on an article by Martyn Fogg in the Journal of the
British Interplanetary Society (JBIS) called 'Extrasolar Planetary Systems:
a Microcomputer Simulation'.  In it, he described how to generate various
sun-like solar systems randomly.  Since he did a good job of listing
references, I decided to implement it in Turbo Pascal on my PC.

Later, I translated it to C for portability, and the result is what you see
in front of you.  Because of my need to run this on an IBM-PC, there are two
makefiles included with the program: 'Makefile' (for unix systems), and 
'starform.mak' for MS-DOS systems.  To create the executable on a unix 
system, type in 'make' alone; type 'make starform.mak' if you are on 
an MS-DOS machine and using Microsoft C.

Thanks go to Sean Malloy (malloy@nprdc.arpa) for his help with the random
number routines and to Marty Shannon (mjs@mozart.att.com) for the
lisp-style output format, command-line flags, and various other pieces.

Enjoy, and if you find any glaring inconsistancies or interesting pieces to
add to the simulation, let me know and I'll include it in any other
distributions I send out.

Now for some references.  These are not the only good references on this 
subject; only the most interesting of many that were listed in Fogg's 
article in vol 38 of JBIS:

For a good description of the entire program:
	"Extra-Solar Planetary Systems: A Microcomputer Simulation"
	Martyn J. Fogg,  Journal of the British Interplanetary Society
	Vol 38, pp. 501 - 514, 1985

For the surface temperature/albedo iterative loop:
	"The Evolution of the Atmosphere of the Earth"
	Michael H. Hart, Icarus, Vol 33, pp. 23 - 39, 1978

For the determination of the radius of a terrestrial planet:
	"The Internal Constitution of the Planets"
	D. S. Kothari, Ph.D. , Mon. Not. Roy. Astr. Soc.
	Vol 96, pp. 833 - 843, 1936

For the planetary mass accretion algorithm:
	"Formation of Planetary Systems by Aggregation: A Computer Simulation"
	S. H. Dole, RAND paper no. P-4226, 1969

For the day length calculation:
	"Q in the Solar System"
	P. Goldreich and S. Soter, Icarus, Vol 5, pp. 375 - 389, 1966


----------------------------------------------------------------------
 I can be reached at the email address burdick%hpda@hplabs.hp.com
----------------------------------------------------------------------
Here is a sample solar system:


Accrete - V3.0; seed=0x00000005
                         SYSTEM  CHARACTERISTICS
Stellar mass: 1.00 solar masses
Stellar luminosity: 0.99
Age: 4.429 billion years  (5.628 billion left on main sequence)
Habitable ecosphere radius: 0.996 AU

Planets present at:
1	  0.341 	 AU
2	  0.505 	 AU
3	  0.877 	 AU
4	  1.047 	 AU
5	  1.793 	 AU
6	  2.956 	 AU
7	  5.160 	 AU
8	  8.852 	 AU
9	 13.121 	 AU
10	 28.450 	 AU
11	 46.864 	 AU



Planet 1	
Planet is tidally locked with one face to star.
   Distance from primary star:	0.341	AU
   Mass:			0.220	Earth masses
   Surface gravity:		0.59	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		193.31	degrees Celcius
   Equatorial radius:		3893.8	Km
   Density:			5.314	grams/cc
   Eccentricity of orbit:	0.092
   Escape Velocity:		6.71	Km/sec
   Molecular weight retained:	17.63 and above
   Surface acceleration:	578.24	cm/sec2
   Axial tilt:			22	degrees
   Planetary albedo:		0.081
   Length of year:		72.89	days
   Length of day:		1749.33	hours
   Boiling point of water:	-273.0	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 2	
Planet is tidally locked with one face to star.
   Distance from primary star:	0.505	AU
   Mass:			0.202	Earth masses
   Surface gravity:		0.57	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		112.78	degrees Celcius
   Equatorial radius:		3786.9	Km
   Density:			5.310	grams/cc
   Eccentricity of orbit:	0.091
   Escape Velocity:		6.52	Km/sec
   Molecular weight retained:	18.65 and above
   Surface acceleration:	561.97	cm/sec2
   Axial tilt:			28	degrees
   Planetary albedo:		0.060
   Length of year:		130.99	days
   Length of day:		3143.70	hours
   Boiling point of water:	-273.0	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 3	
   Distance from primary star:	0.877	AU
   Mass:			0.165	Earth masses
   Surface gravity:		0.53	Earth gees
   Surface pressure:		2.702	Earth atmospheres	GREENHOUSE EFFECT
   Surface temperature:		45.57	degrees Celcius
   Equatorial radius:		3541.1	Km
   Density:			5.302	grams/cc
   Eccentricity of orbit:	0.015
   Escape Velocity:		6.10	Km/sec
   Molecular weight retained:	21.36 and above
   Surface acceleration:	524.69	cm/sec2
   Axial tilt:			29	degrees
   Planetary albedo:		0.038
   Length of year:		300.44	days
   Length of day:		40.82	hours
   Boiling point of water:	129.5	degrees Celcius
   Hydrosphere percentage:	100.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 4	
   Distance from primary star:	1.047	AU
   Mass:			1.515	Earth masses
   Surface gravity:		1.15	Earth gees
   Surface pressure:		1.889	Earth atmospheres
   Surface temperature:		19.01	degrees Celcius
   Equatorial radius:		7328.1	Km
   Density:			5.494	grams/cc
   Eccentricity of orbit:	0.017
   Escape Velocity:		12.84	Km/sec
   Molecular weight retained:	4.81 and above
   Surface acceleration:	1125.13	cm/sec2
   Axial tilt:			22	degrees
   Planetary albedo:		0.297
   Length of year:		391.74	days
   Length of day:		14.68	hours
   Boiling point of water:	118.4	degrees Celcius
   Hydrosphere percentage:	67.12
   Cloud cover percentage:	61.38
   Ice cover percentage:	1.06


Planet 5	*gas giant*
   Distance from primary star:	1.793	AU
   Mass:			6.262	Earth masses
   Equatorial radius:		18997.9	Km
   Density:			1.303	grams/cc
   Eccentricity of orbit:	0.002
   Escape Velocity:		16.21	Km/sec
   Molecular weight retained:	3.02 and above
   Surface acceleration:	691.87	cm/sec2
   Axial tilt:			29	degrees
   Planetary albedo:		0.500
   Length of year:		877.67	days
   Length of day:		15.54	hours


Planet 6	
   Distance from primary star:	2.956	AU
   Mass:			0.453	Earth masses
   Surface gravity:		0.75	Earth gees
   Surface pressure:		0.207	Earth atmospheres
   Surface temperature:		-136.53	degrees Celcius
   Equatorial radius:		4941.6	Km
   Density:			5.356	grams/cc
   Eccentricity of orbit:	0.140
   Escape Velocity:		8.55	Km/sec
   Molecular weight retained:	10.86 and above
   Surface acceleration:	739.66	cm/sec2
   Axial tilt:			18	degrees
   Planetary albedo:		0.634
   Length of year:		1857.62	days
   Length of day:		17.62	hours
   Boiling point of water:	61.1	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	81.12


Planet 7	*gas giant*
   Distance from primary star:	5.160	AU
   Mass:			69.313	Earth masses
   Equatorial radius:		41830.7	Km
   Density:			1.351	grams/cc
   Eccentricity of orbit:	0.299
   Escape Velocity:		36.35	Km/sec
   Molecular weight retained:	0.60 and above
   Surface acceleration:	1579.66	cm/sec2
   Axial tilt:			42	degrees
   Planetary albedo:		0.512
   Length of year:		4284.26	days
   Length of day:		10.28	hours


Planet 8	*gas giant*
   Distance from primary star:	8.852	AU
   Mass:			11.727	Earth masses
   Equatorial radius:		26059.7	Km
   Density:			0.946	grams/cc
   Eccentricity of orbit:	0.182
   Escape Velocity:		18.95	Km/sec
   Molecular weight retained:	2.21 and above
   Surface acceleration:	688.64	cm/sec2
   Axial tilt:			47	degrees
   Planetary albedo:		0.509
   Length of year:		9626.17	days
   Length of day:		15.57	hours


Planet 9	*gas giant*
   Distance from primary star:	13.121	AU
   Mass:			557.816	Earth masses
   Equatorial radius:		83066.4	Km
   Density:			1.389	grams/cc
   Eccentricity of orbit:	0.083
   Escape Velocity:		73.18	Km/sec
   Molecular weight retained:	0.15 and above
   Surface acceleration:	3223.89	cm/sec2
   Axial tilt:			33	degrees
   Planetary albedo:		0.454
   Length of year:		17357.91	days
   Length of day:		7.20	hours


Planet 10	
   Distance from primary star:	28.450	AU
   Mass:			0.372	Earth masses
   Surface gravity:		0.40	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		-222.05	degrees Celcius
   Equatorial radius:		6182.7	Km
   Density:			2.246	grams/cc
   Eccentricity of orbit:	0.000
   Escape Velocity:		6.93	Km/sec
   Molecular weight retained:	16.54 and above
   Surface acceleration:	388.05	cm/sec2
   Axial tilt:			57	degrees
   Planetary albedo:		0.149
   Length of year:		55468.32	days
   Length of day:		24.33	hours
   Boiling point of water:	-38.3	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.10


Planet 11	
   Distance from primary star:	46.864	AU
   Mass:			0.283	Earth masses
   Surface gravity:		0.36	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		-233.50	degrees Celcius
   Equatorial radius:		5653.0	Km
   Density:			2.236	grams/cc
   Eccentricity of orbit:	0.047
   Escape Velocity:		6.32	Km/sec
   Molecular weight retained:	19.88 and above
   Surface acceleration:	353.22	cm/sec2
   Axial tilt:			54	degrees
   Planetary albedo:		0.157
   Length of year:		117268.25	days
   Length of day:		25.50	hours
   Boiling point of water:	-45.5	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.08


@EOF
set `sum $sumopt <README`; if test $1 -ne 39709
then
	echo ERROR: README checksum is $1 should be 39709
fi
set `wc -lwc <README`
if test $1$2$3 != 29212909478
then
	echo ERROR: wc results of README are $* should be 292 1290 9478
fi

chmod 644 README

echo x - starform.mak
cat >starform.mak <<'@EOF'
# This is a makefile for the Microsoft QuickC version of "starform",
# a star system and planet generator

# To make a version for debugging or tracing, uncomment this line:
#CFLAGS = /Zi

# To make a normal optimized version, uncomment this line:
CFLAGS = /Ox

# To make a codeview-debuggable executable, uncomment this line:
#LINKFLAGS = /CODEVIEW

# This line should always be uncommented:
OBJS = accrete.obj enviro.obj display.obj utils.obj


accrete.obj: accrete.c const.h structs.h
	qcl /c $(CFLAGS) accrete.c

enviro.obj: enviro.c const.h structs.h
	qcl /c $(CFLAGS) enviro.c

display.obj: display.c const.h structs.h
	qcl /c $(CFLAGS) display.c

utils.obj: utils.c const.h
	qcl /c $(CFLAGS) utils.c

starform.obj: starform.c const.h structs.h
	qcl /c $(CFLAGS) starform.c

starform.exe: starform.obj $(OBJS)
	link $(LINKFLAGS) starform.obj $(OBJS);

@EOF
set `sum $sumopt <starform.mak`; if test $1 -ne 54724
then
	echo ERROR: starform.mak checksum is $1 should be 54724
fi
set `wc -lwc <starform.mak`
if test $1$2$3 != 34118858
then
	echo ERROR: wc results of starform.mak are $* should be 34 118 858
fi

chmod 644 starform.mak

echo x - Makefile
cat >Makefile <<'@EOF'
# Makefile for "starform", a star system and planet generator

# To make a version for debugging or tracing, uncomment this line:
#CFLAGS = -g

# For those machines in which the rand() function returns a long int, put
# a LONG_RAND flag into the CFLAGS line that you use.  For instance, uncomment 
# and use the next line for a normal version of the program:
#CFLAGS = -O -DLONG_RAND

# To make a normal version for machines with rand() returning 16-bit numbers:
CFLAGS = -O

# These two lines should always be uncommented:
OBJS = accrete.o enviro.o display.o utils.o
LIBS = -lm


starform: starform.o $(OBJS)
	cc $(CFLAGS) -o starform starform.o $(OBJS) $(LIBS)
	@echo "starform made"

accrete.o: accrete.c const.h structs.h
	cc -c $(CFLAGS) accrete.c

enviro.o: enviro.c const.h structs.h
	cc -c $(CFLAGS) enviro.c

display.o: display.c const.h structs.h
	cc -c $(CFLAGS) display.c

utils.o: utils.c const.h
	cc -c $(CFLAGS) utils.c

starform.o: starform.c const.h structs.h
	cc -c $(CFLAGS) starform.c

clean:
	rm -f *.o starform

lint:
	lint -abchp starform.c accrete.c enviro.c display.c utils.c

SHARFILES = README starform.mak Makefile starform.c accrete.c enviro.c display.c utils.c const.h structs.h

shar: $(SHARFILES)
	shar -abcCs $(SHARFILES) >starform.shar

@EOF
set `sum $sumopt <Makefile`; if test $1 -ne 54640
then
	echo ERROR: Makefile checksum is $1 should be 54640
fi
set `wc -lwc <Makefile`
if test $1$2$3 != 481861272
then
	echo ERROR: wc results of Makefile are $* should be 48 186 1272
fi

chmod 644 Makefile

echo x - starform.c
cat >starform.c <<'@EOF'
#include	<stdio.h>
#include        <math.h>
#include        <sys/types.h>
#include        <sys/timeb.h>

#ifdef MSDOS
#include        <stddef.h>
#include        <malloc.h>
#include	<stdlib.h>
#include        <float.h>
#endif

#include        "const.h"
#include        "structs.h"

/*  These are all of the global variables used during accretion:  */
planet_pointer innermost_planet;
double stell_mass_ratio, stell_luminosity_ratio, main_seq_life,
     age, r_ecosphere, r_greenhouse;
int flag_verbose=FALSE;
long flag_seed=FALSE;
int flag_lisp = FALSE;
int flag_graphics = FALSE;
int resonance;

/* externals from C library not elsewhere declared: */
extern void srand();

extern double random_number();
extern double luminosity();
extern double stellar_dust_limit();
extern planet_pointer dist_planetary_masses();
extern int orb_zone();
extern double empirical_density();
extern double volume_density();
extern double volume_radius();
extern double kothari_radius();
extern double period();
extern double day_length();
extern int inclination();
extern double escape_vel();
extern double acceleration();
extern double rms_vel();
extern double molecule_limit();
extern double about();
extern int grnhouse();
extern double gravity();
extern double vol_inventory();
extern double pressure();
extern double boiling_point();


void init()
{
        struct timeb grap;
	int seed;
	
	if (flag_seed) {
		(void)srand(flag_seed);
		if (flag_lisp)
			printf("(Accrete %s) ; seed: 0x%.8lx\n", "3.0", flag_seed);
		else
			printf("Accrete - V%s; seed=0x%.8lx\n", "3.0", flag_seed);
	}
	else {
		ftime(&grap);
		seed = (int)((grap.time%100000)+grap.millitm);
		(void)srand(seed);
		if (flag_lisp)
			printf("(Accrete %s) ; seed: 0x%.8lx\n", "3.0", seed);
		else
			printf("Accrete - V%s; seed=0x%.8lx\n", "3.0", seed);
	}
}

void generate_stellar_system()
{
     planet_pointer planet;
     double outer_dust_limit;

     stell_mass_ratio = random_number(0.6,1.3);
     stell_luminosity_ratio = luminosity(stell_mass_ratio);
     outer_dust_limit = stellar_dust_limit(stell_mass_ratio);
     innermost_planet = dist_planetary_masses(stell_mass_ratio,stell_luminosity_ratio,0.0,outer_dust_limit);
     main_seq_life = 1.0E10 * (stell_mass_ratio / stell_luminosity_ratio);
     if ((main_seq_life >= 6.0E9))
	  age = random_number(1.0E9,6.0E9);
     else 
	  age = random_number(1.0E9,main_seq_life);
     r_ecosphere = sqrt(stell_luminosity_ratio);
     r_greenhouse = r_ecosphere * GREENHOUSE_EFFECT_CONST;
     for (planet=innermost_planet; planet != NULL; planet = planet->next_planet)
     {
#ifdef	MOON
	planet->first_moon = dist_moon_masses (planet->mass,
		stell_luminosity_ratio, planet->e,
		0.0, planet_dust_limit(planet->mass));
#endif	/* MOON */
	  planet->orbit_zone = orb_zone(planet->a);
	  if (planet->gas_giant)
	  {
	       planet->density = empirical_density(planet->mass,planet->a,planet->gas_giant);
	       planet->radius = volume_radius(planet->mass,planet->density);
	  }
	  else 
	  {
	       planet->radius = kothari_radius(planet->mass,planet->gas_giant,planet->orbit_zone);
	       planet->density = volume_density(planet->mass,planet->radius);
	  }
	  planet->orb_period = period(planet->a,planet->mass,stell_mass_ratio);
	  planet->day = day_length(planet->mass,planet->radius,planet->e,
				   planet->density, planet->a,
				   planet->orb_period,planet->gas_giant);
	  planet->resonant_period = resonance;
	  planet->axial_tilt = inclination(planet->a);
	  planet->esc_velocity = escape_vel(planet->mass,planet->radius);
	  planet->surf_accel = acceleration(planet->mass,planet->radius);
	  planet->rms_velocity = rms_vel(MOL_NITROGEN,planet->a);
	  planet->molec_weight = molecule_limit(planet->mass,planet->radius);
	  if ((planet->gas_giant))
	  {
	       planet->surf_grav = INCREDIBLY_LARGE_NUMBER;
	       planet->greenhouse_effect = FALSE;
	       planet->volatile_gas_inventory = INCREDIBLY_LARGE_NUMBER;
	       planet->surf_pressure = INCREDIBLY_LARGE_NUMBER;
	       planet->boil_point = INCREDIBLY_LARGE_NUMBER;
	       planet->hydrosphere = INCREDIBLY_LARGE_NUMBER;
	       planet->albedo = about(GAS_GIANT_ALBEDO,0.1);
	       planet->surf_temp = INCREDIBLY_LARGE_NUMBER;
	  }
	  else 
	  {
	       planet->surf_grav = gravity(planet->surf_accel);
	       planet->greenhouse_effect = grnhouse(planet->orbit_zone,planet->a,r_greenhouse);
	       planet->volatile_gas_inventory = vol_inventory(planet->mass,planet->esc_velocity,planet->rms_velocity,stell_mass_ratio,planet->orbit_zone,planet->greenhouse_effect);
	       planet->surf_pressure = pressure(planet->volatile_gas_inventory,planet->radius,planet->surf_grav);
	       if ((planet->surf_pressure == 0.0))
		    planet->boil_point = 0.0;
	       else 
		    planet->boil_point = boiling_point(planet->surf_pressure);
	       iterate_surface_temp(&(planet));
	  }
     }
     display_system(innermost_planet);
}


main (argc, argv)
int argc;
char *argv[];
{
	char *c, *prognam;
	int skip;

	prognam = argv[0];
	while (--argc > 0 && (*++argv)[0] == '-') {
		for (c = argv[0]+1, skip=FALSE; (*c != '\0') && (!(skip)); c++)
			switch (*c) 
			{
			case 'l':	/* set lisp output */
				++flag_lisp;
				break;
			case 'g':	/* display graphically */
				++flag_graphics;
				break;
			case 's':	/* set random seed */
				flag_seed = atoi(&(*++c));
				skip = TRUE;
				break;
			case 'v':	/* increment verbosity */
				++flag_verbose;
				break;
			default:
			case '?':
				fprintf(stderr, "%s: Usage: %s [-l] [-g] [-s#] [-v]\n",
					prognam, prognam);
				return (1);
			}
	}
	init();
	generate_stellar_system();
	return(0);
}

@EOF
set `sum $sumopt <starform.c`; if test $1 -ne 37392
then
	echo ERROR: starform.c checksum is $1 should be 37392
fi
set `wc -lwc <starform.c`
if test $1$2$3 != 1844645612
then
	echo ERROR: wc results of starform.c are $* should be 184 464 5612
fi

chmod 644 starform.c

echo x - accrete.c
cat >accrete.c <<'@EOF'
/*----------------------------------------------------------------------*/
/*                           BIBLIOGRAPHY                               */
/*  Dole, Stephen H.  "Formation of Planetary Systems by Aggregation:   */
/*      a Computer Simulation"  October 1969,  Rand Corporation Paper   */
/*	P-4226.								*/
/*----------------------------------------------------------------------*/

#include	<stdio.h>
#include	<math.h>
#include	"const.h"
#include	"structs.h"

/* externals from C library not elsewhere declared: */
extern char *malloc();
extern void free();

extern double random_number();
extern double random_eccentricity();
extern int flag_verbose, flag_lisp;

/* A few variables global to the entire program:		*/
planet_pointer planet_head;

/* Now for some variables global to the accretion process:      */
int dust_left;
double r_inner, r_outer, reduced_mass, dust_density, cloud_eccentricity;
dust_pointer dust_head;


void set_initial_conditions(inner_limit_of_dust, outer_limit_of_dust)
double inner_limit_of_dust, outer_limit_of_dust;
{
     dust_head = (dust *)malloc(sizeof(dust));
     planet_head = NULL;
     dust_head->next_band = NULL;
     dust_head->outer_edge = outer_limit_of_dust;
     dust_head->inner_edge = inner_limit_of_dust;
     dust_head->dust_present = TRUE;
     dust_head->gas_present = TRUE;
     dust_left = TRUE;
     cloud_eccentricity = 0.2;
}

double stellar_dust_limit(stell_mass_ratio)
double stell_mass_ratio; 
{
       return(200.0 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

double nearest_planet(stell_mass_ratio)
double stell_mass_ratio; 
{
     return(0.3 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

double farthest_planet(stell_mass_ratio)
double stell_mass_ratio; 
{
     return(50.0 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

double inner_effect_limit(a, e, mass)
double a, e, mass;
{
     return (a * (1.0 - e) * (1.0 - mass) / (1.0 + cloud_eccentricity));
}

double outer_effect_limit(a, e, mass)
double a, e, mass;
{
     return (a * (1.0 + e) * (1.0 + mass) / (1.0 - cloud_eccentricity));
}

int dust_available(inside_range, outside_range)
double inside_range, outside_range;
{
     dust_pointer current_dust_band;
     int dust_here;
     
     current_dust_band = dust_head;
     while ((current_dust_band != NULL)
	    && (current_dust_band->outer_edge < inside_range))
	  current_dust_band = current_dust_band->next_band;
     if (current_dust_band == NULL)
	  dust_here = FALSE;
     else dust_here = current_dust_band->dust_present;
     while ((current_dust_band != NULL)
	    && (current_dust_band->inner_edge < outside_range)) {
	       dust_here = dust_here || current_dust_band->dust_present;
	       current_dust_band = current_dust_band->next_band;
	  }
     return(dust_here);
}

void update_dust_lanes(min, max, mass, crit_mass,
		       body_inner_bound, body_outer_bound)
double min, max, mass, crit_mass, body_inner_bound, body_outer_bound;
{
     int gas; 
     dust_pointer node1, node2, node3;
     
     dust_left = FALSE;
     if ((mass > crit_mass))
	  gas = FALSE;
     else 
	  gas = TRUE;
     node1 = dust_head;
     while ((node1 != NULL))
     {
	  if (((node1->inner_edge < min) && (node1->outer_edge > max)))
	  {
	       node2 = (dust *)malloc(sizeof(dust));
	       node2->inner_edge = min;
	       node2->outer_edge = max;
	       if ((node1->gas_present == TRUE))
		    node2->gas_present = gas;
	       else 
		    node2->gas_present = FALSE;
	       node2->dust_present = FALSE;
	       node3 = (dust *)malloc(sizeof(dust));
	       node3->inner_edge = max;
	       node3->outer_edge = node1->outer_edge;
	       node3->gas_present = node1->gas_present;
	       node3->dust_present = node1->dust_present;
	       node3->next_band = node1->next_band;
	       node1->next_band = node2;
	       node2->next_band = node3;
	       node1->outer_edge = min;
	       node1 = node3->next_band;
	  }
	  else 
	       if (((node1->inner_edge < max) && (node1->outer_edge > max)))
	       {
		    node2 = (dust *)malloc(sizeof(dust));
		    node2->next_band = node1->next_band;
		    node2->dust_present = node1->dust_present;
		    node2->gas_present = node1->gas_present;
		    node2->outer_edge = node1->outer_edge;
		    node2->inner_edge = max;
		    node1->next_band = node2;
		    node1->outer_edge = max;
		    if ((node1->gas_present == TRUE))
			 node1->gas_present = gas;
		    else 
			 node1->gas_present = FALSE;
		    node1->dust_present = FALSE;
		    node1 = node2->next_band;
	       }
	       else 
		    if (((node1->inner_edge < min) && (node1->outer_edge > min)))
		    {
			 node2 = (dust *)malloc(sizeof(dust));
			 node2->next_band = node1->next_band;
			 node2->dust_present = FALSE;
			 if ((node1->gas_present == TRUE))
			      node2->gas_present = gas;
			 else 
			      node2->gas_present = FALSE;
			 node2->outer_edge = node1->outer_edge;
			 node2->inner_edge = min;
			 node1->next_band = node2;
			 node1->outer_edge = min;
			 node1 = node2->next_band;
		    }
		    else 
			 if (((node1->inner_edge >= min) && (node1->outer_edge <= max)))
			 {
			      if ((node1->gas_present == TRUE))
				   node1->gas_present = gas;
			      node1->dust_present = FALSE;
			      node1 = node1->next_band;
			 }
			 else 
			      if (((node1->outer_edge < min) || (node1->inner_edge > max)))
				   node1 = node1->next_band;
     }
     node1 = dust_head;
     while ((node1 != NULL))
     {
	  if (((node1->dust_present)
	       && (((node1->outer_edge >= body_inner_bound)
		    && (node1->inner_edge <= body_outer_bound)))))
	       dust_left = TRUE;
	  node2 = node1->next_band;
	  if ((node2 != NULL))
	  {
	       if (((node1->dust_present == node2->dust_present)
		    && (node1->gas_present == node2->gas_present)))
	       {
		    node1->outer_edge = node2->outer_edge;
		    node1->next_band = node2->next_band;
		    free(node2);
	       }
	  }
	  node1 = node1->next_band;
     }
}

double collect_dust(last_mass, a, e, crit_mass, dust_band)
double last_mass, a, e, crit_mass;
dust_pointer dust_band;
{
     double mass_density, temp1, temp2, temp, temp_density, bandwidth, width, volume;
     
     temp = last_mass / (1.0 + last_mass);
     reduced_mass = pow(temp,(1.0 / 4.0));
     r_inner = inner_effect_limit(a, e, reduced_mass);
     r_outer = outer_effect_limit(a, e, reduced_mass);
     if ((r_inner < 0.0))
	  r_inner = 0.0;
     if ((dust_band == NULL))
	  return(0.0);
     else 
     {
	  if ((dust_band->dust_present == FALSE))
	       temp_density = 0.0;
	  else 
	       temp_density = dust_density;
	  if (((last_mass < crit_mass) || (dust_band->gas_present == FALSE)))
	       mass_density = temp_density;
	  else 
	       mass_density = K * temp_density / (1.0 + sqrt(crit_mass / last_mass)
						  * (K - 1.0));
	  if (((dust_band->outer_edge <= r_inner)
	       || (dust_band->inner_edge >= r_outer)))
	       return(collect_dust(last_mass,a,e,crit_mass, dust_band->next_band));
	  else
	  {
	       bandwidth = (r_outer - r_inner);
	       temp1 = r_outer - dust_band->outer_edge;
	       if (temp1 < 0.0)
		    temp1 = 0.0;
	       width = bandwidth - temp1;
	       temp2 = dust_band->inner_edge - r_inner;
	       if (temp2 < 0.0)
		    temp2 = 0.0;
	       width = width - temp2;
	       temp = 4.0 * PI * pow(a,2.0) * reduced_mass
		    * (1.0 - e * (temp1 - temp2) / bandwidth);
	       volume = temp * width;
	       return(volume * mass_density
		      + collect_dust(last_mass,a,e,crit_mass,
				     dust_band->next_band));
	  }
     }
}


/*--------------------------------------------------------------------------*/
/*   Orbital radius is in AU, eccentricity is unitless, and the stellar     */
/*  luminosity ratio is with respect to the sun.  The value returned is the */
/*  mass at which the planet begins to accrete gas as well as dust, and is  */
/*  in units of solar masses.                                               */
/*--------------------------------------------------------------------------*/

double critical_limit(orb_radius, eccentricity, stell_luminosity_ratio)
double orb_radius, eccentricity, stell_luminosity_ratio;
{
     double temp, perihelion_dist;
     
     perihelion_dist = (orb_radius - orb_radius * eccentricity);
     temp = perihelion_dist * sqrt(stell_luminosity_ratio);
     return(B * pow(temp,-0.75));
}



void accrete_dust(seed_mass, a, e, crit_mass,
		  body_inner_bound, body_outer_bound)
double *seed_mass, a, e, crit_mass,
     body_inner_bound, body_outer_bound;
{
     double new_mass, temp_mass;
     
     new_mass = (*seed_mass);
     do
     {
	  temp_mass = new_mass;
	  new_mass = collect_dust(new_mass,a,e,crit_mass,
				  dust_head);
     }
     while (!(((new_mass - temp_mass) < (0.0001 * temp_mass))));
     (*seed_mass) = (*seed_mass) + new_mass;
     update_dust_lanes(r_inner,r_outer,(*seed_mass),crit_mass,body_inner_bound,body_outer_bound);
}



void coalesce_planetesimals(a, e, mass, crit_mass,
			    stell_luminosity_ratio,
			    body_inner_bound, body_outer_bound)
double a, e, mass, crit_mass, stell_luminosity_ratio,
     body_inner_bound, body_outer_bound;
{
     planet_pointer node1, node2, node3;
     int finished; 
     double temp, dist1, dist2, a3;
     
     finished = FALSE;
     node1 = planet_head;
     while ((node1 != NULL))
     {
	  node2 = node1;
	  temp = node1->a - a;
	  if ((temp > 0.0))
	  {
	       dist1 = (a * (1.0 + e) * (1.0 + reduced_mass)) - a;
	       /* x aphelion   */
	       reduced_mass = pow((node1->mass / (1.0 + node1->mass)),(1.0 / 4.0));
	       dist2 = node1->a
		    - (node1->a * (1.0 - node1->e) * (1.0 - reduced_mass));
	  }
	  else 
	  {
	       dist1 = a - (a * (1.0 - e) * (1.0 - reduced_mass));
	       /* x perihelion */
	       reduced_mass = pow(node1->mass / (1.0 + node1->mass),(1.0 / 4.0));
	       dist2 = (node1->a * (1.0 + node1->e) * (1.0 + reduced_mass))
		    - node1->a;
	  }
	  if (((fabs(temp) <= fabs(dist1)) || (fabs(temp) <= fabs(dist2))))
	  {
	       if (flag_verbose)
		       if (flag_lisp)
			       printf(";Collision between two planetesimals!\n");
		       else
			       printf("Collision between two planetesimals!\n");
	       a3 = (node1->mass + mass) / ((node1->mass / node1->a) + (mass / a));
	       temp = node1->mass * sqrt(node1->a) * sqrt(1.0 - pow(node1->e,2.0));
	       temp = temp + (mass * sqrt(a) * sqrt(sqrt(1.0 - pow(e,2.0))));
	       temp = temp / ((node1->mass + mass) * sqrt(a3));
	       temp = 1.0 - pow(temp,2.0);
	       if (((temp < 0.0) || (temp >= 1.0)))
		    temp = 0.0;
	       e = sqrt(temp);
	       temp = node1->mass + mass;
	       accrete_dust(&(temp),a3,e,stell_luminosity_ratio,
			    body_inner_bound,body_outer_bound);
	       node1->a = a3;
	       node1->e = e;
	       node1->mass = temp;
	       node1 = NULL;
	       finished = TRUE;
	  }
	  else 
	       node1 = node1->next_planet;
     }
     if (!(finished))
     {
	  node3 = (planets *)malloc(sizeof(planets));
	  node3->a = a;
	  node3->e = e;
	  if ((mass >= crit_mass))
	       node3->gas_giant = TRUE;
	  else 
	       node3->gas_giant = FALSE;
	  node3->mass = mass;
	  if ((planet_head == NULL))
	  {
	       planet_head = node3;
	       node3->next_planet = NULL;
	  }
	  else 
	  {
	       node1 = planet_head;
	       if ((a < node1->a))
	       {
		    node3->next_planet = node1;
		    planet_head = node3;
	       }
	       else 
		    if ((planet_head->next_planet == NULL))
		    {
			 planet_head->next_planet = node3;
			 node3->next_planet = NULL;
		    }
		    else 
		    {
			 while (((node1 != NULL) && (node1->a < a)))
			 {
			      node2 = node1;
			      node1 = node1->next_planet;
			 }
			 node3->next_planet = node1;
			 node2->next_planet = node3;
		    }
	  }
     }
}


planet_pointer dist_planetary_masses(stell_mass_ratio,
					   stell_luminosity_ratio, inner_dust, outer_dust)
double stell_mass_ratio, stell_luminosity_ratio, inner_dust, outer_dust;
{
     double a, e, mass, crit_mass,
     planet_inner_bound, planet_outer_bound;
     
     set_initial_conditions(inner_dust,outer_dust);
     planet_inner_bound = nearest_planet(stell_mass_ratio);
     planet_outer_bound = farthest_planet(stell_mass_ratio);
     while (dust_left)
     {
	  a = random_number(planet_inner_bound,planet_outer_bound);
	  e = random_eccentricity( );
	  mass = PROTOPLANET_MASS;
	  if (flag_verbose)
		  if (flag_lisp)
			  printf(";Checking %lg AU.\n",a);
		  else
			  printf("Checking %lg AU.\n",a);
	  if (dust_available(inner_effect_limit(a, e, mass),
			     outer_effect_limit(a, e, mass))) {
		  if (flag_verbose)
			  if (flag_lisp)
				  printf(";.. Injecting protoplanet.\n");
			  else
				  printf(".. Injecting protoplanet.\n");
		    dust_density = DUST_DENSITY_COEFF * sqrt(stell_mass_ratio)
			 * exp(-ALPHA * pow(a,(1.0 / N)));
		    crit_mass = critical_limit(a,e,stell_luminosity_ratio);
		    accrete_dust(&(mass),a,e,crit_mass,
				 planet_inner_bound,
				 planet_outer_bound);
		    if ((mass != 0.0) && (mass != PROTOPLANET_MASS))
			 coalesce_planetesimals(a,e,mass,crit_mass,
						stell_luminosity_ratio,
						planet_inner_bound,planet_outer_bound);
		    else if (flag_verbose)
			    if (flag_lisp)
				    printf(";.. failed due to large neighbor.\n");
			    else
				    printf(".. failed due to large neighbor.\n");
	       }
	  else if (flag_verbose)
		  if (flag_lisp)
			  printf(";.. failed.\n");
		  else
			  printf(".. failed.\n");
     }
     return(planet_head);
}



#ifdef	MOON
planet_pointer dist_moon_masses(planetary_mass, stell_luminosity_ratio,
				      planet_eccentricity, inner_dust, outer_dust)
double planetary_mass, stell_luminosity_ratio, planet_eccentricity,
     inner_dust, outer_dust;
{
     double a, e, mass, crit_mass,
     planet_inner_bound, planet_outer_bound;
     
     return(NULL);
}
#endif	/* MOON */


@EOF
set `sum $sumopt <accrete.c`; if test $1 -ne 38658
then
	echo ERROR: accrete.c checksum is $1 should be 38658
fi
set `wc -lwc <accrete.c`
if test $1$2$3 != 459137213814
then
	echo ERROR: wc results of accrete.c are $* should be 459 1372 13814
fi

chmod 644 accrete.c

echo x - enviro.c
cat >enviro.c <<'@EOF'
#include	<math.h>
#include	"const.h"
#include	"structs.h"

extern double about();

extern double stell_luminosity_ratio, stell_mass_ratio, r_ecosphere, age;
extern int resonance;

double luminosity(mass_ratio)
double mass_ratio;
{
     double n; 
     
     if (mass_ratio < 1.0)
	  n = 1.75 * (mass_ratio - 0.1) + 3.325;
     else 
	  n = 0.5 * (2.0 - mass_ratio) + 4.4;
     return(pow(mass_ratio,n));
}


/*--------------------------------------------------------------------------*/
/*   This function, given the orbital radius of a planet in AU, returns     */
/*   the orbital 'zone' of the particle.                                    */
/*--------------------------------------------------------------------------*/

int orb_zone(orb_radius)
double orb_radius; 
{
     if (orb_radius < (4.0 * sqrt(stell_luminosity_ratio)))
	  return(1);
     else 
     {
	  if ((orb_radius >= (4.0 * sqrt(stell_luminosity_ratio))) && (orb_radius < (15.0 * sqrt(stell_luminosity_ratio))))
	       return(2);
	  else 
	       return(3);
     }
}


/*--------------------------------------------------------------------------*/
/*   The mass is in units of solar masses, and the density is in units      */
/*   of grams/cc.  The radius returned is in units of km.                   */
/*--------------------------------------------------------------------------*/

double volume_radius(mass, density)
double mass, density;
{
     double volume; 
     
     mass = mass * SOLAR_MASS_IN_GRAMS;
     volume = mass / density;
     return(pow((3.0 * volume) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
}

/*--------------------------------------------------------------------------*/
/*   Returns the radius of the planet in kilometers.			    */
/*   The mass passed in is in units of solar masses.			    */
/*   This formula is listed as eq.9 in Fogg's article, although some typos  */
/*   crop up in that eq.  See "The Internal Constitution of Planets", by    */
/*   Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 */
/*   pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  */
/*   eq.23, which appears on page 840.                                      */
/*--------------------------------------------------------------------------*/

double kothari_radius(mass, giant, zone)
double mass;
int giant, zone;
{
     double temp, temp2, atomic_weight, atomic_num;
     
     if (zone == 1)
     {
	  if (giant)
	  {
	       atomic_weight = 9.5;
	       atomic_num = 4.5;
	  }
	  else 
	  {
	       atomic_weight = 15.0;
	       atomic_num = 8.0;
	  }
     }
     else 
	  if (zone == 2)
	  {
	       if (giant)
	       {
		    atomic_weight = 2.47;
		    atomic_num = 2.0;
	       }
	       else 
	       {
		    atomic_weight = 10.0;
		    atomic_num = 5.0;
	       }
	  }
	  else 
	  {
	       if (giant)
	       {
		    atomic_weight = 7.0;
		    atomic_num = 4.0;
	       }
	       else 
	       {
		    atomic_weight = 10.0;
		    atomic_num = 5.0;
	       }
	  }
     temp = atomic_weight * atomic_num;
     temp = (2.0 * BETA_20 * pow(SOLAR_MASS_IN_GRAMS,(1.0 / 3.0))) / (A1_20 * pow(temp,(1.0 / 3.0)));
     temp2 = A2_20 * pow(atomic_weight,(4.0 / 3.0)) * pow(SOLAR_MASS_IN_GRAMS,(2.0 / 3.0));
     temp2 = temp2 * pow(mass,(2.0 / 3.0));
     temp2 = temp2 / (A1_20 * pow2(atomic_num));
     temp2 = 1.0 + temp2;
     temp = temp / temp2;
     temp = (temp * pow(mass,(1.0 / 3.0))) / CM_PER_KM;
     return(temp);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the orbital radius  */
/*  is in units of AU.  The density is returned in units of grams/cc.       */
/*--------------------------------------------------------------------------*/

double empirical_density(mass, orb_radius, gas_giant)
double mass, orb_radius;
int gas_giant;
{
     double temp; 
     
     temp = pow(mass * SUN_MASS_IN_EARTH_MASSES,(1.0 / 8.0));
     temp = temp * pow1_4(r_ecosphere / orb_radius);
     if (gas_giant)
	  return(temp * 1.2);
     else 
	  return(temp * 5.5);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/

double volume_density(mass, equat_radius)
double mass, equat_radius;
{
     double volume; 
     
     mass = mass * SOLAR_MASS_IN_GRAMS;
     equat_radius = equat_radius * CM_PER_KM;
     volume = (4.0 * PI * pow3(equat_radius)) / 3.0;
     return(mass / volume);
}


/*--------------------------------------------------------------------------*/
/*  The separation is in units of AU, and both masses are in units of solar */
/*  masses.  The period returned is in terms of Earth days.                 */
/*--------------------------------------------------------------------------*/

double period(separation, small_mass, large_mass)
double separation, small_mass, large_mass;
{
     double period_in_years; 
     
     period_in_years = sqrt(pow3(separation) / (small_mass + large_mass));
     return(period_in_years * DAYS_IN_A_YEAR);
}


/*--------------------------------------------------------------------------*/
/*   Fogg's information for this routine came from Dole "Habitable Planets  */
/* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    */
/* up with his eq.12, which is the equation for the 'base_angular_velocity' */
/* below.  He then used an equation for the change in angular velocity per  */
/* time (dw/dt) from P. Goldreich and S. Soter's paper "Q in the Solar      */
/* System" in Icarus, vol 5, pp.375-389 (1966).  Using as a comparison the  */
/* change in angular velocity for the Earth, Fogg has come up with an	    */
/* approximation for our new planet (his eq.13) and take that into account. */
/* This is used to find 'change_in_angular_velocity' below.                 */
/*									    */
/*   Input parameters are mass (in solar masses), radius (in Km), orbital   */
/* period (in days), orbital radius (in AU), density (in g/cc),		    */
/* eccentricity, and whether it is a gas giant or not.			    */
/*   The length of the day is returned in units of hours.		    */
/*--------------------------------------------------------------------------*/

double day_length(mass, radius, eccentricity, density,
		  orb_radius, orb_period, giant)
double mass, radius, eccentricity, density, orb_radius, orb_period;
int giant;
{
     double base_angular_velocity, planetary_mass_in_grams, k2, ang_velocity,
	equatorial_radius_in_cm, change_in_angular_velocity,
	spin_resonance_factor, year_in_hours, day_in_hours;
     int stopped = FALSE;
     
     resonance = FALSE;
     if (giant)
	  k2 = 0.24;
     else 
	  k2 = 0.33;
     planetary_mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
     equatorial_radius_in_cm = radius * CM_PER_KM;
     year_in_hours = orb_period * 24.0;
     base_angular_velocity = sqrt(2.0 * J * (planetary_mass_in_grams) /
				  (k2 * pow2(equatorial_radius_in_cm)));
/*  This next calculation determines how much the planet's rotation is      */
/*  slowed by the presence of the star.					    */
     change_in_angular_velocity = CHANGE_IN_EARTH_ANG_VEL *
				  (density / EARTH_DENSITY) *
				  (equatorial_radius_in_cm / EARTH_RADIUS) *
				  (EARTH_MASS_IN_GRAMS / planetary_mass_in_grams) *
				  pow(stell_mass_ratio, 2.0) *
				  (1.0 / pow(orb_radius, 6.0));
     ang_velocity = base_angular_velocity + (change_in_angular_velocity * age);
/* Now we change from rad/sec to hours/rotation.			    */
     if (ang_velocity <= 0.0)
	stopped = TRUE;
     else day_in_hours = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * ang_velocity);
     if ((day_in_hours >= year_in_hours) || stopped)
     {
	  if (eccentricity > 0.1)
	  {
	    spin_resonance_factor = (1.0 - eccentricity) / (1.0 + eccentricity);
	    resonance = TRUE;
	    return(spin_resonance_factor * year_in_hours);
	  }
	  else 
	    return(year_in_hours);
     }
     return(day_in_hours);
}


/*--------------------------------------------------------------------------*/
/*   The orbital radius is expected in units of Astronomical Units (AU).    */
/*   Inclination is returned in units of degrees.                           */
/*--------------------------------------------------------------------------*/

int inclination(orb_radius)
double orb_radius; 
{
     int temp; 
     
     temp = (int)(pow(orb_radius,0.2) * about(EARTH_AXIAL_TILT,0.4));
     return(temp % 360);
}


/*--------------------------------------------------------------------------*/
/*   This function implements the escape velocity calculation.  Note that   */
/*  it appears that Fogg's eq.15 is incorrect.                              */
/*  The mass is in units of solar mass, the radius in kilometers, and the   */
/*  velocity returned is in cm/sec.                                         */
/*--------------------------------------------------------------------------*/

double escape_vel(mass, radius)
double mass, radius;
{
     double mass_in_grams, radius_in_cm;
     
     mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
     radius_in_cm = radius * CM_PER_KM;
     return(sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm));
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.16.  The molecular weight (usually assumed to be N2)  */
/*  is used as the basis of the Root Mean Square (RMS) velocity of the	    */
/*  molecule or atom.  The velocity returned is in cm/sec.		    */
/*--------------------------------------------------------------------------*/

double rms_vel(molecular_weight, orb_radius)
double molecular_weight, orb_radius;
{
     double exospheric_temp; 
     
     exospheric_temp = EARTH_EXOSPHERE_TEMP / pow2(orb_radius);
     return(sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight)
		 * CM_PER_METER);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the smallest molecular weight retained by the    */
/*  body, which is useful for determining the atmosphere composition.       */
/*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  */
/*  mass is in units of solar masses, and equatorial radius is in units of  */
/*  kilometers.                                                             */
/*--------------------------------------------------------------------------*/

double molecule_limit(mass, equat_radius)
double mass, equat_radius;
{
     double esc_velocity;
     
     esc_velocity = escape_vel(mass,equat_radius);
     return((3.0 * pow2(GAS_RETENTION_THRESHOLD * CM_PER_METER) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow2(esc_velocity));
}


/*--------------------------------------------------------------------------*/
/*   This function calculates the surface acceleration of a planet.  The    */
/*  mass is in units of solar masses, the radius in terms of km, and the    */
/*  acceleration is returned in units of cm/sec2.                           */
/*--------------------------------------------------------------------------*/

double acceleration(mass, radius)
double mass, radius;
{
     return(GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) /
			    pow2(radius * CM_PER_KM));
}


/*--------------------------------------------------------------------------*/
/*   This function calculates the surface gravity of a planet.  The         */
/*  acceleration is in units of cm/sec2, and the gravity is returned in     */
/*  units of Earth gravities.                                               */
/*--------------------------------------------------------------------------*/

double gravity(acceleration)
double acceleration; 
{
     return(acceleration / EARTH_ACCELERATION);
}


/*--------------------------------------------------------------------------*/
/*  Note that if the orbital radius of the planet is greater than or equal  */
/*  to R_inner, 99% of it's volatiles are assumed to have been deposited in */
/*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
/*--------------------------------------------------------------------------*/

int grnhouse(zone, orb_radius, r_greenhouse)
int zone; 
double orb_radius, r_greenhouse;
{
     if ((orb_radius < r_greenhouse) && (zone == 1))
	  return(TRUE);
     else 
	  return(FALSE);
}


/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.17.  The 'inventory' returned is unitless.    */
/*--------------------------------------------------------------------------*/

double vol_inventory(mass, escape_vel, rms_vel, stellar_mass, zone, greenhouse_effect)
double mass, escape_vel, rms_vel, stellar_mass;
int zone, greenhouse_effect;
{
     double velocity_ratio, proportion_const, temp1, temp2, earth_units;
     
     velocity_ratio = escape_vel / rms_vel;
     if (velocity_ratio >= GAS_RETENTION_THRESHOLD)
     {
	  switch (zone) {
	       case 1:
		    proportion_const = 100000.0;
		    break;
	       case 2:
		    proportion_const = 75000.0;
		    break;
	       case 3:
		    proportion_const = 250.0;
		    break;
	       default:
		    printf("Error: orbital zone not initialized correctly!\n");
		    break;
	       }
	  earth_units = mass * SUN_MASS_IN_EARTH_MASSES;
	  temp1 = (proportion_const * earth_units) / stellar_mass;
	  temp2 = about(temp1,0.2);
	  if (greenhouse_effect)
	       return(temp2);
	  else 
	       return(temp2 / 100.0);
     }
     else 
	  return(0.0);
}


/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.18.  The pressure returned is in units of     */
/*  millibars (mb).  The gravity is in units of Earth gravities, the radius */
/*  in units of kilometers.                                                 */
/*--------------------------------------------------------------------------*/

double pressure(volatile_gas_inventory, equat_radius, gravity)
double volatile_gas_inventory, equat_radius, gravity;
{
     equat_radius = KM_EARTH_RADIUS / equat_radius;
     return(volatile_gas_inventory * gravity / pow2(equat_radius));
}

/*--------------------------------------------------------------------------*/
/*   This function returns the boiling point of water in an atmosphere of   */
/*   pressure 'surf_pressure', given in millibars.  The boiling point is    */
/*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
/*--------------------------------------------------------------------------*/

double boiling_point(surf_pressure)
double surf_pressure; 
{
     double surface_pressure_in_bars; 
     
     surface_pressure_in_bars = surf_pressure / MILLIBARS_PER_BAR;
     return(1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
}


/*--------------------------------------------------------------------------*/
/*   This function is Fogg's eq.22.  Given the volatile gas inventory and   */
/*   planetary radius of a planet (in Km), this function returns the        */
/*   fraction of the planet covered with water.                             */
/*   I have changed the function very slightly:  the fraction of Earth's    */
/*   surface covered by water is 71%, not 75% as Fogg used.                 */
/*--------------------------------------------------------------------------*/

double hydro_fraction(volatile_gas_inventory, planet_radius)
double volatile_gas_inventory, planet_radius;
{
     double temp; 
     
     temp = (0.71 * volatile_gas_inventory / 1000.0) * pow2(KM_EARTH_RADIUS / planet_radius);
     if (temp >= 1.0)
	  return(1.0);
     else 
	  return(temp);
}


/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  */
/*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     */
/*   This equation is Hart's eq.3.                                          */
/*   I have modified it slightly using constants and relationships from     */
/*   Glass's book "Introduction to Planetary Geology", p.46.                */
/*   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     */
/*   covered by one Kg. of cloud.					    */
/*--------------------------------------------------------------------------*/

double cloud_fraction(surf_temp, smallest_MW_retained, equat_radius, hydro_fraction)
double surf_temp, smallest_MW_retained, equat_radius,
     hydro_fraction;
{
     double water_vapor_in_kg, fraction, surf_area, hydro_mass;
     
     if (smallest_MW_retained > WATER_VAPOR)
	  return(0.0);
     else 
     {
	  surf_area = 4.0 * PI * pow2(equat_radius);
	  hydro_mass = hydro_fraction * surf_area * EARTH_WATER_MASS_PER_AREA;
	  water_vapor_in_kg = (0.00000001 * hydro_mass) * exp(Q2_36 * (surf_temp - 288.0));
	  fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surf_area;
	  if (fraction >= 1.0)
	       return(1.0);
	  else 
	       return(fraction);
     }
}


/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of the planet's surface covered by ice.  This is  */
/*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. */
/*   I have changed a constant from 70 to 90 in order to bring it more in   */
/*   line with the fraction of the Earth's surface covered with ice, which  */
/*   is approximatly .016 (=1.6%).                                          */
/*--------------------------------------------------------------------------*/

double ice_fraction(hydro_fraction, surf_temp)
double hydro_fraction, surf_temp;
{
     double temp; 
     
     if (surf_temp > 328.0) 
	  surf_temp = 328.0;
     temp = pow(((328.0 - surf_temp) / 90.0),5.0);
     if (temp > (1.5 * hydro_fraction))
	  temp = (1.5 * hydro_fraction);
     if (temp >= 1.0)
	  return(1.0);
     else 
	  return(temp);
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital */
/*  radius in AU, and the temperature returned is in Kelvin.		    */
/*--------------------------------------------------------------------------*/

double eff_temp(ecosphere_radius, orb_radius, albedo)
double ecosphere_radius, orb_radius, albedo;
{
     return(sqrt(ecosphere_radius / orb_radius)
	    * pow1_4((1.0 - albedo) / 0.7)
	    * EARTH_EFFECTIVE_TEMP);
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
/*  Earth's Atmosphere" article.  The effective temperature given is in     */
/*  units of Kelvin, as is the rise in temperature produced by the          */
/*  greenhouse effect, which is returned.                                   */
/*--------------------------------------------------------------------------*/

double green_rise(optical_depth, effective_temp, surf_pressure)
double optical_depth, effective_temp, surf_pressure;
{
     double convection_factor; 
     
     convection_factor = EARTH_CONVECTION_FACTOR * pow1_4(surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS);
     return(pow1_4(1.0 + 0.75 * optical_depth) - 1.0) * effective_temp * convection_factor;
}


/*--------------------------------------------------------------------------*/
/*   The surface temperature passed in is in units of Kelvin.               */
/*   The cloud adjustment is the fraction of cloud cover obscuring each     */
/*   of the three major components of albedo that lie below the clouds.     */
/*--------------------------------------------------------------------------*/

double planet_albedo(water_fraction, cloud_fraction, ice_fraction, surf_pressure)
double water_fraction, cloud_fraction, ice_fraction, surf_pressure;
{
     double rock_fraction, cloud_adjustment, components, cloud_part,
     rock_part, water_part, ice_part;
     
     rock_fraction = 1.0 - water_fraction - ice_fraction;
     components = 0.0;
     if (water_fraction > 0.0)
	  components = components + 1.0;
     if (ice_fraction > 0.0)
	  components = components + 1.0;
     if (rock_fraction > 0.0)
	  components = components + 1.0;
     cloud_adjustment = cloud_fraction / components;
     if (rock_fraction >= cloud_adjustment)
	  rock_fraction = rock_fraction - cloud_adjustment;
     else 
	  rock_fraction = 0.0;
     if (water_fraction > cloud_adjustment)
	  water_fraction = water_fraction - cloud_adjustment;
     else 
	  water_fraction = 0.0;
     if (ice_fraction > cloud_adjustment)
	  ice_fraction = ice_fraction - cloud_adjustment;
     else 
	  ice_fraction = 0.0;
     cloud_part = cloud_fraction * about(CLOUD_ALBEDO,0.2);
     if (surf_pressure == 0.0)
	  rock_part = rock_fraction * about(ROCKY_AIRLESS_ALBEDO,0.3);
     else 
	  rock_part = rock_fraction * about(ROCKY_ALBEDO,0.1);
     water_part = water_fraction * about(WATER_ALBEDO,0.2);
     if (surf_pressure == 0.0)
	  ice_part = ice_fraction * about(AIRLESS_ICE_ALBEDO,0.4);
     else 
	  ice_part = ice_fraction * about(ICE_ALBEDO,0.1);
     return(cloud_part + rock_part + water_part + ice_part);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the dimensionless quantity of optical depth,     */
/*   which is useful in determining the amount of greenhouse effect on a    */
/*   planet.                                                                */
/*--------------------------------------------------------------------------*/

double opacity(molecular_weight, surf_pressure)
double molecular_weight, surf_pressure;
{
     double optical_depth; 
     
     optical_depth = 0.0;
     if ((molecular_weight >= 0.0) && (molecular_weight < 10.0))
	  optical_depth = optical_depth + 3.0;
     if ((molecular_weight >= 10.0) && (molecular_weight < 20.0))
	  optical_depth = optical_depth + 2.34;
     if ((molecular_weight >= 20.0) && (molecular_weight < 30.0))
	  optical_depth = optical_depth + 1.0;
     if ((molecular_weight >= 30.0) && (molecular_weight < 45.0))
	  optical_depth = optical_depth + 0.15;
     if ((molecular_weight >= 45.0) && (molecular_weight < 100.0))
	  optical_depth = optical_depth + 0.05;
     if (surf_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	  optical_depth = optical_depth * 8.333;
     else 
	  if (surf_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	       optical_depth = optical_depth * 6.666;
	  else 
	       if (surf_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS))
		    optical_depth = optical_depth * 3.333;
	       else 
		    if (surf_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS))
			 optical_depth = optical_depth * 2.0;
		    else 
			 if (surf_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS))
			      optical_depth = optical_depth * 1.5;
     return(optical_depth);
}


/*--------------------------------------------------------------------------*/
/*   The temperature calculated is in degrees Kelvin.                       */
/*   Quantities already known which are used in these calculations:         */
/*	 planet->molec_weight		        			    */
/*	 planet->surf_pressure					            */
/*       R_ecosphere                                                        */
/*	 planet->a							    */
/*	 planet->volatile_gas_inventory					    */
/*	 planet->radius							    */
/*	 planet->boil_point						    */
/*--------------------------------------------------------------------------*/

void iterate_surface_temp(planet)
planet_pointer *planet; 
{
     double surf1_temp, effective_temp, greenhs_rise, previous_temp,
     optical_depth, albedo, water, clouds, ice;
     
     optical_depth = opacity((*planet)->molec_weight,(*planet)->surf_pressure);
     effective_temp = eff_temp(r_ecosphere,(*planet)->a,EARTH_ALBEDO);
     greenhs_rise = green_rise(optical_depth,effective_temp,(*planet)->surf_pressure);
     surf1_temp = effective_temp + greenhs_rise;
     previous_temp = surf1_temp - 5.0;		/* force the while loop the first time */
     while ((fabs(surf1_temp - previous_temp) > 1.0)) {
	       previous_temp = surf1_temp;
	       water = hydro_fraction((*planet)->volatile_gas_inventory,(*planet)->radius);
	       clouds = cloud_fraction(surf1_temp,(*planet)->molec_weight,(*planet)->radius,water);
	       ice = ice_fraction(water,surf1_temp);
	       if ((surf1_temp >= (*planet)->boil_point) || (surf1_temp <= FREEZING_POINT_OF_WATER))
		    water = 0.0;
	       albedo = planet_albedo(water,clouds,ice,(*planet)->surf_pressure);
	       optical_depth = opacity((*planet)->molec_weight,(*planet)->surf_pressure);
	       effective_temp = eff_temp(r_ecosphere,(*planet)->a,albedo);
	       greenhs_rise = green_rise(optical_depth,effective_temp,(*planet)->surf_pressure);
	       surf1_temp = effective_temp + greenhs_rise;
	  }
     (*planet)->hydrosphere = water;
     (*planet)->cloud_cover = clouds;
     (*planet)->ice_cover = ice;
     (*planet)->albedo = albedo;
     (*planet)->surf_temp = surf1_temp;
}

@EOF
set `sum $sumopt <enviro.c`; if test $1 -ne 9655
then
	echo ERROR: enviro.c checksum is $1 should be 9655
fi
set `wc -lwc <enviro.c`
if test $1$2$3 != 664259125348
then
	echo ERROR: wc results of enviro.c are $* should be 664 2591 25348
fi

chmod 644 enviro.c

echo x - display.c
cat >display.c <<'@EOF'
#include	<stdio.h>
#include	<string.h>
#include        <math.h>

#ifdef MSDOS
#include        <stddef.h>
#include        <malloc.h>
#include	<stdlib.h>
#include        <float.h>
#endif

#include	"structs.h"
#include	"const.h"

#define	MAX_EXP_DIGS	3
#define	MAX_MAN_DIGS	20

extern double stell_mass_ratio, stell_luminosity_ratio, main_seq_life,
	age, r_ecosphere;
extern int flag_graphics, flag_lisp;

char OP[] = "(";
char CP[] = ")";


char *engineer_notation(d, p)
double d;
int p;
{
	static char mansign;
	static char expsign;
	static char output[1+MAX_MAN_DIGS+1+1+MAX_EXP_DIGS+1];
	double mantissa;
	int exponent;

	mansign = '+';
	expsign = '+';
	if (p > MAX_MAN_DIGS)
		p = MAX_MAN_DIGS;
	if (p < 3)
		p = 3;
	--p;
	if (d < 0.0)
	{
		mansign = '-';
		d = -d;
	}
	if (d == 0.0)
	{
		exponent = 0;
		mantissa = 0;
	}
	else
	{
		exponent = log10(d);
		if (exponent == 0 && d < 1.0)	/* log10 sometimes lies */
		{
			--exponent;
			--p;
		}
		if (exponent < 0)
		{
			expsign = '-';
			--exponent;
		}
		mantissa = d / pow(10.0, (double) exponent);
		if (exponent < 0)
			exponent = -exponent;
		while ((exponent % 3) != 0)
		{
			mantissa *= 10.0;
			p--;
			if (expsign == '-')
				++exponent;
			else
				--exponent;
		}
	}
	sprintf(output, "%c%*.*lfe%c%*.*d", mansign, p, p, mantissa,
		expsign, MAX_EXP_DIGS, MAX_EXP_DIGS, exponent);
	return (output);
}

void chart_system(innermost_planet)
planet_pointer innermost_planet;
{
}

void text_describe_system(innermost_planet)
planet_pointer innermost_planet;
{
     planet_pointer node1;
     int counter; 
     
     printf("                         SYSTEM  CHARACTERISTICS\n");
     printf("Stellar mass: %4.2lf solar masses\n", stell_mass_ratio);
     printf("Stellar luminosity: %4.2lf\n",stell_luminosity_ratio);
     printf("Age: %5.3lf billion years  (%5.3lf billion left on main sequence)\n",
	     (age /1.0E9),(main_seq_life - age) / 1.0E9);
     printf("Habitable ecosphere radius: %3.3lf AU\n",r_ecosphere);
     printf("\n");
     printf("Planets present at:\n");
     for (node1=innermost_planet, counter=1;
	  node1 != NULL;
	  node1=node1->next_planet, counter++)
     {
        printf("%d\t%7.3lf \t AU\n", counter, node1->a);
     }
     printf("\n\n\n");
     for (node1=innermost_planet, counter=1;
	  node1 != NULL;
	  node1=node1->next_planet, counter++)
     {
          printf("Planet %d\t",counter);
	  if (node1->gas_giant)
               printf("*gas giant*\n");
          else printf("\n");
	  if ((int)node1->day == (int)(node1->orb_period * 24.0))
               printf("Planet is tidally locked with one face to star.\n");
	  if (node1->resonant_period)
               printf("Planet's rotation is in a resonant spin lock with the star\n");
          printf("   Distance from primary star:\t%5.3lf\tAU\n",node1->a);
          printf("   Mass:\t\t\t%5.3lf\tEarth masses\n",node1->mass * SUN_MASS_IN_EARTH_MASSES);
	  if (!(node1->gas_giant))
	  {
               printf("   Surface gravity:\t\t%4.2lf\tEarth gees\n",node1->surf_grav);
               printf("   Surface pressure:\t\t%5.3lf\tEarth atmospheres",(node1->surf_pressure / 1000.0));
	       if ((node1->greenhouse_effect) && (node1->surf_pressure > 0.0))
                    printf("\tGREENHOUSE EFFECT\n");
	       else 
		    printf("\n");
               printf("   Surface temperature:\t\t%4.2lf\tdegrees Celcius\n",(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE));
	  }
          printf("   Equatorial radius:\t\t%3.1lf\tKm\n",node1->radius);
          printf("   Density:\t\t\t%5.3lf\tgrams/cc\n",node1->density);
          printf("   Eccentricity of orbit:\t%5.3lf\n",node1->e);
          printf("   Escape Velocity:\t\t%4.2lf\tKm/sec\n",node1->esc_velocity / CM_PER_KM);
          printf("   Molecular weight retained:\t%4.2lf and above\n",node1->molec_weight);
          printf("   Surface acceleration:\t%4.2lf\tcm/sec2\n",node1->surf_accel);
          printf("   Axial tilt:\t\t\t%d\tdegrees\n",node1->axial_tilt);
          printf("   Planetary albedo:\t\t%5.3lf\n",node1->albedo);
          printf("   Length of year:\t\t%4.2lf\tdays\n",node1->orb_period);
          printf("   Length of day:\t\t%4.2lf\thours\n",node1->day);
	  if (!(node1->gas_giant))
	  {
               printf("   Boiling point of water:\t%3.1lf\tdegrees Celcius\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
               printf("   Hydrosphere percentage:\t%4.2lf\n",(node1->hydrosphere * 100.0));
               printf("   Cloud cover percentage:\t%4.2lf\n",(node1->cloud_cover * 100));
               printf("   Ice cover percentage:\t%4.2lf\n",(node1->ice_cover * 100));
	  }
          printf("\n\n");
     }
}

void lisp_describe_system(innermost_planet)
planet_pointer innermost_planet;
{
	planet_pointer node1; 
	int counter; 
     
	printf("%splanetary-system\n", OP);
	printf(" %ssun\n", OP);
	printf("  %smass %s%s ; kg\n",
		OP,
		engineer_notation(stell_mass_ratio * SOLAR_MASS_IN_GRAMS / 1000.0, 6),
		CP);
	printf("  %sluminosity %s%s ; * SOL luminosity\n",
		OP, engineer_notation(stell_luminosity_ratio, 6), CP);
	printf("  %slifetime %s%s ; years\n",
		OP, engineer_notation(main_seq_life, 6), CP);
	printf("  %scurrent-age %s%s ; years\n",
		OP, engineer_notation(age, 6), CP);
	printf("  %secosphere-radius %s%s ; km\n",
		OP, engineer_notation(r_ecosphere * KM_PER_AU, 6), CP);
	printf(" %s\n", CP);
	for (node1=innermost_planet, counter=1;
	     node1 != NULL;
	     node1=node1->next_planet, counter++)
	{
		printf(" %splanet ; #%d\n",
			OP, counter);
		printf("  ; boolean:\n");
		printf("  %sis-gas-giant %d%s\n", OP, node1->gas_giant, CP);
		printf("  ; orbital statistics:\n");
		printf("  %smean-orbit-radius %s%s ; km\n",
			OP, engineer_notation(node1->a * KM_PER_AU, 6), CP);
		printf("  %sorbit-eccentricity %s%s\n",
			OP, engineer_notation(node1->e, 6), CP);
		printf("  %saxial-tilt %d%s ; degrees\n",
			OP, node1->axial_tilt, CP);
		printf("  %sorbital-period %s%s ; Earth days\n",
			OP, engineer_notation(node1->orb_period, 6), CP);
		printf("  %srotation-period %s%s ; Earth hours\n",
			OP, engineer_notation(node1->day, 6), CP);
		printf("  %sis-resonant %d%s\n", OP, node1->resonant_period, CP);
		printf("  ; planetary measurements:\n");
		printf("  %smass %s%s ; kg\n",
			OP, engineer_notation(node1->mass * SOLAR_MASS_IN_GRAMS / 1000.0, 6), CP);
		printf("  %sequatorial-radius %s%s ; km\n",
			OP, engineer_notation(node1->radius, 6), CP);
		printf("  %sdensity %s%s ; g/cm3\n",
			OP, engineer_notation(node1->density, 6), CP);
		printf("  ; planetary environment:\n");
		printf("  %sescape-velocity %s%s ; km/sec\n",
			OP, engineer_notation(node1->esc_velocity / CM_PER_KM, 6), CP);
		printf("  %smin-molecular-weight-retained %s%s\n",
			OP, engineer_notation(node1->molec_weight, 3), CP);
		printf("  %ssurface-acceleration %s%s ; cm/sec2\n",
			OP, engineer_notation(node1->surf_accel, 6), CP);
		if (!node1->gas_giant)
		{
			printf("  %ssurface-gravity %s%s ; Earth gees\n",
				OP, engineer_notation(node1->surf_grav, 3), CP);
			printf("  %sh2o-boils %s%s ; degrees celcius\n",
				OP,
				engineer_notation(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE, 3),
				CP);
			printf("  %ssurface-pressure %s%s ; Earth atmospheres\n",
				OP, engineer_notation(node1->surf_pressure / 1000.0, 3), CP);
			if (node1->greenhouse_effect && node1->surf_pressure > 0.0)
				printf("  %sgreenhouse 1%s\n", OP, CP);
			else
				printf("  %sgreenhouse 0%s\n", OP, CP);
			printf("  %ssurface-temperature %s%s ; degrees celcius\n",
				OP,
				engineer_notation(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE, 3),
				CP);
			printf("  %shydrosphere %s%s\n",
				OP, engineer_notation(node1->hydrosphere, 3), CP);
			printf("  %scloud-cover %s%s\n",
				OP, engineer_notation(node1->cloud_cover, 3), CP);
			printf("  %sice-cover %s%s\n",
				OP, engineer_notation(node1->ice_cover, 3), CP);
		}
		printf("  %salbedo %s%s\n",
			OP, engineer_notation(node1->albedo, 3), CP);
		printf(" %s\n", CP);
	}
	printf("%s\n", CP);
}

void display_system(innermost_planet)
planet_pointer innermost_planet;
{
	if (flag_graphics)
		chart_system(innermost_planet);
	else if (flag_lisp)
		lisp_describe_system(innermost_planet);
	else
		text_describe_system(innermost_planet);
}

@EOF
set `sum $sumopt <display.c`; if test $1 -ne 36445
then
	echo ERROR: display.c checksum is $1 should be 36445
fi
set `wc -lwc <display.c`
if test $1$2$3 != 2527468243
then
	echo ERROR: wc results of display.c are $* should be 252 746 8243
fi

chmod 644 display.c

echo x - utils.c
cat >utils.c <<'@EOF'
#include	<math.h>
#include	"const.h"

/*----------------------------------------------------------------------*/
/*  This function returns a random real number between the specified    */
/* inner and outer bounds.                                              */
/*----------------------------------------------------------------------*/

double random_number(inner, outer)
double inner, outer;
{
     double range;
     
     range = outer - inner;
     return((((double)rand()) / (double)(RAND_MAX)) * range + inner);
}


/*----------------------------------------------------------------------*/
/*   This function returns a value within a certain variation of the    */
/*   exact value given it in 'value'.                                   */
/*----------------------------------------------------------------------*/

double about(value, variation)
double value, variation;
{
     return(value + (value * random_number(-variation,variation)));
}

double random_eccentricity()
{
     return(1.0 - pow(random_number(0.0, 1.0),ECCENTRICITY_COEFF));
}
@EOF
set `sum $sumopt <utils.c`; if test $1 -ne 8192
then
	echo ERROR: utils.c checksum is $1 should be 8192
fi
set `wc -lwc <utils.c`
if test $1$2$3 != 33901055
then
	echo ERROR: wc results of utils.c are $* should be 33 90 1055
fi

chmod 644 utils.c

echo x - const.h
cat >const.h <<'@EOF'
#ifdef LONG_RAND
#define RAND_MAX        (2147483647.0)
#else
#define RAND_MAX        (32767.0)
#endif

#define PI                      (3.1415926536)
#define	RADIANS_PER_ROTATION	(2.0 * PI)
#define TRUE                    (1)
#define FALSE                   (0)
#define ECCENTRICITY_COEFF      (0.077)		/* Dole's was 0.077         */
#define	PROTOPLANET_MASS	(1.0E-15)	/* Units of solar masses    */
#define CHANGE_IN_EARTH_ANG_VEL (-1.3E-15)	/* Units of radians/sec/year*/
#define SOLAR_MASS_IN_GRAMS	(1.989E33)	/* Units of grams           */
#define EARTH_MASS_IN_GRAMS	(5.977E27)	/* Units of grams           */
#define EARTH_RADIUS		(6.378E8)	/* Units of cm		    */
#define EARTH_DENSITY		(5.52)		/* Units of g/cc	    */
#define KM_EARTH_RADIUS		(6378.0)	/* Units of km              */
#define EARTH_ACCELERATION	(981.0)		/* Units of cm/sec2         */
#define EARTH_AXIAL_TILT	(23.4)		/* Units of degrees         */
#define EARTH_EXOSPHERE_TEMP	(1273.0)	/* Units of degrees Kelvin  */
#define SUN_MASS_IN_EARTH_MASSES (332775.64)
#define EARTH_EFFECTIVE_TEMP	(255.0)		/* Units of degrees Kelvin  */
#define EARTH_ALBEDO		(0.3)
#define	CLOUD_COVERAGE_FACTOR	(1.839E-8)	/* Km2/kg                   */
#define EARTH_WATER_MASS_PER_AREA	(3.83E15)/* grams per square km     */
#define	EARTH_SURF_PRES_IN_MILLIBARS	 (1000.0)
#define EARTH_CONVECTION_FACTOR	(0.43)		/* from Hart, eq.20         */
#define FREEZING_POINT_OF_WATER	(273.0)		/* Units of degrees Kelvin  */
#define DAYS_IN_A_YEAR		(365.256)	/* Earth days per Earth year*/
/*         gas_retention_threshold = 6.0;*/	/* ratio of esc vel to RMS vel */
#define GAS_RETENTION_THRESHOLD	(5.0)		/* ratio of esc vel to RMS vel */
#define GAS_GIANT_ALBEDO	(0.5)		/* albedo of a gas giant    */
#define CLOUD_ALBEDO		(0.52)
#define ROCKY_AIRLESS_ALBEDO	(0.07)
#define ROCKY_ALBEDO		(0.15)
#define WATER_ALBEDO		(0.04)
#define AIRLESS_ICE_ALBEDO	(0.5)
#define ICE_ALBEDO		(0.7)
#define SECONDS_PER_HOUR	(3600.0)
#define CM_PER_AU		(1.495978707E13)/* number of cm in an AU    */
#define CM_PER_KM		(1.0E5)		/* number of cm in a km     */
#define KM_PER_AU               (CM_PER_AU / CM_PER_KM)
#define CM_PER_METER		(100.0)
#define MILLIBARS_PER_BAR	(1000.0)
#define KELVIN_CELCIUS_DIFFERENCE	(273.0)
#define GRAV_CONSTANT		(6.672E-8)	/* units of dyne cm2/gram2  */
#define GREENHOUSE_EFFECT_CONST	(0.93)		/* affects inner radius..   */
#define MOLAR_GAS_CONST		(8314.41)	/* units: g*m2/(sec2*K*mol) */
#define K			(50.0)		/* K = gas/dust ratio       */
#define B			(1.2E-5)	/* Used in Crit_mass calc   */
#define DUST_DENSITY_COEFF	(2.0E-3)	/* A in Dole's paper        */
#define	ALPHA			(5.0)		/* Used in density calcs    */
#define	N			(3.0)		/* Used in density calcs    */
#define J			(1.46E-19)	/* Used in day-length calcs (cm2/sec2 g) */
#define INCREDIBLY_LARGE_NUMBER	(9.9999E37)


/*  Now for a few molecular weights (used for RMS velocity calcs):     */
/*  This table is from Dole's book "Habitable Planets for Man", p. 38  */

#define ATOMIC_HYDROGEN		(1.0)	/* H   */
#define MOL_HYDROGEN		(2.0)	/* H2  */
#define HELIUM			(4.0)	/* He  */
#define ATOMIC_NITROGEN		(14.0)	/* N   */
#define ATOMIC_OXYGEN		(16.0)	/* O   */
#define METHANE			(16.0)	/* CH4 */
#define AMMONIA			(17.0)	/* NH3 */
#define WATER_VAPOR		(18.0)	/* H2O */
#define NEON			(20.2)	/* Ne  */
#define MOL_NITROGEN		(28.0)	/* N2  */
#define CARBON_MONOXIDE		(28.0)	/* CO  */
#define NITRIC_OXIDE		(30.0)	/* NO  */
#define MOL_OXYGEN		(32.0)	/* O2  */
#define HYDROGEN_SULPHIDE	(34.1)	/* H2S */
#define ARGON			(39.9)	/* Ar  */
#define CARBON_DIOXIDE		(44.0)	/* CO2 */
#define NITROUS_OXIDE		(44.0)	/* N2O */
#define NITROGEN_DIOXIDE	(46.0)	/* NO2 */
#define OZONE			(48.0)	/* O3  */
#define SULPH_DIOXIDE		(64.1)	/* SO2 */
#define SULPH_TRIOXIDE		(80.1)	/* SO3 */
#define KRYPTON			(83.8)	/* Kr  */
#define XENON			(131.3)	/* Xe  */

/*  The following defines are used in the kothari_radius function in	*/
/*  file enviro.c.							*/
#define	A1_20			(6.485E12)	/* All units are in cgs system.  */
#define A2_20			(4.0032E-8)	/*   ie: cm, g, dynes, etc.      */
#define BETA_20			(5.71E12)


/*   The following defines are used in determining the fraction of a planet  */
/*  covered with clouds in function cloud_fraction in file enviro.c.	     */
#define	Q1_36			(1.258E19)	/* grams    */
#define Q2_36			(0.0698)	/* 1/Kelvin */

/* macros: */
#define	pow2(a)	((a) * (a))
#define	pow3(a)	((a) * (a) * (a))
#define	pow1_4(a)	sqrt(sqrt(a))

@EOF
set `sum $sumopt <const.h`; if test $1 -ne 39324
then
	echo ERROR: const.h checksum is $1 should be 39324
fi
set `wc -lwc <const.h`
if test $1$2$3 != 1026054468
then
	echo ERROR: wc results of const.h are $* should be 102 605 4468
fi

chmod 644 const.h

echo x - structs.h
cat >structs.h <<'@EOF'
typedef struct dust_record  *dust_pointer;
typedef struct planets_record  *planet_pointer;

typedef struct planets_record {
    double a;			/* semi-major axis of the orbit (in AU)*/
    double e;			/* eccentricity of the orbit	     */
    double mass;		/* mass (in solar masses)	     */
    int gas_giant;		/* TRUE if the planet is a gas giant */
    int orbit_zone;             /* the 'zone' of the planet          */
    double radius;		/* equatorial radius (in km)	     */
    double density;		/* density (in g/cc)		     */
    double orb_period;   	/* length of the local year (days)   */
    double day;			/* length of the local day (hours)   */
    int resonant_period;	/* TRUE if in resonant rotation   */
    int axial_tilt;		/* units of degrees		     */
    double esc_velocity;	/* units of cm/sec		     */
    double surf_accel;  	/* units of cm/sec2		     */
    double surf_grav;   	/* units of Earth gravities	     */
    double rms_velocity;	/* units of cm/sec		     */
    double molec_weight;	/* smallest molecular weight retained*/
    double volatile_gas_inventory;
    double surf_pressure;	/* units of millibars (mb)	     */
    int greenhouse_effect;	/* runaway greenhouse effect?	*/
    double boil_point;		/* the boiling point of water (Kelvin)*/
    double albedo;		/* albedo of the planet		     */
    double surf_temp;   	/* surface temperature in Kelvin     */
    double hydrosphere;		/* fraction of surface covered	     */
    double cloud_cover;		/* fraction of surface covered	     */
    double ice_cover;		/* fraction of surface covered	     */
#ifdef	MOON
    planet_pointer first_moon;
#endif	/* MOON */
    planet_pointer next_planet;
    } planets;


typedef struct dust_record {
	  double inner_edge;
	  double outer_edge;
	  int dust_present;
	  int gas_present;
	  dust_pointer next_band;
     } dust;

@EOF
set `sum $sumopt <structs.h`; if test $1 -ne 56459
then
	echo ERROR: structs.h checksum is $1 should be 56459
fi
set `wc -lwc <structs.h`
if test $1$2$3 != 442401843
then
	echo ERROR: wc results of structs.h are $* should be 44 240 1843
fi

chmod 644 structs.h

exit 0

