package com.szadowsz.stargen.base.starform.system

import com.szadowsz.stargen.base.accrete.system.AbstractSystem
import com.szadowsz.stargen.base.accrete.util.stats.SimulationStats
import com.szadowsz.stargen.base.starform.system.bodies.{Planet, Star}

/**
  * Created on 03/10/2016.
  */
abstract class AbstractStarSystem[S <: Star,R <: SimulationStats[R], P <: Planet] extends AbstractSystem[R,P]{

  val star : S
}
