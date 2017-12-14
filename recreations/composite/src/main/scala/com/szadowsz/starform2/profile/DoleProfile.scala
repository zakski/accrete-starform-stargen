package com.szadowsz.starform2.profile

import com.szadowsz.starform2.model.accrete.AccreteProfile
import com.szadowsz.starform2.model.accrete.calc.AccreteInsertStrat
import com.szadowsz.starform2.model.accrete.calc.insert.RandInsertStrat
import com.szadowsz.starform2.model.accrete.consts.{AccreteConstants, DoleConstants}
import com.szadowsz.starform2.rand.gen.{JDKRandGen, RandGenTrait}

/**
  * Created on 11/04/2017.
  */
class DoleProfile extends AccreteProfile {

  override protected val accConsts: AccreteConstants = new DoleConstants

  override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = new RandInsertStrat(aConst)

  override def buildRand(): RandGenTrait = new JDKRandGen() //TODO work out if we can recrete the generator he originally used
}

