Accrete/Starform/Stargen
========================

## Intro

Accrete's origin dates back to the late 60's when Stephen H. Dole published "Formation of Planetary Systems by Aggregation: A Computer Simulation". 

It grew to prominence in the 90's after a recreated version of the source code based on a susequent paper by Martyn J. Fogg was released into the fertile ground that was the now defunct USML mailing list.

Since then there have been numerous versions, and the work on this module is primarily focused on preserving the timeline of events that I have pieced together.

## Formation of Planetary Systems by Aggregation: A Computer Simulation

This is the main paper that the accretion part of the simulation is based upon. It was written in 1969 by Stephen Dole.

### Basic Assumptions:
- 1 star of 1 solar mass and 1 solar luminosity (basically equivalent to our own star)
- Planets can form between the radii 0.3 astronomical units (AU) and 50.0 AU.

### Features
- Generates a Believable (for the 80s) Sol-like Solar System.

### Major Limitations:
- No way to recreate exact tests results; even with a seed listed in the sample run, the age of the computer hardware he used means that accurately recreating
the pseudo-random number sequence is a tall order without the original software to hand. (internal random number generator of an IBM 7044 PC).

- Collision calculations are less than accurate due to not taking into account any axial inclinations on the orbital plane.

- No consideration given to the accretion of satellites.

- Dust Density Calculation are in 2D
