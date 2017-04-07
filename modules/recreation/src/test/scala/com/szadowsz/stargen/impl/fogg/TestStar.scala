package com.szadowsz.stargen.impl.fogg

import com.szadowsz.stargen.base.starform.calc.StarCalc
import com.szadowsz.stargen.base.starform.system.bodies.Star

/**
  * 04/10/2016.
  */
case class TestStar(calc: StarCalc[TestStar]) extends Star{

  val mass: Double = 1.0

  val luminosity: Double = 1.0

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = 5.746

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}
