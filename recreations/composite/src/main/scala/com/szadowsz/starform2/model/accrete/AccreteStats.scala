package com.szadowsz.starform2.model.accrete

import com.szadowsz.starform2.system.body.Planetismal

/**
  * Abstract Statistics class for the accrete simulation
  *
  *
  * Created on 03/10/2016.
  */
class AccreteStats {

  /**
    * the start time in milliseconds
    */
  protected val startTime: Long = System.currentTimeMillis()

  /**
    * the end time in milliseconds
    */
  protected var endTime: Long = 0

  /**
    * the number of injected protoplanets
    */
  var injectedNuclei: Int = 0

  /**
    * the number of added protoplanets
    */
  var acceptedNuclei: Int = 0

  /**
    * the number of merged protoplanets
    */
  var mergedNuclei: Int = 0

  var minMass : Double = 0

  var maxMass : Double = 0

  var medianMass : Double = 0

  var avgMass : Double = 0

  var varMass : Double = 0

  var stdMass : Double = 0

  /**
    * Function to increment the injected planetismal counter
    *
    * @return updated stats
    */
  def injectNuclei(): this.type = {
    if (endTime == 0) {
      injectedNuclei = injectedNuclei + 1
    }
    this
  }

  /**
    * Function to increment the added planetismal counter
    *
    * @return updated stats
    */
  def acceptNuclei(): this.type = {
    if (endTime == 0) {
      acceptedNuclei = acceptedNuclei + 1
    }
    this
  }

  /**
    * Function to increment the merged planetismal counter
    *
    * @return updated stats
    */
  def mergeNuclei(): this.type = {
    if (endTime == 0) {
      mergedNuclei = mergedNuclei + 1
    }
    this
  }

  /**
    * Function to set the finish time of this simulation
    *
    * @return updated stats
    */
  def finished(pls: List[Planetismal]): this.type = {
    if (endTime == 0) {
      endTime = System.currentTimeMillis()
      val byMass = pls.map(_.mass).sorted
      medianMass = if (byMass.length % 2 != 0) byMass(byMass.length / 2) else (byMass(byMass.length / 2) + byMass(byMass.length / 2 + 1)) / 2
      avgMass = byMass.sum /byMass.length

      val sqDevs = byMass.map(m => Math.pow(m -avgMass,2))
      varMass = sqDevs.sum / sqDevs.length
      stdMass = Math.sqrt(varMass)
      minMass = byMass.head
      maxMass = byMass.last
    }
    this
  }

  /**
    * Function to check the current elapsed time of the simulation
    *
    * @return the time elapsed
    */
  final def timeElapsed: Long = (if (endTime > 0) endTime else System.currentTimeMillis()) - startTime

  /**
    * Function to count the number of rejected nuclei.
    *
    * @return the rejected nuclei count
    */
  final def rejectedNuclei: Int = injectedNuclei - acceptedNuclei - mergedNuclei

  /**
    * Function to calculate the percentage of rejected nuclei.
    *
    * @return the rejected nuclei percentage.
    */
  final def rejectedNucleiPercentage: Double = rejectedNuclei.toDouble / injectedNuclei.toDouble

  /**
    * Function to calculate the percentage of added nuclei.
    *
    * @return the added nuclei percentage.
    */
  final def acceptedNucleiPercentage: Double = acceptedNuclei.toDouble / injectedNuclei.toDouble

  /**
    * Function to calculate the percentage of merged nuclei.
    *
    * @return the merged nuclei percentage.
    */
  final def mergedNucleiPercentage: Double = mergedNuclei.toDouble / injectedNuclei.toDouble

}
