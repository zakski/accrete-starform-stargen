# Formation of Planetary Systems by Aggregation: A Computer Simulation

This is the main paper that the accretion part of the simulation is based upon. It was written in 1969 by Stephen Dole.

## Basic Assumptions:
- 1 star of 1 solar mass and 1 solar luminosity (basically equivalent to our own star)

- Planets can form between the radii 0.3 astronomical units (AU) and 50.0 AU.

- Planets form from a spherically symmetrical cloud of dust and gas with a constant ratio of gas to dust with the
  density decreasing with the distance from the center.

- All particles in the cloud are moving on elliptical orbits with the center of mass (star) at one focus.

- All particles in the cloud have the same orbital eccentricity

## Features
- Generates a Believable (for the 60s/70/s/80s) Sol-like Solar System.
- Accretion algorithm for sequentially adding/growing/merging protoplanets as long as there is gas and dust remaining.
- Distinguishes between rocky and gas planets.

## Limitations:

### In Recreation:
- No way to recreate exact tests results; even with a seed listed in the sample run, the age of the computer hardware he
  used means that accurately recreating the pseudo-random number sequence is a tall order without the original software
  to hand. (internal random number generator of an IBM 7044 PC).

### With the Model:
- Collision calculations are less than accurate due to not taking into account any axial inclinations on the orbital plane.

- No consideration given to the accretion of satellites.

- Dust Density Calculation are in 2D

- Dust / Gas removal is a discrete event, rather than a gradual one

- No consideration given to the kind of atmosphere that rocky planets will have.

- Arbitrarily set the outer and inner limits at with planets can form.

## Compilation
N/a - no source