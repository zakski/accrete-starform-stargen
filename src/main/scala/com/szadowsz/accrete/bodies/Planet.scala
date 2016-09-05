package com.szadowsz.accrete.bodies

import java.text.DecimalFormat

import com.szadowsz.accrete.constants.UnitConverter

object Planet {

  def apply(proto: ProtoPlanet): Planet = {
    new Planet(proto)
  }
}

/**
  * Class to represent the final planetary body.
 *
 * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
 * @see struct planets_record, line 4 in structs.h - Mat Burdick (starform)
  * @see Planet.java - Carl Burke (starform)
 *
 *
 * @param proto the basic characteristics of the accreted planetary body.

  * @author Zakski : 31/12/2015.
 */
class Planet(proto: ProtoPlanet) {

  /**
    * The mas of the planetary body.
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
    * revolution around its star.
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

  override def toString: String = {
    var df: DecimalFormat = new DecimalFormat("#.00000")
    val build: StringBuilder = new StringBuilder("[axis: ")
    build.append(df.format(axis) + "AU eccentricity: ")
    build.append(df.format(ecc) + " mass: ")
    df = new DecimalFormat("#.00000E00")
    build.append(df.format(mass))
    if (mass > 2e-15) {
      df = new DecimalFormat("#.00")
      build.append(" (" + df.format(UnitConverter.solarMassToEarthMass(mass) * 100) + "% of Earth Mass)")
    }
    build.append(" gasGiant: " + (if (isGas) "Y" else "N"))
    build.append("]")
    build.toString()
  }
}
