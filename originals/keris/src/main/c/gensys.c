
#include        <stddef.h>
#include	<stdlib.h>
#include	<stdio.h>
#include        <float.h>
#include        <math.h>
#include        <sys/types.h>
#include        <sys/timeb.h>

#ifdef MSDOS
#include        <malloc.h>
#endif

#include        "const.h"
#include        "structs.h"

#include "accrete.h"
#include "enviro.h"
#include "display.h"
#include "utils.h"
#include "steltype.h"
#include "data.h"

void 
init(void)
{
  struct timeb grap;
  long         seed;

  if (sf_f_seed)
  {
    seed = sf_f_seed;
  }
  else
  {
    ftime(&grap);
    seed = (long)grap.time * 1000 + grap.millitm;
  }
  (void)srand(seed);
  if (sf_f_lisp)
    printf("(Accrete (version %s) (seed 0x%.8lx))\n", "3.0", seed);
  else
    printf("Accrete - V%s; seed=0x%.8lx\n", "3.0", seed);
}

planet_pointer
generate_stellar_system(void)
{
  planet_pointer first_planet;
  planet_pointer planet;
  double      outer_dust_limit;

  star_mass_r = random_number(0.6, 1.3);	/* was 0.6, 1.3 */
  star_radius_r = about(pow(star_mass_r, 1.0 / 3.0), 0.05);
  /* for some unknown reason, only 3 digits wanted... */
  star_radius_r = floor(star_radius_r * 1000.0) / 1000.0;
  star_lum_r = luminosity(star_mass_r);
  /* luminosity is proportional to T^4 and to area of star */
  /* so temp is Tsol * 4th-root ( Lum / r^2 )              */
  star_temp = 5650 * sqrt(sqrt(star_lum_r) / star_radius_r);
  /* ignore fractional degrees */
  star_temp = floor(star_temp);
  sprintf(star_class, "%.16s", starFindClass(star_mass_r, star_temp));
  outer_dust_limit = stellar_dust_limit(star_mass_r);
  first_planet = dist_planetary_masses(star_mass_r, 
                                           star_lum_r, 
                                           0.0, outer_dust_limit);
  main_seq_life = 1.0E10 * (star_mass_r / star_lum_r);
  if (main_seq_life > 6.0E9)
    star_age = random_number(1.0E9, 6.0E9);
  else if (main_seq_life > 1.0E9)
    star_age = random_number(1.0E9, main_seq_life);
  else
    star_age = random_number(main_seq_life/10, main_seq_life);
  r_ecosphere = sqrt(star_lum_r);
  r_greenhouse = r_ecosphere * GREENHOUSE_EFFECT_CONST;
  for (planet = first_planet; planet != NULL; planet = planet->next_planet)
  {
    planet->orbit_zone = orb_zone(planet->a);
    if (planet->gas_giant)
    {
      planet->density = empirical_density(planet->mass, planet->a, 
                                          planet->gas_giant);
      planet->radius = volume_radius(planet->mass, planet->density);
    }
    else
    {
      planet->radius = kothari_radius(planet->mass, planet->gas_giant, 
                                      planet->orbit_zone);
      planet->density = volume_density(planet->mass, planet->radius);
    }
    planet->orb_period = period(planet->a, planet->mass, star_mass_r);
    planet->day = day_length(planet->mass, planet->radius, planet->e,
			     planet->density, planet->a,
			     planet->orb_period, planet->gas_giant,
			     star_mass_r);
    planet->resonant_period = resonance;
    planet->axial_tilt = inclination(planet->a);
    planet->esc_velocity = escape_vel(planet->mass, planet->radius);
    planet->surf_accel = acceleration(planet->mass, planet->radius);
    planet->rms_velocity = rms_vel(MOL_NITROGEN, planet->a);
    planet->molec_weight = molecule_limit(planet->mass, planet->radius);
    if ((planet->gas_giant))
    {
      planet->surf_grav = INCREDIBLY_LARGE_NUMBER;
      planet->greenhouse_effect = FALSE;
      planet->volatile_gas_inventory = INCREDIBLY_LARGE_NUMBER;
      planet->surf_pressure = INCREDIBLY_LARGE_NUMBER;
      planet->boil_point = INCREDIBLY_LARGE_NUMBER;
      planet->hydrosphere = INCREDIBLY_LARGE_NUMBER;
      planet->albedo = about(GAS_GIANT_ALBEDO, 0.1);
      planet->surf_temp = INCREDIBLY_LARGE_NUMBER;
    }
    else
    {
      planet->surf_grav = gravity(planet->surf_accel);
      planet->greenhouse_effect = grnhouse(planet->orbit_zone, planet->a, 
                                           r_greenhouse);
      planet->volatile_gas_inventory = vol_inventory(planet->mass, 
                                                     planet->esc_velocity, 
                                                     planet->rms_velocity, 
                                                     star_mass_r, 
                                                     planet->orbit_zone, 
                                                     planet->greenhouse_effect);
      planet->surf_pressure = pressure(planet->volatile_gas_inventory, 
                                       planet->radius, planet->surf_grav);
      if ((planet->surf_pressure == 0.0))
	planet->boil_point = 0.0;
      else
	planet->boil_point = boiling_point(planet->surf_pressure);
      iterate_surface_temp(&(planet));
    }
#ifdef	MOON
    if (sf_f_moon)
    {
#ifdef  PROPER_MOON
      planet->first_moon = dist_moon_masses(planet->mass,
					    star_lum_r, planet->e,
					    0.0, planet_dust_limit(planet->mass));
#else
      planet->first_moon = do_dist_moon_masses(planet->mass, planet->radius);
      {
	planet_pointer moon = planet->first_moon;

	while (moon)
	{
	  moon->radius = kothari_radius(moon->mass, 0, planet->orbit_zone);
	  moon->density = volume_density(moon->mass, moon->radius);
	  moon->density = random_number(1.5, moon->density * 1.1);
	  if (moon->density < 1.5)
	    moon->density = 1.5;
	  moon->radius = volume_radius(moon->mass, moon->density);
	  moon->orb_period = period(moon->a, moon->mass, planet->mass);
	  moon->day = day_length(moon->mass, moon->radius, moon->e,
				 moon->density, moon->a,
				 moon->orb_period, moon->gas_giant,
				 planet->mass);
	  moon->resonant_period = resonance;
	  moon->axial_tilt = inclination(moon->a);
	  moon->esc_velocity = escape_vel(moon->mass, moon->radius);
	  moon->surf_accel = acceleration(moon->mass, moon->radius);
	  moon->rms_velocity = rms_vel(MOL_NITROGEN, planet->a);
	  moon->molec_weight = molecule_limit(moon->mass, moon->radius);
	  moon->surf_grav = gravity(moon->surf_accel);
	  moon->greenhouse_effect = grnhouse(planet->orbit_zone,
					     planet->a,
					     r_greenhouse);
	  moon->volatile_gas_inventory = vol_inventory(moon->mass,
						       moon->esc_velocity,
						       moon->rms_velocity,
						       star_mass_r,
						       planet->orbit_zone,
						  moon->greenhouse_effect);
	  moon->surf_pressure = pressure(moon->volatile_gas_inventory,
					 moon->radius, moon->surf_grav);
	  if ((moon->surf_pressure == 0.0))
	    moon->boil_point = 0.0;
	  else
	    moon->boil_point = boiling_point(moon->surf_pressure);
	  iterate_surface_temp_moon(&planet, &moon);
	  moon = moon->next_planet;
	}
      }
#endif				/* CC_MOON */
    }
#endif				/* MOON */
  }
  return first_planet;
}

