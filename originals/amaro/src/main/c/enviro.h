long double luminosity(long double);
int orb_zone(long double, long double);
long double volume_radius(long double, long double);
long double kothari_radius(long double, int, int);
long double empirical_density(long double, long double, long double, int);
long double volume_density(long double, long double);
long double period(long double, long double, long double);
long double day_length(planet_pointer);
int inclination(long double);
long double escape_vel(long double, long double);
long double rms_vel(long double, long double);
long double molecule_limit(long double, long double, long double);
long double min_molec_weight (planet_pointer);
long double acceleration(long double, long double);
long double gravity(long double);
long double vol_inventory(long double, long double, long double, long double, int, int, int);
long double pressure(long double, long double, long double);
long double boiling_point(long double);
long double hydro_fraction(long double, long double);
long double cloud_fraction(long double, long double, long double, long double);
long double ice_fraction(long double, long double);
long double eff_temp(long double, long double, long double);
long double est_temp(long double, long double, long double);
int grnhouse(long double r_ecosphere, long double);
long double green_rise(long double, long double, long double);
long double planet_albedo(long double, long double, long double, long double);
long double opacity(long double, long double);
long double gas_life(long double, planet_pointer);
void calculate_surface_temp(planet_pointer, int, long double, long double,
							long double, long double, long double);
void iterate_surface_temp(planet_pointer);

long double inspired_partial_pressure (long double, long double);

unsigned int breathability (planet_pointer);

#define	NONE			0
#define	BREATHABLE		1
#define	UNBREATHABLE	2
#define	POISONOUS		3

extern char* breathability_phrase[4];

extern long double lim(long double x);
long double soft(long double v, long double max, long double min);
extern void set_temp_range(planet_pointer planet);
