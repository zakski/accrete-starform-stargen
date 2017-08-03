/*
   main.c
   Copyright Chris Croughton 1998
   Internet: chris@keris.demon.co.uk

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met (see file LICENSE for more explanation):

   1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   2. Modifications of the source code must, in addition to the above,
   include a statement that the code has been modified and by whom,
   and have relevant contact information.

   3. Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.  Note that this does not apply when the
   binary forms part of a completed work such as an executable
   program of which it is a minor part and from which it cannot be
   extracted in a usable form (for instance linked to form an
   executable binary image).

   4. The name of the author may not be used to endorse or promote
   products derived from this software without specific prior
   written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

/*
   $RCSfile: main.cc,v $

   $Date: 2000/02/22 16:26:25 $
   $Revision: 2.7 $

   $Log: main.cc,v $
   Revision 2.7  2000/02/22 16:26:25  chrisc
   Add debug stuff

   Revision 2.6  2000/02/03 17:39:43  chrisc
   Add stuff for companions and brown dwarfs as stars

   Revision 2.5  2000/01/31 10:07:45  chrisc
   Add -p to do just Earth/moon calcs; add display of 'locked'
   planets and moons; add -a to set age of star.

   Revision 2.4  2000/01/28 13:18:10  chrisc
   Remove extra ComputePlanetStats before making moons

   Revision 2.3  2000/01/27 08:37:59  chrisc
   Put display of system in separate routine (after all calculation),
   display whether a system has a 'possible' good planet, remove
   planet classifications based on pressure of original gas.

   Revision 2.2  2000/01/21 18:10:42  chrisc
   Add temperature, age, lifetime and radius display

   Revision 2.1  2000/01/20 17:55:39  chrisc
   Converted to MKS

   Revision 2.0  2000/01/20 10:23:15  chrisc
   Start of MKS conversion

   Revision 1.6  2000/01/13 17:56:24  chrisc
   Add moon stuff, improve summaries

   Revision 1.5  2000/01/07 16:19:11  chrisc
   Add 'brown dwarf' and 'companion' types

   Revision 1.4  2000/01/07 13:12:49  chrisc
   Converted to C++
   Added planet classifications

   Revision 1.3  2000/01/07 09:19:25  chrisc
   Print mass as Me/1000 units if creating moons

   Revision 1.2  2000/01/06 09:47:02  chrisc
   Do moon creation stuff

   Revision 1.1  2000/01/05 13:05:33  chrisc
   Initial revision

   Revision 1.3  1999/04/25 17:44:20  ccrough
   Change output formats, add option to fix input stellar mass & luminosity

   Revision 1.2  1999/04/22 06:48:52  ccrough
   Reformatted (indent) and protoized

   Revision 1.1  1999/04/21 13:28:56  ccrough
   Initial revision

 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "system.h"
#include "const.h"

/* Compute the physical parameters of a planet */
extern void ComputePlanetStats(Star& s, Planet& p, Planet *prim=NULL);

extern char *LuminosityClass[];
extern char *SpectralClass[];
 

static int    debug = 0;
static double minmass = 0.01 * Me;

void
DisplayPrimaryStats(Star &star)
{
  short   i;

  if (star.spc_class != 'u')
  {
    printf("%-20s %c%d %s\n", "spectral class", star.spc_class,
	   star.spc_subclass, LuminosityClass[star.lum_class]);
  }
  printf("%-20s %.0f K\n", "temperature", star.temperature);
  printf("%-20s %.4g Sol\n", "luminosity", star.luminosity);
  printf("%-20s %.4g Sol\n", "mass", star.mass/Msol);
  printf("%-20s %.4g Sol\n", "radius", star.radius/Rsol);
  //printf("%-20s %.4g AU\n", "ecosphere", star.r_ecos/AU);
  if (star.age < 1 * Gy)
    printf("%-20s %.4g My\n", "age", star.age*1000/Gy);
  else
    printf("%-20s %.4g Gy\n", "age", star.age/Gy);
  if (star.lifetime < 1 * Gy)
    printf("%-20s %.4g My\n", "life", star.lifetime*1000/Gy);
  else
    printf("%-20s %.4g Gy\n", "life", star.lifetime/Gy);
}

#define CM_PER_INCH      2.54
#define INCH_PER_METRE   (100/CM_PER_INCH)
#define KG_PER_LB        2.2

#define PSL  10000

bool
isPossible(const Planet& p)
{
  double  area = 4 * PI * p.radius * p.radius;
  double  press = p.mass_gas * p.surface_gravity / area;

  if ((p.flags & GAS) && (p.mass_gas / p.mass_dust > 0.1 || press/PSL > 10000))
  {
    return false;
  }
  if (p.mass < 0.4 * Me)
    return false;
  if (p.surface_gravity > 20)
    return false;
  if (p.temperature < 260)
    return false;
  if (p.temperature > 310)
    return false;
  if (p.rotation_rate < 12 * 3600)
    return false;
  if (p.rotation_rate > 4 * 24 * 3600)
    return false;
  return true;
}

bool
isPossible(const Star& star)
{
  for (PlanetList::const_iterator n = star.planet.begin();
       n != star.planet.end(); n++)
  {
    if (isPossible(*n))
      return true;
  }
  return false;
}


const char *
classify(const Planet& p)
{
  double  area = 4 * PI * p.radius * p.radius;
  double  press = p.mass_gas * p.surface_gravity / area;

  if (p.flags & STAR)
  {
    if (p.mass > 0.084*Msol)
      return "companion";
    return "brown dwarf";
  }
  if ((p.flags & GAS) && (p.mass_gas / p.mass_dust > 0.1 || press/PSL > 10000))
  {
    if (p.mass > 0.084*Msol)
      return "companion";
    if (p.mass > 3000*Me)
      return "brown dwarf";
    if (p.mass > 100*Me && p.mass_gas / p.mass_dust > 1)
      return "jupiter-type";
    if (p.mass > 10*Me)
      return "gas giant";
    if (p.mass < 0.8*Me)
      return "gas dwarf";
    return "gas planet";
  }
//  if (press / PSL < 0.005)
//    return "rocky";
//  if (press / PSL > 4)
//    return "high pressure";
  if (p.mass < 0.4 * Me)
    return "small";
  if (p.surface_gravity > 20)
    return "heavy";
  if (p.temperature < 260)
    return "cold";
  if (p.temperature > 310)
    return "hot";
  if (p.rotation_rate < 12 * 3600)
    return "day too short";
  if (p.rotation_rate > 4 * 24 * 3600)
    return "day too long";
  return "possible";
}

const char *
tstr(double t) // in seconds
{
  static char buff[64];
  if (t == 0)
    strcpy(buff, "locked");
  else if (t < 30)
    sprintf(buff, "%.2f seconds", t);
  else if ((t/=60) < 30)
    sprintf(buff, "%.2f minutes", t);
  else if ((t/=60) < 12)
    sprintf(buff, "%.2f hours", t);
  else if ((t/=24) < 90)
    sprintf(buff, "%.2f days", t);
  else
    sprintf(buff, "%.2f years", t/365.25);
  return buff;
}

const char *
lockstr(int lock)
{
  static char buff[16];
  switch (lock)
  {
    case 0:
      return "";
    case LOCKED_STAR:
      return "star";
    case LOCKED_PRIM:
      return "planet";
    default:
      sprintf(buff, "moon %d", lock);
      return buff;
  }
}

void
DisplayPlanet(Planet& p)
{
  double  area = 4 * PI * p.radius * p.radius;
  double  press = p.mass_gas * p.surface_gravity / area;

  if (p.flags & STAR)
  {
    Star s(p);
    GenStarDetails(s);
    DisplayPrimaryStats(s);
    printf("\n");
  }
  printf("%-20s %g AU\n",   "orbit_radius", p.r/AU);
  printf("%-20s %g\n",      "eccentricity", p.e);
  printf("%-20s %g Me\n",   "mass", p.mass/Me);
  printf("%-20s %g Me\n",   "mass_dust", p.mass_dust/Me);
  printf("%-20s %g Me\n",   "mass_gas", p.mass_gas/Me);
  printf("%-20s %g km\n",   "radius", p.radius/1000);
  printf("%-20s %g\n",      "density", p.density);
  printf("%-20s %g m/s2\n", "surface_gravity", p.surface_gravity);
  printf("%-20s %g km/s\n", "esc_velocity", p.esc_velocity/1000);
  printf("%-20s %s\n",      "orbit_period",  tstr(p.year));
  if (!(p.flags & STAR))
  {
    printf("%-20s %s\n",      "rotation_rate", tstr(p.rotation_rate));
    if (p.locked)
      printf("%-20s locked to %s\n",    "locked", lockstr(p.locked));
    printf("%-20s %g K\n",    "temperature", p.temperature);
    printf("%-20s %g atm\n",  "pressure", press / PSL);
  }
}

void
DisplayMoon(Planet& p)
{
  double  area = 4 * PI * p.radius * p.radius;
  double  press = p.mass_gas * p.surface_gravity / area;

  printf("  %-18s %g km\n", "orbit_radius", p.r/1000);
  printf("  %-18s %g\n",    "eccentricity", p.e);
  if (p.mass < 0.01*Me)
    printf("  %-18s 1/%.0f Me\n", "mass", Me/p.mass);
  else
    printf("  %-18s %g Me\n",     "mass", p.mass/Me);
  printf("  %-18s %g\n",      "mass_dust", p.mass_dust/Me);
  printf("  %-18s %g\n",      "mass_gas", p.mass_gas/Me);
  if (p.flags & FRAGMENTS)
  {
    printf("  %-18s \n", "fragmented");
  }
  else
  {
    printf("  %-18s %g km\n",   "radius", p.radius/1000);
    printf("  %-18s %g\n",      "density", p.density);
    printf("  %-18s %g m/s2\n", "surface_gravity", p.surface_gravity);
    printf("  %-18s %g km/s\n", "esc_velocity", p.esc_velocity/1000);
    printf("  %-18s %s\n",      "orbit_period",  tstr(p.year));
    printf("  %-18s %s\n",      "rotation_rate", tstr(p.rotation_rate));
  if (p.locked)
    printf("  %-18s locked to %s\n",    "locked", lockstr(p.locked));
    printf("  %-18s %g K\n",    "temperature", p.temperature);
    printf("  %-18s %g atm\n",  "pressure", press / PSL);
  }
}

void
summMoons(const Planet& prim, const PlanetList& moon)
{
  if (moon.size() == 0)
    return;
  printf("\n                  R        Mass / Mp     radius\n");
  for (PlanetList::const_iterator m = moon.begin(); m != moon.end(); m++)
  {
    double mm = m->mass / prim.mass;
    double rr = m->r/1000;
    const char *ss = "km";
    int nn = 0;
    if (m->r > 0.1 * AU)
    {
      rr = m->r / AU;
      nn = 3;
      ss = "AU";
    }
    if (m->flags & FRAGMENTS)
    {
      printf("       %3d: %8.*f %s     %-8.3s    %7.0s  %s\n",
	     m->n, nn, rr, ss, "", "", "ring");
    }
    else if (mm > 0.01)
    {
      printf("       %3d: %8.*f %s     %-8.3f    %7.0f  %s\n",
	     m->n, nn, rr, ss, mm, m->radius/1000, classify(*m));
    }
    else if (mm > 1e-5)
    {
      printf("       %3d: %8.*f %s     1/%-8.0f  %7.0f  %s\n",
	     m->n, nn, rr, ss, 1/mm, m->radius/1000, classify(*m));
    }
    else
    {
      printf("       %3d: %8.*f %s   %10s    %7.0f  %s\n",
	     m->n, nn, rr, ss, "negligible", m->radius/1000, classify(*m));
    }
  }
}

void
displayplanet(Star *star)
{
  int     num = 0;

  for (PlanetList::iterator n = star->planet.begin(); n != star->planet.end(); n++)
  {
    if (n->age < star->age)
      n->age = star->age;
    if (n->mass > minmass)
    {
      num++;
      printf("\nPlanet %d: %s\n", num, classify(*n));
      DisplayPlanet(*n);
      if (n->moon.size() > 0)
      {
	summMoons(*n, n->moon);
	int nm = 0;
	for (PlanetList::iterator m = n->moon.begin(); m != n->moon.end(); m++)
	{
	  if (m->mass > 1e-10)
	  {
	    printf("\n  Moon %d-%d\n", num, ++nm);
	    DisplayMoon(*m);
	  }
	}
      }
    }
  }
}

void
summarise(Star *star)
{
  int     num = 0;

  if (star->planet.size() == 0)
    return;
  if (star->mass < 1e-3)
    printf("\n            R km    Mass       Moons  radius    T(K)   Press\n");
  else
    printf("\n            R AU    Mass       Moons  radius    T(K)   Press\n");
  for (PlanetList::iterator p = star->planet.begin(); p != star->planet.end(); p++)
  {
    double r = (star->mass < 1e-3*Msol ? p->r/1000 : p->r/AU);
    double m = (star->mass < 1e-3*Msol ? p->mass * 1000 : p->mass)/Me;

    if (p->mass > minmass)
    {
      double  area = 4 * PI * p->radius * p->radius;
      double  press = p->mass_gas * p->surface_gravity / area;
      const char *desc = classify(*p);
      int nm = p->moon.size();
      
      num++;
      if (p->mass > 0.084*Msol)
      {
	printf("%3d: %11.2f %8.3f Msol %4d  %7.0f %6.0f %8s %s\n",
	       num, r, p->mass/Msol, nm, p->radius/1000,
	       p->temperature, "", desc);
      }
      else if (p->mass > 3000*Me)
      {
	printf("%3d: %11.2f %8.3f MJ   %4d  %7.0f %6.0f %8s %s\n",
	       num, r, m/317.83, nm, p->radius/1000,
	       p->temperature, "", desc);
      }
      else if (p->flags & GAS)
      {
	printf("%3d: %11.2f %8.3f      %4d  %7.0f %6.0f %8s %s\n",
	       num, r, m, nm, p->radius/1000, p->temperature, "", desc);
      }
      else
      {
	if (press / PSL > 10000)
	  printf("%3d: %11.2f %8.3f      %4d  %7.0f %6.0f %8s %s\n",
		 num, r, m, nm, p->radius/1000,
		 p->temperature, "very", desc);
	else if (press / PSL > 0.005)
	  printf("%3d: %11.2f %8.3f      %4d  %7.0f %6.0f %8.2f %s\n",
		 num, r, m, nm, p->radius/1000,
		 p->temperature, press / PSL, desc);
	else
	  printf("%3d: %11.2f %8.3f      %4d  %7.0f %6.0f %8s %s\n",
		 num, r, m, nm, p->radius/1000,
		 p->temperature, "", desc);
      }
    }
  }
}

void
DisplaySystem(Star& star)
{
  switch (star.spc_class)
  {
    case 'O':
    case 'B':
    case 'A':
      DisplayPrimaryStats(star);
      break;
    case 'F':
    case 'G':
    case 'K':
    case 'M':
      DisplayPrimaryStats(star);
      if (star.lum_class >= 4 && star.lum_class <= 6)
      {
	summarise(&star);
	displayplanet(&star);
      }
      break;
    case 'u':
      DisplayPrimaryStats(star);
      summarise(&star);
      displayplanet(&star);
      break;
  }
}

void
GenerateSystem(struct Star *star, bool moons)
{
  doleDebug(debug > 1);
  switch (star->spc_class)
  {
  case 'O':
  case 'B':
  case 'A':
    break;			/* These guys don't get planets */
  case 'F':
  case 'G':
  case 'K':
  case 'M':
    if (star->lum_class >= 4 && star->lum_class <= 6)
    {
      CreateSystem(*star);
      for (PlanetList::iterator n = star->planet.begin();
	   n != star->planet.end();
	   n++)
      {
	doleDebug(debug > 0);
	if (n->n > 0)
	{
	  ComputePlanetStats(*star, *n);
	  if (n->flags & STAR & 0)
	    doleDebug(1);
	  if (moons)
	    CreateMoons(*star, *n);
	  for (PlanetList::iterator m = n->moon.begin();
	       m != n->moon.end();
	       m++)
	  {
	    ComputePlanetStats(*star, *m, &*n);
	  }
	  ComputePlanetStats(*star, *n);
	}
      }
    }
    break;
  case 'u':
    CreateSystem(*star);
    if (debug > 0)
      doleDebug(1);
    for (PlanetList::iterator n = star->planet.begin(); 
 	 n != star->planet.end(); 
	 n++)
    {
      if (n->n > 0)
      {
	if (moons)
	  CreateMoons(*star, *n);
	ComputePlanetStats(*star, *n);
	for (PlanetList::iterator m = n->moon.begin();
	    m != n->moon.end();
	    m++)
	{
	  ComputePlanetStats(*star, *m, &*n);
	}
	ComputePlanetStats(*star, *n);
      }
    }
    break;
  }
}

void
FreeStar(Star& star)
{
  for (PlanetList::iterator p = star.planet.begin(); p != star.planet.end(); )
    p = star.planet.erase(p);
}

struct Star star;

int
main(int argc, char **argv)
{
  double mass = 0;
  double lum  = 0;
  double age  = 0;
  bool   moons = false;
  bool   planet = false;
  int    n = 1;
  int    i;

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
      case 'm':
	mass = atof(&argv[i][2]) * Msol;
	break;
      case 'l':
	lum = atof(&argv[i][2]);
	break;
      case 'n':
	n = atoi(&argv[i][2]);
	break;
      case 'a':
	age = atof(&argv[i][2]) * Gy;;
	break;
      case 'M':
	moons = true;
	break;
      case 'z':
	debug++;
	break;
      case 'p':
	planet = true;
	break;
      }
    }
  }

  InitGenStar();

  if (planet)
  {
    star.spc_class = 'u';
    star.spc_subclass = 1;
    star.lum_class = 5;
    star.lifetime = 6 * Gy;
    star.mass = Msol;
    star.radius = Rsol;
    star.age = 1 * Gy;
    star.luminosity = 1;
    star.temperature = 5500;
    star.r_ecos = AU;
    star.r_inner = 0.9 * AU;
    star.r_outer = 1.1 * AU;

    Planet p;
    Planet m;

    p.mass = Me;
    p.radius = Re;
    p.age = 1 * Gy;
    p.luminosity = 1;
    p.temperature = 273;
    p.mass_dust = Me;
    p.mass_gas = 0;
    p.r = AU;
    p.e = 0;
    p.n = 1;

    m.mass = 0.0123 * Me;
    m.radius = 1737400;
    m.age = 1 * Gy;
    m.luminosity = 1;
    m.temperature = 273;
    m.mass_dust = 0.0123 * Me;
    m.mass_gas = 0;
    m.r = 384400000;
    m.e = 0.0549;
    m.n = 1;

    p.moon.push_back(m);
    star.planet.push_back(p);

    PlanetList::iterator nn = star.planet.begin(); 
    PlanetList::iterator mm = nn->moon.begin();

    ComputePlanetStats(star, *mm, &*nn);
    ComputePlanetStats(star, *nn);
    DisplaySystem(star);

    exit(0);
  }

  for (i = 0; i < n; i++)
  {
    do
      GenStar(&star);
    while (star.luminosity < 0.01);
    if (mass > 0)
    {
      star.spc_class = 'u';
      star.mass = mass;
    }
    if (lum > 0)
    {
      star.spc_class = 'u';
      star.luminosity = lum;
    }
    if (mass > 0 || lum > 0)
    {
      star.lum_class = 5;
      star.r_ecos = sqrt(star.luminosity) * AU;
      star.r_inner = 0.93 * star.r_ecos;
      star.r_outer = 1.1 * star.r_ecos; /* approximately */
    }
    if (age > 0)
    {
      star.lifetime = age * 2;
      star.age = age;
    }
    GenerateSystem(&star, moons);
    printf("\nSYSTEM %d:%s\n\n", i + 1, 
	   isPossible(star) ? " possible habitable world" : "");
    DisplaySystem(star);
    FreeStar(star);
  }
  return 0;
}
