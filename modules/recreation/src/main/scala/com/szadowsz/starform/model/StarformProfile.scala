package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteProfile
import com.szadowsz.starform.model.accrete.calc.{AccreteCalc, StarformAccrCalc}
import com.szadowsz.starform.model.accrete.calc.planet.{PlanetesimalCalc, StarformPlanCalc}
import com.szadowsz.starform.model.accrete.constants.AccreteConstants
import com.szadowsz.starform.model.eco.calc.EcoCalc
import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.system.bodies.fogg.Star

/**
  * Created on 13/04/2017.
  */
trait StarformProfile extends AccreteProfile {

  protected var star : Star

  def buildEcoCalc() : EcoCalc

  def buildStarCalc() : StarCalc

  override def buildPlanCalc(aConst: AccreteConstants): StarformPlanCalc

  final override def buildAccCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants): StarformAccrCalc = {
    buildStarAccCalc(pCalc.asInstanceOf[StarformPlanCalc],aConst)
  }

  def buildStarAccCalc(pCalc: StarformPlanCalc,aConst: AccreteConstants): StarformAccrCalc
}
