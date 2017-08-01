#include        <stdlib.h>
#include	<math.h>
#include	"const.h"

/*----------------------------------------------------------------------*/
/*  This function returns a random real number between the specified    */
/* inner and outer bounds.                                              */
/*----------------------------------------------------------------------*/

double
random_number(double inner, double outer)
{
  unsigned long r = rand();
  double rr = (double)r / ((double)RAND_MAX);
  double range = outer - inner;
  return (rr * range + inner);
}

/*----------------------------------------------------------------------*/
/*   This function returns a value within a certain variation of the    */
/*   exact value given it in 'value'.                                   */
/*----------------------------------------------------------------------*/

double
about(double value, double variation)
{
  return (value + (value * random_number(-variation, variation)));
}

double
random_eccentricity(void)
{
  return (1.0 - pow(random_number(0.000001, 1.0), ECCENTRICITY_COEFF));
}
