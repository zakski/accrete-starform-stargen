package com.szadowsz.starform.system

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.system.bodies.planetoid.FoggPlanet
import com.szadowsz.starform.system.bodies.star.Star

/**
  * 03/10/2016.
  */
case class StarformSystem[S <: Star, P <: FoggPlanet](
                                            override val seed: Long,
                                            override val stats: AccreteStats,
                                            override val star : S,
                                            override val planets: List[P]
                                          ) extends AbstractStarSystem[S,AccreteStats, P]
