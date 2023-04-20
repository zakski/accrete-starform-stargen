/*
 *	StarGen Main Routine
 *
 *	This file provides the main command-line interface to StarGen.
 *	Other platform-specific UIs can be created by duplicating its
 *	general functionality and then calling stargen(), whose API is
 *	defined in stargen.h
 *
 *	$Id: main.c,v 1.13 2008/12/30 23:15:13 brons Exp $
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

/*
 *		StarGen supports private catalogs. The two here are ones I am using
 *		for debuggery. They may go away.
 */

#define EM(x)		(x)/SUN_MASS_IN_EARTH_MASSES
#define AVE(x,y)	((x+y)/2.)

				/*  No 	Orbit	Eccen. 	Tilt	Mass		Giant?	Dust Mass	Gas */
planets sphinx3   ={ 4,	3.0,	0.046,	10.5,	EM(2.35),	FALSE,	EM(2.35),	0, 	ZEROES,0,NULL, NULL};
planets sphinx2   ={ 3,	2.25,	0.02,	10.5,	EM(2.35),	FALSE,	EM(2.35),	0, 	ZEROES,0,NULL, &sphinx3};
planets sphinx    ={ 2,	1.6,	0.02,	10.5,	EM(2.2),	FALSE,	EM(2.2),	0, 	ZEROES,0,NULL, &sphinx2};
planets manticore ={ 1,	1.115,	0.017,	23.5,	EM(1.01),	FALSE,	EM(1.01),	0, 	ZEROES,0,NULL, &sphinx};


star	manticores[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation			Name
{{1.00,		1.00,	0,		0,		0,		 &mercury,	"Sol",		 	 1, "The Solar System"},
 {1.24,		1.047,	1.0,	0.05,	79.2,	 &manticore,"Manticore A",	 1, "Manticore A"},
 {1.0,		1.00,	1.047,	0.05,	79.2,	 NULL,		"Manticore B",	 1, "Manticore B"},
};

catalog	manticore_cat	= {sizeof(manticores) / sizeof (star),	"B", &manticores};

star	helios[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation		Name
{{1.00,		1.00,	0,		0,		0,		 &mercury,	"Sol",		 1, "The Solar System"},
 {1.08,		1.0,	0.87,	0.45,	8.85,	 NULL,		"Helio A",	 1, "Helio A"},
 {0.83,		0.87,	1.0,	0.45,	8.85,	 NULL,		"Helio B",	 1, "Helio B"},
};

catalog	helio		= {sizeof(helios) / sizeof (star), "?",	&helios};

			     /*	No Orbit Eccen. Tilt   Mass    Gas Giant? Dust Mass   Gas */
planets ilaqrb={1, 0.21, 0.1,   0,     EM(600.),TRUE,     0,   EM(600.), ZEROES,0,NULL, NULL};
planets ilaqrc={2, 0.13, 0.27,  0,     EM(178.),TRUE,     0,   EM(178.), ZEROES,0,NULL, &ilaqrb};
planets ilaqrd={3, 0.021,0.22,  0,     EM(5.9), FALSE,    EM(5.9),    0, ZEROES,0,NULL, &ilaqrc};	// EM(5.9) or 7.53 +/- 0.70 Earth-masses

star	ilAqrs[] = 
// L		Mass	Mass2	Eccen.	SMAxis	 Planets	Designation	Celes	Name
{{1.00,		1.00,	0,		0,		0,		 &mercury,	"Sol",		1, "The Solar System"},
{0.0016,	0.32,	0,		0,		0,		 &ilaqrd,	"IL Aqr",	1, "IL Aquarii/Gliese 876"}	// 15.2
};

catalog	ilAqr_cat		= {sizeof(ilAqrs) / sizeof (star),	"G", &ilAqrs};
void usage(char*);

void usage(char *prognam)
{
	fprintf(stderr, "Usage: %s [options] [system name]\n", prognam);
	fprintf(stderr, "  Options:\n"
					"    -s#  Set random number seed\n"
					"    -m#  Specify stellar mass\n"
					"    -n#  Specify number of systems\n"
					"    -i#  Number to increment each seed by\n"
					"    -x   Use the Solar System's masses/orbits\n"
					"    -d   Use Dole's %d nearby stars\n"
					"    -D#  Use Dole's system #n\n"
					"    -w   Use %d nearby stars taken from the Web\n"
					"    -W#  Use Web system #n\n"
					"    -p   Specify the path for the output file\n"
					"    -o   Output file name\n"
					"    -t   Text-only output\n"
					"    -v#  Set verbosity (hex value)\n"
					"    -l   List nearby stars and exit\n"
					"    -H   Output only systems with habitable planets\n"
					"    -2   Only systems with 2 or more habitable planets\n"
					"    -E   Only systems with earthlike planets\n"
					"\n"
					"  Experimental options (may go away):\n"
					"    -c   Output Celestia .ssc file on stdout\n"
					"    -e   Output Excel .csv file\n"
					"    -V   Create vector graphics (SVG) system image\n"
					"    -k   Incorporate known planets (incomplete)\n"
					"          (use only orbital data at present)\n"
					"          Without -k, -c skips systems with known planets.\n"
					"    -g   Show atmospheric gases\n"
					"    -Z   Dump tables used for gases and exit\n"
					"    -M   Do moons (highly experimental)\n"
					"\n"
					"        Nearest stars taken from:\n"
					"          http://www.solstation.com/stars.htm\n"
					"\n"
					"        StarGen: %s\n"
					"\n",
					dole.count - 1,
					solstation.count - 1,
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
	long		seed_arg				= 0;
	int  		count_arg 				= 1;
	int			increment_arg			= 1;
	catalog	*	catalog					= NULL;
	int 		sys_no_arg				= 0;

	long double	ratio_arg				= 0.0;

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
			case 'n':	// number of systems
				count_arg = atoi(&(*++c));
				skip = TRUE;
				break;
			case 'i':	// number of systems
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
			case 'f':
				catalog = &jimb;
				flag_char = toupper(*c);
				break;
			case 'd':
				catalog = &dole;
				flag_char = toupper(*c);
				break;
			case 'w':
				catalog = &solstation;
				flag_char = toupper(*c);
				break;
			case 'b':						// experimental catal (Manticore, Helios etc.)
				catalog = &manticore_cat;
				flag_char = toupper(*c);
				break;
			case 'B':
				catalog = &manticore_cat;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				skip = TRUE;
				flags_arg |= fNoGenerate;
				sphinx.greenhouse_effect = TRUE;
				break;
			case 'G':
				catalog = &ilAqr_cat;
				flag_char = toupper(*c);
				++c;
				if ((toupper(*c) != 'X') && (*c != '\0'))
					sys_no_arg = atoi(c) + 1;
				skip = TRUE;
				flags_arg |= fNoGenerate;
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
			 seed_arg,
			 count_arg,
			 increment_arg,
			 catalog,
			 sys_no_arg,
			 
			 ratio_arg,
			 
			 flags_arg,
			 out_format,
			 graphic_format
			 );

	return(0);
}
