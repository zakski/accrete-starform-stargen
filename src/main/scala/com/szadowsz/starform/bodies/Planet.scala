package com.szadowsz.starform.bodies

import com.szadowsz.accrete.bodies.{Planetismal, ProtoPlanet}


/**
  * Class to represent TODO.
  *
  * @param proto the basic characteristics of the accreted planetary body.
  *
  * @author Zakski : 20/07/2015.
  */
class Planet(proto: ProtoPlanet) extends Planetismal {

  /**
    * The mass of the body.
    *
    * @note unit of value is Solar Masses.
    */
  override val mass: Double = proto.mass

  /**
    * The semi-major axis of the body's orbit.
    *
    * @note unit of value is AU.
    */
  override val axis: Double = proto.axis

  /**
    * The Eccentricity of the body's orbit. How wildly it deviates from the semi-major axis during the course of one
    * revolution around its planetary body.
    *
    * @note value between 0.0 (inclusive) and 1.0 (exclusive), this range is essential for the body to stay
    *       in the system.
    */
  override val ecc: Double = proto.ecc

  /**
    * The closest to the star that the planet will be during its orbit.
    *
    * @note unit of value is AU.
    */
  override val perihelion: Double = proto.perihelion

  /**
    * The furthest from the star that the planet will be during its orbit..
    *
    * @note unit of value is AU.
    */
  override val aphelion: Double = proto.aphelion

  /**
    * Whether the planet has surpassed its critical mass limit and become a gas giant.
    */
  override val isGasGiant: Boolean = proto.isGasGiant

  //  /**
  //    * the average radius of a planet, calculated using eq.9 in Fogg's article, although some typos
  //    * crop up in that eq. Originally from eq 23 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
  //    *
  //    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
  //    * @see The Internal Constitution of Planets - D. S. Kothari
  //    *
  //    * @note unit is km rather than in terms of earth.
  //    */
  //  val equatorialRadius = calc.kothariRadius(mass, isGas, orbitalZone)
  //
  //  val density = calc.empiricalDensity(mass, axis, calc.getStarEcosphereRadius)
  //
  //  val angularVelocity = calc.totalAngularVelocity(mass, equatorialRadius, axis, isGas, density)
  //
  //  val orbitLength = calc.orbitLength(axis, mass, calc.getStarMass)
  //
  //  val dayLength = calc.dayLength(angularVelocity, orbitLength, ecc)
  //
  //  val gravity = calc.surfaceGravity(mass, equatorialRadius)
  //
  //  val escapeVelocity = calc.escapeVelocity(gravity, equatorialRadius)
  //
  //  val rmsSpeed = calc.speedRMS(calc.MOLECULAR_NITROGEN, equatorialRadius)
  //
  //  val volatileGasInventory = calc.vGasInventory(mass, escapeVelocity, rmsSpeed, orbitalZone,
  //    calc.suffersGreenhouseEffect(axis, calc.getStarGreenhouseRadius), calc.getStarMass)
  //
  //  val surfacePressure = calc.surfacePressure(volatileGasInventory, equatorialRadius, gravity_inGs)
  //
  //  def gravity_inGs: Double = UnitConverter.mSec2ToGs(gravity)
  //
  //  //  double molecule_weight;	/* smallest molecular weight retained*/
  //  //  double boil_point;		/* the boiling point of water (Kelvin)*/
  //  //  double albedo;		/* albedo of the planet		     */
  //  //  double surf_temp;   	/* surface temperature in Kelvin     */
  //  //  double hydrosphere;		/* fraction of surface covered	     */
  //  //  double cloud_cover;		/* fraction of surface covered	     */
  //  //  double ice_cover;		/* fraction of surface covered	     */
}
