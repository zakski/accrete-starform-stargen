package com.szadowsz.starform.system

import com.szadowsz.starform.sim.dole.AccreteStats
import com.szadowsz.starform.system.bodies.fogg.{FoggPlanet, FoggStar}

/**
  * 03/10/2016.
  */
case class StarformSystem[S <: FoggStar, P <: FoggPlanet](
                                            override val seed: Long,
                                            override val stats: AccreteStats,
                                            override val star : S,
                                            override val planets: List[P]
                                          ) extends StarSystem[S,AccreteStats, P]
