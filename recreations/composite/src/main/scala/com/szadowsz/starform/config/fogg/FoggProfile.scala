package com.szadowsz.starform.config.fogg

import com.szadowsz.starform.config.StarformProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.dole.collision.DoleCollCalc
import com.szadowsz.starform.sim.calc.dole.planetismal.RandInsertStrat
import com.szadowsz.starform.sim.calc.fogg.eco.FoggEcoCalc
import com.szadowsz.starform.sim.calc.fogg.star.FoggStarCalc
import com.szadowsz.starform.sim.calc.planetesimal.{PlanetesimalCalc, PlanetesimalInsertStrat}
import com.szadowsz.starform.sim.calc.star.StarCalc
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.dole.DoleConstants
import com.szadowsz.starform.sim.constants.fogg.FoggStarConstants
import com.szadowsz.starform.system.bodies.fogg.FoggStar

/**
  * Created on 13/04/2017.
  */
class FoggProfile extends StarformProfile[FoggStar,FoggStarConstants,FoggEcoCalc] {

  override val starConstants : FoggStarConstants = new FoggStarConstants

  override val rand: RandGenTrait = new JDKRandGen()

  override val accConsts: AccreteConstants = new DoleConstants() // TODO double check they are unchanged

  override def buildEcoCalc(): FoggEcoCalc = new FoggEcoCalc()

  override def buildStarCalc(sConst : FoggStarConstants): StarCalc[FoggStar] = FoggStarCalc(sConst)

  override def buildInsertStrat(aConst: AccreteConstants): PlanetesimalInsertStrat = new RandInsertStrat(aConst)

  override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc)
}
