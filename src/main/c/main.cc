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
   $RCSfile: main.c,v $

   $Date: 1999/04/25 17:44:20 $
   $Revision: 1.3 $

   $Log: main.c,v $
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

void
DisplayPrimaryStats(struct Star *star)
{
  short   i;

  printf("Primary spectral class %c%d %s\n", star->spc_class,
	 star->spc_subclass, LuminosityClass[star->lum_class]);
  printf("Luminosity %.4G Sol\n", star->luminosity);
  printf("Mass       %.4G Sol\n", star->mass);
  printf("Ecosphere  %.4g AU\n", star->r_ecos);
}

#define CM_PER_INCH      2.54
#define INCH_PER_METRE   (100/CM_PER_INCH)
#define KG_PER_LB        2.2

#define PSL  (14*KG_PER_LB*INCH_PER_METRE*INCH_PER_METRE)

void
DisplayPlanet(struct Planet *p)
{
  double  area = 4 * PI * p->radius * p->radius * 1e6;
  double  press = p->mass_gas * Me / area;

  printf("%-20s %g\n", "orbit_radius", p->r);
  printf("%-20s %g\n", "eccentricity", p->e);
  printf("%-20s %g\n", "mass", p->mass);
  printf("%-20s %g\n", "mass_dust", p->mass_dust);
  printf("%-20s %g\n", "mass_gas", p->mass_gas);
  printf("%-20s %g\n", "radius", p->radius);
  printf("%-20s %g\n", "density", p->density);
  printf("%-20s %g\n", "surface_gravity", p->surface_gravity);
  printf("%-20s %g\n", "esc_velocity", p->esc_velocity);
  printf("%-20s %g\n", "year", p->year);
  printf("%-20s %g\n", "rotation_rate", p->rotation_rate);
  printf("%-20s %g\n", "temperature", p->temperature);
  printf("%-20s %g\n", "pressure", press * p->surface_gravity / PSL);
}

void
displayPlanets(struct Star *star)
{
  struct Node *n;
  int     num = 0;

  for (n = star->PlanetList.head; n; n = n->next)
  {
    if (((struct Planet *)n)->mass > 0.01)
    {
      num++;
      printf("\nPlanet %d:\n", num);
      DisplayPlanet((struct Planet *)n);
    }
  }
}

void
summarise(struct Star *star)
{
  struct Node *n;
  int     num = 0;

  if (!star->PlanetList.head)
    return;
  printf("\n       R AU    Mass   radius    T(K)   Press\n");
  for (n = star->PlanetList.head; n; n = n->next)
  {
    struct Planet *p = (struct Planet *)n;

    if (p->mass > 0.01)
    {
      double  area = 4 * PI * p->radius * p->radius * 1e6;
      double  press = p->mass_gas * Me * p->surface_gravity / area;

      num++;
      if (p->flags & GAS)
      {
	printf("%3d: %6.2f %8.3f %7.0f %6.0f    gas giant\n",
	       num, p->r, p->mass, p->radius, p->temperature);
      }
      else
      {
	if (press / PSL > 0.005)
	  printf("%3d: %6.2f %8.3f %7.0f %6.0f %8.2f\n",
		 num, p->r, p->mass, p->radius, p->temperature, press / PSL);
	else
	  printf("%3d: %6.2f %8.3f %7.0f %6.0f\n",
		 num, p->r, p->mass, p->radius, p->temperature);
      }
    }
  }
}

void
GenerateSystem(struct Star *star)
{
  listInit(&star->PlanetList);
  switch (star->spc_class)
  {
  case 'O':
  case 'B':
  case 'A':
    DisplayPrimaryStats(star);
    break;			/* These guys don't get planets */
  case 'F':
  case 'G':
  case 'K':
  case 'M':
    if (star->lum_class >= 4 && star->lum_class <= 6)
    {
      CreateSystem(star);
      DisplayPrimaryStats(star);
      summarise(star);
      displayPlanets(star);
    }
    else
    {
      DisplayPrimaryStats(star);
    }
    break;
  }
}

void
FreeStar(struct Star *star)
{
  listFree(&star->PlanetList);
}

struct Star star;

int
main(int argc, char **argv)
{
  double mass = 0;
  double lum  = 0;
  int     n = 1;
  int     i;

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
      case 'm':
	mass = atof(&argv[i][2]);
	break;
      case 'l':
	lum = atof(&argv[i][2]);
	break;
      case 'n':
	n = atoi(&argv[i][2]);
	break;
      }
    }
  }
  InitGenStar();
  for (i = 0; i < n; i++)
  {
    printf("\nSYSTEM %d:\n\n", i + 1);
    do
      GenStar(&star);
    while (star.luminosity < 0.01);
    if (mass > 0)
      star.mass = mass;
    if (lum > 0)
      star.luminosity = lum;
    if (mass > 0 || lum > 0)
    {
      star.lum_class = 5;
      star.r_ecos = sqrt(star.luminosity);
      star.r_inner = 0.93 * star.r_ecos;
      star.r_outer = 1.1 * star.r_ecos; /* approximately */
    }
    GenerateSystem(&star);
    FreeStar(&star);
  }
  return 0;
}
