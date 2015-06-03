package com.szadowsz.starform.calc

import com.szadowsz.starform.constants.AccreteConstants

import scala.util.Random

/**
 * Separating Calculations from the constants that they use to allow for pick-n-mix changes of the model.
 *
 * @author Zakski : 03/06/2015.
 */
class AccreteCalc {
  this: AccreteConstants =>

  /**
   * Method to calculate dust cloud density at a given radius. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section a) Initial Conditions in the Cloud.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param radius - the current distance from the stellar mass
   * @return Dust density at that radius of the cloud
   */
  def dustCloudDensity(radius: Double): Double = K * DUST_DENSITY_COEFF * Math.exp(-ALPHA * Math.pow(radius, 1.0 / N))

  /**
   * Method to produce the semi major axis of a planet. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section b) The Planetary Nuclei.
   *
   * @note made minor cosmetic change from 50Yi, where Yi is a random number and 50 is outer limit. Innermost limit is
   *       mentioned separately originally.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param rand - a random number generator to supply a value between 0.0 and 1.0
   * @return eccentricity between 0.0 and 1.0, essential for a planet to stay in the system.
   */
  def semiMajorAxis(rand: Random): Double = INNERMOST_PLANET + (OUTERMOST_PLANET - INNERMOST_PLANET) * rand.nextDouble()


  /**
   * Method to produce the eccentricity of a planet. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section b) The Planetary Nuclei.
   *
   * @note made minor cosmetic change from 1 - (1 - Yj)Q, where Yj is a random number and Q is the coefficient.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param rand - a random number generator to supply a value between 0.0 and 1.0
   * @return eccentricity between 0.0 and 1.0, essential for a planet to stay in the system.
   */
  def eccentricity(rand: Random): Double = 1.0 - Math.pow(rand.nextDouble(), ECCENTRICITY_COEFF)

}
