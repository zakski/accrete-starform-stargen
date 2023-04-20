/*
 *	StarGen main API
 */

typedef	enum actions {						// Callable StarGen can:
	aGenerate,								//	- Generate randon system(s)
	aListGases,								//	- List the gas table
	aListCatalog,							//	- List the stars in a catalog
	aListCatalogAsHTML,						//  - For creating a <FORM>
	aSizeCheck,								//  - List sizes of various types
	aListVerbosity,							//  - List values of the -v option
} actions;

int stargen (actions		action,			// One of the above
			 char			flag_char,
			 char *			path,			// OS path to where to write files
			 char *			url_path_arg,	// HTML path to parent of both the
			 								//  directory named in 'path' and
			 								//  the ref directory with images
			 char *			filename_arg,	// Output file name (optional)
			 char *			sys_name_arg,	// Human readble System name (opt.)
			 
			 FILE *			sgOut,			// Main stream to write to 
			 								//	Thumbnails will be written there
			 								//  for HTML format
			 FILE *			sgErr,			// Stream to write errors to (opt.)
			 char *			prognam,		// Name of program (opt.)
			 long double	mass_arg,		// Mass of star (not used with catalog)
			 long			seed_arg,		// Random number seed
			 int			count_arg,		// Number of systems (or cats) to do
			 int			incr_arg,		// Amount to increment seed by
			 catalog *		cat_arg,		// A star catalog (see below)
			 int			sys_no_arg,		// Star within a catalog (0 = all)
			 
			 long double	ratio_arg,		// Change dust density (experimental)
			 
			 int			flags_arg,		// Options (see below)
			 int			out_format,		// Output file formats (see below)
			 int			graphic_format	// Graphic file formats (see below)
			 );

										// Values of flags_arg:
#define	fUseSolarsystem			0x0001
#define	fReuseSolarsystem		0x0002
#define	fUseKnownPlanets		0x0004
#define fNoGenerate				0x0008

#define	fDoGases				0x0010
#define	fDoMoons				0x0020

#define fOnlyHabitable			0x0100
#define fOnlyMultiHabitable		0x0200
#define fOnlyJovianHabitable	0x0400
#define fOnlyEarthlike			0x0800

										// Values of out_format
#define	ffHTML				'HTML'
#define	ffTEXT				'TEXT'
#define	ffCELESTIA			'.SSC'
#define ffCSV				'.CSV'
#define ffCSVdl				'+CSV'
#define ffSVG				'.SVG'

										// Values of graphic_format
#define	gfGIF				'.GIF'
#define gfSVG				'.SVG'

										// The two predefined star catalogs.
extern catalog	solstation;
extern catalog	dole;
extern catalog  jimb;
										// You can roll your own (see main.c)

extern planets mercury;					// For building private catalogs


extern int          flag_verbose;		// Likely to move into stargen() args.

										// Various statistics that are kept:
extern int 		    total_earthlike;
extern int 		    total_habitable;

extern long double	min_breathable_terrestrial_g;
extern long double	min_breathable_g;
extern long double	max_breathable_terrestrial_g;
extern long double	max_breathable_g;
extern long double	min_breathable_terrestrial_l;
extern long double	min_breathable_l;
extern long double	max_breathable_terrestrial_l;
extern long double	max_breathable_l;
extern long double	min_breathable_temp;
extern long double	max_breathable_temp;
extern long double	min_breathable_p;
extern long double	max_breathable_p;

										// Experimental gas model variables
										//  Likely to go away or be changed
extern ChemTable    gases[];
extern int max_gas;

										// OS-specific constants for finding
										// the default output directory and
										// other dirs:
#ifdef macintosh
#define	SUBDIR	":html:"
#define DIRSEP	":"
#else
#ifdef WIN32
#define	SUBDIR	"html\\"
#define DIRSEP	"\\"
#else
#define	SUBDIR	"html/"
#define DIRSEP	"/"
#endif
#endif

extern char *	stargen_revision;		// RCS revision of stargen.c
