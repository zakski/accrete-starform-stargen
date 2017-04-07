package com.szadowsz.stargen.impl.fogg

import com.szadowsz.stargen.base.starform.system.bodies.Star
import com.szadowsz.stargen.impl.fogg.calc.FoggCalc

/**
  * Star Values are populated by Fogg's sample run to make sure everything matches up.
  *
  * Created on 21/09/2016.
  */
object FoggTestCalc extends FoggCalc[TestStar] {

  var star : TestStar = TestStar(this)

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarLuminosity: Double = star.luminosity

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarMass: Double = star.mass

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarAge: Double = star.age

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarEcosphereRadius: Double = star.meanHabitableRadius

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarGreenhouseRadius: Double = greenhouseRadius(getStarEcosphereRadius)

}
