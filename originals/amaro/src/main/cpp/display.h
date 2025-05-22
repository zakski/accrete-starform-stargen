#ifndef DISPLAY_H
#define DISPLAY_H
#include <fstream>
#include <sstream>
#include <string>
#include "structs.h"

using namespace std;

void text_describe_system(planet *, bool, long, bool);
void csv_describe_system(fstream&, planet *, bool, long, bool);
void csv_row(fstream&, planet *, bool, bool, string, stringstream&);
string type_string(planet *);
string cloud_type_string(planet *);
void create_svg_file(planet *, string, string, string, string, bool);
void open_csv_file(string, string, fstream&);
void refresh_file_stream(fstream&, string, string, string);
void open_html_file(string, long, string, string, string, string, string, fstream&);
void close_html_file(fstream&);
void print_description(fstream&, string, planet *, string);
void list_molecules(fstream&, long double);
void html_thumbnails(planet *, fstream&, string, string, string, string, string, bool, bool, bool, bool, int, bool);
void html_thumbnail_totals(fstream&);
void html_decribe_planet(planet *, int, int, bool, string, fstream&);
void html_describe_system(planet *, bool, bool, string, fstream&);
void celestia_describe_system(planet *, string, string, long, long double, long double, bool);
void celestia_describe_world(planet *, string, string, long, long double, long double, int, sun&, bool, int);
void moongen_describe_system(planet *, string, string, long);
void lprint(fstream&, bool&, string);
string image_type_string(planet *);
string printSpinResonanceFactor(long double);
void mol_print(fstream&, bool&, int&, int, long double, string, long double);
string texture_name(planet_type);
void display_clouds(planet *);
void assignDistanceColors(planet *, long double, long double, long double);
void assignTemperatureColors(planet *, long double, long double, long double, long double, long double, long double, long double, long double);
#endif
