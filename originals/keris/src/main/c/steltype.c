#include <stdio.h>

#include "steltype.h"

stellar_type STAR_TYPES[] =
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

stellar_type* find_stellar_type_by_mass(double mass)
{
  stellar_type *p = STAR_TYPES;

  while (p->star_class && mass <= p->mass)
    p++;
  return p->star_class ? p : NULL;
}

stellar_type* find_stellar_type_by_temp(double temperature)
{
  stellar_type *p = STAR_TYPES;

  while (p->star_class && temperature <= p->temp)
    p++;
  return p->star_class ? p : NULL;
}

const char* find_star_class(double temperature)
{
  static char star_class[16];
  double      dm;
  int         sub;
  stellar_type *p = find_stellar_type_by_temp(temperature);

  if (!p)
    return NULL;
  
  if (p == STAR_TYPES)
    return p->star_class;

  --p;
  
  /* p -> smallest star with more mass than wanted */
  dm = p->temp - p[1].temp;
  sub = (int)(10 * (p->temp - temperature) / dm);

  sprintf(star_class, "%c%d", p->star_class[0], sub);
  return star_class;
}
