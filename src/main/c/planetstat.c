
/*
 * Planetstat.c : Compute the physical properties of a planet.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 */

#include "system.h"

double Mass_of_Earth = 5.98E24,    /* kg */
       G             = 6.67E-11,   /* nt - m**2 / kg**2 */
       k             = 5.67E-8;    /* J / mol K */

/*
 * Compute the stellar flux at the top of the planet's atmosphere.  This
 * is scaled from the solar constant at Earth of 1400 Watts / square metre
 * by a linear increase of luminosity and an inverse square relation to
 * the distance from the star.  Luminosity is given in Suns, radius in AU's.
 */
double c_flux(sun_lum, radius)
double sun_lum, radius;
{
   return( 1400.0 * sun_lum / (radius * radius));
}

/*
 * Compute the temperature at the planet, given the luminosity of it's
 * star and orbital distance.  This is the black body temperature, and
 * does not take into account greenhouse effects or radiation from the
 * planet.
 */
double c_temp(sun_lum, radius)
double sun_lum, radius;
{
   return( pow(c_flux(sun_lum, radius) / (4.0 * k), 0.25));
}

/*
 * compute the surface gravity of a planet given it's mass in kg and
 * radius in kilometres, return metres / second ** 2.
 */
double surface_gravity1(mass, radius)
double mass, radius;
{
   radius *= 1000.0;  /* convert to metres */
   return(G * mass / (radius * radius));
}

/*
 * compute the surface gravity of a planet given it's density in grams /
 * cubic centimetres and radius in kilometres, returns metres / second ** 2.
 */
double surface_gravity2(density, radius)
double density, radius;
{
   return(4000000 * PI * G * radius * density / 3);
}

/*
 * Compute the escape velocity in km/sec of a planet given it's mass in
 * kg and radius in km
 */
double escape_velocity(mass, radius)
double mass, radius;
{
   return( sqrt( 2 * G * mass / (radius * 1000)) / 1000.0);
}

/*
 * Compute a whole bunch of other stuff.  Most of this is from Fogg.
 */
void ComputePlanetStats(star, p)
struct Star *star;
struct Planet *p;
{
   float k2, dw;

   p->mass = p->mass_dust + p->mass_gas;
   p->mass *= 329390.0;
   if (p->flags & GAS) {
      p->density = 0.75 + 0.5 * drand48();
      k2 = 0.24;
   } else {
      p->density = pow(p->mass, 0.125) * pow(star->r_ecos / p->r, 0.25) * 5.5;  /* tonnes / m**3 */
      k2 = 0.33;
   }
   p->year = sqrt(pow(p->r, 3.0) / star->mass);
   p->radius = pow(p->mass * 6.0E21 / (p->density * 4.2), 0.333) / 1000.0;
   p->rotation_rate = sqrt(8.73E-2 * p->mass /
                           (0.5 * k2 * p->radius * p->radius));  /* radians / sec */
   /* Tidal braking forces from central star */
   dw = 1.0 *                    /* matter/mass distribution == density??? */
        (p->radius / 6422.0) *   /* in km */
        (1.0 / p->mass) *        /* in Earth masses */
        pow(star->mass, 2.0) *
        pow(1.0 / p->r, 6.0) *
        -1.3E-6;
   dw *= 4.0 /* star->age */ ; /* 10E9 years */
   p->rotation_rate += dw;
   if (p->rotation_rate < 0.0)
      p->rotation_rate = 0.0;
   else
      p->rotation_rate = 2 * PI / (3600.0 * p->rotation_rate); /* hours */

   /* check for spin resonance period */
   if (p->e > 0.1 && p->rotation_rate == 0.0)
      p->rotation_rate = p->year * (1.0 - p->e) / (1.0 + p->e) * 24.0;

   p->temperature = c_temp(star->luminosity, p->r);
   p->surface_gravity = surface_gravity2(p->density, p->radius);
   p->esc_velocity = escape_velocity(p->mass * Mass_of_Earth, p->radius);
}

