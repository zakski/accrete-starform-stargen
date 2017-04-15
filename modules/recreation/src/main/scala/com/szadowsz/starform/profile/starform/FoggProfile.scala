package com.szadowsz.starform.profile.starform

import com.szadowsz.starform.model.StarformProfile
import com.szadowsz.starform.model.accrete.calc.collision.{CollisionCalc, DoleCollCalc}
import com.szadowsz.starform.model.accrete.calc.insert.{AccreteInsertStrat, RandInsertStrat}
import com.szadowsz.starform.model.accrete.calc.planet.{FoggPlanCalc, PlanetesimalCalc, StarformPlanCalc}
import com.szadowsz.starform.model.accrete.calc.{FoggAccCalc, StarformAccrCalc}
import com.szadowsz.starform.model.accrete.constants.{AccreteConstants, DoleConstants}
import com.szadowsz.starform.model.eco.calc.{EcoCalc, FoggEcoCalc}
import com.szadowsz.starform.model.star.calc.{FoggStarCalc, StarCalc}
import com.szadowsz.starform.model.star.constants.FoggStarConstants
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.system.bodies.fogg.FoggStar

/**
  * Created on 13/04/2017.
  */
class FoggProfile extends StarformProfile[FoggStar,FoggStarConstants] {

  override val starConstants : FoggStarConstants = new FoggStarConstants

  override val rand: RandGenTrait = new JDKRandGen()

  override val accConsts: AccreteConstants = new DoleConstants() // TODO double check they are unchanged

  override def buildEcoCalc(): EcoCalc = new FoggEcoCalc()

  override def buildStarCalc(sConst : FoggStarConstants): StarCalc[FoggStar] = FoggStarCalc(sConst)

  override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = new RandInsertStrat(aConst)

  override def buildPlanCalc(aConst: AccreteConstants): StarformPlanCalc = FoggPlanCalc(aConst)

  override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc)

  override def buildStarAccCalc(pCalc: StarformPlanCalc, aConst: AccreteConstants): StarformAccrCalc = FoggAccCalc(pCalc,aConst)
}
