package com.szadowsz.starform.config

import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.sim.calc.accrete.AccreteCalc
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.planetesimal.{PlanetesimalCalc, PlanetesimalInsertStrat}
import com.szadowsz.starform.sim.constants.AccreteConstants

/**
  * Created on 11/04/2017.
  */
trait SimulationProfile {

  val rand: RandGenTrait

  val accConsts: AccreteConstants

  def buildInsertStrat(aConst: AccreteConstants): PlanetesimalInsertStrat

  def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc

  final def buildPlanCalc(aConst: AccreteConstants): PlanetesimalCalc = PlanetesimalCalc(aConst)

  final def buildAccCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants): AccreteCalc = AccreteCalc(pCalc,aConst)
}
