package com.szadowsz.starform

import com.szadowsz.starform.model.accrete.{AccreteCalc, AccreteSimulation}
import com.szadowsz.starform.model.{SimConstants, SimulationStats}
import com.szadowsz.starform.model.eco.EcoCalc
import com.szadowsz.starform.model.star.StarCalc
import com.szadowsz.starform.rand.{MersenneTwisterRandGen, RandGenTrait}
import com.szadowsz.starform.system.StarSystem
import com.szadowsz.starform.system.bodies.{Planet, Planetismal, Star}
import com.szadowsz.starform.unit.UnitConverter

/**
  * @author Zakski : 31/12/2015.
  */
class StarformSimulation(profile: SimConstants) extends AccreteSimulation(profile) {

  protected var star: Star = _

  protected override val rand: RandGenTrait = new MersenneTwisterRandGen() // TODO double check component is right

  /**
    * calculations innately tied to the protoplanets
    */
  protected lazy val eCalc: EcoCalc = new EcoCalc

  /**
    * calculations to work out new protoplanet info after a collision.
    */
  protected lazy val sCalc: StarCalc = new StarCalc

  /**
    * the accretion code to use when hoovering up dust.
    */
  protected override lazy val accCalc: AccreteCalc = AccreteCalc(star, pCalc, aConsts)




  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[SimulationStats]] instance.
    */
  override protected def initStats(): SimulationStats = SimulationStats()


  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  final protected def generatePlanets(): List[Planet] = {
    star = sCalc.initStar(rand)
    pCalc.setStar(star)
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

  protected def buildEcosphere(proto: Planetismal): Planet  = {
    val orbitZone: Int = eCalc.orbitalZone(star.luminosity, proto.axis)

    val (eqRadius, density) = eCalc.radiusAndDensity(proto.mass, proto.axis, star.meanHabitableRadius, proto.isGasGiant, orbitZone)

    val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, proto.mass, eqRadius, proto.axis, density, proto.isGasGiant)
    val lengthOfOrbit = eCalc.orbitLength(proto.axis, proto.mass, star.mass)
    val (synch, resonant, dayLen) = eCalc.dayLength(angularVelocity, lengthOfOrbit, proto.ecc)

    val gravity = eCalc.surfaceGravity(proto.mass, eqRadius)
    val escapeVel = eCalc.escapeVelocity(UnitConverter.mToKm(gravity), eqRadius)
    val rmsSpeed = eCalc.speedRMS(eCalc.MOLECULAR_NITROGEN, eqRadius)

    val suffersFromGE = eCalc.suffersGreenhouseEffect(proto.axis, star.innerHabitableRadius)
    val retainsGas = eCalc.hasGasRetention(escapeVel, rmsSpeed)
    val volatileGasInventory = eCalc.vGasInventory(rand, proto.mass, orbitZone, retainsGas, suffersFromGE, star.mass)

    val surfPressure = eCalc.surfacePressure(volatileGasInventory, eqRadius, gravity)
    val atmos = eCalc.atmosphere(orbitZone, surfPressure, suffersFromGE, proto.isGasGiant)
    val mw = eCalc.molecule_limit(proto.mass,escapeVel,eqRadius)
    val (water, clouds, ice, albedo, surfTemp) = eCalc.calcClimate(star.meanHabitableRadius,proto.axis, eqRadius, surfPressure, volatileGasInventory, mw, atmos)

    val tilt = eCalc.inclination(rand,proto.axis)
    val (day,night,max,min) = eCalc.calcTempLimits(proto.ecc,surfPressure,surfTemp,tilt,dayLen)

    new Planet(proto, eqRadius, density, lengthOfOrbit, dayLen, gravity, surfPressure, water, clouds, ice, albedo, surfTemp,tilt,day, night, min,max)
  }

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[StarSystem]] instance.
    */
  override protected def createSystem(seed: Long, stats: SimulationStats, planets: List[Planet]): StarSystem = {
    StarSystem(seed, stats, star, planets)
  }
}
