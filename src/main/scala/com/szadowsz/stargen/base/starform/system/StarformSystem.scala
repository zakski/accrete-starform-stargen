package com.szadowsz.stargen.base.starform.system

import com.szadowsz.stargen.base.accrete.util.stats.AccreteStats
import com.szadowsz.stargen.base.starform.system.bodies.{Planet, Star}

/**
  * 03/10/2016.
  */
case class StarformSystem[S <: Star, P <: Planet](
                                            override val seed: Long,
                                            override val stats: AccreteStats,
                                            override val star : S,
                                            override val planets: List[P]
                                          ) extends AbstractStarSystem[S,AccreteStats, P]
