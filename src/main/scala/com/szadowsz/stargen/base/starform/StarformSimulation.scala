package com.szadowsz.stargen.base.starform

import com.szadowsz.stargen.base.accrete.AccreteSimulation
import com.szadowsz.stargen.base.accrete.bodies.Planetismal
import com.szadowsz.stargen.base.accrete.calc.CollisionCalc
import com.szadowsz.stargen.base.starform.bodies.{Planet, Star}
import com.szadowsz.stargen.base.starform.calc._
import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.constants.unit.UnitConstants

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation extends AccreteSimulation {
  this: StarformAccrCalc with StarformPlanCalc with StarformRandCalc with StarCalc with EcoCalc with CollisionCalc with StarformConstants with UnitConstants =>

  val star: Star

  def molecule_limit(mass: Double, escapeVel: Double,equat_radius: Double): Double = {
     if (escapeVel == 0.0) return 0.0
    (3.0 * Math.pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * (MOLAR_GAS_CONST * EXOSPHERE_TEMP)) / (escapeVel * escapeVel)
  }

  def buildEcosphere(proto: Planetismal): Planet = {
    val orbitZone: Int = orbitalZone(star.luminosity, proto.axis)

    val (equatorialRadius, density) = radiusAndDensity(proto.mass, proto.axis, star.meanHabitableRadius, proto.isGasGiant, orbitZone)

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
    val atmos = atmosphere(orbitZone, surfPressure, suffersFromGE, proto.isGasGiant)
    val mw = molecule_limit(proto.mass,escapeVel,equatorialRadius)
    val (water, clouds, ice, albedo, surfTemp) = calcClimate(star.meanHabitableRadius,proto.axis, equatorialRadius, surfPressure, volatileGasInventory, mw,
      atmos)


    new Planet(proto, equatorialRadius, density, lengthOfOrbit, lengthOfDay, gravity, surfPressure, water, clouds, ice, albedo, surfTemp)
  }

  def generateSystems(): (Star, List[Planet]) = (star, generateProtoplanets().map(buildEcosphere))
}
