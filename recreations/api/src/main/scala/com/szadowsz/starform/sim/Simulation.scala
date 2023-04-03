package com.szadowsz.starform.sim


import com.szadowsz.starform.system.StarSystem
import com.szadowsz.starform.system.bodies.{Planetismal, Star}

import org.slf4j.Logger
import org.slf4j.LoggerFactory


/**
  * Abstract Simulation Class that attempts to recreated the procedures detailed by Stephen H. Dole in "Formation of Planetary Systems by Aggregation: A
  * Computer Simulation".
  *
  * @tparam S type of class to record the statistics of each system's generation.
  * @tparam P type of protoplanet class to be used as output by the simulation.
  */
trait Simulation[S <: Star,R <: SimulationStats[R], P <: Planetismal, X <: StarSystem[S,R,P]] {

  /**
    * SLF4J built logger to document the goings on during the generation.
    */
  protected val logger: Logger = LoggerFactory.getLogger(getClass)

    /**
      * Function to initialise a new instance at the beginning of each run.
      *
      * @return a new [[SimulationStats]] instance.
      */
    protected def initStats(): R


    /**
      * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
      *
      * @return a new list of [[Planetismal]] instances.
      */
    protected def generatePlanets(): List[P]

    /**
      * Function to initialise a new solar system instance at the end of each run.
      *
      * @return a new [[AbstractStarSystem]] instance.
      */
    protected def createSystem(seed: Long, stats: R, planets: List[P]): X

    /**
      * Function to form a star system by accretion. The main entry point of the generation engine.
      *
      * @see method DistributePlanets, line 89 in Accrete.java - Ian Burrell (accrete)
      * @see method generate_stellar_system, line 84 in main.c - Mat Burdick (accrete)
      * @see method CreateSystem, line 457 in Dole.c - Andrew Folkins (accretion)
      * @see method GenerateSystem, line 164 in main.c - Keris (accretion v1)
      * @see method GenerateSystem, line 514 in main.cc - Keris (accretion v2)
      * @see method generate_stellar_system, line 47 in gensys.c - Keris (starform)
      * @see method generate_stellar_system, line 76 in starform.c - Mat Burdick (starform)
      * @see method Initialize, line 57 in  StarSystem.java - Carl Burke (starform)
      *
      * @param seedOpt optional seed
      * @return the generated solar system.
      */
  def generateSystem(seedOpt: Option[Long] = None): X
}