package com.szadowsz.starform.config.keris

import com.szadowsz.starform.config.SimulationProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.dole.collision.DoleCollCalc
import com.szadowsz.starform.sim.calc.dole.planetismal.RandInsertStrat
import com.szadowsz.starform.sim.calc.planetesimal.{PlanetesimalCalc, PlanetesimalInsertStrat}
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.keris.FKeris2Constants

/**
  * Created on 11/04/2017.
  */
class FKeris2Profile extends SimulationProfile{

  override val rand: RandGenTrait = new JDKRandGen() // TODO check if this aligns to the c/c++ variant

  override val accConsts: AccreteConstants = new FKeris2Constants()

  // TODO separate profile for earlier folkins code as it does something different
  override def buildInsertStrat(aConst : AccreteConstants): PlanetesimalInsertStrat = new RandInsertStrat(aConst)

  override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc)
}
