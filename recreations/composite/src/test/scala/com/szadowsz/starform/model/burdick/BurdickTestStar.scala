package com.szadowsz.starform.model.burdick

import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.system.bodies.base.Star

/**
  * 04/10/2016.
  */
case class BurdickTestStar[S <: Star](calc: StarCalc[S]) extends Star{

  val mass: Double = 1.0

  val luminosity: Double = 0.99

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = 4.429

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}
