package com.szadowsz.starform

import com.szadowsz.accrete.AccreteSimulation
import com.szadowsz.accrete.bodies.{Planetismal, ProtoPlanet}
import com.szadowsz.accrete.calc.CollisionCalc
import com.szadowsz.starform.bodies.Star
import com.szadowsz.starform.calc._
import com.szadowsz.starform.constants.StarformConstants
import com.szadowsz.starform.constants.unit.UnitConstants

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation extends AccreteSimulation {
  this: StarformAccrCalc with StarformPlanCalc with StarformRandCalc with StarCalc with EcoCalc with CollisionCalc with StarformConstants with UnitConstants =>

  val star: Star

//  def iterate_surface_temp(surfPressure : Double) = {
//    var optical_depth = opacity(planet.molecule_weight, surfPressure)
//    var effective_temp = effectiveTemperature(star.meanHabitableRadius, planet.a, EARTH_ALBEDO)
//    var greenhouse_rise = green_rise(optical_depth, effective_temp, surfPressure)
//    var surf1_temp = effective_temp + greenhouse_rise
//    previous_temp = surf1_temp - 5.0 /* force the while loop the first time */
//
//    while ((fabs(surf1_temp - previous_temp) > 1.0)) {
//      previous_temp = surf1_temp
//      water = hydrosphere_fraction(planet.volatile_gas_inventory, planet.radius)
//      clouds = cloud_fraction(surf1_temp, planet.molecule_weight, planet.radius, water)
//      ice = ice_fraction(water, surf1_temp)
//      if ((surf1_temp >= planet.boil_point) || (surf1_temp <= FREEZING_POINT_OF_WATER))
//        water = 0.0
//      albedo = planet_albedo(water, clouds, ice, surfPressure)
//      optical_depth = opacity(planet.molecule_weight, surfPressure)
//      effective_temp = effectiveTemperature(star.meanHabitableRadius, planet.a, albedo)
//      greenhouse_rise = green_rise(optical_depth, effective_temp, surfPressure)
//      surf1_temp = effective_temp + greenhouse_rise
//    }
//
//    (water, clouds, ice, albedo, surf1_temp)
//  }

  def buildEcosphere(proto: ProtoPlanet): Planetismal = {
    val orbitZone: Int = orbitalZone(star.luminosity, proto.axis)

    val equatorialRadius = kothariRadius(proto.mass, proto.isGasGiant, orbitZone)

    val density = if (proto.isGasGiant) volumeDensity(proto.mass, equatorialRadius) else empiricalDensity(proto.mass, proto.axis, star.meanHabitableRadius)

    val angularVelocity = totalAngularVelocity(star.mass, star.age, proto.mass, equatorialRadius, proto.axis, density, proto.isGasGiant)
    val lengthOfOrbit = orbitLength(proto.axis, proto.mass, star.mass)
    val (synch, resonant, lengthOfDay) = dayLength(angularVelocity, lengthOfOrbit, proto.ecc)

    val gravity = surfaceGravity(proto.mass, equatorialRadius)
    val escapeVel = escapeVelocity(gravity, equatorialRadius)
    val rmsSpeed = speedRMS(MOLECULAR_NITROGEN, equatorialRadius)

    val suffersFromGE = suffersGreenhouseEffect(proto.axis, star.innerHabitableRadius)
    val retainsGas = hasGasRetention(escapeVel, rmsSpeed)
    val volatileGasInventory = vGasInventory(rand, proto.mass, orbitZone, retainsGas, suffersFromGE, star.mass)

    val surfPressure = surfacePressure(volatileGasInventory, equatorialRadius, gravity)
    proto
  }
}
