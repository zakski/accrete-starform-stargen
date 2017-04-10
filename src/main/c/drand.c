/* drand48.c
Random number generator between 0 and 1.
Link this program of a program requires drand48()
if there is no drand48() in stdlib.h of your OS.
*/
#include <stdlib.h>

#define C 16807
#define A 2147483647.0
double drand48();
void srand48(long int);
double yz;

void srand48(long int seed)
{
yz = (double)seed;
}

double drand48()
{
long int ki;
double uu;
ki=(C* yz)/A;
yz=C* yz-ki*A;
uu=yz/(A-1);
return uu;
}