package com.szadowsz.accrete.base.calc

/**
 * Orbital Calculations, useful during and after the accretion process.
 *
 * @author Zakski : 26/06/2015.
 */
trait OrbitalCalc {


  /**
   * Method to get the Aphelion distance between an orbiting planetary body and its star. The Aphelion
   * distance is the furthest away that the planetary body will be from its Star.Used to find the outer dust sweep
   * limit, see c) Aggregation in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note equivalent of a + ae in dole's paper.
   * @note unit of return value is AU
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method AphelionDistance, line 41 in DoleParams.java - Ian Burrell (accrete)
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @return the greatest distance between the body and its host star in AU.
   */
  protected def aphelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 + ecc)


  /**
   * Method to get the Perihelion distance between an orbiting planetary body and its star. The Perihelion
   * distance is the closest that the planetary body will be from its Star. Used to find the outer dust sweep
   * limit, see c) Aggregation in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note equivalent of a - ae in dole's paper.
   * @note unit of return value is AU
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method PerihelionDistance, line 37 in DoleParams.java - Ian Burrell (accrete)
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @return the closest distance between the body and its host star in AU.
   */
  protected def perihelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 - ecc)

}
