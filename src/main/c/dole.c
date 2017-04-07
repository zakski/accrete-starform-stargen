
/*
 * Dole.c - Planetary accretion algorithm, Icarus V 13 (1978)
 *
 * This program implements the accretion algorithm given by Dole.  It's
 * major flaw for simulation on a microcomputer is the amount of
 * computation which needs to be done.  I've tried to simplify the
 * computations a bit, these instances are noted in the code.
 * What I'd like to do is use integer arithmetic, but I don't think that's
 * possible.
 *
 * One thing to try is to limit the injection of nuclei.  For example,
 * the average simulation injects about 300 nuclei to produce 8-10
 * planets.  Most of these probably end up smashing into an existing
 * planet fairly often, so why not try to inject them only into the
 * area of dust bands?  As a base line, this is what we have now :
 *
 *   Run    Time  Nuclei Density   Reach   Swept  Swepti Evolvei
 *       (seconds)
 *     1      51     317     910    1085    1322     910    1085
 *     2      39     243     729     838    1045     729     838
 *     3      69     494    1142    1457    1843    1142    1457
 *     4      43     199     943     851    1194     943     851
 *
 *   Let's try modification #1 - 20 random nuclei then inject into
 *   the dust bands.
 *
 *     5      21      40     600     398     614     600     398
 *     6      19      46     516     393     523     516     393
 *     7      25      45     713     477     718     713     477
 *     8      22      45     575     422     590     575     422
 *
 *   Well, that's ups the speed by over 50%, but we get a lot more
 *   little planets, so we'll try a second modification.  As the main
 *   purpose of all those extra nuclei was to vary the eccentricity
 *   of the available planets, we'll increase the eccentricity of
 *   the later nuclei.
 *
 *     9      17      36     447     323     458     447     323
 *    10      19      33     548     352     555     548     352
 *    11      15      35     432     293     453     432     293
 *    12      19      34     502     349     511     502     349
 *
 *   That's better, though this thing's still too slow by at least a
 *   factor of 5.  Unfortunately, about half the time is spent in
 *   density and reach calculations, so the only hope for speeding
 *   things up now is to make the iteration converge faster.  I'm
 *   open for ideas on that one.
 *
 *   One thing we can try is to cut down the number of density calculations
 *   by using planet->r instead of the middle of the sweep area.  We only
 *   have to compute the density when the planet is created or when it's
 *   orbit changes, i.e. MergePlanets().  Modification #3.
 *
 *   That was interesting, the time was cut to the 12-second range, with
 *   only 37 nuclei and 65 Density() calls, though Reach() is up around
 *   400.  All the other iteration counts went up as well.  The system's
 *   seem a bit off too, this modification can produce extra-large gas
 *   giants, in the range of 1000 Earth masses.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 *
 * Modification History :
 *
 *    April 24/88 - First working version.
 *    Sept  10/88 - Incorporated into display program.
 *    Sept  18/88 - Code twiddling to speed things up.
 */


#include <proto/exec.h>
#include <stdio.h>

#include "system.h"

double Ao = 0.0015,   /* coeff. of cloud density (solar masses / AU**3) */
       A,             /* Ao * sqrt(star->mass)                          */
       alpha = 5.0,   /* cloud density parameter                        */
       gamma = 0.33,  /* cloud density parameter                        */
       K = 50,        /* ratio of overall density to density of dust    */
       W = 0.20,      /* eccentricity of cloud particles                */
       m0 = 1E-15,    /* nuclei mass (solar masses)                     */
       B = 1.2E-5,    /* critical mass paramter (solar masses)          */
       beta = 0.5;    /* gas capture parameter                          */

double MinRadius,     /* of planetismal injection, = MINRADIUS, MAXRADIUS */
       MaxRadius;     /* . . . modified by luminosity of primary */

#define MINRADIUS          0.3
#define MAXRADIUS          50.0
#define MAX_ECCENTRICITY   0.20    /* of dust particles */

struct Band {              /* Band of gas or dust */
   struct Node ba_Node;
   double rmin,            /* radius of inner edge */
          rmax;            /* radius of outer edge */
};

struct List
   List0,    /* bands containing gas and dust */
   List1,    /* bands containing gas only */
   List2;    /* bands containing some gas */

double Critical_Mass;    /* for accreting gas */

short n_density = 0,     /* iteration counters for profiling */
      n_reach = 0,
      n_swept = 0,
      n_swepti = 0,
      n_evolvei = 0,
      n_nucleus = 0;

/* Compute the physical parameters of a planet */
extern void ComputePlanetStats(struct Star *, struct Planet *);

/*
 * I'd really like to speed these up, the program spends 50% of it's
 * time in just these two routines.
 */
double Density(r)
double r;
{
   n_density++;
   return(A * exp(-alpha * pow(r, gamma)));
}

double Reach(radius, mass)
double radius, mass;
{
   n_reach++;
   return(radius * pow(mass / (1.0 + mass), 0.25));
}

struct Planet *CreatePlanet(star)
struct Star *star;
{
   struct Node *n;
   struct Planet *newp;

   newp = (struct Planet *)malloc(sizeof(struct Planet));
   if (!newp) return(NULL);
   newp->flags = 0;
   newp->mass = m0;
   newp->mass_dust = m0;
   newp->mass_gas = 0;
   newp->e = 1.0 - pow(drand48(), 0.077);
   newp->r = drand48();
   newp->r = newp->r * newp->r;
   /* Fire the first 20 nuclei in at random, then aim them at the
    * remaining dust bands.  We're just grabbing the first dust band
    * in the list, but the list isn't kept sorted so this is still
    * somewhat random.
    */
   if (n_nucleus <= 20)
      newp->r = MinRadius + (MaxRadius - MinRadius) * newp->r;
   else {
      struct Band *b;
      b = (struct Band *)List0.lh_Head;
      newp->r = b->rmin + (b->rmax - b->rmin) * newp->r;
      newp->e *= 2.0;
   }
   newp->rmin = 0.0;
   newp->rmax = 0.0;
   /* newp->density = Density(newp->r); */  /* Modification #3 */
   newp->n = 0;            /* planet number */
   newp->x = newp->y = 0;  /* screen position */
   n_nucleus++;

   /* Keep the list sorted by orbital radius.  If this was an integer
    * field, we could use the system Enqueue() function, but . . .
    */
   if (ListEmpty(&star->PlanetList))
      AddHead(&star->PlanetList, (struct Node *)newp);
   else {
      n = star->PlanetList.lh_Head;
      while ((n->ln_Succ) && ((struct Planet *)n)->r < newp->r)
         n = n->ln_Succ;
      newp->pl_Node.ln_Succ = n;
      newp->pl_Node.ln_Pred = n->ln_Pred;
      newp->pl_Node.ln_Pred->ln_Succ = (struct Node *)newp;
      n->ln_Pred = (struct Node *)newp;
   }

   return(newp);
}

struct Band *CreateBand(min, max)
double min, max;
{
   struct Band *b;

   b = (struct Band *)malloc(sizeof(struct Band));
   if (!b) return(NULL);
   b->rmin = min;
   b->rmax = max;
   return(b);
}

void InitBands()
{
   NewList(&List0);
   NewList(&List1);
   NewList(&List2);

   AddHead(&List0, (struct Node *)CreateBand(MinRadius, MaxRadius));
   AddHead(&List1, (struct Node *)CreateBand(MinRadius, MaxRadius));
   AddHead(&List2, (struct Node *)CreateBand(MinRadius, MaxRadius));
}

void FreeBands()
{
   FreeList(&List0);
   FreeList(&List1);
   FreeList(&List2);
}

/*
 * Compute the amount of mass (of dust or gas) which the planet p will
 * sweep from the available material in one iteration.
 */
double swept_mass(list, listtype, p)
struct List *list;
short listtype;
struct Planet *p;
{
   double r, mass, min, max, density, t_gas;
   struct Node *n;
   struct Band *b;

   n_swept++;

   mass = 0.0;
   min = p->rmin;
   max = p->rmax;

   /* Account for eccentricity of dust particles */
   if (listtype == 0) {
      min = min / (1 + W);
      max = max / (1 - W);
   }

   /* Used in gas accretion, it's constant so we can move it out here.  */
   t_gas = K / ((K - 1) * pow(Critical_Mass / p->mass, beta) + 1);

   /*
    * Modification #3
    * Approximate density of material we're accreting.  This is actually
    * the density at the planet's orbit, but it's (hopefully) close enough.
    * It shouldn't matter for small planets, but large gas giants may
    * accrete too much.
    */
   /*
    * density = p->density;
    * if (listtype == 2) density *= t_gas;
   */

   /* Traverse the list, looking at each existing band to see what we
    * would sweep up.
    */
   n = list->lh_Head;
   while (n->ln_Succ) {
      b = (struct Band *)n;
      n = n->ln_Succ;

      /* check for trivial rejection */
      if (max < b->rmin || min > b->rmax) continue;

      n_swepti++;

      if (max > b->rmax) max = b->rmax;
      if (min < b->rmin) min = b->rmin;
      r = (min + max) / 2.0;

      /* Modification #3
       * If we were really strict, we'd try to integrate the density
       * function over the range (min, max) of orbital distance, but
       * we'll use the average distance instead.
       */
      density = Density(r);
      if (listtype == 2) density *= t_gas;

      /* The swept mass is supposed to be computed using the gravitational
       * reach and density at the minimum and maximum distances at which
       * dust is encountered.  I'm cheating here by using the reach at
       * the average orbital distance (computed in EvolvePlanet()) and
       * the density at the center of the band.  The total swept mass is
       * then 2 * reach        the height of the swept area
       *      * (max - min)    the width of the swept area
       *      2 * pi * r       revolve around center
       *      * density        the density of the swept volume
       * We can speed things up a bit by moving the constant values
       * outside the loop.
       */
      mass += r * (max - min);
   }
   return(2 * PI * 2 * p->reach * mass * density);
}

/*
 * Update the band structure by removing or splitting bands from which
 * the planet would have accreted mass.
 */
void update_bands(list, p)
struct List *list;
struct Planet *p;
{
   double min, max;
   struct Node *n;
   struct Band *b, *newband;

   min = p->rmin;   /* minimum and maximum reach of the planet */
   max = p->rmax;

   n = list->lh_Head;
   while (n->ln_Succ) {
      b = (struct Band *)n;
      n = n->ln_Succ;

      /* check for trivial rejection */
      if (max < b->rmin || min > b->rmax) continue;

      if (max < b->rmax) {
         if (min > b->rmin) { /* interval within band, so split it */
            newband = CreateBand(b->rmin, min);
            b->rmin = max;
            AddHead(list, (struct Node *)newband);
         } else { /* interval overlaps inner edge */
            b->rmin = max;
         }
      } else {
         if (min > b->rmin) { /* interval overlaps outer edge */
            b->rmax = min;
         } else { /* interval contains band, so kill it */
            Remove((struct Node *)b);
            free((char *)b);
            b = NULL;
         }
      }
   }
}

/*
 * Sweep up all available dust and gas.
 */
void EvolvePlanet(star, p)
struct Star *star;
struct Planet *p;
{
   double perihelion, aphelion, previous_mass, swept;

   if (!p) return;

   /* Our planetoid will accrete all matter within it's orbit . . . */
   perihelion = p->r * (1 - p->e);
   aphelion = p->r * (1 + p->e);

   Critical_Mass = B * pow(perihelion * sqrt(1.0 / star->luminosity), -0.75);

   for (;;) {
      n_evolvei++;

      /* . . . as well as within it's gravitational reach.  We should be
       * computing the reach at aphelion and at perihelion, but they
       * aren't that different so we'll cut out some computation.
       */
      p->reach = Reach(p->r, p->mass);
      p->rmax = aphelion + p->reach;    /* Reach(aphelion, p->mass); */
      p->rmin = perihelion - p->reach;  /* Reach(perihelion, p->mass); */

      previous_mass = p->mass;

      swept = swept_mass(&List0, 0, p);      /* accrete dust */
      p->mass_dust = max(p->mass_dust, swept);

      if (p->mass_dust > Critical_Mass) {    /* accrete gas */
         p->flags |= GAS;
         swept = swept_mass(&List2, 2, p);
         p->mass_gas = max(p->mass_gas, swept);
      }
      p->mass = p->mass_dust + p->mass_gas;

      if (((p->mass - previous_mass) / p->mass < 0.01)) break;
   }

   /* You'll notice we didn't modify the band structure at all while
    * accreting matter, we do that now.
    */
   update_bands(&List0, p);
   if (p->flags & GAS) {         /* do something with the gas density */
      /* In this case, it's cheaper to just recompute the accreted gas
       * in each iteration as we only use the one gas band.
       */
      /*
      update_bands(&List1, p);
      update_bands(&List2, p);
      */
   }
}

/*
 * We've found a collision, so we just stick the two planets together.
 * No fragments or moon creation, no close passes which would eject one
 * planet from the system, nothing fancy like that.  We weight the
 * final orbital radius by the masses of the planets involved, and
 * use the smaller eccentricity.
 */
struct Planet *MergePlanets(p1, p2)
struct Planet *p1, *p2;
{
   p2->r = (p1->mass + p2->mass) / ((p1->mass / p1->r) + (p2->mass / p2->r));
   p2->e = min(p1->e, p2->e);
   p2->mass += p1->mass;
   p2->mass_dust += p1->mass_dust;
   p2->mass_gas += p1->mass_gas;
   /* p2->density = Density(p2->r); */ /* Modification #3 */
   Remove((struct Node *)p1);
   free((char *)p1);
   return(p2);
}

/*
 * Let's see who 'p' will run into, if anyone.
 */
void CheckCoalesence(star, p)
struct Star *star;
struct Planet *p;
{
   struct Planet *p1;
   short merged = TRUE;

   while (merged) {
      merged = FALSE;
      for(;;) {
         p1 = (struct Planet *)p->pl_Node.ln_Pred;
         if (p1 == (struct Planet *)&star->PlanetList.lh_Head) break;
         if (p1->rmax >= p->rmin) {
            MergePlanets(p1, p);
            merged = TRUE;
         } else
            break;
      }
      for(;;) {
         p1 = (struct Planet *)p->pl_Node.ln_Succ;
         if (p1 == (struct Planet *)&star->PlanetList.lh_Tail) break;
         if (p1->rmin <= p->rmax) {
            MergePlanets(p1, p);
            merged = TRUE;
         } else
            break;
      }
      if (merged) EvolvePlanet(star, p);
   }
}

void CreateSystem(star)
struct Star *star;
{
   struct Planet *p;
   struct Node *n;
   short i;

   n_density = n_reach = n_swept = n_swepti = n_evolvei = n_nucleus = 0;

   /* A little initialization . . . */
   A = Ao * sqrt(star->mass);
   MinRadius = MINRADIUS * pow(star->mass, 0.33);
   MaxRadius = MAXRADIUS * pow(star->mass, 0.33);
   InitBands();

   /* . . . and we're off to play God. */
   while (!ListEmpty(&List0)) {
      if ((p = CreatePlanet(star)) == NULL) break;
      EvolvePlanet(star, p);
      CheckCoalesence(star, p);
   }

#ifdef DEBUG
   printf("%d nuclei injected\n", n_nucleus);
   printf("density = %d  reach = %d  swept = %d  swepti = %d  evolvei = %d\n",
           n_density, n_reach, n_swept, n_swepti, n_evolvei);
#endif

   FreeBands();

   i = 1;
   for (n = star->PlanetList.lh_Head; n->ln_Succ; n = n->ln_Succ) {
      p = (struct Planet *)n;
      if (p->mass != m0) {
         p->n = i++;
         ComputePlanetStats(star, p);
      }
   }
}


