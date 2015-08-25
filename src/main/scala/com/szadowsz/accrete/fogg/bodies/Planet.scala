package com.szadowsz.accrete.fogg.bodies

import com.szadowsz.accrete.base.bodies.ProtoPlanet
import com.szadowsz.accrete.fogg.calc.FoggPlanCalc
import com.szadowsz.accrete.fogg.constants.FoggConstants
import com.szadowsz.accrete.util.UnitConverter

/**
 * Class to represent an accreting proto planetary body. Uses an internal linked-list structure to maintain the
 * ordering of the protoplanets.
 *
 * @see Planetismal.java - Ian Burrell (accrete)
 * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
 * @see struct planets_record, line 4 in structs.h - Mat Burdick (starform)
 * @see Protoplanet.java - Carl Burke (starform)
 *
 * @constructor Constructor is used make all subsequent dust bands during the splitting process, in which we
 *              acknowledge dust and gas being removed from part of existing bands.
 *
 * @param calc inner limit of the dust band in AU.
 * @param proto the basic characteristics of the accreted planetary body.

 * @author Zakski : 20/07/2015.
 */
class Planet(calc: FoggPlanCalc with FoggConstants, proto: ProtoPlanet) {

  /**
   * The mas of the planetismal body.
   *
   * @note unit of value is Solar Masses.
   */
  val mass: Double = proto.mass

  /**
   * The semi-major axis of the body's orbit.
   *
   * @note unit of value is AU.
   */
  val axis: Double = proto.axis

  /**
   * The Eccentricity of the body's orbit. How wildly it deviates from the semi-major axis during the course of one
   * revolution around its planetary body.
   *
   * @note value between 0.0 (inclusive) and 1.0 (exclusive), this range is essential for the body to stay
   *       in the system.
   */
  val ecc: Double = proto.ecc

  /**
   * Whether the planet has surpassed its critical mass limit and become a gas giant.
   */
  val isGas = proto.isGas

  /**
   * The furthest from the star that the planet will be during its orbit..
   *
   * @note unit of value is AU.
   */
  val aphelion = proto.aphelion

  /**
   * The closest to the star that the planet will be during its orbit.
   *
   * @note unit of value is AU.
   */
  val perihelion = proto.perihelion

  /**
   * the orbital zone of a planet extrapolated from "5. Planetary Characteristics" in Extra-Solar
   * Planetary Systems: A Microcomputer Simulation by Mat Burdick.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   * @note between 1-3, inclusive
   */
  val orbitalZone = calc.orbitalZone(axis)

  /**
   * the average radius of a planet, calculated using eq.9 in Fogg's article, although some typos
   * crop up in that eq. Originally from eq 23 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see The Internal Constitution of Planets - D. S. Kothari
   *
   * @note unit is km rather than in terms of earth.
   */
  val equatorialRadius = calc.kothariRadius(mass, isGas, orbitalZone)

  val density = calc.empiricalDensity(mass, axis, calc.getStarEcosphereRadius)

  val angularVelocity = calc.totalAngularVelocity(mass, equatorialRadius, axis, isGas, density)

  val orbitLength = calc.orbitLength(axis, mass, calc.getStarMass)

  val dayLength = calc.dayLength(angularVelocity, orbitLength, ecc)

  val gravity = calc.surfaceGravity(mass, equatorialRadius)

  val escapeVelocity = calc.escapeVelocity(gravity, equatorialRadius)

  val rmsSpeed = calc.speedRMS(calc.MOLECULAR_NITROGEN, equatorialRadius)

  val volatileGasInventory = calc.vGasInventory(mass, escapeVelocity, rmsSpeed, orbitalZone,
    calc.suffersGreenhouseEffect(axis, calc.getStarGreenhouseRadius), calc.getStarMass)

  val surfacePressure = calc.surfacePressure(volatileGasInventory, equatorialRadius, gravity_inGs)

  def gravity_inGs: Double = UnitConverter.mSec2ToGs(gravity)

  //  int resonant_period;	/* TRUE if in resonant rotation   */
  //  int axial_tilt;		/* units of degrees		     */
  //  double molecule_weight;	/* smallest molecular weight retained*/
  //  double boil_point;		/* the boiling point of water (Kelvin)*/
  //  double albedo;		/* albedo of the planet		     */
  //  double surf_temp;   	/* surface temperature in Kelvin     */
  //  double hydrosphere;		/* fraction of surface covered	     */
  //  double cloud_cover;		/* fraction of surface covered	     */
  //  double ice_cover;		/* fraction of surface covered	     */

}
