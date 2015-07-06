package com.szadowsz.accrete.base.bodies

import java.text.DecimalFormat

import com.szadowsz.accrete.base.calc.{AccreteCalc, PlanetaryCalc}
import com.szadowsz.accrete.util.UnitConverter

/**
 * Class to represent an accreting planetary body. Uses an internal linked-list structure to maintain the
 * ordering of the protoplanets.
 *
 * @author Zakski : 25/06/2015.
 */

protected[accrete] class ProtoPlanet(accrete: AccreteCalc, nmass: Double, naxis: Double, necc: Double) extends PlanetaryCalc {

  private val _accrete = accrete

  /**
   * mass of Planetismal.
   *
   * @note unit of value is Solar Masses.
   */
  var mass: Double = nmass

  /**
   * semi-major axis of the body's orbit.
   *
   * @note unit of value is AU.
   */
  var axis: Double = naxis

  /**
   * eccentricity of the body's orbit
   *
   * @note value between 0.0 and 1.0, range essential for a planet to stay in the system.
   */
  var ecc: Double = necc

  var next: Option[ProtoPlanet] = None

  def innerGravLimit = _accrete.innerGravLimit(perihelion, mass)

  def outerGravLimit = _accrete.outerGravLimit(aphelion, mass)

  def innerBandLimit = _accrete.innerBandLimit(_accrete.innerGravLimit(perihelion, mass))

  def outerBandLimit = _accrete.outerBandLimit(_accrete.outerGravLimit(aphelion, mass))

  def aphelion = aphelionDistance(axis, ecc)

  override def toString: String = {
    var df: DecimalFormat = new DecimalFormat("#.00000")
    val build: StringBuilder = new StringBuilder("[axis: ")
    build.append(df.format(axis) + "AU eccentricity: ")
    build.append(df.format(ecc) + " mass: ")
    df = new DecimalFormat("#.00000E00")
    build.append(df.format(mass))
    if (mass > 2e-15) {
      df = new DecimalFormat("#.00")
      build.append(" (" + df.format(UnitConverter.solarMassToEarthMass(mass) * 100) + "% of Earth Mass)")
    }
    build.append(" gasGiant: " + (if (isGas) "Y" else "N"))
    build.append("]")
    build.toString()
  }

  def isGas = mass >= criticalMass

  def criticalMass = _accrete.criticalMass(perihelion)

  def perihelion = perihelionDistance(axis, ecc)
}
