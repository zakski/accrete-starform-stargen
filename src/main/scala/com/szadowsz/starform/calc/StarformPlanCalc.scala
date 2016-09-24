package com.szadowsz.starform.calc

import com.szadowsz.accrete.calc.PlanetesimalCalc
import com.szadowsz.starform.constants.StarformConstants
import com.szadowsz.starform.util.StarUtil

/**
  * @author Zakski : 21/07/2015.
  */
trait StarformPlanCalc extends PlanetesimalCalc {
  this: StarUtil with StarformConstants =>

  /**
    * Method to calculate whether a planetesimal has gained enough mass to accrete gas as well as dust, see "III. Experimental Simulation, section c)
    * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". Modified by Fogg in his eq. 7 to take solar luminosity into
    * account.
    *
    * @note original formula is located in [[com.szadowsz.accrete.calc.PlanetesimalCalc]]
    * @note unit of return value is solar mass.
    *
    * @see eq (7), p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method critical_limit, line 257 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 359 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 435 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 526 in dole.cc - Keris (accretion v2)
    * @see method critical_limit, line 283 in accrete.c - Keris (starform)
    * @see method critical_limit, line 256 in accrete.c - Mat Burdick (starform)
    * @see method critical_limit, line 243 in  Star.java - Carl Burke (starform)
    *
    * @param perihelion closest protoplanet gets to the sun.
    * @return critical mass in solar mass.
    */
  override def criticalMass(perihelion: Double): Double = B * Math.pow(perihelion * Math.sqrt(getStarLuminosity), -0.75)

  //  def isIterative(isGasGiant: Boolean, vGasInventory: Double, greenhouseRadius: Double, axis: Double,
  //                  ecoRadius: Double): Boolean = {
  //    vGasInventory > 0 && !isGasGiant && axis > greenhouseRadius && axis < ecoRadius * 4
  //  }
  //
  //  //
  //  //  /*--------------------------------------------------------------------------*/
  //  //  /*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
  //  //  /*  Earth's Atmosphere" article.  The effective temperature given is in     */
  //  //  /*  units of Kelvin, as is the rise in temperature produced by the          */
  //  //  /*  greenhouse effect, which is returned.                                   */
  //  //  /*--------------------------------------------------------------------------*/
  //  /**
  //    *
  //    *
  //    * @param opticalDepth
  //    * @param effectiveTemp the current effective suface temperature in dgerees kelvin.
  //    * @param surfacePressure the atmosphere pressure in millibars.
  //    * @return the rise in temperature produced by the greenhouse effect in degrees kelvin.
  //    */
  //  def greenhouseEffectDelta(opticalDepth: Double, effectiveTemp: Double, surfacePressure: Double): Double = {
  //    val convection_factor = EARTH_CONVECTION_FACTOR * Math.pow(surfacePressure / EARTH_SURF_PRES_IN_MILLIBARS, 0.25)
  //    (Math.pow(1.0 + 0.75 * opticalDepth, 0.25) - 1.0) * effectiveTemp * convection_factor;
  //  }
  //
}
