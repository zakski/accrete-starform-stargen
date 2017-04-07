package com.szadowsz.stargen.base.accrete.calc

import com.szadowsz.stargen.base.accrete.constants.AccreteConstants

import scala.util.Random

/**
  * Pseudo-Random Generation Methods required for the Accretion simulation.
  *
  * @author Zakski : 06/09/2016.
  */
trait RandomCalc {
  this : AccreteConstants =>

  /**
    * Method to produce the eccentricity of a planetesimal. Formula taken from "Formation of Planetary Systems
    * by Aggregation: A Computer Simulation" in "III. Experimental Simulation, section b) The Planetary Nuclei".
    *
    * @note made minor cosmetic change from 1 - (1 - Yj)Q, where Yj is a random number and Q is the coefficient.
    *
    * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method RandomEccentricity, line 128 in DoleParams.java - Ian Burrell (accrete)
    * @see method distribute_planetary_masses, line 406 in accrete.c - Mat Burdick (accrete)
    * @see method ComputePlanetStats, line 148 in Dole.c - Andrew Folkins (accretion)
    * @see method CreatePlanet, lines 203 in dole.c - Keris (accretion v1)
    * @see method CreatePlanet, line 288 in dole.cc - Keris (accretion v2)
    * @see method dist_planetary_masses, line 434 in accrete.c - Keris (starform)
    * @see method dist_planetary_masses, line 404 in accrete.c - Mat Burdick (starform)
    * @see constructor Protoplanet, line 151 in  Protoplanet.java - Carl Burke (starform)
    *
    * @param rand - a random number generator to supply a value between 0.0 and 1.0
    * @return eccentricity between 0.0 and 1.0, essential for a planetesimal to stay in the system.
    */
  def eccentricity(rand: Random): Double = 1.0 - Math.pow(rand.nextDouble(), ECCENTRICITY_COEFF)

}
