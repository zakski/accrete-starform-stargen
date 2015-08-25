package com.szadowsz.accrete.util

import com.szadowsz.accrete.base.constants.unit.UnitConstants

/**
 * @author Zakski : 03/07/2015.
 */
object UnitConverter extends UnitConstants {

  def solarMassToEarthMass(sunMass: Double) = sunMass * SOLAR_MASS_IN_EARTH_MASS

  def solarMassToKilograms(sunMass: Double) = sunMass * SOLAR_MASS_IN_KG

  def solarMassToGrams(sunMass: Double) = sunMass * SOLAR_MASS_IN_GRAMS

  def kmToM(kilograms: Double) = kilograms * METERS_PER_KM

  def mToKm(meters: Double) = meters / METERS_PER_KM

  def kmToCm(kilograms: Double) = kilograms * CM_PER_KM

  def radSecToHoursPerRotation(radSec: Double) = 1 / radSecToRotationsPerHour(radSec)

  def radSecToRotationsPerHour(radSec: Double) = (SECONDS_PER_HOUR * radSec) / TWO_PI

  def mSec2ToGs(acceleration: Double) = acceleration / EARTH_GRAVITY

}
