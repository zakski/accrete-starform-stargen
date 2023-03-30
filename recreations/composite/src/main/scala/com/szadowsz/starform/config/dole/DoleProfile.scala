package com.szadowsz.starform.config.dole

import com.szadowsz.starform.config.SimulationProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.dole.collision.DoleCollCalc
import com.szadowsz.starform.sim.calc.dole.planetismal.RandInsertStrat
import com.szadowsz.starform.sim.calc.planetismal.{PlanetismalCalc, PlanetismalInsertStrat}
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.dole.DoleConstants

/**
  * Created on 11/04/2017.
  */
class DoleProfile extends SimulationProfile {

  override val rand: RandGenTrait = new JDKRandGen()

  override val accConsts: AccreteConstants = new DoleConstants()

  override def buildInsertStrat(aConst: AccreteConstants): PlanetismalInsertStrat = new RandInsertStrat(aConst)

  override def buildCollCalc(pCalc: PlanetismalCalc): CollisionCalc = DoleCollCalc(pCalc)
}

