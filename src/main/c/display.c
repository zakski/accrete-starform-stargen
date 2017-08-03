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
	sun*			sun = innermost_planet->sun;
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

void csv_describe_system(FILE *file, planet_pointer innermost_planet, int do_gases, long int seed)
{
	planet_pointer 	planet;
	sun*			sun = innermost_planet->sun;
	int 			counter; 
	char 			buffer[2000];
	planet_pointer 	moon;
	int 			moons; 

	fprintf (file,
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s'\n",
			"seed",
			"name",
			"luminosity",
			"mass",
			"life",
			"age",
			"r_ecosphere"
			);

	fprintf (file,
			"%ld, '%s', %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf\n",
			seed,
			sun->name,
			sun->luminosity,
			sun->mass,
			sun->life,
			sun->age,
			sun->r_ecosphere
			);

	fprintf (file,
			"'%s', "
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s', "
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s', "
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s', "
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s', "
			"'%s', '%s', '%s', '%s', '%s', '%s', '%s', "
			"'%s', '%s', '%s', '%s'\n",
			"planet_no",
			"a",
			"e",
			"axial_tilt",
			"mass",
			"gas_giant",
			"dust_mass",
			"gas_mass",
			"core_radius",
			"radius",
			"orbit_zone",
			"density",
			"orb_period",
			"day",
			"resonant_period",
			"esc_velocity",
			"surf_accel",
			"surf_grav",
			"rms_velocity",
			"molec_weight",
			"volatile_gas_inventory",
			"surf_pressure",
			"greenhouse_effect",
			"boil_point",
			"albedo",
			"exospheric_temp",
			"estimated_temp",
			"estimated_terr_temp",
			"surf_temp",
			"greenhs_rise",
			"high_temp",
			"low_temp",
			"max_temp",
			"min_temp",
			"hydrosphere",
			"cloud_cover",
			"ice_cover",

			"atmosphere",
			"type",
			"minor_moons"
			);

	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		char	*ptr = buffer;
		
		*buffer = '\0';
		
		if (do_gases && (planet->gases > 0))
		{
			int	i;
			
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
					sprintf (ptr, "%s %.1Lf%% %.0Lfmb (ipp:%.0Lf)%s; ",
									gases[index].symbol,
									100. * (planet->atmosphere[i].surf_pressure /
											planet->surf_pressure),
									planet->atmosphere[i].surf_pressure,
									inspired_partial_pressure (planet->surf_pressure,
															   planet->atmosphere[i].surf_pressure),
									poisonous ? " poisonous" : ""
							);
					ptr = buffer + strlen(buffer);
				}
			}
		}

		fprintf (file,
			"'%s %d', %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, "
				"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, %5.3Lf, "
				"%5.3Lf, %5.3Lf, %d, %5.3Lf, %5.3Lf, %5.3Lf, "
				"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, %5.3Lf, "
				"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, "
				"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, "
				"%5.3Lf, '%s', '%s', %d\n",
				sun->name, planet->planet_no,
				planet->a,
				planet->e,
				planet->axial_tilt,
				planet->mass,
				planet->gas_giant,
				planet->dust_mass,
				planet->gas_mass,
				planet->core_radius,
				planet->radius,
				planet->orbit_zone,
				planet->density,
				planet->orb_period,
				planet->day,
				planet->resonant_period,
				planet->esc_velocity,
				planet->surf_accel,
				planet->surf_grav,
				planet->rms_velocity,
				planet->molec_weight,
				planet->volatile_gas_inventory,
				planet->surf_pressure,
				planet->greenhouse_effect,
				planet->boil_point,
				planet->albedo,
				planet->exospheric_temp,
				planet->estimated_temp,
				planet->estimated_terr_temp,
				planet->surf_temp,
				planet->greenhs_rise,
				planet->high_temp,
				planet->low_temp,
				planet->max_temp,
				planet->min_temp,
				planet->hydrosphere,
				planet->cloud_cover,
				planet->ice_cover,
				(do_gases && (planet->gases > 0))
					? buffer 
					: "",
				type_string (planet->type),
				planet->minor_moons
			);
			
		for (moon = planet->first_moon, moons=1;
			moon != NULL;
			moon=moon->next_planet, moons++)
		{
			ptr = buffer;
			
			*buffer = '\0';
			
			if (do_gases && (moon->gases > 0))
			{
				int	i;
				
				for (i = 0; i < moon->gases; i++)
				{
					int n;
					int index = max_gas;
					int	poisonous = FALSE;
					
					for (n = 0; n < max_gas; n++)
					{
						if (gases[n].num == moon->atmosphere[i].num)
							index = n;
					}
					
					if (inspired_partial_pressure (moon->surf_pressure,
												   moon->atmosphere[i].surf_pressure)
						> gases[index].max_ipp)
						poisonous = TRUE;
					
					if (((moon->atmosphere[i].surf_pressure
						 / moon->surf_pressure) > .0005)
					 || poisonous)
					{
						sprintf (ptr, "%s %.1Lf%% %.0Lfmb (ipp:%.0Lf)%s; ",
										gases[index].symbol,
										100. * (moon->atmosphere[i].surf_pressure /
												moon->surf_pressure),
										moon->atmosphere[i].surf_pressure,
										inspired_partial_pressure (moon->surf_pressure,
																   moon->atmosphere[i].surf_pressure),
										poisonous ? " poisonous" : ""
								);
						ptr = buffer + strlen(buffer);
					}
				}
			}
	
			fprintf (file,
				"'%s %d.%d', %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, "
					"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, %5.3Lf, "
					"%5.3Lf, %5.3Lf, %d, %5.3Lf, %5.3Lf, %5.3Lf, "
					"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %d, %5.3Lf, "
					"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, "
					"%5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, %5.3Lf, "
					"%5.3Lf, '%s', '%s'\n",
					sun->name, planet->planet_no, moons,
					moon->a,
					moon->e,
					moon->axial_tilt,
					moon->mass,
					moon->gas_giant,
					moon->dust_mass,
					moon->gas_mass,
					moon->core_radius,
					moon->radius,
					moon->orbit_zone,
					moon->density,
					moon->orb_period,
					moon->day,
					moon->resonant_period,
					moon->esc_velocity,
					moon->surf_accel,
					moon->surf_grav,
					moon->rms_velocity,
					moon->molec_weight,
					moon->volatile_gas_inventory,
					moon->surf_pressure,
					moon->greenhouse_effect,
					moon->boil_point,
					moon->albedo,
					moon->exospheric_temp,
					moon->estimated_temp,
					moon->estimated_terr_temp,
					moon->surf_temp,
					moon->greenhs_rise,
					moon->high_temp,
					moon->low_temp,
					moon->max_temp,
					moon->min_temp,
					moon->hydrosphere,
					moon->cloud_cover,
					moon->ice_cover,
					(do_gases && (moon->gases > 0))
						? buffer 
						: "",
					type_string (moon->type)
				);
		}
	}

}

void csv_thumbnails(FILE*	file, 
					char*	url_path,
					char*	subdir,
					char*	file_name,
					char*	csv_url)
{
	fprintf(file, 
			"<table border=3 cellpadding=2 align=center bgcolor='#FFE6CC' width='75%%'>\n"
			"	<tr>\n"
			"		<td align=center><a href='%s' type='text/csv'><img \n"
			"				src='%sref/CSVicon.png' alt='[CSV file]'\n"
			"				height=48 width=48></a>\n"
			"			%s</td>\n"
			"		<td>Click on the file icon to download the data in CSV\n"
			"			(comma separated values) format.</td>\n"
			"	</tr>\n"
			"</table>\n\n",
			csv_url,
			url_path,
			file_name);
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

void create_svg_file (FILE				*file_arg,
					  planet_pointer	innermost_planet, 
					  char				*path, 
					  char 				*file_name, 
					  char 				*svg_ext, 
					  char 				*prognam)
{
	planet_pointer 	outermost_planet;
	planet_pointer	planet;
	FILE*	file = stdout;
	char	file_spec[300];
	
	if (file_arg == NULL)
	{
		sprintf (&file_spec[0], "%s%s%s", path, file_name, svg_ext);

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
	else
	{
		file = file_arg;
	}
	
	if (NULL != file)
	{
		for (outermost_planet = innermost_planet;
			 outermost_planet->next_planet != NULL;
			 outermost_planet=outermost_planet->next_planet)
			;
		
		{
			double long		max_x		= 760.;
			double long		max_y		= 120.;
			double long		margin		= 20.;
			double long		inner_edge 	= innermost_planet->a * (1.0 - innermost_planet->e);
			double long		outer_edge  = outermost_planet->a * (1.0 + outermost_planet->e);
			double long		floor		= (int)(log10(inner_edge) - 1.);
			double long		min_log 	= floor;
			double long		ceiling		= (int)(log10(outer_edge) + 1.);
			double long		max_log 	= 0.0;
			double long		mult		= max_x / (max_log - min_log);
			double long		offset  	= -mult * (1.0 + min_log);
			double long		em_scale 	= 5;
			double long		x;
	
			for (x = floor;
				 x <= ceiling;
				 x += 1.0)
			{
				float	n;
				
				for (n = 1.;
					 n < 9.9;
					 n++)
				{
					if (inner_edge > pow(10., x + log10(n)))
						min_log = x + log10(n);
						
					if ((max_log == 0.0)
					 && (outer_edge < pow(10., x + log10(n))))
					{
						max_log = x + log10(n);
					}
				}
			}
	
			mult		= max_x / (max_log - min_log);
			offset  	= -mult * (1.0 + min_log);
			em_scale 	= 5;
	
			fprintf (file,
					 "<?xml version='1.0' standalone='no'?>\n"
					 "<!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 1.1//EN' \n"
					 "  'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'>\n"
					"\n"
					 "<svg width='100%%' height='100%%' version='1.1'\n"
					 "     xmlns='http://www.w3.org/2000/svg'\n"
					 "     viewBox='-%.0Lf -%.0Lf %.0Lf %.0Lf' >\n"
					 "\n"
					 "<title>%s</title>\n"
					 "<desc>Created by: %s - %s</desc>\n"
					 "\n"
					 "<g stroke='black' stroke-width='1'>\n"
					 "    <line x1='%.0Lf' y1='%.0Lf' x2='%.0Lf' y2='%.0Lf' />\n",
					 margin, margin,
					 max_x + (margin * 2.), max_y + (margin * 2.),
					 (innermost_planet->sun)->name,
					 prognam, stargen_revision, 
					 (offset+mult)+(min_log*mult), max_y - margin, 
					 (offset+mult)+(max_log*mult), max_y - margin
					);
			
			for (x = floor;
				 x <= ceiling;
				 x += 1.0)
			{
				float	n;
				
				for (n = 1.;
					 n < 9.9;
					 n++)
				{
					if ((min_log <= x + log10(n))
					 && (max_log >= x + log10(n)))
					{
						fprintf (file,
								 "    <line x1='%.0Lf' y1='%.0Lf' x2='%.0Lf' y2='%.0Lf' />\n",
								 (offset+mult)+((x + log10(n))*mult),
								 max_y - margin - ((n == 1) ? 10 : 5),
								 (offset+mult)+((x + log10(n))*mult),
								 max_y - margin + ((n == 1) ? 10 : 5)
								);
					}
				}
			}
	
			fprintf (file,  "</g>\n\n" );
	
			{
				long double min_r_ecosphere = sqrt( (innermost_planet->sun)->luminosity / 1.51 );
				long double max_r_ecosphere = sqrt( (innermost_planet->sun)->luminosity / 0.48 );

				fprintf (file,
						 "<line x1='%.0Lf' y1='%.0Lf' x2='%.0Lf' y2='%.0Lf' stroke='blue' stroke-width='1' />\n",
						 (offset+mult)+(log10((innermost_planet->sun)->r_ecosphere)*mult), (max_y - margin) - 5,
						 (offset+mult)+(log10((innermost_planet->sun)->r_ecosphere)*mult), (max_y - margin) + 5
						);
				
				fprintf (file,
						 "<line x1='%.0Lf' y1='%.0Lf' x2='%.0Lf' y2='%.0Lf' stroke='#66c' stroke-width='10' stroke-opacity='0.5' />\n",
						 (offset+mult)+(log10(min_r_ecosphere)*mult), max_y - margin,
						 (offset+mult)+(log10(max_r_ecosphere)*mult), max_y - margin
						);
			}

			fprintf (file,
					 "<g font-family='Arial' font-size='10' \n"
					 "   font-style='normal' font-weight='normal'\n"
					 "   fill='black' text-anchor='middle'>\n"
					);
	
			for (x = floor;
				 x <= ceiling;
				 x += 1.0)
			{
				if ((min_log <= x )
				 && (max_log >= x ))
				{
					fprintf (file,
							 "    <text x='%.0Lf' y='120'> %.0f AU </text>\n",
							 (offset + mult) + (x * mult),
							 pow(10., x)
							);
				}
			}

			fprintf (file,  "\n" );
	
			for (planet = innermost_planet;
				 planet != NULL;
				 planet = planet->next_planet)
			{
				double long	x = (offset + mult) + (log10(planet->a) * mult);
				double long r = pow((planet->mass * SUN_MASS_IN_EARTH_MASSES), 1./3.) * em_scale;
				double long	x1 = (offset + mult) + (log10(planet->a * (1. - planet->e)) * mult);
				double long	x2 = (offset + mult) + (log10(planet->a * (1. + planet->e)) * mult);
	
				fprintf (file,
						 "    <circle cx='%.0Lf' cy='30' r='%.0Lf' fill='none' stroke='black' stroke-width='1' />\n"
						 "    <line x1='%.0Lf' y1='%.0Lf' x2='%.0Lf' y2='%.0Lf' stroke='black' stroke-width='8' stroke-opacity='0.3'/>\n"
						 "    <text x='%.0Lf' y='%.0Lf'>",
						 x, r, 
						 x1, (max_y - margin) - 15, x2, (max_y - margin) - 15,
						 x, max_y - (margin * 2.)
						);
	
				fprintf (file,
						 (planet->mass * SUN_MASS_IN_EARTH_MASSES) <= 1.0 
						 ? "%.2Lf"
						 : (planet->mass * SUN_MASS_IN_EARTH_MASSES) <= 10.0 
						   ? "%.1Lf"
						   : "%.0Lf",
						 planet->mass * SUN_MASS_IN_EARTH_MASSES
						);
	
				fprintf (file, "</text>\n\n");
			}
	
			fprintf (file,
					 "</g>\n"
					 "</svg>\n"
					);
		}
		
		fflush (file);
		fclose (file);
	}
}

FILE *open_csv_file (char *path,
					 char *file_name)
{
	FILE *file;
	char file_spec[120];

	sprintf (&file_spec[0], "%s%s", path, file_name);
	
#ifdef macintosh
		_fcreator ='XCEL';
		_ftype = 'TEXT';
#endif
		file = fopen (file_spec, "w");
#ifdef macintosh
		_fcreator ='R*ch';
		_ftype = 'TEXT';
#endif
	
	return file;
}

/*
 *	HTML document headers
 */

FILE *open_html_file (char *system_name, 
					  long	seed,
					  char *path,
					  char *url_path,
					  char *file_name, 
					  char *ext,
					  char *prognam,
					  FILE *file_arg)
{
	FILE *file;
	char file_spec[300];
	int  noname = ((NULL == system_name) || (0 == system_name[0]));
	
	if (file_arg != NULL)
	{
		file = file_arg;
	}
	else
	{
		sprintf (&file_spec[0], "%s%s%s", path, file_name, ext);
	
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
		        "        %chttp://www.w3.org/TR/html4/loose.dtd%c>\n"
				"<html>\n<head>\n"
				"<meta http-equiv=content-type content='text/html; charset=utf-8'>\n"
				"\t<title>System %ld%s%s</title>\n"
				"\t<meta name='generator' content='%s - %s'>\n"
				"<style type='text/css'>\r"
				"<!--\r"
				"table {border-color: #ffd;}\r"
				"-->\r"
				"</style>\r"
				"<link rel='icon' type='image/png' href='%sref/favicon.png'>\r"
				"</head>\n<body bgcolor='" BGCOLOR "' text='" TXCOLOR "' "
							   "link='" LINKCOLOR "' vlink='" TXCOLOR "' alink='" ALINKCOLOR "'>\n\n\n", 
				'"','"','"','"',
				seed,
				noname ? "" : " - ",
				noname ? "" : system_name,
				prognam, stargen_revision,
				url_path
				);
	}
	
	return file;
}

void close_html_file(file)
FILE *file;
{

	fprintf (file,
			"<p>\n\n"
			"<center>\n"
			"This page was created by <a href='" STARGEN_URL "'>StarGen</a>.\n"
			"</center>\n"
			"<p>\n\n"
	        "</body>\n</html>\n");
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
	MOL_PRINTF("H<sub><small>2</small></sub>",	MOL_HYDROGEN);
	MOL_PRINTF("He",							HELIUM);
	MOL_PRINTF("N",								ATOMIC_NITROGEN);
	MOL_PRINTF("O",								ATOMIC_OXYGEN);
	MOL_PRINTF("CH<sub><small>4</small></sub>", METHANE);
	MOL_PRINTF("NH<sub><small>3</small></sub>", AMMONIA);
	MOL_PRINTF("H<sub><small>2</small></sub>O", WATER_VAPOR);
	MOL_PRINTF("Ne",							NEON);
	MOL_PRINTF("N<sub><small>2</small></sub>",	MOL_NITROGEN);
	MOL_PRINTF("CO",							CARBON_MONOXIDE);
	MOL_PRINTF("NO",							NITRIC_OXIDE);
	MOL_PRINTF("O<sub><small>2</small></sub>",	MOL_OXYGEN);
	MOL_PRINTF("H<sub><small>2</small></sub>S", HYDROGEN_SULPHIDE);
	MOL_PRINTF("Ar",							ARGON);
	MOL_PRINTF("CO<sub><small>2</small></sub>", CARBON_DIOXIDE);
	MOL_PRINTF("N<sub><small>2</small></sub>O", NITROUS_OXIDE);
	MOL_PRINTF("NO<sub><small>2</small></sub>", NITROGEN_DIOXIDE);
	MOL_PRINTF("O<sub><small>3</small></sub>",	OZONE);
	MOL_PRINTF("SO<sub><small>2</small></sub>", SULPH_DIOXIDE);
	MOL_PRINTF("SO<sub><small>3</small></sub>", SULPH_TRIOXIDE);
	MOL_PRINTF("Kr",							KRYPTON);
	MOL_PRINTF("Xe",							XENON);
}

/*
 *	Table of scaled planet pictures
 */
 
void html_thumbnails(planet_pointer innermost_planet, 
					 FILE*	file, 
					 char*	system_name, 
					 char*	url_path,
					 char*	system_url,
					 char*	svg_url,
					 char*	file_name,
					 int	details,
					 int	terrestrials,
					 int	int_link,
					 int    do_moons,
					 int	graphic_format)
{
	planet_pointer 	planet;
	sun*			sun = innermost_planet->sun;
	int 			counter; 
	int				planet_count=0;
	int				terrestrials_seen = FALSE;
	planet_pointer 	moon;
	int 			moons; 
	
	for (planet=innermost_planet;
		 planet != NULL;
		 planet=planet->next_planet)
		planet_count++;
 
	fprintf (file,
	        "\n<p>\n\n"
	        "<table border=3 cellspacing=2 cellpadding=2 align=center "
	        	   "bgcolor='" BGTABLE "' width='90%%'>\n"
			"<tr><th colspan=2 bgcolor='" BGTABLE "' align=center>\n"
			"\t<font size='+2' color='" TXTABLE "'>");

	if (file_name[0] == '\0')
		fprintf (file, "%s", system_name);
	else
		fprintf (file, "<a href='%s'>%s</a>", 
						system_url, system_name);

	fprintf (file,
		    	"</font></th></tr>\n"
				"<tr bgcolor='" BGTABLE "'><td colspan=2>\n"
	        );

	if (graphic_format == gfSVG)
	{
		fprintf (file, 
				 "<object data='%s' type='image/svg+xml'\n"
				 "        width='100%%' height='100%%' border=1 style='background-color:white;'>\n",
					svg_url
				);
	}

	{
		fprintf (file,
					"<table border=0 cellspacing=0 cellpadding=3 bgcolor='" BGSPACE "' width='100%%'>\n"
				);
	
		fprintf (file,
					"<tr><td colspan=%d bgcolor='" BGHEADER "' align=center>\n"
						"\t<font size='+1'  color='" TXHEADER "'><b>%d Planets</b> </font>\n"
						"\t(<font size='-1' color='" TXHEADER "'>size proportional to Sqrt(Radius)</font>)\n"
					"</td></tr>\n"
					"<tr valign=middle bgcolor='" BGSPACE "'>\n"
					"<td bgcolor='" BGSPACE "'><img alt='Sun' src='%sref/Sun.gif' "
						"width=15 height=63 border=0></td>\n", 
				planet_count+2, planet_count, url_path);
				
		for (planet = innermost_planet, counter = 1;
			planet != NULL;
			planet = planet->next_planet, counter++)
		{
			int	ppixels = ((int)( sqrt(planet->radius / KM_EARTH_RADIUS) * 30.)) + 1;
			char *ptype = type_string (planet->type);
			char info[100];
			
			if (planet->type == tAsteroids)
				ppixels = (int)(25.0 + ( 5.0 * log ((planet->mass * SUN_MASS_IN_EARTH_MASSES) / 
													ASTEROID_MASS_LIMIT)));
			
			if (ppixels < 3)
				ppixels = 3;
			
			if ((planet->type == tGasGiant)
			 || (planet->type == tSubSubGasGiant)
			 || (planet->type == tSubGasGiant))
				sprintf(&info[0], "%s: %.1LfEM (c. %.0Lf&deg;)", 
						ptype, planet->mass * SUN_MASS_IN_EARTH_MASSES,
						planet->estimated_temp);
			else if (planet->type == tUnknown)
				sprintf(&info[0], "%s: %.1LfEM, %.2LfEM from gas (%.1Lf%c) Zone = %d", 
						ptype, planet->mass * SUN_MASS_IN_EARTH_MASSES,
						planet->gas_mass * SUN_MASS_IN_EARTH_MASSES,
						100.0 * (planet->gas_mass / planet->mass), '%',
						planet->orbit_zone);
			else
				sprintf(&info[0], "%s: %.2LfEM, %.2Lfg, %.1Lf&deg; Zone = %d", 
						ptype, planet->mass * SUN_MASS_IN_EARTH_MASSES, planet->surf_grav, 
						(planet->surf_temp - FREEZING_POINT_OF_WATER),
						planet->orbit_zone);
			
			fprintf (file,
				"\t<td bgcolor='" BGSPACE "' align=center><a href='%s#%d' title='#%d - %s'>"
					"<img alt='%s' src='%sref/%sPlanet.gif' width=%d height=%d border=0>"
					"</a>", 
				int_link ? "" : system_url,
				counter, counter, info, ptype, 
				url_path, ptype, 
				ppixels, ppixels);
	
			if ((planet->type == tTerrestrial)
			 || (planet->type == tWater)
			 || (breathability (planet) == BREATHABLE)
			 || ((planet->surf_pressure > 0.001)
			  && (planet->surf_temp > FREEZING_POINT_OF_WATER - 15)
			  && (planet->surf_temp < EARTH_AVERAGE_KELVIN + 15)))
				terrestrials_seen = TRUE;
	
			for (moon = planet->first_moon, moons=1;
				 do_moons && moon != NULL;
				 moon = moon->next_planet, moons++)
			{
				// DISPLAY THEM
				char *mtype = type_string (moon->type);
				int	mpixels = ((int)( sqrt(moon->radius / KM_EARTH_RADIUS) * 30.)) + 1;
	
				if ((moon->type == tGasGiant)
				 || (moon->type == tSubSubGasGiant)
				 || (moon->type == tSubGasGiant))
					sprintf(&info[0], "%s: %.1LfEM (c. %.0Lf&deg;)", 
							mtype, moon->mass * SUN_MASS_IN_EARTH_MASSES,
							moon->estimated_temp);
				else if (moon->type == tUnknown)
					sprintf(&info[0], "%s: %.1LfEM, %.2LfEM from gas (%.1Lf%c) Zone = %d", 
							mtype, moon->mass * SUN_MASS_IN_EARTH_MASSES,
							moon->gas_mass * SUN_MASS_IN_EARTH_MASSES,
							100.0 * (moon->gas_mass / moon->mass), '%',
							moon->orbit_zone);
				else
					sprintf(&info[0], "%s: %.2LfEM, %.2Lfg, %.1Lf&deg; Zone = %d", 
							mtype, moon->mass * SUN_MASS_IN_EARTH_MASSES, moon->surf_grav, 
							(moon->surf_temp - FREEZING_POINT_OF_WATER),
							moon->orbit_zone);
	
				fprintf (file,
					"\n\t\t<br><a href='%s#%d.%d' title='#%d.%d - %s'>"
						"<img alt='%s' src='%sref/%sPlanet.gif' width=%d height=%d border=0>"
						"</a>", 
					int_link ? "" : system_url,
					counter, moons, counter, moons, info, mtype, 
					url_path, mtype, mpixels, mpixels);
	
				if ((moon->type == tTerrestrial)
				 || (moon->type == tWater)
				 || (breathability (moon) == BREATHABLE)
				 || ((moon->surf_pressure > 0.001)
				  && (moon->surf_temp > FREEZING_POINT_OF_WATER - 15)
				  && (moon->surf_temp < EARTH_AVERAGE_KELVIN + 15)))
					terrestrials_seen = TRUE;
			}
			
			fprintf (file, "</td>\n");
		}
		
		fprintf (file, 
				 "<td bgcolor='" BGSPACE "' align=right valign=bottom>"
				 "<a href='%sref/Key.html'><font size='-3' color='" TXSPACE "'>See<br>Key</font></a></td>\n"
				 "</tr></table>\n",
				 url_path);
	}
	
	if (graphic_format == gfSVG)
	{
		fprintf (file, 
				 "</object>\n"
				);
	}
	
	fprintf (file, 
			 "</td></tr>\n");

/*
 *	Table of data on the star system
 */

	if (terrestrials && terrestrials_seen)
	{
		fprintf (file, "<tr><td colspan=2><table width='100%%'>");
		
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
						 "\n\t<tr><td align=right width='5%%'>"
						 "<a href='%s#%d'><small>#%d</small></a>"
						 "</td>\n\t\t<td><small>%s: </small>", 
						 int_link ? "" : system_url,
						 counter, counter, 
						 type_string(planet->type));
				
				print_description(file, "", planet, "");

				fprintf (file, "</td></tr>");
			}
			
			for (moon=planet->first_moon, moons=1;
				moon != NULL;
				moon=moon->next_planet, moons++)
			{
				if (((breathability (moon) == BREATHABLE) ||
					 ((moon->max_temp >= FREEZING_POINT_OF_WATER) &&
					  (moon->min_temp <= moon->boil_point))) &&
					(moon->type != tSubSubGasGiant))
				{
					fprintf (file,
 							 "\n\t<tr><td align=right width='5%%'>"
 							 "<a href='%s#%d.%d'><small>#%d.%d</small></a>"
 							 "</td>\n\t\t<td><small>%s: </small>", 
							 int_link ? "" : system_url,
							 counter, moons, counter, moons, 
							 type_string(moon->type));
					
					print_description(file, "", moon, "");
	
					fprintf (file, "</td></tr>");
				}
			}

			
		}

		fprintf (file, "</table></td></tr>\n");
	}
	
	if (details)
	{
		long double min_r_ecosphere = sqrt( sun->luminosity / 1.51 );
		long double max_r_ecosphere = sqrt( sun->luminosity / 0.48 );

		fprintf (file,
		        "<tr><td colspan=2 bgcolor='" BGHEADER "' align=center>"
		        	"<font size='+1' color='" TXHEADER "'><b>Stellar characteristics</b></font>"
		        "</td></tr>\n");
		fprintf (file,
		        "<tr><td>Stellar mass</td>\n"
		        "\t<td>%4.2Lf solar masses</td></tr>\n", 
				sun->mass);
		fprintf (file,
		        "<tr><td>Stellar luminosity</td>\n"
		        "\t<td>%4.2Lf</td></tr>\n",
				sun->luminosity);
		fprintf (file,
		        "<tr><td>Age</td>\n"
		        "\t<td>%5.3Lf billion years<br>"
				"(%5.3Lf billion left on main sequence)<br>",
			   (sun->age / 1.0E9),
			   (sun->life - sun->age) / 1.0E9);
		fprintf (file,
		        "<tr><td>Habitable ecosphere radius</td>\n"
		        "\t<td>%3.3Lf AU (%3.3Lf - %3.3Lf AU)</td></tr>\n",
				sun->r_ecosphere,
				min_r_ecosphere,
				max_r_ecosphere);
	}

	fprintf (file, "</table>\n<br clear=all>\n");
	fflush (file);
}

void html_thumbnail_totals(FILE *file)
{
	fprintf (file,
	        "\n<p>\n\n"
	        "<table border=3 cellspacing=2 cellpadding=2 align=center "
	        	   "bgcolor='" BGTABLE "'>\n"
		        "<tr><th colspan=2 bgcolor='" BGHEADER "' align=center>\n"
		        	"\t<font size='+1' color='" TXHEADER "'>"
		        	"<b>Summary</b></font></th></tr>\n"
	        );
	
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tEarthlike planets\n</td><td align=center>\n\t%d\n</td></tr>\n", total_earthlike);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tBreathable atmospheres\n</td><td align=center>\n\t%d\n</td></tr>\n", total_habitable);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tBreathable g range\n</td><td align=center>\n\t%4.2Lf -  %4.2Lf\n</td></tr>\n", 
			 min_breathable_g, 
			 max_breathable_g);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tTerrestrial g range\n</td><td align=center>\n\t%4.2Lf -  %4.2Lf\n</td></tr>\n", 
			 min_breathable_terrestrial_g,
			 max_breathable_terrestrial_g);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tBreathable pressure range\n</td><td align=center>\n\t%4.2Lf -  %4.2Lf\n</td></tr>\n", 
			 min_breathable_p, 
			 max_breathable_p);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tBreathable temp range\n</td><td align=center>\n\t%+.1Lf C -  %+.1Lf C\n</td></tr>\n", 
			 min_breathable_temp - EARTH_AVERAGE_KELVIN, 
			 max_breathable_temp - EARTH_AVERAGE_KELVIN);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tBreathable illumination range\n</td><td align=center>\n\t%4.2Lf -  %4.2Lf\n</td></tr>\n", 
			 min_breathable_l, 
			 max_breathable_l);
	fprintf (file, 
			"<tr bgcolor='" BGTABLE "'><td align=right>\n"
				"\tTerrestrial illumination range\n</td><td align=center>\n\t%4.2Lf -  %4.2Lf\n</td></tr>\n", 
			 min_breathable_terrestrial_l,
			 max_breathable_terrestrial_l);

	fprintf (file,
	        "</table>\n\n"
	        );
}


void html_decribe_planet(planet_pointer planet,
						 int			counter,
						 int			moons,
						 int 			do_gases, 
						 char*			url_path,
						 FILE*			file)
{
	char	planet_id[80];
	char	*typeString = type_string (planet->type);
	
	if (moons == 00)
		sprintf(planet_id, "%d", counter);
	else
		sprintf(planet_id, "%d.%d", counter, moons);
	
	fprintf (file,
			"<p>\n<a name='%s'></a><table border=3 cellspacing=2 cellpadding=2 align=center "
										 "bgcolor='" BGTABLE "' width='%d%%'>\n"
			"<colgroup span=1 align=left valign=middle>"
			"<colgroup span=2 align=left valign=middle>"
			"<tr><th colspan=3 bgcolor='" BGHEADER "' align=center>\n"
				"<font size='+2' color='" TXHEADER "'>%s #%s Statistics</font></th></tr>\n", 
			planet_id,
			(moons == 00) ? 95 : 90,
			(moons == 00) ? "Planet" : "Moon",
			planet_id);
	
	fprintf (file,
			"<tr><th>Planet type</th>"
			"<td colspan=2><img alt='%s' src='%sref/%s.gif' align=middle width=20 height=20>%s",
			typeString, 
			url_path, 
			typeString, 
			typeString);

	if ((int)planet->day == (int)(planet->orb_period * 24.0))
		fprintf (file, "<br>Tidally Locked 1 Face\n");
		
	if (planet->resonant_period)
		fprintf (file, "<br>Resonant Spin Locked\n");
	
	print_description(file, "<br>", planet, "");

	fprintf (file, "</td></tr>\n");
				
	fprintf (file,
		"<tr><th>Distance from primary star</th><td>%.2LG KM</td>"
		"<td>%5.3Lf AU</td></tr>\n",
			planet->a * KM_PER_AU,
			planet->a);
	fprintf (file,
			"<tr><th>Mass</th><td>%.2LGKg</td>"
			"<td>",
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
					"<table border=0 cellspacing=0 cellpadding=0 bgcolor='#000000' background='%sref/Atmosphere.gif' align=right>"
					"<tr align=right valign=bottom background='%sref/Atmosphere.gif'>"
					"<td width=50 height=50 align=right valign=bottom bgcolor='#000000' background='%sref/Atmosphere.gif'>"
					"<img src='%sref/Core.gif' alt='' width=%d height=%d>"
					"</td></tr></table>"
					"\n", 
					url_path, 
					url_path, 
					url_path,
					url_path,
					core_size,
					core_size
					);
		}
	}

	fprintf (file,
			"%5.3Lf Earth masses<br>",
			planet->mass * SUN_MASS_IN_EARTH_MASSES);

	if ((planet->dust_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006)
	 && (planet->gas_mass * SUN_MASS_IN_EARTH_MASSES >= 0.0006))
	{
		fprintf (file,
			"%5.3Lf Earth masses dust<br>"
			"%5.3Lf Earth masses gas<br>",
				planet->dust_mass * SUN_MASS_IN_EARTH_MASSES,
				planet->gas_mass * SUN_MASS_IN_EARTH_MASSES);
	}
	
	fprintf (file,
		"</td></tr>\n");

	if ((planet->type != tGasGiant) 
	 && (planet->type != tSubGasGiant) 
	 && (planet->type != tSubSubGasGiant))
	{
		long double	celsius = (planet->surf_temp - FREEZING_POINT_OF_WATER);
		
		fprintf (file,
				"<tr><th>Surface gravity</th>"
				"<td>%4.1Lf cm/sec<sup>2</sup></td>"
				"<td>%4.2Lf Earth gees</td></tr>\n",
					planet->surf_accel,
					planet->surf_grav);
		
		fprintf (file,
				 "<tr><th>Surface pressure</th><td>%5.0Lf millibars",
				planet->surf_pressure);
		
		fprintf (file,
				 "</td><td>%5.3Lf Earth atmospheres</td></tr>\n",
				 (planet->surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS));
		
		fprintf (file,
				"<tr><th>Surface temperature</th>"
				"<td>%5.1Lf&deg; Celcius"
				"<br>%5.1Lf&deg; Fahrenheit</td>"
				"<td rowspan=2 valign=top>%+4.1Lf&deg; C Earth temperature"
				"<br>%+4.1Lf&deg; F Earth temperature",
					celsius,
					32 + (celsius * 1.8),
					celsius - EARTH_AVERAGE_CELSIUS,
					((celsius - EARTH_AVERAGE_CELSIUS) * 1.8));

		
		if (planet->greenhs_rise > 0.1)
		{
			fprintf (file, 
				"<br>%+4.1Lf&deg; C greenhouse effect", 
					planet->greenhs_rise);

			if ((planet->greenhouse_effect) && (planet->surf_pressure > 0.0))
				fprintf (file, " (GH)");
		
		}
		
		fprintf (file,"</td></tr>\n");
		
		
		{
			fprintf (file, 
				"<tr><th>Normal temperature range</th>"
				"<td><center><table>\n");

			if (fabs(planet->high_temp - planet->max_temp) > 10 
			 || fabs(planet->low_temp - planet->min_temp) > 10)
			{
				fprintf (file, "\t<tr><th>Night</th><th></th><th>Day</th></tr>\n");
				
				fprintf (file, 
					"\t<tr><td>%5.1Lf&deg; C<br>%5.1Lf&deg; F</td>"
					"<td> - </td>",
						planet->low_temp - FREEZING_POINT_OF_WATER,
						32.0 + (1.8 * (planet->low_temp - FREEZING_POINT_OF_WATER)));

				fprintf (file, 
					"<td>%5.1Lf&deg; C<br>%5.1Lf&deg; F</td>"
					"</tr>\n",
						planet->high_temp - FREEZING_POINT_OF_WATER,
						32.0 + (1.8 * (planet->high_temp - FREEZING_POINT_OF_WATER)));
			}
			
			fprintf (file, "\t<tr><th>Min</th><th></th><th>Max</th></tr>\n");
				
			fprintf (file, 
				"\t<tr><td>%5.1Lf&deg; C<br>%5.1Lf&deg; F</td>"
				"<td> - </td>",
				planet->min_temp - FREEZING_POINT_OF_WATER,
				32.0 + (1.8 * (planet->min_temp - FREEZING_POINT_OF_WATER)));

			fprintf (file, 
				"<td>%5.1Lf&deg; C<br>%5.1Lf&deg; F</td>"
				"</tr>\n",
					planet->max_temp - FREEZING_POINT_OF_WATER,
					32.0 + (1.8 * (planet->max_temp - FREEZING_POINT_OF_WATER)));

		fprintf (file, 
			"</table></center></td></tr>\n");
		}
	}

	fprintf (file,
		"<tr><th>Equatorial radius</th>"
		"<td>%3.1Lf Km</td>"
		"<td>%.2LG Earth radii</td></tr>\n",
			planet->radius,
			planet->radius / KM_EARTH_RADIUS);
	fprintf (file,
		"<tr><th>Density</th>"
		"<td>%4.2Lf grams/cc</td>"
		"<td>%.2LG Earth densities</td></tr>\n",
			planet->density,
			planet->density / EARTH_DENSITY);
	fprintf (file,
		"<tr><th>Eccentricity of orbit</th><td>%5.3Lf</td>"
		"<td></td></tr>\n",
			planet->e);
	fprintf (file,
		"<tr><th>Escape Velocity</th><td>%4.1Lf Km/sec</td>"
		"<td></td></tr>\n",
			planet->esc_velocity / CM_PER_KM);
	fprintf (file,
		"<tr><th>Molecular weight retained</th><td>%4.1Lf and above</td>"
		"<td>",
			planet->molec_weight);
			
	list_molecules(file, planet->molec_weight);
	
	if (do_gases && (planet->gases > 0))
	{
		int	i;
		
		fprintf (file, "\n<table border=0 cellspacing=0 cellpadding=0>\n");
		
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
				fprintf (file, "<tr><th align=left>%s&nbsp;</th>"
							   "<td align=right>%4.1Lf%%&nbsp;</td>"
							   "<td align=right>%5.0Lf mb&nbsp;</td>"
							   "<td align=right>(ipp:%5.0Lf)</td>"
							   "<td align=right>&nbsp;%s</td></tr>\n",
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
		fprintf (file, "</table>\n");
	}
	
	fprintf (file, "</td></tr>\n");
	fprintf (file,
		"<tr><th>Axial tilt</th><td>%2.0Lf&deg;</td>"
		"<td></td></tr>\n",
			planet->axial_tilt);
	fprintf (file,
		"<tr><th>Planetary albedo</th><td>%5.2Lf</td>"
		"<td></td></tr>\n",
			planet->albedo);
	fprintf (file,
		"<tr><th>Exospheric Temperature</th><td>%6.2Lf&deg; K</td>"
		"<td>%+6.2Lf&deg; C Earth temperature</td></tr>\n",
			planet->exospheric_temp,
			planet->exospheric_temp - EARTH_EXOSPHERE_TEMP);
	fprintf (file,
		"<tr><th>Length of year</th>"
		"<td>%4.2Lf Earth days</td>"
		"<td>%4.2Lf Local days",
			planet->orb_period,
			(planet->orb_period*24) / planet->day);
	if (planet->orb_period > DAYS_IN_A_YEAR)
		fprintf (file,
			"<br>%4.2Lf Earth years",
			planet->orb_period / DAYS_IN_A_YEAR);
	fprintf (file, 
		"</td></tr>\n");
	fprintf (file,
		"<tr><th>Length of day</th><td>%4.2Lf hours</td>"
		"<td></td></tr>\n",
			planet->day);

	if ((planet->type != tGasGiant)
	 && (planet->type != tSubGasGiant) 
	 && (planet->type != tSubSubGasGiant))
	{
		fprintf (file,
		"<tr><th>Boiling point of water</th>"
		"<td>%3.1Lf&deg; Celcius"
		"<br>%3.1Lf&deg; Fahrenheit</td>"
		"<td></td></tr>\n",
				(planet->boil_point - FREEZING_POINT_OF_WATER),
				32 + ((planet->boil_point - FREEZING_POINT_OF_WATER) * 1.8));
		fprintf (file,
		"<tr><th>Hydrosphere percentage</th><td>%4.1Lf</td>"
		"<td></td></tr>\n",
				(planet->hydrosphere * 100.0));
		fprintf (file,
		"<tr><th>Cloud cover percentage</th><td>%4.1Lf</td>"
		"<td></td></tr>\n",
				(planet->cloud_cover * 100));
		fprintf (file,
		"<tr><th>Ice cover percentage</th><td>%4.1Lf</td>"
		"<td></td></tr>\n",
				(planet->ice_cover * 100));
	}

	fprintf (file,
		"</table>\n\n<p>\n<br>\n\n");
}


void html_describe_system(planet_pointer 	innermost_planet, 
						  int 				do_gases, 
						  char*				url_path,
						  FILE*				file)
{
	planet_pointer 	planet;
	int 			counter; 
	planet_pointer 	moon;
	int 			moons; 
	
	/*
	 *	System summary
	 */
	 
	fprintf (file,
	        "\n<table border=3 cellspacing=2 cellpadding=2 align=center bgcolor='" BGTABLE "' width='90%c'>\n"
			"<tr><th colspan=7 bgcolor='" BGHEADER "' align=center>\n"
		        	"<font size='+2' color='" TXHEADER "'>Planetary Overview</font></th></tr>\n\n"
			"<tr align=center>\n"
			"	<th>#</th><th colspan=3>Type</th><th>Dist.</th><th>Mass</th><th>Radius</th>\n"
			"</tr>\n", '%');

	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		char	*typeString = type_string (planet->type);
		
		fprintf (file,
	        "<tr align=right>\n"
				"\t<td><a href='#%d'>%d</a></td>\n"
				"\t<td align=center><img alt='%s' src='%sref/%s.gif'></td>\n"
				"\t<td colspan=2>%s</td>\n"
				"\t<td>%7.3Lf  AU</td>\n"
				"\t<td>%8.3Lf EM</td>\n"
				"\t<td>%8.3Lf ER</td>"
				"</tr>\n",
				counter, counter, 
			    typeString, 
			    url_path, 
			    typeString, 
			    typeString, 
				planet->a, 
				planet->mass * SUN_MASS_IN_EARTH_MASSES,
				planet->radius / KM_EARTH_RADIUS);
		for (moon=planet->first_moon, moons=1;
			moon != NULL;
			moon=moon->next_planet, moons++)
		{
			char	*typeString = type_string (moon->type);

			fprintf (file,
				"<tr align=right>\n"
					"\t<td></td>\n"
					"\t<td align=center><a href='#%d.%d'>%d.%d</a></td>\n"
					"\t<td align=center><img alt='%s' src='%sref/%s.gif'></td>\n"
					"\t<td>%s</td>\n"
					"\t<td>%7.3Lf  AU</td>\n"
					"\t<td>%8.3Lf EM</td>\n"
					"\t<td>%8.3Lf ER</td>"
					"</tr>\n",
					counter, moons, counter, moons, 
					typeString, 
					url_path, 
					typeString, 
					typeString, 
					moon->a, 
					moon->mass * SUN_MASS_IN_EARTH_MASSES,
					moon->radius / KM_EARTH_RADIUS);
		}

	}
	fprintf (file,
	        "</table>\n<br clear=all>\n");
	
	/*
	 *	Tables for individual planets
	 */
	 
	for (planet=innermost_planet, counter=1;
		planet != NULL;
		planet=planet->next_planet, counter++)
	{
		html_decribe_planet(planet, counter, 0, do_gases, url_path, file);

		for (moon=planet->first_moon, moons=1;
			moon != NULL;
			moon=moon->next_planet, moons++)
		{
			html_decribe_planet(moon, counter, moons, do_gases, url_path, file);
		}
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
