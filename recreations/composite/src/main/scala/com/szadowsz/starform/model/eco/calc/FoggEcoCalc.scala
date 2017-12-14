package com.szadowsz.starform.model.eco.calc

import com.szadowsz.starform.model.eco.constants.EcoConstants

/**
  * Created on 13/04/2017.
  */
class FoggEcoCalc extends EcoCalc with EcoConstants {

  def atmosphere(zone: Int, surfacePressure: Double, suffersGE: Boolean, isGiant: Boolean): Atmosphere = {
    // IF It is a Gas Giant
    if (isGiant) {
      Atmosphere.GAS_GIANT // RETURN Gas Giant Atmosphere
      // ELSE
    } else {
      // IF Does Not Retains Atmosphere
      if (surfacePressure < 1.0) {
        if (zone == 3) Atmosphere.AIRLESS_ICE else Atmosphere.AIRLESS_ROCK // IF Zone 3, RETURN Icy Airless Atmosphere ELSE RETURN Rocky Airless Atmosphere
        // ELSE
      } else {
        zone match {
          case 3 => Atmosphere.ATMOS_VII // IF Zone 3, RETURN Icy Atmosphere VII
          case 2 => Atmosphere.ATMOS_III // IF Zone 2, RETURN Atmosphere III
          case 1 if suffersGE => Atmosphere.ATMOS_II_VENUS // IF Zone 1 AND Suffering Runaway Greenhouse effect, RETURN Venus Atmosphere II
          case _ => Atmosphere.FEEDBACK_MODEL // ELSE RETURN Atmosphere I,II or V
        }
      }
    }
  }

  def getInitialAlbedo(a: Atmosphere): Double = {
    a match {
      case Atmosphere.GAS_GIANT => GAS_GIANT_ALBEDO
      case Atmosphere.AIRLESS_ROCK => AIRLESS_ROCKY_ALBEDO
      case Atmosphere.AIRLESS_ICE => AIRLESS_ICE_ALBEDO
      case Atmosphere.FEEDBACK_MODEL => EARTH_ALBEDO
      case Atmosphere.ATMOS_II_VENUS => ATMOSPHERE_II_V_ALBEDO
      case Atmosphere.ATMOS_III => ATMOSPHERE_III_ALBEDO
      case Atmosphere.ATMOS_VII => ATMOSPHERE_VII_ALBEDO
    }
  }

  def calcClimate(
                   ecoRadius: Double,
                   axis: Double,
                   eqRadius: Double,
                   surfPressure: Double,
                   volatileGasInventory: Double,
                   molecularWeight: Double,
                   atmosphere: Atmosphere
                 ): (Double, Double, Double, Double, Double) = {
    var clouds = Double.NaN
    var ice = Double.NaN
    var albedo = getInitialAlbedo(atmosphere)
    var surfTemperature = effectiveTemperature(ecoRadius, axis, albedo)
    var water = hydrosphereFraction(volatileGasInventory, eqRadius)

    if (atmosphere == Atmosphere.FEEDBACK_MODEL) {
      var previous = Double.NaN
      val boilPoint = boilingPoint(surfPressure)
      do {
        previous = surfTemperature
        clouds = cloudFraction(surfTemperature)
        water = hydrosphereFraction(volatileGasInventory, eqRadius)
        ice = iceFraction(water, surfTemperature)

        if ((surfTemperature >= boilPoint) || (surfTemperature <= FREEZING_POINT_OF_WATER)) {
          water = 0.0
        }

        albedo = calcAlbedo(water, clouds, ice)
        val optical_depth = opacity(molecularWeight, surfPressure)
        val effectiveTemp = effectiveTemperature(ecoRadius, axis, albedo)
        val greenhouseDelta = greenhouseEffectDelta(optical_depth, effectiveTemp, surfPressure)
        surfTemperature = effectiveTemp + greenhouseDelta
      } while (Math.abs(surfTemperature - previous) > 1.0)
    }
    (water, clouds, ice, albedo, surfTemperature)
  }
}