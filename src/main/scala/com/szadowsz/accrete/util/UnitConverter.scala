package com.szadowsz.accrete.util

import com.szadowsz.accrete.base.constants.UnitConstants

/**
 * @author Zakski : 03/07/2015.
 */
object UnitConverter extends UnitConstants {

  def solarMassToEarthMass(sunMass: Double) = sunMass * SOLAR_MASS_IN_EARTH_MASS
}
