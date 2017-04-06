Accrete/Starform/Stargen
========================

## Intro

Accrete's origin dates back to the late 60's when Stephen H. Dole published "Formation of Planetary Systems by Aggregation: A Computer Simulation". 

It grew to prominence in the 90's after a recreated version of the source code based on a susequent paper by Martyn J. Fogg was released into the fertile ground that was the now defunct USML mailing list.

Since then there have been numerous versions, and the work on this module is primarily focused on preserving the timeline of events that I have pieced together.

More detailed analysis can be found in the docs folder.

## Requirements

- Gradle 3.4.x+
- Visual Studio 2015 (any edition)

## Source Code

This section contains general comments about the recovered source code for each processed version.

### Gilham
***

#### Acrete (basic)

This is his first iteration, published in White Dwarf back in 1984. 

Its written in ibm basic which I could not even begin to guess how to compile. So I have ran the article through a web ocr utility and abandoned cleaning 
that up until I have more time. 

#### Acrete (psuedocode)

Gilham's second iteration, published on Usenet. 

The psuedo code just reiterates the info published in the WD article.

#### Acrete (C++)

Gilham's third and final extant iteration, published on Usenet. 

The code recreates Dole's algorithms, and only needed a few minor "std::" iostream tweaks to get up and running.

### Burdick
***

Matt Burdick's codeline popularised accrete and disseminated across the web via ftp sites and usenet in the late 80's to mid 90's. 

#### Accretion (Pascal)

The first iteration of Burdick's code is written in Turbo Pascal 3 circa 1988. Naturally this is difficult to compile on modern systems, so while I have 
attempted it, I have not got it to run. 

However, you can see in the source code that most of the features of his later C/C++ versions are present. 

#### Accrete (C)

Burdick ported his pascal code to c some time in '88 or '89. This would pretty much turn out to be the language family of choice for the majority of 
developers that forked his code.
 
I have added c/visual studio support to gradle to accommodate these major revisions.

##### 1988 - Matt Budick - Accrete -  Steve Gilham Incomplete
This particular version is an incomplete one, published by Steve Gilham, so naturally it will not compile, but I have cleaned up all invalid whitespace characters.

##### 1994 - Matt Burdick - Accrete
This is the first complete c version; classes files that existed in the previous version seem identical baring whitespace. 
 
Unfortunately the C code is quite elderly so it does not compile right off the bat using Gradle/VS either, and I do not want to change it at this time.

##### 1995 - Nyrath - Accrete
There are minor differences between this and Burrell's version.
 - EARTH_ALBEDO has been changed from 0.3 to 0.39 in const.h
 - printf changed to fprintf to print out to a file
 - moved initialisation method around
 
Unfortunately like Burrell's variant it doesn't compile using Gradle/VS either.

##### 1999 - Peter Keel - Accrete
There are minor cosmetic differences between this and Nyrath's version.
 
Doesn't compile using Gradle/VS either.

#### Accrete2 / Starform (C)

This branch is actually the 3rd iteration of Burdick's code. The main changes between what is the first/second iteration and this seem to be its psuedorandom 
number routines and its lisp-style console output.

##### 1994 - Matt Burdick - Starform

Sorts out the dependency issues that I was seeing with the older code. Improves on the prior versions in general.

##### 1995 - Matt Burdick - Starform

Steve Dang seems to of straight up copied Ian Burrell's version to his Geocities page.

##### 1999 - Peter Keel - Starform

Peter Keel seems to have a version more or less identically to the prior two versions.

##### 1993 - Matt Burdick - starform - Sean Molloy

Sean Molloy posted a v3.1 version that seems to be the highest iteration of Burdick's original code available on the web. It seems to have some runtime 
issues that could be the product of my new build process.

## Papers

The Research Papers that inspired all the extant accrete code. 

At some point I hope to go back through these and find improvements / enhancements suggested by papers that cite these and add them to my recreation as 
options. 

### Formation of Planetary Systems by Aggregation: A Computer Simulation
***
This is the main paper that the accretion part of the simulation is based upon. It was written in 1969 by Stephen Dole.

#### Basic Assumptions:
- 1 star of 1 solar mass and 1 solar luminosity (basically equivalent to our own star)
- Planets can form between the radii 0.3 astronomical units (AU) and 50.0 AU.

#### Features
- Generates a Believable (for the 60s/70/s/80s) Sol-like Solar System.

#### Limitations:
- No way to recreate exact tests results; even with a seed listed in the sample run, the age of the computer hardware he used means that accurately recreating
the pseudo-random number sequence is a tall order without the original software to hand. (internal random number generator of an IBM 7044 PC).

- Collision calculations are less than accurate due to not taking into account any axial inclinations on the orbital plane.

- No consideration given to the accretion of satellites.

- Dust Density Calculation are in 2D

### Computer Simulation of the Formation of Planetary Systems
***
Stephen Dole's follow-up paper which was published in Icarus a year later. 

Its main usages are as a cross-reference for references found in the previous paper, its comparison of a small dataset against the available accurate (for 
the time) measurements of the solar system, and its slightly alternate look at some of the formula used.

The model seems to be identical to the one in the previous paper.

### Computer Simulations of Planetary Accretion Dynamics: Sensitivity to Initial Conditions
***
A review/critique of the initial parameters and formulae of Dole's model written in 1977 by R. Isaacman and Carl Sagan.

#### Looks At/Discusses/Mentions
 
- initial dust density distribution formula

- the choices of orbital eccentricity for the dust cloud

- parallel growth and injection of plantismals

- varying the planetismal seed mass

- altering the dust to gas mass ratio

-  alternative planetary distancing

#### Conclusions

that ACRETE is missing some of the essential physics of solar system cosmogony, or that planetary systems of our type are only one example in a rich array of
alternative varieties of planetary systems. 

Likewise, more fundamental changes in the nebular morphology (e.g. from an exponential to a power law density 
distribution function) generate planetary systems some of which, although they do not closely resemble our own, are not fundamentally objectionable.

### Extra-Solar Planetary Systems: A Microcomputer Simulation
***

This paper reconstitutes Dole's algorithm from his published works and condenses them into 2K of Basic code, able to be ran on microcomputers built at the time.

After that he adds his own improvements and enhancements to the model.

This paper is the one that Matt Burdick based his code on.

#### Changes

- varies mass of star between 0.7 & 1.3 solar masses. Spectral classes K5-F5.

- adjusts minimum and maximum planetary formation distance by luminosity of star.

- adjusts the planetary critical mass formula (limit at which planet begins to accrete gas as well as dust) by luminosity of the star.

- varies the central density parameter by the mass of the star.

#### Features

- calculates the Luminosity, Age, Main Sequence Lifespan and Habitual Zone of the Star. 

- calculates the "Zone", Density, Radius, Day Length, Orbit Period and Spin Resonance of the Planets.

- calculates the atmospheric conditions of the Planets.

- assesses Habitability and possibility of Life on each Planet.


#### Limitations:
- No way to recreate the exact accretion tests results; even with a seed listed in the sample run, the age of the computer hardware he used means that
accurately recreating the pseudo-random number sequence is a tall order without the original software to hand. However unlike Dole's paper we can try to
verify the modern ecosphere code is correct by comparing the non-random functions against the sample data he provides.

- No solution for Dole's less than stellar Collision calculations.

- No consideration given to the accretion of satellites.

- Atmosphere decision gates and terrestrial planet composition derivations are not explained in the paper, because of this burdick and co's source code
regresses in these areas.
