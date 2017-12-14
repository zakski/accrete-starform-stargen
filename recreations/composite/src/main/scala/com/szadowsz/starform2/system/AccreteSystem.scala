package com.szadowsz.starform2.system

import com.szadowsz.starform2.model.accrete.AccreteStats
import com.szadowsz.starform2.system.body.planet.DolePlanet
import com.szadowsz.starform2.system.body.star.DoleStar

/**
  * 03/10/2016.
  */
case class AccreteSystem(
                          override val star: DoleStar,
                          override val seed: Long,
                          override val stats: AccreteStats,
                          override val planets: List[DolePlanet]
                        ) extends AbstractStarSystem[DoleStar, AccreteStats, DolePlanet]
