package com.szadowsz.accrete.base.process

import java.util.Random

import com.szadowsz.accrete.base.bodies.{DustBand, ProtoPlanet}
import com.szadowsz.accrete.base.calc.{AccreteCalc, CollisionCalc, PlanetesimalCalc}
import com.szadowsz.accrete.base.constants.AccreteConstants
import org.slf4j.{Logger, LoggerFactory}

abstract class AbstractProcess(random: Random) {
  this: AccreteCalc with PlanetesimalCalc with CollisionCalc with AccreteConstants =>

  protected val _logger: Logger = LoggerFactory.getLogger(classOf[AbstractProcess])

  protected val _rand: Random = random
  protected var _dustHead: DustBand = null
  protected var _innermost: ProtoPlanet = null
  protected var _planetCount: Int = 0
  protected var _hasDust: Boolean = false

  /**
   * Method to return the number of planets generated
   *
   * @return the _planetCount
   */
  def getPlanetCount: Int = {
    _planetCount
  }

  /**
   * Method to form planets by accretion
   *
   * @return head of the planet for this system
   */
  def accrete(): ProtoPlanet = {
    if (_innermost == null)
      accrete(_rand)
    else
      _innermost
  }

  protected def createProtoPlanet(): ProtoPlanet = {
    val axis: Double = semiMajorAxis(_rand)
    val ecc: Double = eccentricity(_rand)
    var mass: Double = PROTOPLANET_MASS
    new ProtoPlanet(this, mass, axis, ecc)
  }

  /**
   * Steps through list of dust bands checking to see if any of those that bands that overlap the given
   * range have dust present.
   *
   * @param proto the protoplanet trying to pull dust
   * @return whether or not there is still dust between innerBandLimit and outerBandLimit in this current
   *         accretion process.
   */
  protected def isDustAvailable(proto: ProtoPlanet): Boolean = {
    var current: DustBand = _dustHead
    var hasDust: Boolean = false
    while (current != null && current.outerEdge < proto.innerBandLimit) {
      current = current.next.orNull
    }

    while (current != null && current.innerEdge < proto.outerBandLimit) {
      hasDust = hasDust || current.hasDust
      current = current.next.orNull
    }

    hasDust
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
      val currMass = accreteDust(proto, _dustHead)
      proto.mass = if (currMass > lastMass) currMass else lastMass
    } while (shouldAccreteContinue(lastMass, proto.mass))
  }

  /**
   * Method to turn all available DustBands into mass for the protoplanet
   *
   * @param proto
   * @param band
   * @return the new calculated mass
   */
  protected def accreteDust(proto: ProtoPlanet, band: DustBand): Double = {
    if (band == null) {
      return 0.0
    }
    var innerSweep = proto.innerBandLimit
    var outerSweep = proto.outerBandLimit

    if (innerSweep < 0.0) {
      innerSweep = 0.0
    }

    if (band.outerEdge <= innerSweep) {
      accreteDust(proto, band.next.orNull)
    } else if (band.innerEdge >= outerSweep) {
      0.0
    } else {
      var density: Double = if (band.hasDust) dustCloudDensity(proto.axis) else 0.0

      if (band.hasGas && proto.isGas) {
        density = cloudDensity(density, proto.criticalMass, proto.mass)
      }
      val volume = bandVolume(proto.mass, proto.axis, proto.ecc, innerSweep, outerSweep, band.innerEdge, band.outerEdge)
      volume * density + accreteDust(proto, band.next.orNull)
    }
  }

  /**
   * Method to split a band into 3 based on a subsumed proto-planet
   *
   * @param band   - the band to split
   * @param hasGas - whether there is gas
   * @return next band
   */
  protected def splitForSubPlanet(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): DustBand = {
    val middle: DustBand = new DustBand(proto.innerBandLimit, proto.outerBandLimit, false, band.hasGas && hasGas)
    val right: DustBand = new DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    right.next = band.next
    middle.next = Some(right)
    band.next = Some(middle)
    band.outerEdge = proto.innerBandLimit
    right.next.orNull
  }

  /**
   * Method to split a band into 2 based on overlapping a proto-planet's outer edge
   *
   * @param band   - the band to split
   * @param hasGas - whether there is gas
   * @return next band
   */
  protected def splitOnPlanetMaxEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): DustBand = {
    val right: DustBand = new DustBand(proto.outerBandLimit, band.outerEdge, band.hasDust, band.hasGas)
    right.next = band.next
    band.next = Some(right)
    band.outerEdge = proto.outerBandLimit
    band.hasDust = false
    band.hasGas = hasGas
    right.next.orNull
  }

  /**
   * Method to split a band into 2 based on overlapping a proto-planet's inner edge
   *
   * @param band   - the band to split
   * @param hasGas - whether there is gas
   * @return next band
   */
  protected def splitOnPlanetMinEdge(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): DustBand = {
    val right: DustBand = new DustBand(proto.innerBandLimit, band.outerEdge, false, band.hasGas && hasGas)
    right.next = band.next
    band.next = Some(right)
    band.outerEdge = proto.innerBandLimit
    right.next.orNull
  }

  /**
   * Split a dust lane into several dust lanes, and mark the dust as used. Returns the next dust lane in the
   * list.
   */
  protected def splitBands(proto: ProtoPlanet, band: DustBand, hasGas: Boolean): DustBand = {
    if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.outerBandLimit) {
      return splitForSubPlanet(proto, band, hasGas)
    }
    else if (band.innerEdge < proto.outerBandLimit && band.outerEdge > proto.outerBandLimit) {
      return splitOnPlanetMaxEdge(proto, band, hasGas)
    }
    else if (band.innerEdge < proto.innerBandLimit && band.outerEdge > proto.innerBandLimit) {
      return splitOnPlanetMinEdge(proto, band, hasGas)
    }
    else if (band.innerEdge >= proto.innerBandLimit && band.outerEdge <= proto.outerBandLimit) {
      band.hasDust = false
      if (band.hasGas) {
        band.hasGas = hasGas
      }
      return band.next.orNull
    }
    else if (band.outerEdge < proto.innerBandLimit || band.innerEdge > proto.outerBandLimit) {
      return band.next.orNull
    }
    band
  }

  /**
   * this function coalesces neighbor dust lanes that have or do not have dust and/or gas
   *
   */
  protected def mergeDustBands() {
    {
      var lane: DustBand = _dustHead
      while (lane != null) {
        {
          if (lane.hasDust && lane.outerEdge >= INNERMOST_PLANET && lane.innerEdge <= OUTERMOST_PLANET) {
            _hasDust = true
          }
          if (lane.next.isDefined && lane.hasDust == lane.next.get.hasDust && lane.hasGas == lane.next.get.hasGas) {
            lane.outerEdge = lane.next.get.outerEdge
            lane.next = lane.next.get.next
          }
        }
        lane = lane.next.orNull
      }
    }
  }

  /**
   * Method to Update (Split/Merge) dust bands based on an inserted planet
   *
   * @param proto  newly coalesced proto-planet
   */
  protected def updateDustLanes(proto: ProtoPlanet) {
    _hasDust = false
    val removeGas: Boolean = proto.mass <= proto.criticalMass

    var lane: DustBand = _dustHead
    while (lane != null) {
      lane = splitBands(proto, lane, removeGas)
    }

    mergeDustBands()
  }

  /**
   * Method to merge a newly coalesced planet with an existing one
   *
   * @param planet the existing planet
   * @param newcomer the new planet
   */
  protected def mergeTwoPlanets(planet: ProtoPlanet, newcomer: ProtoPlanet) {
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
    if (_innermost == null) {
      _innermost = proto
    }
    else if (proto.axis < _innermost.axis) {
      proto.next = Some(_innermost)
      _innermost = proto
    } else {
      var prev: ProtoPlanet = _innermost
      var curr: ProtoPlanet = _innermost.next.orNull
      while ((curr != null) && (curr.axis < proto.axis)) {
        prev = curr
        curr = curr.next.orNull
      }
      proto.next = prev.next
      prev.next = Some(proto)
    }
  }

  /**
   * Method to check for collisions between planets and merge them
   *
   * @param newcomer the new plantismal
   * @return true if planets collided, false if not
   */
  protected def coalescePlanetesimals(newcomer: ProtoPlanet): Boolean = {

    var curr: ProtoPlanet = _innermost
    while (curr != null) {
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

      if ((Math.abs(dist) <= dist1) || (Math.abs(dist) <= dist2)) {
        _logger.debug("Collision between planetesimals {} and {}", Array(newcomer, curr))
        mergeTwoPlanets(curr, newcomer)
        return true
      }
      curr = curr.next.orNull
    }
    false
  }

  /**
   * Method to form planets by accretion
   *
   * @param rand - pseudo-random number generator
   * @return head of the planet for this system
   */
  protected def accrete(rand: Random): ProtoPlanet = {
    _hasDust = true
    _dustHead = new DustBand(0.0, outerDustLimit(1.0))
    while (_hasDust) {
      val proto = createProtoPlanet()
      _logger.debug("Checking {} AU for suitability.", proto.axis)

      if (isDustAvailable(proto)) {
        _logger.debug("Injecting protoplanet at {} AU.", proto.axis)

        accreteDust(proto)
        updateDustLanes(proto)

        if (proto.mass > PROTOPLANET_MASS) {
          if (!coalescePlanetesimals(proto)) {
            insertPlanet(proto)
            _planetCount += 1
            _logger.info("Injecting protoplanet at {} AU Successful.", proto.axis)
          }
        } else {
          _logger.debug("Injection of protoplanet at {} AU failed due to large neighbor.", proto.axis)
        }
      }
      else {
        _logger.debug("Injection of protoplanet at {} AU failed due to no available dust.", proto.axis)
      }
    }
    _innermost
  }
}