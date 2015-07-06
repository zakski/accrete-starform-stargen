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


}
