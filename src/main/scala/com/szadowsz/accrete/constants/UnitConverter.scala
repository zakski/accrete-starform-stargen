package com.szadowsz.accrete.constants

import com.szadowsz.accrete.constants.units.UnitConstants

/**
  * @author Zakski : 03/07/2015.
  */
object UnitConverter extends UnitConstants {

  def solarMassToEarthMass(sunMass: Double): Double = sunMass * SOLAR_MASS_IN_EARTH_MASS

  def solarMassToKilograms(sunMass: Double): Double = sunMass * SOLAR_MASS_IN_KG

  def solarMassToGrams(sunMass: Double): Double = sunMass * SOLAR_MASS_IN_GRAMS

  def kmToM(kilograms: Double): Double = kilograms * METERS_PER_KM

  def kmToCm(kilograms: Double): Double = kilograms * CM_PER_KM

  def mToKm(meters: Double): Double = meters / METERS_PER_KM

  def radSecToHoursPerRotation(radSec: Double): Double = 1 / radSecToRotationsPerHour(radSec)

  def radSecToRotationsPerHour(radSec: Double): Double = (SECONDS_PER_HOUR * radSec) / TWO_PI

  def mSec2ToGs(acceleration: Double): Double = acceleration / EARTH_GRAVITY

}
