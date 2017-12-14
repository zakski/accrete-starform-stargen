package com.szadowsz.starform2.model

import com.szadowsz.starform2.model.accrete.AccreteSimulation
import com.szadowsz.starform2.model.eco.calc.EcoCalc
import com.szadowsz.starform2.model.star.calc.StarCalc
import com.szadowsz.starform2.model.star.consts.StarConstants
import com.szadowsz.starform2.system.AbstractStarSystem
import com.szadowsz.starform2.system.body.planet.FoggPlanet
import com.szadowsz.starform2.system.body.{Planetismal, Star}


/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation[S <: Star, P <: FoggPlanet, C <: StarConstants, H <: SimulationStats, R <: AbstractStarSystem[S, H, P], E <: EcoCalc]
(profile: StarformProfile[S, C, E]) extends AccreteSimulation[S,P, H, R](profile) {

  protected val sConst: C = profile.starConstants

  /**
    * calculations innately tied to the protoplanets
    */
  protected lazy val eCalc: E = profile.buildEcoCalc()

  /**
    * calculations to work out new protoplanet info after a collision.
    */
  protected lazy val sCalc: StarCalc[S,C] = profile.buildStarCalc(sConst)


  final override protected def generateStar(): S = {
    sCalc.buildStar(rand)
  }

    /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  final override protected def generatePlanets(): List[P] = {
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

  protected def buildEcosphere(proto: Planetismal): P
}
