#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"const.h"
#include	"utils.h"

/*----------------------------------------------------------------------*/
/*	This function returns a random real number between the specified	*/
/* inner and outer bounds.												*/
/*----------------------------------------------------------------------*/

long double random_number(long double inner, long double outer)
{
	long double range;
	
	range = outer - inner;
	return((((long double)rand()) / (long double)(RAND_MAX)) * range + inner);
}


/*----------------------------------------------------------------------*/
/*	 This function returns a value within a certain variation of the	*/
/*	 exact value given it in 'value'.									*/
/*----------------------------------------------------------------------*/

long double about(long double value, long double variation)
{
	return(value + (value * random_number(-variation,variation)));
}

long double random_eccentricity(long double ecc_coef)
{
	long double	e;
	
	//seb	e = 1.0 - pow(random_number(0.0, 1.0), ECCENTRICITY_COEFF);
	e = 1.0 - pow(random_number(0.0, 1.0), ecc_coef);

	if (e > .99)	// Note that this coresponds to a random
		e = .99;	// number less than 10E-26
					// It happens with GNU C for -S254 -W27
	return(e);
}
// seb (for polar axis inclination, aka obliquity)
// gaussian (normal) random number function
// using Box-Muller transform
// ref: http://en.literateprograms.org/Box-Muller_transform_%28C%29

long double gaussian(long double sigma)
{
  long double x,y,r;
    do {
      x = random_number(-1.0,1.0);
      y = random_number(-1.0,1.0);
      r = x*x+y*y;
	}
    while (r == 0 || r > 1.0);
  r = sigma * sqrt (-2.0*log(r)/r);
  return (x*r);
}

  long double Exponential(long double m)
/* =========================================================
 *      Generator         Range (x)     Mean         Variance
 *      Exponential(m)    x > 0         m            m*m
 * Returns an exponentially distributed positive real number. 
 * NOTE: use m > 0.0
 * =========================================================
 */
{
  return (-m * log(1.0 - random_number(0.0,1.0)));
}


   long Poisson(long double m)
/* ================================================== 
 *      Generator         Range (x)     Mean         Variance
 *      Poisson(m)        x = 0,...     m            m
 * Returns a Poisson distributed non-negative integer. 
 * NOTE: use m > 0
 * ==================================================
 */
{ 
  long double t = 0.0;
  long  x = 0;

  while (t < m) {
    t += Exponential(1.0);
    x++;
  }
  return (x - 1);
}

long double quad_trend(long double a, long double b, long double c, long double x)
{
  return (a * pow2(x)) + (b * x) + c;
}

long double ln_trend(long double a, long double b, long double x)
{
  return a + (b * log(x));
}

long double gen_radii(long double a, long double b, long double c, long double d, long double e, long double f, long double mass, long double fraction)
{
  return (((a * fraction) + b) * pow(log10(mass), 2.0)) + (((c * fraction) + d) * log10(mass)) + ((e * fraction) + f);
  /*long double log_of_mass = (long double)log(mass);
  long double a_times_fraction = a * fraction;
  long double c_times_fraction = c * fraction;
  long double e_times_fraction = e * fraction;
  long double a2 = a_times_fraction + b;
  long double b2 = c_times_fraction + d;
  long double c2 = e_times_fraction + f;
  long double log_of_mass_squared = log_of_mass * log_of_mass;
  long double first_part = a2 * log_of_mass_squared;
  long double second_part = b2 * log_of_mass;
  long double first_two_parts = first_part + second_part;
  fprintf (stderr, "mass: %5.3Lf a: %5.3Lf b: %5.3Lf c: %5.3Lf mass2: %5.3Lf first_part: %5.3Lf second_part: %5.3Lf first_two_parts: %5.3Lf\n", mass, a2, b2, c2, log_of_mass_squared, first_part, second_part, first_two_parts);
  return first_two_parts + c2;*/
}
