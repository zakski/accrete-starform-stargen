#ifndef _ELEMENTS_H
#define _ELEMENTS_H

typedef struct
{
  int         num;
  char       *symbol;
  char       *name;
  double      weight;
  double      melt;
  double      boil;
  double      density;
  double      abunde;
  double      abunds;
  double      reactivity;
} element;

extern element elements[];

char *find_liquid_elements_at_temp(char *out, double temperature);
char *sort_elements_by_melting_point(char *list);
int   make_element_vector(char *str, element ** vec, int max);
char *find_gas_elements_at_temp(char *out, double temperature);
char *sort_elements_by_abundance(char *list);
char *sort_elements_reverse(char *list);

#endif
