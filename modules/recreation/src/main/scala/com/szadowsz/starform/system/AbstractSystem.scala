package com.szadowsz.starform.system

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.system.bodies.base.Planetismal

/**
  * Created on 03/10/2016.
  */
abstract class AbstractSystem[S <: SimulationStats[S], P <: Planetismal]{
  val seed : Long
  val stats : S
  val planets : List[P]
}
