package com.szadowsz.starform.system.bodies.star

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