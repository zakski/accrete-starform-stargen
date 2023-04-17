#include	<stdio.h>
#include	<string.h>
#include	<math.h>

#ifdef THINK_C
#define macintosh 1
#endif

#ifdef macintosh
#include	<console.h>
#include	<unix.h>
#endif

#ifdef MSDOS
#include	<stddef.h>
#include	<stdlib.h>
#include	<string.h>
#include	<float.h>
#endif

#include	"structs.h"
#include	"const.h"
#include	"display.h"
#include	"enviro.h"
#include	"stargen.h"

#define	MAX_EXP_DIGS	3
#define	MAX_MAN_DIGS	20

char default_url_path[] = "../";
char *url_path = default_url_path;

char *engineer_notation(long double d, 
						int 		p)
{
	static char mansign;
	static char expsign;
	static char output[1+MAX_MAN_DIGS+1+1+MAX_EXP_DIGS+1];
	long double mantissa;
	int 		exponent;

	mansign = '+';
	expsign = '+';
	if (p > MAX_MAN_DIGS)
		p = MAX_MAN_DIGS;
	if (p < 3)
		p = 3;
	--p;
	if (d < 0.0)
	{
		mansign = '-';
		d = -d;
	}
	if (d == 0.0)
	{
		exponent = 0;
		mantissa = 0;
	}
	else
	{
		exponent = (int)log10(d);
		if (exponent == 0 && d < 1.0)	/* log10 sometimes lies */
		{
			--exponent;
			--p;
		}
		if (exponent < 0)
		{
			expsign = '-';
			--exponent;
		}
		mantissa = d / pow(10.0, (long double) exponent);
		if (exponent < 0)
			exponent = -exponent;
		while ((exponent % 3) != 0)
		{
			mantissa *= 10.0;
			p--;
			if (expsign == '-')
				++exponent;
			else
				--exponent;
		}
	}
	sprintf(output, "%c%*.*Lfe%c%*.*d", mansign, p, p, mantissa,
		expsign, MAX_EXP_DIGS, MAX_EXP_DIGS, exponent);
	return (output);
}

void text_describe_system(planet_pointer innermost_planet, int do_gases, long int seed)
{
	planet_pointer 	planet;
	primary*		sun = innermost_planet->primary;
	int 			counter; 
	
	printf("Stargen - V%s; seed=%ld\n", stargen_revision, seed);
	printf("                          SYSTEM  CHARACTERISTICS\n");
	printf("Stellar mass: %4.2Lf solar masses\n", sun->mass);
	printf("Stellar luminosity: %4.2Lf\n",sun->luminosity);
	printf("Age: %5.3Lf billion years	(%5.3Lf billion left on main sequence)\n",
		   (sun->age /1.0E9),(sun->life - sun->age) / 1.0E9);
	printf("Habitable ecosphere radius: %3.3Lf AU\n",sun->r_ecosphere);
	printf("\n");
	printf("Planets present at:\n");
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
	   printf("%d\t%7.3Lf AU\t%8.3Lf EM\t%c\n", 
			  counter, planet->a,planet->mass * SUN_MASS_IN_EARTH_MASSES,
			  planet->gas_giant ? 'O' :
			  ((planet->greenhouse_effect) && (planet->surf_pressure > 0.0)) ? '+' :
			  ((planet->hydrosphere > .05) && (planet->hydrosphere < .95)) ? '*' :
			  ((planet->mass * SUN_MASS_IN_EARTH_MASSES) > .1) ? 'o' : '.');
	}
	printf("\n\n\n");
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		printf("Planet %d",counter);
		if (planet->gas_giant)
			printf("\t*gas giant*\n");
		else printf("\n");
		if ((int)planet->day == (int)(planet->orb_period * 24.0))
			printf("Planet is tidally locked with one face to star.\n");
		if (planet->resonant_period)
			printf("Planet's rotation is in a resonant spin lock with the star\n");
		printf("   Distance from primary star:\t%5.3Lf\tAU\n",planet->a);
		printf("   Mass:\t\t\t%5.3Lf\tEarth masses\n",planet->mass * SUN_MASS_IN_EARTH_MASSES);
		if (!(planet->gas_giant))
		{
			printf("   Surface gravity:\t\t%4.2Lf\tEarth gees\n",planet->surf_grav);
			printf("   Surface pressure:\t\t%5.3Lf\tEarth atmospheres",(planet->surf_pressure / 1000.0));
			if ((planet->greenhouse_effect) && (planet->surf_pressure > 0.0))
				printf("\tGREENHOUSE EFFECT\n");
			else 
				printf("\n");
			printf("   Surface temperature:\t\t%4.2Lf\tdegrees Celcius\n",
					(planet->surf_temp - FREEZING_POINT_OF_WATER));
		}
		printf("   Equatorial radius:\t\t%3.1Lf\tKm\n",planet->radius);
		printf("   Density:\t\t\t%5.3Lf\tgrams/cc\n",planet->density);
		printf("   Eccentricity of orbit:\t%5.3Lf\n",planet->e);
		printf("   Escape Velocity:\t\t%4.2Lf\tKm/sec\n",planet->esc_velocity / CM_PER_KM);
		printf("   Molecular weight retained:\t%4.2Lf and above\n",planet->molec_weight);
		printf("   Surface acceleration:\t%4.2Lf\tcm/sec2\n",planet->surf_accel);
		printf("   Axial tilt:\t\t\t%2.0Lf\tdegrees\n",planet->axial_tilt);
		printf("   Planetary albedo:\t\t%5.3Lf\n",planet->albedo);
		printf("   Length of year:\t\t%4.2Lf\tdays\n",planet->orb_period);
		printf("   Length of day:\t\t%4.2Lf\thours\n",planet->day);
		if (!(planet->gas_giant))
		{
			printf("   Boiling point of water:\t%3.1Lf\tdegrees Celcius\n",(planet->boil_point - FREEZING_POINT_OF_WATER));
			printf("   Hydrosphere percentage:\t%4.2Lf\n",(planet->hydrosphere * 100.0));
			printf("   Cloud cover percentage:\t%4.2Lf\n",(planet->cloud_cover * 100));
			printf("   Ice cover percentage:\t%4.2Lf\n",(planet->ice_cover * 100));
		}
		printf("\n\n");

		if (do_gases
		 && (planet->type != tGasGiant) 
		 && (planet->type != tSubGasGiant) 
		 && (planet->type != tSubSubGasGiant))
		{
			//gases?
		}
	}
}

char *type_string (planet_type type)
{
	char *typeString = "Unknown";
	
	switch (type)
	{
		case tUnknown:			typeString = "Unknown";		break;
		case tRock:				typeString = "Rock";		break;
		case tVenusian:			typeString = "Venusian";	break;
		case tTerrestrial:		typeString = "Terrestrial";	break;
		case tSubSubGasGiant:	typeString = "GasDwarf";	break;
		case tSubGasGiant:		typeString = "Sub-Jovian";	break;
		case tGasGiant:			typeString = "Jovian";		break;
		case tMartian:			typeString = "Martian";		break;
		case tWater:			typeString = "Water";		break;
		case tIce:				typeString = "Ice";			break;
		case tAsteroids: 		typeString = "Asteroids";	break;
		case t1Face:			typeString = "1Face";		break;
	}
	return typeString;
}

char *texture_name (planet_type type)
{
	char *typeString = "Unknown";
	
	switch (type)
	{
		case tUnknown:			typeString = "x.jpg";			break;
		case tRock:				typeString = "callisto.jpg";	break;
		case tVenusian:			typeString = "venuslike.jpg";	break;
		case tTerrestrial:		typeString = "Earthlike.png";	break;
		case tSubSubGasGiant:	typeString = "x.jpg";			break;
		case tSubGasGiant:		typeString = "gasgiant.jpg";	break;
		case tGasGiant:			typeString = "jupiterlike.jpg";	break;
		case tMartian:			typeString = "mars.jpg";		break;
		case tWater:			typeString = "x.jpg";			break;
		case tIce:				typeString = "pluto.jpg";		break;
		case tAsteroids: 		typeString = "asteroid.jpg";	break;
		case t1Face:			typeString = "x.jpg";			break;
	}
	return typeString;
}

/*
 *	HTML document headers
 */

FILE *open_html_file (char *system_name, 
					  long	seed,
					  char *path,
					  char *file_name, 
					  char *prognam,
					  FILE *file_arg)
{
	FILE *file;
	char file_spec[120];
	int  noname = ((NULL == system_name) || (0 == system_name[0]));
	
	if (file_arg != NULL)
	{
		file = file_arg;
	}
	else
	{
		sprintf (&file_spec[0], "%s%s", path, file_name);
	
#ifdef macintosh
		_fcreator ='MSIE';
		_ftype = 'TEXT';
#endif
		file = fopen (file_spec, "w");
#ifdef macintosh
		_fcreator ='R*ch';
		_ftype = 'TEXT';
#endif
	}

	if (NULL != file)
	{
		fprintf (file,
		        "<!DOCTYPE HTML PUBLIC %c-//W3C//DTD HTML 4.01 Transitional//EN%c\n"
		        "        %chttp://www.w3.org/TR/1999/REC-html401-19991224/loose.dtd%c>\n"
				"<HTML>\n<HEAD>\n"
				"\t<TITLE>System %ld%s%s</TITLE>\n"
				"\t<META NAME='generator' CONTENT='%s - %s'>\n"
				"</HEAD>\n<BODY BGCOLOR='" BGCOLOR "' TEXT='" TXCOLOR "' "
							   "LINK='" LINKCOLOR "' VLINK='" TXCOLOR "' ALINK='" ALINKCOLOR "'>\n\n\n", 
				'"','"','"','"',
				seed,
				noname ? "" : " - ",
				noname ? "" : system_name,
				prognam, stargen_revision
				);
	}
	
	return file;
}

void close_html_file(file)
FILE *file;
{

	fprintf (file,
			"<P>\n\n"
			"<CENTER>\n"
			"This page was created by <A HREF='" STARGEN_URL "'>StarGen</A>.\n"
			"</CENTER>\n"
			"<P>\n\n"
	        "</BODY>\n</HTML>\n");
	fflush (file);
	fclose (file);
}

#define LPRINT(x)	{fprintf (file, "%s%s", first ? "" : ", ", x); first = FALSE;}

void print_description(FILE*			file,
					   char*			opening,
					   planet_pointer 	planet,
					   char*			closing)
{
	if ((planet->type == tGasGiant)
	 || (planet->type == tSubGasGiant)
	 || (planet->type == tSubSubGasGiant))
	{
		// Nothing, for now.
	}
	else
	{
		int			first      = TRUE;
		long double	rel_temp   = (planet->surf_temp -  FREEZING_POINT_OF_WATER) - 
								 EARTH_AVERAGE_CELSIUS;
		long double	seas       = (planet->hydrosphere * 100.0);
		long double	clouds     = (planet->cloud_cover * 100.0);
		long double	atmosphere = (planet->surf_pressure / 
								 EARTH_SURF_PRES_IN_MILLIBARS);
		long double	ice        = (planet->ice_cover * 100.0);
		long double	gravity    = planet->surf_grav;
		
		fprintf (file, opening);
		
		if (gravity < .8)				LPRINT ("Low-G")	/* .8 gees */
		else if (gravity > 1.2)			LPRINT ("High-G")
		
		if (rel_temp < -5.)				LPRINT ("Cold")		/* 5 C below earth */
		else if (rel_temp < -2.0)		LPRINT ("Cool")
		else if (rel_temp > 7.5)		LPRINT ("Hot")
		else if (rel_temp > 3.0)		LPRINT ("Warm")
		
		if (ice > 10.)					LPRINT ("Icy")		/* 10% surface is ice */

		if (atmosphere < 0.001)			LPRINT ("Airless")
		else
		{
			if (planet->type != tWater)
			{
				if (seas < 25.)			LPRINT ("Arid")		/* 25% surface is water */
				else if (seas < 50.)	LPRINT ("Dry")
				else if (seas > 80.)	LPRINT ("Wet")
			}
			
			if (clouds < 10.)			LPRINT ("Cloudless")/* 10% cloud cover */
			else if (clouds < 40.)		LPRINT ("Few clouds")
			else if (clouds > 80.)		LPRINT ("Cloudy")
			
			if (planet->max_temp >= planet->boil_point)
										LPRINT ("Boiling ocean")
			
			if (planet->surf_pressure < MIN_O2_IPP)
										LPRINT ("Unbreathably thin atmosphere")
			else if (atmosphere < 0.5)	LPRINT ("Thin atmosphere")
			else if (atmosphere > MAX_HABITABLE_PRESSURE /	/* Dole, pp. 18-19 */
								  EARTH_SURF_PRES_IN_MILLIBARS)
										LPRINT ("Unbreathably thick atmosphere")
			else if (atmosphere > 2.0)	LPRINT ("Thick atmosphere")
			else if (planet->type != tTerrestrial)
										LPRINT ("Normal atmosphere")
		}

		if (first)						LPRINT ("Earth-like");

		if (planet->gases > 0)
		{
			int	i;
			int	first = TRUE;
			unsigned int temp;
			
			fprintf (file, " (");

			for (i = 0; i < planet->gases; i++)
			{
				int n;
				int index = max_gas;
				
				for (n = 0; n < max_gas; n++)
				{
					if (gases[n].num == planet->atmosphere[i].num)
						index = n;
				}
				
				if ((planet->atmosphere[i].surf_pressure / planet->surf_pressure)
					> .01)
				{
					LPRINT (gases[index].html_symbol);
				}
			}
			
			if ((temp = breathability (planet)) != NONE)
				fprintf (file, " - %s)",
					 breathability_phrase[temp]);
		}
		
		if ((int)planet->day == (int)(planet->orb_period * 24.0)
		 || (planet->resonant_period))
			LPRINT ("1-Face");
		
		fprintf (file, closing);
	}
}

/*
 *  This function lists the gases whose atomic/molecular weight is
 *  large enough that it is retained.
 */

#define MOL_PRINTF(x,y)	{ if (y >= weight) { \
							{if (++count > max) {fprintf(file, "..."); return;} \
							 else LPRINT(x)} } }
void list_molecules(FILE*		file,
					long double	weight)
{
	int count = 0;
	int max   = 8;
	int	first = TRUE;
	
	MOL_PRINTF("H",								ATOMIC_HYDROGEN);
	MOL_PRINTF("H<SUB><SMALL>2</SMALL></SUB>",	MOL_HYDROGEN);
	MOL_PRINTF("He",							HELIUM);
	MOL_PRINTF("N",								ATOMIC_NITROGEN);
	MOL_PRINTF("O",								ATOMIC_OXYGEN);
	MOL_PRINTF("CH<SUB><SMALL>4</SMALL></SUB>", METHANE);
	MOL_PRINTF("NH<SUB><SMALL>3</SMALL></SUB>", AMMONIA);
	MOL_PRINTF("H<SUB><SMALL>2</SMALL></SUB>O", WATER_VAPOR);
	MOL_PRINTF("Ne",							NEON);
	MOL_PRINTF("N<SUB><SMALL>2</SMALL></SUB>",	MOL_NITROGEN);
	MOL_PRINTF("CO",							CARBON_MONOXIDE);
	MOL_PRINTF("NO",							NITRIC_OXIDE);
	MOL_PRINTF("O<SUB><SMALL>2</SMALL></SUB>",	MOL_OXYGEN);
	MOL_PRINTF("H<SUB><SMALL>2</SMALL></SUB>S", HYDROGEN_SULPHIDE);
	MOL_PRINTF("Ar",							ARGON);
	MOL_PRINTF("CO<SUB><SMALL>2</SMALL></SUB>", CARBON_DIOXIDE);
	MOL_PRINTF("N<SUB><SMALL>2</SMALL></SUB>O", NITROUS_OXIDE);
	MOL_PRINTF("NO<SUB><SMALL>2</SMALL></SUB>", NITROGEN_DIOXIDE);
	MOL_PRINTF("O<SUB><SMALL>3</SMALL></SUB>",	OZONE);
	MOL_PRINTF("SO<SUB><SMALL>2</SMALL></SUB>", SULPH_DIOXIDE);
	MOL_PRINTF("SO<SUB><SMALL>3</SMALL></SUB>", SULPH_TRIOXIDE);
	MOL_PRINTF("Kr",							KRYPTON);
	MOL_PRINTF("Xe",							XENON);
}

/*
 *	Table of scaled planet pictures
 */
 
void html_thumbnails(planet_pointer innermost_planet, 
					 FILE*	file, 
					 char*	system_name, 
					 char*	subdir,
					 char*	file_name,
					 int	details,
					 int	terrestrials)
{
	planet_pointer 	planet;
	primary*		sun = innermost_planet->primary;
	int 			counter; 
	int				planet_count=0;
	int				terrestrials_seen = FALSE;
	
	for (planet=innermost_planet;
		 planet != NULL;
		 planet=planet->next_planet)
		planet_count++;
 
	fprintf (file,
	        "\n<P>\n\n"
	        "<TABLE BORDER=3 CELLSPACING=2 CELLPADDING=2 ALIGN=CENTER "
	        	   "BGCOLOR='" BGTABLE "' WIDTH='90%c'>\n"
		        "<TR><TH COLSPAN=2 BGCOLOR='" BGTABLE "' ALIGN=CENTER>\n"
		        	"\t<FONT SIZE='+2' COLOR='" TXTABLE "'>",
	        '%');

	if (file_name[0] == '\0')
		fprintf (file, "%s", system_name);
	else
		fprintf (file, "<A HREF='%s%s%s'>%s</A>", url_path, subdir, file_name, system_name);

	fprintf (file,
		    	"</FONT></TH></TR>\n"
	        "<TR BGCOLOR='" BGTABLE "'><TD COLSPAN=2>\n"
	        "<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3 BGCOLOR='" BGSPACE "' WIDTH='100%c'>\n",
	        '%');

	fprintf (file,
		        "<TR><TD COLSPAN=%d BGCOLOR='" BGHEADER "' ALIGN=CENTER>\n"
		        	"\t<FONT SIZE='+1'  COLOR='" TXHEADER "'><B>%d Planets</B> </FONT>\n"
		        	"\t(<FONT SIZE='-1' COLOR='" TXHEADER "'>size proportional to Sqrt(Radius)</FONT>)\n"
		        "</TD></TR>\n"
	        	"<TR VALIGN=MIDDLE BGCOLOR='" BGSPACE "'>\n"
	        	"<TD BGCOLOR='" BGSPACE "'><IMG ALT='Sun' SRC='%sref/Sun.gif' "
	        		"WIDTH=15 HEIGHT=63 BORDER=0></TD>\n", 
	        planet_count+2, planet_count, url_path);
	        
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		int	pixels = ((int)( sqrt(planet->radius / KM_EARTH_RADIUS) * 30.)) + 1;
		char *type = type_string (planet->type);
		char info[100];
		
		if (planet->type == tAsteroids)
			pixels = (int)(25.0 + ( 5.0 * log ((planet->mass * SUN_MASS_IN_EARTH_MASSES) / 
										        ASTEROID_MASS_LIMIT)));
		
		if (pixels < 3)
			pixels = 3;
		
		if ((planet->type == tGasGiant)
		 || (planet->type == tSubSubGasGiant)
		 || (planet->type == tSubGasGiant))
			sprintf(&info[0], "%s: %.1LfEM (c. %.0Lf&deg;)", 
					type, planet->mass * SUN_MASS_IN_EARTH_MASSES,
					planet->estimated_temp);
		else if (planet->type == tUnknown)
			sprintf(&info[0], "%s: %.1LfEM, %.2LfEM from gas (%.1Lf%c) Zone = %d", 
					type, planet->mass * SUN_MASS_IN_EARTH_MASSES,
					planet->gas_mass * SUN_MASS_IN_EARTH_MASSES,
					100.0 * (planet->gas_mass / planet->mass), '%',
					planet->orbit_zone);
		else
			sprintf(&info[0], "%s: %.2LfEM, %.2Lfg, %.1Lf&deg; Zone = %d", 
					type, planet->mass * SUN_MASS_IN_EARTH_MASSES, planet->surf_grav, 
					(planet->surf_temp - FREEZING_POINT_OF_WATER),
					planet->orbit_zone);
		
		fprintf (file,
	        "\t<TD BGCOLOR='" BGSPACE "'><A HREF='%s%s%s#%d' TITLE='#%d - %s'>"
	        	"<IMG ALT='%s' SRC='%sref/%sPlanet.gif' WIDTH=%d HEIGHT=%d BORDER=0></A></TD>\n", 
			(file_name[0] == '\0') ? "" : url_path, 
			(file_name[0] == '\0') ? "" : subdir,
			file_name, 
			counter, counter, info, type, 
			url_path, type, 
			pixels, pixels);

		if ((planet->type == tTerrestrial)
		 || (planet->type == tWater)
		 || (breathability (planet) == BREATHABLE)
		 || ((planet->surf_pressure > 0.001)
		  && (planet->surf_temp > FREEZING_POINT_OF_WATER - 15)
		  && (planet->surf_temp < EARTH_AVERAGE_KELVIN + 15)))
			terrestrials_seen = TRUE;
	}
	fprintf (file, 
			 "<TD BGCOLOR='" BGSPACE "' ALIGN=RIGHT VALIGN=BOTTOM>"
			 "<A HREF='%sref/Key.html'><FONT SIZE='-3' COLOR='" TXSPACE "'>See<BR>Key</FONT></A></TD>\n"
			 "</TR></TABLE></TD></TR>\n",
			 url_path);

/*
 *	Table of data on the star system
 */

	if (terrestrials && terrestrials_seen)
	{
		fprintf (file, "<TR><TD COLSPAN=2><TABLE WIDTH='100%%'>");
		
		for (planet=innermost_planet, counter=1;
			planet != NULL;
			planet=planet->next_planet, counter++)
		{
			if (((breathability (planet) == BREATHABLE) ||
			     ((planet->max_temp >= FREEZING_POINT_OF_WATER) &&
				  (planet->min_temp <= planet->boil_point))) &&
				(planet->type != tSubSubGasGiant))
			{
				fprintf (file,
						 "\n\t<TR><TD ALIGN=RIGHT WIDTH='5%%'>"
						 "<A HREF='%s%s%s#%d'><SMALL>#%d</SMALL></A>"
						 "</TD>\n\t\t<TD><SMALL>%s: </SMALL>", 
						 (file_name[0] == '\0') ? "" : url_path, 
						 (file_name[0] == '\0') ? "" : subdir,
						 file_name, 
						 counter, counter, 
						 type_string(planet->type));
				
				print_description(file, "", planet, "");

				fprintf (file, "</TD></TR>");
			}
		}

		fprintf (file, "</TABLE></TD></TR>");
	}
	
	if (details)
	{
		fprintf (file,
		        "<TR><TD COLSPAN=2 BGCOLOR='" BGHEADER "' ALIGN=CENTER>"
		        	"<FONT SIZE='+1' COLOR='" TXHEADER "'><B>Stellar charactersistics</B></FONT>"
		        "</TD></TR>\n");
		fprintf (file,
		        "<TR><TD>Stellar mass</TD>\n"
		        "\t<TD>%4.2Lf solar masses</TD></TR>\n", 
				sun->mass);
		fprintf (file,
		        "<TR><TD>Stellar luminosity</TD>\n"
		        "\t<TD>%4.2Lf</TD></TR>\n",
				sun->luminosity);
		fprintf (file,
		        "<TR><TD>Age</TD>\n"
		        "\t<TD>%5.3Lf billion years<BR>"
				"(%5.3Lf billion left on main sequence)<BR>",
			   (sun->age / 1.0E9),
			   (sun->life - sun->age) / 1.0E9);
		fprintf (file,
		        "<TR><TD>Habitable ecosphere radius</TD>\n"
		        "\t<TD>%3.3Lf AU</TD></TR>\n",
				sun->r_ecosphere);
	}

	fprintf (file, "</TABLE>\n<BR CLEAR=ALL>\n");
	fflush (file);
}

void html_thumbnail_totals(FILE *file)
{
	fprintf (file,
	        "\n<P>\n\n"
	        "<TABLE BORDER=3 CELLSPACING=2 CELLPADDING=2 ALIGN=CENTER "
	        	   "BGCOLOR='" BGTABLE "'>\n"
		        "<TR><TH COLSPAN=2 BGCOLOR='" BGHEADER "' ALIGN=CENTER>\n"
		        	"\t<FONT SIZE='+1' COLOR='" TXHEADER "'>"
		        	"<B>Summary</B></FONT></TH></TR>\n"
	        );
	
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tEarthlike planets\n</TD><TD ALIGN=CENTER>\n\t%d\n</TD></TR>\n", earthlike);
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tBreathable atmospheres\n</TD><TD ALIGN=CENTER>\n\t%d\n</TD></TR>\n", total_habitable);
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tBreathable g range\n</TD><TD ALIGN=CENTER>\n\t%4.2Lf -  %4.2Lf\n</TD></TR>\n", 
			 min_breathable_g, 
			 max_breathable_g);
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tTerrestrial g range\n</TD><TD ALIGN=CENTER>\n\t%4.2Lf -  %4.2Lf\n</TD></TR>\n", 
			 min_breathable_terrestrial_g,
			 max_breathable_terrestrial_g);
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tBreathable pressure range\n</TD><TD ALIGN=CENTER>\n\t%4.2Lf -  %4.2Lf\n</TD></TR>\n", 
			 min_breathable_p, 
			 max_breathable_p);
	fprintf (file, 
			"<TR BGCOLOR='" BGTABLE "'><TD ALIGN=RIGHT>\n"
				"\tBreathable temp range\n</TD><TD ALIGN=CENTER>\n\t%+.1Lf C -  %+.1Lf C\n</TD></TR>\n", 
			 min_breathable_temp - EARTH_AVERAGE_KELVIN, 
			 max_breathable_temp - EARTH_AVERAGE_KELVIN);

	fprintf (file,
	        "</TABLE>\n\n"
	        );
}

void html_describe_system(planet_pointer innermost_planet, 
						  int do_gases, 
						  FILE *file)
{
	planet_pointer planet;
	int counter; 
	
	/*
	 *	System summary
	 */
	 
	fprintf (file,
	        "\n<TABLE BORDER=3 CELLSPACING=2 CELLPADDING=2 ALIGN=CENTER BGCOLOR='" BGTABLE "' WIDTH='90%c'>\n"
			"<TR><TH COLSPAN=6 BGCOLOR='" BGHEADER "' ALIGN=CENTER>\n"
		        	"<FONT SIZE='+2' COLOR='" TXHEADER "'>Planetary Overview</FONT></TH></TR>\n\n"
			"<TR ALIGN=CENTER>\n"
			"	<TH>#</TH><TH COLSPAN=2>Type</TH><TH>Dist.</TH><TH>Mass</TH><TH>Radius</TH>\n"
			"</TR>\n", '%');

	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		char	*typeString = type_string (planet->type);
		
		fprintf (file,
	        "<TR ALIGN=RIGHT>\n"
				"\t<TD><A HREF='#%d'>%d</A></TD>\n"
				"\t<TD ALIGN=CENTER><IMG ALT='%s' SRC='%sref/%s.gif'></TD>\n"
				"\t<TD>%s</TD>\n"
				"\t<TD>%7.3Lf  AU</TD>\n"
				"\t<TD>%8.3Lf EM</TD>\n"
				"\t<TD>%8.3Lf ER</TD>"
				"</TR>\n",
				counter, counter, 
			    typeString, 
			    url_path, 
			    typeString, 
			    typeString, 
				planet->a, 
				planet->mass * SUN_MASS_IN_EARTH_MASSES,
				planet->radius / KM_EARTH_RADIUS);
	}
	fprintf (file,
	        "</TABLE>\n<BR CLEAR=ALL>\n");
	
	/*
	 *	Tables for individual planets
	 */
	 
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		char	*typeString = type_string (planet->type);
		
		fprintf (file,
	        	"<P>\n<A NAME='%d'></A><TABLE BORDER=3 CELLSPACING=2 CELLPADDING=2 ALIGN=CENTER "
	        								 "BGCOLOR='" BGTABLE "' WIDTH='90%c'>\n"
				"<COLGROUP SPAN=1 ALIGN=LEFT VALIGN=MIDDLE>"
				"<COLGROUP SPAN=2 ALIGN=LEFT VALIGN=MIDDLE>"
				"<TR><TH COLSPAN=3 BGCOLOR='" BGHEADER "' ALIGN=CENTER>\n"
		        	"<FONT SIZE='+2' COLOR='" TXHEADER "'>Planet #%d Statistics</FONT></TH></TR>\n", 
				counter,
				'%',
				counter);
		
		fprintf (file,
				"<TR><TH>Planet type</TH>"
				"<TD COLSPAN=2><IMG ALT='%s' SRC='%sref/%s.gif' ALIGN=MIDDLE WIDTH=20 HEIGHT=20>%s",
				typeString, 
				url_path, 
				typeString, 
				typeString);

		if ((int)planet->day == (int)(planet->orb_period * 24.0))
			fprintf (file, "<BR>Tidally Locked 1 Face\n");
			
		if (planet->resonant_period)
			fprintf (file, "<BR>Resonant Spin Locked\n");
		
		print_description(file, "<BR>", planet, "");

		fprintf (file, "</TD></TR>\n");
					
		fprintf (file,
	        "<TR><TH>Distance from primary star</TH><TD>%.2LG KM</TD>"
	        "<TD>%5.3Lf AU</TD></TR>\n",
				planet->a * KM_PER_AU,
				planet->a);
		fprintf (file,
		        "<TR><TH>Mass</TH><TD>%.2LGKg</TD>"
		        "<TD>",
				planet->mass * SUN_MASS_IN_EARTH_MASSES * EARTH_MASS_IN_GRAMS / 1000.);

		if ((planet->dust_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
		 && (planet->gas_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
		 && (planet->type != tGasGiant) 
		 && (planet->type != tSubGasGiant))
		{
			int core_size = (int)((50. * planet->core_radius) / planet->radius);
			
			if (core_size <= 49)
			{
				fprintf (file,
						"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 BGCOLOR='#000000' BACKGROUND='%sref/Atmosphere.gif' ALIGN=RIGHT>"
						"<TR ALIGN=RIGHT VALIGN=BOTTOM BACKGROUND='%sref/Atmosphere.gif'>"
						"<TD WIDTH=50 HEIGHT=50 ALIGN=RIGHT VALIGN=BOTTOM BGCOLOR='#000000' BACKGROUND='%sref/Atmosphere.gif'>"
						"<IMG SRC='Core.gif' ALT='' WIDTH=%d HEIGHT=%d>"
						"</TD></TR></TABLE>"
		        		"\n", 
		        		url_path, 
		        		url_path, 
		        		url_path,
		        		core_size,
		        		core_size
		        		);
			}
		}

		fprintf (file,
		        "%5.3Lf Earth masses<BR>",
				planet->mass * SUN_MASS_IN_EARTH_MASSES);

		if ((planet->dust_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
		 && (planet->gas_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006))
		{
			fprintf (file,
		        "%5.3Lf Earth masses dust<BR>"
		        "%5.3Lf Earth masses gas<BR>",
					planet->dust_mass * SUN_MASS_IN_EARTH_MASSES,
					planet->gas_mass * SUN_MASS_IN_EARTH_MASSES);
		}
		
		fprintf (file,
	        "</TD></TR>\n");

		if ((planet->type != tGasGiant) 
		 && (planet->type != tSubGasGiant) 
		 && (planet->type != tSubSubGasGiant))
		{
			long double	celsius = (planet->surf_temp - FREEZING_POINT_OF_WATER);
			
			fprintf (file,
			        "<TR><TH>Surface gravity</TH>"
			        "<TD>%4.1Lf cm/sec<SUP>2</SUP></TD>"
			        "<TD>%4.2Lf Earth gees</TD></TR>\n",
						planet->surf_accel,
						planet->surf_grav);
			
			fprintf (file,
	        		 "<TR><TH>Surface pressure</TH><TD>%5.0Lf millibars",
	        		planet->surf_pressure);
	        
			fprintf (file,
			         "</TD><TD>%5.3Lf Earth atmospheres</TD></TR>\n",
					 (planet->surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS));
			
			fprintf (file,
			        "<TR><TH>Surface temperature</TH>"
			        "<TD>%5.1Lf&deg; Celcius"
			        "<BR>%5.1Lf&deg; Fahrenheit</TD>"
			        "<TD ROWSPAN=2 VALIGN=TOP>%+4.1Lf&deg; C Earth temperature"
			        "<BR>%+4.1Lf&deg; F Earth temperature",
						celsius,
						32 + (celsius * 1.8),
						celsius - EARTH_AVERAGE_CELSIUS,
						((celsius - EARTH_AVERAGE_CELSIUS) * 1.8));

			
			if (planet->greenhs_rise > 0.1)
			{
				fprintf (file, 
					"<BR>%+4.1Lf&deg; C greenhouse effect", 
						planet->greenhs_rise);

				if ((planet->greenhouse_effect) && (planet->surf_pressure > 0.0))
					fprintf (file, " (GH)");
			
			}
			
			fprintf (file,"</TD></TR>\n");
			
			
			{
		    	fprintf (file, 
		    		"<TR><TH>Normal temperature range</TH>"
		    		"<TD><CENTER><TABLE>\n");

		    	if (fabs(planet->high_temp - planet->max_temp) > 10 
		    	 || fabs(planet->low_temp - planet->min_temp) > 10)
			    {
			    	fprintf (file, "\t<TR><TH>Night</TH><TH></TH><TH>Day</TH></TR>\n");
			    	
			    	fprintf (file, 
			    		"\t<TR><TD>%5.1Lf&deg; C<BR>%5.1Lf&deg; F</TD>"
			    		"<TD> - </TD>",
			    			planet->low_temp - FREEZING_POINT_OF_WATER,
			    			32.0 + (1.8 * (planet->low_temp - FREEZING_POINT_OF_WATER)));

			    	fprintf (file, 
			    		"<TD>%5.1Lf&deg; C<BR>%5.1Lf&deg; F</TD>"
			    		"</TR>\n",
			    			planet->high_temp - FREEZING_POINT_OF_WATER,
			    			32.0 + (1.8 * (planet->high_temp - FREEZING_POINT_OF_WATER)));
			    }
		    	
		    	fprintf (file, "\t<TR><TH>Min</TH><TH></TH><TH>Max</TH></TR>\n");
			    	
		    	fprintf (file, 
		    		"\t<TR><TD>%5.1Lf&deg; C<BR>%5.1Lf&deg; F</TD>"
		    		"<TD> - </TD>",
	    			planet->min_temp - FREEZING_POINT_OF_WATER,
		    		32.0 + (1.8 * (planet->min_temp - FREEZING_POINT_OF_WATER)));

		    	fprintf (file, 
		    		"<TD>%5.1Lf&deg; C<BR>%5.1Lf&deg; F</TD>"
		    		"</TR>\n",
		    			planet->max_temp - FREEZING_POINT_OF_WATER,
			    		32.0 + (1.8 * (planet->max_temp - FREEZING_POINT_OF_WATER)));

	    	fprintf (file, 
	    		"</TABLE></CENTER></TD></TR>\n");
		    }
		}

		fprintf (file,
	        "<TR><TH>Equatorial radius</TH>"
	        "<TD>%3.1Lf Km</TD>"
	        "<TD>%.2LG Earth radii</TD></TR>\n",
				planet->radius,
				planet->radius / KM_EARTH_RADIUS);
		fprintf (file,
	        "<TR><TH>Density</TH>"
	        "<TD>%4.2Lf grams/cc</TD>"
	        "<TD>%.2LG Earth densities</TD></TR>\n",
				planet->density,
				planet->density / EARTH_DENSITY);
		fprintf (file,
	        "<TR><TH>Eccentricity of orbit</TH><TD>%5.3Lf</TD>"
	        "<TD></TD></TR>\n",
				planet->e);
		fprintf (file,
	        "<TR><TH>Escape Velocity</TH><TD>%4.1Lf Km/sec</TD>"
	        "<TD></TD></TR>\n",
				planet->esc_velocity / CM_PER_KM);
		fprintf (file,
	        "<TR><TH>Molecular weight retained</TH><TD>%4.1Lf and above</TD>"
	        "<TD>",
				planet->molec_weight);
				
		list_molecules(file, planet->molec_weight);
		
		if (do_gases && (planet->gases > 0))
		{
			int	i;
			
			fprintf (file, "\n<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>\n");
			
			for (i = 0; i < planet->gases; i++)
			{
				int n;
				int index = max_gas;
				int	poisonous = FALSE;
				
				for (n = 0; n < max_gas; n++)
				{
					if (gases[n].num == planet->atmosphere[i].num)
						index = n;
				}
				
				if (inspired_partial_pressure (planet->surf_pressure,
									   		   planet->atmosphere[i].surf_pressure)
					> gases[index].max_ipp)
					poisonous = TRUE;
				
				if (((planet->atmosphere[i].surf_pressure
					 / planet->surf_pressure) > .0005)
				 || poisonous)
				{
					fprintf (file, "<TR><TH ALIGN=LEFT>%s&nbsp;</TH>"
								   "<TD ALIGN=RIGHT>%4.1Lf%%&nbsp;</TD>"
								   "<TD ALIGN=RIGHT>%5.0Lf mb&nbsp;</TD>"
								   "<TD ALIGN=RIGHT>(ipp:%5.0Lf)</TD>"
								   "<TD ALIGN=RIGHT>&nbsp;%s</TD></TR>\n",
									gases[index].name,
									100. * (planet->atmosphere[i].surf_pressure /
											planet->surf_pressure),
									planet->atmosphere[i].surf_pressure,
									inspired_partial_pressure (planet->surf_pressure,
															   planet->atmosphere[i].surf_pressure),
									poisonous ? "poisonous" : ""
							);
				}
			}
			fprintf (file, "</TABLE>\n");
		}
		
		fprintf (file, "</TD></TR>\n");
		fprintf (file,
	        "<TR><TH>Axial tilt</TH><TD>%2.0Lf&deg;</TD>"
	        "<TD></TD></TR>\n",
				planet->axial_tilt);
		fprintf (file,
	        "<TR><TH>Planetary albedo</TH><TD>%5.2Lf</TD>"
	        "<TD></TD></TR>\n",
				planet->albedo);
		fprintf (file,
	        "<TR><TH>Exospheric Temperature</TH><TD>%6.2Lf&deg; K</TD>"
	        "<TD>%+6.2Lf&deg; C Earth temperature</TD></TR>\n",
				planet->exospheric_temp,
				planet->exospheric_temp - EARTH_EXOSPHERE_TEMP);
		fprintf (file,
	        "<TR><TH>Length of year</TH>"
			"<TD>%4.2Lf Earth days</TD>"
	        "<TD>%4.2Lf Local days",
				planet->orb_period,
				(planet->orb_period*24) / planet->day);
		if (planet->orb_period > DAYS_IN_A_YEAR)
			fprintf (file,
				"<BR>%4.2Lf Earth years",
				planet->orb_period / DAYS_IN_A_YEAR);
		fprintf (file, 
			"</TD></TR>\n");
		fprintf (file,
	        "<TR><TH>Length of day</TH><TD>%4.2Lf hours</TD>"
	        "<TD></TD></TR>\n",
				planet->day);

		if ((planet->type != tGasGiant)
		 && (planet->type != tSubGasGiant) 
		 && (planet->type != tSubSubGasGiant))
		{
			fprintf (file,
	        "<TR><TH>Boiling point of water</TH>"
	        "<TD>%3.1Lf&deg; Celcius"
	        "<BR>%3.1Lf&deg; Fahrenheit</TD>"
	        "<TD></TD></TR>\n",
					(planet->boil_point - FREEZING_POINT_OF_WATER),
					32 + ((planet->boil_point - FREEZING_POINT_OF_WATER) * 1.8));
			fprintf (file,
	        "<TR><TH>Hydrosphere percentage</TH><TD>%4.1Lf</TD>"
	        "<TD></TD></TR>\n",
					(planet->hydrosphere * 100.0));
			fprintf (file,
	        "<TR><TH>Cloud cover percentage</TH><TD>%4.1Lf</TD>"
	        "<TD></TD></TR>\n",
					(planet->cloud_cover * 100));
			fprintf (file,
	        "<TR><TH>Ice cover percentage</TH><TD>%4.1Lf</TD>"
	        "<TD></TD></TR>\n",
					(planet->ice_cover * 100));
		}

		fprintf (file,
	        "</TABLE>\n\n<P>\n<BR>\n\n");
	}
}

void celestia_describe_system(planet_pointer innermost_planet, char* designation)
{
	planet_pointer planet;
	int counter; 
	
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		char	*typeString = texture_name (planet->type);
		
		printf("\"p%d\" \"%s\"\n", counter, designation);
		printf("{\n");

		printf("	Texture \"%s\"\n",	typeString);
		printf("	Radius %3.1Lf\n", planet->radius);
		printf("	Mass %3.1Lf\n", planet->mass * SUN_MASS_IN_EARTH_MASSES);
		printf("\n");
		
		switch (planet->type)
		{
			 case tUnknown:
				break;
			 case tRock:
			 case tAsteroids:
			 case t1Face:
				printf("	Color   [ 0.52 0.47 0.42 ]\n");
				printf("	BlendTexture true\n");
				printf("\n");
				break;
			 case tIce:
				printf("	Color [ 1.0 0.9 0.75 ]\n");
				printf("	HazeColor [ 0.2 0.5 1 ]\n");
				printf("	HazeDensity 1\n");
				printf("\n");
				printf("	Atmosphere {\n");
				printf("		Height 60\n");
				printf("		Lower [ 0.8 0.4 0.1 ]\n");
				printf("		Upper [ 0.0 0.0 0.9 ]\n");
				printf("		Sky [ 0.8 0.4 0.1 ]\n");
				printf("	}\n");
				printf("\n");
				break;
			 case tMartian:
				printf("	Color   [ 1 0.75 0.7 ]\n");
				printf("	HazeColor [ 1 1 1 ]\n");
				printf("	HazeDensity 0.45\n");
				printf("\n");
				printf("	Atmosphere {\n");
				printf("		Height 30\n");
				printf("		Lower [ 0.8 0.6 0.6 ]\n");
				printf("		Upper [ 0.7 0.3 0.3 ]\n");
				printf("		Sky [ 0.83 0.75 0.65 ]\n");
				printf("	}\n");
				printf("\n");
				break;
			 case tTerrestrial:
				printf("	Color [ 0.85 0.85 1.0 ]\n");
				printf("	SpecularColor [ 0.5 0.5 0.55 ]\n");
				printf("	SpecularPower 25.0\n");
				printf("	HazeColor [ 1 1 1 ]\n");
				printf("	HazeDensity 0.3\n");
				printf("\n");
				printf("	Atmosphere {\n");
				printf("		Height 60\n");
				printf("		Lower [ 0.5 0.5 0.65 ]\n");
				printf("		Upper [ 0.3 0.3 0.6 ]\n");
				printf("		Sky [ 0.3 0.6 0.9 ]\n");
				printf("		CloudHeight 7\n");
				printf("		CloudSpeed 65\n");
				printf("		CloudMap \"earth-clouds.png\"\n");
				printf("	}\n");
				printf("\n");
				break;
			 case tWater:
				printf("	Color [ 0.75 0.75 1.0 ]\n");
				printf("	SpecularColor [ 0.5 0.5 0.55 ]\n");
				printf("	SpecularPower 25.0\n");
				printf("	HazeColor [ 1 1 1 ]\n");
				printf("	HazeDensity 0.3\n");
				printf("\n");
				printf("	Atmosphere {\n");
				printf("		Height 90\n");
				printf("		Lower [ 0.4 0.4 0.7 ]\n");
				printf("		Upper [ 0.2 0.2 0.6 ]\n");
				printf("		Sky [ 0.4 0.7 0.9 ]\n");
				printf("	}\n");
				printf("\n");
				break;
			 case tVenusian:
				printf("	HazeColor [ 0.5 0.35 0.2 ]\n");
				printf("	HazeDensity 0.35\n");
				printf("\n");
				printf("	Atmosphere {\n");
				printf("		Height 60\n");
				printf("		Lower [ 0.8 0.8 0.5 ]\n");
				printf("		Upper [ 0.6 0.6 0.6 ]\n");
				printf("		Sky [ 0.8 0.8 0.5 ]\n");
				printf("	}\n");
				printf("\n");
				break;
			 case tSubSubGasGiant:
			 case tSubGasGiant:
				printf("	Color [ 0.75 0.85 1.0 ]\n");
				printf("	HazeColor [ 0.5 0.8 1.0 ]\n");
				printf("	HazeDensity 0.2\n");
				printf("\n");
				break;
			 case tGasGiant:
				printf("	HazeColor [ 0.4 0.45 0.5 ]\n");
				printf("	HazeDensity 0.3\n");
				printf("\n");
				break;
		}
		
		printf("	EllipticalOrbit {\n");
		printf("		Period            %4.2Lf  # years\n", planet->orb_period / DAYS_IN_A_YEAR);
		printf("		SemiMajorAxis     %5.3Lf  # AU\n", planet->a);
		printf("		Eccentricity      %5.3Lf\n", planet->e);
		printf("		Inclination       0.0\n");
		printf("		AscendingNode     0\n");
		printf("		LongOfPericenter  0\n");
		printf("	        MeanLongitude 0\n");
		printf("	}\n");
		printf("\n");
		printf("	RotationPeriod    %4.2Lf\n", planet->day);
		printf("	Obliquity         %2.0Lf\n", planet->axial_tilt);
		printf("	Albedo            %5.3Lf\n", planet->albedo);

		printf("}\n");
		printf("\n");
	}
}
