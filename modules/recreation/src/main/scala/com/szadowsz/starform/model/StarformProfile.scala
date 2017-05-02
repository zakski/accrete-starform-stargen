package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteProfile
import com.szadowsz.starform.model.accrete.calc.{AccreteCalc, StarformAccrCalc}
import com.szadowsz.starform.model.accrete.calc.planet.{PlanetesimalCalc, StarformPlanCalc}
import com.szadowsz.starform.model.accrete.constants.AccreteConstants
import com.szadowsz.starform.model.eco.calc.EcoCalc
import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.model.star.constants.StarConstants
import com.szadowsz.starform.system.bodies.star.Star

/**
  * Created on 13/04/2017.
  */
trait StarformProfile[S <: Star, C <: StarConstants] extends AccreteProfile {

  val starConstants : C

  def buildEcoCalc() : EcoCalc

  def buildStarCalc(sConst : C) : StarCalc[S]

  override def buildPlanCalc(aConst: AccreteConstants): StarformPlanCalc

  final override def buildAccCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants): StarformAccrCalc = {
    buildStarAccCalc(pCalc.asInstanceOf[StarformPlanCalc],aConst)
  }

  def buildStarAccCalc(pCalc: StarformPlanCalc,aConst: AccreteConstants): StarformAccrCalc
}
