package com.szadowsz.starform.model.accrete.calc
import com.szadowsz.starform.model.accrete.calc.planet.PlanetesimalCalc
import com.szadowsz.starform.model.accrete.constants.AccreteConstants

/**
  * Created on 12/04/2017.
  */
case class DoleAccCalc(override val pCalc: PlanetesimalCalc, override val aConst: AccreteConstants) extends AccreteCalc