//// scalastyle:off method.name
//package com.szadowsz.starform.model.eco.constants
//
///**
//  * Created on 13/04/2017.
//  */
//trait EcoConstants {
//  /**
//    * Constant for the Kothari Radius as defined in eq 17 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
//    *
//    * @see eq. 9, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see eq. 17, p. 839, The Internal Constitution of Planets - D. S. Kothari
//    * @see var A1_20, line 90 in const.h - Mat Burdick (accrete)
//    * @see var A1_20, line 90 in const.h - Keris (starform)
//    * @see var A1_20, line 88 in const.h - Mat Burdick (starform)
//    * @see var A1_20, line 137 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def A1: Double = 6.47E12
//
//  /**
//    * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
//    *
//    * @see eq. 9, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see eq. 19, p. 839, The Internal Constitution of Planets - D. S. Kothari
//    * @see var A2_20, line 91 in const.h - Mat Burdick (accrete)
//    * @see var A2_20, line 91 in const.h - Keris (starform)
//    * @see var A2_20, line 89 in const.h - Mat Burdick (starform)
//    * @see var A2_20, line 138 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def A2: Double = 4.00E-8
//
//  /**
//    * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S.
//    * Kothari.
//    *
//    * @see The Internal Constitution of Planets - D. S. Kothari
//    * @see line 92 in const.h - Mat Burdick (accrete)
//    * @see line 90 in const.h - Mat Burdick (starform)
//    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def BETA: Double = 5.71E12
//
//  /**
//    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
//    * condensation.
//    *
//    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see method day_length, line 207 in const.h - Mat Burdick (accrete)
//    * @see method day_length, line 207 in const.h - Mat Burdick (starform)
//    * @see method day_length, line 532 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def K2_GIANT: Double = 0.24
//
//  /**
//    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
//    * condensation.
//    *
//    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see method day_length, line 209 in const.h - Mat Burdick (accrete)
//    * @see method day_length, line 209 in const.h  - Mat Burdick (starform)
//    * @see method day_length, line 534 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def K2_TERRESTRIAL: Double = 0.33
//
//  /**
//    * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article.
//    *
//    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see line 92 in const.h - Mat Burdick (accrete)
//    * @see line 90 in const.h - Mat Burdick (starform)
//    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def J: Double = 1.46E-19
//
//  /**
//    * Purported value for the change in earth's angular velocity as defined in eq 12 in Fogg's article.
//    *
//    * TODO investigate if this is being sued correctly in our recreation.
//    *
//    * @note unit is radians/sec/ byr
//    *
//    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see line 92 in const.h - Mat Burdick (accrete)
//    * @see line 90 in const.h - Mat Burdick (starform)
//    * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def CHANGE_IN_EARTH_ANG_VEL: Double = -1.3E-15
//
//  /**
//    * The minimum ratio of escape velocity to molecule root mean square speed require for the plane to successfully
//    * retain an atmosphere according to Fogg in "5.3 Atmosphere and Climate".
//    *
//    * @note unitless.
//    *
//    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
//    * @see line 34 in const.h - Mat Burdick (accrete)
//    * @see line 32 in const.h - Mat Burdick (starform)
//    * @see line 81 in PhysicalConstants.java - Carl Burke (starform)
//    */
//  def GAS_RETENTION_THRESHOLD: Double = 5.0 /* ratio of esc vel to RMS vel */
//
//
//  def EARTH_AXIAL_TILT : Double = 23.4
//
//  def CONVECTION_FACTOR: Double = 0.43
//
//  def GAS_GIANT_ALBEDO: Double = 0.5
//
//  def AIRLESS_ROCKY_ALBEDO: Double = 0.07
//
//  def AIRLESS_ICE_ALBEDO: Double = 0.7
//
//  def EARTH_ALBEDO: Double = 0.3
//
//  def ATMOSPHERE_II_V_ALBEDO = 0.7
//
//  def ATMOSPHERE_III_ALBEDO = 0.2
//
//  def ATMOSPHERE_VII_ALBEDO = AIRLESS_ICE_ALBEDO
//
//  def CLOUD_ALBEDO: Double = 0.52
//
//  def ROCK_ALBEDO: Double = 0.15
//
//  def OCEAN_ALBEDO: Double = 0.04
//
//  def ICE_ALBEDO: Double = 0.7
//
//  def Q1 = 1.258E19
//
//  def Q2 = 0.0698
//
//}
