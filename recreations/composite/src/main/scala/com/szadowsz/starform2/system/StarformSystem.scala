package com.szadowsz.starform2.system

import com.szadowsz.starform2.model.SimulationStats
import com.szadowsz.starform2.system.body.planet.FoggPlanet
import com.szadowsz.starform2.system.body.star.FoggStar

/**
  * 03/10/2016.
  */
case class StarformSystem[S <: FoggStar, R <: SimulationStats, P <: FoggPlanet](
                                                                                 override val seed: Long,
                                                                                 override val stats: R,
                                                                                 override val star: S,
                                                                                 override val planets: List[P]
                                                                               ) extends AbstractStarSystem[S, R, P]
