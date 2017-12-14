package com.szadowsz.starform2.model

import com.szadowsz.starform2.model.accrete.AccreteProfile
import com.szadowsz.starform2.model.eco.calc.EcoCalc
import com.szadowsz.starform2.model.star.calc.StarCalc
import com.szadowsz.starform2.model.star.consts.StarConstants
import com.szadowsz.starform2.system.body.Star

/**
  * Created on 13/04/2017.
  */
abstract class StarformProfile[S <: Star, C <: StarConstants, E <: EcoCalc](
                                                                             a: Option[Double] = None,
                                                                             k: Option[Double] = None,
                                                                             w: Option[Double] = None
                                                                           ) extends AccreteProfile(a,k,w) {

  val starConstants : C

  def buildEcoCalc() : E

  def buildStarCalc(sConst : C) : StarCalc[S,C]
}
