#define VERBOSE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "structs.h"

/*  These are all of the global variables used during accretion:  */
extern float anum;
extern planet_pointer planet_head;
extern double stellar_mass_ratio, stellar_luminosity_ratio, main_seq_life;
extern double age, r_ecosphere, r_greenhouse;
extern int spin_resonance;


double
	luminosity(double mass_ratio),
//	volume_radius(double mass, double density),
	kothari_radius(double mass, double orbital_radius, int giant, int zone),
	empirical_density(double mass, double orbital_radius, int gas_giant),
//	volume_density(double mass, double equatorial_radius),
//	period(double separation, double small_mass, double large_mass),
	day_length(double mass, double radius, double orbital_period,double eccentricity, int giant),
//	escape_vel(double mass, double radius),
//	rms_vel(double molecular_weight, double orbital_radius),
//	molecule_limit(double orbital_radius, double mass, double equatorial_radius),
	vol_inventory(double mass, double escape_vel, double rms_vel,double stellar_mass, int zone, int greenhouse_effect),
//	pressure(double volatile_gas_inventory, double equatorial_radius, double gravity),
//	boiling_point(double surface_pressure),
//	hydrosphere_fraction(double volatile_gas_inventory, double planetary_radius),
	cloud_fraction(double surface_temp, double smallest_MW_retained,double equatorial_radius, double hydrosphere_fraction),
	ice_fraction(double hydrosphere_fraction, double surface_temp),
//	green_rise(double optical_depth, double effective_temp, double surface_pressure),
	planet_albedo(double water_fraction, double cloud_fraction,double ice_fraction, double surface_pressure),
	opacity(double molecular_weight, double surface_pressure),
	collect_dust(double last_mass, double a, double e, double crit_mass,dust_pointer dust_band),
	critical_limit(double orbital_radius, double eccentricity,double stellar_luminosity_ratio);

int
	orbital_zone(double orbital_radius),
//	inclination(double orbital_radius),
	dust_available(double inside_range, double outside_range);

void
	iterate_surface_temp(planets_record &planet),
	generate_stellar_system(void),
	display_system(void),
	set_initial_conditions(double inner_limit_of_dust, double outer_limit_of_dust),
	update_dust_lanes(double min, double max, double mass, double crit_mass,double body_inner_bound, double body_outer_bound),
	accrete_dust(double &seed_mass, double a, double e, double crit_mass, double body_inner_bound, double body_outer_bound),
	coalesce_planetesimals(double a, double e, double mass, double crit_mass,double stellar_luminosity_ratio,double body_inner_bound, double body_outer_bound);

planet_pointer
	distribute_planetary_masses(double stellar_mass_ratio,double stellar_luminosity_ratio, double inner_dust, double outer_dust),
	distribute_moon_masses(double planetary_mass, double stellar_luminosity_ratio,double planet_eccentricity, double inner_dust, double outer_dust);

// Globally used inline functions
/*----------------------------------------------------------------------*/
/*  This function returns a random real number between the specified    */
/* inner and outer bounds.                                              */
/*----------------------------------------------------------------------*/
inline double random_number(double inner, double outer)
{
	  double range = outer - inner;
	  return((((double)rand()) / (double)(RAND_MAX)) * range + inner);
}

/*----------------------------------------------------------------------*/
/*   This function returns a value within a certain variation of the    */
/*   exact value given it in 'value'.                                   */
/*----------------------------------------------------------------------*/
inline double about (double value, double variation)
{
	  return(value + (value * random_number(-variation,variation)));
}


