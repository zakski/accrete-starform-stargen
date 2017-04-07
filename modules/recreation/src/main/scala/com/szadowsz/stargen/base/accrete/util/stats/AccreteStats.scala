package com.szadowsz.stargen.base.accrete.util.stats

/**
  * Concrete Statistics case class for the accrete simulation
  *
  * @param startTime the start time in milliseconds
  * @param endTime the end time in milliseconds
  * @param injectedNuclei the number of injected protoplanets
  * @param acceptedNuclei the number of added protoplanets
  * @param mergedNuclei the number of merged protoplanets
  *
  * 03/10/2016.
  */
case class AccreteStats(
                         override val startTime: Long = System.currentTimeMillis(),
                         override val endTime: Long = 0,
                         override val injectedNuclei: Int = 0,
                         override val acceptedNuclei: Int = 0,
                         override val mergedNuclei: Int = 0
                       ) extends SimulationStats[AccreteStats] {

  /**
    * Function to increment the injected planetismal counter
    *
    * @return updated stats
    */
  override def injectNuclei: AccreteStats = copy(injectedNuclei = injectedNuclei + 1)

  /**
    * Function to increment the added planetismal counter
    *
    * @return updated stats
    */
  override def acceptNuclei: AccreteStats = copy(acceptedNuclei = acceptedNuclei + 1)

  /**
    * Function to increment the merged planetismal counter
    *
    * @return updated stats
    */
  override def mergeNuclei: AccreteStats = copy(mergedNuclei = mergedNuclei + 1)

  /**
    * Function to set the finish time of this simulation
    *
    * @return updated stats
    */
  override def finished: AccreteStats = copy(endTime = System.currentTimeMillis())
}
