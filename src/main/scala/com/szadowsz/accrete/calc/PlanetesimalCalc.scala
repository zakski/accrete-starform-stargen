package com.szadowsz.accrete.calc


import com.szadowsz.accrete.constants.AccreteConstants

import scala.util.Random

/**
 * Calculations need to form Planetesimals.
 *
 * @author Zakski : 21/07/2015.
 */
trait PlanetesimalCalc {
  this: AccreteConstants =>

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
  def aphelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 + ecc)


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
  def perihelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 - ecc)

  /**
   * Method to calculate whether a planetesimal has gained enough mass to accrete gas as well as dust, see "c)
   * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param perihelion closest the planetesimal gets to the sun in AU.
   * @return critical mass in solar mass.
   */
  def criticalMass(perihelion: Double): Double = B * Math.pow(perihelion, -0.75)

  /**
   * Method is used to calculate the inner distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction, accounting for eccentricity.
   *
   * @note equivalent of (rp - xp)/(1.0 + W) in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @param mass the mass of the body in solar mass (M?).
   * @return the greatest distance between the body and its host star in AU.
   */
  def innerBandLimit(axis: Double, ecc: Double, mass: Double): Double = {
    innerBandLimit(innerGravLimit(axis, ecc, mass))
  }

  /**
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of ra + xa in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @param mass the mass of the body in solar mass (M?).
   * @return the greatest distance between the body and its host star in AU.
   */
  def innerGravLimit(axis: Double, ecc: Double, mass: Double): Double = {
    innerGravLimit(perihelionDistance(axis, ecc), mass)
  }

  /**
   * Method is used to calculate the inner distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of rp - xp in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param perihelion the closest distance between the body and its host star in AU.
   * @param mass the mass of the body in solar mass (M?).
   * @return the perihelion - the gravitational pull distance in AU.
   */
  def innerGravLimit(perihelion: Double, mass: Double) = perihelion * (1.0 - muMassFunction(mass))

  /**
   * Method is function of mass used in calculation to get the distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction. Used to find the dust sweep limits, see c) Aggregation in "Formation of
   * Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note equivalent of mu in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass - the mass of the protoplanetary body in solar mass (M?).
   * @return coeffecient applied to perihelion and aphelion distances.
   */
  def muMassFunction(mass: Double): Double = Math.pow(mass / (1.0 + mass), 1.0 / 4.0)

  /**
   * Method is used to calculate the inner distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction, accounting for eccentricity.
   *
   * @note equivalent of (rp - xp)/(1.0 + W) in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param innerGravLimit  the perihelion - the gravitational pull distance in AU.
   * @return The inner bound of the protoplanet's ability to accrete in AU.
   */
  def innerBandLimit(innerGravLimit: Double): Double = innerGravLimit / (1.0 + CLOUD_ECCENTRICITY)

  /**
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction, accounting for eccentricity.
   *
   * @note equivalent of (ra + xa)/(1.0 - W) in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @param mass the mass of the body in solar mass (M?).
   * @return the closest distance between the body and its host star in AU.
   */
  def outerBandLimit(axis: Double, ecc: Double, mass: Double): Double = {
    outerBandLimit(outerGravLimit(axis, ecc, mass))
  }

  /**
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of ra + xa in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @param mass the mass of the body in solar mass (M?).
   * @return the closest distance between the body and its host star in AU.
   */
  def outerGravLimit(axis: Double, ecc: Double, mass: Double): Double = {
    outerGravLimit(aphelionDistance(axis, ecc), mass)
  }

  /**
   * Method is used to calculate the inner distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of rp - xp in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param aphelion the furthest distance between the body and its host star in AU.
   * @param mass the mass of the body in solar mass (M?).
   * @return the aphelion + the gravitational pull distance in AU.
   */
  def outerGravLimit(aphelion: Double, mass: Double) = aphelion * (1.0 + muMassFunction(mass))

  /**
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction, accounting for eccentricity.
   *
   * @note equivalent of (ra + xa)/(1.0 - W) in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param outerGravLimit the aphelion + the gravitational pull distance in AU.
   * @return The outer bound of the protoplanet's ability to accrete
   */
  def outerBandLimit(outerGravLimit: Double): Double = outerGravLimit / (1.0 - CLOUD_ECCENTRICITY)

}
