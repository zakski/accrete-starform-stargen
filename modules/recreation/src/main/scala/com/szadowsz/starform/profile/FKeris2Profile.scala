package com.szadowsz.starform.profile

import com.szadowsz.starform.accrete.constants.{AccreteConstants, FKeris2Constants}
import com.szadowsz.starform.rand.{JDKRandGen, RandGenTrait}

/**
  * Created on 11/04/2017.
  */
class FKeris2Profile extends AlgoProfile{

  override val rand: RandGenTrait = new JDKRandGen() // TODO check if this aligns to the c/c++ variant

  override val accConsts: AccreteConstants = new FKeris2Constants()
}
