package com.szadowsz.dole.bodies

import com.szadowsz.accrete.bodies.{Planetismal, ProtoPlanet}
import com.szadowsz.dole.calc.DoleCalc

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
  * @param calc
  * @param m The mass of the body.
  * @param a The semi-major axis of the body's orbit.
  * @param e The Eccentricity of the body's orbit.
  *
  * @author Zakski : 25/06/2015.
  */
class DolePlanet(val calc: DoleCalc, m: Double, a: Double, e: Double) extends ProtoPlanet(m,a,e) {

  /**
    * The closest to the star that the planet will be during its orbit.
    *
    * @note unit of value is AU.
    */
  override def perihelion: Double = calc.perihelionDistance(axis, ecc)

  /**
    * The furthest from the star that the planet will be during its orbit..
    *
    * @note unit of value is AU.
    */
  override def aphelion: Double = calc.aphelionDistance(axis, ecc)

  /**
    * The closest to the star that the planet will accrete mass from, given gravitational pull.
    *
    * @note unit of value is AU.
    */
  override def innerGravLimit: Double = calc.innerGravLimit(perihelion, mass)

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull.
    *
    * @note unit of value is AU.
    */
  override def outerGravLimit: Double = calc.outerGravLimit(aphelion, mass)

  /**
    * The closest to the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  override def innerBandLimit: Double = calc.innerBandLimit(innerGravLimit)

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  override def outerBandLimit: Double = calc.outerBandLimit(outerGravLimit)

  /**
    * the limit at which a proto planet has gained enough mass to accrete gas as well as dust
    *
    * @note unit of value is Solar Masses.
    */
  override def criticalMass: Double = calc.criticalMass(perihelion)
}
