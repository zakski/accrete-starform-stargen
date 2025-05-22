#ifndef SOLID_RADIUS_HELPERS_H
#define SOLID_RADIUS_HELPERS_H
#include <map>
#include "structs.h"

long double water_radius(long double, planet *, map<long double, long double> &);
long double one_quater_rock_three_fourths_water_radius(long double, long double, planet *, map<long double, long double> &);
long double half_rock_half_water_radius(long double, long double, planet *, map<long double, long double> &);
long double rock_radius(long double, long double, planet *, map<long double, long double> &);
long double half_rock_half_iron_radius(long double, long double, planet *, map<long double, long double> &);
long double iron_radius(long double, planet *, map<long double, long double> &);
long double solid_0point953_iron_0point047_water_radius(long double, planet *, map<long double, long double> &);
long double solid_0point51_iron_0point49_water_radius(long double, planet *, map<long double, long double> &);
long double solid_0point264_iron_0point736_water_radius(long double, planet *, map<long double, long double> &);
long double fraction_radius(long double, long double, long double, long double);

#endif
