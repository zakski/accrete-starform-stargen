#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct StellarTypeS StellarType;

struct StellarTypeS
{
  const char *star_class;
  double      temp;
  const char *balmer;
  const char *lines;
  double      mass;
  double      size;
  double      density;
  double      lum;
  double      star_age;
};

StellarType StarType[] =
{
/*  Type  Tsurf   Balmer     Other Lines     Mrel  Rrel  rho   Lrel   MS Age */
/*         max    lines                                                years */
  {"O0",  1e10,  "weak",    "He+ O-II He-II", 40,  17.8, 0.01, 405000,  1e6},
  {"B0", 30000,  "medium",  "He",             18,  7.4,  0.1,  13000,  11e6},
  {"A0", 12000,  "strong",  "",               3.5,  2.5, 0.3,  80,    440e6},
  {"F0",  7500,  "medium",  "",               1.7,  1.4, 1.0,  6.4,     3e9},
  {"G0",  6000,  "weak",    "Ca++ Fe++",      1.1,  1.0, 1.4,  1.4,     8e9},
  {"K0",  5000,  "v. weak", "Ca++ Fe++",      0.8,  0.8, 1.8,  0.46,   17e9},
  {"M0",  3500,  "v. weak", "Ca++ TiO2",      0.5,  0.6, 2.5,  0.08,   56e9},
  {"D0",  1500,  "none",    "",               0,    0,   2.5,  0.00,   56e9},
  {NULL, 0, 0, 0, 0, 0, 0, 0, 0}
};

StellarType *
starFindByMass(double mass)
{
  StellarType *p = StarType;

  while (p->star_class && mass <= p->mass)
    p++;
  return (p->star_class ? p : NULL);
}

StellarType *
starFindByTemp(double temp)
{
  StellarType *p = StarType;

  while (p->star_class && temp <= p->temp)
    p++;
  return (p->star_class ? p : NULL);
}

const char *
starFindClass(double mass, double temp)
{
  static char star_class[16];
  double      dm;
  int         sub;
  StellarType *p = starFindByTemp(temp);

  mass = mass; /* not used at present */

  if (!p)
    return NULL;
  if (p == StarType)
    return p->star_class;

  --p;
  /* p -> smallest star with more mass than wanted */
  dm = p->temp - p[1].temp;
  sub = (int)(10 * (p->temp - temp) / dm);

  sprintf(star_class, "%c%d", p->star_class[0], sub);
  return star_class;
}

#ifdef TEST

int
main(int argc, char **argv)
{
  int         i;

  for (i = 1; i < argc; i++)
  {
    const char *star_class = starFindClass(atof(argv[i]), 0);

    printf("Mass %-8g  star_class %s\n", 
	   atof(argv[i]), star_class ? star_class : "brown dwarf");
  }
  return 0;
}

#endif
