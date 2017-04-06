
/*
 * Genstar.c : Generate a random star with realistic mass, luminosity,
 *             and spectral class.  That includes creating stars with
 *             a realistic distribution of types and classes.
 *
 * To use these functions, call InitGenStar() to initialize the
 * distribution, and then GenStar(struct Star *) to create a star.
 *
 * Author : Andrew Folkins
 *
 * This code is public domain, see the file 'display.c'.
 */

#include "system.h"

#ifdef MAIN
#include <stdio.h>
struct Star star;

#endif

#define MINMAG -7
#define MAXMAG 16
#define N_SPC_CLASS 7
#define N_MAG_CLASS 24
#define N_LUM_CLASS 8

/*
 * This table gives the approximate relative numbers of stars of the
 * various spectral types and luminosity classes, the units are stars
 * per million cubic parsecs. The program totals this information
 * and computes a cumulative distribution function from it for
 * actual use.  The spectral classes range from O on the left to M
 * on the right, the luminosities from an absolute magnitude of -7
 * at the top to +16 at the bottom.  Thus, the table looks roughly
 * like the traditional Hertzsprung-Russell diagram.
 *
 * One thing you'll notice about this, there's a *lot* of red dwarfs
 * in a realistic distribution, a star like the sun is in the top 10%
 * of the population.  This makes the occurance of habitable planets
 * pretty low.
 *
 * Most of this information is from a message I recived from John Carr
 * <athena.mit.edu!jfc> on April 19/88, he didn't mention his source
 * though he did make the comment that "the birthrate function is much
 * flatter at high luminosities than the luminosity function, due to
 * the short lifetime of high-mass stars.  This is important for young
 * areas."  I don't think that idea is accounted for here.
 */
float   StarCounts[N_MAG_CLASS][N_SPC_CLASS] =
{
/*        O        B        A        F        G        K        M       Mag */
  {  0.0002,  0.0005,  0.0003,  0.0003, 0.00003,       0,       0 }, /*  -7 */
  {  0.0005,  0.0025,   0.001,   0.001,  0.0001,  0.0004,  0.0004 }, /*  -6 */
  {   0.001,   0.025,    0.01,   0.006,   0.008,   0.004,    0.01 }, /*  -5 */
  {   0.003,    0.16,    0.01,   0.016,   0.025,   0.012,   0.012 }, /*  -4 */
  {    0.01,     0.5,    0.05,    0.08,    0.08,     0.1,    0.06 }, /*  -3 */
  {    0.01,     2.5,    0.08,     0.2,     0.3,     0.6,     0.4 }, /*  -2 */
  {    0.01,    12.5,       1,     1.6,       1,     2.5,       3 }, /*  -1 */
  {   0.001,      20,      20,       2,       8,      25,      10 }, /*  +0 */
  {       0,      30,     100,      30,      30,     120,      10 }, /*  +1 */
  {       0,      20,     200,     160,      50,     110,       0 }, /*  +2 */
  {       0,      10,      80,     700,     150,     100,       0 }, /*  +3 */
  {       0,       0,      30,    1200,     700,     100,       0 }, /*  +4 */
  {       0,       0,       0,     600,    2000,     300,       0 }, /*  +5 */
  {       0,       0,       0,     200,    1500,    1500,      10 }, /*  +6 */
  {       0,       0,       0,     100,     800,    3000,     100 }, /*  +7 */
  {       0,       0,       0,      10,     400,    2500,    1000 }, /*  +8 */
  {       0,       0,       0,       0,     200,    1500,    3000 }, /*  +9 */
  {       0,      10,       0,       0,       0,     400,    8000 }, /* +10 */
  {       0,     100,      30,      10,       0,     200,    9000 }, /* +11 */
  {       0,     200,     400,     100,       0,     100,   10000 }, /* +12 */
  {       0,     400,     600,     300,     100,     400,   10000 }, /* +13 */
  {       0,     800,    1000,    1000,     600,     800,   10000 }, /* +14 */
  {       0,    1500,    2000,    1000,    1500,    1200,    8000 }, /* +15 */
  {       0,    3000,    5000,    3000,    3000,       0,    6000 }, /* +16 */
};



#if 0
float   StarCounts[N_MAG_CLASS][N_SPC_CLASS] =
{
/*  O      B       A      F      G      K      M */
  {2E-4,   5E-4,   3E-4,  3E-4,  3E-5,  0,     0},
  {5E-4,   2.5E-3, 1E-3,  1E-3,  1E-4,  4E-4,  4E-4},
  {.001,   .025,   .010,  .006,  .008,  .004,  .010},
  {.003,   .16,    .01,   .016,  .025,  .012,  .012},
  {.01,    .50,    .05,   .08,   .08,   .1,    .06},
  {.01,    2.5,    .08,   .2,    .3,    .6,    .4},
  {.01,    12.5,   1,     1.6,   1,     2.5,   3},
  {.001,   20,     20,    2,     8,     25,    10},
  {0,      30,     100,   30,    30,    120,   10},
  {0,      20,     200,   160,   50,    110,   0},
  {0,      10,     80,    700,   150,   100,   0},
  {0,      0,      30,    1200,  700,   100,   0},
  {0,      0,      0,     600,   2000,  300,   0},
  {0,      0,      0,     200,   1500,  1500,  10},
  {0,      0,      0,     100,   800,   3000,  100},
  {0,      0,      0,     10,    400,   2500,  1000},
  {0,      0,      0,     0,     200,   1500,  3000},
  {0,      10,     0,     0,     0,     400,   8000},
  {0,      100,    30,    10,    0,     200,   9000},
  {0,      200,    400,   100,   0,     100,   10000},
  {0,      400,    600,   300,   100,   400,   10000},
  {0,      800,    1000,  1000,  600,   800,   10000},
  {0,      1500,   2000,  1000,  1500,  1200,  8000},
  {0,      3000,   5000,  3000,  3000,  0,     6000}
};
#endif

/* Absolute magnitude - anything of number or below is that class
 * e.g Class G, mag 5.0 is class V.  Most of this is guesstimates
 * from a H-R diagram.
 */
float   LClassMag[N_LUM_CLASS][N_SPC_CLASS] =
{
/*   O      B       A      F      G      K      M */
  {-6.5,  -6.5,   -6.5,  -6.5,  -6.5,  -6.5,  -6.5},	/* Ia */
  {-6.0,  -6.0,   -5.0,  -5.0,  -5.0,  -5.0,  -5.0},	/* Ib */
  {-5.0,  -3.5,   -3.0,  -2.0,  -2.0,  -2.5,  -2.5},	/* II */
  {-4.0,  -3.0,   -0.5,   1.5,   2.5,   3.0,   2.0},	/* III */
  {-3.0,  -2.0,    0.5,   2.5,   3.5,   5.5,   2.0},	/* IV */
  {-1.0,   2.0,    2.5,   5.0,   7.0,  10.0,  14.0},	/* V */
  { 1.0,   4.0,    5.0,   9.0,  10.0,  20.0,  20.0},	/* VI */
  {20.0,  20.0,   20.0,  20.0,  20.0,  20.0,  20.0},	/* VII */
};

char    SpectralClass[7] =
{'O', 'B', 'A', 'F', 'G', 'K', 'M'};
char   *LuminosityClass[8] =
{"Ia ", "Ib ", "II ", "III", "IV ", "V  ", "VI ", "VII"};

/*
 * Compute a cumulative distribution from the values in StarCounts[][]
 * by adding up all the values, then dividing each entry in the array
 * by the total.
 */
void
ComputeProbabilities(void)
{
  short   i,
          j;
  float   t,
          total;

  total = 0.0;
  for (i = 0; i < N_MAG_CLASS; i++)
    for (j = 0; j < N_SPC_CLASS; j++)
      total += StarCounts[i][j];

  t = 0.0;
  for (i = 0; i < N_MAG_CLASS; i++)
    for (j = 0; j < N_SPC_CLASS; j++)
    {
      t += StarCounts[i][j];
      StarCounts[i][j] = t / total;
    }
}

/*
 * Hey, let's make a star.
 */
void
GenStar(struct Star *s)
{
  short   i,
          j;
  float   t;

  s->rnd = drand48();
  for (i = 0; i < N_MAG_CLASS; i++)
    for (j = 0; j < N_SPC_CLASS; j++)
      if (StarCounts[i][j] >= s->rnd)
	goto found;

found:

  s->spc_class = SpectralClass[j];
  t = drand48();
  s->spc_subclass = t * 10;	/* Give it a random subclass */
  s->abs_magnitude = MINMAG + i + t;
  /* Compute luminosity relative to Sun */
  s->luminosity = pow(2.5118, 4.7 - s->abs_magnitude);

  for (i = 0; i < N_LUM_CLASS; i++)
    if (LClassMag[i][j] >= s->abs_magnitude)
      break;
  s->lum_class = i;

  switch (s->lum_class)
  {
  case 0:
  case 1:
  case 2:
  case 3:
    /* Supergiants & giants */
    t = log(s->luminosity) + (drand48() / 5.0);
    s->mass = exp(t / 3.0);
    break;
  case 4:
  case 5:
  case 6:
    /* subgiants, dwarfs, subdwarfs */
    t = log(s->luminosity) + 0.1 + (drand48() / 5.0 - 0.1);
    s->mass = exp(t / 4.1);
    break;
  case 7:
    /* white dwarfs */
    s->mass = 0.7 * drand48() + 0.6;
    break;
  }
  s->r_ecos = sqrt(s->luminosity);
  s->r_inner = 0.93 * s->r_ecos;
  s->r_outer = 1.1 * s->r_ecos;	/* approximately */
}

/*
 * Call this before you do anything else.
 */
void
InitGenStar(void)
{
  short   seed[3];

  seed[0] = time(NULL) >> 16;
  seed[1] = time(NULL) & 0xFFFF;
  seed[2] = time(NULL) & 0xFFFF;
  srand48(seed);

  ComputeProbabilities();
}

#ifdef MAIN
void
PrintStar(s)
struct Star *s;
{
  printf("%c%d %s ", s->spc_class, s->spc_subclass, LuminosityClass[s->lum_class]);
  printf("Abs mag  %5.2f  ", s->abs_magnitude);
  printf("Luminosity %10.3f  ", s->luminosity);
  printf("Mass %8.5f ", s->mass);
  printf("\n");
}

int
main(int argc, char **argv)
{
  short   i;

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
        case 'S':
          {
            int i, j;
            printf("{\n");
            printf("/*  ");
            for (j = 0; j < N_SPC_CLASS; j++)
              printf("%7c  ", SpectralClass[j]);
            printf("     Mag */\n");
            for (i = 0; i < N_MAG_CLASS; i++)
            {
              printf("  { ");
              for (j = 0; j < N_SPC_CLASS; j++)
              {
                char buff[16];
                if (StarCounts[i][j] < 1)
                {
                  char *p;
                  sprintf(buff, "%7.5f", StarCounts[i][j]);
                  for (p = strchr(buff, 0); p - buff > 1; p--)
                  {
                    if (p[-1] == '0' || p[-1] == '.')
                      p[-1] = 0;
                    else
                      break;
                  }
                }
                else
                  sprintf(buff, "%7.7g", StarCounts[i][j]);
                printf("%7.7s%s ", buff, j==N_SPC_CLASS-1 ? "" : ",");
              }
              printf("}, /* %+3d */\n", i-7);
            }
            printf("};\n");
          }
          return 0;
      }
    }
  }
  InitGenStar();
  for (i = 0; i < 20; i++)
  {
    GenStar(&star);
    PrintStar(&star);
  }
  return 0;
}
#endif
