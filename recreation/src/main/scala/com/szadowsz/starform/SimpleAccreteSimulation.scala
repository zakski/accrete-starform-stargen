package com.szadowsz.starform

import com.szadowsz.starform.model.accrete.{AccreteProfile, AccreteSimulation, AccreteStats}
import com.szadowsz.starform.model.accrete.body.ProtoPlanet
import com.szadowsz.starform.system.SolLikeSystem
import com.szadowsz.starform.system.star.Sol

class SimpleAccreteSimulation(profile : AccreteProfile) extends AccreteSimulation[Sol,ProtoPlanet,AccreteStats,SolLikeSystem](profile) {
  /**
   * Function to initialise a new instance at the beginning of each run.
   *
   * @return a new [[AccreteStats]] instance.
   */
  override protected def initStats(): AccreteStats = ???
  
  /**
   * Function to generate the Star. Dole uses the values of our own.
   *
   * @return a new star.
   */
  override protected def generateStar(): Sol = ???
  
  /**
   * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
   *
   * @return a new list of [[Planetismal]] instances.
   */
  override protected def generatePlanets(): List[ProtoPlanet] = ???
  
  /**
   * Function to initialise a new solar system instance at the end of each run.
   *
   * @return a new [[AbstractStarSystem]] instance.
   */
  override protected def createSystem(seed: Long, stats: AccreteStats, planets: List[ProtoPlanet]): SolLikeSystem = ???
}
