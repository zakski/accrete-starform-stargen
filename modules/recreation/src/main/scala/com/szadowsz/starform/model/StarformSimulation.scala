package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteSimulation
import com.szadowsz.starform.model.accrete.calc.StarformAccrCalc
import com.szadowsz.starform.model.accrete.calc.planet.StarformPlanCalc
import com.szadowsz.starform.model.eco.calc.EcoCalc
import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.model.star.constants.StarConstants
import com.szadowsz.starform.system.AbstractStarSystem
import com.szadowsz.starform.system.bodies.base.{Planetismal, Star}
import com.szadowsz.starform.system.bodies.fogg.Planet
import com.szadowsz.starform.unit.UnitConverter

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation
[S <: Star, C <: StarConstants, H <: SimulationStats[H], R <: AbstractStarSystem[S, H, Planet]](profile : StarformProfile[S,C])
  extends AccreteSimulation[H, Planet, R](profile) {

  protected var star : S = _

  protected val sConst : C = profile.starConstants

  /**
    * calculations innately tied to the protoplanets
    */
  protected lazy val eCalc: EcoCalc = profile.buildEcoCalc()

  /**
    * calculations to work out new protoplanet info after a collision.
    */
  protected lazy val sCalc : StarCalc[S] = profile.buildStarCalc(sConst)

  /**
    * calculations innately tied to the protoplanets
    */
  protected override lazy val pCalc: StarformPlanCalc = profile.buildPlanCalc(this)

  /**
    * the accretion code to use when hoovering up dust.
    */
  protected override lazy val accCalc: StarformAccrCalc = profile.buildAccCalc(pCalc,this)


  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  final protected def generatePlanets(): List[Planet] = {
    star = sCalc.initStar(rand)
    pCalc.setStar(star)
    accCalc.setStar(star)
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

  protected def buildEcosphere(proto: Planetismal): Planet = {
      val orbitZone: Int = eCalc.orbitalZone(star.luminosity, proto.axis)

      val (equatorialRadius, density) = eCalc.radiusAndDensity(proto.mass, proto.axis, star.meanHabitableRadius, proto.isGasGiant, orbitZone)

      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, proto.mass, equatorialRadius, proto.axis, density, proto.isGasGiant)
      val lengthOfOrbit = eCalc.orbitLength(proto.axis, proto.mass, star.mass)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, lengthOfOrbit, proto.ecc)

      val gravity = eCalc.surfaceGravity(proto.mass, equatorialRadius)
      val escapeVel = eCalc.escapeVelocity(UnitConverter.mToKm(gravity), equatorialRadius)
      val rmsSpeed = eCalc.speedRMS(eCalc.MOLECULAR_NITROGEN, equatorialRadius)

      val suffersFromGE = eCalc.suffersGreenhouseEffect(proto.axis, star.innerHabitableRadius)
      val retainsGas = eCalc.hasGasRetention(escapeVel, rmsSpeed)
      val volatileGasInventory = eCalc.vGasInventory(rand, proto.mass, orbitZone, retainsGas, suffersFromGE, star.mass)

      val surfPressure = eCalc.surfacePressure(volatileGasInventory, equatorialRadius, gravity)
      val atmos = eCalc.atmosphere(orbitZone, surfPressure, suffersFromGE, proto.isGasGiant)
      val mw = eCalc.molecule_limit(proto.mass,escapeVel,equatorialRadius)
      val (water, clouds, ice, albedo, surfTemp) = eCalc.calcClimate(star.meanHabitableRadius,proto.axis, equatorialRadius, surfPressure, volatileGasInventory, mw, atmos)


      new Planet(proto, equatorialRadius, density, lengthOfOrbit, lengthOfDay, gravity, surfPressure, water, clouds, ice, albedo, surfTemp)
    }
}
