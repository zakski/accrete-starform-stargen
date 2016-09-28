package com.szadowsz.stargen.base.starform.bodies

/**
  * Abstract Outline Class to represent a star. Defines the basic members required for the starform simulation.
  *
  * @see pp. 502-503, 3. Characteristics Of The Primary Star, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
  * @see struct Star, line 21 in system.h - Andrew Folkins (accretion)
  * @see struct Star, line 33 in system.h - Keris (accretion v1)
  * @see struct Star, line 72 in system.h - Keris (accretion v2)
  * @see struct StellarTypeS, in steltype.h - Keris (starform)
  * @see Star.java - Carl Burke (starform)
  *
  * @author Zakski : 06/07/2015.
  */
abstract class Star {

  /**
    * The mass of the Star. Naturally the unit of the member is Solar Mass. Most iterations expect a pseudo-random value between 0.6 and 1.3 M☉. This is due to
    * the original simulation calculations and values being extrapolated from research on our own star. This variance is introduced in "Extra-solar Planetary
    * Systems: A Microcomputer Simulation", prior to that the star was assumed to be 1 M☉ and did not need to be factored into our calculations.
    *
    * @note unit of value is Solar Masses.
    */
  val mass: Double

  /**
    * The luminosity of the Star. A measurement of how bright the star is. This value can be approximated from the mass using the mass-luminosity relation, if
    * required.
    *
    * @note unit of value is Solar Luminosity.
    */
  val luminosity: Double

  /**
    * An Estimation of the Star's Lifespan on the main sequence.
    *
    * @note unit of value is Byr (billion years).
    */
  val lifespan: Double

  /**
    * A member to record the Star's current age.
    *
    * @note unit of value is Byr (billion years).
    */
  val age: Double

  /**
    * The mean orbital radius at which we may expect a planetary body to have a habitable ecosphere.
    *
    * @note unit of value is AU.
    */
  val meanHabitableRadius: Double

  /**
    * The minimum orbital radius at which we may expect a planetary body to have a habitable ecosphere.
    *
    * @note the outer limit is dependent on the planet and determined individually for each in this simulation.
    * @note unit of value is AU.
    */
  val innerHabitableRadius: Double
}
