package com.szadowsz.starform2.model.fogg

import com.szadowsz.starform2.model.star.calc.StarCalc
import com.szadowsz.starform2.model.star.consts.StarConstants
import com.szadowsz.starform2.system.body.Star

/**
  * 04/10/2016.
  */
case class FoggTestStar[S <: Star, C <: StarConstants](calc: StarCalc[S,C]) extends Star{

  val mass: Double = 1.0

  val luminosity: Double = 1.0

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = 5.746

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}
