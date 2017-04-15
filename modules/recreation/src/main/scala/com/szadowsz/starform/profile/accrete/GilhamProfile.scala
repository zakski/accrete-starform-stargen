package com.szadowsz.starform.profile.accrete

import com.szadowsz.starform.model.accrete.AccreteProfile
import com.szadowsz.starform.model.accrete.calc.collision.{CollisionCalc, DoleCollCalc}
import com.szadowsz.starform.model.accrete.calc.insert.{AccreteInsertStrat, RandInsertStrat}
import com.szadowsz.starform.model.accrete.calc.planet.{DolePlanCalc, PlanetesimalCalc}
import com.szadowsz.starform.model.accrete.calc.{AccreteCalc, DoleAccCalc}
import com.szadowsz.starform.model.accrete.constants.{AccreteConstants, FKeris2Constants}
import com.szadowsz.starform.rand.{GilhamRandGen, RandGenTrait}

/**
  * Created on 11/04/2017.
  */
class GilhamProfile extends AccreteProfile{

  override val rand: RandGenTrait = new GilhamRandGen()

  override val accConsts: AccreteConstants = new FKeris2Constants() // TODO change to Gilham

  override def buildInsertStrat(aConst : AccreteConstants): AccreteInsertStrat = new RandInsertStrat(aConst)

  override def buildPlanCalc(aConst : AccreteConstants): PlanetesimalCalc = DolePlanCalc(aConst) // TODO check if it should use Gilham calc

  override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc) // TODO check if it should use Gilham calc

  // TODO check if it should use Gilham calc
  override def buildAccCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants): AccreteCalc = DoleAccCalc(pCalc,aConst)
}

