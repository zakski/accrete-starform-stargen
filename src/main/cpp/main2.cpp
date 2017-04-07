// ACCRETE revision history:
// mod  0: rewritten for C++, added UWP info and prompts for star info
// mod  1: added support for user-defined mainworld UWP

#include <ctype.h>
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

int UWP2int(char c)
{
	if(isdigit(c)) return c-'0';
	else if(isalpha(c)) return (toupper(c))-'A'+10;
	else return 0;
}

void getMainworldInfo(int& diam, int& atm, int&hyd)
{
	printf("Enter world UWP info, or leave blank for a fully random system.\nUse the format ### for the UWP (diam,atm,hyd: eg 867): ");
	char buf[16];
	gets(buf);
	if(!buf[0])
	{
   	diam=atm=hyd=-1;
	}
	else
	{
		diam=UWP2int(buf[0]);
		atm=UWP2int(buf[1]);
		hyd=UWP2int(buf[2]);
	}
}

void main(int argc, char **argv)
{
	randomize();
	double sMass, sLuminosity;
	int diam, atm, hyd;
	if(argc>2)
	{
		sMass=atof(argv[1]);
		sLuminosity=atof(argv[2]);
		if(argc==4)
		{
			diam=UWP2int(argv[3][0]);
			atm=UWP2int(argv[3][1]);
			hyd=UWP2int(argv[3][2]);
		}
		else
			diam=atm=hyd=-1;
	}
	else
	{
		getStellarInfo(sMass, sLuminosity);
		getMainworldInfo(diam,atm,hyd);
	}

	if(diam==-1 || atm==-1 || hyd==-1) diam=atm=hyd=-1;

	if(diam>-1) printf("Main world UWP: %X%X%XXXX\n",diam,atm,hyd);
	else printf("Creating main world.\n");

	starSystem sys(sMass, sLuminosity);

	sys.make(diam,atm,hyd);

	sys.display();
}