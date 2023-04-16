#ifndef _STELTYPE_H
#define _STELTYPE_H

typedef struct
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
} stellar_type;

extern stellar_type STAR_TYPES[];

const char* find_star_class(double temperature);

#endif
