package com.szadowsz.accrete.calc

/**
 * Basic Calculations for Combining to planetesimals into one.
 *
 * @author Zakski : 21/07/2015.
 */
trait CollisionCalc {
  this: PlanetesimalCalc =>


  /**
   * Method to calculate whether two coalescing planetesimals have collided. see "d)
   * Coalescence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass1 mass of closest protoplanet in Solar Mass.
   * @param axis1 axis of closest protoplanet in AU.
   * @param ecc1 eccentricity of closest protoplanet.
   * @param mass2 mass of furthest protoplanet in Solar Mass.
   * @param axis2 axis of furthest protoplanet in AU.
   * @param ecc2 eccentricity of furthest protoplanet.
   * @return coalesced axis in AU.
   */
  def hasCollision(mass1: Double, axis1: Double, ecc1: Double,
                   mass2: Double, axis2: Double, ecc2: Double): Boolean = {

    val dist: Double = axis2 - axis1
    val outer = outerGravLimit(axis1, ecc1, mass1) - axis1
    val inner = axis2 - innerGravLimit(axis2, ecc2, mass2)

    (Math.abs(dist) <= outer) || (Math.abs(dist) <= inner)
  }

  /**
   * Method to calculate the combined axis of two coalescing planetesimals. see "d)
   * Coalescence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass1 mass of first protoplanet in Solar Mass.
   * @param axis1 axis of first protoplanet in AU.
   * @param mass2 mass of second protoplanet in Solar Mass.
   * @param axis2 axis of second protoplanet in AU.
   * @return coalesced axis in AU.
   */
  def coalesceAxis(mass1: Double, axis1: Double, mass2: Double, axis2: Double): Double = {
    (mass1 + mass2) / (mass1 / axis1 + mass2 / axis2)
  }

  /**
   * Method to calculate the combined eccentricity of two coalescing planetesimals. see "d)
   * Coalescence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass1 mass of first protoplanet in Solar Mass.
   * @param axis1 axis of first protoplanet in AU.
   * @param ecc1 eccentricity of first protoplanet.
   * @param mass2 mass of second protoplanet in Solar Mass.
   * @param axis2 axis of second protoplanet in AU.
   * @param ecc2 eccentricity of second protoplanet.
   * @param axis3 combined axis of protoplanets in AU.
   * @return coalesced eccentricity.
   */
  def coalesceEccentricity(mass1: Double, axis1: Double, ecc1: Double,
                           mass2: Double, axis2: Double, ecc2: Double, axis3: Double): Double = {

    val term1: Double = eccTerm(axis1, ecc1, mass1) + eccTerm(axis2, ecc2, mass2)
    val term2: Double = term1 / ((mass1 + mass2) * Math.sqrt(axis3))
    val term3: Double = 1.0 - term2 * term2

    Math.sqrt(Math.abs(term3))
  }

  /**
   * Convenience Method used as part of the combined eccentricity of coalescing planetesimals calculation. see "d)
   * Coalescence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   */
  protected def eccTerm(axis: Double, ecc: Double, mass: Double): Double = {
    mass * Math.sqrt(axis) * Math.sqrt(1.0 - ecc * ecc)
  }
}
