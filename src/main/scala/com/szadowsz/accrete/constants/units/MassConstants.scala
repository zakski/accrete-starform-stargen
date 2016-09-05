package com.szadowsz.accrete.constants.units

/**
 * Separation of Mass Unit Constants from General Program Constants.
 *
 * @author Zakski : 08/07/2015.
 */
protected[constants] trait MassConstants {

  /**
   * Number of grams in a kilogram. Unit of Mass.
   *
   * @note unit is grams.
   *
   * @see line 17 in Astro.java - Ian Burrell (accrete)
   * @see line 18 in const.h - Mat Burdick (accrete)
   * @see line 16 in const.h - Mat Burdick (starform)
   * @see line 66 in  PhysicalConstants.java - Carl Burke (starform)
   */
  final val GRAMS_PER_KG: Double = 1000.0

  /**
   * Earth Mass in kg. Original value used by Carl, Mat and Ian is 5.977E24. A more up-to-date  and (hopefully)
   * accurate value is 5.9722E24 taken from the Nasa space facts website and converted from kilograms to grams.
   *
   * @note unit is kilograms.
   * @note Earth mass is the unit of mass equal to that of Earth in kg.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   */
  final val EARTH_MASS_IN_KG: Double = 5.9722E24

  /**
   * Earth Mass in g. Original value used by Carl, Mat and Ian is 5.977E27. A more up-to-date  and (hopefully)
   * accurate value is 5.9722E27 taken from the Nasa space facts website and converted from kilograms to grams.
   *
   * @note unit is grams.
   * @note Earth mass is the unit of mass equal to that of Earth in kg.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 14 in Astro.java - Ian Burrell (accrete)
   * @see line 17 in const.h - Mat Burdick (accrete)
   * @see line 15 in const.h - Mat Burdick (starform)
   * @see line 65 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val EARTH_MASS_IN_GRAMS: Double = EARTH_MASS_IN_KG * GRAMS_PER_KG

  /**
   * Sun Mass in kg.
   *
   * @note unit is kilograms.
   * @note Solar mass is the unit of mass equal to that of Sun in kg.
   *
   * @see http://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html
   *
   */
  final val SOLAR_MASS_IN_KG: Double = 1.9885E30

  /**
   * Sun Mass in grams.
   *
   * @note unit is grams.
   * @note Solar mass is the unit of mass equal to that of Sun in kg.
   *
   * @see http://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html
   * @see line 13 in Astro.java - Ian Burrell (accrete)
   * @see line 16 in const.h - Mat Burdick (accrete)
   * @see line 14 in const.h - Mat Burdick (starform)
   * @see line 64 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val SOLAR_MASS_IN_GRAMS: Double = SOLAR_MASS_IN_GRAMS * GRAMS_PER_KG

  /**
   * Sun Mass in Earth Mass.
   *
   * @note unit is Earth Mass.
   * @note Solar mass is the unit of mass equal to that of Sun in kg.
   * @note Earth mass is the unit of mass equal to that of Earth in kg.
   *
   * @see http://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 15 in Astro.java - Ian Burrell (accrete)
   * @see line 24 in const.h - Mat Burdick (accrete)
   * @see line 22 in const.h - Mat Burdick (starform)
   * @see line 72 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val SOLAR_MASS_IN_EARTH_MASS: Double = SOLAR_MASS_IN_KG / EARTH_MASS_IN_KG
}
