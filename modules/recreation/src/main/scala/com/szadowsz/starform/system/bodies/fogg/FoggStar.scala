package com.szadowsz.starform.system.bodies.fogg

import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.rand.RandGenTrait

/**
  * @author Zakski : 06/07/2015.
  */
class FoggStar(calc: StarCalc, rand: RandGenTrait) extends Star{

  val mass: Double = calc.stellarMass(rand)

  val luminosity: Double = calc.stellarLuminosity(mass)

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = calc.stellarAge(rand, lifespan)

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)
}