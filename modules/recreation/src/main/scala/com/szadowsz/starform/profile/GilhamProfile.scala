package com.szadowsz.starform.profile

import com.szadowsz.starform.accrete.constants.{AccreteConstants, FKeris2Constants}
import com.szadowsz.starform.rand.{GilhamRandGen, JDKRandGen, RandGenTrait}

/**
  * Created on 11/04/2017.
  */
class GilhamProfile  extends AlgoProfile{

  override val rand: RandGenTrait = new GilhamRandGen()

  override val accConsts: AccreteConstants = new FKeris2Constants() // TODO change to Gilham
}

