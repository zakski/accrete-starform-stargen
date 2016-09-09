package com.szadowsz.starform.calc

import com.szadowsz.accrete.calc.RandomCalc
import com.szadowsz.starform.constants.FoggConstants

import scala.util.Random

/**
  * Additional psuedo-random methods for Starform.
  *
  * @author Zakski : 07/09/2016.
  */
trait StarformRandCalc extends RandomCalc {
  this : FoggConstants =>

  /**
    * Method to pseudo-randomly generate the mass of a star in solar mass.
    *
    * The solar mass is a standard unit of mass in astronomy that is used to indicate the masses of
    * other stars, as well as clusters, nebulae and galaxies. It is equal to the mass of the Sun, about two
    * nonillion kilograms. As per section "2. The Microcomputer Model" in Extra-solar Planetary Systems: A Microcomputer
    * Simulation, we are aiming for a star of a mass between 0.6 and 1.3 solar masses.
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
    * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
    *
    * @param rand pseudo-random number generator interface
    * @return generated mass in terms of solar mass
    */
  def stellarMass(rand: Random): Double = (UPPER_SOLAR_MASS - LOWER_SOLAR_MASS) * rand.nextDouble() + LOWER_SOLAR_MASS


}
