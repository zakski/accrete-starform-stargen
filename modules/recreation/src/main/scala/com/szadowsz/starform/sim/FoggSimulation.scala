package com.szadowsz.starform.sim

import com.szadowsz.starform.model.{StarformProfile, StarformSimulation}
import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.model.star.constants.FoggBaseStarConst
import com.szadowsz.starform.system.StarformSystem
import com.szadowsz.starform.system.bodies.fogg.{FoggStar, Planet}

case class FoggSimulation[C <: FoggBaseStarConst](profile : StarformProfile[FoggStar,C])
  extends StarformSimulation[FoggStar, C,AccreteStats, StarformSystem[FoggStar, Planet]](profile) {

  override var star: FoggStar = _

  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[AccreteStats]] instance.
    */
  override protected def initStats(): AccreteStats = AccreteStats()

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[StarformSystem]] instance.
    */
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[Planet]): StarformSystem[FoggStar, Planet] = {
    StarformSystem(seed, stats, star, planets)
  }
}