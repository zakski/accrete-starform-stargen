package com.szadowsz.starform.calc

import com.szadowsz.accrete.calc.RandomCalc
import com.szadowsz.starform.constants.StarformConstants
import com.szadowsz.starform.util.UnitConverter

import scala.util.Random

/**
  * Additional psuedo-random methods for Starform.
  *
  * @author Zakski : 07/09/2016.
  */
trait StarformRandCalc extends RandomCalc {
  this : StarformConstants =>

  /**
    * Method to pseudo-randomly generate the mass of a star in solar mass.
    *
    * @note The solar mass is a standard unit of mass in astronomy that is used to indicate the masses of other stars, as well as clusters, nebulae and
    *       galaxies. It is equal to the mass of the Sun, about two nonillion kilograms. As per section "2. The Microcomputer Model" in "Extra-solar Planetary
    *       Systems: A Microcomputer Simulation", we are aiming for a star of a mass between 0.6 and 1.3 solar masses.
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
    * @see method generate_stellar_system, line 68 in gensys.c - Keris (starform)
    * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
    * @see constructor StarSystem, line 50 in  StarSystem.java - Carl Burke (starform)
    *
    * @param rand pseudo-random number generator interface
    * @return generated mass in terms of solar mass
    */
  def stellarMass(rand: Random): Double = (UPPER_SOLAR_MASS - LOWER_SOLAR_MASS) * rand.nextDouble() + LOWER_SOLAR_MASS

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
  def stellarAge(rand: Random, lifespan: Double): Double = {
    if (lifespan >= 6.0) {
      rand.nextDouble() * 5.0 + 1.0
    } else {
      rand.nextDouble() * (lifespan - 1.0) + 1.0
    }
  }

  /**
    * Calculates the volatile gas inventory of the planet.Uses Fog's assumption that the initial inventory is directly
    * proportional to the mass of the planet and inversely proportional to the mass of the central star. This is taken
    * from Fogg's equation 17.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method vol_inventory, line 361 in enviro.c - Mat Burdick (accrete)
    * @see method vol_inventory, line 359 in enviro.c - Mat Burdick (starform)
    * @see method vol_inventory, line 692 in Planet.java - Carl Burke (starform)
    *
    * @param mass planetary mass in terms of solar mass.
    * @param zone the zone the planet is classified within (1-3)
    * @param doesRetainGas true if the planet is too close to the sun, false otherwise (Greenhouse Effect)
    * @param hasGE true if the planet is too close to the sun, false otherwise (Greenhouse Effect)
    * @param stellarMass mass of the central star in terms of solar mass.
    * @return volatile gas inventory.
    */
  def vGasInventory(rand: Random, mass: Double, zone: Int, doesRetainGas : Boolean, hasGE: Boolean, stellarMass: Double): Double = {
    if (doesRetainGas) {
      val q = zone match {
        case 1 => 100000.0
        case 2 => 75000.0
        case 3 => 250.0
      }
      val massInEM = UnitConverter.solarMassToEarthMass(mass) // equation calls for earth mass.
      val temp1 = (q * massInEM) / stellarMass
      val temp2 = temp1 + (temp1 * (rand.nextDouble()*0.4 -0.2)) // +/- 20 percent
      if (hasGE) {
        temp2
        // matt and everyone that follows him applies this to all planets outside the greenhouse zone unlike fogg.
      } else if (zone == 1) {
        temp2 / 100.0
      } else {
        temp2
      }
    } else {
      0.0
    }
  }
}
