package com.szadowsz.starform.system

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.system.bodies.planetoid.FoggPlanet
import com.szadowsz.starform.system.bodies.star.Star

/**
  * Created on 03/10/2016.
  */
abstract class AbstractStarSystem[S <: Star,R <: SimulationStats[R], P <: FoggPlanet] extends AbstractSystem[R,P]{

  val star : S
}
