package com.szadowsz.starform2.unit

/**
  * Separation of Distance Unit Constants from General Program Constants.
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
trait DistanceConstants {

  /**
    * Number of centimetres in a metre.
    *
    * @note unit is centimetres (cm).
    * @note represents 1 metre (m).
    */
  final val CM_PER_METER: Double = 100.0

  /**
    * Number of centimetres in a metre.
    *
    * @note unit is metres (m).
    * @note represents 1 kilometre (km).
    */
  final val METERS_PER_KM: Double = 1000.0

  /**
    * Number of centimetres in a kilometre.
    *
    * @note unit is centimetres (cm).
    * @note represents 1 kilometre (km).
    */
  final val CM_PER_KM: Double = CM_PER_METER * METERS_PER_KM

  /**
    * Earth Radius in km. Represents mean earth radius. Distances from points on the surface to the center range from 6,353 km to 6,384 km (3,947–3,968 mi).
    * This length is also used as a unit of distance, especially in astronomy and geology.
    *
    * Original value used by Mat is 6.378E8. A more up-to-date and (hopefully) accurate value is 6.371E8 taken from the Nasa space facts website and
    * converted from kilometers to centimetres.
    *
    * @note unit is kilometres.
    * @note Earth radius is the unit of distance equal to that of Earth in km.
    *
    * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
    */
  final val EARTH_RADIUS_IN_KM: Double = 6371.0

    /**
     * Earth Radius in cm. Represents mean radius. Distances from points on the surface to the center range from
     * 6,353 km to 6,384 km (3,947–3,968 mi). This length is also used as a unit of distance, especially in
     * astronomy and geology.
     *
     * Original value used by Mat is 6.378E8, whereas Ian incorrectly uses 6.378E6. A more up-to-date and
     * (hopefully) accurate value is 6.371E8 taken from the Nasa space facts website and converted from kilometers
     * to centimetres.
     *
     * @note unit is centimetres.
     * @note Earth radius is the unit of distance equal to that of Earth in km.
     *
      * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
      * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
      */
    final val EARTH_RADIUS_IN_CM: Double = EARTH_RADIUS_IN_KM * CM_PER_KM
}
