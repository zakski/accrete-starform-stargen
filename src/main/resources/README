Starform (also known as Accrete) was created by Matt Burdick in 1988.  Since
then it has been hacked about by many people.  This version is based on the
original released 'starform' code, as far as I know, with my hacks to it to
make it do what I want.

My changes are:

  Convert it to use ANSI C function prototypes, and have a header file for
  each module containing the exported functions and variables.

  Make it more modular, so that modules are not using data from modules that
  call them (and hopefully not calling functions 'upward' either).
  
  Put the 'main' function as the only thing in starform.c, so that (hopefully)
  all the other modules can be called by other programs.

  Add day/night and maximum/minimum temperatures for rocky (not gas giant)
  worlds.  The algorithm was stolen shamelessly from Stephen Kimmel's "World
  Builder" BASIC program, and then hacked about until it gave the sort of
  results my other simulations produce.

  Add stuff to list what materials are liquid on the planets' surface and
  what gasses might be in the atmosphere (if any).  It's guesswork to an
  extent (especially proportions), if you want to take it out look for
  function 'text_list_stuff' in module display.c and delete the calls to it.
  If you know more than I do about the amounts or properties (not hard!)
  please let me know any changes to make it better.  Note that I haven't yet
  made it look at the max and min temperatures to see whether stuff freezes or
  evaporates only part of the time...

  I've also added some ad-hoc moon generation stuff, if you define 'MOON' when
  compiling (add '-DMOON' to the CFLAGS variable in the makefile) then you'll
  get moons generated as well.  It's not scientifically based, though, so you
  probably don't want to do that...

Please read the INSTALL file to find out how to build it.

If you want to see the sort of output it produces, have a look at the EXAMPLE
files in this archive.

Chris Croughton, 1999.11.24
mailto:chris@keris.demon.co.uk

The following is Matt Burdick's original README file.

-----------------------------------------------------------------------------

This program is based on an article by Martyn Fogg in the Journal of the
British Interplanetary Society (JBIS) called 'Extrasolar Planetary Systems:
a Microcomputer Simulation'.  In it, he described how to generate various
sun-like solar systems randomly.  Since he did a good job of listing
references, I decided to implement it in Turbo Pascal on my PC.

Later, I translated it to C for portability, and the result is what you see
in front of you.  Because of my need to run this on an IBM-PC, there are two
makefiles included with the program: 'Makefile' (for unix systems), and 
'starform.mak' for MS-DOS systems.  To create the executable on a unix 
system, type in 'make' alone; type 'make starform.mak' if you are on 
an MS-DOS machine and using Microsoft C.

Thanks go to Sean Malloy (malloy@nprdc.arpa) for his help with the random
number routines and to Marty Shannon (mjs@mozart.att.com) for the
lisp-style output format, command-line flags, and various other pieces.

Enjoy, and if you find any glaring inconsistancies or interesting pieces to
add to the simulation, let me know and I'll include it in any other
distributions I send out.

Now for some references.  These are not the only good references on this 
subject; only the most interesting of many that were listed in Fogg's 
article in vol 38 of JBIS:

For a good description of the entire program:
	"Extra-Solar Planetary Systems: A Microcomputer Simulation"
	Martyn J. Fogg,  Journal of the British Interplanetary Society
	Vol 38, pp. 501 - 514, 1985

For the surface temperature/albedo iterative loop:
	"The Evolution of the Atmosphere of the Earth"
	Michael H. Hart, Icarus, Vol 33, pp. 23 - 39, 1978

For the determination of the radius of a terrestrial planet:
	"The Internal Constitution of the Planets"
	D. S. Kothari, Ph.D. , Mon. Not. Roy. Astr. Soc.
	Vol 96, pp. 833 - 843, 1936

For the planetary mass accretion algorithm:
	"Formation of Planetary Systems by Aggregation: A Computer Simulation"
	S. H. Dole, RAND paper no. P-4226, 1969

For the day length calculation:
	"Q in the Solar System"
	P. Goldreich and S. Soter, Icarus, Vol 5, pp. 375 - 389, 1966


----------------------------------------------------------------------
 I can be reached at the email address burdick%hpda@hplabs.hp.com
----------------------------------------------------------------------
Here is a sample solar system:


Accrete - V3.0; seed=0x00000005
                         SYSTEM  CHARACTERISTICS
Stellar mass: 1.00 solar masses
Stellar luminosity: 0.99
Age: 4.429 billion years  (5.628 billion left on main sequence)
Habitable ecosphere radius: 0.996 AU

Planets present at:
1	  0.341 	 AU
2	  0.505 	 AU
3	  0.877 	 AU
4	  1.047 	 AU
5	  1.793 	 AU
6	  2.956 	 AU
7	  5.160 	 AU
8	  8.852 	 AU
9	 13.121 	 AU
10	 28.450 	 AU
11	 46.864 	 AU



Planet 1	
Planet is tidally locked with one face to star.
   Distance from primary star:	0.341	AU
   Mass:			0.220	Earth masses
   Surface gravity:		0.59	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		193.31	degrees Celcius
   Equatorial radius:		3893.8	Km
   Density:			5.314	grams/cc
   Eccentricity of orbit:	0.092
   Escape Velocity:		6.71	Km/sec
   Molecular weight retained:	17.63 and above
   Surface acceleration:	578.24	cm/sec2
   Axial tilt:			22	degrees
   Planetary albedo:		0.081
   Length of year:		72.89	days
   Length of day:		1749.33	hours
   Boiling point of water:	-273.0	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 2	
Planet is tidally locked with one face to star.
   Distance from primary star:	0.505	AU
   Mass:			0.202	Earth masses
   Surface gravity:		0.57	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		112.78	degrees Celcius
   Equatorial radius:		3786.9	Km
   Density:			5.310	grams/cc
   Eccentricity of orbit:	0.091
   Escape Velocity:		6.52	Km/sec
   Molecular weight retained:	18.65 and above
   Surface acceleration:	561.97	cm/sec2
   Axial tilt:			28	degrees
   Planetary albedo:		0.060
   Length of year:		130.99	days
   Length of day:		3143.70	hours
   Boiling point of water:	-273.0	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 3	
   Distance from primary star:	0.877	AU
   Mass:			0.165	Earth masses
   Surface gravity:		0.53	Earth gees
   Surface pressure:		2.702	Earth atmospheres	GREENHOUSE EFFECT
   Surface temperature:		45.57	degrees Celcius
   Equatorial radius:		3541.1	Km
   Density:			5.302	grams/cc
   Eccentricity of orbit:	0.015
   Escape Velocity:		6.10	Km/sec
   Molecular weight retained:	21.36 and above
   Surface acceleration:	524.69	cm/sec2
   Axial tilt:			29	degrees
   Planetary albedo:		0.038
   Length of year:		300.44	days
   Length of day:		40.82	hours
   Boiling point of water:	129.5	degrees Celcius
   Hydrosphere percentage:	100.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.00


Planet 4	
   Distance from primary star:	1.047	AU
   Mass:			1.515	Earth masses
   Surface gravity:		1.15	Earth gees
   Surface pressure:		1.889	Earth atmospheres
   Surface temperature:		19.01	degrees Celcius
   Equatorial radius:		7328.1	Km
   Density:			5.494	grams/cc
   Eccentricity of orbit:	0.017
   Escape Velocity:		12.84	Km/sec
   Molecular weight retained:	4.81 and above
   Surface acceleration:	1125.13	cm/sec2
   Axial tilt:			22	degrees
   Planetary albedo:		0.297
   Length of year:		391.74	days
   Length of day:		14.68	hours
   Boiling point of water:	118.4	degrees Celcius
   Hydrosphere percentage:	67.12
   Cloud cover percentage:	61.38
   Ice cover percentage:	1.06


Planet 5	*gas giant*
   Distance from primary star:	1.793	AU
   Mass:			6.262	Earth masses
   Equatorial radius:		18997.9	Km
   Density:			1.303	grams/cc
   Eccentricity of orbit:	0.002
   Escape Velocity:		16.21	Km/sec
   Molecular weight retained:	3.02 and above
   Surface acceleration:	691.87	cm/sec2
   Axial tilt:			29	degrees
   Planetary albedo:		0.500
   Length of year:		877.67	days
   Length of day:		15.54	hours


Planet 6	
   Distance from primary star:	2.956	AU
   Mass:			0.453	Earth masses
   Surface gravity:		0.75	Earth gees
   Surface pressure:		0.207	Earth atmospheres
   Surface temperature:		-136.53	degrees Celcius
   Equatorial radius:		4941.6	Km
   Density:			5.356	grams/cc
   Eccentricity of orbit:	0.140
   Escape Velocity:		8.55	Km/sec
   Molecular weight retained:	10.86 and above
   Surface acceleration:	739.66	cm/sec2
   Axial tilt:			18	degrees
   Planetary albedo:		0.634
   Length of year:		1857.62	days
   Length of day:		17.62	hours
   Boiling point of water:	61.1	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	81.12


Planet 7	*gas giant*
   Distance from primary star:	5.160	AU
   Mass:			69.313	Earth masses
   Equatorial radius:		41830.7	Km
   Density:			1.351	grams/cc
   Eccentricity of orbit:	0.299
   Escape Velocity:		36.35	Km/sec
   Molecular weight retained:	0.60 and above
   Surface acceleration:	1579.66	cm/sec2
   Axial tilt:			42	degrees
   Planetary albedo:		0.512
   Length of year:		4284.26	days
   Length of day:		10.28	hours


Planet 8	*gas giant*
   Distance from primary star:	8.852	AU
   Mass:			11.727	Earth masses
   Equatorial radius:		26059.7	Km
   Density:			0.946	grams/cc
   Eccentricity of orbit:	0.182
   Escape Velocity:		18.95	Km/sec
   Molecular weight retained:	2.21 and above
   Surface acceleration:	688.64	cm/sec2
   Axial tilt:			47	degrees
   Planetary albedo:		0.509
   Length of year:		9626.17	days
   Length of day:		15.57	hours


Planet 9	*gas giant*
   Distance from primary star:	13.121	AU
   Mass:			557.816	Earth masses
   Equatorial radius:		83066.4	Km
   Density:			1.389	grams/cc
   Eccentricity of orbit:	0.083
   Escape Velocity:		73.18	Km/sec
   Molecular weight retained:	0.15 and above
   Surface acceleration:	3223.89	cm/sec2
   Axial tilt:			33	degrees
   Planetary albedo:		0.454
   Length of year:		17357.91	days
   Length of day:		7.20	hours


Planet 10	
   Distance from primary star:	28.450	AU
   Mass:			0.372	Earth masses
   Surface gravity:		0.40	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		-222.05	degrees Celcius
   Equatorial radius:		6182.7	Km
   Density:			2.246	grams/cc
   Eccentricity of orbit:	0.000
   Escape Velocity:		6.93	Km/sec
   Molecular weight retained:	16.54 and above
   Surface acceleration:	388.05	cm/sec2
   Axial tilt:			57	degrees
   Planetary albedo:		0.149
   Length of year:		55468.32	days
   Length of day:		24.33	hours
   Boiling point of water:	-38.3	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.10


Planet 11	
   Distance from primary star:	46.864	AU
   Mass:			0.283	Earth masses
   Surface gravity:		0.36	Earth gees
   Surface pressure:		0.000	Earth atmospheres
   Surface temperature:		-233.50	degrees Celcius
   Equatorial radius:		5653.0	Km
   Density:			2.236	grams/cc
   Eccentricity of orbit:	0.047
   Escape Velocity:		6.32	Km/sec
   Molecular weight retained:	19.88 and above
   Surface acceleration:	353.22	cm/sec2
   Axial tilt:			54	degrees
   Planetary albedo:		0.157
   Length of year:		117268.25	days
   Length of day:		25.50	hours
   Boiling point of water:	-45.5	degrees Celcius
   Hydrosphere percentage:	0.00
   Cloud cover percentage:	0.00
   Ice cover percentage:	0.08


