package com.szadowsz.accrete.base.calc

import com.szadowsz.accrete.base.constants.AccreteConstants

import scala.util.Random

/**
 * Separating Calculations from the constants that they use to allow for detailing of changes to the model.
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
   * @param radius - the current distance from the stellar mass in AU
   * @return Dust density at that radius of the cloud
   */
  def dustCloudDensity(radius: Double): Double = K * DUST_DENSITY_COEFF * Math.exp(-ALPHA * Math.pow(radius, 1.0 / N))

  /**
   * Method to produce the semi major axis of a planet. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section b) The Planetary Nuclei.
   *
   * @note made minor cosmetic change from 50Yi, where Yi is a random number and 50 is outer limit. Innermost limit is
   *       mentioned separately originally.
   * @note unit of return value is AU
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param rand - a random number generator to supply a value between 0.0 and 1.0
   * @return the semi major axis of a planetismal orbiting a star in AU.
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

  /**
   * Method to get the Aphelion distance between an orbiting planetary body and its star. The Aphelion
   * distance is the furthest away that the planetary body will be from its Star.Used to find the outer dust sweep
   * limit, see c) Aggregation in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note equivalent of a + ae in dole's paper.
   * @note unit of return value is AU
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
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
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @return the closest distance between the body and its host star in AU.
   */
  def perihelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 - ecc)

  /**
   * Method is used to calculate the inner distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of rp - xp in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param perihelion the closest distance between the body and its host star in AU.
   * @param mass the mass of the body in solar mass.
   * @return the perihelion - the gravitational pull distance in AU.
   */
  def innerGravitationalLimit(perihelion: Double, mass: Double) = perihelion * (1.0 - muMassFunction(mass))

  /**
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of ra + xa in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param aphelion the furthest distance between the body and its host star in AU.
   * @param mass the mass of the body in solar mass.
   * @return the aphelion + the gravitational pull distance in AU.
   */
  def outerGravitationalLimit(aphelion: Double, mass: Double) = aphelion * (1.0 + muMassFunction(mass))

  /**
   * Method is function of mass used in calculation to get the distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction. Used to find the dust sweep limits, see c) Aggregation in "Formation of
   * Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note equivalent of mu in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass - the mass of the protoplanetary body in solar mass.
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
   * @param outerGravLimit the aphelion + the gravitational pull distance in AU.
   * @return The outer bound of the protoplanet's ability to accrete
   */
  def outerBandLimit(outerGravLimit: Double): Double = outerGravLimit / (1.0 - CLOUD_ECCENTRICITY)

  /**
   * Method to calculate whether the Accretion Process for a protoplanet should continue, see c) Aggregation in
   * "Formation of Planetary Systems by Aggregation: A Computer Simulation". Ian, Mat and Carl use the same
   * calculation for this.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke
   *
   * @param oldMass Mass of the previous iteration
   * @param newMass Mass as of this iteration
   * @return True if it is not worthwhile to continue simulation, False otherwise.
   */
  def shouldAccretionStop(oldMass: Double, newMass: Double): Boolean = (newMass - oldMass) < (0.0001 * oldMass)

  /**
   * Method to calculate whether a protoplanet has gained enough mass to accrete gas as well as dust, see "c)
   * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param perihelion closest protoplanet gets to the sun.
   * @return critical mass in solar mass.
   */
  def criticalMass(perihelion: Double): Double = B * Math.pow(perihelion, -0.75)

  /**
   * Method to calculate the combined axis of the coalescing protoplanets. see "d)
   * Coalesence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
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
   * Method to calculate the combined eccentricity of the coalescing protoplanets. see "d)
   * Coalescence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param mass1 mass of first protoplanet in Solar Mass.
   * @param axis1 axis of first protoplanet in AU.
   * @param ecc1 eccentricity of first protoplanet in AU.
   * @param mass2 mass of second protoplanet in Solar Mass.
   * @param axis2 axis of second protoplanet in AU.
   * @param ecc2 eccentricity of first protoplanet in AU.
   * @param axis3 combined axis of protoplanets in AU.
   * @return coalesced axis in AU.
   */
  def coalesceEccentricity(mass1: Double, axis1: Double, ecc1: Double,
                           mass2: Double, axis2: Double, ecc2: Double, axis3: Double): Double = {
    val term1: Double = eccTerm(axis1, ecc1, mass1) + eccTerm(axis2, ecc2, mass2)
    val term2: Double = term1 / ((mass1 + mass2) * Math.sqrt(axis3))
    val term3: Double = 1.0 - term2 * term2
    Math.sqrt(Math.abs(term3))
  }

  def eccTerm(axis: Double, ecc: Double, mass: Double): Double = {
    mass * Math.sqrt(axis) * Math.sqrt(1.0 - ecc * ecc)
  }
}