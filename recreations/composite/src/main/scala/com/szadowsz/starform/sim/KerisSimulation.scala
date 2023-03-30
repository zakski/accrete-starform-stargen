//package com.szadowsz.starform.sim
//
//import com.szadowsz.starform.model.eco.calc.{FoggEcoCalc, KerisEcoCalc}
//import com.szadowsz.starform.model.star.constants.FoggBaseStarConst
//import com.szadowsz.starform.model.{StarformProfile, StarformSimulation}
//import com.szadowsz.starform.sim.dole.AccreteStats
//import com.szadowsz.starform.system.StarformSystem
//import com.szadowsz.starform.system.bodies.Planetismal
//import com.szadowsz.starform.system.bodies.fogg.{FoggPlanet, FoggStar}
//import com.szadowsz.starform.system.bodies.keris.KerisPlanet
//import com.szadowsz.starform.unit.UnitConverter
//
//case class KerisSimulation[C <: FoggBaseStarConst](profile : StarformProfile[FoggStar,C, KerisEcoCalc])
//  extends StarformSimulation[FoggStar, FoggPlanet, C,AccreteStats, StarformSystem[FoggStar, FoggPlanet],KerisEcoCalc](profile) {
//
//  /**
//    * Function to initialise a new instance at the beginning of each run.
//    *
//    * @return a new [[AccreteStats]] instance.
//    */
//  override protected def initStats(): AccreteStats = AccreteStats()
//
//  /**
//    * Function to initialise a new solar system instance at the end of each run.
//    *
//    * @return a new [[StarformSystem]] instance.
//    */
//  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[FoggPlanet]): StarformSystem[FoggStar, FoggPlanet] = {
//    StarformSystem(seed, stats, star, planets)
//  }
//
//  override protected def buildEcosphere(proto: Planetismal): FoggPlanet  = {
//    val orbitZone: Int = eCalc.orbitalZone(star.luminosity, proto.axis)
//
//    val (eqRadius, density) = eCalc.radiusAndDensity(proto.mass, proto.axis, star.meanHabitableRadius, proto.isGasGiant, orbitZone)
//
//    val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, proto.mass, eqRadius, proto.axis, density, proto.isGasGiant)
//    val lengthOfOrbit = eCalc.orbitLength(proto.axis, proto.mass, star.mass)
//    val (synch, resonant, dayLen) = eCalc.dayLength(angularVelocity, lengthOfOrbit, proto.ecc)
//
//    val gravity = eCalc.surfaceGravity(proto.mass, eqRadius)
//    val escapeVel = eCalc.escapeVelocity(UnitConverter.mToKm(gravity), eqRadius)
//    val rmsSpeed = eCalc.speedRMS(eCalc.MOLECULAR_NITROGEN, eqRadius)
//
//    val suffersFromGE = eCalc.suffersGreenhouseEffect(proto.axis, star.innerHabitableRadius)
//    val retainsGas = eCalc.hasGasRetention(escapeVel, rmsSpeed)
//    val volatileGasInventory = eCalc.vGasInventory(rand, proto.mass, orbitZone, retainsGas, suffersFromGE, star.mass)
//
//    val surfPressure = eCalc.surfacePressure(volatileGasInventory, eqRadius, gravity)
//    val atmos = eCalc.atmosphere(orbitZone, surfPressure, suffersFromGE, proto.isGasGiant)
//    val mw = eCalc.molecule_limit(proto.mass,escapeVel,eqRadius)
//    val (water, clouds, ice, albedo, surfTemp) = eCalc.calcClimate(star.meanHabitableRadius,proto.axis, eqRadius, surfPressure, volatileGasInventory, mw, atmos)
//
//    val tilt = eCalc.inclination(rand,proto.axis)
//    val (day,night,max,min) = eCalc.calcTempLimits(proto.ecc,surfPressure,surfTemp,tilt,dayLen)
//
//    new KerisPlanet(proto, eqRadius, density, lengthOfOrbit, dayLen, gravity, surfPressure, water, clouds, ice, albedo, surfTemp, tilt, day, night, min,max)
//  }
//}