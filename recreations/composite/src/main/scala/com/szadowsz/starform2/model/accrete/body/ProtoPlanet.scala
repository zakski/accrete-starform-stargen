package com.szadowsz.starform2.model.accrete.body

import com.szadowsz.starform2.model.accrete.calc.PlanetesimalCalc
import com.szadowsz.starform2.system.body.{Planetismal, Star}

/**
  * Class to represent an accreting proto planetary body. Adds variable mass/axis/ecc to the Planetismal trait to allow for easier alteration during
  * the accretion process.
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
  * @constructor Constructor is used make all protoplanets during the accretion process.
  *
  * @param mass The mass of the body.
  * @param axis The semi-major axis of the body's orbit.
  * @param ecc The Eccentricity of the body's orbit.
  *
  * @author Zakski : 25/06/2015.
  */
class ProtoPlanet(val star : Star, val calc: PlanetesimalCalc, var mass: Double, var axis: Double, var ecc: Double) extends Planetismal {

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
  def innerGravLimit: Double = calc.innerGravLimit(perihelion, mass)

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull.
    *
    * @note unit of value is AU.
    */
  def outerGravLimit: Double = calc.outerGravLimit(aphelion, mass)

  /**
    * The closest to the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  def innerBandLimit: Double = calc.innerBandLimit(innerGravLimit)

  /**
    * The furthest from the star that the planet will accrete mass from, given gravitational pull and
    * cloud particle eccentricity.
    *
    * @note unit of value is AU.
    */
  def outerBandLimit: Double = calc.outerBandLimit(outerGravLimit)

  /**
    * the limit at which a proto planet has gained enough mass to accrete gas as well as dust
    *
    * @note unit of value is Solar Masses.
    */
  def criticalMass: Double = calc.criticalMass(star.luminosity,perihelion)


  /**
    * Whether the planet has surpassed its critical mass limit and become a gas giant.
    */
  override def isGasGiant: Boolean = mass >= criticalMass
}
