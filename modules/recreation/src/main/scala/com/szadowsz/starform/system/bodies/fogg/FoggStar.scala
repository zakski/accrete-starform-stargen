package com.szadowsz.starform.system.bodies.fogg

import com.szadowsz.starform.model.star.calc.StarCalc
import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.system.bodies.base.Star

/**
  * @author Zakski : 06/07/2015.
  */
case class FoggStar(
                     override val mass: Double,
                     override val luminosity: Double,
                     override val lifespan: Double,
                     override val age: Double,
                     override val innerHabitableRadius: Double,
                     override val meanHabitableRadius: Double
                   ) extends Star