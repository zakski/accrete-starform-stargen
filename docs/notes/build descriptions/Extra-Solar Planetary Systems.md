# Extra-Solar Planetary Systems: A Microcomputer Simulation

This paper reconstitutes Dole's algorithm from his published works and condenses them into 2K of Basic code, able to be ran on microcomputers built at the 
time. After that he adds his own improvements and enhancements to the model.

This paper is the one that Matt Burdick based his code on.

#### Changes To Existing Code

- varies mass of star between 0.7 & 1.3 solar masses. Spectral classes K5-F5.

- adjusts minimum and maximum planetary formation distance by luminosity of star.

- adjusts the planetary critical mass formula (limit at which planet begins to accrete gas as well as dust) by luminosity of the star.

- varies the central density parameter by the mass of the star.

#### Features of the Model

- calculates the Luminosity, Age, Main Sequence Lifespan and Habitual Zone of the Star. 

- calculates the "Zone", Density, Radius, Day Length, Orbit Period and Spin Resonance of the Planets.

- calculates the atmospheric conditions of the Planets.

- assesses Habitability and possibility of Life on each Planet.

- see [notes on original paper](/docs/notes/build%20descriptions/Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

## Limitations:
see [notes on original paper](/docs/notes/build%20descriptions/Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

### In Recreation:
- Atmosphere decision gates and terrestrial planet composition derivations are not explained in the paper, because of this burdick and co's source code
regresses in these areas.

### With the Model:
- No way to recreate the exact accretion tests results; even with a seed listed in the sample run, the age of the computer hardware he used means that
accurately recreating the pseudo-random number sequence is a tall order without the original software to hand. However unlike Dole's paper we can try to
verify the modern ecosphere code is mostly correct by comparing the non-random functions against the sample data he provides.
