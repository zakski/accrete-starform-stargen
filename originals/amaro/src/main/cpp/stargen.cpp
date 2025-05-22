#include "stargen.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "accrete.h"
#include "const.h"
#include "display.h"
#include "elements.h"
#include "enviro.h"
#include "planets.h"
#include "utils.h"

using namespace std;

int flags_arg_clone = 0;

sun the_sun_clone;

int flag_verbose = 0;
/*  These are the global variables used during accretion:  */
planet *innermost_planet;
long double dust_density_coeff = DUST_DENSITY_COEFF;

long flag_seed = 0;

long double min_age = 0;
long double max_age = 10.0E9;
long double max_age_backup = 10.0E9;

bool is_circumbinary = false;
long double compainion_mass_arg = 0;
long double compainion_eccentricity_arg = 0;
long double compainion_distant_arg = 0;
long double compainion_lum_arg = 0;
long double compainion_eff_arg = 0;
string companion_spec_arg = "";
int decimals_arg = 0;

long double temp_arg = 0;
string type_arg = "";

long double max_distance_arg = 0;

int earthlike = 0;
int total_earthlike = 0;
int habitable = 0;
int habitable_jovians = 0;
int habitable_superterrans =0;
int total_habitable = 0;
int potential_habitable = 0;
int total_worlds = 0;
int total_habitable_earthlike = 0;
int total_habitable_conservative = 0;
int total_habitable_optimistic = 0;
int total_potentially_habitable = 0;
int total_potentially_habitable_earthlike = 0;
int total_potentially_habitable_conservative = 0;
int total_potentially_habitable_optimistic = 0;

long double min_breathable_terrestrial_g = 1000.0;
long double min_breathable_g = 1000.0;
long double max_breathable_terrestrial_g = 0.0;
long double max_breathable_g = 0.0;
long double min_breathable_temp = 1000.0;
long double max_breathable_temp = 0.0;
long double min_breathable_p = 100000.0;
long double max_breathable_p = 0.0;
long double min_breathable_terrestrial_l = 1000.0;
long double min_breathable_l = 1000.0;
long double max_breathable_terrestrial_l = 0.0;
long double max_breathable_l = 0.0;
long double max_moon_mass = 0.0;
long double min_breathable_mass = 0;
long double max_breathable_mass = 0;

long double min_potential_terrestrial_g = 1000.0;
long double min_potential_g = 1000.0;
long double max_potential_terrestrial_g = 0.0;
long double max_potential_g = 0.0;
long double min_potential_temp = 1000.0;
long double max_potential_temp = 0.0;
long double min_potential_p = 100000.0;
long double max_potential_p = 0.0;
long double min_potential_terrestrial_l = 1000.0;
long double min_potential_l = 1000.0;
long double max_potential_terrestrial_l = 0.0;
long double max_potential_l = 0.0;
long double min_potential_mass = 0;
long double max_potential_mass = 0;

int type_counts[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //seb
int type_count = 0;
int max_type_count = 0;

bool allow_planet_migration = false;

long system_seed = 0;

string stargen_revision = "$Revision: 2.0 $";

int stargen(actions action, string flag_char, string path, string url_path_arg, string filename_arg, string sys_name_arg, string prognam, long double mass_arg, long double luminosity_arg, long seed_arg, int count_arg, int incr_arg, catalog &cat_arg, int sys_no_arg, long double ratio_arg, long double ecc_coef_arg, long double inner_planet_factor_arg, int flags_arg, int out_format, int graphic_format)
{
  sun the_sun;
  long double min_mass = 0.4;
  long double inc_mass = 0.05;
  long double max_mass = 2.35;
  long double sys_inc = 0.0; //seb
  long double sys_an  = 0.0; //seb
  int system_count = 1;
  int seed_increment = 1;
  string default_path = SUBDIR;			/* OS specific */
  string default_url_path = "../";
  string url_path = default_url_path;
  string thumbnail_file = "Thumbnails";
  string file_name = "StarGen";
  string subdir = "";
  string csv_file_name = "StarGen.csv";
  fstream html_file;
  fstream thumbnails; 
  fstream csv_file;
  int index = 0;
  bool do_catalog = cat_arg.count() > 0 && sys_no_arg == 0;
  int catalog_count = 0;
  bool do_gases = (flags_arg & fDoGases) != 0;
  bool use_solar_system = (flags_arg & fUseSolarsystem) != 0;
  bool reuse_solar_system = (flags_arg & fReuseSolarsystem) != 0;
  bool use_known_planets = (flags_arg & fUseKnownPlanets) != 0;
  bool no_generate = (flags_arg & fNoGenerate) != 0;
  bool do_moons = (flags_arg & fDoMoons) != 0;
  bool only_habitable = (flags_arg & fOnlyHabitable) != 0;
  bool only_multi_habitable= (flags_arg & fOnlyMultiHabitable) != 0;
  bool only_three_habitable= (flags_arg & fOnlyThreeHabitable) != 0;
  bool only_jovian_habitable=(flags_arg & fOnlyJovianHabitable) != 0;
  bool only_earthlike = (flags_arg & fOnlyEarthlike) != 0;
  bool only_superterrans = (flags_arg & fOnlySuperTerans) != 0;
  bool only_potential_habitable = (flags_arg & fOnlyPotentialHabitable) != 0;
  allow_planet_migration = (flags_arg & fDoMigration) != 0;
  is_circumbinary = (flags_arg & fIsCircubinaryStar) != 0;
  stringstream ss;
  
  if (do_catalog)
  {
    catalog_count = cat_arg.count();
  }
  
  if (only_habitable && only_multi_habitable)
  {
    only_habitable = false;
  }
  
  if (only_habitable && only_earthlike)
  {
    only_habitable = false;
  }
  
  if (only_three_habitable)
  {
    only_habitable = false;
    only_earthlike = false;
    only_multi_habitable = false;
  }
  
  if (only_superterrans)
  {
    only_habitable = false;
    only_earthlike = false;
    only_multi_habitable = false;
    only_three_habitable = false;
  }
  
  if (prognam.empty())
  {
    prognam = "StarGen";
  }
  
  //cout << path << endl;
  if (path.empty())
  {
    path = default_path;
  }
  //cout << path << endl;
  
  if (graphic_format == 0)
  {
    graphic_format = gfGIF;
  }
  
  if (!url_path_arg.empty())
  {
    url_path = url_path_arg;
  }
  
  // Find the last sub-dir in the path
  ss << path.substr(path.find_last_of(DIRSEP) + 1) << DIRSEP;
  subdir = ss.str();
  ss.str("");
  //cout << subdir << endl;
  
  if (path.find_last_of(DIRSEP) != path.size())
  {
    path.append(DIRSEP);
  }
  //cout << path << endl;

  switch (action)
  {
    case aListGases:
    {
      long double total = 0.0;
      int count = gases.count();
      for (int i = 0; i < count; i++)
      {
	if (gases[i].getWeight() >= AN_N && gases[i].getMaxIpp() < INCREDIBLY_LARGE_NUMBER)
	{
	  total += gases[i].getMaxIpp();
	}
	//cout << " " << gases[i].getNum() << ": " << gases[i].getSymbol() << " - " << gases[i].getName() << " " << toString(gases[i].getMinIpp()) << " mb - " << toString(gases[i].getMaxIpp()) << " mb" << endl;
      }
      cout << gases;
      cout << "Total Max ipp: " << toString(total) << endl;
      cout << "Max pressure: " << toString(MAX_HABITABLE_PRESSURE) << " atm" << endl;
      return EXIT_SUCCESS;
    }
    case aListCatalog:
    {
      cout << cat_arg;
      return EXIT_SUCCESS;
    }
    case aListCatalogAsHTML:
    {
      int count = cat_arg.count();
      for (int i = 0; i < count; i++)
      {
	cout << "\t<option value=" << i << ">" << cat_arg[i].getName() << "</option>" << endl;
      }
      return EXIT_SUCCESS;
    }
    case aSizeCheck:
    {
      long double tempE = est_temp(1.0,  1.0,  EARTH_ALBEDO);
      long double tempJ = est_temp(1.0,  5.2034,  GAS_GIANT_ALBEDO);
      long double tempS = est_temp(1.0,  9.5371,  GAS_GIANT_ALBEDO);
      long double tempU = est_temp(1.0, 19.1913,  GAS_GIANT_ALBEDO);
      long double tempN = est_temp(1.0, 30.0690,  GAS_GIANT_ALBEDO);
      
      cout << "Size of float: " << sizeof(float) << endl;
      cout << "Size of doubles: " << sizeof(double) << endl;
      cout << "Size of long doubles: " << sizeof(long double) << endl;
      cout << "Earth Eff Temp: " << toString(tempE) << " K, " << toString(tempE - FREEZING_POINT_OF_WATER) << " C, Earth rel: " << toString(tempE - EARTH_AVERAGE_KELVIN) << " C" << endl;
      cout << "Jupiter Eff Temp: " << toString(tempJ) << " K" << endl;
      cout << "Saturn Eff Temp: " << toString(tempS) << " K" << endl;
      cout << "Uranus Eff Temp: " << toString(tempU) << " K" << endl;
      cout << "Neptune Eff Temp: " << toString(tempN) << " K" << endl;
      return EXIT_SUCCESS;
    }
    case aListVerbosity:
    {
      cout << "Stargen " << stargen_revision << endl;
      cout << "Verbosity flags are hexidecimal numbers:" << endl;
      cout << "\t0001\tEarthlike count" << endl;
      cout << "\t0002\tTrace Min/Max" << endl;
      cout << "\t0004\tList Habitable" << endl;
      cout << "\t0008\tList Earthlike & Sphinxlike" << endl;
      cout << endl;
      cout << "\t0010\tList Gases" << endl;
      cout << "\t0020\tTrace temp iterations" << endl;
      cout << "\t0040\tGas lifetimes" << endl;
      cout << "\t0080\tList loss of accreted gas mass" << endl;
      cout << endl;
      cout << "\t0100\tInjecting, collision" << endl;
      cout << "\t0200\tChecking..., Failed..." << endl;
      cout << "\t0400\tList binary info" << endl;
      cout << "\t0800\tList accreted atmospheres" << endl;
      cout << endl;
      cout << "\t1000\tMoons (experimental)" << endl;
      cout << "\t2000\tOxygen poisoned (experimental)" << endl;
      cout << "\t4000\tTrace gas percentages" << endl;
      cout << "\t8000\tList Jovians in the ecosphere" << endl;
      cout << endl;
      cout << "\t10000\tList type diversity" << endl;
      cout << "\t20000\tTrace Surface temp interations" << endl;
      cout << "\t40000\tDisplay Roche Limits and Hill Sphere distances" << endl;
      cout << "\t80000\tDisplay mass-radius maps" << endl;
      return EXIT_SUCCESS;
    }
    case aGenerate:
      break;
  }
  
  flag_seed = seed_arg;
  the_sun.setMass(mass_arg);
  the_sun.setLuminosity(luminosity_arg);
  if (the_sun.getMass() == 0 && the_sun.getLuminosity() != 0)
  {
    the_sun.setMass(luminosity_to_mass(the_sun.getLuminosity())); 
  }
  the_sun.setEffTemp(temp_arg);
  the_sun.setSpecType(type_arg);
  
  system_count = count_arg;
  seed_increment = incr_arg;
  
  if (ratio_arg > 0.0)
  {
    dust_density_coeff *= ratio_arg;
  }
  
  if (reuse_solar_system)
  {
    system_count = 1 + (int) ((max_mass - min_mass) / inc_mass);
    
    the_sun.setLuminosity(1.0);
    the_sun.setMass(1.0);
    the_sun.setAge(5E9);
    
    use_solar_system = true;
  }
  else if (do_catalog)
  {
    system_count = catalog_count + ((system_count - 1) * (catalog_count - 1));
    use_solar_system = true;
  }
  
  if (system_count > 1 && out_format != ffCSVdl)
  {
    if (filename_arg.size() > 0)
    {
      thumbnail_file = filename_arg;
    }
    
    open_html_file("Thumbnails", flag_seed, path, url_path, thumbnail_file, ".html", prognam, thumbnails);
  }
  
  if (out_format == ffCSV || out_format == ffCSVdl)
  {
    string csv_url;
    string cleaned_arg = "StarGen";
    
    if (filename_arg.size() > 0)
    {
      char *ptr;
      
      cleaned_arg = filename_arg;
    }
    ss.str("");
    ss << cleaned_arg << ".csv";
    csv_file_name = ss.str();
    
    open_csv_file(path, csv_file_name, csv_file);
  }
  
  for (index = 0; index < system_count; index++)
  {
    //cout << "test " << index << endl;
    cout << "";
    string system_name;
    string designation;
    string cp;
    long double outer_limit;
    long double inner_dust_limit;
    int sys_no;
    bool has_known_planets = false;
    planet *seed_planets = NULL;
    bool use_seed_system;
    bool in_celestia;
    
    init();
    
    outer_limit = 0;
    
    if (do_catalog || sys_no_arg)
    {
      if (sys_no_arg)
      {
	//sys_no = sys_no_arg - 1;
	sys_no = sys_no_arg;
      }
      else
      {
	if (index >= catalog_count)
	{
	  sys_no = ((index - 1) % (catalog_count - 1)) + 1;
	}
	else
	{
	  sys_no = index;
	}
      }
      //sys_no += 1;

      sys_inc = cat_arg[sys_no].getInc();
      sys_an = cat_arg[sys_no].getAn();
      
      if (cat_arg[sys_no].getKnownPlanets() != NULL)
      {
	has_known_planets = true;
      }
      else
      {
	has_known_planets = false;
      }
      
      if ((use_known_planets || no_generate) && has_known_planets)
      {
	seed_planets = cat_arg[sys_no].getKnownPlanets();
	use_seed_system = no_generate;
      }
      else
      {
	seed_planets = NULL;
	use_seed_system = false;
      }
    
      in_celestia = cat_arg[sys_no].getInCelestia();
      
      //cout << cat_arg[sys_no].getMass() << " " << cat_arg[sys_no].getLuminosity() << " " << cat_arg[sys_no].getEffTemp() << " " << cat_arg[sys_no].getSpecType() << endl;

      the_sun.setMass(cat_arg[sys_no].getMass());
      the_sun.setLuminosity(cat_arg[sys_no].getLuminosity());
      the_sun.setEffTemp(cat_arg[sys_no].getEffTemp());
      the_sun.setSpecType(cat_arg[sys_no].getSpecType());
      if (cat_arg[sys_no].getIsCircumbinary())
      {
	the_sun.setIsCircumbinary(true);
	the_sun.setSecondaryMass(cat_arg[sys_no].getMass2());
	the_sun.setSecondaryLuminosity(cat_arg[sys_no].getLuminosity2());
	the_sun.setSecondaryEffTemp(cat_arg[sys_no].getEffTemp2());
	the_sun.setSecondarySpecType(cat_arg[sys_no].getSpecType2());
	the_sun.setSeperation(cat_arg[sys_no].getDistance());
	the_sun.setEccentricity(cat_arg[sys_no].getEccentricity());
      }
      else
      {
	the_sun.setIsCircumbinary(false);
      }
      
      if (do_catalog || sys_name_arg.empty())
      {
	system_name = cat_arg[sys_no].getName();
	designation = cat_arg[sys_no].getDesig();
      }
      else
      {
	system_name = sys_name_arg;
	designation = sys_name_arg;
      }
      
      ss.str("");
      ss << designation << "-" << flag_seed;
      file_name = ss.str();
      
      if (cat_arg[sys_no].getMass2() == 0)
      {
	inner_dust_limit = cat_arg[sys_no].getDistance();
      }
      else
      {
	inner_dust_limit = 0;
      }

      if (cat_arg[sys_no].getMass2() > .001 && !cat_arg[sys_no].getIsCircumbinary())
      {
	long double m1 = the_sun.getMass();
	long double m2 = cat_arg[sys_no].getMass2();
	long double mu = m2 / (m1 + m2);
	long double e = cat_arg[sys_no].getEccentricity();
	long double a = cat_arg[sys_no].getDistance();
	
	outer_limit = (0.464 + (-0.380 * mu) + (-0.631 * e) + (0.586 * mu * e) + (0.150 * pow2(e)) + (-0.198 * mu * pow2(e))) * a;
      }
      else
      {
	outer_limit = 0;
      }
    }
    else if (reuse_solar_system)
    {
      /*system_name = "Earth-";
      system_name.append(float_to_string(earth->getMass() * SUN_MASS_IN_EARTH_MASSES));*/
      ss.str("");
      ss << "Earth-" << (earth->getMass() * SUN_MASS_IN_EARTH_MASSES);
      system_name = ss.str();
      file_name = designation = system_name;
      
      outer_limit = 0;
    }
    else
    {
      stringstream ss;
      if (!sys_name_arg.empty())
      {
	system_name = sys_name_arg;
	designation = sys_name_arg;
      }
      else
      {
	ss.str("");
	ss << prognam << " " << flag_seed << "-" << the_sun.getMass();
	system_name = ss.str();
	designation = prognam;
      }
      ss.str("");
      ss << designation << "-" << flag_seed << "-" << the_sun.getMass();
      file_name = ss.str();
    }
    
    if (compainion_mass_arg > .001)
    {
      long double m1 = the_sun.getMass();
      long double m2 = compainion_mass_arg;
      long double mu = m2 / (m1 + m2);
      long double e = compainion_eccentricity_arg;
      long double a = compainion_distant_arg;
      
      if (is_circumbinary)
      {
	the_sun.setIsCircumbinary(true);
	the_sun.setSecondaryMass(m2);
	the_sun.setSecondaryLuminosity(compainion_lum_arg);
	the_sun.setSecondaryEffTemp(compainion_eff_arg);
	the_sun.setSecondarySpecType(companion_spec_arg);
	the_sun.setEccentricity(e);
	the_sun.setSeperation(a);
	outer_limit = 0;
      }
      else
      {
	outer_limit = (0.464 + (-0.380 * mu) + (-0.631 * e) + (0.586 * mu * e) + (0.150 * pow2(e)) + (-0.198 * mu * pow2(e))) * a;
      }
    }
    
    the_sun.setName(system_name);
    
    if (flag_verbose & 0x0400 && outer_limit > 0.0)
    {
      cerr << system_name << ", Outer Limit: " << toString(outer_limit) << endl;
    }
    if (system_count == 1 && filename_arg.size() > 0)
    {
      file_name = filename_arg;
    }

    file_name = replaceStrChar(file_name, ' ', '-');
    file_name = replaceStrChar(file_name, '\'', '-');

    earthlike = habitable = habitable_jovians = habitable_superterrans = potential_habitable = 0;
    
    if (reuse_solar_system)
    {
      seed_planets = mercury;
      use_seed_system = true;
    }
    else if (use_solar_system)
    {
      if  (index == 0)
      {
	seed_planets = mercury;
	use_seed_system = true;
      }
      else
      {
	use_seed_system = false;
	if (!use_known_planets)
	{
	  seed_planets = NULL;
	}
	if (has_known_planets && use_known_planets && no_generate)
	{
	  use_seed_system = true;
	}
      }
    }
    
    for (int i = 0; i < 16; i++)
    {
      type_counts[i] = 0;
    }
    type_count = 0;
    //cout << index << endl;
    the_sun_clone = the_sun;
    generate_stellar_system(the_sun, use_seed_system, seed_planets, flag_char, sys_no, system_name, inner_dust_limit, outer_limit, ecc_coef_arg, inner_planet_factor_arg, do_gases, do_moons);
    
    planet *a_planet;
    int counter;
    int wt_type_count = type_count;
    int norm_type_count = 0;
    
    if (type_counts[0] > 0)
    {
      wt_type_count += 1; // Unknown
    }
    if (type_counts[1] > 0)
    {
      wt_type_count += 3; // Rock
    }
    if (type_counts[2] > 0)
    {
      wt_type_count += 16; // Venusian
    }
    if (type_counts[3] > 0)
    {
      wt_type_count += 20; // Terrestrial
    }
    if (type_counts[4] > 0)
    {
      wt_type_count += 12; // Gas Dwarf
    }
    if (type_counts[5] > 0)
    {
      wt_type_count += 11; // Neptunian
    }
    if (type_counts[6] > 0)
    {
      wt_type_count += 2; // Jovian
    }
    if (type_counts[7] > 0)
    {
      wt_type_count += 15; // Martian
    }
    if (type_counts[8] > 0)
    {
      wt_type_count += 18; // Water
    }
    if (type_counts[9] > 0)
    {
      wt_type_count += 14; // Ice
    }
    if (type_counts[10] > 0)
    {
      wt_type_count += 13; // Asteroids
    }
    if (type_counts[11] > 0)
    {
      wt_type_count += 10; // 1-Face
    }
    
    for (a_planet = innermost_planet, counter = 0; a_planet != NULL; a_planet = a_planet->next_planet, counter++);
    
    norm_type_count = wt_type_count - (counter - type_count);
    
    if (max_type_count < norm_type_count)
    {
      max_type_count = norm_type_count;
    }
    
    if (flag_verbose & 0x10000)
    {
      cerr << "System " << flag_seed << " - " << system_name << " (-s" << flag_seed << " -" << flag_char << sys_no << ") has " << type_count << " types out of " << counter << " planets. [" << norm_type_count << "]" << endl;
    }
    
    total_habitable += habitable;
    total_potentially_habitable += potential_habitable;
    total_earthlike += earthlike;
    if ((!(only_habitable || only_multi_habitable || only_jovian_habitable || only_earthlike || only_three_habitable || only_superterrans || only_potential_habitable)) || (only_habitable && (habitable > 0) && !only_jovian_habitable) || (only_habitable && only_jovian_habitable && habitable > 0 && habitable_jovians > 0) || (only_multi_habitable && (habitable > 1) && !only_jovian_habitable) || (only_multi_habitable && only_jovian_habitable && habitable > 1 && habitable_jovians > 0) || (only_earthlike && (earthlike > 0) && !only_jovian_habitable) || (only_earthlike && only_jovian_habitable && earthlike > 0 && habitable_jovians > 0) || (only_jovian_habitable && (habitable_jovians > 0) && !(only_earthlike || only_multi_habitable || only_habitable || only_three_habitable)) || (only_three_habitable && only_jovian_habitable && habitable > 2 && habitable_jovians > 0) || (only_three_habitable && (habitable > 2)) || (only_superterrans && habitable_superterrans > 0) || (only_potential_habitable && potential_habitable > 0))
    {
      string system_url, svg_url;
      
      ss.str("");
      ss << url_path << subdir << file_name << ".html";
      system_url = ss.str();
      
      ss.str("");
      ss << url_path << subdir << file_name << ".svg";
      svg_url = ss.str();
      switch (out_format)
      {
	case ffSVG:
	  create_svg_file(innermost_planet, path, file_name, ".svg", prognam, do_moons);
	  break;
	case ffHTML:
	  //refresh_file_stream(thumbnails, path, thumbnail_file, ".html");
	  
	  if (graphic_format == gfSVG)
	  {
	    create_svg_file(innermost_planet, path, file_name, ".svg", prognam, do_moons);
	  }
	  html_thumbnails(innermost_planet, thumbnails, system_name, url_path, system_url, svg_url, file_name, false, true, false, do_moons, graphic_format, do_gases);
	  open_html_file(system_name, flag_seed, path, url_path, file_name, ".html", prognam, html_file);
	  html_thumbnails(innermost_planet, html_file, system_name, url_path, system_url, svg_url, file_name, true, false, true, do_moons, graphic_format, do_gases);
	  html_describe_system(innermost_planet, do_gases, do_moons, url_path, html_file);
	  close_html_file(html_file);
	  break;
	case ffTEXT:
	  text_describe_system(innermost_planet, do_gases, flag_seed, do_moons);
	  break;
	case ffCSV:
	case ffCSVdl:
	  csv_describe_system(csv_file, innermost_planet, do_gases, flag_seed, do_moons);
	  break;
	case ffCELESTIA:
	  celestia_describe_system(innermost_planet, designation, system_name, flag_seed, sys_inc, sys_an, do_moons);
	  break;
	/*case ffMOONGEN:
	  moongen_describe_system(innermost_planet, designation, system_name, flag_seed);
	  break;*/
      }
      if (habitable > 1 && flag_verbose & 0x0001)
      {
	cerr << "System " << flag_seed << " - " << system_name << " (-s" << flag_seed << " -" << flag_char << sys_no << ") has " << habitable << " planets with breathable atmospheres." << endl;
      }
    }
    
    if (!(use_solar_system && index == 0))
    {
      flag_seed += seed_increment;
    }
    
    if (reuse_solar_system)
    {
      earth->setDustMass(earth->getDustMass() + EM(inc_mass));
    }
    
    if (!use_seed_system)
    {
      free_generations();
    }
    else
    {
      planet *ptr = NULL;
      planet *node = NULL;
      planet *next = NULL;
      for (ptr = innermost_planet; ptr != NULL; ptr = ptr->next_planet)
      {
	ptr->setImf(0);
	ptr->setRmf(0);
	ptr->setCmf(0);
	if (do_moons)
	{
	  for (node = ptr->first_moon; node != NULL; node = next)
	  {
	    next = node->next_planet;
	    if (node->getDeletable())
	    {
	      delete node;
	    }
	    else
	    {
	      node->setMoonA(0);
	      node->setMoonE(0);
	      node->setImf(0);
	      node->setRmf(0);
	      node->setCmf(0);
	      node->next_planet = node->reconnect_to;
	    }
	    //cout << "Deleted World" << endl;
	  }
	  ptr->first_moon = ptr->first_moon_backup;
	}
      }
    }
  }
  
  if (flag_verbose & 0x0001 || flag_verbose & 0x0002)
  {
    cerr << "Earthlike planets: " << total_earthlike << endl;
    cerr << "Breathable atmospheres: " << total_habitable << endl;
    cerr << "Breathable g range: " << toString(min_breathable_g) << " - " << toString(max_breathable_g) << endl;
    cerr << "Terrestrial g range: " << toString(min_breathable_terrestrial_g) << " - " << toString(max_breathable_terrestrial_g) << endl;
    cerr << "Breathable pressure range: " << toString(min_breathable_p) << " - " << toString(max_breathable_p) << endl;
    cerr << "Breathable temp range: " << toString(min_breathable_temp - EARTH_AVERAGE_KELVIN) << " C - " << toString(max_breathable_temp - EARTH_AVERAGE_KELVIN) << " C" << endl;
    cerr << "Breathable illumination range: " << toString(min_breathable_l) << " - " << toString(max_breathable_l) << endl;
    cerr << "Terrestrial illumination range: " << toString(min_breathable_terrestrial_l) << " - " << toString(max_breathable_terrestrial_l) << endl;
    cerr << "Max moon mass: " << toString(max_moon_mass * SUN_MASS_IN_EARTH_MASSES) << " Earth Masses" << endl;
  }
  
  if (system_count > 1)
  {
    if (out_format == ffHTML)
    {
      if (do_gases)
      {
	html_thumbnail_totals(thumbnails);
      }
      close_html_file(thumbnails);
    }
  }
  
  return EXIT_SUCCESS;
}

void init()
{
  if (!flag_seed)
  {
    time_t temp_time;
    unsigned seed = (unsigned)(time(&temp_time));
    srand(seed);
    flag_seed = rand();
  }
  srand(flag_seed);
  system_seed = flag_seed;
}

int system_counter = 0;

void generate_stellar_system(sun &the_sun, bool use_seed_system, planet *seed_system, string flag_char, int sys_no, string system_name, long double inner_dust_limit, long double outer_planet_limit, long double ecc_coef, long double inner_planet_factor, bool do_gases, bool do_moons)
{
  do_gases = (flags_arg_clone & fDoGases) != 0;
  do_moons = (flags_arg_clone & fDoMoons) != 0;
  system_counter++;
  long double outer_dust_limit;
  
  if (!the_sun.getIsCircumbinary())
  {
    outer_dust_limit = stellar_dust_limit(the_sun.getMass());
  }
  else
  {
    outer_dust_limit = stellar_dust_limit(the_sun.getCombinedMass());
  }
  
  if (the_sun.getLuminosity() == 0)
  {
    the_sun.setLuminosity(mass_to_luminosity(the_sun.getMass()));
  }
  if (the_sun.getMass() == 0)
  {
    the_sun.setMass(luminosity_to_mass(the_sun.getLuminosity()));
  }
  
  if (the_sun.getMass() == 0)
  {
    //cout << system_name << " " << sys_no << endl;
  }
  
  if (the_sun.getEffTemp() == 0)
  {
    the_sun.setEffTemp(spec_type_to_eff_temp(the_sun.getSpecType()));
  }
  max_age = max_age_backup;
  if (use_seed_system)
  {
    innermost_planet = seed_system;
    
    long double max_age_of_star = the_sun.getLife();
    if (max_age_of_star > 10E9)
    {
      max_age_of_star = 10E9;
    }
    if (max_age > max_age_of_star)
    {
      max_age = max_age_of_star;
    }
    if (min_age > max_age_of_star)
    {
      min_age = max_age_of_star;
    }
    //cout << min_age << " " << max_age << endl;
    the_sun.setAge(random_number(min_age, max_age));
  }
  else
  {
    long double max_age_of_star = the_sun.getLife();
    if (max_age_of_star > 10E9)
    {
      max_age_of_star = 10E9;
    }
    if (max_age > max_age_of_star)
    {
      max_age = max_age_of_star;
    }
    if (min_age > max_age_of_star)
    {
      min_age = max_age_of_star;
    }
    //cout << min_age << " " << max_age << endl;
    innermost_planet = dist_planetary_masses(the_sun, inner_dust_limit, outer_dust_limit, outer_planet_limit, dust_density_coeff, ecc_coef, inner_planet_factor, seed_system, do_moons);
    the_sun.setAge(random_number(min_age, max_age));
  }
  //cout << "test" << system_counter << endl;
  generate_planets(the_sun, !use_seed_system, flag_char, sys_no, system_name, do_gases, do_moons);
}

void generate_planets(sun &the_sun, bool random_tilt, string flag_char, int sys_no, string system_name, bool do_gases, bool do_moons)
{
  do_gases = (flags_arg_clone & fDoGases) != 0;
  do_moons = (flags_arg_clone & fDoMoons) != 0;
  planet *the_planet;
  int planet_no = 0;
  planet *moon;
  int moons = 0;
  
  for (the_planet = innermost_planet, planet_no = 1; the_planet != NULL; the_planet = the_planet->next_planet, planet_no++)
  {
    string planet_id;
    stringstream ss;
    
    ss.str("");
    ss << system_name <<" (-s" << toString(flag_seed) << " -" << flag_char << toString(sys_no) << ") " << toString(planet_no);
    planet_id = ss.str();
    //cout << planet_id << endl;
    if (!(the_planet->getKnownRadius() > 0))
    {
      the_planet->setImf(0);
      the_planet->setRmf(0);
      the_planet->setCmf(0);
    }
    
    if (!the_sun.getIsCircumbinary())
    {
      generate_planet(the_planet, planet_no, the_sun, random_tilt, planet_id, do_gases, do_moons, false, the_sun.getMass());
    }
    else
    {
      generate_planet(the_planet, planet_no, the_sun, random_tilt, planet_id, do_gases, do_moons, false, the_sun.getCombinedMass());
    }
    
    check_planet(the_planet, planet_id, false);
    
    if (do_moons)
    {
      for (moon = the_planet->first_moon, moons = 1; moon != NULL; moon = moon->next_planet, moons++)
      {
	string moon_id;
	
	ss.str("");
	ss << planet_id << "-" << toString(moons);
	moon_id = ss.str();
	
	check_planet(moon, moon_id, true);
      }
    }
  }
}

void generate_planet(planet* the_planet, int planet_no, sun& the_sun, bool random_tilt, string planet_id, bool do_gases, bool do_moons, bool is_moon, long double parent_mass)
{
  do_gases = (flags_arg_clone & fDoGases) != 0;
  do_moons = (flags_arg_clone & fDoMoons) != 0;
  long double tmp;
  long double ecc_coef = 0.077;
  long double lambda;
  long double the_fudged_radius = 0.0;
  
  if (do_moons && !is_moon)
  {
    srandf(system_seed + (1000 * planet_no));
  }
  
  the_planet->setTheSun(the_sun);
  
  the_planet->setOrbitZone(orb_zone(the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA()));
  
  the_planet->setHzd(calcHzd(the_planet));
  
  assign_composition(the_planet, the_sun, is_moon);

  if (!is_moon)
  {
    the_planet->setOrbPeriod(period(the_planet->getA(), the_planet->getMass(), parent_mass));
    if (random_tilt || the_planet->getAxialTilt() == 0)
    {
      the_planet->setAxialTilt(inclination(the_planet->getA(), parent_mass));
    }
  }
  else
  {
    the_planet->setOrbPeriod(period(the_planet->getMoonA(), the_planet->getMass(), parent_mass));
    if (random_tilt || the_planet->getAxialTilt() == 0)
    {
      the_planet->setAxialTilt(inclination(the_planet->getMoonA(), parent_mass));
    }
  }
  
  the_planet->setInclination(gaussian(1.0));
  
  the_planet->setAscendingNode(random_number(0.0, 360.0));
  the_planet->setLongitudeOfPericenter(random_number(0.0, 360.0));
  the_planet->setMeanLongitude(random_number(0.0, 360.0));
  
  the_planet->setExosphericTemp(EARTH_EXOSPHERE_TEMP / pow2(the_planet->getA() / the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES)));
  the_planet->setRmsVelocity(rms_vel(MOL_NITROGEN, the_planet->getExosphericTemp()));
  the_planet->setCoreRadius(radius_improved(the_planet->getDustMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), false, the_planet->getOrbitZone(), the_planet));
  
  the_planet->setDensity(empirical_density(the_planet->getMass(), the_planet->getA(), the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), true));
  the_planet->setRadius(volume_radius(the_planet->getMass(), the_planet->getDensity()));
  
  the_planet->setSurfAccel(acceleration(the_planet->getMass(), the_planet->getRadius()));
  the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
  
  the_planet->setMolecWeight(min_molec_weight(the_planet));
  
  bool force_gas_giant = false;
  if ((the_planet->getGasMass() / the_planet->getMass()) > 0.05 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 10.0)
  {
    force_gas_giant = true;
  }
  if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 1.0 && (the_planet->getGasMass() / the_planet->getMass()) > 0.05 && min_molec_weight(the_planet) <= 4.0) || ((the_planet->getGasMass() / the_planet->getMass()) > 0.2 && the_planet->getA() < 0.8) || force_gas_giant) // it's a gas planet
  {
    if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 10.0)
    {
      the_planet->setType(tSubSubGasGiant); // it's a gas dwarf
    }
    else if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 50.0)
    {
      the_planet->setType(tSubGasGiant); // it's a neptunian
    }
    else if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) / JUPITER_MASS) >= 13.0)
    {
      the_planet->setType(tBrownDwarf); // it's a brown dwarf
    }
    else
    {
      the_planet->setType(tGasGiant); // it's a jovian
    }
  }
  else // If not, it's rocky.
  {
    the_fudged_radius = fudged_radius(the_planet->getMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet);
    the_planet->setRadius(radius_improved(the_planet->getMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), false, the_planet->getOrbitZone(), the_planet));
    the_planet->setDensity(volume_density(the_planet->getMass(), the_planet->getRadius()));
    
    the_planet->setSurfAccel(acceleration(the_planet->getMass(), the_planet->getRadius()));
    the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
    
    if ((the_planet->getGasMass() / the_planet->getMass()) > 0.000001)
    {
      long double h2_mass = the_planet->getGasMass() * 0.85;
      long double he_mass = (the_planet->getGasMass() - h2_mass) * 0.999;
      
      long double h2_loss = 0.0;
      long double he_loss = 0.0;
      
      long double h2_life = gas_life(MOL_HYDROGEN, the_planet);
      long double he_life = gas_life(HELIUM, the_planet);
      
      if (h2_life < the_sun.getAge())
      {
	h2_loss = ((1.0 - (1.0 / exp(the_sun.getAge() / h2_life))) * h2_mass);
	
	the_planet->setGasMass(the_planet->getGasMass() - h2_loss);
	
	the_planet->setSurfAccel(acceleration(the_planet->getMass(), the_planet->getRadius()));
	the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
      }
      
      if (he_life < the_sun.getAge())
      {
	he_loss = ((1.0 - (1.0 / exp(the_sun.getAge() / he_life))) * he_mass);
	
	the_planet->setGasMass(the_planet->getGasMass() - he_loss);
	
	the_planet->setSurfAccel(acceleration(the_planet->getMass(), the_planet->getRadius()));
	the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
      }
      
      if ((h2_loss + he_loss) > .000001 && flag_verbose & 0x0080)
      {
	cerr << planet_id << "\tLosing gas: H2: " << toString(h2_loss * SUN_MASS_IN_EARTH_MASSES) << " EM, He: " << toString(he_loss * SUN_MASS_IN_EARTH_MASSES) << " EM" << endl;
      }
    }
  }
  
  the_planet->setDay(day_length(the_planet, parent_mass, is_moon));
  the_planet->setOblateness(calcOblateness(the_planet));
  
  the_planet->setEscVelocity(escape_vel(the_planet->getMass(), the_planet->getRadius()));
  
  if (is_gas_planet(the_planet))
  {
    the_planet->setGreenhouseEffect(false);
    the_planet->setVolatileGasInventory(INCREDIBLY_LARGE_NUMBER);
    the_planet->setSurfPressure(INCREDIBLY_LARGE_NUMBER);
    
    the_planet->setBoilPoint(INCREDIBLY_LARGE_NUMBER);
    
    the_planet->setGreenhsRise(0);
    
    the_planet->setHydrosphere(1);
    the_planet->setCloudCover(1);
    the_planet->setIceCover(0);
    the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
    if (force_gas_giant)
    {
      the_planet->setMolecWeight(about(0.5, 0.1));
    }
    else
    {
      the_planet->setMolecWeight(min_molec_weight(the_planet));
    }
    
    gas_giant_temperature_albedo(the_planet, parent_mass, is_moon);
    //the_planet->setDay(day_length(the_planet, parent_mass, is_moon));
    //the_planet->setOblateness(calcOblateness(the_planet));
    
    the_planet->setDensity(volume_density(the_planet->getMass(), the_planet->getRadius()));
    
    the_planet->setEstimatedTerrTemp(est_temp(the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), EARTH_ALBEDO));
    
    if (do_gases)
    {
      the_sun = the_planet->getTheSun();
      calculate_gases(the_sun, the_planet, planet_id);
    }
    
    long double temp = the_planet->getEstimatedTerrTemp();
    
    if (is_habitable_jovian(the_planet))
    {
      habitable_jovians++;
      
      if (flag_verbose & 0x8000)
      {
	string planet_type, moon_string;
	planet_type = type_string(the_planet);
	if (the_planet->first_moon != NULL)
	{
	  moon_string = " WITH MOON";
	}
	else
	{
	  moon_string = "";
	}
	cerr << planet_id << "\t" << planet_type << " (" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EM " << toString(the_sun.getAge() / 1.0E9) << " By)" << moon_string << " with earth-like temperature (" << toString(temp - FREEZING_POINT_OF_WATER) << " C, " << toString(32.0 + ((temp - FREEZING_POINT_OF_WATER) * 1.8)) << " F, " << (temp - EARTH_AVERAGE_KELVIN) << " C Earth)." << endl;
      }
    }
  }
  else
  {
    the_planet->setEstimatedTemp(est_temp(the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(),  EARTH_ALBEDO));
    the_planet->setEstimatedTerrTemp(est_temp(the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(),  EARTH_ALBEDO));
    
    the_planet->setSurfGrav(gravity(the_planet->getSurfAccel()));
    the_planet->setMolecWeight(min_molec_weight(the_planet));
    
    the_planet->setGreenhouseEffect(grnhouse(the_sun.getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA()));
    long double fudged_escape_velocity = escape_vel(the_planet->getMass(), the_fudged_radius);
    the_planet->setVolatileGasInventory(vol_inventory(the_planet->getMass(), fudged_escape_velocity, the_planet->getRmsVelocity(), the_sun.getMass(), the_planet->getOrbitZone(), the_planet->getGreenhouseEffect(), the_planet->getGasMass() > 0.0));
    the_planet->setSurfPressure(pressure(the_planet->getVolatileGasInventory(), the_fudged_radius, the_planet->getSurfGrav()));
    
    if (the_planet->getSurfPressure() == 0.0)
    {
      the_planet->setBoilPoint(0.0);
    }
    else
    {
      the_planet->setBoilPoint(boiling_point(the_planet->getSurfPressure()));
    }
    
    iterate_surface_temp(the_planet, do_gases);
    
    if (do_gases)
    {
      the_sun = the_planet->getTheSun();
      calculate_gases(the_sun, the_planet, planet_id);
    }
    
    assign_type(the_sun, the_planet, planet_id, is_moon, do_gases, false);
  }
  
  the_planet->setHzc(calcHzc(the_planet));
  the_planet->setHza(calcHza(the_planet));
  the_planet->setEsi(calcEsi(the_planet));
  the_planet->setSph(calcSph(the_planet));
  
  if (do_moons && !is_moon)
  {
    bool skip_minor_moons = false;
    long double moon_mass = 0.0;
    int n;
    stringstream ss;
    string moon_id;
    long double temp_hill_sphere = 0;
    long double min_rand_distance = 0;
    if (the_planet->first_moon != NULL)
    {
      planet *ptr = NULL;
      planet *prev = NULL;
      planet *next_moon = NULL;
      
      // reset moon distances for predefined moons
      /*for (n = 0, ptr = the_planet->first_moon; ptr != NULL; ptr = next_moon)
      {
	next_moon = ptr->next_planet;
	ptr->setMoonA(0);
	ptr->setMoonE(0);
      }*/
      
      long double hill_sphere = 0.0;
      
      hill_sphere = the_planet->getA() * KM_PER_AU * pow(the_planet->getMass() / (3.0 * the_sun.getMass()), 1.0 / 3.0);
      
      for (n = 0, ptr = the_planet->first_moon; ptr != NULL; ptr = next_moon)
      //for (n = 0; n < the_planet->getMoonCount(); n++)
      {
	next_moon = ptr->next_planet;
	moon_mass += ptr->getMass() * SUN_MASS_IN_EARTH_MASSES;
	
	long double roche_limit = 0.0;
	long double distance = 0.0;
	long double eccentricity = 0.0;
	
	ptr->setA(the_planet->getA());
	ptr->setE(the_planet->getE());
	ptr->setOrbitZone(the_planet->getOrbitZone());
	
	assign_composition(ptr, the_sun, true);
	
	ss.str("");
	ss << planet_id << "-" << toString(n + 1);
	moon_id = ss.str();
	ss.str("");
	
	//generate_planet(ptr, n, the_sun, random_tilt, moon_id, do_gases, do_moons, true, the_planet->getMass());
	ptr->setRadius(radius_improved(ptr->getMass(), ptr->getImf(), ptr->getRmf(), ptr->getCmf(), false, ptr->getOrbitZone(), ptr));
	ptr->setDensity(volume_density(ptr->getMass(), ptr->getRadius()));
	
	roche_limit = 2.44 * the_planet->getRadius() * pow(the_planet->getDensity() / ptr->getDensity(), 1.0 / 3.0);
	
	if ((roche_limit * 1.5) < (hill_sphere / 3.0) && (hill_sphere / 3.0) > (the_planet->getRadius() * 2.5))
	{
	  bool done = false;
	  bool bad_place;
	  bool to_many_tries = false;
	  planet *the_moon = NULL;
	  long double hill_sphere2 = 0;
	  int tries = 0;
	  while (!done)
	  {
	    tries++;
	    if (tries > 20)
	    {
	      to_many_tries = true;
	      break;
	    }
	    bad_place = false;
	    
	    if ((roche_limit * 1.5) > (the_planet->getRadius() * 2.5))
	    {
	      min_rand_distance = roche_limit * 1.5;
	    }
	    else
	    {
	      min_rand_distance = the_planet->getRadius() * 2.5;
	    }
	    
	    distance = random_number(min_rand_distance, hill_sphere / 3.0);
	    eccentricity = random_number(0, 0.01); // I know I should use random_eccentricity here but I want to prevent orbits from crossing each other
	    for (the_moon = the_planet->first_moon; the_moon != NULL; the_moon = the_moon->next_planet)
	    {
	      hill_sphere2 = the_moon->getMoonA() * KM_PER_AU * pow(the_moon->getMass() / (3.0 * the_planet->getMass()), 1.0 / 3.0);
	      temp_hill_sphere = distance * pow(ptr->getMass() / (3.0 * the_planet->getMass()), 1.0 / 3.0);
	      if (((the_moon->getMoonA() * KM_PER_AU) >= (distance - temp_hill_sphere) && (the_moon->getMoonA() * KM_PER_AU) <= (distance + temp_hill_sphere)) || (distance >= ((the_moon->getMoonA() * KM_PER_AU) - hill_sphere2) && distance <= ((the_moon->getMoonA() * KM_PER_AU) + hill_sphere2)))
	      {
		bad_place = true;
		break;
	      }
	    }
	    if (!bad_place)
	    {
	      done = true;
	    }
	  }
	  
	  if (to_many_tries)
	  {
	    bool dont_break = false;
	    if (flag_verbose & 0x1000)
	    {
	      cerr << "  " << planet_id << ": can't fit anymore moons!" << endl;
	    }
	    skip_minor_moons = true;
	    planet *node = NULL;
	    planet *next = NULL;
	    for (node = ptr; node != NULL; node = next)
	    {
	      next = node->next_planet;
	      if (node->getDeletable())
	      {
		delete node;
	      }
	      else
	      {
		node->next_planet = node->reconnect_to;
		n = 0;
		the_planet->first_moon = the_planet->first_moon_backup;
		ptr = the_planet->first_moon;
		dont_break = true;
		continue;
	      }
	    }
	    if (prev != NULL)
	    {
	      prev->next_planet = NULL;
	    }
	    else
	    {
	      the_planet->first_moon = NULL;
	    }
	    /*for (int m = n; m < the_planet->getMoonCount(); m++)
	    {
	      the_planet->deleteMoon(m);
	    }*/
	    if (!dont_break)
	    {
	      break;
	    }
	  }
	  else
	  {
	    ptr->setMoonA(distance / KM_PER_AU);
	    ptr->setMoonE(eccentricity);
	    
	    ptr->setOrbPeriod(period(ptr->getMoonA(), ptr->getMass(), the_planet->getMass()));
	    ptr->setType(tUnknown);
	    generate_planet(ptr, n, the_sun, random_tilt, moon_id, do_gases, do_moons, true, the_planet->getMass());
	    
	    if (flag_verbose & 0x40000)
	    {
	      cerr << "   Roche limit: R = " << toString(the_planet->getRadius()) << ", rM = " << toString(the_planet->getDensity()) << ", rm = " << toString(ptr->getDensity()) << " -> " << toString(roche_limit) << " km" << endl;
	      cerr << "   Hill Sphere: a = " << toString(the_planet->getA() * KM_PER_AU) << ", m = " << toString(the_planet->getMass() * SOLAR_MASS_IN_KILOGRAMS) << ", M = " << toString(the_sun.getMass() * SOLAR_MASS_IN_KILOGRAMS) << " -> " << toString(hill_sphere) << " km" << endl;
	      cerr << moon_id << " Moon orbit: a = " << toString(ptr->getMoonA() * KM_PER_AU) << " km, e = " << toString(ptr->getMoonE()) << endl;
	    }
	    
	    if (flag_verbose & 0x1000)
	    {
	      cerr << "  " << planet_id << ": (" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EM) " << n << " " << toString(ptr->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EM" << endl;
	    }
	    prev = ptr;
	  }
	}
	else
	{
	  if (flag_verbose & 0x1000)
	  {
	    cerr << "  " << planet_id << " lost moons due to gravity of the sun!" << endl;
	  }
	  skip_minor_moons = true;
	  // delete moons
	  planet *node = NULL;
	  planet *next = NULL;
	  for (node = the_planet->first_moon; node != NULL; node = next)
	  {
	    next = node->next_planet;
	    if (node->getDeletable())
	    {
	      delete node;
	    }
	    else
	    {
	      node->next_planet = node->reconnect_to;
	      n = 0;
	      the_planet->first_moon = the_planet->first_moon_backup;
	      ptr = the_planet->first_moon;
	      continue;
	    }
	  }
	  n = 0;
	  the_planet->first_moon = NULL;
	  /*for (int m = 0; m < the_planet->getMoonCount(); m++)
	   *	    {
	   *	      the_planet->deleteMoon(m);
	   }*/
	  break;
	}
      }
    }
    
    if (skip_minor_moons)
    {
      the_planet->setMinorMoons(0);
    }
    else
    {
      the_planet->setMinorMoons(poisson(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES));
    }
    
    if (the_planet->getMinorMoons() > 0)
    {
      long double max_total_moon_mass;
      long double remaining_moon_mass;
      long double new_moon_mass;
      long double new_moon_gas_mass;
      long double min_new_moon_mass = 1.0 / 100000000000.0;
      planet *tmp = NULL;
      planet *ref = NULL;
      int attempts = 0;
      bool done2 = false;
      bool too_many_tries = false;
      bool bad_place2;
      long double hill_sphere3 = 0;
      long double hill_sphere4 = 0;
      long double roche_limit2 = 0;
      int tries2 = 0;
      
      hill_sphere3 = the_planet->getA() * KM_PER_AU * pow(the_planet->getMass() / (3.0 * the_sun.getMass()), 1.0 / 3.0);
      if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 1000.0)
      {
	max_total_moon_mass = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES * 0.05;
      }
      else if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 10.0)
      {
	max_total_moon_mass = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES * (1.5 / 10000.0);
      }
      else if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 0.5)
      {
	if (the_planet->getRadius() > 15000.0)
	{
	  max_total_moon_mass = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES * 0.01;
	}
	else
	{
	  max_total_moon_mass = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES * 0.05;
	}
      }
      else
      {
	max_total_moon_mass = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES * (1.5 / 10000.0);
      }
      remaining_moon_mass = max_total_moon_mass - moon_mass;
      
      // get the pointer to the last moon in the list
      if (the_planet->first_moon != NULL)
      {
	tmp = the_planet->first_moon;
	while (true)
	{
	  if (tmp->next_planet == NULL)
	  {
	    break;
	  }
	  tmp = tmp->next_planet;
	}
      }
      else
      {
	tmp = NULL;
      }
      
      n++;
      int moon_count = 0;
      while (true)
      {
	done2 = false;
	ss.str("");
	ss << planet_id << "-" << toString(n);
	moon_id = ss.str();
	ss.str("");
	
	if (remaining_moon_mass <= 0.0 || attempts > 5 || moon_count > the_planet->getMinorMoons() || (hill_sphere3 / 3.0) <= the_planet->getRadius())
	{
	  break;
	}
	planet *new_moon = NULL;
	new_moon = new planet();
	new_moon->setPlanetNo(n);
	new_moon->setOrbitZone(the_planet->getOrbitZone());
	new_moon->setA(the_planet->getA());
	new_moon->setE(the_planet->getE());
	new_moon->setHzd(the_planet->getHzd());
	
	double r1 = randf();
	double maxln = exp(1.0);
	double r2 = log(1.0 + (maxln * r1)) / 1.33;
	
	new_moon_mass = r2 * remaining_moon_mass;
	
	if (new_moon_mass < min_new_moon_mass)
	{
	  new_moon_mass = min_new_moon_mass;
	}
	
	if (new_moon_mass > 10.0)
	{
	  new_moon_gas_mass = new_moon_mass * random_number(0.05, 1.0);
	  new_moon->setGasGiant(true);
	}
	else
	{
	  new_moon_gas_mass = 0;
	  new_moon->setGasGiant(false);
	}
	new_moon->setDustMass((new_moon_mass - new_moon_gas_mass) / SUN_MASS_IN_EARTH_MASSES);
	new_moon->setGasMass(new_moon_gas_mass / SUN_MASS_IN_EARTH_MASSES);
	
	assign_composition(new_moon, the_sun, true);
	
	//generate_planet(new_moon, n, the_sun, random_tilt, moon_id, do_gases, do_moons, true, the_planet->getMass());
	new_moon->setRadius(radius_improved(new_moon->getMass(), new_moon->getImf(), new_moon->getRmf(), new_moon->getCmf(), false, new_moon->getOrbitZone(), new_moon));
	new_moon->setDensity(volume_density(new_moon->getMass(), new_moon->getRadius()));
	
	long double distance2;
	long double eccentricity2;
	
	roche_limit2 = 2.44 * the_planet->getRadius() * pow(the_planet->getDensity() / new_moon->getDensity(), 1.0 / 3.0);
	if ((roche_limit2 * 1.5) >= (hill_sphere3 / 3.0))
	{
	  if (flag_verbose & 0x1000)
	  {
	    cerr << "  " << planet_id << ": Can't add anymore moons!" << endl;
	  }
	  delete new_moon;
	  break;
	}
	tries2 = 0;
	while (!done2)
	{
	  tries2++;
	  bad_place2 = false;
	  too_many_tries = false;
	  distance2 = random_number(roche_limit2 * 1.5, hill_sphere3 / 3.0);
	  eccentricity2 = random_number(0, 0.01); // I know I should use random_eccentricity here but I want to prevent orbits from crossing each other
	  if (flag_verbose & 0x1000)
	  {
	    cerr << "  " << planet_id << ": Attempting to add moon (" << toString(new_moon->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EU) at " << toString(distance2) << " km with eccentricity of " << toString(eccentricity2) << endl;
	  }
	  
	  for (ref = the_planet->first_moon; ref != NULL; ref = ref->next_planet)
	  {
	    hill_sphere4 = ref->getMoonA() * KM_PER_AU * pow(ref->getMass() / (3.0 * the_planet->getMass()), 1.0 / 3.0);
	    temp_hill_sphere = distance2 * pow(new_moon->getMass() / (3.0 * the_planet->getMass()), 1.0 / 3.0);
	    //cout << toString(distance2) << " " << toString(distance2 - temp_hill_sphere) << " " << toString(distance2 + temp_hill_sphere) << endl;
	    if (((ref->getMoonA() * KM_PER_AU) >= (distance2 - temp_hill_sphere) && (ref->getMoonA() * KM_PER_AU) <= (distance2 + temp_hill_sphere)) || (distance2 >= ((ref->getMoonA() * KM_PER_AU) - hill_sphere4) && distance2 <= ((ref->getMoonA() * KM_PER_AU) + hill_sphere4)))
	    {
	      bad_place2 = true;
	      if (flag_verbose & 0x1000)
	      {
		cerr << "  Failed due to neighboring moon." << endl;
	      }
	      break;
	    }
	  }
	  if (!bad_place2 || tries2 > 20)
	  {
	    done2 = true;
	  }
	  if (tries2 > 20)
	  {
	    too_many_tries = true;
	  }
	}
	new_moon->setMoonA(distance2 / KM_PER_AU);
	new_moon->setMoonE(eccentricity2);
	if (bad_place2 || too_many_tries)
	{
	  delete new_moon;
	  attempts++;
	  if (flag_verbose & 0x1000)
	  {
	    cerr << "  Failed to add moon." << endl;
	  }
	}
	else
	{
	  attempts = 0;
	  generate_planet(new_moon, n, the_sun, random_tilt, moon_id, do_gases, do_moons, true, the_planet->getMass());
	  if (tmp != NULL)
	  {
	    tmp->next_planet = new_moon;
	    tmp = tmp->next_planet;
	  }
	  else
	  {
	    the_planet->first_moon = new_moon;
	    tmp = the_planet->first_moon;
	  }
	  //the_planet->addMoon(new_moon);
	  remaining_moon_mass -= new_moon_mass;
	  moon_mass += new_moon_mass;
	  n++;
	  moon_count++;
	  
	  if (flag_verbose & 0x40000)
	  {
	    cerr << "   Roche limit: R = " << toString(the_planet->getRadius()) << ", rM = " << toString(the_planet->getDensity()) << ", rm = " << toString(new_moon->getDensity()) << " -> " << toString(roche_limit2) << " km" << endl;
	    cerr << "   Hill Sphere: a = " << toString(the_planet->getA() * KM_PER_AU) << ", m = " << toString(the_planet->getMass() * SOLAR_MASS_IN_KILOGRAMS) << ", M = " << toString(the_sun.getMass() * SOLAR_MASS_IN_KILOGRAMS) << " -> " << toString(hill_sphere3) << " km" << endl;
	    cerr << moon_id << " Moon orbit: a = " << toString(new_moon->getMoonA() * KM_PER_AU) << " km, e = " << toString(new_moon->getMoonE()) << endl;
	  }
	  
	  if (flag_verbose & 0x1000)
	  {
	    cerr << "  New Moon for " << planet_id << ": (" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EM) " << n << " " << toString(new_moon->getMass() * SUN_MASS_IN_EARTH_MASSES) << " EM" << endl;
	  }
	}
      }
      
      if (the_planet->first_moon != NULL)
      {
	// reorder the moons
	the_planet->sortMoons();
	
	// make some modifications to the moons
	int moon_number = 0;
	for (tmp = the_planet->first_moon, moon_number = 1; tmp != NULL; tmp = tmp->next_planet, moon_number++)
	{
	  tmp->setPlanetNo(moon_number);
	  ss.str("");
	  ss << planet_id << "-" << tmp->getPlanetNo();
	  moon_id = ss.str();
	  
	  // change inclinations
	  long double fdist = (tmp->getMoonA() * KM_PER_AU) / (hill_sphere3 / 3.0);
	  long double fmass = pow(moon_mass / (tmp->getMass() * SUN_MASS_IN_EARTH_MASSES), 0.2);
	  tmp->setInclination(fdist * fmass * tmp->getInclination());
	  
	  if (tmp->getGasMass() == 0)
	  {
	    // we don't want moons with too thick an atmosphere
	    if (tmp->getSurfPressure() > 6000)
	    {
	      tmp->setType(tUnknown);
	      tmp->setSurfPressure(calcPhlPressure(tmp) * EARTH_SURF_PRES_IN_MILLIBARS);
	      while (tmp->getSurfPressure() > 6000)
	      {
		tmp->setSurfPressure(tmp->getSurfPressure() - 1.0);
	      }
	      iterate_surface_temp(tmp, do_gases);
	      if (do_gases)
	      {
		tmp->clearGases();
		calculate_gases(the_sun, tmp, moon_id);
	      }
	      assign_type(the_sun, tmp, moon_id, true, do_gases, false);
	    }
	  }
	  
	  tmp->setHzc(calcHzc(tmp));
	  tmp->setHza(calcHza(tmp));
	  tmp->setEsi(calcEsi(tmp));
	  tmp->setSph(calcSph(tmp));
	}
      }
    }
  }
}

void check_planet(planet* the_planet, string planet_id, bool is_moon)
{
  int tIndex = 0;
  
  if (the_planet->getType() == tUnknown)
  {
    tIndex = 0;
  }
  else if (the_planet->getType() == tRock)
  {
    tIndex = 1;
  }
  else if (the_planet->getType() == tVenusian)
  {
    tIndex = 2;
  }
  else if (the_planet->getType() == tTerrestrial)
  {
    tIndex = 3;
  }
  else if (the_planet->getType() == tSubSubGasGiant)
  {
    tIndex = 4;
  }
  else if (the_planet->getType() == tSubGasGiant)
  {
    tIndex = 5;
  }
  else if (the_planet->getType() == tGasGiant)
  {
    tIndex = 6;
  }
  else if (the_planet->getType() == tMartian)
  {
    tIndex = 7;
  }
  else if (the_planet->getType() == tWater)
  {
    tIndex = 8;
  }
  else if (the_planet->getType() == tIce)
  {
    tIndex = 9;
  }
  else if (the_planet->getType() == tAsteroids)
  {
    tIndex = 10;
  }
  else if (the_planet->getType() == t1Face)
  {
    tIndex = 11;
  }
  else if (the_planet->getType() == tBrownDwarf)
  {
    tIndex = 12;
  }
  else if (the_planet->getType() == tIron)
  {
    tIndex = 13;
  }
  else if (the_planet->getType() == tCarbon)
  {
    tIndex = 14;
  }
  else if (the_planet->getType() == tOil)
  {
    tIndex = 15;
  }
  
  if (type_counts[tIndex] == 0)
  {
    ++type_count;
  }
  
  ++type_counts[tIndex];
  
  unsigned int breathe = breathability(the_planet);
  
  //if (breathe == BREATHABLE && the_planet->getA() > habitable_zone_distance(the_planet->getTheSun(), RECENT_VENUS) && the_planet->getA() < habitable_zone_distance(the_planet->getTheSun(), EARLY_MARS))
  total_worlds++;
  if (is_habitable(the_planet))
  {
    bool list_it = false;
    long double illumination = calcLuminosity(the_planet);
    
    habitable++;
    
    if (is_habitable_earth_like(the_planet))
    {
      total_habitable_earthlike++;
      total_habitable_conservative++;
      total_habitable_optimistic++;
    }
    else if (is_habitable_conservative(the_planet))
    {
      total_habitable_conservative++;
      total_habitable_optimistic++;
    }
    else if (is_habitable_optimistic(the_planet))
    {
      total_habitable_optimistic++;
    }
    
    if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) >= 5.0 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) < 10.0) || (convert_km_to_eu(the_planet->getRadius()) >= 1.5 && convert_km_to_eu(the_planet->getRadius()) <= 2.5))
    {
      habitable_superterrans++;
    }
    
    if (min_breathable_temp > the_planet->getSurfTemp() || min_breathable_temp == 0.0)
    {
      min_breathable_temp = the_planet->getSurfTemp();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_breathable_temp < the_planet->getSurfTemp())
    {
      max_breathable_temp = the_planet->getSurfTemp();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_breathable_g > the_planet->getSurfGrav() || min_breathable_g == 0.0)
    {
      min_breathable_g = the_planet->getSurfGrav();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_breathable_g < the_planet->getSurfGrav())
    {
      max_breathable_g = the_planet->getSurfGrav();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_breathable_l > illumination || min_breathable_l == 0.0)
    {
      min_breathable_l = illumination;
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_breathable_l < illumination)
    {
      max_breathable_l = illumination;
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (the_planet->getType() == tTerrestrial)
    {
      if (min_breathable_terrestrial_g > the_planet->getSurfGrav() || min_breathable_terrestrial_g == 0.0)
      {
	min_breathable_terrestrial_g = the_planet->getSurfGrav();
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (max_breathable_terrestrial_g < the_planet->getSurfGrav())
      {
	max_breathable_terrestrial_g = the_planet->getSurfGrav();
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (min_breathable_terrestrial_l > illumination || min_breathable_terrestrial_l == 0.0)
      {
	min_breathable_terrestrial_l = illumination;
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (max_breathable_terrestrial_l < illumination)
      {
	max_breathable_terrestrial_l = illumination;
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
    }
    
    if (min_breathable_p > the_planet->getSurfPressure() || min_breathable_p == 0.0)
    {
      min_breathable_p = the_planet->getSurfPressure();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_breathable_p < the_planet->getSurfPressure())
    {
      max_breathable_p = the_planet->getSurfPressure();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_breathable_mass > the_planet->getMass() || min_breathable_mass == 0.0)
    {
      min_breathable_mass = the_planet->getMass();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_breathable_mass < the_planet->getMass())
    {
      max_breathable_mass = the_planet->getMass();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (flag_verbose & 0x0004)
    {
      list_it = true;
    }
    
    if (list_it)
    {
      cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) << "\tl=" << toString(illumination) << "\t" << planet_id << endl;
    }
  }
  else if (is_potentialy_habitable(the_planet))
  {
    potential_habitable++;
    bool list_it = false;
    long double illumination = calcLuminosity(the_planet);
    
    if (is_potentialy_habitable_earth_like(the_planet))
    {
      total_potentially_habitable_earthlike++;
      total_potentially_habitable_conservative++;
      total_potentially_habitable_optimistic++;
    }
    else if (is_potentialy_habitable_conservative(the_planet))
    {
      total_potentially_habitable_conservative++;
      total_potentially_habitable_optimistic++;
    }
    else if (is_potentialy_habitable_optimistic(the_planet))
    {
      total_potentially_habitable_optimistic++;
    }
    
    if (min_potential_temp > the_planet->getSurfTemp() || min_potential_temp == 0.0)
    {
      min_potential_temp = the_planet->getSurfTemp();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_potential_temp < the_planet->getSurfTemp())
    {
      max_potential_temp = the_planet->getSurfTemp();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_potential_g > the_planet->getSurfGrav() || min_potential_g == 0.0)
    {
      min_potential_g = the_planet->getSurfGrav();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_potential_g < the_planet->getSurfGrav())
    {
      max_potential_g = the_planet->getSurfGrav();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_potential_l > illumination || min_potential_l == 0.0)
    {
      min_potential_l = illumination;
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_potential_l < illumination)
    {
      max_potential_l = illumination;
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (the_planet->getType() == tTerrestrial || (the_planet->getType() == t1Face && the_planet->getHydrosphere() >= 0.05 && the_planet->getHydrosphere() <= 0.8))
    {
      if (min_breathable_terrestrial_g > the_planet->getSurfGrav() || min_breathable_terrestrial_g == 0.0)
      {
	min_breathable_terrestrial_g = the_planet->getSurfGrav();
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (max_breathable_terrestrial_g < the_planet->getSurfGrav())
      {
	max_breathable_terrestrial_g = the_planet->getSurfGrav();
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (min_breathable_terrestrial_l > illumination || min_breathable_terrestrial_l == 0.0)
      {
	min_breathable_terrestrial_l = illumination;
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
      
      if (max_breathable_terrestrial_l < illumination)
      {
	max_breathable_terrestrial_l = illumination;
	
	if (flag_verbose & 0x0002)
	{
	  list_it = true;
	}
      }
    }
    
    if (min_potential_p > the_planet->getSurfPressure() || min_potential_p == 0.0)
    {
      min_potential_p = the_planet->getSurfPressure();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_potential_p < the_planet->getSurfPressure())
    {
      max_potential_p = the_planet->getSurfPressure();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (min_potential_mass > the_planet->getMass() || min_potential_mass == 0.0)
    {
      min_potential_mass = the_planet->getMass();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (max_potential_mass < the_planet->getMass())
    {
      max_potential_mass = the_planet->getMass();
      
      if (flag_verbose & 0x0002)
      {
	list_it = true;
      }
    }
    
    if (flag_verbose & 0x0004)
    {
      list_it = true;
    }
    
    if (list_it)
    {
      cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) << "\tl=" << toString(illumination) << "\t" << planet_id << endl;
    }
  }
  
  if (is_moon && max_moon_mass < the_planet->getMass())
  {
    max_moon_mass = the_planet->getMass();
    
    if (flag_verbose & 0x0002)
    {
      cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) << "\t" << planet_id << endl;
    }
  }
  
  if ((flag_verbose & 0x0800) && (the_planet->getDustMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.0006 && (the_planet->getGasMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.0006 && the_planet->getType() != tGasGiant && the_planet->getType() != tSubGasGiant && the_planet->getType() != tBrownDwarf)
  {
    int core_size = (int)((50.0 * the_planet->getCoreRadius()) / the_planet->getRadius());
    
    if (core_size <= 49)
    {
      cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getCoreRadius()) << "\tr=" << toString(the_planet->getRadius()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\t" << planet_id << "\t" << (50 - core_size) << endl;
    }
  }
  
  long double rel_temp = (the_planet->getSurfTemp() - FREEZING_POINT_OF_WATER) - EARTH_AVERAGE_CELSIUS;
  long double seas = the_planet->getHydrosphere() * 100.0;
  long double clouds = the_planet->getCloudCover() * 100.0;
  long double pressure = the_planet->getSurfPressure() / EARTH_SURF_PRES_IN_MILLIBARS;
  long double ice = the_planet->getIceCover() * 100.0;
  long double gravity = the_planet->getSurfGrav();
  //unsigned int breathe = breathability(the_planet);
  breathe = breathability(the_planet);
  
  if (is_earth_like(the_planet))
  {
    earthlike++;
    
    if (flag_verbose & 0x0008)
    {
      cerr << type_string(the_planet) <<"\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) <<"\t" << habitable << " " << planet_id << "\tEarth-like" << endl;
    }
  }
  else if (breathe == BREATHABLE && gravity > 1.3 && rel_temp < -2.0 && ice < 10.0 && habitable > 1)
  {
    if (flag_verbose & 0x0008)
    {
      cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) << "\t" << habitable << " " << planet_id << "\tSphinx-like" << endl;
    }
  }
}

void assign_type(sun &the_sun, planet *the_planet, string planet_id, bool is_moon, bool do_gases, bool second_time)
{
  if (the_planet->getSurfPressure() < 1.0)
  {
    if (the_planet->getRadius() < round_threshold(the_planet->getDensity()))
    {
      the_planet->setType(tAsteroids);
    }
    else
    {
      if (the_planet->getImf() > 0.5 || the_planet->getIceCover() >= 0.5)
      {
	the_planet->setType(tIce);
      }
      else if ((the_planet->getImf() + the_planet->getRmf()) < 0.2)
      {
	the_planet->setType(tIron);
      }
      else if (the_planet->getCmf() >= 0.75)
      {
	the_planet->setType(tCarbon);
      }
      else
      {
	the_planet->setType(tRock);
      }
    }
  }
  /*else if (the_planet->getSurfPressure() > 6000.0 && the_planet->getMolecWeight() <= 2.0) // Retains Hydrogen
  {
    the_planet->setType(tSubSubGasGiant);
  }*/
  else
  {
    if ((((int)the_planet->getDay() == (int)(the_planet->getOrbPeriod() * 24.0)) || the_planet->getResonantPeriod()) && !is_moon)
    {
      the_planet->setType(t1Face);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getImf() >= 0.05 && the_planet->getHydrosphere() == 0.0)
    {
      the_planet->setType(tIce);
      /*the_planet->setIceCover(the_planet->getIceCover() + the_planet->getHydrosphere());
      if (the_planet->getIceCover() > 1.0)
      {
	the_planet->setIceCover(1.0);
      }*/
      the_planet->setHydrosphere(0.0);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getHydrosphere() >= 0.8) // In Star Trek, any planet that is 80% covered with water, it is considered an ocean planet
    {
      if (the_planet->getCmf() >= 0.75)
      {
	the_planet->setType(tOil);
      }
      else
      {
	the_planet->setType(tWater);
      }
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getIceCover() >= 0.8) // In Star Trek, any planet that is 80% covered with ice, it is considered an ice planet
    {
      the_planet->setType(tIce);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getHydrosphere() >= 0.05)
    {
      if (the_planet->getCmf() >= 0.75)
      {
	the_planet->setType(tOil);
      }
      else
      {
	the_planet->setType(tTerrestrial);
      }
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getSurfTemp() > the_planet->getBoilPoint())
    {
      the_planet->setType(tVenusian);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if ((the_planet->getGasMass() / the_planet->getMass()) > 0.0001)
    {
      the_planet->setType(tIce); // Accreted gas but no Greenhouseor or liquid water
      the_planet->setIceCover(1.0);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getSurfPressure() < 250)
    {
      the_planet->setType(tMartian);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else if (the_planet->getSurfTemp() < FREEZING_POINT_OF_WATER)
    {
      the_planet->setType(tIce);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
    }
    else
    {
      the_planet->setType(tUnknown);
      if (!second_time)
      {
	makeHabitable(the_sun, the_planet, planet_id, is_moon, do_gases);
      }
      
      if (flag_verbose & 0x0001)
      {
	string one_face_string;
	if (((int)the_planet->getDay() == (int)(the_planet->getOrbPeriod() * 24.0)) || the_planet->getResonantPeriod())
	{
	  one_face_string = "(1-Face)";
	}
	else
	{
	  one_face_string = "";
	}
	cerr << type_string(the_planet) << "\tp=" << toString(the_planet->getSurfPressure()) << "\tm=" << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << "\tg=" << toString(the_planet->getSurfGrav()) << "\tt=" << toString(the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN) << "\t" << planet_id << "\t Unknown " << one_face_string << endl;
      }
    }
  }
}