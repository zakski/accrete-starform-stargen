package com.szadowsz.starform.constants.unit

/**
  * Separation of Distance Unit Constants from General Program Constants.
  *
  * @author Zakski : 08/07/2015.
  */
trait DistanceConstants {

  /**
    * Number of centimetres in a metre.
    *
    * @note unit is centimetres (cm).
    * @note represents 1 metre (m).
    *
    * @see line 46 in const.h - Mat Burdick (accrete)
    * @see line 44 in const.h - Mat Burdick (starform)
    * @see line 93 in  PhysicalConstants.java - Carl Burke (starform)
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
    *
    * @see line 44 in const.h - Mat Burdick (accrete)
    * @see line 42 in const.h - Mat Burdick (starform)
    * @see line 91 in  PhysicalConstants.java - Carl Burke (starform)
    */
  final val CM_PER_KM: Double = CM_PER_METER * METERS_PER_KM

  /**
    * Earth Radius in km. Represents mean earth radius. Distances from points on the surface to the center range from 6,353 km to 6,384 km (3,947–3,968 mi).
    * This length is also used as a unit of distance, especially in astronomy and geology.
    *
    * Original value used by Carl and Mat is 6.378E8. A more up-to-date and (hopefully) accurate value is 6.371E8 taken from the Nasa space facts website and
    * converted from kilometers to centimetres.
    *
    * @note unit is kilometres.
    * @note Earth radius is the unit of distance equal to that of Earth in km.
    *
    * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
    * @see var EARTH_RADIUS_IN_KM, line 20 in const.h - Mat Burdick (accrete)
    * @see var KM_EARTH_RADIUS, line 21 in const.h - Keris (starform)
    * @see var KM_EARTH_RADIUS, line 18 in const.h - Mat Burdick (starform)
    * @see var KM_EARTH_RADIUS, line 68 in  PhysicalConstants.java - Carl Burke (starform)
    */
  final val EARTH_RADIUS_IN_KM: Double = 6371.0

    /**
     * Earth Radius in cm. Represents mean radius. Distances from points on the surface to the center range from
     * 6,353 km to 6,384 km (3,947–3,968 mi). This length is also used as a unit of distance, especially in
     * astronomy and geology.
     *
     * Original value used by Carl and Mat is 6.378E8, whereas Ian incorrectly uses 6.378E6. A more up-to-date and
     * (hopefully) accurate value is 6.371E8 taken from the Nasa space facts website and converted from kilometers
     * to centimetres.
     *
     * @note unit is centimetres.
     * @note Earth radius is the unit of distance equal to that of Earth in km.
     *
      * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
      * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
      * @see var EARTH_RADIUS, line 18 in const.h - Mat Burdick (accrete)
      * @see var EARTH_RADIUS, line 19 in const.h - Keris (starform)
      * @see var EARTH_RADIUS, line 16 in const.h - Mat Burdick (starform)
      * @see var EARTH_RADIUS, line 66 in  PhysicalConstants.java - Carl Burke (starform)
      */
    final val EARTH_RADIUS_IN_CM: Double = EARTH_RADIUS_IN_KM * CM_PER_KM

  //
  //  /**
  //   * Number of kilometres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
  //   *
  //   *
  //   * @note unit is kilometres (km).
  //   * @note represents 1 Astronomical Unit (AU).
  //   *
  //   * @see http://neo.jpl.nasa.gov/glossary/au.html
  //   * @see line 23 in Astro.java - Ian Burrell (accrete)
  //   * @see line 45 in const.h - Mat Burdick (accrete)
  //   * @see line 43 in const.h - Mat Burdick (starform)
  //   * @see line 92 in  PhysicalConstants.java - Carl Burke (starform)
  //   */
  //  final val KM_PER_AU: Double = 1.495978707E8
  //
  //  /**
  //   * Number of metres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
  //   *
  //   *
  //   * @note unit is centimetres (cm).
  //   * @note represents 1 Astronomical Unit (AU).
  //   *
  //   * @see http://neo.jpl.nasa.gov/glossary/au.html
  //   * @see line 22 in Astro.java - Ian Burrell (accrete)
  //   * @see line 43 in const.h - Mat Burdick (accrete)
  //   * @see line 41 in const.h - Mat Burdick (starform)
  //   * @see line 90 in  PhysicalConstants.java - Carl Burke (starform)
  //   */
  //  final val CM_PER_AU: Double = KM_PER_AU * CM_PER_KM
  //
  //
}
