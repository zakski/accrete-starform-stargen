/*
 *	StarGen Main Routine
 *
 *	This file provides the main command-line interface to StarGen.
 *	Other platform-specific UIs can be created by duplicating its
 *	general functionality and then calling stargen(), whose API is
 *	defined in stargen.h
 *
 *	$Id: main.c,v 1.14 2009/01/15 23:15:55 brons Exp $
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>
#include	<time.h>
#include	<ctype.h>

#include	"Dumas.h"

#ifdef THINK_C
#define macintosh 1
#endif

#ifdef macintosh
#include	<console.h>
#include	<unix.h>
#else
#include	<sys/types.h>
#endif

#ifdef MSDOS
#include	<stddef.h>
#include	<stdlib.h>
#include	<float.h>
#endif

#ifdef WIN32
#pragma warning (disable: 4048) // Hush compiler - don't complain about storing specific arrays in generic pointers
#endif

#include	"const.h"
#include	"structs.h"
#include	"stargen.h"
#include 	"ring_universe.h"
#include	"ic3094.h"
#include	"ba_gal.h"
#include	"omega_galaxy.h"

/*
 *		StarGen supports private catalogs. The two here are ones I am using
 *		for debuggery. They may go away.
 */

#define EM(x)		(x)/SUN_MASS_IN_EARTH_MASSES
#define AVE(x,y)	((x+y)/2.)

 // light minutes in 1 AU (Honorverse distances are in LM)
#define lmpau  8.31675359
// mass = g x r x r // HV values are g and D

		/*  No 	Orbit	Eccen. 	Tilt	Mass		Giant?	Dust Mass	Gas */
//planets sphinx3   ={ 4,	3.0,	0.046,	10.5,	EM(2.35),	FALSE,	EM(2.35),	0, 	ZEROES,0,NULL, NULL};
//planets sphinx2   ={ 3,	2.25,	0.02,	10.5,	EM(2.35),	FALSE,	EM(2.35),	0, 	ZEROES,0,NULL, &sphinx3};
///planets sphinx    ={ 2,	1.6,	0.02,	10.5,	EM(2.2),	FALSE,	EM(2.2),	0, 	ZEROES,0,NULL, &sphinx2};
//planets manticore ={ 1,	1.115,	0.017,	23.5,	EM(1.01),	FALSE,	EM(1.01),	0, 	ZEROES,0,NULL, &sphinx};

// mass = g x r x r // HV values are g and D
// manticore A system
                  /*  No 	Orbit	Eccen. 	Tilt	Mass		Giant?	Dust Mass	Gas */
#define mau7  (156.96/lmpau)
#define mm7  38.72 // (3*(38.72)*(38.72))
planets wyvern    =  { 7,       mau7,	0.02,	10.5,	EM(mm7),	TRUE,	0,	0, 	ZEROES,0,NULL, NULL};

#define mau6  (79.35/lmpau)
#define mm6  423.19 //  (3*(423.19)*(423.19))
planets roc    =  { 6,       mau6,	0.02,	10.5,	EM(mm6),	TRUE,	0,	0, 	ZEROES,0,NULL, &wyvern};

#define mau5  (40.55/lmpau)
#define mm5  293.66 // (3*(293.66)*(293.66))
planets draco    =  { 5,       mau5,	0.02,	10.5,	EM(mm5),	TRUE,	0,	0, 	ZEROES,0,NULL, &roc};

#define mau4  (21.25/lmpau)
#define mm4  (1.30*(1.30)*(1.30))
planets sphinx    =  { 4,       mau4,	0.02,	10.5,	EM(mm4),	FALSE,	0,	0, 	ZEROES,0,NULL, &draco};

#define mau3  (11.45/lmpau)
#define mm3  (1.01*(1.22)*(1.22))
planets manticore =  { 3,       mau3,	0.017,	23.5,	EM(mm3),	FALSE,	0,	0, 	ZEROES,0,NULL, &sphinx};

#define mau2  (6.6/lmpau)
#define mm2  (0.75*(0.75)*(0.75))
planets phoenix =    { 2,       mau2,	0.002,	23.5,	EM(mm2),	FALSE,	0,	0, 	ZEROES,0,NULL, &manticore};

#define mau1  (1.75/lmpau)
#define mm1  (0.25*(0.41)*(0.41))
planets salamander = { 1,       mau1,	0.0,	0.0,    EM(mm1),	FALSE,	0,	0, 	ZEROES,0,NULL, &phoenix};


// manticore B system
#define mau210  (258.24/lmpau)
#define mm210 125.62// (2*(125.62)*(125.62))
planets Fenris = { 10,       mau210,	0.0,	0.0,    EM(mm210),	TRUE,	0,	0, 	ZEROES,0,NULL, NULL};

#define mau29  (116.17/lmpau)
#define mm29  (0.00001*(0.00001)*(0.00001))
planets GorgonBelt = { 9,       mau29,	0.0,	0.0,    EM(mm29),	FALSE,	0,	0, 	ZEROES,0,NULL, &Fenris};

#define mau28  (83.61/lmpau)
#define mm28 695.26// (2*(695.26)*(695.26))
planets Titan = { 8,       mau28,	0.0,	0.0,    EM(mm28),	TRUE,	0,	0, 	ZEROES,0,NULL, &GorgonBelt};

#define mau27  (42.33/lmpau)
#define mm27  (0.00001*(0.00001)*(0.00001))
planets NibelungBelt = { 7,       mau27,	0.0,	0.0,    EM(mm27),	FALSE,	0,	0, 	ZEROES,0,NULL, &Titan};

#define mau26  (21.69/lmpau)
#define mm26  (0.00001*(0.00001)*(0.00001))
planets UnicornBelt = { 6,       mau26,	0.0,	0.0,    EM(mm26),	FALSE,	0,	0, 	ZEROES,0,NULL, &NibelungBelt};

#define mau25  (11.37/lmpau)
#define mm25  (1.00*(1.01)*(1.01))
planets gryphon = { 5,       mau25,	0.0,	0.0,    EM(mm25),	FALSE,	0,	0, 	ZEROES,0,NULL, &UnicornBelt};

#define mau24  (6.21/lmpau)
#define mm24  (1.19*(0.97)*(0.97))
planets damocles = { 4,       mau24,	0.0,	0.0,    EM(mm24),	FALSE,	0,	0, 	ZEROES,0,NULL, &gryphon};

#define mau23  (3.63/lmpau)
#define mm23  (0.96*(0.96)*(0.96))
planets aphrodite = { 3,       mau23,	0.0,	0.0,    EM(mm23),	FALSE,	0,	0, 	ZEROES,0,NULL, &damocles};

#define mau22  (2.34/lmpau)
#define mm22   (0.76*(0.81)*(0.81))
planets gorgon = { 2,       mau22,	0.0,	0.0,    EM(mm22),	FALSE,	0,	0, 	ZEROES,0,NULL, &aphrodite};

#define mau21  (1.05/lmpau)
#define mm21  (0.85*(0.72)*(0.72))
planets erinye = { 1,       mau21,	0.0,	0.0,    EM(mm21),	FALSE,	0,	0, 	ZEROES,0,NULL, &gorgon};




star	manticores[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation			Name
  {
    {1.6374,   	1.12,	0.92,	0.119,	44.84,	 0,0,&salamander,"Manticore A",	 1, "Manticore A"},
    {0.6842,   	0.92,	1.12,	0.119,	54.65,	 0,0,&erinye,  	"Manticore B",	 1, "Manticore B"},
  };

catalog	manticore_cat	= {sizeof(manticores) / sizeof (star),	"B", &manticores};

star	helios[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation		Name
  {{1.00,		1.00,	0,		0,		0,		 0,0,&mercury,	"Sol",		 1, "The Solar System"},
   {1.08,		1.0,	0.87,	0.45,	8.85,	 0,0,NULL,		"Helio A",	 1, "Helio A"},
   {0.83,		0.87,	1.0,	0.45,	8.85,	 0,0,NULL,		"Helio B",	 1, "Helio B"}
};

catalog	helio		= {sizeof(helios) / sizeof (star), "?",	&helios};

			     /*	No Orbit Eccen. Tilt   Mass    Gas Giant? Dust Mass   Gas */
planets ilaqrb={1, 0.21, 0.1,   0,     EM(600.),TRUE,     0,   EM(600.), ZEROES,0,NULL, NULL};
planets ilaqrc={2, 0.13, 0.27,  0,     EM(178.),TRUE,     0,   EM(178.), ZEROES,0,NULL, &ilaqrb};
planets ilaqrd={3, 0.021,0.22,  0,     EM(5.9), FALSE,    EM(5.9),    0, ZEROES,0,NULL, &ilaqrc};	// EM(5.9) or 7.53 +/- 0.70 Earth-masses

star	ilAqrs[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation	Celes	Name
  {
   {0.0016,	0.32,	0,     	0,	0,	 0,0,&ilaqrd,	"IL Aqr",	1, "IL Aquarii/Gliese 876"}	// 15.2
};

catalog	ilAqr_cat		= {sizeof(ilAqrs) / sizeof (star),	"G", &ilAqrs};


void usage(char*);

void usage(char *prognam)
{
	fprintf(stderr, "Usage: %s [options] [system name]\n", prognam);
	fprintf(stderr, 
		"  Options:\n"
		"Seed values:\n"
		"    -s#  Set random number seed [default: from time]\n"
		"    -i#  Number to increment each random seed [default: 1]\n"
		"    -n#  Specify number of systems [default: 1]\n"
		"    -A#  set accretion dust density ratio_arg to # [default: 0.0]\n"    
		"    -q#  set accretion inner dust border to # [default: 0.3]\n"    
		"    -Q#  set accretion planetesimal seed eccentricity coefficient to # [default: 0.077]\n"    
		"Preset seeds:\n"
		"    -k   Use known planets as planitesimal seeds [from internal tables]\n"
		"    -K   Generate only known planets [from internal tables]\n"
		"      -x   Use the Solar System's masses/orbits\n"
		"      -a   Use the Solar System's masses/orbits varying Earth\n"
		"Stars:\n"
		"    -m#  Specify stellar mass # [fraction of Sun's mass]\n"
		"    -y#  Specify stellar luminosity # [fraction of Sun's luminosity]\n"
		"or select an internal table:\n"
		"    -B   Use all %d Manticore systems & planets\n"    
		"    -B#  Use Manticore system #\n"    
 		"    -D   Use all of Dole's %d nearby stars\n"
		"    -D#  Use Dole's system #\n"
		"    -F   Use all %d AU systems\n"    
		"    -F#  Use AU system #\n"    
		"    -G   Use all %d IL Aqr systems & planets\n"
		"    -G#  Use IL Aqr system #\n"
		"    -W   Use all %d nearby stars taken from the Web\n"
		"    -W#  Use Web system #\n"
		"    -R   Use all %d stars in the Ring Universe Galaxy\n"
		"    -R#  Use Ring Universe system #\n"
		"    -I   Use all %d fictious stars in IC 3094\n"
		"    -I#  Use IC 3094 system #\n"
		"    -N   Use all %d fictious stars in the fictious galaxy BA GAL 1\n"
		"    -N#  Use BA GAL 1 system #\n"
		"    -U   Use all %d fictious stars in the fictious Omega Galaxy\n"
		"    -U#  Use Omega Galaxy system #\n"
		"    -l   List stars of selected table and exit\n"
		"    -L   List stars of selected table as HTML and exit\n"
		"Filters:\n"
		"    -E   Only systems with earthlike planets\n"
		"    -H   Only systems with habitable planets\n"
		"    -2   Only systems with 2 or more habitable planets\n"
		"    -3   Only systems with 3 or more habitable planets\n"
		"    -J   Only systems with Jovian planets in habitable region\n"
		"    -g   Include atmospheric gases\n"
		"    -v   List verbosities [hex values] and exit\n"
		"    -v#  Set verbosity [hex value]\n"
		"    -V   Use vector graphics [SVG] images [default: GIF]\n"
		"    -z   Do numeric size check and exit\n"
		"    -Z   Dump tables used for gases and exit\n"
		"File specs:\n"
		"    --   use stdout\n"
		"    -o   Name for the output file(s) [default: taken from star name]\n"
		"    -p   Path for the output file(s) [default: ./html]\n"
		"    -u   Internet URL path for/in the output file(s) [default: none]\n"
		"Output formats: (only one is generated)\n"
		"(default) HTML to file\n"
		"    -c   Celestia .ssc to stdout\n"
		"    -C   Excel .csv [dl: no thumbnail html] to file\n"
		"    -e   Excel .csv to file\n"
		"    -S   Vector graphics (SVG) to file\n"
		"    -t   Text to stdout\n"
		"    -P   Moon creation script to stdout\n"
		"Other:\n"
		"    -M   Generate moons (highly experimental and incomplete)\n"
		"\n"
		"        Web systems (-W) taken from\n"
		"          http://www.solstation.com/stars.htm\n"
		"        AU systems (-F) taken from\n"
		"          stories by C.J. Cherryh\n"
		"        Manticore systems (-B) taken from\n"
		"          stories by David Weber\n"
		"\n"
		"        StarGen: %s\n"
		"\n",
		manticore_cat.count,
		dole.count ,
		jimb.count ,
		ilAqr_cat.count ,
		solstation.count ,
		ring_universe.count,
		ic3094.count,
		ba_gal.count,
		omega_galaxy.count,
		stargen_revision);
}

int main (int argc, char *argv[])
{
	actions		action					= aGenerate;
	char		flag_char				= '?';
	char		path[300]				= SUBDIR;
	char 		url_path_arg[300]		= "";
	char		filename_arg[300]		= "";
	char 		arg_name [80] 			= "";

	int			use_stdout				= FALSE;
	char *		prognam;
	long double	mass_arg				= 0.0;
	long double	luminosity_arg				= 0.0;
	long		seed_arg				= 0;
	int  		count_arg 				= 1;
	int			increment_arg			= 1;
	catalog	*	catalog					= NULL;
	int 		sys_no_arg				= 0;

	long double	ratio_arg				= 0.0;
	long double	ecc_coef_arg				= 0.077; //seb: dole value
	long double	inner_planet_factor_arg			= 0.3; //seb: dole value

	int			flags_arg				= 0;
	int			out_format				= ffHTML;
	int			graphic_format			= gfGIF;
	
	char 		*c						= NULL;
	int  		skip					= FALSE;
	int  		index					= 0;

#ifdef macintosh
	_ftype 		= 'TEXT';
	_fcreator 	= 'R*ch';
	argc = ccommand (&argv);
#endif
	
	prognam = argv[0];
	
	if ((c = strrchr(prognam, DIRSEP[0])) != NULL)
		prognam = c + 1;
	
	if (argc <= 1)
	{
		usage(prognam);
		return(1);
	}
	
	while (--argc > 0 && (*++argv)[0] == '-') {
		for (c = argv[0]+1, skip=FALSE; 
			 (*c != '\0') && (!(skip)); 
			 c++)
			switch (*c) 
			{
			case '-':
				use_stdout = TRUE;
				break;
			case 's':	// set random seed
				seed_arg = atol(&(*++c));
				skip = TRUE;
				break;
			case 'm':	// set mass of star
			{
				double	m;	// gnu C doesn't like to scanf long doubles
				sscanf (++c, "%lf", &m);
				mass_arg = m;
				
				skip = TRUE;
				break;
			}
			case 'y':	// set luminosity of star
			{
				double	l;	// gnu C doesn't like to scanf long doubles
				sscanf (++c, "%lf", &l);
				luminosity_arg = l;
				
				skip = TRUE;
				break;
			}
			case 'n':	// number of systems
				count_arg = atoi(&(*++c));
				skip = TRUE;
				break;
			case 'i':	// step random number seed by this for next system
				increment_arg = atoi(&(*++c));
				skip = TRUE;
				break;
/*
			case 'T':	// Use the solar system with Titan, not Saturn
				jupiter.next_planet = &titan2;
 */
			case 'x':	// Use the solar system
				flag_char = *c;
				flags_arg |= fUseSolarsystem;
				if (mass_arg == 0.0)
					mass_arg = 1.0;
				break;
			case 'a':	// Use the solar system varying earth
				flag_char = *c;
				flags_arg |= fReuseSolarsystem;
				break;
			case 'D':
				catalog = &dole;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				skip = TRUE;
				break;
			case 'W':
				catalog = &solstation;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				skip = TRUE;
				break;
			case 'F':
				catalog = &jimb;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				skip = TRUE;
				break;
				/* seb: make options available -- lower case options subsumed by upper case versions
				 * case 'f':
				 * catalog = &jimb;
				 * flag_char = toupper(*c);
				 * break;
				 * case 'd':
				 * catalog = &dole;
				 * flag_char = toupper(*c);
				 * break;
				 *  case 'w':
				 * catalog = &solstation;
				 * flag_char = toupper(*c);
				 * break;
				 * case 'b':
				 * // experimental catal (Manticore, Helios etc.)
				 * catalog = &manticore_cat;
				 * flag_char = toupper(*c);
				 * break;
				 */
			case 'B':
				catalog = &manticore_cat;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb: option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				sphinx.greenhouse_effect = TRUE;
				break;
			case 'G':
				catalog = &ilAqr_cat;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				break;
			case 'R':
				catalog = &ring_universe;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				break;
			case 'I':
				catalog = &ic3094;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				break;
			case 'N':
				catalog = &ba_gal;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				break;
			case 'U':
				catalog = &omega_galaxy;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				//seb option -K else flags_arg |= fNoGenerate;
				skip = TRUE;
				break;
			case 'o':
				if (*++c == '\0')
					if (argc > 1)
					{
						--argc;
						c = (++argv)[0];
					}
				
				if (*c != '\0')
					strcpy(filename_arg, c);

				skip = TRUE;
				break;
			case 't':	// display text
				out_format = ffTEXT;
				break;
			case 'e':
				out_format = ffCSV;
				break;
			case 'C':
				out_format = ffCSVdl;
				break;
			case 'c':
				out_format = ffCELESTIA;
				break;
			case 'P':
				out_format = ffMOONGEN;
				break;
			case 'V':
				graphic_format = gfSVG;
				break;
			case 'S':
				graphic_format = gfSVG;
				out_format = ffSVG;
				break;
			case 'k':
				flags_arg |= fUseKnownPlanets;
				break;
			case 'K': //seb: make force of listed planets optional
				flags_arg |= fUseKnownPlanets | fNoGenerate;
				break;
			case 'p':
				if (*++c == '\0')
					if (argc > 1)
					{
						--argc;
						c = (++argv)[0];
					}
				
				if (*c != '\0')
					strcpy(path, c);
				
				if (strcmp(path + strlen(path) - strlen(DIRSEP), DIRSEP) != 0)
					strncat (path, DIRSEP, 80-strlen(path));
					
				skip = TRUE;
				break;
			case 'u':
				if (*++c == '\0')
					if (argc > 1)
					{
						--argc;
						c = (++argv)[0];
					}
				
				if (*c != '\0')
					strcpy(url_path_arg, c);
				
				if (strcmp(url_path_arg + strlen(url_path_arg) - strlen("/"), "/") != 0)
					strncat (url_path_arg, "/", 80-strlen(url_path_arg));
				
				skip = TRUE;
				break;
			case 'g':
				flags_arg |= fDoGases;
				break;
			case 'v':	// verbosity
				if (isdigit(*(c+1)))
				{
					sscanf (++c, "%x", &flag_verbose);
					skip = TRUE;
					if (flag_verbose & 0x0001)
						flags_arg |= fDoGases;
				}
				else
					action = aListVerbosity;
				break;
			case 'l':
				action = aListCatalog;
				break;
			case 'L':
				action = aListCatalogAsHTML;
				break;
			case 'z':
				action = aSizeCheck;
				break;
			case 'Z':
				action = aListGases;
				break;
			case 'M':
				flags_arg |= fDoMoons;
				break;
			case 'H':
				flags_arg |= fDoGases | fOnlyHabitable;
				break;
			case '2':
				flags_arg |= fDoGases | fOnlyMultiHabitable;
				break;
			case '3':
				flags_arg |= fDoGases | fOnlyThreeHabitable;
				break;
			case 'J':
				flags_arg |= fDoGases | fOnlyJovianHabitable;
				break;
			case 'E':
				flags_arg |= fDoGases | fOnlyEarthlike;
				break;
			case 'A':
			{
				double ratio;
				
				sscanf (++c, "%lf", &ratio);
				skip = TRUE;
				
				if (ratio > 0.0)
					ratio_arg = ratio;
				else 
				  {
				    fprintf (stderr, "Accrete dust density coefficient -A (%f) must be > 0.0\n", ratio);
				    return (1);
				  }
				break;
			}
			
			case 'Q': //seb: eccentricity coefficient for accrete
			{
				double ecc;
				
				sscanf (++c, "%lf", &ecc);
				skip = TRUE;
				
				if (ecc > 0.0)
					ecc_coef_arg = ecc;
				else 
				  {
				    fprintf (stderr, "Accrete eccentricity coeffecient -Q (%f) must be > 0.0\n", ecc);
				    return (1);
				  }
				break;
			}
			case 'q': //seb: inner dust limit for accrete
			{
				double lim;
				
				sscanf (++c, "%lf", &lim);
				skip = TRUE;
				
				if (lim > 0.0)
					inner_planet_factor_arg = lim;
				else 
				  {
				    fprintf (stderr, "Accrete inner dust boundary -q (%f) must be > 0.0\n", lim);
				    return (1);
				  }
				break;
			}
			
			default:
				fprintf (stderr, "Unknown option: %s\n", c);
			case '?':
			case 'h':
				usage(prognam);
				return (1);
			}
	}
	
	for (index = 0; index < argc; index++) {
		if ((strlen(argv[index]) + strlen(arg_name)) < sizeof(arg_name))
		{
			if (strlen(arg_name))
				strcpy(arg_name+strlen(arg_name), " ");
			
			strcpy(arg_name+strlen(arg_name), argv[index]);
		}
	}
	
	if (use_stdout)
	{
		if (flags_arg & (fOnlyHabitable
					   | fOnlyMultiHabitable
					   | fOnlyJovianHabitable
					   | fOnlyEarthlike))
		{
			if (count_arg > 50000)
			{
				printf ("Sorry, you cannot set the Repeat count > 50,000 even "
						 "if you use a filter, due to system resource issues.");
				return (1);
			}
		}
		else
		{
			if (count_arg > 1000)
			{
				printf ("Sorry, you cannot set the Repeat count > 1,000 unless "
						 "you use a filter, due to system resource issues.");
				return (1);
			}
		}
	}
	
	stargen (action,
			 flag_char,
			 path,
			 url_path_arg,
			 filename_arg,
			 arg_name,
			 
			 use_stdout ? stdout : NULL,
			 stderr,
			 prognam,
			 mass_arg,
			 luminosity_arg,
			 seed_arg,
			 count_arg,
			 increment_arg,
			 catalog,
			 sys_no_arg,
			 
			 ratio_arg,
			 ecc_coef_arg,
			 inner_planet_factor_arg,
			 
			 flags_arg,
			 out_format,
			 graphic_format
			 );

	return(0);
}
