package com.szadowsz.stargen.base.starform

import com.szadowsz.stargen.base.accrete.AccreteSimulation
import com.szadowsz.stargen.base.accrete.calc.CollisionCalc
import com.szadowsz.stargen.base.accrete.system.bodies.{Planetismal, ProtoPlanet}
import com.szadowsz.stargen.base.accrete.util.stats.SimulationStats
import com.szadowsz.stargen.base.starform.calc._
import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.constants.unit.UnitConstants
import com.szadowsz.stargen.base.starform.system.AbstractStarSystem
import com.szadowsz.stargen.base.starform.system.bodies.{Planet, Star}

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation[S <: Star, H <: SimulationStats[H], R <: AbstractStarSystem[S, H, Planet]] extends AccreteSimulation[H, Planet, R] {
  this: StarformAccrCalc[S]
    with StarformPlanCalc[S]
    with StarformRandCalc[S]
    with StarCalc[S]
    with EcoCalc[S]
    with CollisionCalc
    with StarformConstants[S]
    with UnitConstants =>


  protected def initStar(): S

  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  final protected def generatePlanets(): List[Planet] = {
    star = initStar()
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

    def molecule_limit(mass: Double, escapeVel: Double,equat_radius: Double): Double = {
       if (escapeVel == 0.0) return 0.0
      (3.0 * Math.pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * (MOLAR_GAS_CONST * EXOSPHERE_TEMP)) / (escapeVel * escapeVel)
    }

  protected def buildEcosphere(proto: Planetismal): Planet = {
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
}
