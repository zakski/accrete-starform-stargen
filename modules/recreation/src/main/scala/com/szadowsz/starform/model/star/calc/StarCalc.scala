package com.szadowsz.starform.model.star.calc

import com.szadowsz.starform.model.star.constants.StarConstants
import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.system.bodies.star.Star

/**
  * @author Zakski : 10/09/2016.
  */
trait StarCalc[S <: Star] {

  val sConst : StarConstants

  def initStar(rand : RandGenTrait): S

  /**
    * function to randomise the star's age as noted in "3. Characteristics of The Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, lines 94-97 in main.c - Mat Burdick (accrete)
    * @see method getLifetime, line 179 in genstar.cc - Keris (accretion v2)
    * @see method generate_stellar_system, line 69-74 in gensys.c - Keris (starform)
    * @see method generate_stellar_system, lines 86-89 in starform.c - Mat Burdick (starform)
    * @see method commonConstructor, lines 113-116 in  StarSystem.java - Carl Burke (starform)
    *
    * @note unit is Byr (1.0E9 years)
    *
    * @param rand pseudo-random number generator interface
    * @param lifespan the lifespan the star can expect on the main sequence
    * @return the approximate age of the star in Byr
    */
  def stellarAge(rand: RandGenTrait, lifespan: Double): Double = {
    if (lifespan >= 6.0) {
      rand.nextDouble() * 5.0 + 1.0
    } else {
      rand.nextDouble() * (lifespan - 1.0) + 1.0
    }
  }

  /**
    * Method to approximate the star's lifespan on the main sequence. eq. 4 in "3. Characteristics of The Primary Star" from "Extra-solar Planetary Systems: A
    * Microcomputer Simulation".
    *
    * @note unit is Byr (1.0E9 years)
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 93 in main.c - Mat Burdick (accrete)
    * @see method getLifetime, line 179 in genstar.cc - Keris (accretion v2)
    * @see method critical_limit, line 283 in accrete.c - Keris (starform)
    * @see method generate_stellar_system, line 85 in starform.c - Mat Burdick (starform)
    * @see method commonConstructor, line 112 in  Star.java - Carl Burke (starform)
    *
    * @param stellarMass - star's mass in terms of solar mass
    * @param stellarLuminosity - star's luminosity in terms of solar luminosity
    * @return star's Main Sequence Lifespan in terms of billon years (Byr)
    */
  def stellarMSLifespan(stellarMass: Double, stellarLuminosity: Double): Double = 10 * (stellarMass / stellarLuminosity)

  /**
    * function to calculate the mean habitable orbit around the star from "3. Characteristics of The Primary Star" in "Extra-solar Planetary Systems:
    * A Microcomputer Simulation".
    *
    * @see eq.5, p.502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 91 in main.c - Mat Burdick (accrete)
    * @see method GenStar, line 167 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 214 in genstar.c - Keris (accretion v1)
    * @see method generate_stellar_system, line 75 in gensys.c - Keris (starform)
    * @see method generate_stellar_system, line 90 in starform.c - Mat Burdick (starform)
    * @see method commonConstructor, line 118 in  Star.java - Carl Burke (starform)
    *
    * @param stellarLuminosity star's luminosity in terms of solar luminosity
    * @return mean habitable radius in AU.
    */
  def ecosphereRadius(stellarLuminosity: Double): Double = Math.sqrt(stellarLuminosity)

  /**
    * function to calculate the closest possible habitable orbit around the star from "3. Characteristics of The Primary Star" in "Extra-solar Planetary
    * Systems: A Microcomputer Simulation".
    *
    * @see eq.6, p.503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 92 in main.c - Mat Burdick (accrete)
    * @see method GenStar, line 168 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 215 in genstar.c - Keris (accretion v1)
    * @see method generate_stellar_system, line 76 in gensys.c - Keris (starform)
    * @see method generate_stellar_system, line 91 in starform.c - Mat Burdick (starform)
    * @see method commonConstructor, line 119 in  Star.java - Carl Burke (starform)
    *
    * @param ecosphereRadius mean habitable radius in AU.
    * @return inner habitable radius in AU.
    */
  def greenhouseRadius(ecosphereRadius: Double): Double = ecosphereRadius * sConst.GREENHOUSE_EFFECT_CONST

}
