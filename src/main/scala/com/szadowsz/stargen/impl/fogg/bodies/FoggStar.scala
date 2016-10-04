package com.szadowsz.stargen.impl.fogg.bodies

import java.util.Random

import com.szadowsz.stargen.base.starform.calc.{StarCalc, StarformRandCalc}
import com.szadowsz.stargen.base.starform.system.bodies.Star

/**
  * @author Zakski : 06/07/2015.
  */
class FoggStar(calc: StarCalc[FoggStar] with StarformRandCalc[FoggStar], rand: Random) extends Star{

  val mass: Double = calc.stellarMass(rand)

  val luminosity: Double = calc.stellarLuminosity(mass)

  val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)

  val age: Double = calc.stellarAge(rand, lifespan)

  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)

  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)


}