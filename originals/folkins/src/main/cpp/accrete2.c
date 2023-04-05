
/*
 * Accrete2.c - Replacement system generation code (use instead of dole.c).
 *
 * This code uses a simple Bode-type law, along with the accretion
 * formulae from Dole's algorithm, to generate a planetary system.  It
 * has the advantage that it's about 10 times faster, but it's output
 * is considerably more random.  The planetary nuclei are injected
 * in sequence outward from the inner edge of the dust cloud, and far
 * apart enough that they shouldn't interact.  When we've reached the
 * outer edge, we're finished even though we may not have accreted all
 * the available dust.  In fact, we don't even bother to keep track
 * of the band structure in dole.c.
 *
 * This is quick and dirty, but it doesn't seem overly realistic as
 * given, it seems especially difficult to generate Earth-mass
 * terrestrial planets.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 */

#include <proto/exec.h>
#include <stdio.h>

#include "system.h"

extern void ComputePlanetStats(struct Star *, struct Planet *);

double A, Ao = 0.0015, /* coeff. of cloud density (solar masses / AU**3) */
       alpha = 5.0,   /* cloud density parameter */
       gamma = 0.33,  /* cloud density parameter */
       K = 50,        /* ratio of overall density to density of dust */
       m0 = 1E-15,    /* nuclei mass (solar masses) */
       B = 1.2E-5,    /* critical mass parameter (solar masses) */
       beta = 0.5;    /* gas capture parameter */

short n_nuclei;       /* This is actually used for something */

double Critical_Mass;

double Density(r)
double r;
{
   return(A * exp(-alpha * pow(r, gamma)));
}

double Reach(radius, mass)
double radius, mass;
{
   return(radius * pow(mass / (1.0 + mass), 0.25));
}

struct Planet *CreatePlanet(radius0, radius1)
double radius0, radius1;
{
   struct Planet *newp;

   newp = (struct Planet *)malloc(sizeof(struct Planet));
   if (!newp) return(NULL);
   newp->flags = 0;
   newp->mass = m0;
   newp->mass_dust = m0;
   newp->mass_gas = 0;
   newp->e = 1.0 - pow(drand48(), 0.077);
   newp->rmin = radius0;
   newp->rmax = radius1;
   newp->r = (radius0 + radius1) / 2.0;
   newp->density = Density(newp->r);
   newp->n = n_nuclei++;
   newp->x = newp->y = 0;

   return(newp);
}

double swept_mass(listn, p)
short listn;
struct Planet *p;
{
   double mass;

   mass = 2 * PI * 2 * p->reach * p->r * (p->rmax - p->rmin) * p->density;
   if (listn == 2)
      mass *= K / ((K - 1) * pow(Critical_Mass / p->mass, beta) + 1);
   return(mass);
}

void EvolvePlanet(star, p)
struct Star *star;
struct Planet *p;
{
   double perihelion, previous_mass, mass_dust, mass_gas;

   if (!p) return;

   perihelion = p->r * (1 - p->e);
   Critical_Mass = B * pow(perihelion * sqrt(1.0 / star->luminosity), -0.75);

   mass_dust = 0.0;
   mass_gas = 0.0;
   for (;;) {
      p->reach = Reach(p->r, p->mass);
      mass_dust = swept_mass(0, p);
      if (mass_dust > Critical_Mass) {    /* accrete gas */
         p->flags |= GAS;
         mass_gas = swept_mass(2, p);
      }
      previous_mass = p->mass;
      p->mass_dust = mass_dust;
      p->mass_gas = mass_gas;
      p->mass = mass_dust + mass_gas;
      if ((p->mass - previous_mass) / p->mass < 0.01) break;
   }
}

void CreateSystem(star)
struct Star *star;
{
   struct Planet *p;
   double r0, mult, radius0, radius1, maxradius;

   n_nuclei = 1;

   /* The relative spacing of the orbits . . . */
   r0 = 1.1;
   /* . . . multiplied by a random factor. */
   mult = 2.0;

   /* With these two values, the orbital spacing will vary from 1.1
    * to 3.1, with an average of about 2.1, which sounds about right.
    */

   A = Ao * sqrt(star->mass);
   maxradius = (40.0 + drand48() * 20.0) * pow(star->mass, 0.33);
   radius0 = (0.2 + drand48() * 0.1) * pow(star->mass, 0.33);
   while (radius0 < maxradius) {
      radius1 = radius0 * (r0 + mult * drand48());
      p = CreatePlanet(radius0, radius1);
      AddTail(&star->PlanetList, (struct Node *)p);
      EvolvePlanet(star, p);
      radius0 = radius1;
      ComputePlanetStats(star, p);
   }
}
