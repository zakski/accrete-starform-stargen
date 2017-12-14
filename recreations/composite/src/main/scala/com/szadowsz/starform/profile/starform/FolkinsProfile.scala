package com.szadowsz.starform.profile.starform

import com.szadowsz.starform.model.accrete.calc.collision.{CollisionCalc, DoleCollCalc}
import com.szadowsz.starform.model.accrete.calc.insert.{AccreteInsertStrat, FolkinsInsertStrat}
import com.szadowsz.starform.model.accrete.calc.planet.PlanetesimalCalc
import com.szadowsz.starform.model.accrete.constants.{AccreteConstants, DoleConstants}
import com.szadowsz.starform.model.eco.calc.{EcoCalc, FoggEcoCalc}
import com.szadowsz.starform.model.star.calc.{FolkinsStarCalc, StarCalc}
import com.szadowsz.starform.model.star.constants.FolkinsStarConstants
import com.szadowsz.starform.profile.StarformProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.system.bodies.star.FolkinsStar

/**
  * Created on 15/04/2017.
  */
class FolkinsProfile extends StarformProfile[FolkinsStar,FolkinsStarConstants,FoggEcoCalc] {

  override val starConstants : FolkinsStarConstants = new FolkinsStarConstants

  override val rand: RandGenTrait = new JDKRandGen() // TODO double check component is right

  override val accConsts: AccreteConstants = new DoleConstants() // TODO double check they are unchanged

  override def buildEcoCalc(): FoggEcoCalc = new FoggEcoCalc() // TODO double check component is right

  override def buildStarCalc(sConst : FolkinsStarConstants): StarCalc[FolkinsStar] = FolkinsStarCalc(sConst)

  override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = new FolkinsInsertStrat(aConst)

   override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc) // TODO double check component is right
}
