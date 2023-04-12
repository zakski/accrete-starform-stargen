#include <stdio.h>

#include "system.h"

void getStellarInfo(double &mass, double &lum)
{
	char str[16];

	printf("Enter stellar mass (Sol = 1.0)      : ");
	mass=atof(gets(str));
	printf("Enter stellar luminosity (Sol = 1.0): ");
	lum=atof(gets(str));
}

void main(int argc, char **argv)
{
	randomize();
	double sMass, sLuminosity;
	if(argc==3)
	{
		sMass=atof(argv[1]);
      sLuminosity=atof(argv[2]);
	}
	else getStellarInfo(sMass, sLuminosity);

	starSystem sys(sMass, sLuminosity);

	sys.make();

   sys.display();
}