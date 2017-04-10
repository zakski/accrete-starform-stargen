#include	<stdio.h>
#include	<string.h>
#include        <math.h>

#ifdef MSDOS
#include        <stddef.h>
#include        <malloc.h>
#include	<stdlib.h>
#include        <float.h>
#endif

#include	"structs.h"
#include	"const.h"

#include "propert.h"
#include "enviro.h"
#include "data.h"

#define	MAX_EXP_DIGS	3
#define	MAX_MAN_DIGS	20

static char OP[] = "(";
static char CP[] = ")";

typedef struct Temp_s Temp;
struct Temp_s
{
  double high;
  double low;
  double max;
  double min;
};

char *
engineer_notation(double d, int p)
{
  static char mansign;
  static char expsign;
  static char output[1 + MAX_MAN_DIGS + 1 + 1 + MAX_EXP_DIGS + 1];
  double      mantissa;
  int         exponent;

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
    mantissa = d / pow(10.0, (double)exponent);
    if (exponent < 0)
      exponent = -exponent;
    while (exponent % 3 != 0)
    {
      mantissa *= 10.0;
      p--;
      if (expsign == '-')
	++exponent;
      else
	--exponent;
    }
  }
  sprintf(output, "%c%*.*fe%c%*.*d", mansign, p, p, mantissa,
	  expsign, MAX_EXP_DIGS, MAX_EXP_DIGS, exponent);
  return (output);
}

void 
chart_system(planet_pointer first_planet)
{
  first_planet = first_planet;
}

double
local_bp(double bp_at_stp, double surf_pressure)
{
  volatile double surface_pressure_in_bars;
  double      bp;

  surface_pressure_in_bars = surf_pressure / MILLIBARS_PER_BAR;
  bp = 1.0 / (log(surface_pressure_in_bars + 0.001) / -5050.5 + 1.0 / 373);
  bp /= 373;
  bp *= bp_at_stp;
  return bp;
}

/* function for 'soft limiting' temperatures */

double lim(double x)
{
  return x / sqrt(sqrt(1 + x*x*x*x));
}

double
soft(double v, double max, double min)
{
  double dv = v - min;
  double dm = max - min;
  return (lim(2*dv/dm-1)+1)/2 * dm + min;
}

  Temp
get_temp_range(planet_pointer planet)
{
  double pressmod = 1 / sqrt(1 + 20 * planet->surf_pressure/1000.0);
  double ppmod    = 1 / sqrt(10 + 5 * planet->surf_pressure/1000.0);
  double tiltmod  = cos(planet->axial_tilt * PI/180) * pow(1 + planet->e, 2);
  double daymod   = 1 / (200/planet->day + 1);
  double mh = pow(1 + daymod, pressmod);
  double ml = pow(1 - daymod, pressmod);
  double hi = mh * planet->surf_temp;
  double lo = ml * planet->surf_temp;
  double sh = hi + pow((100+hi) * tiltmod, sqrt(ppmod));
  double wl = lo - pow((150+lo) * tiltmod, sqrt(ppmod));
  double max = planet->surf_temp + sqrt(planet->surf_temp) * 10;
  double min = planet->surf_temp / sqrt(planet->day + 24);
  Temp t;

  if (lo < min) lo = min;
  if (wl < 0)   wl = 0;

  t.high = soft(hi, max, min);
  t.low  = soft(lo, max, min);
  t.max  = soft(sh, max, min);
  t.min  = soft(wl, max, min);
  return t;
}

void
text_list_stuff(double temp, double min_weight, double pressure,
		double orbital_radius, double escape_vel, double star_age)
{
  Property   *stuff[200];
  double      amount[200];
  char        buff[200*5];
  int         n;
  int         i;

  temp += 273.15;
  propFindLiquidAtTemp(buff, temp);
  propSortByMelt(buff);
  n = propMakeVector(buff, stuff, 200);
  for (i = 0; i < n; i++)
  {
    double      bp = local_bp(stuff[i]->boil, pressure);

    if (stuff[i]->boil > 0 && bp < temp)
    {
      memmove(&stuff[i], &stuff[i + 1], sizeof(stuff[i]) * (n - i));
      n--;
      i--;
    }
  }
  if (n > 0)
  {
    printf("   liquids at surface:\n");
    for (i = 0; i < n; i++)
    {
      if (stuff[i]->melt < 0)
      {
	printf("\t\t\t\t%-12s\n", stuff[i]->name);
      }
      else if (stuff[i]->boil <= 0)
      {
	printf("\t\t\t\t%-12s melts at %-4.0f\n",
	       stuff[i]->name, stuff[i]->melt - 273.15);
      }
      else
      {
	printf("\t\t\t\t%-12s melts at %-4.0f  boils at %.0f\n",
	       stuff[i]->name, stuff[i]->melt - 273.15,
	       local_bp(stuff[i]->boil, pressure) - 273.15);
      }
    }
  }
  propFindGasAtTemp(buff, temp);
  propSortByAbundance(buff);
  propSortReverse(buff);
  n = propMakeVector(buff, stuff, 200);
  if (pressure > 0)
  {
    double      totamount = 0;

    for (i = 0; i < n; i++)
    {
      if (stuff[i]->weight < min_weight)
      {
	memmove(&stuff[i], &stuff[i + 1], sizeof(stuff[i]) * (n - i));
	n--;
	i--;
      }
      else
      {
	double      vrms = rms_vel(stuff[i]->weight, orbital_radius);
	double      pvrms = pow(1 / (1 + vrms / escape_vel), star_age / 1e9);
	double      P = pressure / 1000;

	amount[i] = /* stuff[i]->abunde */ stuff[i]->abunds;
	amount[i] *= pvrms;
	if (strcmp(stuff[i]->symbol, "O") == 0 && star_age > 2e9 &&
	    temp > 270 && temp < 400)
	{
	  amount[i] *= pow(1 / (1 + stuff[i]->reactivity), 
			   sqrt(sqrt(star_age/2e9)) * (0.7 + P/2));
	}
	else if (strcmp(stuff[i]->symbol, "Ar") == 0)
	{
	  amount[i] = stuff[i]->abunde * pvrms * star_age/4e9;
	}
	else
	{
	  amount[i] *= pow(1 / (1 + stuff[i]->reactivity), 
			   star_age/2e9 * (0.7 + P));
	}
	amount[i] *= (1 - min_weight / stuff[i]->weight);
	totamount += amount[i];
      }
    }
    if (n > 0 && pressure > 0)
    {
      printf("   gasses in atmosphere:\n");
      for (i = 0; i < n; i++)
      {
	if (100 * amount[i] / totamount > 0.05)
	  printf("\t\t\t\t%-16s %4.1f%%  PP %6.1f mb\n",
		 stuff[i]->name,
		 100 * amount[i] / totamount,
		 pressure * amount[i] / totamount);
      }
    }
  }
}

void
text_describe_planet(char *start, planet_pointer node1)
{
  start = start;
  if (node1->gas_giant)
    printf("*gas giant*\n");
  else
    printf("\n");
  if (node1->resonant_period)
  {
    if ((int)node1->day == (int)(node1->orb_period * 24.0))
      printf("   Planet is tidally locked with one face to primary.\n");
    else
      printf("   Planet's rotation is in a resonant spin lock with primary.\n");
  }
  if (node1->a < 0.01)
    printf("   Distance from primary:\t%8.0f\tkm\n", node1->a * KM_PER_AU);
  else
    printf("   Distance from primary:\t%5.3f\tAU\n", node1->a);
  if (node1->mass * SUN_MASS_IN_EARTH_MASSES < 0.01)
    printf("   Mass:\t\t\t1/%0.4g\tEarth masses\n",
	   1.0 / (SUN_MASS_IN_EARTH_MASSES * node1->mass));
  else
    printf("   Mass:\t\t\t%5.3f\tEarth masses\n",
	   node1->mass * SUN_MASS_IN_EARTH_MASSES);
  printf("   Equatorial radius:\t\t%3.1f\tkm\n", node1->radius);
  printf("   Density:\t\t\t%5.3f\tgrams/cc\n", node1->density);
  printf("   Eccentricity of orbit:\t%5.3f\n", node1->e);
  if (!(node1->gas_giant))
  {
    printf("   Surface gravity:\t\t%4.2f\tEarth gees\n", node1->surf_grav);
    printf("   Surface pressure:\t\t%5.3f\tEarth atmospheres",
	   (node1->surf_pressure / 1000.0));
    if ((node1->greenhouse_effect) && (node1->surf_pressure > 0.0))
      printf("    GREENHOUSE EFFECT\n");
    else
      printf("\n");
    printf("   Surface temperature:\t\t%4.2f\tdegrees Celcius\n",
	   (node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE));
    {
      Temp t = get_temp_range(node1);
      if (fabs(t.high - t.max) > 10 || fabs(t.low - t.min) > 10)
      {
	printf("   Normal daytime temperature:\t%4.2f\tdegrees Celcius\n",
	    t.high - KELVIN_CELCIUS_DIFFERENCE);
	printf("   Normal night temperature:\t%4.2f\tdegrees Celcius\n",
	    t.low - KELVIN_CELCIUS_DIFFERENCE);
      }
      printf("   Maximum temperature:   \t%4.2f\tdegrees Celcius\n",
	     t.max - KELVIN_CELCIUS_DIFFERENCE);
      printf("   Minimum temperature:   \t%4.2f\tdegrees Celcius\n",
	     t.min - KELVIN_CELCIUS_DIFFERENCE);
    }
  }
  printf("   Escape Velocity:\t\t%4.2f\tkm/sec\n",
	 node1->esc_velocity / CM_PER_KM);
  printf("   Molecular weight retained:\t%4.2f and above\n",
	 node1->molec_weight);
  printf("   Surface acceleration:\t%4.2f\tcm/sec2\n", node1->surf_accel);
  printf("   Axial tilt:\t\t\t%d\tdegrees\n", node1->axial_tilt);
  printf("   Planetary albedo:\t\t%5.3f\n", node1->albedo);
  printf("   Length of year:\t\t%4.2f\tdays\n", node1->orb_period);
  printf("   Length of day:\t\t%4.2f\thours\n", node1->day);
  if (!(node1->gas_giant))
  {
    printf("   Boiling point of water:\t%3.1f\tdegrees Celcius\n",
	   (node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
    printf("   Hydrosphere percentage:\t%4.2f\n",
	   (node1->hydrosphere * 100.0));
    printf("   Cloud cover percentage:\t%4.2f\n",
	   (node1->cloud_cover * 100));
    printf("   Ice cover percentage:\t%4.2f\n", (node1->ice_cover * 100));
    text_list_stuff(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE,
		    node1->molec_weight,
		    node1->surf_pressure,
		    node1->a,
		    node1->esc_velocity,
		    star_age);
  }
}

void 
text_describe_system(planet_pointer first_planet)
{
  planet_pointer node1;
  int         counter;

  printf("                         SYSTEM  CHARACTERISTICS\n");
  printf("Stellar mass: %4.2f solar masses\n", star_mass_r);
  printf("Stellar radius: %4.2f solar radii\n", star_radius_r);
  printf("Stellar luminosity: %4.2f\n", star_lum_r);

  printf("Stellar temperature: %g K\n", star_temp);
  printf("Stellar class: %s\n", star_class);

  printf("Age: %5.3f billion years  (%5.3f billion left on main sequence)\n",
	 (star_age / 1.0E9), (main_seq_life - star_age) / 1.0E9);
  printf("Habitable ecosphere radius: %3.3f AU\n", r_ecosphere);
  printf("\n");
  printf("Planets present at:\n");
  for (node1 = first_planet, counter = 1;
       node1 != NULL;
       node1 = node1->next_planet, counter++)
  {
    const char *type = "";

    if (node1->gas_giant)
      type = "gas giant";
    else if (node1->surf_pressure < 100)
      type = "no atmosphere";
    else if (node1->greenhouse_effect)
      type = "greenhouse";
    else if (node1->surf_pressure > 2000)
      type = "high pressure";
    else if (node1->surf_grav > 2)
      type = "heavy";
    else if (node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE < 0)
      type = "cold";
    else if (node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE > 30)
      type = "hot";
    printf("%d\t%7.3f AU\t%s\n",
	   counter, node1->a, type);
  }
  printf("\n\n\n");
  for (node1 = first_planet, counter = 1;
       node1 != NULL;
       node1 = node1->next_planet, counter++)
  {
    planet_pointer moon;
    int         num = 0;

    printf("Planet %d\t", counter);
    text_describe_planet("", node1);
    for (moon = node1->first_moon; moon; moon = moon->next_planet)
    {
      num++;
      printf("\n  Moon %d-%d\t", counter, num);
      text_describe_planet("  ", moon);
    }
    printf("\n\n");
  }
}

void 
lisp_describe_planet(char *opar, char *bstr, planet_pointer node1)
{
  printf("  %s boolean:\n", bstr);
  printf("  %sis-gas-giant %d%s\n", opar, node1->gas_giant, CP);
  printf("  %s orbital statistics:\n", bstr);
  printf("  %smean-orbit-radius %s%s ; km\n",
	 opar, engineer_notation(node1->a * KM_PER_AU, 6), CP);
  printf("  %sorbit-eccentricity %s%s\n",
	 opar, engineer_notation(node1->e, 6), CP);
  printf("  %saxial-tilt %d%s ; degrees\n",
	 opar, node1->axial_tilt, CP);
  printf("  %sorbital-period %s%s ; Earth days\n",
	 opar, engineer_notation(node1->orb_period, 6), CP);
  printf("  %srotation-period %s%s ; Earth hours\n",
	 opar, engineer_notation(node1->day, 6), CP);
  printf("  %sis-resonant %d%s\n", opar, node1->resonant_period, CP);
  printf("  %s planetary measurements:\n", bstr);
  printf("  %smass %s%s ; kg\n",
	 opar, engineer_notation(node1->mass * SOLAR_MASS_IN_GRAMS / 1000.0, 6), CP);
  printf("  %sequatorial-radius %s%s ; km\n",
	 opar, engineer_notation(node1->radius, 6), CP);
  printf("  %sdensity %s%s ; g/cm3\n",
	 opar, engineer_notation(node1->density, 6), CP);
  printf("  %s planetary environment:\n", bstr);
  printf("  %sescape-velocity %s%s ; km/sec\n",
	 opar, engineer_notation(node1->esc_velocity / CM_PER_KM, 6), CP);
  printf("  %smin-molecular-weight-retained %s%s\n",
	 opar, engineer_notation(node1->molec_weight, 3), CP);
  printf("  %ssurface-acceleration %s%s ; cm/sec2\n",
	 opar, engineer_notation(node1->surf_accel, 6), CP);
  if (!node1->gas_giant)
  {
    printf("  %ssurface-gravity %s%s ; Earth gees\n",
	   opar, engineer_notation(node1->surf_grav, 3), CP);
    printf("  %sh2o-boils %s%s ; degrees celcius\n",
	   opar,
     engineer_notation(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE, 3),
	   CP);
    printf("  %ssurface-pressure %s%s ; Earth atmospheres\n",
	   opar, engineer_notation(node1->surf_pressure / 1000.0, 3), CP);
    if (node1->greenhouse_effect && node1->surf_pressure > 0.0)
      printf("  %sgreenhouse 1%s\n", opar, CP);
    else
      printf("  %sgreenhouse 0%s\n", opar, CP);
    printf("  %ssurface-temperature %s%s ; degrees celcius\n",
	   opar,
      engineer_notation(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE, 3),
	   CP);
    printf("  %shydrosphere %s%s\n",
	   opar, engineer_notation(node1->hydrosphere, 3), CP);
    printf("  %scloud-cover %s%s\n",
	   opar, engineer_notation(node1->cloud_cover, 3), CP);
    printf("  %sice-cover %s%s\n",
	   opar, engineer_notation(node1->ice_cover, 3), CP);
  }
  printf("  %salbedo %s%s\n",
	 opar, engineer_notation(node1->albedo, 3), CP);
}

void 
lisp_describe_system(planet_pointer first_planet)
{
  planet_pointer node1;
  int         counter;

  printf("%splanetary-system\n", OP);
  printf(" %ssun\n", OP);
  printf("  %smass %s%s ; kg\n",
	 OP,
   engineer_notation(star_mass_r * SOLAR_MASS_IN_GRAMS / 1000.0, 6),
	 CP);
  printf("  %sradius %s%s ; km\n",
	 OP,
	 engineer_notation(star_radius_r
			   * SOLAR_RADIUS_IN_METRES / 1000.0, 6),
	 CP);
  printf("  %stemperature %.0f%s ; K\n",
	 OP, star_temp, CP);
  printf("  %sluminosity %s%s ; * SOL luminosity\n",
	 OP, engineer_notation(star_lum_r, 6), CP);
  printf("  %slifetime %s%s ; years\n",
	 OP, engineer_notation(main_seq_life, 6), CP);
  printf("  %scurrent-age %s%s ; years\n",
	 OP, engineer_notation(star_age, 6), CP);
  printf("  %secosphere-radius %s%s ; km\n",
	 OP, engineer_notation(r_ecosphere * KM_PER_AU, 6), CP);
  printf(" %s\n", CP);
  for (node1 = first_planet, counter = 1;
       node1 != NULL;
       node1 = node1->next_planet, counter++)
  {
    planet_pointer moon;
    int         num = 0;

    printf(" %splanet ; #%d\n",
	   OP, counter);
    lisp_describe_planet(OP, ";", node1);
    printf(" %s\n", CP);
    for (moon = node1->first_moon; moon; moon = moon->next_planet)
    {
      num++;
      printf(" %smoon ; #%d-%d\n",
	     OP, counter, num);
      lisp_describe_planet("(", ";", moon);
      printf(" %s\n", CP);
    }
  }
  printf("%s\n", CP);
}

void 
display_system(planet_pointer first_planet)
{
  if (sf_f_graphics)
    chart_system(first_planet);
  else if (sf_f_lisp)
    lisp_describe_system(first_planet);
  else
    text_describe_system(first_planet);
}
