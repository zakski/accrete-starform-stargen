package com.szadowsz.starform2.model.star.calc

import com.szadowsz.starform2.system.body.star.FoggStar
import com.szadowsz.starform2.rand.gen.RandGenTrait
import com.szadowsz.starform2.model.star.consts.FoggStarConstants



/**
  * Created on 16/08/2017.
  */
class BurdickStarCalc (c : FoggStarConstants) extends FoggStarCalc[FoggStar,FoggStarConstants](c) {

  override def buildStar(rand: RandGenTrait): FoggStar = {
    val mass: Double = stellarMass(rand)
    val luminosity: Double = stellarLuminosity(mass)
    val lifespan: Double = stellarMSLifespan(mass, luminosity)
    val age: Double = stellarAge(rand, lifespan)
    val meanHabitableRadius: Double = ecosphereRadius(luminosity)
    val innerHabitableRadius: Double = greenhouseRadius(meanHabitableRadius)
    new FoggStar(mass, luminosity, lifespan, age, innerHabitableRadius, meanHabitableRadius)
  }
}
