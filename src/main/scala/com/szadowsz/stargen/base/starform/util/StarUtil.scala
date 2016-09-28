// TODO Investigate whether this is the best way forward
package com.szadowsz.stargen.base.starform.util

/**
  * Utility trait to allow for the inclusion of Star information into inherited functions without needing to change their signature.
  *
  * @author Zakski : 31/12/2015.
  */
trait StarUtil {

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarLuminosity: Double

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarMass: Double

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarAge: Double

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarEcosphereRadius: Double

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  def getStarGreenhouseRadius: Double
}
