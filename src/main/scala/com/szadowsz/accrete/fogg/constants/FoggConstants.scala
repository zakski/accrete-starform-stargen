package com.szadowsz.accrete.fogg.constants

import com.szadowsz.accrete.base.constants.AccreteConstants

/**
 * @author Zakski : 26/06/2015.
 */
trait FoggConstants extends AccreteConstants {

  /**
   * The range which we bind the mass of the star between was chosen because as noted in "2. The Microcomputer Model"
   * in Extra-solar Planetary Systems: A Microcomputer Simulation, core of the algorithm was designed based on our
   * star and results become increasingly unreliable with high and low mass values. This particular variable is the
   * lower bound of that range.
   *
   * @note unit is solar mass.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   */
  def LOWER_SOLAR_MASS: Double = 0.6

  /**
   * The range which we bind the mass of the star between was chosen because as noted in "2. The Microcomputer Model"
   * in Extra-solar Planetary Systems: A Microcomputer Simulation, core of the algorithm was designed based on our
   * star and results become increasingly unreliable with high and low mass values. This particular variable is the
   * upper bound of that range.
   *
   * @note unit is solar mass.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   */
  def UPPER_SOLAR_MASS: Double = 1.3

  /**
   * Optimistic constant specified by Fogg in "3. Characteristics of The Primary Star" in Extra-solar Planetary
   * Systems: A Microcomputer Simulation, based on greenhouse models by Michael H. Hart.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   */
  def GREENHOUSE_EFFECT_CONST: Double = 0.93


  /**
   * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S.
   * Kothari.
   *
   * @see The Internal Constitution of Planets - D. S. Kothari
   * @see line 90 in const.h - Mat Burdick (accrete)
   * @see line 88 in const.h - Mat Burdick (starform)
   * @see line 137 in PhysicalConstants.java - Carl Burke (starform)
   */
  def A1 = 6.47E12

  /**
   * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S.
   * Kothari.
   *
   * @see The Internal Constitution of Planets - D. S. Kothari
   * @see line 91 in const.h - Mat Burdick (accrete)
   * @see line 89 in const.h - Mat Burdick (starform)
   * @see line 138 in PhysicalConstants.java - Carl Burke (starform)
   */
  def A2 = 4.00E-8

  /**
   * Constant for the Kothari Radius as defined in eq 12 in "The Internal Constitution of Planets", by Dr. D. S.
   * Kothari.
   *
   * @see The Internal Constitution of Planets - D. S. Kothari
   * @see line 92 in const.h - Mat Burdick (accrete)
   * @see line 90 in const.h - Mat Burdick (starform)
   * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
   */
  def BETA = 5.71E12

  /**
   * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
   * condensation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method day_length, line 207 in const.h - Mat Burdick (accrete)
   * @see method day_length, line 207 in const.h - Mat Burdick (starform)
   * @see method day_length, line 532 in PhysicalConstants.java - Carl Burke (starform)
   */
  def K2_GIANT = 0.24

  /**
   * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article. Related to central
   * condensation.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see method day_length, line 209 in const.h - Mat Burdick (accrete)
   * @see method day_length, line 209 in const.h  - Mat Burdick (starform)
   * @see method day_length, line 534 in PhysicalConstants.java - Carl Burke (starform)
   */
  def K2_TERRESTRIAL = 0.33

  /**
   * Constant for the calculating Angular Velocity as defined in eq 12 in Fogg's article.
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see line 92 in const.h - Mat Burdick (accrete)
   * @see line 90 in const.h - Mat Burdick (starform)
   * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
   */
  def J = 1.46E-19

  /**
   * Purported value for the change in earth's angular velocity as defined in eq 12 in Fogg's article.
   *
   * @todo investigate if this is being sued correctly in our recreation.
   *
   * @note unit is radians/sec/ byr
   *
   * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   * @see line 92 in const.h - Mat Burdick (accrete)
   * @see line 90 in const.h - Mat Burdick (starform)
   * @see line 139 in PhysicalConstants.java - Carl Burke (starform)
   */
  def CHANGE_IN_EARTH_ANG_VEL = -1.3E-15

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   *
   */
  def getStarLuminosity: Double

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   */
  def getStarMass: Double

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   */
  def getStarAge: Double

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   */
  def getStarEcosphereRadius: Double

}
