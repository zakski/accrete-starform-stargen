package com.szadowsz.stargen.base.starform

import com.szadowsz.stargen.base.accrete.calc.CollisionCalc
import com.szadowsz.stargen.base.starform.calc._
import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.constants.unit.UnitConstants
import com.szadowsz.stargen.base.starform.util.StarUtil

/**
  * Star Values are populated by Fogg's sample run to make sure everything matches up.
  *
  * Created on 21/09/2016.
  */
object FoggTestCalc
  extends StarformAccrCalc
    with StarformPlanCalc
    with StarformRandCalc
    with StarCalc
    with EcoCalc
    with CollisionCalc
    with StarformConstants
    with StarUtil
    with UnitConstants {

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarLuminosity: Double = 1

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarMass: Double = 1

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarAge: Double = 5.746

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarEcosphereRadius: Double = 1

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarGreenhouseRadius: Double = greenhouseRadius(getStarEcosphereRadius)
}
