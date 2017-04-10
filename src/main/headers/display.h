extern char *engineer_notation(double d, int p);
extern void chart_system(planet_pointer first_planet);
extern double local_bp(double bp_at_stp, double surf_pressure);
extern void text_list_stuff(double temp, double min_weight, double pressure, double orbital_radius, double escape_vel, double star_age);
extern void text_describe_planet(char *start, planet_pointer node1, int counter);
extern void text_describe_system(planet_pointer first_planet);
extern void lisp_describe_planet(char *opar, char *bstr, planet_pointer node1, int counter);
extern void lisp_describe_system(planet_pointer first_planet);
extern void display_system(planet_pointer first_planet);
