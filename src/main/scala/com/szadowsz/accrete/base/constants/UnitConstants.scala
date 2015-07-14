package com.szadowsz.accrete.base.constants

import com.szadowsz.accrete.base.constants.unit.{DistanceConstants, MassConstants}

/**
 * Constants File made up of values taken from all versions of the program that do not specifically reference variables
 * of the program. Most have been updated where more accurate values exist. Unlike the more subjective variables of
 * tied to the accretion process, I do not see the need to separate them by version. Additionally they are vals rather
 * than defs as I do not imagine them changing during the course of a program.
 *
 * @author Zakski : 31/05/2015.
 */
trait UnitConstants extends DistanceConstants with MassConstants {

  /**
   * Number of millibars in a bar. Unit of pressure. Used to measure atmospheric pressure.
   *
   * @note don't confuse with standard atmosphere (atm) which has the value of 1013.25 millibars.
   * @note unit is millibars.
   *
   * @see line 47 in const.h - Mat Burdick (accrete)
   * @see line 45 in const.h - Mat Burdick (starform)
   * @see line 94 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val MILLIBARS_PER_BAR: Double = 1000.0
  /**
   * The freezing point of water in degrees kelvin. Original value used by Mat and Carl was 273.0 which is
   * incorrect.
   *
   * @note unit is degrees kelvin.
   *
   * @see line 31 in const.h - Mat Burdick (accrete)
   * @see line 29 in const.h - Mat Burdick (starform)
   * @see line 79 in PhysicalConstants.java - Carl Burke (starform)
   */
  final val FREEZING_POINT_OF_WATER: Double = 273.15
  /**
   * Atmospheric air pressure is often given in millibars where standard sea level pressure is defined as 1000 mbar
   * or 1 bar. This should be distinguished from the now deprecated unit of pressure, known as the "atmosphere" (atm),
   * which is equal to 1.01325 bar. hectopascal is the numerically SI equivalent.
   *
   * @note unit is millibar.
   *
   * @see line 29 in const.h - Mat Burdick (accrete)
   * @see line 27 in const.h - Mat Burdick (starform)
   * @see line 77 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_SURF_PRES_IN_MILLIBARS: Double = 1000.0
  /**
   * Earth Density in g/cm3. The average density of the earth. Original value used by Carl, Ian and Mat is 5.52. A
   * more up-to-date  and (hopefully) accurate value is 5.513 taken from the Nasa space facts website.
   *
   * @note unit is grams per centimeter cubed.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 19 in const.h - Mat Burdick (accrete)
   * @see line 17 in const.h - Mat Burdick (starform)
   * @see line 67 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_DENSITY: Double = 5.513
  /**
   * Earth Gravity in cm/sec2. Represents the nominal gravitational acceleration of an object in a vacuum
   * near the surface of the Earth. Referred to as the standard acceleration due to gravity. Original value used by
   * Carl and Mat is 981.0. A more up-to-date  and (hopefully) accurate value is 980.665 taken from the Nasa
   * space facts website and converted from kilometers to centimetres.
   *
   * @note unit is centimetres per second squared.
   * @note Standard Gravity is usually measured in m/sec2. 9.80665 m/sec2.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 21 in const.h - Mat Burdick (accrete)
   * @see line 19 in const.h - Mat Burdick (starform)
   * @see line 69 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_ACCELERATION: Double = 980.665
  /**
   * Earth's Axial Tilt in degrees. Represents the angle between an object's rotational axis and the perpendicular
   * to its Orbital plane, both oriented by the right hand rule. Original value used by Carl and Mat is 23.4. A more
   * up-to-date  and (hopefully) accurate value is 23.4393 taken from the Nasa space facts website and converted
   * from kilometers to centimetres.
   *
   * @note unit is degrees.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @see line 22 in const.h - Mat Burdick (accrete)
   * @see line 20 in const.h - Mat Burdick (starform)
   * @see line 70 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_AXIAL_TILT: Double = 23.4393
  /**
   * Earth's Exosphere temperature. Temperature in kelvin.
   *
   * @note unit is degrees kelvin.
   *
   * @see line 23 in const.h - Mat Burdick (accrete)
   * @see line 21 in const.h - Mat Burdick (starform)
   * @see line 71 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_EXOSPHERE_TEMP: Double = 1273.0


  /**
   * Earth's Effective temperature. Temperature in kelvin.
   *
   * @note unit is degrees kelvin.
   *
   * @see line 25 in const.h - Mat Burdick (accrete)
   * @see line 23 in const.h - Mat Burdick (starform)
   * @see line 73 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_EFFECTIVE_TEMP: Double = 255.0

  /**
   * Earth's Albedo. It represents the ratio of reflected radiation from the surface to incident radiation upon it. The
   * Albedo is expressed as a percentage and is measured on a scale from zero for no reflection of a perfectly black
   * surface to 1 for perfect reflection of a white surface.
   *
   * @note scale of 0.0 to 1.0.

   * @see line 26 in const.h - Mat Burdick (accrete)
   * @see line 24 in const.h - Mat Burdick (starform)
   * @see line 74 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_ALBEDO: Double = 0.3

  /**
   * The Cloud Coverage Factor is the amount of surface area on Earth covered by one Kg. of cloud. Assumed to be
   * defined on pg.46 of "Introduction to Planetary Geology" by Billy P.Glass which is now sadly out of print with
   * no digital copy extant.
   *
   * @note unit is Km2/kg.
   *
   * @see "Introduction to Planetary Geology" by Billy P.Glass
   * @see line 27 in const.h - Mat Burdick (accrete)
   * @see line 25 in const.h - Mat Burdick (starform)
   * @see line 75 in PhysicalConstants.java - Carl Burke (starform)
   */
  val CLOUD_COVERAGE_FACTOR: Double = 1.839E-8

  /**
   * Mass of Water on Earth for each km2 of area of the Planet. Assumed to be defined on pg.46 of "Introduction to
   * Planetary Geology" by Billy P.Glass which is now sadly out-of-print with no digital copy extant.
   *
   * @note unit is grams/km2.
   *
   * @see "Introduction to Planetary Geology" by Billy P.Glass
   * @see line 28 in const.h - Mat Burdick (accrete)
   * @see line 26 in const.h - Mat Burdick (starform)
   * @see line 76 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_WATER_MASS_PER_AREA: Double = 3.83E15

  /**
   * Used to represent Heat Transfer by Convection on Earth during Greenhouse calculations. Value is taken from
   * "The Evolution of the Atmosphere of the Earth" by Michael H. Hart, Icarus, Vol 33, pp. 23 - 39, 1978.
   *
   * @note I am assuming a scale of 0.0 to 1.0.
   *
   * @see equation 20 in "The Evolution of the Atmosphere of the Earth - Michael H. Hart.pdf"
   * @see line 32 in const.h - Mat Burdick (accrete)
   * @see line 30 in const.h - Mat Burdick (starform)
   * @see line 80 in PhysicalConstants.java - Carl Burke (starform)
   */
  val EARTH_CONVECTION_FACTOR: Double = 0.43
  /**
   * Earth's Orbital (sidereal) period in days. Represents the time it takes for the earth to rotate once around the
   * sun. Original value used by Carl, Ian and Mat is 365.256 days. A more up-to-date  and (hopefully) accurate value
   * is 365.26 days taken from the Nasa space facts website and converted from kilometers to centimetres.
   *
   * @note unit is days.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   * @see line 22 in const.h - Mat Burdick (accrete)
   * @see line 20 in const.h - Mat Burdick (starform)
   * @see line 70 in PhysicalConstants.java - Carl Burke (starform)
   */
  val DAYS_IN_A_YEAR: Double = 365.26
}
