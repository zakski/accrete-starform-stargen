package com.szadowsz.starform.system

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.system.bodies.base.Planetismal
import com.szadowsz.starform.system.bodies.planetoid.DolePlanet
import com.szadowsz.starform.system.bodies.star.DoleStar

/**
  * 03/10/2016.
  */
case class AccreteSystem(
                          override val star: DoleStar,
                          override val seed: Long,
                          override val stats: AccreteStats,
                          override val planets: List[DolePlanet]
                        ) extends AbstractStarSystem[DoleStar, AccreteStats, DolePlanet]
