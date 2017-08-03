package com.szadowsz.starform.model.keris

import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.system.bodies.star.Star

/**
  * 04/10/2016.
  */
case class KerisTestStar[S <: Star](calc: StarCalc[S]) extends Star{

  val mass: Double = 1.04

  val luminosity: Double = 1.22

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = 4.570

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}
