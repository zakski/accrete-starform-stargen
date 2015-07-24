package com.szadowsz.accrete.fogg.bodies

import com.szadowsz.accrete.fogg.calc.FoggAccrCalc

import scala.util.Random

/**
 * @author Zakski : 06/07/2015.
 */
class Star(calc: FoggAccrCalc, rand: Random) {

  val mass: Double = calc.stellarMass(rand)

  val luminosity: Double = calc.stellarLuminosity(mass)
  val age: Double = calc.stellarAge(rand, _lifespan)
  val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)
  val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)
  private val _lifespan: Double = calc.stellarMSLifespan(mass, luminosity)
}
