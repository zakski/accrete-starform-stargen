package com.szadowsz.starform.system

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.model.accrete.body.ProtoPlanet
import com.szadowsz.starform.system.star.Sol

class SolLikeSystem(
                     override val seed: Long,
                     override val star: Sol,
                     override val planets: List[ProtoPlanet],
                     override val stats: AccreteStats
                   )  extends AbstractStarSystem[Sol,AccreteStats,ProtoPlanet]