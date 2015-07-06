package com.szadowsz.accrete.base.bodies

/**
 *
 * Class to represent a band of dust of gas. Contains the inner and outer edge, and whether it has dust or
 * gas present. Uses an internal linked-list structure to maintain the list of bands.
 *
 * @see DustBand.java - Ian Burrell (accrete)
 * @see struct dust_record, line 37 in structs.h - Mat Burdick (accrete)
 * @see struct dust_record, line 37 in structs.h - Mat Burdick (starform)
 * @see DustBand.java - Carl Burke (starform)

 *
 * @param innerLimit inner limit of the dust band
 * @param outerLimit outer limit of the dust band
 * @param dustPresent if dust is present
 * @param gasPresent if gas is present
 *
 * @author zakski
 */
protected[accrete] class DustBand(innerLimit: Double, outerLimit: Double, dustPresent: Boolean, gasPresent: Boolean) {

  var innerEdge: Double = innerLimit

  var outerEdge: Double = outerLimit

  var hasDust: Boolean = dustPresent

  var hasGas: Boolean = gasPresent

  var next: Option[DustBand] = None

  /**
   * Initial Constructor during Accretion
   *
   * @param innerLimit inner limit of the dust band
   * @param outerLimit outer limit of the dust band
   */
  def this(innerLimit: Double, outerLimit: Double) {
    this(innerLimit, outerLimit, true, true)
  }
}