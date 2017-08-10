package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteProfile
import com.szadowsz.starform.model.accrete.constants.AccreteConstants
import com.szadowsz.starform.model.eco.calc.EcoCalc
import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.model.star.constants.StarConstants
import com.szadowsz.starform.system.bodies.base.Star

/**
  * Created on 13/04/2017.
  */
trait StarformProfile[S <: Star, C <: StarConstants, E <: EcoCalc] extends AccreteProfile {

  val starConstants : C

  def buildEcoCalc() : E

  def buildStarCalc(sConst : C) : StarCalc[S]
}
