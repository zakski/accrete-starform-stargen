package com.szadowsz.stargen.base.starform.calc

import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.system.bodies.Star

/**
  * @author Zakski : 10/09/2016.
  */
trait StarCalc[S <: Star] {
  this: StarformConstants[S] =>

  /**
    * Method to approximate the luminosity of a star for a given mass. See eq. 1-3 in section "3. Characteristics of The Primary Star" in Extra-solar Planetary
    * Systems: A Microcomputer Simulation.
    *
    * @note The solar luminosity, is a unit of radiant flux (power emitted in the form of photons) conventionally used by astronomers to measure the luminosity
    *       of stars. One solar luminosity is equal to the current accepted luminosity of the Sun, which is 3.839×1026 W, or 3.839×1033 erg/s. The value is
    *       slightly higher, 3.939×1026 W (equivalent to 4.382×109 kg/s or 1.9×10?16 M?/d) if the solar neutrino radiation is included as well as
    *       electromagnetic radiation. The Sun is a weakly variable star and its luminosity therefore fluctuates. The major fluctuation is the eleven-year
    *       solar cycle (sunspot cycle), which causes a periodic variation of about ±0.1%. Any other variation over the last 200–300 years is thought to be
    *       much smaller than this.
    *
    * @see p. 502 Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method luminosity, line 10 in enviro.c - Mat Burdick (accrete)
    * @see method luminosity, line 11 in accrete.c - Keris (starform)
    * @see method luminosity, line 10 in accrete.c - Mat Burdick (starform)
    * @see method LUMINOSITY, line 182 in  Star.java - Carl Burke (starform)
    *
    * @param stellarMass star's mass in terms of solar mass
    * @return star's luminosity in terms of solar luminosity
    */
  def stellarLuminosity(stellarMass: Double): Double = {
    if (stellarMass < 1.0) {
      Math.pow(stellarMass, 1.75 * (stellarMass - 0.1) + 3.325)
    } else {
      Math.pow(stellarMass, 0.5 * (2.0 - stellarMass) + 4.4)
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
  def greenhouseRadius(ecosphereRadius: Double): Double = ecosphereRadius * GREENHOUSE_EFFECT_CONST

}
