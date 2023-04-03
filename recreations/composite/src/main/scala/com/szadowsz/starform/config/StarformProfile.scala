package com.szadowsz.starform.config

import com.szadowsz.starform.sim.calc.eco.EcoCalc
import com.szadowsz.starform.sim.calc.star.StarCalc
import com.szadowsz.starform.sim.constants.star.StarConstants
import com.szadowsz.starform.system.bodies.Star

/**
  * Created on 13/04/2017.
  */
trait StarformProfile[S <: Star, C <: StarConstants, E <: EcoCalc] extends SimulationProfile {

  val starConstants : C

  def buildEcoCalc() : E

  def buildStarCalc(sConst : C) : StarCalc[S]
}
