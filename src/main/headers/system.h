
/*
 * System.h : Header file for planetary system generation program.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 */

/*
 * For you non-Amiga types, all linked list handling is done using the
 * List structure to define a doubly-linked list, and a Node structure in
 * each element of the list.  Simple routines for inserting and deleting
 * are provided, though the code for traversing a list is a bit ugly.
 */

#ifdef AMIGA
#include <exec/types.h>
#include <exec/lists.h>
#else
#include "list.h"
#define PI      3.14159265358979323846
#define TRUE    1
#define FALSE   0
#endif

#include <stdlib.h>
#include <math.h>

typedef struct Star   Star;
typedef struct Planet Planet;

struct Star {
   short spc_class;
   short spc_subclass;
   short lum_class;
   float rnd;             /* random seed to generate system */
   float mass;
   float luminosity;
   float abs_magnitude;
   float r_inner;         /* inner limit of ecosphere */
   float r_ecos;
   float r_outer;         /* outer limit of ecosphere */
   List PlanetList;
};

struct Planet {
   Node pl_Node;
   double mass;
   double mass_dust;
   double mass_gas;
   double radius;
   double r;
   double e;
   double density;
   double esc_velocity;
   double year;
   double rotation_rate;
   double surface_gravity;
   double temperature;
   double rmin;            /* Inner limit of gravitational reach */
   double rmax;            /* Outer limit of gravitational reach */
   double reach;           /* Gravitational reach */
#define GAS      1
   short flags;
   short n;                /* Planet number */
   short x, y, dradius;    /* rendering information */
};

extern char SpectralClass[7];
extern char *LuminosityClass[8];

extern void InitGenStar(void);
extern void GenStar(struct Star *);

#define ListEmpty(list) ((list)->head == NULL)
extern void InitList(struct List *),
            FreeList(struct List *);

extern void CreateSystem(struct Star *);



