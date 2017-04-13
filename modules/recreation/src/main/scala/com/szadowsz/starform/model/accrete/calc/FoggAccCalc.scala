package com.szadowsz.starform.model.accrete.calc

import com.szadowsz.starform.model.accrete.calc.planet.StarformPlanCalc
import com.szadowsz.starform.model.accrete.constants.AccreteConstants

/**
  * Created on 12/04/2017.
  */
case class FoggAccCalc(override val pCalc: StarformPlanCalc, override val aConst: AccreteConstants) extends StarformAccrCalc