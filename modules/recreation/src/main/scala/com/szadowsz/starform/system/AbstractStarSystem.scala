package com.szadowsz.starform.system

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.system.bodies.fogg.{Planet, Star}

/**
  * Created on 03/10/2016.
  */
abstract class AbstractStarSystem[S <: Star,R <: SimulationStats[R], P <: Planet] extends AbstractSystem[R,P]{

  val star : S
}
