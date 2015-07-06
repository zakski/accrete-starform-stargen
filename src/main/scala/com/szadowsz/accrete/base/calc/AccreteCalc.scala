package com.szadowsz.accrete.base.calc

import com.szadowsz.accrete.base.constants.AccreteConstants

import scala.util.Random

/**
 * Separating Calculations from the constants that they use to allow for detailing of changes to the model. All
 * calculations here based on Dole's Paper. Most versions of code use Fogg's adjusted versions where applicable which
 * we will declare as a sub-type of this. Otherwise if code is functionally identical we will reference where it occurs
 * in each identical application.
 *
 * @author Zakski : 03/06/2015.
 */
trait AccreteCalc {
  this: PlanetaryCalc with AccreteConstants =>

  /**
   * Method to calculate outer dust band edge. The Formula that this comes from is unknown, it seems to be introduced
   * in one of the early accrete versions, but I cannot see any reference to it in the research papers. In base
   * process this might as well just return 200 since the solar mass is assumed to be 1.
   *
   *
   * @param mass - the stellar mass in solar mass.
   * @return Dust density at that radius of the cloud
   */
  def outerDustLimit(mass: Double): Double = 200 * Math.pow(mass, 1.0 / 3.0)

  /**
   * Method to calculate dust cloud density at a given radius. Formula taken from "Formation of Planetary Systems
   * by Aggregation: A Computer Simulation" in section a) Initial Conditions in the Cloud.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param radius - the current distance from the stellar mass in AU
   * @return Dust density at that radius of the cloud
   */
  def dustCloudDensity(radius: Double): Double = DUST_DENSITY_COEFF * Math.exp(-ALPHA * Math.pow(radius, 1.0 / N))

  /**
   * Method to calculate total mass density in situations where critical mass has been reached and the protoplanet is
   * accreting gas as well as dust. Formula comes from c) Aggregation in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation"
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param dustDensity - the current dust density value
   * @param criticalMass - the critical mass limit of the protoplanet
   * @param mass - the current mass of the protoplanet
   * @return the current Mass density
   */
  def cloudDensity(dustDensity: Double, criticalMass: Double, mass: Double): Double = {
    K * dustDensity / (1.0 + Math.sqrt(criticalMass / mass) * (K - 1.0))
  }

  /**
   * Method to calculate total mass density in situations where critical mass has been reached and the protoplanet is
   * accreting gas as well as dust. A Formula similar to this is alluded to in c) Aggregation in "Formation of Planetary
   * Systems by Aggregation: A Computer Simulation" but unfortunately I have not been able to discover a source for
   * this earlier than the earliest of recreating simulations.
   *
   * @param mass mass of closest protoplanet in Solar Mass.
   * @param axis axis of closest protoplanet in AU.
   * @param ecc eccentricity of closest protoplanet.
   * @param iSweep inner sweep distance of the protoplanet in AU.
   * @param oSweep outer sweep distance of the protoplant in AU.
   * @param iEdge inner edge of the dust band in AU.
   * @param oEdge outer edge of the dust band in AU.
   * @return
   */
  def bandVolume(mass: Double, axis: Double, ecc: Double,
                 iSweep: Double, oSweep: Double, iEdge: Double, oEdge: Double): Double = {

    val relativeMass = muMassFunction(mass)
    val bandwidth: Double = oSweep - iSweep

    var outside = oSweep - oEdge
    if (outside < 0.0) outside = 0.0

    var inside = iEdge - iSweep
    if (inside < 0.0) inside = 0.0

    val width = bandwidth - outside - inside

    val term1 = 4.0 * Math.PI * axis * axis
    val term2 = term1 * relativeMass * (1.0 - ecc * (outside - inside) / bandwidth)

    term2 * width
  }

  /**
   * Method to produce the semi major axis of a planet. Formula taken from "Formation of Planetary Systems
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
   * Method to produce the eccentricity of a planet. Formula taken from "Formation of Planetary Systems
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
   * @return eccentricity between 0.0 and 1.0, essential for a planet to stay in the system.
   */
  def eccentricity(rand: Random): Double = 1.0 - Math.pow(rand.nextDouble(), ECCENTRICITY_COEFF)

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
  def shouldAccreteContinue(oldMass: Double, newMass: Double): Boolean = !(newMass - oldMass < 0.0001 * oldMass)

  /**
   * Method to calculate whether a protoplanet has gained enough mass to accrete gas as well as dust, see "c)
   * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param perihelion closest protoplanet gets to the sun.
   * @return critical mass in solar mass (M?).
   */
  def criticalMass(perihelion: Double): Double = B * Math.pow(perihelion, -0.75)

  /**
   * Method to calculate whether two coalescing protoplanets have collided. see "d)
   * Coalesence of Planets" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
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
    val outer = outerGravLimit(aphelionDistance(axis1, ecc1), mass1) - axis1
    val inner = axis2 - innerGravLimit(perihelionDistance(axis2, ecc2), mass2)

    (Math.abs(dist) <= outer) || (Math.abs(dist) <= inner)
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
   * Method is used to calculate the outer distance at which the protoplanet nuclei will attract
   * particles by gravitation attraction.
   *
   * @note equivalent of ra + xa in dole's paper.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @param aphelion the furthest distance between the body and its host star in AU.
   * @param mass the mass of the body in solar mass (M?).
   * @return the aphelion + the gravitational pull distance in AU.
   */
  def outerGravLimit(aphelion: Double, mass: Double) = aphelion * (1.0 + muMassFunction(mass))

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

  def eccTerm(axis: Double, ecc: Double, mass: Double): Double = {
    mass * Math.sqrt(axis) * Math.sqrt(1.0 - ecc * ecc)
  }
}