package com.szadowsz.starform.system

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.system.bodies.base.Planetismal

/**
  * 03/10/2016.
  */
case class AccreteSystem[P <: Planetismal](
                                            override val seed: Long,
                                            override val stats: AccreteStats,
                                            override val planets: List[P]
                                          ) extends AbstractSystem[AccreteStats, P]
