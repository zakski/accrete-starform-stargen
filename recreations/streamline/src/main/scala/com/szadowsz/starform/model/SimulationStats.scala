package com.szadowsz.starform.model

/**
  * Statistical class to specify all relevant information to be recorded.
  */
case class  SimulationStats(start: Long = System.currentTimeMillis(), end: Long = 0, injectedNuclei: Int = 0, acceptedNuclei: Int = 0, mergedNuclei: Int = 0) {

  /**
    * Function to increment the injected planetismal counter
    *
    * @return updated stats
    */
  def injectNuclei: SimulationStats = copy(injectedNuclei = injectedNuclei + 1)

  /**
    * Function to increment the added planetismal counter
    *
    * @return updated stats
    */
  def acceptNuclei: SimulationStats = copy(acceptedNuclei = acceptedNuclei + 1)

  /**
    * Function to increment the merged planetismal counter
    *
    * @return updated stats
    */
  def mergeNuclei: SimulationStats = copy(mergedNuclei = mergedNuclei + 1)

  /**
    * Function to check the current elapsed time of the simulation
    *
    * @return the time elapsed
    */
  final def timeElapsed: Long = (if (end > 0) end else System.currentTimeMillis()) - start

  /**
    * Function to count the number of rejected nuclei.
    *
    * @return the rejected nuclei count
    */
  final def rejectedNuclei : Int = injectedNuclei - acceptedNuclei - mergedNuclei

  /**
    * Function to calculate the percentage of rejected nuclei.
    *
    * @return the rejected nuclei percentage.
    */
  final def rejectedNucleiPercentage : Double = rejectedNuclei.toDouble / injectedNuclei.toDouble

  /**
    * Function to calculate the percentage of added nuclei.
    *
    * @return the added nuclei percentage.
    */
  final def acceptedNucleiPercentage : Double = acceptedNuclei.toDouble / injectedNuclei.toDouble

  /**
    * Function to calculate the percentage of merged nuclei.
    *
    * @return the merged nuclei percentage.
    */
  final def mergedNucleiPercentage : Double = mergedNuclei.toDouble / injectedNuclei.toDouble

  /**
    * Function to set the finish time of this simulation
    *
    * @return updated stats
    */
  def finished: SimulationStats = copy(end = System.currentTimeMillis())
}
