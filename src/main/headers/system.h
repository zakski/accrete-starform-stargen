
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

#include <exec/types.h>
#include <exec/lists.h>
#include <math.h>

struct Star {
   short spc_class, spc_subclass, lum_class;
   float rnd,             /* random seed to generate system */
         mass,
         luminosity,
         abs_magnitude,
         r_inner,         /* inner limit of ecosphere */
         r_ecos,
         r_outer;         /* outer limit of ecosphere */
   struct List PlanetList;
};

struct Planet {
   struct Node pl_Node;
   double mass,
          mass_dust, mass_gas,
          radius,
          r,
          e,
          density,
          esc_velocity,
          year,
          rotation_rate,
          surface_gravity,
          temperature;
   double rmin,            /* Inner limit of gravitational reach */
          rmax,            /* Outer limit of gravitational reach */
          reach;           /* Gravitational reach */
#define GAS      1
   short flags,
         n;                /* Planet number */
   short x, y, dradius;    /* rendering information */
};

extern char SpectralClass[7];
extern char *LuminosityClass[8];

extern void InitGenStar();
extern void GenStar(struct Star *);

#define ListEmpty(list) ((list)->lh_Head->ln_Succ == NULL)
extern void InitList(struct List *),
            FreeList(struct List *);

extern void CreateSystem(struct Star *);


