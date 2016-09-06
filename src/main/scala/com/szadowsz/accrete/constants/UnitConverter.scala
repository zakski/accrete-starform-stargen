package com.szadowsz.accrete.constants

/**
  * @author Zakski : 03/07/2015.
  */
object UnitConverter extends MassConstants {

  def solarMassToEarthMass(sunMass: Double): Double = sunMass * SOLAR_MASS_IN_EARTH_MASS
}
