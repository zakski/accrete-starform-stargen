package com.szadowsz.starform.config.folkins

import com.szadowsz.starform.config.StarformProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.dole.collision.DoleCollCalc
import com.szadowsz.starform.sim.calc.fogg.eco.FoggEcoCalc
import com.szadowsz.starform.sim.calc.folkins.{FolkinsInsertStrat, FolkinsStarCalc}
import com.szadowsz.starform.sim.calc.planetesimal.{PlanetesimalCalc, PlanetesimalInsertStrat}
import com.szadowsz.starform.sim.calc.star.StarCalc
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.dole.DoleConstants
import com.szadowsz.starform.sim.constants.folkins.FolkinsStarConstants
import com.szadowsz.starform.system.bodies.folkins.FolkinsStar

/**
  * Created on 15/04/2017.
  */
class FolkinsProfile extends StarformProfile[FolkinsStar,FolkinsStarConstants,FoggEcoCalc] {

  override val starConstants : FolkinsStarConstants = new FolkinsStarConstants

  override val rand: RandGenTrait = new JDKRandGen() // TODO double check component is right

  override val accConsts: AccreteConstants = new DoleConstants() // TODO double check they are unchanged

  override def buildEcoCalc(): FoggEcoCalc = new FoggEcoCalc() // TODO double check component is right

  override def buildStarCalc(sConst : FolkinsStarConstants): StarCalc[FolkinsStar] = FolkinsStarCalc(sConst)

  override def buildInsertStrat(aConst: AccreteConstants): PlanetesimalInsertStrat = new FolkinsInsertStrat(aConst)

   override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc) // TODO double check component is right
}
