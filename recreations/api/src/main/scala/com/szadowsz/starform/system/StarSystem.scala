package com.szadowsz.starform.system

import com.szadowsz.starform.sim.SimulationStats
import com.szadowsz.starform.system.bodies.{Planetismal, Star}

/**
  * Created on 03/10/2016.
  */
trait StarSystem[S <: Star,R <: SimulationStats[R], P <: Planetismal] {

  val star : S

  val seed : Long

  val stats : R

  val planets : List[P]
}
