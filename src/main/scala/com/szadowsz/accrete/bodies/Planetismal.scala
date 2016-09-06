package com.szadowsz.accrete.bodies

import java.text.DecimalFormat

/**
  * Abstract Outline Class to represent an accreting proto-planetary body. Defines the basic members required for the aggregation part of simulation.
  *
  * @see Planetismal.java - Ian Burrell (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
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
    * The closest to the star that the planet will accrete mass from, given gravitational pull.
    *
    * @note unit of value is AU.
    */
  def innerGravLimit: Double

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull.
    *
    * @note unit of value is AU.
    */
  def outerGravLimit: Double


  /**
    * The closest to the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  def innerBandLimit: Double

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  def outerBandLimit: Double

  /**
    * the limit at which a proto planet has gained enough mass to accrete gas as well as dust
    *
    * @note unit of value is Solar Masses.
    */
  def criticalMass: Double


  /**
    * Whether the planet has surpassed its critical mass limit and become a gas giant.
    */
  def isGasGiant: Boolean = mass >= criticalMass

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