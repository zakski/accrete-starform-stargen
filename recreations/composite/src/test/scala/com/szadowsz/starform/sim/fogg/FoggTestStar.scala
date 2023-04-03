package com.szadowsz.starform.sim.fogg

import com.szadowsz.starform.sim.calc.star.StarCalc
import com.szadowsz.starform.system.bodies.Star

/**
  * 04/10/2016.
  */
case class FoggTestStar[S <: Star](calc: StarCalc[S]) extends Star{

  val mass: Double = 1.0

  val luminosity: Double = 1.0

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = 5.746

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}
