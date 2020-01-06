#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "const.h"
#include "structs.h"

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

int orbital_zone(orbital_radius)
double orbital_radius;
{
     if (orbital_radius < (4.0 * sqrt(stellar_luminosity_ratio)))
	  return(1);
     else
     {
	  if ((orbital_radius >= (4.0 * sqrt(stellar_luminosity_ratio))) && (orbital_radius < (15.0 * sqrt(stellar_luminosity_ratio))))
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
/*    Returns the radius of the planet in kilometers.                       */
/*   The mass passed in is in units of solar masses, the orbital radius     */
/*   in A.U.                                                                */
/*   This formula is listed as eq.9 in Fogg's article, although some typos  */
/*   crop up in that eq.  See "The Internal Constitution of Planets", by    */
/*   Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 */
/*   pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  */
/*   eq.23, which appears on page 840.                                      */
/*--------------------------------------------------------------------------*/

double kothari_radius(mass, orbital_radius, giant, zone)
double mass, orbital_radius;
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
     temp2 = temp2 / (A1_20 * pow(atomic_num, 2.0));
     temp2 = 1.0 + temp2;
     temp = temp / temp2;
     temp = (temp * pow(mass,(1.0 / 3.0))) / CM_PER_KM;
     return(temp);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the orbital radius  */
/*  is in units of AU.  The density is returned in units of grams/cc.       */
/*--------------------------------------------------------------------------*/

double empirical_density(mass, orbital_radius, gas_giant)
double mass, orbital_radius;
int gas_giant;
{
     double temp;

     temp = pow(mass * EARTH_MASSES_PER_SOLAR_MASS,(1.0 / 8.0));
     temp = temp * pow(r_ecosphere / orbital_radius,(1.0 / 4.0));
     if (gas_giant)
	  return(temp * 1.2);
     else
	  return(temp * 5.5);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/

double volume_density(mass, equatorial_radius)
double mass, equatorial_radius;
{
     double volume;

     mass = mass * SOLAR_MASS_IN_GRAMS;
     equatorial_radius = equatorial_radius * CM_PER_KM;
     volume = (4.0 * PI * pow(equatorial_radius,3.0)) / 3.0;
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

     period_in_years = sqrt(pow(separation,3.0) / (small_mass + large_mass));
     return(period_in_years * DAYS_IN_A_YEAR);
}


/*--------------------------------------------------------------------------*/
/*   Fogg's information for this routine came from Dole "Habitable Planets  */
/* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    */
/* up with his eq.12, which is the equation for the base_angular_velocity   */
/* below.  Going a bit further, he found an equation for the change in      */
/* angular velocity per time (dw/dt) from P. Goldreich and S. Soter's paper */
/* "Q in the Solar System" in Icarus, vol 5, pp.375-389 (1966).  Comparing  */
/* to the change in angular velocity for the Earth, we can come up with an  */
/* approximation for our new planet (his eq.13) and take that into account. */
/*--------------------------------------------------------------------------*/

double day_length(mass, radius, orbital_period, eccentricity, giant)
double mass, radius, orbital_period, eccentricity;
int giant;
{
     double base_angular_velocity, planetary_mass_in_grams, k2, temp,
     equatorial_radius_in_cm, change_in_angular_velocity, spin_resonance_period;

     spin_resonance = FALSE;
     if (giant)
	  k2 = 0.24;
     else
	  k2 = 0.33;
     planetary_mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
     equatorial_radius_in_cm = radius * CM_PER_KM;
     base_angular_velocity = sqrt(2.0 * J * (planetary_mass_in_grams) / (k2 * pow(equatorial_radius_in_cm, 2.0)));
     /*   This next term describes how much a planet's rotation is slowed by    */
     /*  it's moons.  Find out what dw/dt is after figuring out Goldreich and   */
     /*  Soter's Q'.                                                            */
     change_in_angular_velocity = 0.0;
     temp = base_angular_velocity + (change_in_angular_velocity * age);
     /*   'temp' is now the angular velocity. Now we change from rad/sec to     */
     /*  hours/rotation.							   */
     temp = 1.0 / ((temp / radians_per_rotation) * SECONDS_PER_HOUR);
     if (temp >= orbital_period)
     {
	  spin_resonance_period = ((1.0 - eccentricity) / (1.0 + eccentricity)) * orbital_period;
	  if (eccentricity > 0.1)
	  {
	       temp = spin_resonance_period;
	       spin_resonance = TRUE;
	  }
	  else
	       temp = orbital_period;
     }
     return(temp);
}


/*--------------------------------------------------------------------------*/
/*   The orbital radius is expected in units of Astronomical Units (AU).    */
/*   Inclination is returned in units of degrees.                           */
/*--------------------------------------------------------------------------*/

int inclination(orbital_radius)
double orbital_radius;
{
     int temp;

     temp = (int)(pow(orbital_radius,0.2) * about(EARTH_AXIAL_TILT,0.4));
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
/*  is used as the basis of the Root Mean Square velocity of the molecule   */
/*  or atom.  The velocity returned is in cm/sec.                           */
/*--------------------------------------------------------------------------*/

double rms_vel(molecular_weight, orbital_radius)
double molecular_weight, orbital_radius;
{
     double exospheric_temp;

     exospheric_temp = EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0);
     return(sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight) * CM_PER_METER);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the smallest molecular weight retained by the    */
/*  body, which is useful for determining the atmosphere composition.       */
/*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  *)
    (*  mass is in units of solar masses, and equatorial radius is in units of  */
/*  kilometers.                                                             */
/*--------------------------------------------------------------------------*/

double molecule_limit(orbital_radius, mass, equatorial_radius)
double orbital_radius, mass, equatorial_radius;
{
     double numerator, denominator1, denominator2, escape_velocity, temp;

     escape_velocity = escape_vel(mass,equatorial_radius);
     return((3.0 * pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow(escape_velocity, 2.0));
}


/*--------------------------------------------------------------------------*/
/*   This function calculates the surface acceleration of a planet.  The    */
/*  mass is in units of solar masses, the radius in terms of km, and the    */
/*  acceleration is returned in units of cm/sec2.                           */
/*--------------------------------------------------------------------------*/

double acceleration(mass, radius)
double mass, radius;
{
     return(GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / pow(radius * CM_PER_KM, 2.0));
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

int greenhouse(zone, orbital_radius, greenhouse_radius)
int zone;
double orbital_radius, greenhouse_radius;
{
     if ((orbital_radius < greenhouse_radius) && (zone == 1))
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
     double velocity_ratio, proportion_const, temp1, temp2, mass_in_earth_units;

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
	  mass_in_earth_units = mass * EARTH_MASSES_PER_SOLAR_MASS;
	  temp1 = (proportion_const * mass_in_earth_units) / stellar_mass;
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

double pressure(volatile_gas_inventory, equatorial_radius, gravity)
double volatile_gas_inventory, equatorial_radius, gravity;
{
     equatorial_radius = EARTH_RADIUS_IN_KM / equatorial_radius;
     return(volatile_gas_inventory * gravity / pow(equatorial_radius, 2.0));
}

/*--------------------------------------------------------------------------*/
/*   This function returns the boiling point of water in an atmosphere of   */
/*   pressure 'surface_pressure', given in millibars.  The boiling point is */
/*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
/*--------------------------------------------------------------------------*/

double boiling_point(surface_pressure)
double surface_pressure;
{
     double surface_pressure_in_bars;

     surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;
     return(1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
}


/*--------------------------------------------------------------------------*/
/*   This function is Fogg's eq.22.  Given the volatile gas inventory and   */
/*   planetary radius of a planet (in Km), this function returns the        */
/*   fraction of the planet covered with water.                             */
/*   I have changed the function very slightly:  the fraction of Earth's    */
/*   surface covered by water is 71%, not 75% as Fogg used.                 */
/*--------------------------------------------------------------------------*/

double hydrosphere_fraction(volatile_gas_inventory, planetary_radius)
double volatile_gas_inventory, planetary_radius;
{
     double temp;

     temp = (0.71 * volatile_gas_inventory / 1000.0) * pow(EARTH_RADIUS_IN_KM / planetary_radius, 2.0);
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

double cloud_fraction(surface_temp, smallest_MW_retained, equatorial_radius, hydrosphere_fraction)
double surface_temp, smallest_MW_retained, equatorial_radius,
     hydrosphere_fraction;
{
     double water_vapor_in_kg, fraction, surface_area, hydrosphere_mass;

     if (smallest_MW_retained > WATER_VAPOR)
	  return(0.0);
     else
     {
	  surface_area = 4.0 * PI * pow(equatorial_radius, 2.0);
	  hydrosphere_mass = hydrosphere_fraction * surface_area * EARTH_WATER_MASS_PER_AREA;
	  water_vapor_in_kg = (0.00000001 * hydrosphere_mass) * exp(Q2_36 * (surface_temp - 288.0));
	  fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surface_area;
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

double ice_fraction(hydrosphere_fraction, surface_temp)
double hydrosphere_fraction, surface_temp;
{
     double temp;

     if (surface_temp > 328.0)
	  surface_temp = 328.0;
     temp = pow(((328.0 - surface_temp) / 90.0),5.0);
     if (temp > (1.5 * hydrosphere_fraction))
	  temp = (1.5 * hydrosphere_fraction);
     if (temp >= 1.0)
	  return(1.0);
     else
	  return(temp);
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital */
/*  radius in AU, and the temperature returned is in Kelvin.		    */
/*--------------------------------------------------------------------------*/

double eff_temp(ecosphere_radius, orbital_radius, albedo)
double ecosphere_radius, orbital_radius, albedo;
{
     return(sqrt(ecosphere_radius / orbital_radius) * pow((1.0 - albedo) / 0.7,0.25) * EARTH_EFFECTIVE_TEMP);
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
/*  Earth's Atmosphere" article.  The effective temperature given is in     */
/*  units of Kelvin, as is the rise in temperature produced by the          */
/*  greenhouse effect, which is returned.                                   */
/*--------------------------------------------------------------------------*/

double green_rise(optical_depth, effective_temp, surface_pressure)
double optical_depth, effective_temp, surface_pressure;
{
     double convection_factor;

     convection_factor = EARTH_CONVECTION_FACTOR * pow((surface_pressure / EARTH_SURF_PRES_IN_MILLIBARS),0.25);
     return(pow((1.0 + 0.75 * optical_depth),0.25) - 1.0) * effective_temp * convection_factor;
}


/*--------------------------------------------------------------------------*/
/*   The surface temperature passed in is in units of Kelvin.               */
/*   The cloud adjustment is the fraction of cloud cover obscuring each     */
/*   of the three major components of albedo that lie below the clouds.     */
/*--------------------------------------------------------------------------*/

double planet_albedo(water_fraction, cloud_fraction, ice_fraction, surface_pressure)
double water_fraction, cloud_fraction, ice_fraction, surface_pressure;
{
     double rock_fraction, cloud_adjustment, components, cloud_contribution,
     rock_contribution, water_contribution, ice_contribution;

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
     cloud_contribution = cloud_fraction * about(CLOUD_ALBEDO,0.2);
     if (surface_pressure == 0.0)
	  rock_contribution = rock_fraction * about(AIRLESS_ROCKY_ALBEDO,0.3);
     else
	  rock_contribution = rock_fraction * about(ROCKY_ALBEDO,0.1);
     water_contribution = water_fraction * about(WATER_ALBEDO,0.2);
     if (surface_pressure == 0.0)
	  ice_contribution = ice_fraction * about(AIRLESS_ICE_ALBEDO,0.4);
     else
	  ice_contribution = ice_fraction * about(ICE_ALBEDO,0.1);
     return(cloud_contribution + rock_contribution + water_contribution + ice_contribution);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the dimensionless quantity of optical depth,     */
/*   which is useful in determining the amount of greenhouse effect on a    */
/*   planet.                                                                */
/*--------------------------------------------------------------------------*/

double opacity(molecular_weight, surface_pressure)
double molecular_weight, surface_pressure;
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
     if (surface_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	  optical_depth = optical_depth * 8.333;
     else
	  if (surface_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	       optical_depth = optical_depth * 6.666;
	  else
	       if (surface_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS))
		    optical_depth = optical_depth * 3.333;
	       else
		    if (surface_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS))
			 optical_depth = optical_depth * 2.0;
		    else
			 if (surface_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS))
			      optical_depth = optical_depth * 1.5;
     return(optical_depth);
}


/*--------------------------------------------------------------------------*/
/*   The temperature calculated is in degrees Kelvin.                       */
/*   Quantities already known which are used in these calculations:         */
/*	 planet->molecule_weight					    */
/*	 planet->surface_pressure					    */
/*       R_ecosphere                                                        */
/*	 planet->a							    */
/*	 planet->volatile_gas_inventory					    */
/*	 planet->radius							    */
/*	 planet->boil_point						    */
/*--------------------------------------------------------------------------*/

void iterate_surface_temp(planet)
planet_pointer *planet;
{
     double surface_temp, effective_temp, greenhouse_rise, previous_temp,
     optical_depth, albedo, water, clouds, ice;

     optical_depth = opacity((*planet)->molecule_weight,(*planet)->surface_pressure);
     effective_temp = eff_temp(r_ecosphere,(*planet)->a,EARTH_ALBEDO);
     greenhouse_rise = green_rise(optical_depth,effective_temp,(*planet)->surface_pressure);
     surface_temp = effective_temp + greenhouse_rise;
     previous_temp = surface_temp - 5.0;		/* force the while loop the first time */
     while ((fabs(surface_temp - previous_temp) > 1.0)) {
	       previous_temp = surface_temp;
	       water = hydrosphere_fraction((*planet)->volatile_gas_inventory,(*planet)->radius);
	       clouds = cloud_fraction(surface_temp,(*planet)->molecule_weight,(*planet)->radius,water);
	       ice = ice_fraction(water,surface_temp);
	       if ((surface_temp >= (*planet)->boil_point) || (surface_temp <= FREEZING_POINT_OF_WATER))
		    water = 0.0;
	       albedo = planet_albedo(water,clouds,ice,(*planet)->surface_pressure);
	       optical_depth = opacity((*planet)->molecule_weight,(*planet)->surface_pressure);
	       effective_temp = eff_temp(r_ecosphere,(*planet)->a,albedo);
	       greenhouse_rise = green_rise(optical_depth,effective_temp,(*planet)->surface_pressure);
	       surface_temp = effective_temp + greenhouse_rise;
	  }
     (*planet)->hydrosphere = water;
     (*planet)->cloud_cover = clouds;
     (*planet)->ice_cover = ice;
     (*planet)->albedo = albedo;
     (*planet)->surface_temp = surface_temp;
}
