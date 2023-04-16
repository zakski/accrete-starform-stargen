#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

#include "gensys.h"
#include "structs.h"
#include "accrete.h"
#include "enviro.h"
#include "steltype.h"

void display_banner()
{
  printf("Accrete - V%s\n", "4.0");
}

// seed the random number generator with this random seed, or the current time
// if the random_seed is 0.
void setup_seed(stellar_system* system, unsigned long random_seed)
{
  if (random_seed == 0)
  {
    struct timeval time;
    gettimeofday(&time, NULL);
    random_seed = time.tv_sec * 1000 + time.tv_usec;
  }

  // seed the system random number generator
  srand(random_seed);
  
  // preserve the random seed in our stellar system
  system->random_seed = random_seed;
}

stellar_system* generate_stellar_system(unsigned long random_seed)
{
  planet* planet;
  double      outer_dust_limit;

  stellar_system *system = malloc(sizeof(stellar_system));
  system->first_planet = NULL;
  setup_seed(system, random_seed);

  system->star_mass_r = random_number(0.6, 1.3);  /* was 0.6, 1.3 */
  system->star_radius_r = about(pow(system->star_mass_r, 1.0 / 3.0), 0.05);
  /* for some unknown reason, only 3 digits wanted... */
  system->star_radius_r = floor(system->star_radius_r * 1000.0) / 1000.0;
  system->star_lum_r = luminosity(system->star_mass_r);
  /* luminosity is proportional to T^4 and to area of star */
  /* so temp is Tsol * 4th-root ( Lum / r^2 )              */
  system->star_temp = 5650 * sqrt(sqrt(system->star_lum_r) / system->star_radius_r);
  /* ignore fractional degrees */
  system->star_temp = floor(system->star_temp);
  sprintf(system->star_class, "%.16s", find_star_class(system->star_temp));
  outer_dust_limit = stellar_dust_limit(system->star_mass_r);
  system->first_planet = distribute_planetary_masses(system, 0.0, outer_dust_limit);
  system->main_seq_life = 1.0E10 * (system->star_mass_r / system->star_lum_r);
  if (system->main_seq_life > 6.0E9)
    system->star_age = random_number(1.0E9, 6.0E9);
  else if (system->main_seq_life > 1.0E9)
    system->star_age = random_number(1.0E9, system->main_seq_life);
  else
    system->star_age = random_number(system->main_seq_life/10, system->main_seq_life);
  system->r_ecosphere = sqrt(system->star_lum_r);
  system->r_greenhouse = system->r_ecosphere * GREENHOUSE_EFFECT_CONST;
  for (planet = system->first_planet; planet != NULL; planet = planet->next_planet)
  {
    planet->orbit_zone = orbital_zone(system, planet->a);
    if (planet->gas_giant)
    {
      planet->density = empirical_density(system, planet->mass, planet->a, 
                                          planet->gas_giant);
      planet->radius = volume_radius(planet->mass, planet->density);
    }
    else
    {
      planet->radius = kothari_radius(planet->mass, planet->gas_giant, 
                                      planet->orbit_zone);
      planet->density = volume_density(planet->mass, planet->radius);
    }
    planet->orb_period = period(planet->a, planet->mass, system->star_mass_r);
    planet->day = day_length(system, planet->mass, planet->radius, planet->e,
           planet->density, planet->a,
           planet->orb_period, planet->gas_giant,
           system->star_mass_r);
    planet->resonant_period = system->resonance;
    planet->axial_tilt = inclination(planet->a);
    planet->esc_velocity = escape_velocity(planet->mass, planet->radius);
    planet->surf_accel = acceleration(planet->mass, planet->radius);
    planet->rms_velocity = rms_velocity(system, MOL_NITROGEN, planet->a);
    planet->molec_weight = molecule_limit(planet->mass, planet->radius);
    if ((planet->gas_giant))
    {
      planet->surf_grav = INCREDIBLY_LARGE_NUMBER;
      planet->greenhouse_effect = false;
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
      planet->greenhouse_effect = greenhouse(planet->orbit_zone, planet->a, 
                                           system->r_greenhouse);
      planet->volatile_gas_inventory = vol_inventory(planet->mass, 
                                                     planet->esc_velocity, 
                                                     planet->rms_velocity, 
                                                     system->star_mass_r, 
                                                     planet->orbit_zone, 
                                                     planet->greenhouse_effect);
      planet->surf_pressure = pressure(planet->volatile_gas_inventory, 
                                       planet->radius, planet->surf_grav);
      if (planet->surf_pressure == 0.0)
        planet->boil_point = 0.0;
      else
        planet->boil_point = boiling_point(planet->surf_pressure);
      iterate_surface_temp(system, &(planet));
    }
#ifdef  MOON
    if (args.make_moon)
    {
#ifdef  PROPER_MOON
      planet->first_moon = dist_moon_masses(planet->mass,
              star_lum_r, planet->e,
              0.0, planet_dust_limit(planet->mass));
#else
      planet->first_moon = do_dist_moon_masses(planet->mass, planet->radius);
      {
  planet* moon = planet->first_moon;

  while (moon)
  {
    moon->radius = kothari_radius(moon->mass, 0, planet->orbit_zone);
    moon->density = volume_density(moon->mass, moon->radius);
    moon->density = random_number(1.5, moon->density * 1.1);
    if (moon->density < 1.5)
      moon->density = 1.5;
    moon->radius = volume_radius(moon->mass, moon->density);
    moon->orb_period = period(moon->a, moon->mass, planet->mass);
    moon->day = day_length(system, moon->mass, moon->radius, moon->e,
         moon->density, moon->a,
         moon->orb_period, moon->gas_giant,
         planet->mass);
    moon->resonant_period = system->resonance;
    moon->axial_tilt = inclination(moon->a);
    moon->esc_velocity = escape_vel(moon->mass, moon->radius);
    moon->surf_accel = acceleration(moon->mass, moon->radius);
    moon->rms_velocity = rms_vel(system, MOL_NITROGEN, planet->a);
    moon->molec_weight = molecule_limit(moon->mass, moon->radius);
    moon->surf_grav = gravity(moon->surf_accel);
    moon->greenhouse_effect = grnhouse(planet->orbit_zone,
               planet->a,
               system->r_greenhouse);
    moon->volatile_gas_inventory = vol_inventory(moon->mass,
                   moon->esc_velocity,
                   moon->rms_velocity,
                   system->star_mass_r,
                   planet->orbit_zone,
              moon->greenhouse_effect);
    moon->surf_pressure = pressure(moon->volatile_gas_inventory,
           moon->radius, moon->surf_grav);
    if ((moon->surf_pressure == 0.0))
      moon->boil_point = 0.0;
    else
      moon->boil_point = boiling_point(moon->surf_pressure);
    iterate_surface_temp_moon(system, &planet, &moon);
    moon = moon->next_planet;
  }
      }
#endif        /* CC_MOON */
    }
#endif        /* MOON */
  }
  return system;
}

void free_stellar_system(stellar_system* system)
{
  // first, free all the planets
  planet *p, *q = NULL;
  for (p = system->first_planet;
       p != NULL; 
       p = q)
  {
    q = p->next_planet;
    free(p);
  }
  
  // now, free the system
  free(system);
}
