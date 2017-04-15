package com.szadowsz.starform.system.bodies.dole

import com.szadowsz.starform.system.bodies.base.Star

/**
  * Created on 15/04/2017.
  */
case class FolkinsStar(
                        spectralClass: Char,
                        spectralSubclass: Int,
                        luminosityClass: String,
                        magnitude: Double,
                        override val mass: Double,
                        override val luminosity: Double,
                        override val lifespan: Double,
                        override val age: Double,
                        override val innerHabitableRadius: Double,
                        override val meanHabitableRadius: Double
                      ) extends Star
