package com.szadowsz.starform.config.burrell

import com.szadowsz.starform.config.SimulationProfile
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform.sim.calc.collision.CollisionCalc
import com.szadowsz.starform.sim.calc.dole.collision.DoleCollCalc
import com.szadowsz.starform.sim.calc.dole.planetismal.RandInsertStrat
import com.szadowsz.starform.sim.calc.planetesimal.{PlanetesimalCalc, PlanetesimalInsertStrat}
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.burrell.BurrellConstants

/**
  * Created on 11/04/2017.
  */
class BurrellProfile extends SimulationProfile {

  override val rand: RandGenTrait = new JDKRandGen()

  override val accConsts: AccreteConstants = new BurrellConstants()

  override def buildInsertStrat(aConst: AccreteConstants): PlanetesimalInsertStrat = new RandInsertStrat(aConst)


  override def buildCollCalc(pCalc: PlanetesimalCalc): CollisionCalc = DoleCollCalc(pCalc)
}

