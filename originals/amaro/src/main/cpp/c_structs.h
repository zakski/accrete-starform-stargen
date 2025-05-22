#ifndef C_STRUCTS_H
#define C_STRUCTS_H

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct star2 {
  long double		luminosity;
  long double		mass;
  long double		eff_temp;
  char *		spec_type;
  long double		m2;
  long double		e;
  long double		a;
  long double		inc;
  long double		an;
  char *		desig;
  int			in_celestia;
  char *		name;
} old_star;

#ifdef __cplusplus
}
#endif

#endif
