package com.szadowsz.accrete.base.constants.unit

/**
 * @author Zakski : 08/07/2015.
 */
private[constants] trait DistanceConstants {

  /**
   * Number of centimetres in a metre.
   *
   * @note unit is centimetres.
   *
   * @see line 46 in const.h - Mat Burdick (accrete)
   * @see line 44 in const.h - Mat Burdick (starform)
   * @see line 93 in  PhysicalConstants.java - Carl Burke (starform)
   */
  final val CM_PER_METER: Double = 100.0

  /**
   * Number of centimetres in a metre.
   *
   * @note unit is metres.
   */
  final val METERS_PER_KM: Double = 1000.0

  /**
   * Number of centimetres in a kilometre.
   *
   * @note unit is centimetres.
   *
   * @see line 44 in const.h - Mat Burdick (accrete)
   * @see line 42 in const.h - Mat Burdick (starform)
   * @see line 91 in  PhysicalConstants.java - Carl Burke (starform)
   */
  final val CM_PER_KM: Double = CM_PER_METER * METERS_PER_KM
  /**
   * Number of metres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
   *
   *
   * @note unit is centimetres.
   *
   * @see http://neo.jpl.nasa.gov/glossary/au.html
   * @see line 22 in Astro.java - Ian Burrell (accrete)
   * @see line 43 in const.h - Mat Burdick (accrete)
   * @see line 41 in const.h - Mat Burdick (starform)
   * @see line 90 in  PhysicalConstants.java - Carl Burke (starform)
   */
  final val CM_PER_AU: Double = KM_PER_AU * CM_PER_KM
  /**
   * Number of kilometres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
   *
   *
   * @note unit is kilometres.
   *
   * @see http://neo.jpl.nasa.gov/glossary/au.html
   * @see line 23 in Astro.java - Ian Burrell (accrete)
   * @see line 45 in const.h - Mat Burdick (accrete)
   * @see line 43 in const.h - Mat Burdick (starform)
   * @see line 92 in  PhysicalConstants.java - Carl Burke (starform)
   */
  val KM_PER_AU: Double = 1.495978707E8
  /**
   * Earth Radius in km. Represents mean radius. Distance from points on the surface
   * to the center range from 6,353 km to 6,384 km (3,947–3,968 mi). Original value used by
   * Carl, Mat and Ian is 6378.0 km. A more up-to-date  and (hopefully) accurate value is
   * 6371 km taken from the Nasa space facts website and converted from kilometers to centimetres.
   *
   * @note unit is kilometres.
   * @note Earth radius is the unit of distance equal to that of Earth in km.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 18 in Astro.java - Ian Burrell (accrete)
   * @see line 20 in const.h - Mat Burdick (accrete)
   * @see line 18 in const.h - Mat Burdick (starform)
   * @see line 68 in  PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_RADIUS_IN_KM: Double = 6371.0

  /**
   * Earth Radius in cm. Represents mean radius. Distances from points on the surface
   * to the center range from 6,353 km to 6,384 km (3,947–3,968 mi). Original value used by
   * Carl and Mat is 6.378E8, whereas Ian incorrectly uses 6.378E6. A more up-to-date  and (hopefully)
   * accurate value is 6.371E8 taken from the Nasa space facts website and converted from kilometers to centimetres.
   *
   * @note unit is centimetres.
   * @note Earth radius is the unit of distance equal to that of Earth in km.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 17 in Astro.java - Ian Burrell (accrete)
   * @see line 18 in const.h - Mat Burdick (accrete)
   * @see line 16 in const.h - Mat Burdick (starform)
   * @see line 66 in  PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_RADIUS_IN_CM: Double = EARTH_RADIUS_IN_KM * CM_PER_KM

}
