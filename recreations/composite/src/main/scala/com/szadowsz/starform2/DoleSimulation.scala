// scalastyle:off method.name
package com.szadowsz.starform2

import com.szadowsz.starform2.model.accrete.{AccreteProfile, AccreteSimulation, AccreteStats}
import com.szadowsz.starform2.system.AccreteSystem
import com.szadowsz.starform2.system.body.planet.DolePlanet
import com.szadowsz.starform2.system.body.star.DoleStar

case class DoleSimulation(profile: AccreteProfile) extends AccreteSimulation[DoleStar,DolePlanet, AccreteStats,AccreteSystem](profile) {



  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[AccreteStats]] instance.
    */
  override protected def initStats(): AccreteStats = new AccreteStats()

  /**
    * Function to generate the Star. Dole uses the values of our own.
    *
    * @return a new star.
    */
  override protected def generateStar(): DoleStar = new DoleStar()

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
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[DolePlanet]): AccreteSystem = {
    AccreteSystem(star,seed, stats, planets)
  }

}