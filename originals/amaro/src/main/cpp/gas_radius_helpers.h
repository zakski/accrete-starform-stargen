#ifndef GAS_RADIUS_HELPERS_H
#define GAS_RADIUS_HELPERS_H
#include "structs.h"

long double gas_radius_300Myr(long double, long double, long double, planet *);
long double gas_radius_1Gyr(long double, long double, long double, planet *);
long double gas_radius_4point5Gyr(long double, long double, long double, planet *);
long double mini_neptune_radius(planet *);
long double gas_dwarf_radius(planet *);

#endif
