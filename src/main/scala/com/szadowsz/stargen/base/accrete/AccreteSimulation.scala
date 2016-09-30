package com.szadowsz.stargen.base.accrete

import java.util.Random

import com.szadowsz.stargen.base.accrete.bodies.{DustBand, ProtoPlanet,Planetismal}
import com.szadowsz.stargen.base.accrete.calc.{AccreteCalc, CollisionCalc, PlanetesimalCalc, RandomCalc}
import com.szadowsz.stargen.base.accrete.constants.AccreteConstants
import org.slf4j.{Logger, LoggerFactory}

abstract class AccreteSimulation {
  this: AccreteCalc with PlanetesimalCalc with CollisionCalc with RandomCalc with AccreteConstants =>

  /**
    * SLF4J built logger to document the goings on during the generation.
    */
  protected val logger: Logger = LoggerFactory.getLogger(getClass)

  /**
    * Representation of the dust cloud that the planetismals form from.
    */
  protected var _dust: List[DustBand] = List(DustBand(0.0, outerDustLimit(1.0)))

  /**
    * Current list of coalesced proto-planets in the system.
    */
  protected var _planetismals: List[ProtoPlanet] = Nil

  /**
    * The random number generator to use throughout the process.
    */
  protected val rand: Random

  /**
    * Method to turn all available DustBands into mass for the Planetismal
    *
    * @param proto
    * @param bands
    * @return the new calculated mass
    */
  protected def accreteDust(proto: ProtoPlanet, bands: List[DustBand]): Double = {
    val innerSweep = if (proto.innerBandLimit < 0.0) 0.0 else proto.innerBandLimit
    val outerSweep = proto.outerBandLimit

    bands match {
      case band :: tail =>
        if (band.outerEdge <= innerSweep) {
          accreteDust(proto, tail)
        } else if (band.innerEdge >= outerSweep) {
          0.0
        } else {
          var density: Double = if (band.hasDust) dustDensity(proto.axis) else 0.0

          if (band.hasGas && proto.isGasGiant) {
            density = dustAndGasDensity(density, proto.criticalMass, proto.mass)
          }

          val volume = bandVolume(proto.mass, proto.axis, proto.ecc, innerSweep, outerSweep, band.innerEdge, band.outerEdge)
          // volume X density = mass
          volume * density + accreteDust(proto,tail)
        }
      case Nil => 0.0
    }
  }

  /**
    * Method to split a band into 3 based on a subsumed proto-planet
    *
    * @param band   - the band to split
    * @param hasGas - whether there is gas
    * @return next band
    */
  protected def splitForSubPlanet(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val left = DustBand(band.innerEdge, proto.innerBandLimit, band.hasDust, band.hasGas)
    val middle: DustBand = DustBand(proto.innerBandLimit, proto.outerBandLimit, false, band.hasGas && hasGas)
    val right: DustBand = DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    List(left, middle, right)
  }

  /**
    * Method to split a band into 2 based on overlapping a proto-planet's outer edge
    *
    * @param band   - the band to split
    * @param hasGas - whether there is gas
    * @return next band
    */
  protected def splitOnPlanetMaxEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val right = DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    val left = DustBand(band.innerEdge, proto.outerBandLimit, false, hasGas)
    List(left, right)
  }

  /**
    * Method to split a band into 2 based on overlapping a proto-planet's inner edge
    *
    * @param band   - the band to split
    * @param hasGas - whether there is gas
    * @return next band
    */
  protected def splitOnPlanetMinEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    val right = DustBand(proto.innerBandLimit, band.outerEdge, false, band.hasGas && hasGas)
    val left = DustBand(band.innerEdge, proto.innerBandLimit, band.hasDust, band.hasGas)
    List(left, right)
  }

  /**
    * Split a dust lane into several dust lanes, and mark the dust as used. Returns the next dust lane in the
    * list.
    */
  protected def splitBands(proto: ProtoPlanet, band: DustBand, retainGas: Boolean): List[DustBand] = {
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
    * this function coalesces neighbor dust lanes that have or do not have dust and/or gas
    *
    */
  protected def mergeDustBands(head : DustBand, tail : List[DustBand]): List[DustBand] = {
    tail match {
      case Nil => List(head)

      case other :: ntail if head.canMerge(other) =>
        val nHead = DustBand(head.innerEdge, other.outerEdge, head.hasDust,head.hasGas)
        mergeDustBands(nHead,ntail)

      case nHead :: ntail =>
        List(head) ++ mergeDustBands(nHead,ntail)
    }
  }

  /**
    * Method to Update (Split/Merge) dust bands based on an inserted planet
    *
    * @param proto newly coalesced proto-planet
    */
  protected def updateDustLanes(proto: ProtoPlanet): Unit = {
    val retainGas : Boolean = !proto.isGasGiant
    _dust = _dust.flatMap(d => splitBands(proto, d, retainGas))
    _dust = mergeDustBands(_dust.head,_dust.tail)
  }

  /**
    * Method to merge a newly coalesced planet with an existing one
    *
    * @param planet   the existing planet
    * @param newcomer the new planet
    */
  protected def mergeTwoPlanets(planet: ProtoPlanet, newcomer: ProtoPlanet): Unit = {
    val new_mass: Double = planet.mass + newcomer.mass
    val new_axis: Double = coalesceAxis(planet.mass, planet.axis, newcomer.mass, newcomer.axis)
    val new_ecc: Double = coalesceEccentricity(planet.mass, planet.axis, planet.ecc,
      newcomer.mass, newcomer.axis, newcomer.ecc, new_axis)

    planet.axis = new_axis
    planet.ecc = new_ecc
    planet.mass = new_mass

    accreteDust(planet)
    updateDustLanes(planet)
  }

  /**
    * Method to add a newly coalesced planet
    *
    */
  protected def insertPlanet(proto: ProtoPlanet) {
    _planetismals = (proto +: _planetismals).sortBy(_.axis)
  }

  /**
    * Method to check for collisions between planets and merge them
    *
    * @param newcomer the new plantismal
    * @return true if planets collided, false if not
    */
  protected def coalescePlanetesimals(newcomer: ProtoPlanet): Boolean = {
    val result = _planetismals.find(curr => {
      val dist: Double = curr.axis - newcomer.axis
      var dist1: Double = .0
      var dist2: Double = .0

      if (dist > 0.0) {
        dist1 = newcomer.outerGravLimit - newcomer.axis
        dist2 = curr.axis - curr.innerGravLimit
      } else {
        dist1 = newcomer.axis - newcomer.innerGravLimit
        dist2 = curr.outerGravLimit - curr.axis
      }
      ((Math.abs(dist) <= dist1) || (Math.abs(dist) <= dist2))
    })

    result match {
      case Some(existing) =>
        logger.info("Collision between planetesimals {} AU and {} AU", newcomer.axis, existing.axis)
        mergeTwoPlanets(existing, newcomer)
        true
      case _ =>
        false
    }
  }


  /**
    * Method to calculate the mass for the Planetismal. Sucks mass from all dust bands in range of its gravitational pull during its elliptical orbit.
    *
    * @param proto
    */
  protected def accreteDust(proto: ProtoPlanet): Unit = {
    var lastMass: Double = 0.0
    do {
      lastMass = proto.mass
      val currMass = accreteDust(proto, _dust)
      proto.mass = if (currMass > lastMass) currMass else lastMass
    } while (shouldAccreteContinue(lastMass, proto.mass))
  }

  /**
    * Method to generate a new Planetismal. Varies from implementation to implementation.
    *
    * @return a freshly made proto-planet.
    */
  protected def createProtoplanet() : ProtoPlanet

  /**
    * Steps through list of dust bands checking to see if any of those that bands that overlap the given
    * range have dust present.
    *
    * This is used in two situations:
    *
    * 1: Checking the end conditions of the experiment, that all dust between two arbitrary radii is swept away. This is taken from "III. Experimental
    * Simulation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation"; The inner and outer bounds of where a planet can spawn are
    * used by Dole as these radii, which has been adopted by several subsequent implementations.
    *
    * 2: To check whether an injection at a given AU is possible, based on the curretn dust banding situation.
    *
    * @see pg13. Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    *
    * @param inner the inner limit of the range in AU.
    * @param outer the outer limit of the range in AU.
    * @return whether or not there is still dust between inner and outer limits in this current accretion process.
    */
  protected def isDustAvailable(inner : Double, outer : Double): Boolean = {
    _dust.exists(d => d.hasDust && d.outerEdge > inner  && d.innerEdge < outer)
  }

  /**
    * Method to form planets by accretion
    *
    * @return head of the planet for this system
    */
  protected def accrete(): List[ProtoPlanet] = {
    while (isDustAvailable(INNERMOST_PLANET,OUTERMOST_PLANET)) {
      val proto : ProtoPlanet = createProtoplanet()
      logger.debug("Checking {} AU for suitability.", proto.axis)

      if (isDustAvailable(proto.innerBandLimit,proto.outerBandLimit)) {
        logger.info("Injecting protoplanet at {} AU.", proto.axis)

        accreteDust(proto)
        updateDustLanes(proto)

        if (proto.mass > PROTOPLANET_MASS) {
          if (!coalescePlanetesimals(proto)) {
            insertPlanet(proto)
            logger.info("Injecting protoplanet at {} AU Successful.", proto.axis)
          }
        } else {
          logger.debug("Injection of protoplanet at {} AU failed due to large neighbor.", proto.axis)
        }
      } else {
        logger.debug("Injection of protoplanet at {} AU failed due to no available dust.", proto.axis)
      }
    }
    _planetismals
  }

  /**
    * Method to form planets by accretion, if none have already been formed. The main entrypoint of the generation engine.
    *
    * @return the list of generated proto-planets for this system.
    */
  def generateProtoplanets(): List[Planetismal] = {
    if (_planetismals.isEmpty) {
      logger.info("Beginning generation of protoplanets.")
      accrete()
      logger.info("Finished generation of protoplanets.")
    }
    _planetismals
  }
}