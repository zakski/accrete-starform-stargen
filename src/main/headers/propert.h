#ifndef _PROPERT_H
#define _PROPERT_H

typedef struct PropertyS Property;
struct PropertyS
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
};

extern Property property[];

extern int  propMakeVector(char *str, Property ** vec, int max);
extern char *propSortByWeight(char *list);
extern char *propSortByMelt(char *list);
extern char *propSortByBoil(char *list);
extern char *propSortByAbundance(char *list);
extern char *propSortReverse(char *list);
extern char *propFindGasAtTemp(char *out, double temp);
extern char *propFindLiquidAtTemp(char *out, double temp);
extern char *propFindSolidAtTemp(char *out, double temp);

#endif
