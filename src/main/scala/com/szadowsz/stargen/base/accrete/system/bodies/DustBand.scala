package com.szadowsz.stargen.base.accrete.system.bodies

import java.text.DecimalFormat

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
  * @see struct Band, line 95 in Dole.c - Andrew Folkins (accretion)
  * @see struct Band, line 104 in dole.c - Keris (accretion v1)
  * @see struct Band, line 178 in dole.cc - Keris (accretion v2)
  * @see struct dust_record, line 39 in structs.h - Keris (starform)
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
case class DustBand(innerEdge: Double, outerEdge: Double, hasDust: Boolean = true, hasGas: Boolean  = true) {

  /**
    * Method to check that the levels of dust and gas in an other band suit it being merged with this one.
    *
    * @param band the band to check against
    * @return true if the two bands are compatible, false otherwise
    */
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