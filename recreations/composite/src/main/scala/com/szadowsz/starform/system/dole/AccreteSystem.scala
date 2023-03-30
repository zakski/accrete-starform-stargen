package com.szadowsz.starform.system.dole

import com.szadowsz.starform.sim.dole.AccreteStats
import com.szadowsz.starform.system.StarSystem
import com.szadowsz.starform.system.bodies.Planetismal
import com.szadowsz.starform.system.bodies.dole.{DolePlanet, DoleStar}

/**
  * 03/10/2016.
  */
case class AccreteSystem(
                          override val star: DoleStar,
                          override val seed: Long,
                          override val stats: AccreteStats,
                          override val planets: List[DolePlanet]
                        ) extends StarSystem[DoleStar, AccreteStats, DolePlanet]
