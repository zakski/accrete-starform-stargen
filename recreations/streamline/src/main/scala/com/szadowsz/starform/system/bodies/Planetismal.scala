package com.szadowsz.starform.system.bodies

import java.text.DecimalFormat

/**
  * Outline of an accreting proto-planetary body. Defines the basic members required for the aggregation part of simulation.
  *
  * @see Planetismal.java - Ian Burrell (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
  * @see struct Band, line 95 in Dole.c - Andrew Folkins (accretion)
  * @see struct Band, line 104 in dole.c - Keris (accretion v1)
  * @see struct Band, line 178 in dole.cc - Keris (accretion v2)
  * @see struct dust_record, line 39 in structs.h - Keris (starform)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (starform)
  * @see Protoplanet.java - Carl Burke (starform)
  *
  * @author Zakski : 25/06/2015.
  */
trait Planetismal {

  /**
    * The mass of the body.
    *
    * @note unit of value is Solar Masses.
    */
  def mass: Double

  /**
    * The semi-major axis of the body's orbit.
    *
    * @note unit of value is AU.
    */
  def axis: Double

  /**
    * The Eccentricity of the body's orbit. How wildly it deviates from the semi-major axis during the course of one
    * revolution around its planetary body.
    *
    * @note value between 0.0 (inclusive) and 1.0 (exclusive), this range is essential for the body to stay
    *       in the system.
    */
  def ecc: Double

  /**
    * The closest to the star that the planet will be during its orbit.
    *
    * @note unit of value is AU.
    */
  def perihelion: Double

  /**
    * The furthest from the star that the planet will be during its orbit..
    *
    * @note unit of value is AU.
    */
  def aphelion: Double

  /**
    * Whether the planet has surpassed its critical mass limit and become a gas giant.
    */
  def isGasGiant: Boolean


  override def equals(obj: Any): Boolean = {
    obj match {
      case p : Planetismal =>
        mass == p.mass && ecc == p.ecc && axis == p.axis && isGasGiant == p.isGasGiant
      case _ => false
    }
  }

  /**
    * Method to supply String representation of the proto planet.
    *
    * @return current status of the  proto planet in String form.
    */
  override def toString: String = {
    var df: DecimalFormat = new DecimalFormat("#.00000")
    val build: StringBuilder = new StringBuilder("[axis: ")
    build.append(df.format(axis) + " AU eccentricity: ")
    build.append(df.format(ecc) + " mass: ")
    df = new DecimalFormat("#.00000E00")
    build.append(df.format(mass))
    build.append(" M☉ gasGiant: " + (if (isGasGiant) "Y" else "N"))
    build.append("]")
    build.toString()
  }
}