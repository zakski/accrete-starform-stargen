#ifndef ENVIRO_H
#define ENVIRO_H

//include "const.h"
#include "structs.h"
#include "utils.h"

extern string breathability_phrase[4];
extern map<map<long double, long double>, vector<long double> > polynomial_cache;

long double mass_to_luminosity(long double);
long double luminosity_to_mass(long double);
string getStarType(string);
int getSubType(string);
long double spec_type_to_eff_temp(string);
string eff_temp_to_spec_type(long double, long double);
int orb_zone(long double, long double);
long double volume_radius(long double, long double);
long double empirical_density(long double, long double, long double, bool);
long double volume_density(long double, long double);
long double period(long double, long double, long double);
long double day_length(planet *, long double, bool);
long double inclination(long double, long double);
long double escape_vel(long double, long double);
long double rms_vel(long double, long double);
long double molecule_limit(long double, long double, long double);
long double min_molec_weight(planet *);
long double acceleration(long double, long double);
long double gravity(long double);
long double vol_inventory(long double, long double, long double, long double, int, bool, bool);
long double pressure(long double, long double, long double);
long double boiling_point(long double);
long double hydro_fraction(long double, long double);
long double cloud_fraction(long double, long double, long double, long double);
long double ice_fraction(long double, long double);
long double eff_temp(long double, long double, long double);
long double est_temp(long double, long double, long double);
bool grnhouse(long double, long double);
long double green_rise(long double, long double, long double);
long double planet_albedo(planet *);
long double opacity(long double, long double);
long double gas_life(long double, planet *);
void calculate_surface_temp(planet *, bool, long double, long double, long double, long double, long double, bool);
void iterate_surface_temp(planet *, bool);
long double inspired_partial_pressure(long double, long double);
unsigned int breathability(planet *);
void set_temp_range(planet *);
long double getSpinResonanceFactor(long double);
long double radius_improved(long double, long double, long double, long double, bool, int, planet *);
long double fudged_radius(long double, long double, long double, long double, bool, int, planet *);
long double gas_radius(long double, long double, long double, long double, planet *);
long double round_threshold(long double);
long double ultimateStrength(long double);
long double habitable_zone_distance(sun&, int, long double);
long double calcLambda(long double, long double);
void gas_giant_temperature_albedo(planet *, long double, bool);
long double getGasGiantAlbedo(string, string, long double);
void calculate_gases(sun&, planet *, string);
void assign_composition(planet *, sun &, bool);
bool is_gas_planet(planet *);
bool is_earth_like(planet *);
bool is_habitable_jovian_conservative(planet *);
bool is_habitable_jovian(planet *);
bool is_terrestrial(planet *);
long double calcOblateness(planet *);
long double calcPhlPressure(planet *);
bool is_habitable_conservative(planet *);
bool is_habitable_optimistic(planet *);
long double calcHzd(planet *);
long double calcHzc(planet *);
long double calcHza(planet *);
long double calcEsi(planet *);
long double calcSph(planet *);
long double calcEsiHelper(long double value, long double ref_value, long double weight, long double n = 4);
bool is_potentialy_habitable_conservative(planet *);
bool is_potentialy_habitable_optimistic(planet *);
long double calcRelHumidity(planet *);
long double getPlantLifeAlbedo(string, long double);
long double calcFlux(long double, long double);
long double calculate_moment_of_inertia_coeffient(planet *);
long double calculate_moment_of_inertia(planet *);
long double calcOblateness_improved(long double, long double, long double, long double);
long double calcLuminosity(planet *);
long double calcRadius(planet *);
long double planet_radius_helper(long double planet_mass, long double mass1, long double radius1, long double mass2, long double radius2, long double mass3, long double radius3, bool use_cache = true);
long double planet_radius_helper2(long double, long double, long double, long double, long double);
long double planet_radius_helper3(long double, long double, long double, long double, long double);
long double convert_su_to_eu(long double);
long double convert_au_to_km(long double);
bool is_potentialy_habitable_extended(planet *);
bool is_habitable_extended(planet *);
bool is_potentialy_habitable_earth_like(planet *);
bool is_habitable_earth_like(planet *);
bool is_potentialy_habitable(planet *);
bool is_habitable(planet *);
long double convert_km_to_eu(long double);
void makeHabitable(sun&, planet *, string, bool, bool);

template <typename Key, typename T>
void radiusDebug(const string& text, planet *the_planet, long double calculated_radii, map<Key, T>& radii);

template <typename Key, typename T>
void radiusDebug(const string& text, planet* the_planet, long double calculated_radii, map<Key, T>& radii)
{
  cerr << "Age: " << toString(the_planet->getTheSun().getAge()) << endl;
  if (the_planet->getMoonA() == 0.0)
  {
    cerr << "Planet's distance: " << toString(the_planet->getA()) << " AU" << endl;
  }
  else
  {
    cerr << "Moon's parent's distance: " << toString(the_planet->getA()) << " AU" << endl;
    cerr << "Moon's distance: " << toString(convert_au_to_km(the_planet->getMoonA())) << " km" << endl;
  }
  cerr << "Core composition: " << toString(the_planet->getImf() * 100.0, 4) << "% ice, " << toString(the_planet->getRmf() * 100.0, 4) << "% rock (" << toString(the_planet->getCmf() * 100.0, 4) << "% carbon)" << endl;
  cerr << "Mass: " << toString(convert_su_to_eu(the_planet->getMass())) << " EU" << endl;
  if (the_planet->getGasGiant())
  {
    cerr << "Dust mass: " << toString(convert_su_to_eu(the_planet->getDustMass())) << " EU" << endl;
    cerr << "Temperature: " << toString(the_planet->getEstimatedTemp()) << " K" << endl;
  }
  cerr << "Calculated radius: " << toString(calculated_radii) << endl;
  cerr << text << endl;
  writeMap(radii);
}
#endif
