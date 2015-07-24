package com.szadowsz.accrete.base.calc

import com.szadowsz.accrete.base.constants.AccreteConstants

/**
 * Calculations specific to the formation of the star and the dust cloud.
 *
 * @author Zakski : 03/06/2015.
 */
trait AccreteCalc {
  this: PlanetesimalCalc with AccreteConstants =>

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
}