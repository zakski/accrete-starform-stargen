// scalastyle:off method.name
package com.szadowsz.stargen.impl.dole

import java.util.Random

import com.szadowsz.stargen.base.accrete.system.bodies.ProtoPlanet
import com.szadowsz.stargen.base.accrete.calc.insert.InsertionStrat
import com.szadowsz.stargen.base.accrete.AccreteSimulation
import com.szadowsz.stargen.base.accrete.util.stats.AccreteStats
import com.szadowsz.stargen.base.accrete.system.{AccreteSystem, AbstractSystem}
import com.szadowsz.stargen.impl.dole.bodies.DolePlanet
import com.szadowsz.stargen.impl.dole.calc.DoleCalc

case class DoleSimulation(
                           override protected val rand: Random,
                           override protected val iStrat: InsertionStrat,
                           a: Option[Double] = None,
                           k: Option[Double] = None,
                           w: Option[Double] = None
                         ) extends AccreteSimulation[AccreteStats,DolePlanet,AccreteSystem[DolePlanet]] with DoleCalc {


  override val DUST_DENSITY_COEFF: Double = a.getOrElse(super.DUST_DENSITY_COEFF)

  override val K: Double = k.getOrElse(super.K)

  override val CLOUD_ECCENTRICITY: Double = w.getOrElse(super.CLOUD_ECCENTRICITY)

  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[AccreteStats]] instance.
    */
  override protected def initStats(): AccreteStats = AccreteStats()

  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[DolePlanet]] instances.
    */
  override protected def generatePlanets(): List[DolePlanet] = {
    accrete()
    planetismals.map(new DolePlanet(_))
  }

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[AccreteSystem]] instance.
    */
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[DolePlanet]): AccreteSystem[DolePlanet] = {
    AccreteSystem(seed, stats, planets)
  }
}