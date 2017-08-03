#define VERBOSE

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#include "fctn.h"

//  These are all of the global variables used during accretion:
float anum;
planet_pointer planet_head;
double stellar_mass_ratio, stellar_luminosity_ratio, main_seq_life;
double age, r_ecosphere, r_greenhouse, radians_per_rotation;
int spin_resonance;

// some inline functions dropped here/

/*--------------------------------------------------------------------------*/
/*   This function calculates the surface acceleration of a planet.  The    */
/*  mass is in units of solar masses, the radius in terms of km, and the    */
/*  acceleration is returned in units of cm/sec2.                           */
/*--------------------------------------------------------------------------*/
inline double acceleration(double mass, double radius)
{
	  return(GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / pow(radius * CM_PER_KM, 2.0));
}

/*--------------------------------------------------------------------------*/
/*   This function calculates the surface gravity of a planet.  The         */
/*  acceleration is in units of cm/sec2, and the gravity is returned in     */
/*  units of Earth gravities.                                               */
/*--------------------------------------------------------------------------*/
inline double gravity(double acceleration)
{
	  return(acceleration / EARTH_ACCELERATION);
}

/*--------------------------------------------------------------------------*/
/*  Note that if the orbital radius of the planet is greater than or equal  */
/*  to R_inner, 99% of it's volatiles are assumed to have been deposited in */
/*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
/*--------------------------------------------------------------------------*/
inline int greenhouse(int zone, double orbital_radius, double greenhouse_radius)
{
	return ((orbital_radius < greenhouse_radius) && (zone == 1));
}

inline double stellar_dust_limit(double stellar_mass_ratio)
{
	  return(200.0 * pow(stellar_mass_ratio,(1.0 / 3.0)));
}

inline double luminosity(double mass_ratio)
{
//	double n;
	double n = (mass_ratio < 1.0) ? (1.75 * (mass_ratio - 0.1) + 3.325) : (0.5 * (2.0 - mass_ratio) + 4.4);

//	if (mass_ratio < 1.0)
//		n = 1.75 * (mass_ratio - 0.1) + 3.325;
//	else
//		n = 0.5 * (2.0 - mass_ratio) + 4.4;

	return(pow(mass_ratio,n));
}


/*--------------------------------------------------------------------------*/
/*   The mass is in units of solar masses, and the density is in units      */
/*   of grams/cc.  The radius returned is in units of km.                   */
/*--------------------------------------------------------------------------*/
inline double volume_radius(double mass, double density)
{
//	double volume = mass * SOLAR_MASS_IN_GRAMS / density;

//	mass = mass * SOLAR_MASS_IN_GRAMS;
//	volume = mass * SOLAR_MASS_IN_GRAMS / density;
	return(pow((3.0 * mass * SOLAR_MASS_IN_GRAMS / density) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
//	return(pow((3.0 * volume) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/
inline double volume_density(double mass, double equatorial_radius)
{
//	double volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;

//	mass = mass * SOLAR_MASS_IN_GRAMS;
//	equatorial_radius = equatorial_radius * CM_PER_KM;
//	volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;
	return(mass*SOLAR_MASS_IN_GRAMS / ((4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0));
}


/*--------------------------------------------------------------------------*/
/*  The separation is in units of AU, and both masses are in units of solar */
/*  masses.  The period returned is in terms of Earth days.                 */
/*--------------------------------------------------------------------------*/
inline double period(double separation, double small_mass, double large_mass)
{
//	  double period_in_years;

//     period_in_years = sqrt(pow(separation,3.0) / (small_mass + large_mass));
	return(sqrt(pow(separation,3.0) / (small_mass + large_mass)) * DAYS_IN_A_YEAR);
}


/*--------------------------------------------------------------------------*/
/*   The orbital radius is expected in units of Astronomical Units (AU).    */
/*   Inclination is returned in units of degrees.                           */
/*--------------------------------------------------------------------------*/
inline int inclination(double orbital_radius)
{
//	int temp;

//	temp = (int)(pow(orbital_radius,0.2) * about(EARTH_AXIAL_TILT,0.4));
	return(((int)(pow(orbital_radius,0.2) * about(EARTH_AXIAL_TILT,0.4))) % 360);
}


/*--------------------------------------------------------------------------*/
/*   This function implements the escape velocity calculation.  Note that   */
/*  it appears that Fogg's eq.15 is incorrect.                              */
/*  The mass is in units of solar mass, the radius in kilometers, and the   */
/*  velocity returned is in cm/sec.                                         */
/*--------------------------------------------------------------------------*/
inline double escape_vel(double mass, double radius)
{
//	double
//		mass_in_grams = mass * SOLAR_MASS_IN_GRAMS,
//		radius_in_cm = radius * CM_PER_KM;

//	mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
//	radius_in_cm = radius * CM_PER_KM;

	return(sqrt(2.0 * GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / (radius * CM_PER_KM)));
//	return(sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm));
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.16.  The molecular weight (usually assumed to be N2)  */
/*  is used as the basis of the Root Mean Square velocity of the molecule   */
/*  or atom.  The velocity returned is in cm/sec.                           */
/*--------------------------------------------------------------------------*/
inline double rms_vel(double molecular_weight, double orbital_radius)
{
//	double
//		exospheric_temp= EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0);

//	exospheric_temp = EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0);
	return(sqrt((3.0 * MOLAR_GAS_CONST * (EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0))) / molecular_weight) * CM_PER_METER);
//	return(sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight) * CM_PER_METER);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the smallest molecular weight retained by the    */
/*  body, which is useful for determining the atmosphere composition.       */
/*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  */
/*  mass is in units of solar masses, and equatorial radius is in units of  */
/*  kilometers.                                                             */
/*--------------------------------------------------------------------------*/
inline double molecule_limit(double /*orbital_radius*/, double mass, double equatorial_radius)
{
//	double
//		numerator,
//		denominator1,
//		denominator2,
//		temp,
//		escape_velocity = escape_vel(mass,equatorial_radius);

//	escape_velocity = escape_vel(mass,equatorial_radius);
	return((3.0 * pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow(escape_vel(mass,equatorial_radius), 2.0));
//	return((3.0 * pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow(escape_velocity, 2.0));
}


/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.18.  The pressure returned is in units of     */
/*  millibars (mb).  The gravity is in units of Earth gravities, the radius */
/*  in units of kilometers.                                                 */
/*--------------------------------------------------------------------------*/
inline double pressure(double volatile_gas_inventory, double equatorial_radius, double gravity)
{
//	equatorial_radius = EARTH_RADIUS_IN_KM / equatorial_radius;
	return(volatile_gas_inventory * gravity / pow(EARTH_RADIUS_IN_KM/equatorial_radius, 2.0));
}


/*--------------------------------------------------------------------------*/
/*   This function returns the boiling point of water in an atmosphere of   */
/*   pressure 'surface_pressure', given in millibars.  The boiling point is */
/*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
/*--------------------------------------------------------------------------*/
inline double boiling_point(double surface_pressure)
{
//	double
//		surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;

//	surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;
	return(1.0 / (log(surface_pressure / MILLIBARS_PER_BAR) / -5050.5 + 1.0 / 373.0));
//	return(1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
}



void generate_stellar_system(void)
{
	planet_pointer planet;

	planet = distribute_planetary_masses(stellar_mass_ratio,stellar_luminosity_ratio,0.0,stellar_dust_limit(stellar_mass_ratio));
	main_seq_life = 1.0E10 * (stellar_mass_ratio / stellar_luminosity_ratio);
	if ((main_seq_life >= 6.0E9))
		age = random_number(1.0E9,6.0E9);
	else
		age = random_number(0.7*main_seq_life,main_seq_life);
	r_ecosphere = sqrt(stellar_luminosity_ratio);
	r_greenhouse = r_ecosphere * GREENHOUSE_EFFECT_CONST;
	while (planet != NULL)
	{
		planet->orbit_zone = orbital_zone(planet->a);
		if (planet->gas_giant)
		{
			planet->density = empirical_density(planet->mass,planet->a,planet->gas_giant);
			planet->radius = volume_radius(planet->mass,planet->density);
		}
		else
		{
			planet->radius = kothari_radius(planet->mass,planet->a,planet->gas_giant,planet->orbit_zone);
			planet->density = volume_density(planet->mass,planet->radius);
		}
		planet->orbital_period = period(planet->a,planet->mass,stellar_mass_ratio);
		planet->day = day_length(planet->mass,planet->radius,planet->orbital_period,planet->e,planet->gas_giant);
		planet->resonant_period = spin_resonance;
		planet->axial_tilt = inclination(planet->a);
		planet->escape_velocity = escape_vel(planet->mass,planet->radius);
		planet->surface_accel = acceleration(planet->mass,planet->radius);
		planet->rms_velocity = rms_vel(MOLECULAR_NITROGEN,planet->a);
		planet->molecule_weight = molecule_limit(planet->a,planet->mass,planet->radius);
		if ((planet->gas_giant))
		{
			planet->surface_grav = INCREDIBLY_LARGE_NUMBER;
			planet->greenhouse_effect = FALSE;
			planet->volatile_gas_inventory = INCREDIBLY_LARGE_NUMBER;
			planet->surface_pressure = INCREDIBLY_LARGE_NUMBER;
			planet->boil_point = INCREDIBLY_LARGE_NUMBER;
			planet->hydrosphere = INCREDIBLY_LARGE_NUMBER;
			planet->albedo = about(GAS_GIANT_ALBEDO,0.1);
			planet->surface_temp = INCREDIBLY_LARGE_NUMBER;
		}
		else
		{
			planet->surface_grav = gravity(planet->surface_accel);
			planet->greenhouse_effect = greenhouse(planet->orbit_zone,planet->a,r_greenhouse);
			planet->volatile_gas_inventory = vol_inventory(planet->mass,planet->escape_velocity,planet->rms_velocity,stellar_mass_ratio,planet->orbit_zone,planet->greenhouse_effect);
			planet->surface_pressure = pressure(planet->volatile_gas_inventory,planet->radius,planet->surface_grav);
			if ((planet->surface_pressure == 0.0))
				planet->boil_point = 0.0;
			else
				planet->boil_point = boiling_point(planet->surface_pressure);
			iterate_surface_temp(*planet);
		}
		planet = planet->next_planet;
	}
	display_system( );
}


void generate_star_data(void)
{
	char buf[16];
// create the star's information:  Can enter it manually!!!
	printf("Enter stellar mass (Sol = 1.0): ");
	stellar_mass_ratio=atof(gets(buf));
//	stellar_mass_ratio = random_number(0.6,1.3);
	printf("Enter stellar luminosity (Sol = 1.0): ");
   stellar_luminosity_ratio = atof(gets(buf));
//	stellar_luminosity_ratio = luminosity(stellar_mass_ratio);
}


void main(void)
{
	randomize();
	radians_per_rotation = 2.0 * PI;

	generate_star_data();
	generate_stellar_system();
}
