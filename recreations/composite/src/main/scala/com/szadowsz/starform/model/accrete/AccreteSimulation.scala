package com.szadowsz.starform.model.accrete

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.model.accrete.calc.AccreteCalc
import com.szadowsz.starform.model.accrete.calc.collision.CollisionCalc
import com.szadowsz.starform.model.accrete.calc.insert.AccreteInsertStrat
import com.szadowsz.starform.model.accrete.calc.planet.PlanetesimalCalc
import com.szadowsz.starform.model.accrete.constants.AccreteConstants
import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.system.AbstractSystem
import com.szadowsz.starform.system.bodies.base.{DustBand, Planetismal, ProtoPlanet}
import org.slf4j.{Logger, LoggerFactory}

/**
  * Abstract Simulation Class that attempts to recreated the procedures detailed by Stephen H. Dole in "Formation of Planetary Systems by Aggregation: A
  * Computer Simulation".
  *
  * @tparam S type of class to record the statistics of each system's generation.
  * @tparam P type of protoplanet class to be used as output by the simulation.
  */
abstract class AccreteSimulation[S <: SimulationStats[S], P <: Planetismal, R <: AbstractSystem[S,P]](profile : AccreteProfile) extends AccreteSimConstants {

  /**
    * SLF4J built logger to document the goings on during the generation.
    */
  protected val logger: Logger = LoggerFactory.getLogger(getClass)

  /**
    * The random number generator to use throughout the process.
    */
  protected val rand: RandGenTrait = profile.rand

  protected override val aConsts : AccreteConstants = profile.accConsts

  /**
    * the placement strategy to use when inserting new planetismals.
    */
  protected lazy val iStrat: AccreteInsertStrat = profile.buildInsertStrat(this)

  /**
    * calculations innately tied to the protoplanets
    */
  protected lazy val pCalc: PlanetesimalCalc = profile.buildPlanCalc(this)

  /**
    * calculations to work out new protoplanet info after a collision.
    */
  protected lazy val colCalc : CollisionCalc = profile.buildCollCalc(pCalc)

  /**
    * the accretion code to use when hoovering up dust.
    */
  protected lazy val accCalc: AccreteCalc = profile.buildAccCalc(pCalc,this)



   /**
    * The statistics recorder for the accretion process.
    */
  protected var stats: S = _

  /**
    * Representation of the dust cloud that the planetismals form from.
    */
  protected var dust: List[DustBand] = _

  /**
    * Current list of coalesced proto-planets in the system.
    */
  protected var planetismals: List[ProtoPlanet] = _

  /**
    * Function to initialise a new instance at the beginning of each run.
    *
    * @return a new [[SimulationStats]] instance.
    */
  protected def initStats(): S


  /**
    * Function to generate the Planets via accretion. Separated out to allow for the generation of an atmosphere introduced in Martyn J. Fogg's paper.
    *
    * @return a new list of [[Planetismal]] instances.
    */
  protected def generatePlanets(): List[P]

  /**
    * Function to initialise a new solar system instance at the end of each run.
    *
    * @return a new [[AbstractSystem]] instance.
    */
  protected def createSystem(seed: Long, stats: S, planets: List[P]): R

  /**
    * Method to generate a new [[ProtoPlanet]]. Varies from implementation to implementation.
    *
    * @param mass starting mass of the protoplanet in solar mass.
    * @param axis semi-major axis of the orbit in AU.
    * @param ecc  eccentrisity on a scale of 0 to 1
    * @return a freshly made proto-planet.
    */
  final protected  def createProtoplanet(mass: Double, axis: Double, ecc: Double): ProtoPlanet = new ProtoPlanet(pCalc, mass, axis, ecc)

  /**
    * Steps through list of dust bands checking to see if any of those that bands that overlap the given range have dust present.
    *
    * This is used in two situations:
    *
    * 1: Checking the end conditions of the experiment, that all dust between two arbitrary radii is swept away. This is taken from "III. Experimental
    * Simulation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation"; The inner and outer bounds of where a planet can spawn are
    * used by Dole as these radii, which has been adopted by several subsequent implementations.
    *
    * 2: To check whether an injection at a given AU is possible, based on the curretn dust banding situation.
    *
    * @param inner the inner limit of the range in AU.
    * @param outer the outer limit of the range in AU.
    * @return whether or not there is still dust between inner and outer limits in this current accretion process.
    */
  final protected def isDustAvailable(inner: Double, outer: Double): Boolean = dust.exists(d => d.hasDust && d.outerEdge > inner && d.innerEdge < outer)


  /**
    * Function to turn all available DustBands into mass for the Planetismal
    *
    * @see method AccreteDust, line 154 in Accrete.java - Ian Burrell (accrete)
    * @see method accrete_dust, line 269 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 347 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 421 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 515 in dole.cc - Keris (accretion v2)
    * @see method accrete_dust, line 294 in accrete.c - Keris (starform)
    * @see method accrete_dust, line 268 in accrete.c - Mat Burdick (starform)
    * @see method accrete_dust, line 190 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto newly coalesced proto-planet
    * @param bands the current band list.
    * @return the new calculated mass
    */
  final protected def accreteDust(proto: ProtoPlanet, bands: List[DustBand]): Double = {
    val innerSweep = if (proto.innerBandLimit < 0.0) 0.0 else proto.innerBandLimit
    val outerSweep = proto.outerBandLimit

    bands match {
      case band :: tail =>
        if (band.outerEdge <= innerSweep) {
          accreteDust(proto, tail)
        } else if (band.innerEdge >= outerSweep) {
          0.0
        } else {
          var density: Double = if (band.hasDust) accCalc.dustDensity(proto.axis) else 0.0

          if (band.hasGas && proto.isGasGiant) {
            density = accCalc.dustAndGasDensity(density, proto.criticalMass, proto.mass)
          }

          val volume = accCalc.bandVolume(proto.mass, proto.axis, proto.ecc, innerSweep, outerSweep, band.innerEdge, band.outerEdge)
          // volume X density = mass
          volume * density + accreteDust(proto, tail)
        }
      case Nil => 0.0
    }
  }

  /**
    * Function to calculate the mass for the Planetismal. Sucks mass from all dust bands in range of its gravitational pull during its elliptical orbit.
    *
    * @see method AccreteDust, line 154 in Accrete.java - Ian Burrell (accrete)
    * @see method accrete_dust, line 269 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 347 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 421 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 515 in dole.cc - Keris (accretion v2)
    * @see method accrete_dust, line 294 in accrete.c - Keris (starform)
    * @see method accrete_dust, line 268 in accrete.c - Mat Burdick (starform)
    * @see method accrete_dust, line 190 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto newly coalesced proto-planet
    */
  final protected def accreteDust(proto: ProtoPlanet): Unit = {
    var lastMass: Double = 0.0
    do {
      lastMass = proto.mass
      val currMass = accreteDust(proto, dust)
      proto.mass = if (currMass > lastMass) currMass else lastMass
    } while (accCalc.shouldAccreteContinue(lastMass, proto.mass))
  }

  /**
    * Function to split a band into 3 based on a subsumed proto-planet
    *
    * @see method UpdateDustLanes, line 217 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_bands, line 305 in Dole.c - Andrew Folkins (accretion)
    * @see method update_bands, line 367 in dole.c - Keris (accretion v1)
    * @see method update_bands, line 460 in dole.cc - Keris (accretion v2)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method splitband, line 83 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto  newly coalesced proto-planet
    * @param band   the band to split
    * @param hasGas whether there is gas
    * @return the split bands
    */
  final protected def splitForSubPlanet(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val left = DustBand(band.innerEdge, proto.innerBandLimit, band.hasDust, band.hasGas)
    val middle: DustBand = DustBand(proto.innerBandLimit, proto.outerBandLimit, false, band.hasGas && hasGas)
    val right: DustBand = DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    List(left, middle, right)
  }

  /**
    * Function to split a band into 2 based on overlapping a proto-planet's outer edge
    *
    * @see method UpdateDustLanes, line 217 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_bands, line 305 in Dole.c - Andrew Folkins (accretion)
    * @see method update_bands, line 367 in dole.c - Keris (accretion v1)
    * @see method update_bands, line 460 in dole.cc - Keris (accretion v2)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method splithigh, line 105 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto  newly coalesced proto-planet
    * @param band   the band to split
    * @param hasGas whether there is gas
    * @return the split bands
    */
  final protected def splitOnPlanetMaxEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val right = DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    val left = DustBand(band.innerEdge, proto.outerBandLimit, false, hasGas)
    List(left, right)
  }

  /**
    * Function to split a band into 2 based on overlapping a proto-planet's inner edge
    *
    * @see method UpdateDustLanes, line 217 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_bands, line 305 in Dole.c - Andrew Folkins (accretion)
    * @see method update_bands, line 367 in dole.c - Keris (accretion v1)
    * @see method update_bands, line 460 in dole.cc - Keris (accretion v2)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method splitlow, line 123 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto  newly coalesced proto-planet
    * @param band   the band to split
    * @param hasGas whether there is gas
    * @return the split bands
    */
  final protected def splitOnPlanetMinEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val right = DustBand(proto.innerBandLimit, band.outerEdge, false, band.hasGas && hasGas)
    val left = DustBand(band.innerEdge, proto.innerBandLimit, band.hasDust, band.hasGas)
    List(left, right)
  }

  /**
    * Split a dust lane into several dust lanes, and mark the dust as used. Returns the next dust lane in the list.
    *
    * @see method UpdateDustLanes, line 217 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_bands, line 305 in Dole.c - Andrew Folkins (accretion)
    * @see method update_bands, line 367 in dole.c - Keris (accretion v1)
    * @see method update_bands, line 460 in dole.cc - Keris (accretion v2)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method update_dust_lanes, line 141 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto     newly coalesced proto-planet
    * @param band      current dust band we are examining
    * @param retainGas if the dust stripped bands will also retain gas.
    * @return a list of bands created from the examined band.
    */
  final protected def splitBands(proto: ProtoPlanet, band: DustBand, retainGas: Boolean): List[DustBand] = {
    if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.outerBandLimit) {
      splitForSubPlanet(proto, band, retainGas)

    } else if (band.innerEdge < proto.outerBandLimit && band.outerEdge > proto.outerBandLimit) {
      splitOnPlanetMaxEdge(proto, band, retainGas)

    } else if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.innerBandLimit) {
      splitOnPlanetMinEdge(proto, band, retainGas)

    } else if (band.innerEdge >= proto.innerBandLimit && band.outerEdge <= proto.outerBandLimit) {
      List(DustBand(band.innerEdge, band.outerEdge, false, if (band.hasGas) retainGas else false))
    } else {
      List(band)
    }
  }

  /**
    * Function merges neighbouring dust lanes that have the same characteristics after an inserted planet has accreted dust/gas.
    *
    * @note Folkins' code line does not merge bands.
    *
    * @see method CompressDustLanes, line 285 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method update_dust_lanes, line 141 in  DustDisc.java - Carl Burke (starform)
    *
    * @param head the current dust band we are trying to merge.
    * @param tail the remaining un merged dust bands.
    * @return the updated dust band list.
    */
  final protected def mergeDustBands(head: DustBand, tail: List[DustBand]): List[DustBand] = {
    tail match {
      case Nil => List(head)

      case other :: ntail if head.canMerge(other) =>
        val nHead = DustBand(head.innerEdge, other.outerEdge, head.hasDust, head.hasGas)
        mergeDustBands(nHead, ntail)

      case nHead :: ntail =>
        List(head) ++ mergeDustBands(nHead, ntail)
    }
  }

  /**
    * Function to Update (Split/Merge) dust bands after an inserted planet has accreted dust/gas.
    *
    * @see method UpdateDustLanes, line 217 in Accrete.java - Ian Burrell (accrete)
    * @see method update_dust_lanes, line 96 in accrete.c - Mat Burdick (accrete)
    * @see method update_bands, line 305 in Dole.c - Andrew Folkins (accretion)
    * @see method update_bands, line 367 in dole.c - Keris (accretion v1)
    * @see method update_bands, line 460 in dole.cc - Keris (accretion v2)
    * @see method update_dust_lanes, line 120 in accrete.c - Keris (starform)
    * @see method update_dust_lanes, line 95 in accrete.c - Mat Burdick (starform)
    * @see method update_dust_lanes, line 141 in  DustDisc.java - Carl Burke (starform)
    *
    * @param proto newly coalesced proto-planet
    */
  final protected def updateDustLanes(proto: ProtoPlanet): Unit = {
    logger.debug("Updating Dust Lanes")
    val retainGas: Boolean = !proto.isGasGiant // done here to save recalculating if the planet is a gas giant a bunch of times.
    dust = dust.flatMap(d => splitBands(proto, d, retainGas))
    dust = mergeDustBands(dust.head, dust.tail)
  }

  /**
    * Function to add a newly coalesced planet to the list of protoplanets in the system.
    *
    * @see method InsertPlanet, line 351 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, line 290 in accrete.c - Mat Burdick (accrete)
    * @see method CreatePlanet, line 136 in Dole.c - Andrew Folkins (accretion)
    * @see method AddPlanet, line 170 in dole.c - Keris (accretion v1)
    * @see method AddPlanet, line 265 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, line 316 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, line 289 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, line 53 in  Protosystem.java - Carl Burke (starform)
    *
    * @param proto the new protoplanet to add to the list of protoplanets.
    */
  final protected def insertPlanet(proto: ProtoPlanet): Unit = {
    stats = stats.acceptNuclei
    planetismals = (proto +: planetismals).sortBy(_.axis)
    logger.info("Injecting protoplanet at {} AU Successful.", proto.axis)
  }

  /**
    * Function to merge a newly coalesced planet with an existing one.
    *
    * @see method CoalesceTwoPlanets, line 331 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, line 290 in accrete.c - Mat Burdick (accrete)
    * @see method MergePlanets, line 409 in Dole.c - Andrew Folkins (accretion)
    * @see method MergePlanets, line 492 in dole.c - Keris (accretion v1)
    * @see method MergePlanets, line 586 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, line 316 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, line 289 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, line 53 in  Protosystem.java - Carl Burke (starform)
    *
    * @param planet   the existing planet
    * @param newcomer the new planet
    */
  final protected def mergeTwoPlanets(planet: ProtoPlanet, newcomer: ProtoPlanet): Unit = {
    val new_mass: Double = planet.mass + newcomer.mass
    val new_axis: Double = colCalc.coalesceAxis(planet.mass, planet.axis, newcomer.mass, newcomer.axis)
    val new_ecc: Double = colCalc.coalesceEccentricity(planet.mass, planet.axis, planet.ecc, newcomer.mass, newcomer.axis, newcomer.ecc, new_axis)

    planet.axis = new_axis
    planet.ecc = new_ecc
    planet.mass = new_mass

    accreteDust(planet)
    updateDustLanes(planet)
  }

  /**
    * Function to check for collisions between planets and merge them
    *
    * @see method CoalescePlanetismals, line 304 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, line 290 in accrete.c - Mat Burdick (accrete)
    * @see method CheckCoalesence, line 426 in Dole.c - Andrew Folkins (accretion)
    * @see method CheckCoalesence, line 519 in dole.c - Keris (accretion v1)
    * @see method CheckCoalesence, line 617 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, line 316 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, line 289 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, line 53 in  Protosystem.java - Carl Burke (starform)
    *
    * @param newcomer the new plantismal
    * @return true if the newcomer collided with an existing planet, false if not
    */
  final protected def coalescePlanetesimals(newcomer: ProtoPlanet): Boolean = {
    logger.debug("Checking for collisions.")
    val result = planetismals.find(p => (p.axis > newcomer.axis && (p.innerGravLimit < newcomer.axis || newcomer.outerGravLimit > p.axis)) ||
      (p.axis <= newcomer.axis && (p.outerGravLimit > newcomer.axis || newcomer.innerGravLimit < p.axis)))

    result.foreach { existing =>
      logger.info("Collision between planetesimals {} AU and {} AU", newcomer.axis, existing.axis)
      stats = stats.mergeNuclei
      mergeTwoPlanets(existing, newcomer)
    }
    result.isDefined
  }

  /**
    * Function to form protoplanets by accretion. Main accretion loop.
    *
    * @see method DistributePlanets, line 89 in Accrete.java - Ian Burrell (accrete)
    * @see method dist_planetary_masses, line 393 in accrete.c - Mat Burdick (accrete)
    * @see method CreatePlanet, line 137 & method CreateSystem, line 457 in Dole.c - Andrew Folkins (accretion)
    * @see method CreatePlanet, line 190 & method CreateSystem, line 560 in dole.c - Keris (accretion v1)
    * @see method CreatePlanet, line 278 & method CreateSystem, line 664 in dole.cc - Keris (accretion v2)
    * @see method dist_planetary_masses, line 419 in accrete.c - Keris (starform)
    * @see method dist_planetary_masses, line 392 in accrete.c - Mat Burdick (starform)
    * @see method dist_planetary_masses, line 145 in  Protosystem.java - Carl Burke (starform)
    */
  final protected def accrete(): Unit = {
    logger.debug("Initialising Statistics Recorder")
    planetismals = Nil
    dust = List(DustBand(0.0, accCalc.outerDustLimit(1.0))) // TODO outerDustLimit function goes against the spirit of the base sim and needs to be refactored.

    while (isDustAvailable(INNERMOST_PLANET, OUTERMOST_PLANET)) {
      val axis = iStrat.semiMajorAxis(rand, stats.injectedNuclei, dust)
      val ecc = iStrat.eccentricity(rand)
      val proto: ProtoPlanet = createProtoplanet(PROTOPLANET_MASS, axis, ecc)
      stats = stats.injectNuclei
      logger.debug("Checking {} AU for suitability.", proto.axis)

      if (isDustAvailable(proto.innerBandLimit, proto.outerBandLimit)) {
        logger.info("Injecting protoplanet at {} AU.", proto.axis)

        accreteDust(proto)
        updateDustLanes(proto)

        if (proto.mass > PROTOPLANET_MASS) {
          if (!coalescePlanetesimals(proto)) {
            insertPlanet(proto)
          }
        } else {
          // TODO check if this if/else is needed
          logger.debug("Injection of protoplanet at {} AU failed due to large neighbor.", proto.axis)
        }
      } else {
        logger.debug("Injection of protoplanet at {} AU failed due to no available dust.", proto.axis)
      }
    }
  }

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
  final def generateSystem(seedOpt: Option[Long] = None): R = {
    logger.debug("Initialising Statistics Recorder")
    stats = initStats()

    seedOpt.foreach(s => rand.setSeed(s))
    val seed = seedOpt.getOrElse(rand.getSeed)
    logger.debug("Setting Star System Seed to {}", seed)

    logger.info("Beginning Protoplanet Generation for {}", seed)

    val planets = generatePlanets()
    stats = stats.finished

    logger.info("Finished Protoplanet Generation for {} in {}ms", seed, stats.timeElapsed)
    createSystem(seed, stats, planets)
  }
}