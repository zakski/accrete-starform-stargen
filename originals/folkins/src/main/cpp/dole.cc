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
 *
 *  2000-01-07 Modified for C++ by Chris Croughton <chris@keris.net>
 *
 *  $Log: dole.cc,v $
 *  Revision 2.7  2000/02/22 16:24:57  chrisc
 *  Clear planet and moon vectors before generating them, alter density
 *  function for moons (again)
 *
 *  Revision 2.6  2000/02/21 09:23:11  chrisc
 *  Use local list of planets, copy it to the appropriate vector in the
 *  struct passed in.
 *
 *  Revision 2.5  2000/02/03 17:38:16  chrisc
 *  REject 'planets' with a mass < 10 Mo
 *
 *  Revision 2.4  2000/01/31 10:06:42  chrisc
 *  Rework density and other calculations for moond
 *
 *  Revision 2.3  2000/01/28 13:17:24  chrisc
 *  Use planet's mass instead of its radius for min. moon band distance
 *
 *  Revision 2.2  2000/01/27 08:36:15  chrisc
 *  Add debug stuff.  Use mass_dust (not total mass) of planets when
 *  creating moons.
 *
 *  Revision 2.1  2000/01/20 17:55:06  chrisc
 *  Converted to MKS
 *
 *  Revision 2.0  2000/01/20 10:23:15  chrisc
 *  Start of MKS conversion
 *
 *  Revision 1.6  2000/01/20 10:01:50  chrisc
 *  Comment changes, preparatory to MKS conversion
 *
 *  Revision 1.5  2000/01/13 17:55:40  chrisc
 *  Add code to generate moons
 *
 *  Revision 1.4  2000/01/07 16:18:25  chrisc
 *  Make the critical mass 0.1 Msol (just over "brown dwarf" size)
 *
 *  Revision 1.3  2000/01/07 13:12:23  chrisc
 *  Converted to C++
 *
 */

#ifndef DEBUG
#define DEBUG 0
#endif

static int debug = DEBUG;

#include <cstdio>
#include <cstdlib>

#include "rand.h"
#include "system.h"
#include "const.h"

// Unfortunately, some systems have functions called alpha, beta and gamma
// (especially gamma() which is a mathematical function).  So that we can use
// them as variables, I #define them to local names...

#define alpha   _our_alpha
#define beta    _our_beta
#define gamma   _our_gamma

// Similarly with min and max functions
 
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

/* coeff. of cloud density (Msol / AU**3) */
static const double  Ao = 0.0015 * Msol / (AU*AU*AU);

/* cloud density parameter */
static const double  alpha = 5.0;

/* cloud density parameter */
static const double  gamma = 0.33;

/* ratio of overall density to density of dust */
static const double  K = 50;

/* eccentricity of cloud particles */
static const double  W = 0.20;

/* nuclei mass (solar masses) */
static const double  m0 = 1E-15 * Msol;

/* critical mass paramter (solar masses) */
static const double  B = 1.2E-5 * Msol;

/* gas capture parameter */
static const double  beta = 0.5;


static double  A;              /* Ao * sqrt(star->mass) */

static double  CvtRadius;
static double  MinRadius;     /* of planetismal injection, = MINRADIUS */
static double  MaxRadius;     /* MAXRADIUS modified by luminosity of primary */

#define MINRADIUS          0.3*AU
#define MAXRADIUS          50*AU
#define MAX_ECCENTRICITY   0.20 /* of dust particles */

typedef struct Band Band;

typedef std::list<Band>   BandList;
typedef std::list<Planet> PList;

struct Band
{                      /* Band of gas or dust */
  double  rmin;        /* radius of inner edge */
  double  rmax;        /* radius of outer edge */
};

static BandList    List0;         /* bands containing gas and dust */
static BandList    List1;         /* bands containing gas only */
static BandList    List2;         /* bands containing some gas */

static PList       planets;

static double  Critical_Mass; /* for accreting gas */

static short   n_density = 0; /* iteration counters for profiling */
static short   n_reach = 0;
static short   n_swept = 0;
static short   n_swepti = 0;
static short   n_evolvei = 0;
static short   n_nucleus = 0;

static bool moons = false;

/* Compute the physical parameters of a planet */
// extern void ComputePlanetStats(Star *, Planet *);

static double
between(double a, double b)
{
  double d = b - a;
  double r = drand48() * d;
  return a + r;
}

/*
 * I'd really like to speed these up, the program spends 50% of it's
 * time in just these two routines.
 */
static double
Density(double r)
{
  n_density++;
  double dens;
  if (moons)
  {
    double cm = CvtRadius / MaxRadius;
    double rm = r / MaxRadius;
    double rr = rm - cm;
    dens = A * exp(-rr*rr * 9) * pow(1-rm, (1 - cm*cm)/2) / rm;
  }
  else
    dens = A * exp(-alpha * pow(r/AU, gamma));
  return dens;
}

static double
Reach(double radius, double mass)
{
  n_reach++;
  return (radius * pow(mass / (Msol + mass), 0.25));
}

static void
dumpPlanets(PList& list, PList::iterator newp)
{
  if (debug)
  {
    int     num = 1;
    double  factor = (moons ? 1000000 : AU);
    printf("%2s%3s  %12s  %9s %12s     %12s  %8s\n", 
	"", "", "Radius", "min", "max", "Reach", "Mass");
    for (PList::iterator n = list.begin(); n != list.end(); n++)
    {
      printf("%2s%3d  %12.3f (%12.3f %12.3f) %12.4f  %8.2f\n",
	  (n == newp ? "->" : ""),
	  num++,
	  n->r / factor,
	  n->rmin / factor,
	  n->rmax / factor,
	  Reach(n->r, n->mass) / factor,
	  log(n->mass / Msol) / log(10) + 15);
    }
    printf("\n");
  }
}

static PList::iterator
AddPlanet(PList& list, Planet& newp)
{
  PList::iterator p;
  /* Keep the list sorted by orbital radius. */
  PList::iterator n;
  for (n = list.begin(); n != list.end(); n++)
    if (n->r > newp.r)
      break;
  p = list.insert(n, newp);
  return p;
}

static PList::iterator
CreatePlanet(Star& star, double eccmod=-1)
{
  PList::iterator p;
  Planet newp;
  bool ismoon = (eccmod > 0);

  newp.flags = 0;
  newp.mass = m0;
  newp.mass_dust = m0;
  newp.mass_gas = 0;
  newp.e = 1.0 - pow(drand48()*0.99+0.01, 0.077);
  newp.r = drand48();
  newp.r = newp.r * newp.r;
  // Fire all nuclei in at random now...

  // frig eccentricity if it's a moon
  if (ismoon)
    newp.e = pow(newp.e, eccmod);
  else
    newp.e *= 2;
  if (newp.e > 0.9)
    newp.e = drand48() * 0.7 + 0.2;

  newp.r = MinRadius + (MaxRadius - MinRadius) * newp.r;

  newp.rmin = newp.r;
  newp.rmax = newp.r;
  /* newp.density = Density(newp.r); *//* Modification #3 */
  newp.n = 0;                  /* planet number */
  newp.x = newp.y = 0;        /* screen position */
  n_nucleus++;
  p = AddPlanet(planets, newp);
  if (debug)
  {
    printf("Insert new planet\n");
    dumpPlanets(planets, p);
  }
  return (p);
}

static Band
CreateBand(double min, double max)
{
  Band b;
  b.rmin = min;
  b.rmax = max;
  return (b);
}

static void
InitBands(void)
{
  List0.push_back(CreateBand(MinRadius, MaxRadius));
  List1.push_back(CreateBand(MinRadius, MaxRadius));
  List2.push_back(CreateBand(MinRadius, MaxRadius));
}

static void
FreeBand(BandList& list)
{
  for (BandList::iterator b = list.begin(); b != list.end(); )
    b = list.erase(b);
}

static void
FreeBands(void)
{
  FreeBand(List0);
  FreeBand(List1);
  FreeBand(List2);
}

/*
 * Compute the amount of mass (of dust or gas) which the planet p will
 * sweep from the available material in one iteration.
 */
static double
swept_mass(BandList& list, short int listtype, Planet& p)
{
  double  r;
  double  mass;
  double  min;
  double  max;
  double  density;
  double  t_gas;
  BandList::iterator b;

  n_swept++;

  mass = 0.0;
  min = p.rmin;
  max = p.rmax;

  /* Account for eccentricity of dust particles */
  if (listtype == 0)
  {
    min = min / (1 + W);
    max = max / (1 - W);
  }

  /* Used in gas accretion, it's constant so we can move it out here.  */
  t_gas = K / ((K - 1) * pow(Critical_Mass / p.mass, beta) + 1);

  /*
   * Modification #3
   * Approximate density of material we're accreting.  This is actually
   * the density at the planet's orbit, but it's (hopefully) close enough.
   * It shouldn't matter for small planets, but large gas giants may
   * accrete too much.
   */
  /*
   * density = p.density;
   * if (listtype == 2) density *= t_gas;
   */

  /* Traverse the list, looking at each existing band to see what we
   * would sweep up.
   */
  for (b = list.begin(); b != list.end(); b++)
  {
    /* check for trivial rejection */
    if (max < b->rmin || min > b->rmax)
      continue;

    n_swepti++;

    if (max > b->rmax)
      max = b->rmax;
    if (min < b->rmin)
      min = b->rmin;
    r = (min + max) / 2.0;

    /* Modification #3
     * If we were really strict, we'd try to integrate the density
     * function over the range (min, max) of orbital distance, but
     * we'll use the average distance instead.
     */
    density = Density(r);
    if (listtype == 2)
      density *= t_gas;

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
    mass += r * (max - min) * density;
  }
  return (2 * PI * 2 * p.reach * mass);
}

static void
dispbands(BandList& list, BandList::iterator band, const char *str)
{
  if (debug)
  {
    double factor = (moons ? 1000000 : AU);
    int w = strlen(str);
    for (BandList::iterator b = list.begin(); b != list.end(); b++)
    {
      printf("%-*s %2s %12.3f %12.3f  dens  %12g %12g\n",
	  w, str,
	  (b == band ? "->" : ""),
	  b->rmin/factor, b->rmax/factor,
	  Density(b->rmin), Density(b->rmax));
      str = "";
    }
  }
}

/*
 * Update the band structure by removing or splitting bands from which
 * the planet would have accreted mass.
 */
static void
update_bands(BandList& list, Planet& p)
{
  double  min;
  double  max;
  BandList::iterator b;
  Band   newband;

  min = p.rmin;                /* minimum and maximum reach of the planet */
  max = p.rmax;

  for (b = list.begin(); b != list.end(); )
  {
    /* check for trivial rejection */
    if (max < b->rmin || min > b->rmax)
    {
      b++;
      continue;
    }

    if (max < b->rmax)
    {
      if (min > b->rmin)
      {                         /* interval within band, so split it */
        newband = CreateBand(b->rmin, min);
        b->rmin = max;
        list.insert(b, newband);
        dispbands(list, b, "Split bands");
        b++;
      }
      else
      {                         /* interval overlaps inner edge */
        b->rmin = max;
        b++;
      }
    }
    else
    {
      if (min > b->rmin)
      {                         /* interval overlaps outer edge */
        b->rmax = min;
        b++;
      }
      else
      {                         /* interval contains band, so kill it */
        dispbands(list, b, "Remove band");
        b = list.erase(b);
      }
    }
  }
}

/*
 * Sweep up all available dust and gas.
 */
static void
EvolvePlanet(Star& star, Planet& p)
{
  double  perihelion;
  double  aphelion;
  double  previous_mass;
  double  swept;

  /* Our planetoid will accrete all matter within it's orbit . . . */
  perihelion = p.r * (1 - p.e);
  aphelion = p.r * (1 + p.e);

  Critical_Mass = B * pow(sqrt(star.luminosity) / (perihelion/AU), 0.75);

  for (;;)
  {
    n_evolvei++;

    perihelion = p.r * (1 - p.e);
    aphelion = p.r * (1 + p.e);
    /* . . . as well as within it's gravitational reach.  We should be
     * computing the reach at aphelion and at perihelion, but they
     * aren't that different so we'll cut out some computation.
     */
    p.reach = Reach(p.r, p.mass);
    p.rmax = aphelion + p.reach;      /* Reach(aphelion, p.mass); */
    p.rmin = perihelion - p.reach;    /* Reach(perihelion, p.mass); */

    if (p.rmin < 1)
      p.rmin = 1;

    previous_mass = p.mass;

    swept = swept_mass(List0, 0, p);   /* accrete dust */
    p.mass_dust = max(p.mass_dust, swept);

    p.mass_gas  = max(p.mass_gas, swept*drand48()*p.mass/Msol);

    if (p.mass_dust > Critical_Mass)   /* accrete gas */
    {
      p.flags |= GAS;
      swept = swept_mass(List2, 2, p);
      p.mass_gas = max(p.mass_gas, swept);
    }
    p.mass = p.mass_dust + p.mass_gas;

    if (((p.mass - previous_mass) / p.mass < 0.01))
      break;
  }

  /* You'll notice we didn't modify the band structure at all while
   * accreting matter, we do that now.
   */
  update_bands(List0, p);
  if (p.flags & GAS)
  { /* do something with the gas density */
    /* In this case, it's cheaper to just recompute the accreted gas
     * in each iteration as we only use the one gas band.
     */
    update_bands(List1, p);
    update_bands(List2, p);
  }
}

/*
 * We've found a collision, so we just stick the two planets together.
 * No fragments or moon creation, no close passes which would eject one
 * planet from the system, nothing fancy like that.  We weight the
 * final orbital radius by the masses of the planets involved, and
 * use the smaller eccentricity.
 */
static PList::iterator
MergePlanets(PList& list, PList::iterator p1, PList::iterator p2)
{
  double  perihelion;
  double  aphelion;
  if (debug)
  {
    printf("Merge planets\n");
    dumpPlanets(list, p1);
  }
  p2->r = (p1->mass + p2->mass) / ((p1->mass / p1->r) + (p2->mass / p2->r));

  p2->e = (p1->e * p1->mass + p2->e * p2->mass) / (p1->mass + p2->mass);
  p2->e = between(fabs(p1->e - p2->e), p1->e + p2->e);
  p2->e = min(p1->e, p2->e);

  perihelion = p2->r * (1 - p2->e);
  aphelion = p2->r * (1 + p2->e);
  p2->rmax = aphelion + Reach(aphelion, p2->mass);
  p2->rmin = perihelion - Reach(perihelion, p2->mass);
  p2->mass += p1->mass;
  p2->mass_dust += p1->mass_dust;
  p2->mass_gas += p1->mass_gas;
  /* p2->density = Density(p2->r); *//* Modification #3 */
  list.erase(p1);
  return p2;
}

/*
 * Let's see who 'p' will run into, if anyone.
 */
static void
CheckCoalesence(Star& star, PList::iterator p)
{
  PList::iterator p1;
  short   merged = TRUE;

  while (merged)
  {
    merged = FALSE;
    while ( p != planets.begin())
    {
      p1 = p;
      p1--;
      if (p1->rmax >= p->rmin)
      {
        MergePlanets(planets, p1, p);
        merged = TRUE;
      }
      else
        break;
    }
    for (;;)
    {
      p1 = p;
      p1++;
      if (p1 == planets.end())
        break;
      if (p1->rmin <= p->rmax)
      {
        MergePlanets(planets, p, p1);
        p = p1;
        merged = TRUE;
      }
      else
        break;
    }
    if (merged)
      EvolvePlanet(star, *p);
  }
  // if it gets too close to the primary, break it up
  if (p->r * (1 - p->e) < MinRadius)
  {
    // p->flags |= FRAGMENTS;
    // planets.erase(p);
  }
}

void
CreateSystem(Star& star)
{
  Planet p;
  short  i;

  moons = false;

  n_density = n_reach = n_swept = n_swepti = n_evolvei = n_nucleus = 0;

  /* A little initialization . . . */
  A = Ao * sqrt(star.mass/Msol);
  MinRadius = MINRADIUS * pow(star.mass/Msol, 0.33);
  MaxRadius = MAXRADIUS * pow(star.mass/Msol, 0.33);
  CvtRadius = 1*AU;
  InitBands();
  dispbands(List0, NULL, "Band 0");
  dispbands(List1, NULL, "Band 1");
  dispbands(List2, NULL, "Band 2");

  /* . . . and we're off to play God. */
  while (List0.size() > 0)
  {
    PList::iterator p = CreatePlanet(star);
    EvolvePlanet(star, *p);
    CheckCoalesence(star, p);
  }

  FreeBands();

  if (debug)
  {
    printf("%d nuclei injected\n", n_nucleus);
    printf("density = %d  reach = %d  swept = %d  swepti = %d  evolvei = %d\n",
	n_density, n_reach, n_swept, n_swepti, n_evolvei);
    printf("\n");

    printf("End of creation\n");
    dumpPlanets(planets, NULL);
  }

  star.planet.clear();
  i = 1;
  for (PList::iterator n = planets.begin(); n != planets.end(); n++)
  {
    if (n->mass != m0 * 10)
    {
      if (debug)
	printf("copy planet %d\n", i);
      n->n = i++;
      star.planet.push_back(*n);
    }
  }
  planets.clear();
}

// M/R2 = m/r2  r2 = R2 m/M

void
CreateMoons(Star& star, Planet& planet)
{
  Planet p;
  Star   s;
  short  i;

  moons = true;

  if (planet.mass < m0 * 100)
    return;

  n_density = n_reach = n_swept = n_swepti = n_evolvei = n_nucleus = 0;

  // Calculate Roche limit based on planet's mass with assumed density
  // as for Earth (at worst it will be a bit close, we'll handle actual
  // Roche limits elsewhere to create rings if we need to).
  
  double rad = pow(3/(4*PI) * planet.mass / 5500, 0.3333333);
  MinRadius = 2.4 * rad;
  MaxRadius = Reach(planet.r, planet.mass) / (10 + star.luminosity);

  // mrad is the point at which the pull of the star is the twice that of the
  // planet (this is not the same as the L1 point, it's further out beacuse it
  // doesn't take into account the orbital velocity, but it represents the
  // point at which the star's gravitational pull will seriously perturb the
  // orbit of a moon).
  double mrad = planet.r * sqrt(planet.mass / star.mass) * 2;
  if (MaxRadius > mrad)
    MaxRadius = mrad;

  if (MaxRadius < MinRadius * 2)
    return;

  CvtRadius = MinRadius * 50 / (1 + pow(planet.mass/Me, 0.3));
  if (CvtRadius > MaxRadius * 0.95)
    CvtRadius = MaxRadius * 0.95;
    // CvtRadius = MaxRadius / (1 + pow(planet.mass/Me, 0.3)) + MinRadius;

  A = 1;
  double totmass = 0;
  for (double r = MinRadius+rad/20; r < MaxRadius; r += rad/10)
    totmass += r/AU * rad/AU/10 * Density(r);
  
  A = Ao * 0.01 * sqrt(planet.mass_dust/Me) / totmass;
  A *= pow(drand48(), (1 + Me/planet.mass)/2);

  if (debug)
  {
    printf("\np.mass    = %8.4g Me (log = %0.2f)\n", 
	   planet.mass/Me,
           log(planet.mass / Msol) / log(10) + 15);
    printf("orbit rad = %8.2f AU\n", planet.r / AU);
    printf("MinRadius = %8.0f km\n", MinRadius/1000);
    printf("CvtRadius = %8.0f km\n", CvtRadius/1000);
    printf("MaxRadius = %8.0f km\n", MaxRadius/1000);
    printf("RadRadius = %8.0f km\n", mrad/1000);
    printf("A = %g\n", A/Msol);
    printf("\n");
    for (double r = MinRadius + MaxRadius/40; r <= MaxRadius; r += MaxRadius/20)
      printf("Density %10.0f = %g\n", r/1000, Density(r)*r*rad);
    printf("\n");
  }

  InitBands();
  dispbands(List0, NULL, "Band 0");
  dispbands(List1, NULL, "Band 1");
  dispbands(List2, NULL, "Band 2");

  s.mass = planet.mass;
  s.luminosity = star.luminosity / pow(planet.r/AU, 2);

  double eccmod = pow(planet.mass/(20*Me), 0.8);
  if (eccmod > 0.9)
    eccmod = 0.9;

  /* . . . and we're off to play God. */
  while (List0.size() > 0)
  {
    PList::iterator p = CreatePlanet(s, eccmod);
    EvolvePlanet(s, *p);
    CheckCoalesence(s, p);
  }

  FreeBands();

  if (debug)
  {
    printf("%d nuclei injected\n", n_nucleus);
    printf("density = %d  reach = %d  swept = %d  swepti = %d  evolvei = %d\n",
	n_density, n_reach, n_swept, n_swepti, n_evolvei);
    printf("\n");

    printf("End of creation\n");
    dumpPlanets(planets, NULL);
  }

  planet.moon.clear();
  i = 1;
  for (PList::iterator n = planets.begin(); n != planets.end(); n++)
  {
    if (n->mass > m0 * 10)
    {
      if (debug)
	printf("copy moon %d\n", i);
      n->e = pow(n->e, 1/eccmod);
      n->n = i++;
      planet.moon.push_back(*n);
    }
  }
  planets.clear();
}

void
doleDebug(int val)
{
  debug = val;
}

