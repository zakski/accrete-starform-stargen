package com.szadowsz.accrete.base.constants.unit

/**
 * Constants File inherits the fully fledged unit categories and declares constants that don't quite fit into them.
 *
 * @author Zakski : 31/05/2015.
 */
trait UnitConstants extends DistanceConstants with MassConstants {

  /**
   * Earth Density in g/cm3. The average density of the earth. Original value used by Carl, Ian and Mat is 5.52. A
   * more up-to-date  and (hopefully) accurate value is 5.513 taken from the Nasa space facts website. Used to express
   * planetary density in terms of earth when trying to determine angular velocity deceleration due to the planet's
   * star.
   *
   * @note unit is g / cm^3^.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 19 in const.h - Mat Burdick (accrete)
   * @see line 17 in const.h - Mat Burdick (starform)
   * @see line 67 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val EARTH_DENSITY: Double = 5.513

  /**
   * Number of Radians in a Circle. Used in calculating rotation length in hours.
   *
   * @note unit is sec.
   *
   * @see line 42 in const.h - Mat Burdick (accrete)
   * @see line 40 in const.h - Mat Burdick (starform)
   * @see line 89 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val TWO_PI: Double = Math.PI * 2.0

  /**
   * Number of Seconds in an hour. Used in calculating rotation length in hours.
   *
   * @note unit is sec.
   *
   * @see line 42 in const.h - Mat Burdick (accrete)
   * @see line 40 in const.h - Mat Burdick (starform)
   * @see line 89 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val SECONDS_PER_HOUR: Double = 3600.0

  /**
   * Number of Seconds in an hour. Used in calculating rotation length in hours.
   *
   * @note unit is sec.
   *
   * @see line 42 in const.h - Mat Burdick (accrete)
   * @see line 40 in const.h - Mat Burdick (starform)
   * @see line 89 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val DAYS_IN_A_YEAR: Double = 365.25
}
