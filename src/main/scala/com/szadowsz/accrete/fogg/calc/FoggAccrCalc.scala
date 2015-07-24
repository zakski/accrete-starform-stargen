package com.szadowsz.accrete.fogg.calc

import com.szadowsz.accrete.base.calc.{AccreteCalc, PlanetesimalCalc}
import com.szadowsz.accrete.fogg.constants.FoggConstants

import scala.util.Random

/**
 * @author Zakski : 21/07/2015.
 */
trait FoggAccrCalc extends AccreteCalc {
  this: PlanetesimalCalc with FoggConstants =>

  /**
   * Method to procedurally generate the mass of a star in solar mass.
   *
   * The solar mass is a standard unit of mass in astronomy that is used to indicate the masses of
   * other stars, as well as clusters, nebulae and galaxies. It is equal to the mass of the Sun, about two
   * nonillion kilograms. As per section "2. The Microcomputer Model" in Extra-solar Planetary Systems: A Microcomputer
   * Simulation, we are aiming for a star of a mass between 0.6 and 1.3 solar masses.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
   * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
   *
   * @param rand pseudo-random number generator interface
   * @return generated mass in terms of solar mass
   */
  def stellarMass(rand: Random): Double = {
    (UPPER_SOLAR_MASS - LOWER_SOLAR_MASS) * rand.nextDouble() + LOWER_SOLAR_MASS
  }

  /**
   * Method to approximate the luminosity of a star for a given mass. This function comes from the section
   * "3. Characteristics of The Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
   *
   * @note The solar luminosity, is a unit of radiant flux (power emitted in the form of photons)
   *       conventionally used by astronomers to measure the luminosity of stars. One solar luminosity is equal to
   *       the current accepted luminosity of the Sun, which is 3.839×1026 W, or 3.839×1033 erg/s. The value is
   *       slightly higher, 3.939×1026 W (equivalent to 4.382×109 kg/s or 1.9×10?16 M?/d) if the solar
   *       neutrino radiation is included as well as electromagnetic radiation. The Sun is a weakly variable star
   *       and its luminosity therefore fluctuates.[4] The major fluctuation is the eleven-year solar cycle
   *       (sunspot cycle), which causes a periodic variation of about ±0.1%. Any other variation over the last
   *       200–300 years is thought to be much smaller than this.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method Luminosity, line 31 in Astro.java - Ian Burrell (accrete)
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
   * Method to approximate the star's lifespan on the main sequence. Taken from "3. Characteristics of The
   * Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method generate_stellar_system, line 93 in main.c - Mat Burdick (accrete)
   * @see method generate_stellar_system, line 85 in starform.c - Mat Burdick (starform)
   *
   * @note unit is Byr (1.0E9 years)
   *
   * @param stellarMass - star's mass in terms of solar mass
   * @param stellarLuminosity - star's luminosity in terms of solar luminosity
   * @return star's Main Sequence Lifespan in terms of billon years (Byr)
   */
  def stellarMSLifespan(stellarMass: Double, stellarLuminosity: Double): Double = {
    10 * (stellarMass / stellarLuminosity)
  }

  /**
   * function to randomise the star's age as noted in "3. Characteristics of The
   * Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method generate_stellar_system, line 94 in main.c - Mat Burdick (accrete)
   * @see method generate_stellar_system, line 86 in starform.c - Mat Burdick (starform)
   *
   * @note unit is Byr (1.0E9 years)
   *
   * @param rand pseudo-random number generator interface
   * @param lifespan the lifespan the star can expect on the main sequence
   * @return the approximate age of the star in Byr
   */
  def stellarAge(rand: Random, lifespan: Double): Double = {
    if (lifespan >= 6.0) {
      rand.nextDouble() * 5.0 + 1.0
    } else {
      rand.nextDouble() * (lifespan - 1.0) + 1.0
    }
  }

  /**
   * function to calculate the mean of the habitable orbital zone of the star from "3. Characteristics of The
   * Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method generate_stellar_system, line 91 in main.c - Mat Burdick (accrete)
   * @see method generate_stellar_system, line 90 in starform.c - Mat Burdick (starform)
   *
   * @param stellarLuminosity star's luminosity in terms of solar luminosity
   * @return mean habitable radius in AU.
   */
  def ecosphereRadius(stellarLuminosity: Double): Double = {
    Math.sqrt(stellarLuminosity)
  }

  /**
   * function to calculate the closest habitable orbit of the star from "3. Characteristics of The
   * Primary Star" in Extra-solar Planetary Systems: A Microcomputer Simulation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method generate_stellar_system, line 91 in main.c - Mat Burdick (accrete)
   * @see method generate_stellar_system, line 90 in starform.c - Mat Burdick (starform)
   *
   * @param ecosphereRadius mean habitable radius in AU.
   * @return inner habitable radius in AU.
   */
  def greenhouseRadius(ecosphereRadius: Double): Double = {
    ecosphereRadius * GREENHOUSE_EFFECT_CONST
  }

  /**
   * Method to calculate dust cloud density at a given radius. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section a) Initial Conditions in the Cloud. Modified by Fogg to take
   * solar mass into account.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   * @param radius - the current distance from the stellar mass in AU
   * @return Dust density at that radius of the cloud
   */
  override def dustCloudDensity(radius: Double): Double = {
    (DUST_DENSITY_COEFF * Math.sqrt(getStarMass)) * Math.exp(-ALPHA * Math.pow(radius, 1.0 / N))
  }

}
