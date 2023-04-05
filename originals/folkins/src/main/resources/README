ABOUT THE PROGRAM

This program is an attempt to model the creation of stellar systems
('solar systems' if you like).  The original is by Andrew Folkins, based
fairly closely on Stephen Dole's original paper (but more CPU intensive)
and modified to ANSI C++ by me. I've hacked it about, removing some of
his optimisations (modern processors don't have any problem with the
time it takes, it's well under a second now on any Pentium) to get back
nearer to the original. I've also added gas accretion for normal planets
to give some sort of atmosphere, it seems to work reasonably. The output
formats are (of course) totally different from Matt Burdick's 'starform'
program (although I intend to add a lisp-type output which is compatible).

Having altered the eccentricity of input particles, I now get quite a
lot of systems like our Solar Systems.  However, I also see a fair
number of very massive planets (up to 10 times the mass of Jupiter),
occasionally a 'brown dwarf' (between 10 and 84 times Mj) and the
occasional companion star (just hot enough for fusion, over 84 Mj).
This seems not unreasonable to me, since planets and companions of those
masses are being found round real stars.  It seems that around 5% of
systems have a brown dwarf in them and 1% have a companion (in the Real
World, apparently around 60% of stars like Sol, and 35% of M-type
dwarfs have a lower-mass companion star of some sort, which implies
that I'm not providing enough mass).

Occasionally, the moons of one of the 'companion' stars include another
star.  I don't believe that a three-star system like that is stable, I
suspect that once formed a system should undergo a 'shakedown' to
eliminate silly things.  However, an interesting occurrence is a
'possible' moon of a companion star...

The output routines now look for "possibly habitable" worlds - since I'm
not yet generating an atmosphere, that's not included in the
characteristics, what I look for is surface gravity, temperature and
rotation.  It's interesting that almost all of the ones found as
'possible' are in systems with G or F class stars with a smattering of K
class (the coolest I've seen so far was a K4).

It seems that in order to get a rotation like Earth's a large moon is
needed to do tidal braking.  The system as I have it doesn't seem to
create one that size, I rather favour the idea that it was either a
"twin planet" which didn't merge or a 'captured' large asteroid, neither
of which my system will (yet) model.

In the conversion to C++, I have removed the original Amiga-type list
handling system and replaced it with ANSI C++ STL list template classes.
I also use maps and will use vectors in addition to lists (in particular
the output structures should use vectors for planets and moons so they
can be indexed easily).

*** NEW! ***

All values used are now in MKS units (metres, kilograms and seconds) instead
of the old mixed-unit system (some masses as a proportion of the sun, some of
the earth; some distances in AU, others in km, etc.).

*** NEW! ***

Code to generate a system, gven the parameters of a primary (normally a
star), is in file dole.cc, this file should be able to be used as a
library or common module.  The code to generate moons is, I admit,
rather ad-hoc and not based on any analysis of how they are really
created, mainly tweaked to give 'reasonable' results.  This should
eventually become a class, so don't depend on the interfaces!

Code to generate stars is in, logically, genstar.cc, which has a set of
probabilities to determine star type, luminosity and mass.  I've tweaked
those a bit to increase the number of systems with planets (basically
dropping the number of dwarf stars drastically) but the original table
is still there in #if 0.

Code to generate planetary parameters (radius, temperature, rotation
etc.) are in file planetstat.cc, it is crude code (compared to the
Martyn Fogg algorithms in 'starform') and is likely to be replaced.
Again, this interface will change, probably drastically.

SAMPLE RESULTS

Out of 10 000 systems created (using -n10000 -M, see later for parameter
meanings) the following statistics were gathered:

10000 systems
  752 habitable
  593 brown dwarfs
   75 companions

Just looking at the 'habitable' systems, 13 had a brown dwarf in the system
and 2 had companion stars (one at 14 AU with a mass of 0.1 Msol, the other at
44 AU with a mass of almost 1/3 Msol).

MAKING THE PROGRAM

The makefile is set up to use the GNU C/C++ compiler.  Note that if the
DOS port of the compiler (DJGPP) is used then the use of the 'g++'
program must be replaced by 'gpp' (DOS doesn't support the '+' character
in file or program names).  I haven't tried it with any other compilers,
but note that the Standard Template Library was introduced rather late
in the C++ standardisation process so some compilers may not be fully
compliant.  I've avoided using some of the very late features like
namespaces.

*** NOTE ***

It now uses my C++ library XLIB, available from my web and FTP sites
(http://www.keris.net/things.html points to the latest version).  This
should be installed wherever you put your system libraries, or in
library and header paths for your compiler.

*** NOTE ***

The executable program is 'mkstars'.  The default action is to produce
one random system on stdout and exit.  This can be modified using
options:

  -n#  Set the number of systems to output (-n5 produces 5 systems,
       etc.)

  -m#  Set the mass of the primary (Sol = 1, normally random)
  
  -l#  Set the luminosity  of the primary (Sol = 1, normally random)

  -a#  Set the age of the system (in GigaYears, normally random based on
       the star type).  The lifetime will be set to twice this value if
       specified to avoid anomalies.

  -M   Create moons.  This takes a LOT of processing power (several
       seconds per system on a Sun Ultra-1).  This is fairly realistic
       now, at least in the number of moons compared to the planet
       sizes.

  -p   This is purely for testing, it sets up an artificial system with
       the Earth and the Moon.

  -z   Switches on debugging stuff.  You really /don't/ want to use this
       unless you want it to go very slowly with masses of output.
       Using it twice increases the amount of 'stuff'.

Note that unlike other utilities the parameters to options must not have
spaces, so -n5 is correct but -n 5 isn't.  The main program is designed
as a test platform only (in fact in the original it was part of one of
the other files).

Using -m1 -l1 -a4 is a good way to test that the program creates systems
similar to our own with the same start conditions.  Out of a sample 100
systems generated with those parameters 60 had a 'habitable' planet,
which is not bad.

OTHER PROGRAMS AND SCRIPTS

I've included the start of an atmosphere model, atmos.cc, which uses a
chemical reaction model (in parsefrm.cc, elem.h and elem.ch).

I've also included two shell scripts which use nawk (an extended version
of awk, but I don't think the extensions are used).  findhab will output
just the 'habitable' systems (from file or as a filter) and classify
counts the number of systems, number of habitable ones, number of brown
dwarfs and number of companions, again either from a file or as a
filter.

Chris Croughton, CE 2000-02-02
