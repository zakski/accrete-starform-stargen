package com.szadowsz.starform.system.bodies.fogg

import com.szadowsz.starform.system.bodies.Star

/**
  * Class to represent a star as defined by Fogg, required for the starform simulation.
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
class FoggStar(
                override val mass: Double,
                override val luminosity: Double,
                lSpan: Double,
                exist: Double,
                inner: Double,
                mean: Double
              ) extends Star {

  /**
    * An Estimation of the Star's Lifespan on the main sequence.
    *
    * @note unit of value is Byr (billion years).
    */
  val lifespan: Double = lSpan

  /**
    * A member to record the Star's current age.
    *
    * @note unit of value is Byr (billion years).
    */
  val age: Double = exist

  /**
    * The mean orbital radius at which we may expect a planetary body to have a habitable ecosphere.
    *
    * @note unit of value is AU.
    */
  val meanHabitableRadius: Double = mean

  /**
    * The minimum orbital radius at which we may expect a planetary body to have a habitable ecosphere.
    *
    * @note the outer limit is dependent on the planet and determined individually for each in this simulation.
    * @note unit of value is AU.
    */
  val innerHabitableRadius: Double = inner
}
