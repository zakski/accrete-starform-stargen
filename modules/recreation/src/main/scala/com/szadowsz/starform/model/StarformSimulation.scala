package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteSimulation
import com.szadowsz.starform.model.accrete.calc.StarformAccrCalc
import com.szadowsz.starform.model.accrete.calc.planet.StarformPlanCalc
import com.szadowsz.starform.model.eco.calc.EcoCalc
import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.model.star.constants.StarConstants
import com.szadowsz.starform.system.AbstractStarSystem
import com.szadowsz.starform.system.bodies.base.Planetismal
import com.szadowsz.starform.system.bodies.planetoid.FoggPlanet
import com.szadowsz.starform.system.bodies.star.Star
import com.szadowsz.starform.unit.UnitConverter

/**
  * @author Zakski : 31/12/2015.
  */
abstract class StarformSimulation
[S <: Star, P <: FoggPlanet, C <: StarConstants, H <: SimulationStats[H], R <: AbstractStarSystem[S, H, P]](profile : StarformProfile[S,C])
  extends AccreteSimulation[H, P, R](profile) {

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
  final protected def generatePlanets(): List[P] = {
    star = sCalc.initStar(rand)
    pCalc.setStar(star)
    accCalc.setStar(star)
    accrete()
    planetismals.map(proto => buildEcosphere(proto))
  }

  protected def buildEcosphere(proto: Planetismal): P
}
