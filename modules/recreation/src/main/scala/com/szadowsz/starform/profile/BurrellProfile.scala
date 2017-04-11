package com.szadowsz.starform.profile

import com.szadowsz.starform.accrete.constants.{AccreteConstants, BurrellConstants}
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}

/**
  * Created on 11/04/2017.
  */
class BurrellProfile extends AlgoProfile{

  override val rand: RandGenTrait = new JDKRandGen()

  override val accConsts: AccreteConstants = new BurrellConstants()
}

