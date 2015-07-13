package com.szadowsz.accrete.base.bodies

import java.text.DecimalFormat

/**
 * Class to represent a band of dust of gas. Contains the inner and outer edge, and whether it has dust or
 * gas present. Uses an internal linked-list structure to maintain the list of bands.
 *
 * @see DustBand.java - Ian Burrell (accrete)
 * @see struct dust_record, line 37 in structs.h - Mat Burdick (accrete)
 * @see struct dust_record, line 37 in structs.h - Mat Burdick (starform)
 * @see DustBand.java - Carl Burke (starform)
 *
 * @constructor Constructor is used make all subsequent dust bands during the splitting process, in which we
 *              acknowledge dust and gas being removed from part of existing bands.
 *
 * @param innerLimit inner limit of the dust band in AU.
 * @param outerLimit outer limit of the dust band in AU.
 * @param dustPresent true if dust is present, false otherwise.
 * @param gasPresent true if gas is present, false otherwise.
 *
 * @author zakski : 06/07/2015.
 */
protected[accrete] class DustBand(innerLimit: Double, outerLimit: Double, dustPresent: Boolean, gasPresent: Boolean) {

  /**
   * The edge of the dust band closest to the star.
   *
   * @note unit is AU.
   */
  var innerEdge: Double = innerLimit

  /**
   * The edge of the dust band furthest to the star.
   *
   * @note unit is AU.
   */
  var outerEdge: Double = outerLimit

  /**
   * Whether the band has dust remaining.
   */
  var hasDust: Boolean = dustPresent

  /**
   * Whether the band has gas remaining.
   *
   * @note gas is only removed if a coalescing planet has attained critical mass.
   */
  var hasGas: Boolean = gasPresent

  /**
   * Internal LinkedList structure to keep track of dust bands, starting with the closest to the star and
   * ending with the furthest. If it is not defined then the band is the furthest from the star.
   */
  var next: Option[DustBand] = None

  /**
   * Initial Constructor during Accretion. Used solely to form the first band of gas and dust as it is the only
   * time at which both gas and dust can be assumed to be present.
   *
   * @param innerLimit inner limit of the dust band in AU.
   * @param outerLimit outer limit of the dust band in AU.
   */
  def this(innerLimit: Double, outerLimit: Double) {
    this(innerLimit, outerLimit, true, true)
  }

  /**
   * Convenience Method to check if there are more dust bands after it.
   *
   * @return true if it is not the furthest dust band, false otherwise.
   */
  def hasNext: Boolean = next.isDefined

  /**
   * Method to supply String representation of the band.
   *
   * @return current status of the band in String form.
   */
  override def toString: String = {
    val df: DecimalFormat = new DecimalFormat("#.00000")
    val build: StringBuilder = new StringBuilder("[band: ")
    build.append(df.format(innerEdge) + " - ")
    build.append(df.format(outerEdge) + "AU ")
    build.append(" dust: " + (if (hasDust) "Y" else "N"))
    build.append(" gas: " + (if (hasGas) "Y" else "N"))
    build.append("]")
    build.toString()

  }
}