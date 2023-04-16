#ifndef _STARFORM_H
#define _STARFORM_H

#include "const.h"
#include "structs.h"

typedef struct 
{
  double        star_mass_r;
  double        star_lum_r;
  double        star_radius_r;
  double        star_temp;
  double        main_seq_life;
  double        star_age;
  double        r_ecosphere;
  double        r_greenhouse;
  char          star_class[17];
  int           resonance;
  unsigned long random_seed;
  planet*       first_planet;
} stellar_system;

void init(void);
stellar_system* generate_stellar_system(unsigned long random_seed);
void free_stellar_system(stellar_system* system);

#endif
