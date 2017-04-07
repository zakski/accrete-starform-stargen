package com.szadowsz.stargen.base.accrete.system

import com.szadowsz.stargen.base.accrete.system.bodies.{Planetismal, ProtoPlanet}
import com.szadowsz.stargen.base.accrete.util.stats.AccreteStats

/**
  * 03/10/2016.
  */
case class AccreteSystem[P <: Planetismal](
                                            override val seed: Long,
                                            override val stats: AccreteStats,
                                            override val planets: List[P]
                                          ) extends AbstractSystem[AccreteStats, P]
