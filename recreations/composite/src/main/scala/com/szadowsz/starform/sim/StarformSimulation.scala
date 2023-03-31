package com.szadowsz.starform.sim

import com.szadowsz.starform.config.StarformProfile
import com.szadowsz.starform.sim.calc.accrete.AccreteCalc
import com.szadowsz.starform.sim.calc.eco.EcoCalc
import com.szadowsz.starform.sim.calc.planetismal.PlanetismalCalc
import com.szadowsz.starform.sim.calc.star.StarCalc
import com.szadowsz.starform.sim.constants.star.StarConstants
import com.szadowsz.starform.system.StarSystem
import com.szadowsz.starform.system.bodies.fogg.FoggPlanet
import com.szadowsz.starform.system.bodies.{Planetismal, Star}
import com.szadowsz.starform.util.UnitConverter

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation[S <: Star, P <: FoggPlanet, C <: StarConstants, H <: SimulationStats[H], R <: StarSystem[S, H, P], E <: EcoCalc]
(profile: StarformProfile[S, C, E]) extends AccreteSimulation[S,H, P, R](profile) {

  protected val sConst: C = profile.starConstants

  /**
    * calculations innately tied to the protoplanets
    */
  protected lazy val eCalc: E = profile.buildEcoCalc()

  /**
    * calculations to work out new protoplanet info after a collision.
    */
  protected lazy val sCalc: StarCalc[S] = profile.buildStarCalc(sConst)

  /**
    * calculations innately tied to the protoplanets
    */
  protected override lazy val pCalc: PlanetismalCalc = profile.buildPlanCalc(this)

  /**
    * the accretion code to use when hoovering up dust.
    */
  protected override lazy val accCalc: AccreteCalc = profile.buildAccCalc(pCalc, this)


  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  final protected def generatePlanets(): List[P] = {
    star = sCalc.initStar(rand)
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

  protected def buildEcosphere(proto: Planetismal): P
}
