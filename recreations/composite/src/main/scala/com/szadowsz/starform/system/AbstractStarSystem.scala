package com.szadowsz.starform.system

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.system.bodies.base.{Planetismal, Star}
import com.szadowsz.starform.system.bodies.planetoid.FoggPlanet

/**
  * Created on 03/10/2016.
  */
abstract class AbstractStarSystem[S <: Star,R <: SimulationStats[R], P <: Planetismal] {

  val star : S

  val seed : Long

  val stats : R

  val planets : List[P]
}
