package com.szadowsz.starform.model.accrete

import com.szadowsz.starform.model.accrete.calc.AccreteCalc
import com.szadowsz.starform.model.accrete.calc.collision.CollisionCalc
import com.szadowsz.starform.model.accrete.calc.insert.AccreteInsertStrat
import com.szadowsz.starform.model.accrete.calc.planet.PlanetesimalCalc
import com.szadowsz.starform.model.accrete.constants.AccreteConstants
import com.szadowsz.starform.rand.RandGenTrait

/**
  * Created on 11/04/2017.
  */
trait AccreteProfile {

  val rand: RandGenTrait

  val accConsts: AccreteConstants

  def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat

  def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc

  final def buildPlanCalc(aConst: AccreteConstants): PlanetesimalCalc = PlanetesimalCalc(aConst)

  final def buildAccCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants): AccreteCalc = AccreteCalc(pCalc,aConst)
}
