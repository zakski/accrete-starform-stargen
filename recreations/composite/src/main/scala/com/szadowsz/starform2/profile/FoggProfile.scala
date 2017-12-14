package com.szadowsz.starform2.profile

import com.szadowsz.starform2.model.StarformProfile
import com.szadowsz.starform2.model.accrete.calc.AccreteInsertStrat
import com.szadowsz.starform2.model.accrete.calc.insert.RandInsertStrat
import com.szadowsz.starform2.model.accrete.consts.{AccreteConstants, DoleConstants}
import com.szadowsz.starform2.model.eco.calc.FoggEcoCalc
import com.szadowsz.starform2.model.star.calc.{BurdickStarCalc, StarCalc}
import com.szadowsz.starform2.model.star.consts.FoggStarConstants
import com.szadowsz.starform2.rand.gen.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform2.system.body.star.FoggStar

/**
  * Created on 13/04/2017.
  */
class FoggProfile extends StarformProfile[FoggStar,FoggStarConstants,FoggEcoCalc] {

  override val starConstants : FoggStarConstants = new FoggStarConstants

  override protected val accConsts: AccreteConstants = new DoleConstants

  override def buildEcoCalc(): FoggEcoCalc = new FoggEcoCalc

  override def buildStarCalc(sConst: FoggStarConstants): StarCalc[FoggStar, FoggStarConstants] = new  BurdickStarCalc(sConst)

  override def buildRand(): RandGenTrait = new JDKRandGen()

  /**
    * Generates a new insertion strategy, using the Accrete Constants to specify the closest and furthest from the central star a planetismal can form.
    *
    * @param aConst the Accrete Simulation Constants
    * @return the initialised insertion strategy.
    */
  override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = new RandInsertStrat(aConst)
}
