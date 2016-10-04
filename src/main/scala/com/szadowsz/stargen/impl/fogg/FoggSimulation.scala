package com.szadowsz.stargen.impl.fogg

import java.util.Random

import com.szadowsz.stargen.base.accrete.calc.insert.InsertionStrat
import com.szadowsz.stargen.base.accrete.util.stats.AccreteStats
import com.szadowsz.stargen.base.starform.StarformSimulation
import com.szadowsz.stargen.base.starform.system.StarformSystem
import com.szadowsz.stargen.base.starform.system.bodies.Planet
import com.szadowsz.stargen.impl.fogg.bodies.FoggStar
import com.szadowsz.stargen.impl.fogg.calc.FoggCalc

case class FoggSimulation(override protected val rand: Random, override protected val iStrat: InsertionStrat)
  extends StarformSimulation[FoggStar, AccreteStats, StarformSystem[FoggStar, Planet]] with FoggCalc[FoggStar] {

  override var star: FoggStar = _

  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[AccreteStats]] instance.
    */
  override protected def initStats(): AccreteStats = AccreteStats()

  override protected def initStar(): FoggStar = new FoggStar(this, rand)

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[StarformSystem]] instance.
    */
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[Planet]): StarformSystem[FoggStar, Planet] = {
    StarformSystem(seed, stats, star, planets)
  }
}