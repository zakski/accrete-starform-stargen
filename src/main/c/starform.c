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

