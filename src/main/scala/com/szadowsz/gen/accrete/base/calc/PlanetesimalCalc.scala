package com.szadowsz.gen.accrete.base.calc

import com.szadowsz.gen.accrete.base.AccreteConstants

import scala.util.Random

/**
 * Calculations need to form Planetesimals.
 *
 * @author Zakski : 21/07/2015.
 */
trait PlanetesimalCalc {
  this: OrbitalCalc with AccreteConstants =>

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
