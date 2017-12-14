package com.szadowsz.starform2

import com.szadowsz.starform2.model.accrete.AccreteStats
import com.szadowsz.starform2.model.{SimulationStats, StarformProfile, StarformSimulation}
import com.szadowsz.starform2.model.eco.calc.FoggEcoCalc
import com.szadowsz.starform2.model.star.consts.StarConstants
import com.szadowsz.starform2.system.StarformSystem
import com.szadowsz.starform2.system.body.Planetismal
import com.szadowsz.starform2.system.body.planet.FoggPlanet
import com.szadowsz.starform2.system.body.star.FoggStar
import com.szadowsz.starform2.unit.UnitConverter

case class FoggSimulation[C <: StarConstants](profile: StarformProfile[FoggStar, C, FoggEcoCalc])
  extends StarformSimulation[FoggStar, FoggPlanet, C, SimulationStats, StarformSystem[FoggStar, SimulationStats, FoggPlanet], FoggEcoCalc](profile) {

  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[AccreteStats]] instance.
    */
  override protected def initStats(): SimulationStats = new SimulationStats()

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[StarformSystem]] instance.
    */
  override protected def createSystem(seed: Long, stats: SimulationStats, planets: List[FoggPlanet]): StarformSystem[FoggStar, SimulationStats, FoggPlanet] = {
    StarformSystem(seed, stats, star, planets)
  }

  override protected def buildEcosphere(proto: Planetismal): FoggPlanet = {
    val orbitZone: Int = eCalc.orbitalZone(star.luminosity, proto.axis)

    val (eqRadius, density) = eCalc.radiusAndDensity(proto.mass, proto.axis, star.meanHabitableRadius, proto.isGasGiant, orbitZone)

    val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, proto.mass, eqRadius, proto.axis, density, proto.isGasGiant)
    val lengthOfOrbit = eCalc.orbitLength(proto.axis, proto.mass, star.mass)
    val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, lengthOfOrbit, proto.ecc)

    val gravity = eCalc.surfaceGravity(proto.mass, eqRadius)
    val escapeVel = eCalc.escapeVelocity(UnitConverter.mToKm(gravity), eqRadius)
    val rmsSpeed = eCalc.speedRMS(eCalc.MOLECULAR_NITROGEN, eqRadius)

    val suffersFromGE = eCalc.suffersGreenhouseEffect(proto.axis, star.innerHabitableRadius)
    val retainsGas = eCalc.hasGasRetention(escapeVel, rmsSpeed)
    val vGasInventory = eCalc.vGasInventory(rand, proto.mass, orbitZone, retainsGas, suffersFromGE, star.mass)

    val surfPressure = eCalc.surfacePressure(vGasInventory, eqRadius, gravity)
    val atmos = eCalc.atmosphere(orbitZone, surfPressure, suffersFromGE, proto.isGasGiant)
    val mw = eCalc.moleculeLimit(proto.mass, escapeVel, eqRadius)
    val (water, clouds, ice, albedo, surfTemp) = eCalc.calcClimate(star.meanHabitableRadius, proto.axis, eqRadius, surfPressure, vGasInventory, mw, atmos)

    val tilt = eCalc.inclination(rand, proto.axis)

    new FoggPlanet(proto, eqRadius, density, lengthOfOrbit, lengthOfDay, gravity, surfPressure, water, clouds, ice, albedo, surfTemp, tilt)
  }
}