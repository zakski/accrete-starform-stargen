package com.szadowsz.stargen.base.accrete.system

import com.szadowsz.stargen.base.accrete.system.bodies.Planetismal
import com.szadowsz.stargen.base.accrete.util.stats.SimulationStats

/**
  * Created on 03/10/2016.
  */
abstract class AbstractSystem[S <: SimulationStats[S], P <: Planetismal]{
  val seed : Long
  val stats : S
  val planets : List[P]
}
