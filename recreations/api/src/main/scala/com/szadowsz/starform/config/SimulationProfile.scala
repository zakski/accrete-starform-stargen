package com.szadowsz.starform.config

import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.sim.calc.accrete.AccreteCalc
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.planetismal.{PlanetismalCalc, PlanetismalInsertStrat}
import com.szadowsz.starform.sim.constants.AccreteConstants

/**
  * Created on 11/04/2017.
  */
trait SimulationProfile {

  val rand: RandGenTrait

  val accConsts: AccreteConstants

  def buildInsertStrat(aConst: AccreteConstants): PlanetismalInsertStrat

  def buildCollCalc(pCalc: PlanetismalCalc): CollisionCalc

  final def buildPlanCalc(aConst: AccreteConstants): PlanetismalCalc = PlanetismalCalc(aConst)

  final def buildAccCalc(pCalc: PlanetismalCalc, aConst: AccreteConstants): AccreteCalc = AccreteCalc(pCalc,aConst)
}
