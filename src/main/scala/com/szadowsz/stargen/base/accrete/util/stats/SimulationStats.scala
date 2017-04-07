package com.szadowsz.stargen.base.accrete.util.stats

/**
  * Statistical Base class to specify all relevant information to be recorded.
  *
  * @tparam T the sub-class type instance being used.
  */
abstract class SimulationStats[T <: SimulationStats[T]] {

  val startTime: Long

  val endTime: Long

  val injectedNuclei: Int

  val acceptedNuclei: Int

  val mergedNuclei: Int

  /**
    * Function to increment the injected planetismal counter
    *
    * @return updated stats
    */
  def injectNuclei: T

  /**
    * Function to increment the added planetismal counter
    *
    * @return updated stats
    */
  def acceptNuclei: T

  /**
    * Function to increment the merged planetismal counter
    *
    * @return updated stats
    */
  def mergeNuclei: T

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
  def finished: T
}
