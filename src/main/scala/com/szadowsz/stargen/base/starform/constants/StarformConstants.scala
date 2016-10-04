// scalastyle:off method.name
package com.szadowsz.stargen.base.starform.constants

import com.szadowsz.stargen.base.accrete.constants.AccreteConstants
import com.szadowsz.stargen.base.starform.system.bodies.Star

/**
  * Constants Specific to Martyn J. Fogg's adaptation of Dole's paper.
  *
  * @author Zakski : 26/06/2015.
  */
trait StarformConstants[S <: Star] extends AccreteConstants {

  var star : S

  /**
    * The range with which we bind the mass of the star between was chosen because as noted in "3. Characteristics Of The Primary Star" in "Extra-solar
    * Planetary Systems: A Microcomputer Simulation". The core of the algorithm was designed based on our star and results become increasingly unreliable with
    * high and low mass values. This particular variable is the lower bound of that range.
    *
    * @note unit is solar mass.
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
    * @see method GenStar, line 164 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 211 in genstar.c - Keris (accretion v1)
    * @see method GenStar, lines 288 in genstar.cc - Keris (accretion v2)
    * @see method generate_stellar_system, line 81 in enviro.c - Keris (starform)
    * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
    * @see constructor StarSystem, line 50 in StarSystem.java - Carl Burke (starform)
    */
  def LOWER_SOLAR_MASS: Double = 0.6

  /**
    * The range with which we bind the mass of the star between was chosen because as noted in "3. Characteristics Of The Primary Star" in "Extra-solar
    * Planetary Systems: A Microcomputer Simulation". The core of the algorithm was designed based on our star and results become increasingly unreliable with
    * high and low mass values. This particular variable is the upper bound of that range.
    *
    * @note unit is solar mass.
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
    * @see method GenStar, line 164 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 211 in genstar.c - Keris (accretion v1)
    * @see method GenStar, lines 288 in genstar.cc - Keris (accretion v2)
    * @see method generate_stellar_system, line 81 in enviro.c - Keris (starform)
    * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
    * @see constructor StarSystem, line 50 in StarSystem.java - Carl Burke (starform)
    */
  def UPPER_SOLAR_MASS: Double = 1.3


  /**
    * Optimistic constant specified by Fogg in "3. Characteristics of The Primary Star" in "Extra-solar Planetary Systems: A Microcomputer Simulation", based
    * on greenhouse models by Michael H. Hart.
    *
    * @see p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see var GREENHOUSE_EFFECT_CONST, line 50 in const.h - Mat Burdick (accrete)
    * @see method GenStar, line 168 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 215 in genstar.c - Keris (accretion v1)
    * @see method GenStar, lines 292 in genstar.cc - Keris (accretion v2)
    * @see var GREENHOUSE_EFFECT_CONST, line 51 in const.h - Keris (starform)
    * @see var GREENHOUSE_EFFECT_CONST, line 48 in const.h - Mat Burdick (starform)
    * @see var GREENHOUSE_EFFECT_CONST, line 97 in PhysicalConstants.java - Carl Burke (starform)
    *
    */
  def GREENHOUSE_EFFECT_CONST: Double = 0.93

  /**
    * Constant for the Kothari Radius as defined in eq 17 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
    *
    * @see eq. 9, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see eq. 17, p. 839, The Internal Constitution of Planets - D. S. Kothari
    * @see var A1_20, line 90 in const.h - Mat Burdick (accrete)
    * @see var A1_20, line 90 in const.h - Keris (starform)
    * @see var A1_20, line 88 in const.h - Mat Burdick (starform)
    * @see var A1_20, line 137 in PhysicalConstants.java - Carl Burke (starform)
    */
  def A1: Double = 6.47E12

  /**
    * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
    *
    * @see eq. 9, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see eq. 19, p. 839, The Internal Constitution of Planets - D. S. Kothari
    * @see var A2_20, line 91 in const.h - Mat Burdick (accrete)
    * @see var A2_20, line 91 in const.h - Keris (starform)
    * @see var A2_20, line 89 in const.h - Mat Burdick (starform)
    * @see var A2_20, line 138 in PhysicalConstants.java - Carl Burke (starform)
    */
  def A2: Double = 4.00E-8

  /**
    * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S.
    * Kothari.
    *
    * @see The Internal Constitution of Planets - D. S. Kothari
    * @see line 92 in const.h - Mat Burdick (accrete)
    * @see line 90 in const.h - Mat Burdick (starform)
    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
    */
  def BETA: Double = 5.71E12

  /**
    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
    * condensation.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method day_length, line 207 in const.h - Mat Burdick (accrete)
    * @see method day_length, line 207 in const.h - Mat Burdick (starform)
    * @see method day_length, line 532 in PhysicalConstants.java - Carl Burke (starform)
    */
  def K2_GIANT: Double = 0.24

  /**
    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
    * condensation.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method day_length, line 209 in const.h - Mat Burdick (accrete)
    * @see method day_length, line 209 in const.h  - Mat Burdick (starform)
    * @see method day_length, line 534 in PhysicalConstants.java - Carl Burke (starform)
    */
  def K2_TERRESTRIAL: Double = 0.33

  /**
    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see line 92 in const.h - Mat Burdick (accrete)
    * @see line 90 in const.h - Mat Burdick (starform)
    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
    */
  def J: Double = 1.46E-19

  /**
    * Purported value for the change in earth's angular velocity as defined in eq 12 in Fogg's article.
    *
    * TODO investigate if this is being sued correctly in our recreation.
    *
    * @note unit is radians/sec/ byr
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see line 92 in const.h - Mat Burdick (accrete)
    * @see line 90 in const.h - Mat Burdick (starform)
    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
    */
  def CHANGE_IN_EARTH_ANG_VEL: Double = -1.3E-15

  /**
    * The minimum ratio of escape velocity to molecule root mean square speed require for the plane to successfully
    * retain an atmosphere according to Fogg in "5.3 Atmosphere and Climate".
    *
    * @note unitless.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see line 34 in const.h - Mat Burdick (accrete)
    * @see line 32 in const.h - Mat Burdick (starform)
    * @see line 81 in PhysicalConstants.java - Carl Burke (starform)
    */
  def GAS_RETENTION_THRESHOLD: Double = 5.0 /* ratio of esc vel to RMS vel */


  def CONVECTION_FACTOR: Double = 0.43

  def GAS_GIANT_ALBEDO: Double = 0.5

  def AIRLESS_ROCKY_ALBEDO: Double = 0.07

  def AIRLESS_ICE_ALBEDO: Double = 0.7

  def EARTH_ALBEDO: Double = 0.3

  def ATMOSPHERE_II_V_ALBEDO = 0.7

  def ATMOSPHERE_III_ALBEDO = 0.2

  def ATMOSPHERE_VII_ALBEDO = AIRLESS_ICE_ALBEDO

  def CLOUD_ALBEDO: Double = 0.52

  def ROCK_ALBEDO: Double = 0.15

  def OCEAN_ALBEDO: Double = 0.04

  def ICE_ALBEDO: Double = 0.7

  def Q1 = 1.258E19

  def Q2 = 0.0698

}
