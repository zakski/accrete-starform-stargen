package com.szadowsz.accrete.bodies

import java.text.DecimalFormat

object DustBand {

  def apply(innerEdge: Double, outerEdge: Double): DustBand = {
    new DustBand(innerEdge, outerEdge)
  }
}

/**
  * Class to represent a band of dust of gas. Contains the inner and outer edge, and whether it has dust or
  * gas present.
  *
  * @note Most implementations that I have the source for use an internal linked-list structure to maintain the list of
  *       bands. I have chosen to disregard this choice in scala in order to use scala's robust lambda feature set. In
  *       any case this class can be extended to accommodate the internal structure.
  *
  * @see DustBand.java - Ian Burrell (accrete)
  * @see struct dust_record, line 37 in structs.h - Mat Burdick (accrete)
  * @see struct dust_record, line 37 in structs.h - Mat Burdick (starform)
  * @see DustBand.java - Carl Burke (starform)
  *
  * @constructor Constructor is used make all subsequent dust bands during the splitting process, in which we
  *              acknowledge dust and gas being removed from part of existing bands.
  *
  * @param innerEdge inner limit of the dust band in AU.
  * @param outerEdge outer limit of the dust band in AU.
  * @param hasDust true if dust is present, false otherwise.
  * @param hasGas true if gas is present, false otherwise.
  *
  * @author zakski : 06/07/2015.
  */
case class DustBand(innerEdge: Double, outerEdge: Double, hasDust: Boolean, hasGas: Boolean) {

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

  def canMerge(band: DustBand): Boolean = {
    hasDust == band.hasDust && hasGas == band.hasGas
  }

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