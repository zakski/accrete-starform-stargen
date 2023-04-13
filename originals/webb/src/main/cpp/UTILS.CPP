#include <math.h>
#include <stdlib.h>

#include "fctn.h"

/*----------------------------------------------------------------------*/
/*  This function returns a random real number between the specified    */
/* inner and outer bounds.                                              */
/*----------------------------------------------------------------------*/
/*
double random_number(double inner, double outer)
{
	  double range;

	  range = outer - inner;
	  return((((double)rand()) / (double)(RAND_MAX)) * range + inner);
} */


/*----------------------------------------------------------------------*/
/*   This function returns a value within a certain variation of the    */
/*   exact value given it in 'value'.                                   */
/*----------------------------------------------------------------------*/

/*double about (double value, double variation)
{
	  return(value + (value * random_number(-variation,variation)));
}

double random_eccentricity ()
{
	  return(1.0 - pow(random_number(0.0, 1.0),ECCENTRICITY_COEFF));
}*/
