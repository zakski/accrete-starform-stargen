
/*
 * System.h : Header file for planetary system generation program.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 *
 * 2000-01-07 Modified for C++ by Chris Croughton <chris@keris.net>
 *
 */


#define PI      3.14159265358979323846
#define TRUE    1
#define FALSE   0

#include <stdlib.h>
#include <math.h>

#include <vector>
#include <list>

typedef struct Star     Star;
typedef struct Planet   Planet;
typedef vector<Planet>  PlanetList;

struct Object
{
   double mass;
   double radius;
   float  age;
   float  luminosity;
   float  temperature;
   Object() : mass(0), radius(0), age(0), luminosity(0), temperature(0) {}
};

struct Planet : public Object
{
   double mass_dust;
   double mass_gas;
   double r;
   double e;
   double density;
   double esc_velocity;
   double year;
   double rotation_rate;
   int    locked;
#define LOCKED_STAR -1
#define LOCKED_PRIM -2
   double surface_gravity;
   double rmin;            /* Inner limit of gravitational reach */
   double rmax;            /* Outer limit of gravitational reach */
   double reach;           /* Gravitational reach */
#define GAS         1
#define FRAGMENTS   2
#define BROWN_DWARF 4
#define STAR        8
   short flags;
   short n;                /* Planet number */
   short x, y, dradius;    /* rendering information */
   PlanetList moon;
   Planet() : mass_dust(0), mass_gas(0), r(0), e(0), density(0),
              esc_velocity(0), year(0), rotation_rate(0), surface_gravity(0),
              rmin(0), rmax(0), reach(0), flags(0), n(0), x(0), y(0),
	      dradius(0), locked(0), Object()
   {
   }

};

struct Star : public Object
{
   double rnd;             /* random seed to generate system */
   short  spc_class; 
   short  spc_subclass; 
   short  lum_class;
   double abs_magnitude;
   double lifetime;
   double r_inner;         /* inner limit of ecosphere */
   double r_ecos;
   double r_outer;         /* outer limit of ecosphere */
   PlanetList planet;
   Star(const Object& o=Object()) : 
     spc_class(0), spc_subclass(0), lum_class(0), rnd(0),
     abs_magnitude(0), lifetime(0), r_inner(0), r_ecos(0), r_outer(0),
     Object(o)
   {}
};


extern void  InitGenStar(void);
extern void  GenStar(struct Star *);
extern Star& GenStarDetails(Star& s);
extern Star  GenStarFromMass(double mass);

extern void CreateSystem(Star&);
extern void CreateMoons(Star& star, Planet& planet);

extern void doleDebug(int val);


