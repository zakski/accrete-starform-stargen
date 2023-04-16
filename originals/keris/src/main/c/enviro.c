#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "const.h"
#include "structs.h"
#include "utils.h"
#include "enviro.h"

double luminosity(double mass_ratio)
{
  double      n;

  if (mass_ratio < 1.0)
    n = 1.75 * (mass_ratio - 0.1) + 3.325;
  else
    n = 0.5 * (2.0 - mass_ratio) + 4.4;
  
  return pow(mass_ratio, n);
}

/*--------------------------------------------------------------------------*/
/*   This function, given the orbital radius of a planet in AU, returns     */
/*   the orbital 'zone' of the particle.                                    */
/*--------------------------------------------------------------------------*/

int orbital_zone(stellar_system* system, double orbital_radius)
{
  if (orbital_radius < (4.0 * sqrt(system->star_lum_r)))
    return 1;

  if (orbital_radius >= 4.0 * sqrt(system->star_lum_r) && 
      orbital_radius < 15.0 * sqrt(system->star_lum_r))
    return 2;

  return 3;
}

/*--------------------------------------------------------------------------*/
/*   The mass is in units of solar masses, and the density is in units      */
/*   of grams/cc.  The radius returned is in units of km.                   */
/*--------------------------------------------------------------------------*/

double volume_radius(double mass, double density)
{
  double      volume;

  mass = mass * SOLAR_MASS_IN_GRAMS;
  volume = mass / density;
  return pow((3.0 * volume) / (4.0 * PI), (1.0 / 3.0)) / CM_PER_KM;
}

/*--------------------------------------------------------------------------*/
/*   Returns the radius of the planet in kilometers.                        */
/*   The mass passed in is in units of solar masses.                        */
/*   This formula is listed as eq.9 in Fogg's article, although some typos  */
/*   crop up in that eq.  See "The Internal Constitution of Planets", by    */
/*   Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 */
/*   pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  */
/*   eq.23, which appears on page 840.                                      */
/*--------------------------------------------------------------------------*/

double kothari_radius(double mass, bool giant, int zone)
{
  double temperature, temp2, atomic_weight, atomic_num;

  if (zone == 1)
  {
    atomic_weight = giant ? 9.5 : 15.0;
    atomic_num    = giant ? 4.5 :  8.0;
  }
  else if (zone == 2)
  {
    atomic_weight = giant ? 2.47 : 10.0;
    atomic_num    = giant ? 2.0  :  5.0;
  }
  else
  {
    atomic_weight = giant ? 7.0 : 10.0;
    atomic_num    = giant ? 4.0 :  5.0;
  }
  
  temperature = atomic_weight * atomic_num;
  temperature = (2.0 * BETA_20 * pow(SOLAR_MASS_IN_GRAMS, (1.0 / 3.0))) / 
         (A1_20 * pow(temperature, (1.0 / 3.0)));
  temp2 = A2_20 * pow(atomic_weight, (4.0 / 3.0)) * 
          pow(SOLAR_MASS_IN_GRAMS, (2.0 / 3.0));
  temp2 = temp2 * pow(mass, (2.0 / 3.0));
  temp2 = temp2 / (A1_20 * pow2(atomic_num));
  temp2 = 1.0 + temp2;
  temperature = temperature / temp2;
  temperature = (temperature * pow(mass, (1.0 / 3.0))) / CM_PER_KM;
  return temperature;
}

/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the orbital radius  */
/*  is in units of AU.  The density is returned in units of grams/cc.       */
/*--------------------------------------------------------------------------*/

double empirical_density(stellar_system* system, 
        double mass, double orb_radius, bool is_gas_giant)
{
  double temperature;

  temperature = pow(mass * SUN_MASS_IN_EARTH_MASSES, (1.0 / 8.0));
  temperature = temperature * pow1_4(system->r_ecosphere / orb_radius);
  
  return temperature * (is_gas_giant ? 1.2 : 5.5);
}

/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/

double volume_density(double mass, double equatorial_radius)
{
  double volume;

  mass = mass * SOLAR_MASS_IN_GRAMS;
  equatorial_radius = equatorial_radius * CM_PER_KM;
  volume = (4.0 * PI * pow3(equatorial_radius)) / 3.0;
  return mass / volume;
}

/*--------------------------------------------------------------------------*/
/*  The separation is in units of AU, and both masses are in units of solar */
/*  masses.  The period returned is in terms of Earth days.                 */
/*--------------------------------------------------------------------------*/

double period(double separation, double small_mass, double large_mass)
{
  double period_in_years;

  period_in_years = sqrt(pow3(separation) / (small_mass + large_mass));
  return period_in_years * DAYS_IN_A_YEAR;
}

/*--------------------------------------------------------------------------*/
/*   Fogg's information for this routine came from Dole "Habitable Planets  */
/* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    */
/* up with his eq.12, which is the equation for the 'base_angular_velocity' */
/* below.  He then used an equation for the change in angular velocity per  */
/* time (dw/dt) from P. Goldreich and S. Soter's paper "Q in the Solar      */
/* System" in Icarus, vol 5, pp.375-389 (1966).  Using as a comparison the  */
/* change in angular velocity for the Earth, Fogg has come up with an       */
/* approximation for our new planet (his eq.13) and take that into account. */
/* This is used to find 'change_in_angular_velocity' below.                 */
/*                                                                          */
/*   Input parameters are mass (in solar masses), radius (in Km), orbital   */
/* period (in days), orbital radius (in AU), density (in g/cc),             */
/* eccentricity, and whether it is a gas giant or not.                      */
/*   The length of the day is returned in units of hours.                   */
/*--------------------------------------------------------------------------*/

double day_length(stellar_system* system, 
        double mass, double radius, double eccentricity, 
        double density, double orb_radius, double orb_period, 
        bool is_gas_giant, double mass_ratio)
{
  double      base_angular_velocity;
  double      planetary_mass_in_grams;
  double      k2;
  double      ang_velocity;
  double      equatorial_radius_in_cm;
  double      change_in_angular_velocity;
  double      spin_resonance_factor;
  double      year_in_hours;
  double      day_in_hours;
  double      rel_mass;
  double      pow_ratio;
  int         stopped = false;

  system->resonance = false;
  k2 = is_gas_giant ? 0.24 : 0.33;
  pow_ratio = 2.0 + 2e-2 / sqrt(mass_ratio);
  planetary_mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
  rel_mass = EARTH_MASS_IN_GRAMS / planetary_mass_in_grams;
  equatorial_radius_in_cm = radius * CM_PER_KM;
  year_in_hours = orb_period * 24.0;
  base_angular_velocity = sqrt(2.0 * J * (planetary_mass_in_grams) /
             (k2 * pow2(equatorial_radius_in_cm)));
/*  This next calculation determines how much the planet's rotation is      */
/*  slowed by the presence of the star.                                     */
  change_in_angular_velocity = CHANGE_IN_EARTH_ANG_VEL *
      (density / EARTH_DENSITY) *
      (equatorial_radius_in_cm / EARTH_RADIUS) *
      (rel_mass) *
      pow(mass_ratio, pow_ratio) *
      (1.0 / pow(orb_radius, 6.0));
  ang_velocity = base_angular_velocity + (change_in_angular_velocity * system->star_age);
/* Now we change from rad/sec to hours/rotation.                            */
  if (ang_velocity <= 0.0)
  {
    day_in_hours = -1;
    stopped = true;
  }
  else
    day_in_hours = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * ang_velocity);
  
  if (stopped || day_in_hours >= year_in_hours)
  {
    if (eccentricity > 0.1)
    {
      spin_resonance_factor = (1.0 - eccentricity) / (1.0 + eccentricity);
      system->resonance = true;
      return spin_resonance_factor * year_in_hours;
    }

    return year_in_hours;
  }
  return day_in_hours;
}

/*--------------------------------------------------------------------------*/
/*   The orbital radius is expected in units of Astronomical Units (AU).    */
/*   Inclination is returned in units of degrees.                           */
/*--------------------------------------------------------------------------*/

int inclination(double orb_radius)
{
  int temperature;

  temperature = (int)(pow(orb_radius, 0.2) * about(EARTH_AXIAL_TILT, 0.4));
  return temperature % 360;
}

/*--------------------------------------------------------------------------*/
/*   This function implements the escape velocity calculation.  Note that   */
/*  it appears that Fogg's eq.15 is incorrect.                              */
/*  The mass is in units of solar mass, the radius in kilometers, and the   */
/*  velocity returned is in cm/sec.                                         */
/*--------------------------------------------------------------------------*/

double escape_velocity(double mass, double radius)
{
  double mass_in_grams, radius_in_cm;

  mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
  radius_in_cm = radius * CM_PER_KM;
  return sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm);
}

/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.16.  The molecular weight (usually assumed to be N2)  */
/*  is used as the basis of the Root Mean Square (RMS) velocity of the      */
/*  molecule or atom.  The velocity returned is in cm/sec.                  */
/*--------------------------------------------------------------------------*/

double rms_velocity(stellar_system* system, 
        double molecular_weight, double orb_radius)
{
  double exospheric_temp;

  exospheric_temp = EARTH_EXOSPHERE_TEMP / pow2(orb_radius);
  exospheric_temp *= sqrt(system->star_lum_r);
  return (sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight)
    * CM_PER_METER);
}

/*--------------------------------------------------------------------------*/
/*   This function returns the smallest molecular weight retained by the    */
/*  body, which is useful for determining the atmosphere composition.       */
/*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  */
/*  mass is in units of solar masses, and equatorial radius is in units of  */
/*  kilometers.                                                             */
/*--------------------------------------------------------------------------*/

double molecule_limit(double mass, double equat_radius)
{
  double esc_velocity;

  esc_velocity = escape_velocity(mass, equat_radius);
  return ((3.0 * pow2(GAS_RETENTION_THRESHOLD * CM_PER_METER) * 
     MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow2(esc_velocity));
}

/*--------------------------------------------------------------------------*/
/*   This function calculates the surface acceleration of a planet.  The    */
/*  mass is in units of solar masses, the radius in terms of km, and the    */
/*  acceleration is returned in units of cm/sec2.                           */
/*--------------------------------------------------------------------------*/

double acceleration(double mass, double radius)
{
  return (GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) /
    pow2(radius * CM_PER_KM));
}

/*--------------------------------------------------------------------------*/
/*   This function calculates the surface gravity of a planet.  The         */
/*  acceleration is in units of cm/sec2, and the gravity is returned in     */
/*  units of Earth gravities.                                               */
/*--------------------------------------------------------------------------*/

double gravity(double acceleration)
{
  return acceleration / EARTH_ACCELERATION;
}

/*--------------------------------------------------------------------------*/
/*  Note that if the orbital radius of the planet is greater than or equal  */
/*  to R_inner, 99% of it's volatiles are assumed to have been deposited in */
/*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
/*--------------------------------------------------------------------------*/

int greenhouse(int zone, double orb_radius, double r_greenhouse)
{
  return (orb_radius < r_greenhouse && zone == 1);
}

/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.17.  The 'inventory' returned is unitless.    */
/*--------------------------------------------------------------------------*/
double vol_inventory(double mass, double escape_vel, double rms_vel, 
        double stellar_mass, int zone, int greenhouse_effect)
{
  double velocity_ratio;
  double proportion_const;
  double temp1;
  double temp2;
  double earth_units;

  velocity_ratio = escape_vel / rms_vel;
  if (velocity_ratio >= GAS_RETENTION_THRESHOLD)
  {
    switch (zone)
    {
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
        return 0.0;
    }

    earth_units = mass * SUN_MASS_IN_EARTH_MASSES;

    temp1 = (proportion_const * earth_units) / stellar_mass;
    temp2 = about(temp1, 0.2);

    return greenhouse_effect ? temp2 : temp2 / 100.0;
  }

  return 0.0;
}

/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.18.  The pressure returned is in units of     */
/*  millibars (mb).  The gravity is in units of Earth gravities, the radius */
/*  in units of kilometers.                                                 */
/*--------------------------------------------------------------------------*/

double pressure(double volatile_gas_inventory,
        double equatorial_radius, 
        double gravity)
{
  equatorial_radius = KM_EARTH_RADIUS / equatorial_radius;
  return volatile_gas_inventory * gravity / pow2(equatorial_radius);
}

/*--------------------------------------------------------------------------*/
/*   This function returns the boiling point of water in an atmosphere of   */
/*   pressure 'surf_pressure', given in millibars.  The boiling point is    */
/*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
/*--------------------------------------------------------------------------*/

double boiling_point(double surf_pressure)
{
  double      surface_pressure_in_bars;

  surface_pressure_in_bars = surf_pressure / MILLIBARS_PER_BAR;
  return 1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0);
}

/*--------------------------------------------------------------------------*/
/*   This function is Fogg's eq.22.  Given the gas inventory and   */
/*   planetary radius of a planet (in Km), this function returns the        */
/*   fraction of the planet covered with water.                             */
/*   I have changed the function very slightly:  the fraction of Earth's    */
/*   surface covered by water is 71%, not 75% as Fogg used.                 */
/*--------------------------------------------------------------------------*/
double water_fraction(double volatile_gas_inventory, double planet_radius)
{
  double      temperature;

  temperature = (0.71 * volatile_gas_inventory / 1000.0) 
          * pow2(KM_EARTH_RADIUS / planet_radius);
  
  return (temperature >= 1.0) ? 1.0 : temperature;
}

/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  */
/*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     */
/*   This equation is Hart's eq.3.                                          */
/*   I have modified it slightly using constants and relationships from     */
/*   Glass's book "Introduction to Planetary Geology", p.46.                */
/*   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     */
/*   covered by one Kg. of cloud.                                           */
/*--------------------------------------------------------------------------*/

double cloud_fraction(double surf_temp, 
        double smallest_MW_retained, 
        double equatorial_radius, 
        double water_fraction)
{
  double water_vapor_in_kg, fraction, surf_area, hydro_mass;

  if (smallest_MW_retained > WATER_VAPOR)
    return 0.0;
  
  surf_area = 4.0 * PI * pow2(equatorial_radius);
  hydro_mass = water_fraction * surf_area * EARTH_WATER_MASS_PER_AREA;
  water_vapor_in_kg = (0.00000001 * hydro_mass) * 
                      exp(Q2_36 * (surf_temp - 288.0));

  fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surf_area;

  return (fraction >= 1.0) ? 1.0 : fraction;
}

/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of the planet's surface covered by ice.  This is  */
/*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. */
/*   I have changed a constant from 70 to 90 in order to bring it more in   */
/*   line with the fraction of the Earth's surface covered with ice, which  */
/*   is approximatly .016 (=1.6%).                                          */
/*--------------------------------------------------------------------------*/

double ice_fraction(double water_fraction, double surf_temp)
{
  double      temperature;

  if (surf_temp > 328.0)
    surf_temp = 328.0;
  
  temperature = pow(((328.0 - surf_temp) / 90.0), 5.0);
  
  if (temperature > (1.5 * water_fraction))
    temperature = (1.5 * water_fraction);
  
  return (temperature >= 1.0) ? 1.0 : temperature;
}

/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital */
/*  radius in AU, and the temperature returned is in Kelvin.                */
/*--------------------------------------------------------------------------*/

double eff_temp(double ecosphere_radius, double orb_radius, double albedo)
{
  return (sqrt(ecosphere_radius / orb_radius)
    * pow1_4((1.0 - albedo) / 0.7)
    * EARTH_EFFECTIVE_TEMP);
}

/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
/*  Earth's Atmosphere" article.  The effective temperature given is in     */
/*  units of Kelvin, as is the rise in temperature produced by the          */
/*  greenhouse effect, which is returned.                                   */
/*--------------------------------------------------------------------------*/

double green_rise(double optical_depth, 
        double effective_temp, 
        double surf_pressure)
{
  double      convection_factor;

  convection_factor = EARTH_CONVECTION_FACTOR 
          * pow1_4(surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS);
  
  return (pow1_4(1.0 + 0.75 * optical_depth) - 1.0) * effective_temp * convection_factor;
}

/*--------------------------------------------------------------------------*/
/*   The surface temperature passed in is in units of Kelvin.               */
/*   The cloud adjustment is the fraction of cloud cover obscuring each     */
/*   of the three major components of albedo that lie below the clouds.     */
/*--------------------------------------------------------------------------*/

double planet_albedo(double water_fraction, 
        double cloud_fraction, double ice_fraction, double surf_pressure)
{
  double rock_fraction, cloud_adjustment, components, cloud_part, 
         rock_part, water_part, ice_part;

  rock_fraction = 1.0 - water_fraction - ice_fraction;
  components = 0.0;
  
  if (water_fraction > 0.0)
    components += 1.0;
  
  if (ice_fraction > 0.0)
    components += 1.0;
  
  if (rock_fraction > 0.0)
    components += 1.0;
  
  cloud_adjustment = cloud_fraction / components;
  
  if (rock_fraction >= cloud_adjustment)
    rock_fraction -= cloud_adjustment;
  else
    rock_fraction = 0.0;
  
  if (water_fraction > cloud_adjustment)
    water_fraction -= cloud_adjustment;
  else
    water_fraction = 0.0;
  
  if (ice_fraction > cloud_adjustment)
    ice_fraction -= cloud_adjustment;
  else
    ice_fraction = 0.0;
  
  cloud_part = cloud_fraction * about(CLOUD_ALBEDO, 0.2);
  
  if (surf_pressure == 0.0)
    rock_part = rock_fraction * about(AIRLESS_ROCKY_ALBEDO, 0.3);
  else
    rock_part = rock_fraction * about(ROCKY_ALBEDO, 0.1);
  
  water_part = water_fraction * about(WATER_ALBEDO, 0.2);
  
  if (surf_pressure == 0.0)
    ice_part = ice_fraction * about(AIRLESS_ICE_ALBEDO, 0.4);
  else
    ice_part = ice_fraction * about(ICE_ALBEDO, 0.1);
  
  return cloud_part + rock_part + water_part + ice_part;
}

/*--------------------------------------------------------------------------*/
/*   This function returns the dimensionless quantity of optical depth,     */
/*   which is useful in determining the amount of greenhouse effect on a    */
/*   planet.                                                                */
/*--------------------------------------------------------------------------*/

double opacity(double molecular_weight, double surf_pressure)
{
  double      optical_depth;

  optical_depth = 0.0;
  if (molecular_weight >= 0.0 && molecular_weight < 10.0)
    optical_depth += 3.0;
  
  if (molecular_weight >= 10.0 && molecular_weight < 20.0)
    optical_depth += 2.34;
  
  if (molecular_weight >= 20.0 && molecular_weight < 30.0)
    optical_depth += 1.0;
  
  if (molecular_weight >= 30.0 && molecular_weight < 45.0)
    optical_depth += 0.15;
  
  if (molecular_weight >= 45.0 && molecular_weight < 100.0)
    optical_depth += 0.05;
  
  if (surf_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    optical_depth *= 8.333;
  else if (surf_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    optical_depth *= 6.666;
  else if (surf_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    optical_depth *= 3.333;
  else if (surf_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    optical_depth *= 2.0;
  else if (surf_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    optical_depth *= 1.5;
  
  return optical_depth;
}

/*--------------------------------------------------------------------------*/
/*   The temperature calculated is in degrees Kelvin.                       */
/*   Quantities already known which are used in these calculations:         */
/*       planet->molec_weight                                               */
/*       planet->surf_pressure                                              */
/*       R_ecosphere                                                        */
/*       planet->a                                                          */
/*       planet->volatile_gas_inventory                                     */
/*       planet->radius                                                     */
/*       planet->boil_point                                                 */
/*--------------------------------------------------------------------------*/

void iterate_surface_temp(stellar_system* system, planet** planet)
{
  double      surf1_temp;
  double      effective_temp;
  double      greenhs_rise;
  double      previous_temp;
  double      optical_depth;
  double      albedo = 0;
  double      water  = 0;
  double      clouds = 0;
  double      ice    = 0;
  int         num_iter = 0;

  optical_depth = opacity((*planet)->molec_weight, (*planet)->surf_pressure);
  effective_temp = eff_temp(system->r_ecosphere, (*planet)->a, EARTH_ALBEDO);
  greenhs_rise = green_rise(optical_depth, effective_temp,
          (*planet)->surf_pressure);
  surf1_temp = effective_temp + greenhs_rise;
  do
  {
    previous_temp = surf1_temp;
    water = water_fraction((*planet)->volatile_gas_inventory,
         (*planet)->radius);
    clouds = cloud_fraction(surf1_temp,
          (*planet)->molec_weight,
          (*planet)->radius, water);
    ice = ice_fraction(water, surf1_temp);
    if ((surf1_temp >= (*planet)->boil_point) ||
        (surf1_temp <= FREEZING_POINT_OF_WATER))
      water = 0.0;
    albedo = planet_albedo(water, clouds, ice, (*planet)->surf_pressure);
    
    if (num_iter++ > 1000)
      break;
    
    optical_depth = opacity((*planet)->molec_weight, (*planet)->surf_pressure);
    effective_temp = eff_temp(system->r_ecosphere, (*planet)->a, albedo);
    greenhs_rise = green_rise(optical_depth, effective_temp,
            (*planet)->surf_pressure);
    surf1_temp = effective_temp + greenhs_rise;
  } while (fabs(surf1_temp - previous_temp) > 1.0);
  
  (*planet)->hydrosphere = water;
  (*planet)->cloud_cover = clouds;
  (*planet)->ice_cover = ice;
  (*planet)->albedo = albedo;
  (*planet)->surf_temp = surf1_temp;
}

void iterate_surface_temp_moon(stellar_system* system, planet** primary, planet** planet)
{
  double      surf1_temp;
  double      effective_temp;
  double      greenhs_rise;
  double      previous_temp;
  double      optical_depth;
  double      albedo = 0;
  double      water  = 0;
  double      clouds = 0;
  double      ice    = 0;
  int         num_iter = 0;

  optical_depth = opacity((*planet)->molec_weight, (*planet)->surf_pressure);
  effective_temp = eff_temp(system->r_ecosphere, (*primary)->a, EARTH_ALBEDO);
  greenhs_rise = green_rise(optical_depth, effective_temp,
          (*planet)->surf_pressure);
  surf1_temp = effective_temp + greenhs_rise;
  do
  {
    previous_temp = surf1_temp;
    water = water_fraction((*planet)->volatile_gas_inventory,
         (*planet)->radius);
    clouds = cloud_fraction(surf1_temp,
          (*planet)->molec_weight,
          (*planet)->radius, water);
    ice = ice_fraction(water, surf1_temp);
    if ((surf1_temp >= (*planet)->boil_point) ||
        (surf1_temp <= FREEZING_POINT_OF_WATER))
      water = 0.0;
    albedo = planet_albedo(water, clouds, ice, (*planet)->surf_pressure);
    if (num_iter++ > 1000)
      break;
    optical_depth = opacity((*planet)->molec_weight, (*planet)->surf_pressure);
    effective_temp = eff_temp(system->r_ecosphere, (*primary)->a, albedo);
    greenhs_rise = green_rise(optical_depth, effective_temp,
            (*planet)->surf_pressure);
    surf1_temp = effective_temp + greenhs_rise;
  } while (fabs(surf1_temp - previous_temp) > 1.0);
 
  (*planet)->hydrosphere = water;
  (*planet)->cloud_cover = clouds;
  (*planet)->ice_cover = ice;
  (*planet)->albedo = albedo;
  (*planet)->surf_temp = surf1_temp;
}
