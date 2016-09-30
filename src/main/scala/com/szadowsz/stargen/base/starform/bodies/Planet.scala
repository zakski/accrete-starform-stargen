package com.szadowsz.stargen.base.starform.bodies

import com.szadowsz.stargen.base.accrete.bodies.Planetismal

/**
  * Class to represent TODO.
  *
  * @param proto the basic characteristics of the accreted planetary body.
  *
  * @author Zakski : 20/07/2015.
  */
class Planet(
              proto: Planetismal,
              eqRad: Double,
              den: Double,
              lengthOfOrbit: Double,
              lengthOfDay: Double,
              grav: Double,
              surfPressure: Double,
              water: Double,
              clouds: Double,
              ice: Double,
              alb: Double,
              surfTemp: Double
            )
  extends Planetismal {

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

  val equatorialRadius = eqRad

  val density = den

  val orbitLength = lengthOfOrbit

  val dayLength = lengthOfDay

  val gravity = grav

  val surfacePressure = surfPressure

  val hydrosphere = water

  val cloudCover = clouds

  val iceCover = ice

  val albedo = alb

  val surfaceTemperature = surfTemp
}
