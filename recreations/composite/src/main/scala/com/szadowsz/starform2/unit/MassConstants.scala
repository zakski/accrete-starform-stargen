package com.szadowsz.starform2.unit

/**
  * Separation of Mass Unit Constants from General Program Constants.
  *
  * These values should not be alterable.
  *
  * These values come from the following files of the original programs unless otherwise noted:
  * const.h - Burdick (accrete)
  * const.h - Burdick (starform)
  * const.h - Keris (starform)
  * const.h - Webb (starform)
  * PhysicalConstants.java - Burke (starform)
  * Astro.java - Burrell (accrete)
  *
  * Folkins and Gilham do not have a separation between constants and calculation, therefore you will find their declarations in the same place as the
  * functions that use them.
  *
  * @author Zakski : 08/07/2015.
  */
trait MassConstants {

  /**
    * Number of grams in a kilogram. Unit of Mass.
    *
    * @note unit is grams.
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
    final val SOLAR_MASS_IN_KG: Double = 1.98985E30 //16012.865955436559


    /**
     * Sun Mass in Earth Mass.
     *
     * @note unit is Earth Mass.
     * @note Solar mass is the unit of mass equal to that of Sun in kg.
     * @note Earth mass is the unit of mass equal to that of Earth in kg.
     *
     * @see http://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html
     * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
     */
    final val SOLAR_MASS_IN_EARTH_MASS: Double = SOLAR_MASS_IN_KG / EARTH_MASS_IN_KG

    /**
     * Sun Mass in grams.
     *
     * @note unit is grams.
     * @note Solar mass is the unit of mass equal to that of Sun in kg.
     *
     * @see http://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html
     */
    final val SOLAR_MASS_IN_GRAMS: Double = SOLAR_MASS_IN_KG * GRAMS_PER_KG
 }
