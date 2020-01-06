#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "const.h"
#include "structs.h"

/*  These are all of the global variables used during accretion declared in main.c  */
extern float anum;
extern planet_pointer planet_head;
extern double stellar_mass_ratio, stellar_luminosity_ratio, main_seq_life;
extern double age, r_ecosphere, r_greenhouse, radians_per_rotation;
extern int spin_resonance;

void display_system()
{
     planet_pointer node1;
     int counter;
     char word[(10)+1];

     FILE *f;
     f = fopen("New.System", "w");

     fprintf(f,"                         SYSTEM  CHARACTERISTICS\n");
     fprintf(f,"Mass of central star (in solar masses): %4.2lf\n", stellar_mass_ratio);
     fprintf(f,"Luminosity of central star (relative to the sun): %5.2lf\n",stellar_luminosity_ratio);
     fprintf(f,"Total main sequence lifetime (in million yrs): %10.3lf\n", (main_seq_life / 1.0E6));
     fprintf(f,"Current age of stellar system (in million yrs): %10.3lf\n",(age / 1.0E6));
     fprintf(f,"Radius of habitable ecosphere (AU): %3.3lf\n",r_ecosphere);
     node1 = planet_head;
     counter = 1;
     while (node1 != NULL)
     {
	  fprintf(f,"Planet #%d:\n",counter);
	  if (node1->gas_giant)
	       fprintf(f,"Gas giant...\n");
	  if (node1->resonant_period)
	       fprintf(f,"In resonant period with primary.\n");
	  fprintf(f,"   Distance from primary star (in A.U.): %7.3lf\n",node1->a);
	  fprintf(f,"   Eccentricity of orbit: %5.3lf\n",node1->e);
	  fprintf(f,"   Mass (in Earth masses): %7.3lf\n",node1->mass * EARTH_MASSES_PER_SOLAR_MASS);
	  fprintf(f,"   Equatorial radius (in Km): %10.1lf\n",node1->radius);
	  fprintf(f,"   Density (in g/cc): %6.3lf\n",node1->density);
	  fprintf(f,"   Escape Velocity (in km/sec): %5.2lf\n",node1->escape_velocity / CM_PER_KM);
	  fprintf(f,"   Smallest molecular weight retained: %5.2lf\n",node1->molecule_weight);
	  fprintf(f,"   Surface acceleration (in cm/sec2): %6.2lf\n",node1->surface_accel);
	  if (!(node1->gas_giant))
	  {
	       fprintf(f,"   Surface Gravity (in Earth gees): %5.2lf\n",node1->surface_grav);
	       fprintf(f,"   Boiling point of water (celcius): %4.1lf\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
	       fprintf(f,"   Surface Pressure (in atmospheres): %5.3lf",(node1->surface_pressure / 1000.0));
	       if ((node1->greenhouse_effect) && (node1->surface_pressure > 0.0))
		    fprintf(f,"     RUNAWAY GREENHOUSE EFFECT\n");
	       else
		    fprintf(f,"\n");
	       fprintf(f,"   Surface temperature (Celcius): %4.2lf\n",(node1->surface_temp - KELVIN_CELCIUS_DIFFERENCE));
	       fprintf(f,"   Hydrosphere percentage: %6.2lf\n",(node1->hydrosphere * 100.0));
	       fprintf(f,"   Cloud cover percentage: %6.2lf\n",(node1->cloud_cover * 100));
	       fprintf(f,"   Ice cover percentage: %6.2lf\n",(node1->ice_cover * 100));
	  }
	  fprintf(f,"   Axial tilt (in degrees): %d\n",node1->axial_tilt);
	  fprintf(f,"   Planetary albedo: %4.3lf\n",node1->albedo);
	  fprintf(f,"   Length of year (in days): %7.2lf\n",node1->orbital_period);
	  fprintf(f,"   Length of day (in hours): %7.2lf\n",node1->day);
	  counter++;
	  node1 = node1->next_planet;
     }
        fclose(f);
}
