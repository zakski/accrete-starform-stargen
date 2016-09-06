package com.szadowsz.accrete

import java.util.Random

import com.szadowsz.accrete.bodies.{DustBand, Planet, ProtoPlanet}
import com.szadowsz.accrete.calc.{AccreteCalc, CollisionCalc, PlanetesimalCalc}
import com.szadowsz.accrete.constants.AccreteConstants
import org.slf4j.{Logger, LoggerFactory}

abstract class AbstractSimulation {
  this: AccreteCalc with PlanetesimalCalc with CollisionCalc with AccreteConstants =>

  protected val rand: Random

  protected val logger: Logger = LoggerFactory.getLogger(getClass)

  protected var _planets: List[Planet] = Nil

  protected var _planetismals: List[ProtoPlanet] = Nil

  protected var _dust: List[DustBand] = Nil

  /**
    * Method to form planets by accretion
    *
    * @return head of the planet for this system
    */
  def accrete(): List[Planet] = {
    if (_planets.isEmpty) {
      logger.info("Beginning generation of protoplanets.")
      _planets = accrete(rand).map(p => Planet(p))
    }
    _planets
  }

  protected def createDust(): List[DustBand] = {
    List(DustBand(0.0, outerDustLimit(1.0)))
  }

  protected def createProtoplanet(): ProtoPlanet = {
    val axis: Double = semiMajorAxis(rand)
    val ecc: Double = eccentricity(rand)
    val mass: Double = PROTOPLANET_MASS
    ProtoPlanet(this, mass, axis, ecc)
  }

  /**
    * Steps through list of dust bands checking to see if any of those that bands that overlap the given
    * range have dust present.
    *
    * @param inner the inner limit of the range in AU.
    * @param outer the outer limit of the range in AU.
    * @return whether or not there is still dust between inner and outer limits in this current accretion process.
    */
  protected def isDustAvailable(inner : Double, outer : Double): Boolean = {
    _dust.exists(d => d.hasDust && d.outerEdge > INNERMOST_PLANET  && d.innerEdge < OUTERMOST_PLANET)
  }


  /**
    * Method to calculate the mass for the protoplanet
    *
    * @param proto
    */
  protected def accreteDust(proto: ProtoPlanet): Unit = {
    var lastMass: Double = .0
    do {
      lastMass = proto.mass
      val currMass = accreteDust(proto, _dust)
      proto.mass = if (currMass > lastMass) currMass else lastMass
    } while (shouldAccreteContinue(lastMass, proto.mass))
  }

  /**
    * Method to turn all available DustBands into mass for the protoplanet
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
          var density: Double = if (band.hasDust) dustCloudDensity(proto.axis) else 0.0

          if (band.hasGas && proto.isGas) {
            density = cloudDensity(density, proto.criticalMass, proto.mass)
          }

          val volume = bandVolume(proto.mass, proto.axis, proto.ecc, innerSweep, outerSweep, band.innerEdge, band.outerEdge)
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
  protected def splitBands(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): List[DustBand] = {
    if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.outerBandLimit) {
      splitForSubPlanet(proto, band, hasGas)

    } else if (band.innerEdge < proto.outerBandLimit && band.outerEdge > proto.outerBandLimit) {
      splitOnPlanetMaxEdge(proto, band, hasGas)

    } else if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.innerBandLimit) {
      splitOnPlanetMinEdge(proto, band, hasGas)

    } else if (band.innerEdge >= proto.innerBandLimit && band.outerEdge <= proto.outerBandLimit) {
      List(DustBand(band.innerEdge, band.outerEdge, false, if (band.hasGas) hasGas else false))
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
    val removeGas: Boolean = proto.mass <= proto.criticalMass
    _dust = _dust.flatMap(d => splitBands(proto, d, removeGas))
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
    * Method to form planets by accretion
    *
    * @param rand - pseudo-random number generator
    * @return head of the planet for this system
    */
  protected def accrete(rand: Random): List[ProtoPlanet] = {
    _dust = createDust()
    while (isDustAvailable(INNERMOST_PLANET,OUTERMOST_PLANET)) {
      val proto = createProtoplanet()
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
}