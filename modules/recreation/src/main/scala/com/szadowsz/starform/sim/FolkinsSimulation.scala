package com.szadowsz.starform.sim

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.model.star.constants.FolkinsBaseStarConst
import com.szadowsz.starform.model.{StarformProfile, StarformSimulation}
import com.szadowsz.starform.system.StarformSystem
import com.szadowsz.starform.system.bodies.dole.FolkinsStar
import com.szadowsz.starform.system.bodies.fogg.{FoggStar, Planet}

case class FolkinsSimulation[C <: FolkinsBaseStarConst](profile : StarformProfile[FolkinsStar,C])
  extends StarformSimulation[FolkinsStar, C,AccreteStats, StarformSystem[FolkinsStar, Planet]](profile) {

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
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[Planet]): StarformSystem[FolkinsStar, Planet] = {
    StarformSystem(seed, stats, star, planets)
  }
}