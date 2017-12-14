// scalastyle:off method.name
package com.szadowsz.starform2.model.star.consts

/**
  * Created on 15/04/2017.
  */
class FoggStarConstants extends StarConstants {

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

}
