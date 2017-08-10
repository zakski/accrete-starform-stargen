package com.szadowsz.starform.model.keris

import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.system.bodies.star.FoggStar

/**
  * 04/10/2016.
  */
object KerisTestStar {

  /**
    * Creates a pre-defined star based on the example specified by Keris in his Readme.
    *
    * @param calc Fogg's star calculations.
    * @return Fogg style star.
    */
  def apply(calc: StarCalc[FoggStar]): FoggStar = {
    val mass: Double = 1.04
    val luminosity: Double = 1.22
    val lifespan: Double = calc.stellarMSLifespan(mass, luminosity)
    val age: Double = 4.570
    val meanHabitableRadius: Double = calc.ecosphereRadius(luminosity)
    val innerHabitableRadius: Double = calc.greenhouseRadius(meanHabitableRadius)

    new FoggStar(mass,luminosity,lifespan,age,innerHabitableRadius,meanHabitableRadius)
  }
}