package com.szadowsz.accrete.calc

import com.szadowsz.accrete.constants.AccreteConstants

import scala.util.Random

/**
  * @author Zakski : 06/09/2016.
  */
trait RandomCalc {
  this : AccreteConstants =>

  /**
    * Method to produce the semi major axis of a planetesimal. Formula taken from "Formation of Planetary Systems
    * by Aggregation: A Computer Simulation" in section b) The Planetary Nuclei.
    *
    * @note made minor cosmetic change from 50Yi, where Yi is a random number and 50 is outer limit. Innermost limit is
    *       mentioned separately originally.
    * @note unit of return value is AU
    *
    * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method RandomPlanetismal, line 58 in Planetismal.java - Ian Burrell (accrete)
    * @see method distribute_planetary_masses, line 405 in accrete.c - Mat Burdick (accrete)
    * @see method dist_planetary_masses, line 403 in accrete.c - Mat Burdick (starform)
    * @see constructor Protoplanet, line 150 in  Protoplanet.java - Carl Burke (starform)
    *
    * @param rand - a random number generator to supply a value between 0.0 and 1.0
    * @return the semi major axis of a planetismal orbiting a star in AU.
    */
  def semiMajorAxis(rand: Random): Double = INNERMOST_PLANET + (OUTERMOST_PLANET - INNERMOST_PLANET) * rand.nextDouble()

  /**
    * Method to produce the eccentricity of a planetesimal. Formula taken from "Formation of Planetary Systems
    * by Aggregation: A Computer Simulation" in section b) The Planetary Nuclei.
    *
    * @note made minor cosmetic change from 1 - (1 - Yj)Q, where Yj is a random number and Q is the coefficient.
    *
    * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method RandomEccentricity, line 128 in DoleParams.java - Ian Burrell (accrete)
    * @see method distribute_planetary_masses, line 406 in accrete.c - Mat Burdick (accrete)
    * @see method dist_planetary_masses, line 404 in accrete.c - Mat Burdick (starform)
    * @see constructor Protoplanet, line 151 in  Protoplanet.java - Carl Burke (starform)
    *
    * @param rand - a random number generator to supply a value between 0.0 and 1.0
    * @return eccentricity between 0.0 and 1.0, essential for a planetesimal to stay in the system.
    */
  def eccentricity(rand: Random): Double = 1.0 - Math.pow(rand.nextDouble(), ECCENTRICITY_COEFF)

}
