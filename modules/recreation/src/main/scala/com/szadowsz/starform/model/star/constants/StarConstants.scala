// scalastyle:off method.name
package com.szadowsz.starform.model.star.constants

import com.szadowsz.starform.system.bodies.base.Star

/**
  * Star Generation Constants Specific to Martyn J. Fogg's adaptation of Dole's paper.
  *
  * @author Zakski : 26/06/2015.
  */
trait StarConstants {

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
}
