#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include "andromeda.h"
#include "dole.h"
#include "elements.h"
#include "ic3094.h"
#include "jimb.h"
#include "omega_galaxy.h"
#include "Planetary_Habitability_Laboratory.h"
#include "planets.h"
#include "radius_tables.h"
#include "ring_universe.h"
#include "solstation.h"
#include "stargen.h"
#include "star_trek.h"
#include "structs.h"
#include "utils.h"

using namespace std;

void initData();
void usage(string);

int main(int argc, char **argv)
{
  actions action = aGenerate;
  string flag_char = "?";
  string path = SUBDIR;
  string url_path_arg = "";
  string filename_arg = "";
  string arg_name = "";
  char arg_name_temp[80] = "";

  bool use_stdout = false;
  string prognam;
  long double mass_arg = 0.0;
  long double luminosity_arg = 0.0;
  long seed_arg = 0;
  int count_arg = 1;
  int increment_arg = 1;
  catalog star_catalog;
  int sys_no_arg = 0;

  long double ratio_arg = 0.0;
  long double ecc_coef_arg = 0.077; //seb: dole value
  long double inner_planet_factor_arg = 0.3; //seb: dole value

  int flags_arg = 0;
  int out_format = ffHTML;
  int graphic_format = gfGIF;
	
  const char *c;
  bool skip = false;
  int index = 0;
  
  string temp_string;

#ifdef macintosh
  _ftype  = 'TEXT';
  _fcreator = 'R*ch';
  argc = ccommand (&argv);
#endif
  
  initData();

  prognam = argv[0];
  if ((c = strrchr(prognam.c_str(), DIRSEP[0])) != NULL)
  {
    prognam = c + 1;
  }
  
  if (argc <= 1)
  {
    usage(prognam);
    return EXIT_FAILURE;
  }
  
  // need to somehow parse arguments
  bool first_part_of_name = true;
  for (int i = 0; i < argc; i++)
  {
    skip = false;
    temp_string = argv[i];
    if (compare_string_char(temp_string, 0, "-"))
    {
      if (compare_string_char(temp_string, 1, "-"))
      {
	use_stdout = true;
      }
      else if (compare_string_char(temp_string, 1, "PHL", 3))
      {
	star_catalog = phl;
	if (temp_string.length() > 2)
	{
	  sys_no_arg = atoi(temp_string.substr(4, temp_string.length() - 4).c_str());
	}
	else
	{
	  sys_no_arg = 0;
	}
	
	flag_char = star_catalog.getArg();
      }
      else if (compare_string_char(temp_string, 1, "sn", 2))
      {
	decimals_arg = atoi(temp_string.substr(3, temp_string.length() - 3).c_str());
      }
      else if (compare_string_char(temp_string, 1, "CB", 2))
      {
	flags_arg |= fIsCircubinaryStar;
      }
      else if (compare_string_char(temp_string, 1, "MY", 2))
      {
	max_age_backup = max_age = atof(temp_string.substr(3, temp_string.length() - 3).c_str());
      }
      else if (compare_string_char(temp_string, 1, "md", 2))
      {
	max_distance_arg = atof(temp_string.substr(3, temp_string.length() - 3).c_str());
      }
      else if (compare_string_char(temp_string, 1, "s"))
      {
	seed_arg = atol(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "m"))
      {
	mass_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "y"))
      {
	luminosity_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "Y"))
      {
	min_age = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "n"))
      {
	count_arg = atoi(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "i"))
      {
	increment_arg = atoi(temp_string.substr(2, temp_string.length() - 2).c_str());
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "x"))
      {
	flag_char = temp_string.substr(1, 1).c_str();
	flags_arg |= fUseSolarsystem;
	if (mass_arg == 0.0)
	  mass_arg = 1.0;
      }
      else if (compare_string_char(temp_string, 1, "a"))
      {
	flag_char = temp_string.substr(1, 1).c_str();
	flags_arg |= fReuseSolarsystem;
	break;
      }
      else if (compare_string_char(temp_string, 1, "D") || compare_string_char(temp_string, 1, "W") || compare_string_char(temp_string, 1, "F") || compare_string_char(temp_string, 1, "O") || compare_string_char(temp_string, 1, "R") || compare_string_char(temp_string, 1, "I") || compare_string_char(temp_string, 1, "U") || compare_string_char(temp_string, 1, "G"))
      {
	if (compare_string_char(temp_string, 1, "D"))
	{
	  star_catalog = dole;
	}
	else if (compare_string_char(temp_string, 1, "W"))
	{
	  star_catalog = solstation;
	}
	else if (compare_string_char(temp_string, 1, "F"))
	{
	  star_catalog = jimb;
	}
	else if (compare_string_char(temp_string, 1, "O"))
	{
	  star_catalog = omega_galaxy;
	}
	else if (compare_string_char(temp_string, 1, "R"))
	{
	  star_catalog = ring_universe;
	}
	else if (compare_string_char(temp_string, 1, "I"))
	{
	  star_catalog = ic3094;
	}
	else if (compare_string_char(temp_string, 1, "U"))
	{
	  star_catalog = andromeda;
	}
	else if (compare_string_char(temp_string, 1, "G"))
	{
	  star_catalog = star_trek;
	}
	if (temp_string.length() > 2)
	{
	  sys_no_arg = atoi(temp_string.substr(2, temp_string.length() - 2).c_str());
	}
	else
	{
	  sys_no_arg = 0;
	}
	
	flag_char = star_catalog.getArg();
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "o"))
      {
	filename_arg = argv[i + 1];
	skip = true;
      }
      else if (compare_string_char(temp_string, 1, "t"))
      {
	out_format = ffTEXT;
      }
      else if (compare_string_char(temp_string, 1, "e"))
      {
	out_format = ffCSV;
      }
      else if (compare_string_char(temp_string, 1, "C"))
      {
	out_format = ffCSVdl;
      }
      else if (compare_string_char(temp_string, 1, "c"))
      {
	out_format = ffCELESTIA;
      }
      /*else if (compare_string_char(temp_string, 1, "P"))
      {
	out_format = ffMOONGEN;
      }*/
      else if (compare_string_char(temp_string, 1, "V"))
      {
	graphic_format = gfSVG;
      }
      else if (compare_string_char(temp_string, 1, "S"))
      {
	graphic_format = gfSVG;
	out_format = ffSVG;
      }
      else if (compare_string_char(temp_string, 1, "k"))
      {
	flags_arg |= fUseKnownPlanets;
      }
      else if (compare_string_char(temp_string, 1, "K"))
      {
	flags_arg |= fUseKnownPlanets | fNoGenerate;
      }
      else if (compare_string_char(temp_string, 1, "p"))
      {
	path = argv[i + 1];
	skip = true;
      }
      else if (compare_string_char(temp_string, 1, "u"))
      {
	url_path_arg = argv[i + 1];
	skip = true;
      }
      else if (compare_string_char(temp_string, 1, "g"))
      {
	flags_arg |= fDoGases;
      }
      else if (compare_string_char(temp_string, 1, "v"))
      {
	if (temp_string.length() > 2)
	{
	  sscanf(temp_string.substr(2, temp_string.length() - 2).c_str(), "%x", &flag_verbose);
	  if (flag_verbose & 0x0001)
	  {
	    flags_arg |= fDoGases;
	  }
	  //skip = true;
	}
	else
	{
	  action = aListVerbosity;
	}
      }
      else if (compare_string_char(temp_string, 1, "l"))
      {
	action = aListCatalog;
      }
      else if (compare_string_char(temp_string, 1, "L"))
      {
	action = aListCatalogAsHTML;
      }
      else if (compare_string_char(temp_string, 1, "z"))
      {
	action = aSizeCheck;
      }
      else if (compare_string_char(temp_string, 1, "Z"))
      {
	action = aListGases;
      }
      else if (compare_string_char(temp_string, 1, "M"))
      {
	flags_arg |= fDoMoons;
      }
      else if (compare_string_char(temp_string, 1, "r"))
      {
	flags_arg |= fDoMigration;
      }
      else if (compare_string_char(temp_string, 1, "H"))
      {
	flags_arg |= fDoGases | fOnlyHabitable;
      }
      else if (compare_string_char(temp_string, 1, "2"))
      {
	flags_arg |= fDoGases | fOnlyMultiHabitable;
      }
      else if (compare_string_char(temp_string, 1, "3"))
      {
	flags_arg |= fDoGases | fOnlyThreeHabitable;
      }
      else if (compare_string_char(temp_string, 1, "J"))
      {
	flags_arg |= fDoGases | fOnlyJovianHabitable;
      }
      else if (compare_string_char(temp_string, 1, "E"))
      {
	flags_arg |= fDoGases | fOnlyEarthlike;
      }
      else if (compare_string_char(temp_string, 1, "P"))
      {
	flags_arg |= fDoGases | fOnlyPotentialHabitable;
      }
      else if (compare_string_char(temp_string, 1, "A"))
      {
	ratio_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (ratio_arg <= 0.0)
	{
	  cout << "Accrete dust density coefficient -A (" << ratio_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "Q"))
      {
	ecc_coef_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (ecc_coef_arg <= 0.0)
	{
	  cout << "Accrete eccentricity coeffecient -Q (" << ecc_coef_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "q"))
      {
	inner_planet_factor_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (inner_planet_factor_arg <= 0.0)
	{
	  cout << "Accrete inner dust boundary -q (" << inner_planet_factor_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "w"))
      {
	compainion_mass_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (compainion_mass_arg <= 0.0)
	{
	  cout << "Mass of compainion object -w (" << compainion_mass_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "f"))
      {
	compainion_eccentricity_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (compainion_eccentricity_arg <= 0.0)
	{
	  cout << "Eccentritiy of compainion object's orbit (" << compainion_eccentricity_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "d"))
      {
	compainion_distant_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (compainion_distant_arg <= 0.0)
	{
	  cout << "Distance of compainion object -d (" << compainion_distant_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "b"))
      {
	temp_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (temp_arg <= 0.0)
	{
	  cout << "Temperature of star -b (" << temp_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "B"))
      {
	type_arg = temp_string.substr(2, temp_string.length() - 2).c_str();
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "j"))
      {
	compainion_lum_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (compainion_lum_arg <= 0.0)
	{
	  cout << "Luminosity of companion star j (" << compainion_lum_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "X"))
      {
	compainion_eff_arg = atof(temp_string.substr(2, temp_string.length() - 2).c_str());
	if (compainion_eff_arg <= 0.0)
	{
	  cout << "Temperature of companion star X (" << compainion_lum_arg << ") must be > 0.0" << endl;
	  return EXIT_FAILURE;
	}
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "N"))
      {
	companion_spec_arg = temp_string.substr(2, temp_string.length() - 2).c_str();
	//skip = true;
      }
      else if (compare_string_char(temp_string, 1, "h"))
      {
	usage(prognam);
	return EXIT_FAILURE;
      }
      else
      {
	usage(prognam);
	return EXIT_FAILURE;
      }
    }
    else if (temp_string != prognam)
    {
      if (first_part_of_name)
      {
	first_part_of_name = false;
	arg_name = temp_string;
      }
      else
      {
	arg_name.append(" ");
	arg_name.append(temp_string);
      }
    }
    if (skip)
    {
      i++;
    }
  }
  
  //cout << arg_name << " blada" << endl;
  
  /*for (index = 0; index < argc; index++)
  {
    if ((strlen(argv[index]) + arg_name.length()) < arg_name.size())
    {
      if (arg_name.length())
	arg_name = " ";
      
      arg_name = argv[index];
    }
    if ((strlen(argv[index]) + strlen(arg_name_temp)) < sizeof(arg_name_temp))
    {
      if (strlen(arg_name_temp))
      {
	strcpy(arg_name_temp + strlen(arg_name_temp), " ");
      }
      strcpy(arg_name_temp + strlen(arg_name_temp), argv[index]);
    }
  }
  
  arg_name = arg_name_temp;*/
  
  if (use_stdout)
  {
    if (flags_arg & (fOnlyHabitable | fOnlyMultiHabitable | fOnlyJovianHabitable | fOnlyEarthlike))
    {
      if (count_arg > 50000)
      {
	cout << "Sorry, you cannot set the Repeat count > 50,000 even if you use a filter, due to system resource issues." << endl;
	return EXIT_FAILURE;
      }
    }
    else
    {
      if (count_arg > 1000)
      {
	cout << "Sorry, you cannot set the Repeat count > 1,000 unless you use a filter, due to system resource issues." << endl;
	return EXIT_FAILURE;
      }
    }
  }
  
  flags_arg_clone = flags_arg;
  return stargen(action, flag_char, path, url_path_arg, filename_arg, arg_name, prognam, mass_arg, luminosity_arg, seed_arg, count_arg, increment_arg, star_catalog, sys_no_arg, ratio_arg, ecc_coef_arg, inner_planet_factor_arg, flags_arg, out_format, graphic_format);
}

void initData()
{
  initRadii();
  initGases();
  initPlanets();
  initDole();
  initSolStation();
  initJimb();
  initOmegaGalaxy();
  initRingUniverse();
  initIC3094();
  initAndromeda();
  initStarTrek();
  initPlanetaryHabitabilityLaboratory();
}

void usage(string program)
{
  cout << "Usage: " << program << " [options] [system name]" << endl;
  cout << "  Options:" << endl;
  cout << "Seed values:" << endl;
  cout << "    -s#  Set random number seed [default: from time]" << endl;
  cout << "    -i#  Number to increment each random seed [default: 1]" << endl;
  cout << "    -n#  Specify number of systems [default: 1]" << endl;
  cout << "    -A#  set accretion dust density ratio_arg to # [default: 0.0]" << endl;
  cout << "    -q#  set accretion inner dust border to # [default: 0.3]" << endl;
  cout << "    -Q#  set accretion planetesimal seed eccentricity coefficient to # [default: 0.077]" << endl;    
  cout << "Preset seeds:" << endl;
  cout << "    -k   Use known planets as planitesimal seeds [from internal tables]" << endl;
  cout << "    -K   Generate only known planets [from internal tables]" << endl;
  cout << "    -x   Use the Solar System's masses/orbits" << endl;
  cout << "    -a   Use the Solar System's masses/orbits varying Earth" << endl;
  cout << "Stars:" << endl;
  cout << "  For a custom star:" << endl;
  cout << "    Please note that for a custom star, you need to specify a mass and/or a luminosity as well as a spectral type and/or a temperature. Other wise the program will not work." << endl;
  cout << "    -m#  Specify stellar mass # [fraction of Sun's mass] (optional if -y is used)" << endl;
  cout << "    -y#  Specify stellar luminosity # [fraction of Sun's luminosity] (optional if -m is used)" << endl;
  cout << "    -Y#  Specify minimum age for star (years) (optional)" << endl;
  cout << "    -MY# Specify maximum age for star (years) (optional)" << endl;
  cout << "    -b#  The temperature of the star (optional if -B is used)" << endl;
  cout << "    -B   Spectral type of the star (optional if -b is used)" << endl;
  cout << "    -CB  Make this a circumbinary system like Tatoonine in Star Wars (optional)" << endl;
  cout << "    -w#  The mass of a companion star (optional and required if the -CB option is used)" << endl;
  cout << "    -j#  The luminosity of a companion star (optional and required if the -CB option is used)" << endl;
  cout << "    -X#  The temperature of a companion star (optional and required if the -CB option is used)" << endl;
  cout << "    -N   Spectral type of the companion star (optional and required if the -CB option is used)" << endl;
  cout << "    -d#  The distance to a companion star (optional and required if the -CB option is used)" << endl;
  cout << "    -f#  The eccentricity of the orbit of the companion star (optional and required if the -CB option is used)" << endl;
  cout << "  For a predefined star:" << endl;
  cout << "    -D   Use all of Dole's " << dole.count() << " nearby stars" << endl;
  cout << "    -D#  Use Dole's system #" << endl;
  cout << "    -F   Use all " << jimb.count() << " AU systems" << endl;
  cout << "    -F#  Use AU system #" << endl;    
  cout << "    -W   Use all " << solstation.count() << " nearby stars taken from the Web" << endl;
  cout << "    -W#  Use Web system #" << endl;
  cout << "    -O   Use all " << omega_galaxy.count() << " fictious stars in the fictious Omega Galaxy" << endl;
  cout << "    -O#  Use Omega Galaxy system #" << endl;
  cout << "    -R   Use all " << ring_universe.count() << " fictious stars in the fictious Ring Universe galaxy" << endl;
  cout << "    -R#  Use Ring Universe system #" << endl;
  cout << "    -I   Use all " << ic3094.count() << " fictious stars in IC 3094 that cham generated" << endl;
  cout << "    -I#  Use IC 3094 system #" << endl; 
  cout << "    -U   Use all " << andromeda.count() << " fictious stars in the Andromeda Galaxy that cham generated" << endl;
  cout << "    -U#  Use Andromeda Galaxy system #" << endl;
  cout << "    -G   Use the " << star_trek.count() << " predefined stars from Star Trek" << endl;
  cout << "    -G#  Use Star Trek system #" << endl;
  cout << "    -PHL Use the " << phl.count() << " predefined stars listed at the Planetary Habitability Library" << endl;
  cout << "    -PHL#Use potentially habitable system #" << endl;
  cout << "    -l   List stars of selected table and exit" << endl;
  cout << "    -L   List stars of selected table as HTML and exit" << endl;
  cout << "Filters:" << endl;
  cout << "    Please note that these options are only usefull if you are making a large batch of systems and only want to save certain ones." << endl;
  cout << "    -E   Only systems with earthlike planets" << endl;
  cout << "    -H   Only systems with habitable planets" << endl;
  cout << "    -2   Only systems with 2 or more habitable planets" << endl;
  cout << "    -3   Only systems with 3 or more habitable planets" << endl;
  cout << "    -T   Only systems with habitable planets more than 2 Earth Masses in size" << endl;
  cout << "    -P   Only systems with planets habitable by the Planetary Habitability Laboratory's criteria" << endl;
  cout << "    -J   Only systems with Jovian planets in habitable region" << endl;
  cout << "    -g   Include atmospheric gases" << endl;
  cout << "    -v   List verbosities [hex values] and exit" << endl;
  cout << "    -v#  Set output verbosity [hex value]" << endl;
  cout << "    -V   Use vector graphics [SVG] images [default: GIF]" << endl;
  cout << "    -z   Do numeric size check and exit" << endl;
  cout << "    -Z   Dump tables used for gases and exit" << endl;
  cout << "File specs:" << endl;
  cout << "    --   use stdout" << endl;
  cout << "    -o   Name for the output file(s) [default: taken from star name]" << endl;
  cout << "    -p   Path for where the output file(s) are saved [default: ./html]" << endl;
  cout << "    -u   Internet URL path for/in the output file(s) [default: none]" << endl;
  cout << "Output formats: (only one is generated)" << endl;
  cout << "(default) HTML to file" << endl;
  cout << "    -c   Celestia .ssc to stdout" << endl;
  cout << "    -C   Excel .csv [dl: no thumbnail html] to file" << endl;
  cout << "    -e   Excel .csv to file" << endl;
  cout << "    -S   Vector graphics (SVG) to file" << endl;
  cout << "    -t   Text to stdout" << endl;
  cout << "    -sn# Number of decimal places for numbers" << endl;
  cout << "Other:" << endl;
  cout << "    -M   Generate moons (highly experimental and incomplete)" << endl;
  cout << "    -r   Allow planet migration after forming. (highly experimental)" << endl;
  cout << endl;
  cout << "Examples:" << endl;
  cout << "10000 systems with 1 as the seed for the first system around a custom star with moons and migrated planets and only save ones with an earthlike planet:" << endl;
  cout << program << " -m1.09 -y1.12609 -BG0V -b6215 -M -r -s1 -n10000 -E" << endl;
  cout << "10000 systems with 1 as the seed for the first system around a custom star in a circumbinary system with moons and migrated planets and only save ones with an earthlike planet:" << endl;
  cout << program << " -m1.09 -y1.12609 -BG0V -b6215 -CB -w0.75 -j0.178473 -X4493 -NK3V -d0.11146 -f0.011 -M -r -s1 -n10000 -E" << endl;
  cout << "10000 systems with 1 as the seed for the first system around a predefined star:" << endl;
  cout << program << " -W73 -M -r -s1 -n10000 -E" << endl;
  cout << "10000 systems with 1 as the seed for the first system around a custom star with a distant companion star with moons and migrated planets and only save ones with an earthlike planet:" << endl;
  cout << program << " -m1.09 -y1.12609 -BG0V -b6215 -w0.75 -d1114.6 -f0.011 -M -r -s1 -n10000 -E" << endl;
  cout << endl;
  cout << "        Web systems (-W) taken from" << endl;
  cout << "          http://www.solstation.com/stars.htm, Wikipedia, and various research papers" << endl;
  cout << "        AU systems (-F) taken from" << endl;
  cout << "          stories by C.J. Cherryh" << endl;
  cout << "        Manticore systems (-B) taken from" << endl;
  cout << "          stories by David Weber" << endl;
  cout << endl;
  cout << "        StarGen: " << stargen_revision << endl;
  cout << endl;
}
