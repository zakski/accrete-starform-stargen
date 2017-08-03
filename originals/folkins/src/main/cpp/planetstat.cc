/*
 * Planetstat.c : Compute the physical properties of a planet.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 */

// #define DEBUG

#include "system.h"
#include "const.h"

#include "parsefrm.h"

double  k = 5.67E-8;   /* J / mol K */

#ifdef DEBUG

#include <stdarg.h>
#include <stdio.h>

static void
debugf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
}

#else

static void
debugf(const char *fmt, ...)
{
  fmt = fmt;
}

#endif

/*
 * Compute the stellar flux at the top of the planet's atmosphere.  This
 * is scaled from the solar constant at Earth of 1400 Watts / square metre
 * by a linear increase of luminosity and an inverse square relation to
 * the distance from the star.  Luminosity is given in Suns, radius in m.
 */
double
c_flux(double sun_lum, double radius)
{
  return (1400.0 * sun_lum / (radius/AU * radius/AU));
}

/*
 * Compute the temperature at the planet, given the luminosity of it's
 * star and orbital distance.  This is the black body temperature, and
 * does not take into account greenhouse effects or radiation from the
 * planet.
 */
double
c_temp(double sun_lum, double radius)
{
  return (pow(c_flux(sun_lum, radius) / (4.0 * k), 0.25));
}

double
c_temp(double lum1, double r1, double lum2, double r2)
{
  double flux = c_flux(lum1, r1) + c_flux(lum2, r2);
  return (pow(flux / (4.0 * k), 0.25));
}

/*
 * compute the surface gravity of a planet given it's mass in kg and
 * radius in metres, return metres / second ** 2.
 */
double
surface_gravity1(double mass, double radius)
{
  return (G * mass / (radius * radius));
}

/*
 * compute the surface gravity of a planet given it's density in grams /
 * cubic centimetres and radius in metres, returns metres / second ** 2.
 */
double
surface_gravity2(double density, double radius)
{
  return (4 * PI * G * radius * density / 3);
}

/*
 * Compute the escape velocity in m/sec of a planet given it's mass in
 * kg and radius in m
 */
double
escape_velocity(double mass, double radius)
{
  return sqrt(2 * G * mass / radius);
}

// Returns the acceleration due to tides across a planet of radius r
// distance R from a mass M (it's assumed that M acts as a point mass)

double
tide(double r, double M, double R)
{
  double r0 = R - r;
  double r1 = R + r;
  double t0 = G * M / (r0 * r0);
  double t1 = G * M / (r1 * r1);
  return t0 - t1;
}

// returns (s/t2)2 / s.m = s/mt4
// braking should be 1/t2, so the 'fiddle factor' must be in units kg.sec^2/m,
// or mass over acceleration(?).

double
tidalbraking(double r, double m, double R, double M)
{
  double t = tide(r, M, R);
  return 1.52398e+21 * t*t / r / m;
}



/*
 * Compute a whole bunch of other stuff.  Most of this is from Fogg.
 */
void
ComputePlanetStats(Star& star, Planet& p, Planet *prim=NULL)
{
  float   k2;
  float   dw;
  Planet  pp;

  double mdust;
  double rdust;

  if (prim)
  {
    pp = *prim;
  }
  else
  {
    pp = p;
  }

  p.mass = p.mass_dust + p.mass_gas;

  if ((p.flags & (GAS | STAR)) && p.mass > 3000*Me)
  {
    Star s = GenStarFromMass(p.mass);
    if ((p.flags & GAS) && p.temperature <= 0)
    {
      p.radius = s.radius;
      p.temperature = s.temperature;
      p.luminosity  = s.luminosity;
      p.flags = STAR;
      p.density = p.mass / (pow(p.radius, 3) * 4*PI/3);
    }
  }
  else
  {
    if (prim)
      p.temperature = c_temp(star.luminosity, pp.r,
	                     prim->luminosity, p.r);
    else
      p.temperature = c_temp(star.luminosity, pp.r);

    /* fiddle densities to likely values */
    if (p.flags & GAS)
    {
      double dm = pow(p.mass_dust/Me, 0.125) * 
	pow(star.r_ecos / pp.r, 0.25) * 5500;
      double dg = (500 + 500 * drand48()) * sqrt(273 / p.temperature);
      double vd = p.mass_dust / dm;
      double vg = p.mass_gas  / dg;
      p.density = p.mass / (vd + vg);
      p.radius = pow(p.mass / (p.density * 4.2), 0.33333333);
      rdust = pow(vd * 3/(4*PI), 0.333333333);
      mdust = p.mass_dust;
      k2 = 0.24;
    }
    else
    {
      p.density = pow(p.mass/Me, 0.125) *
	pow(star.r_ecos / pp.r, 0.25) * 5500;	/* kg / m**3 */
      if (p.density < 2)
	p.density = 1 + drand48() + drand48();
      p.radius = pow(p.mass / (p.density * 4.2), 0.33333333);
      mdust = p.mass;
      rdust = p.radius;
      k2 = 0.33;
    }
  }

  p.surface_gravity = surface_gravity2(p.density, p.radius);
  p.esc_velocity = escape_velocity(p.mass, p.radius);
  
  if (prim)
    p.year = 2*PI * sqrt(pow(p.r, 3.0) / (G * prim->mass));
  else
    p.year = 2*PI * sqrt(pow(p.r, 3.0) / (G * star.mass));

  p.rotation_rate =   /* rad/sec */
    sqrt(8.73E-2 * p.mass/Me / (0.5 * k2 * p.radius * p.radius/1000000));

  // Look for Roche effects

  if (tide(p.radius, pp.mass, p.r) > p.surface_gravity)
  {
    p.flags = FRAGMENTS;
    p.rotation_rate = p.year;
    return;
  }
 

  // Calculate braking effects on rotation


  debugf("\n%s %d   mass = %g Me, radius %.0f km\n",
      prim ? "moon" : "planet", p.n,
      mdust/Me, rdust/1000);
  debugf("rotation rate = %0.8f   age = %g Gy\n",
         p.rotation_rate, star.age/Gy);

  
  typedef map<double, const Planet*>  BrakeMap;

  BrakeMap bm;

  // tidal braking from central star
  dw = tidalbraking(rdust, mdust, pp.r, star.mass) * star.age;
  bm[dw] = 0;

  debugf("star braking at %12g AU from %12g Msol = %g\n",
         pp.r/AU, star.mass/Msol, dw);

  if (prim)
  {
    // tidal braking from primary (planet)
    dw = tidalbraking(rdust, mdust, p.r, prim->mass) * star.age;
    bm[dw] = prim;
    debugf("prim braking at %12g km from %12g Me   = %g\n",
	   p.r/1000, prim->mass/Me, dw);

  }

  for (PlanetList::const_iterator m = p.moon.begin();
       m != p.moon.end();
       m++)
  {
    if (!(m->flags & FRAGMENTS))
    {
      dw = tidalbraking(rdust, mdust, m->r, m->mass) * star.age;
      bm[dw] = &*m;
      debugf("%-4d braking at %12g km from %12g Me   = %g\n",
	     m->n, m->r/1000, m->mass/Me, dw);
    }
  }

  for (BrakeMap::const_iterator b = bm.begin(); b != bm.end(); b++)
  {
    const Planet *bp = b->second;
    dw = b->first;
    
    if (!bp)
    {
      p.rotation_rate -= dw;
      debugf("star braking  = %-10.8f -> %-0.8f\n", dw, p.rotation_rate);
      if (p.rotation_rate < 0)
      {
	p.locked = LOCKED_STAR;
	p.rotation_rate = 0.0;
      }
    }
    else if (bp == prim)
    {
      p.rotation_rate -= dw;
      debugf("prim braking  = %-10.8f -> %-0.8f\n", dw, p.rotation_rate);
      if (p.rotation_rate < 2*PI/p.year)
      {
	p.locked = LOCKED_PRIM;
	p.rotation_rate = 2*PI/p.year;
      }
    }
    else
    {
      double myear = sqrt(G * p.mass / pow(bp->r, 3.0));

      if (p.rotation_rate > myear)
      {
	p.rotation_rate -= dw;
	debugf("moon %d-%d\n", p.n, bp->n);
	debugf("moon braking  = %-10.8f -> %-0.8f\n", dw, p.rotation_rate);
	if (p.rotation_rate < myear)
	{
	  debugf("locked to moon\n");
	  p.locked = bp->n;
	  p.rotation_rate = myear;
	}
      }
      else
      {
	p.rotation_rate += dw;
	debugf("moon %d-%d\n", p.n, bp->n);
	debugf("moon speedup  = %-10.8f -> %-0.8f\n", dw, p.rotation_rate);
	if (p.rotation_rate > myear)
	{
	  debugf("locked to moon\n");
	  p.locked = bp->n;
	  p.rotation_rate = myear;
	}
      }
    }
  }

  debugf("rotation rate = %-0.8f\n\n", p.rotation_rate);

  
  if (p.rotation_rate <= 0.0)
    p.rotation_rate = 0.0;
  else
    p.rotation_rate = 2 * PI / p.rotation_rate;	/* seconds */

  /* check for spin resonance period */
  if (p.rotation_rate == 0.0)
  {
    if (p.e > 0.1 && p.rotation_rate == 0.0)
      p.rotation_rate = p.year * (1.0 - p.e) / (1.0 + p.e);
    else
      p.rotation_rate = p.year;
  }
}



