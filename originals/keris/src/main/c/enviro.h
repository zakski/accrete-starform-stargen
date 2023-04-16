#ifndef __ENVIRO_H
#define __ENVIRO_H

#include "gensys.h"

double luminosity(double mass_ratio);
int    orbital_zone(stellar_system* system, double orb_radius);
double volume_radius(double mass, double density);
double kothari_radius(double mass, bool is_gas_giant, int zone);
double empirical_density(stellar_system* system, double mass, 
        double orb_radius, bool is_gas_giant);
double volume_density(double mass, double equatorial_radius);
double period(double separation, double small_mass, double large_mass);
double day_length(stellar_system* system, double mass, double radius, 
        double eccentricity, double density, double orb_radius, 
        double orb_period, bool is_gas_giant, double mass_ratio);
int    inclination(double orb_radius);
double escape_velocity(double mass, double radius);
double rms_velocity(stellar_system* system, double molecular_weight, double orb_radius);
double molecule_limit(double mass, double equatorial_radius);
double acceleration(double mass, double radius);
double gravity(double acceleration);
int    greenhouse(int zone, double orb_radius, double r_greenhouse);
double vol_inventory(double mass, double escape_velocity, double rms_velocity, 
        double stellar_mass, int zone, int greenhouse_effect);
double pressure(double volatile_gas_inventory, double equatorial_radius, 
        double gravity);
double boiling_point(double surf_pressure);
void   iterate_surface_temp(stellar_system* system, planet** planet);
void   iterate_surface_temp_moon(stellar_system* system, 
        planet** primary, planet** planet);

#endif
