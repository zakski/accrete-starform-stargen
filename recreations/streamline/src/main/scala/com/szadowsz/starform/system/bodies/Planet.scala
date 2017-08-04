package com.szadowsz.starform.system.bodies

import com.szadowsz.starform.model.eco.UWPCalc

/**
  * Created on 04/08/2017.
  */
class Planet(
              proto: Planetismal,
              val equatorialRadius: Double,
              val density: Double,
              val orbitLength: Double,
              val dayLength: Double,
              val gravity: Double,
              val surfacePressure: Double,
              val hydrosphere: Double,
              val cloudCover: Double,
              val iceCover: Double,
              val albedo: Double,
              val surfaceTemperature: Double,
              val tilt: Double,
              val dayTemp: Double,
              val nightTemp: Double,
              val minTemp: Double,
              val maxTemp: Double
            )
  extends Planetismal with UWPCalc {

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

  val uwp : String = "X-" + calcUWPSize(equatorialRadius) + calcUWPAtmos(surfacePressure) + calcUWPHydrographics(hydrosphere,iceCover) + "XXX-X"
}