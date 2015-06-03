package com.szadowsz.starform.constants

/**
 * Constants File made up of values taken from all versions of the program. Most have been updated where more 
 * accurate values exist. This particular file contains all information specifically to do with Earth.
 *
 * @author Zakski : 31/05/2015.
 */
trait EarthConstants extends UnitConstants {

  /**
   * Number of metres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
   *
   * @note unit is metres.
   *
   */
  final val M_PER_AU: Double = KM_PER_AU * METRES_PER_KM
  /**
   * Number of metres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
   *
   * @note unit is centimetres.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  final val CM_PER_AU: Double = M_PER_AU * CM_PER_METRE
  /**
   * Earth Mass in g. Original value used by Carl, Mat and Ian is 5.977E27. A more up-to-date  and (hopefully)
   * accurate value is 5.9722E27 taken from the Nasa space facts website and converted from kilograms to grams.
   *
   * @note unit is grams.
   * @note Earth mass (M?, where ? is the symbol for planet Earth) is the unit of mass equal to that of Earth in kg.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val EARTH_MASS_IN_GRAMS: Double = 5.9722E27
  /**
   * Earth Radius in km. Represents mean radius. Distances from points on the surface
   * to the center range from 6,353 km to 6,384 km (3,947–3,968 mi). Original value used by
   * Carl, Mat and Ian is 6378.0 km. A more up-to-date  and (hopefully) accurate value is
   * 6371 km taken from the Nasa space facts website and converted from kilometers to centimetres.
   *
   * @note unit is kilometres.
   * @note Earth radius (R?, where ? is the symbol for planet Earth) is the unit of distance equal to that of Earth in km.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val KM_EARTH_RADIUS: Double = 6371.0
  /**
   * Earth Radius in cm. Represents mean radius. Distances from points on the surface
   * to the center range from 6,353 km to 6,384 km (3,947–3,968 mi). Original value used by
   * Carl and Mat is 6.378E8, whereas Ian incorrectly uses 6.378E6. A more up-to-date  and (hopefully)
   * accurate value is 6.371E8 taken from the Nasa space facts website and converted from kilometers to centimetres.
   *
   * @note unit is centimetres.
   * @note Earth radius (R?, where ? is the symbol for planet Earth) is the unit of distance equal to that of Earth in km.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val EARTH_RADIUS: Double = KM_EARTH_RADIUS * CM_PER_KM
  /**
   * Earth Density in g/cm3. The average density of the earth. Original value used by Carl, Ian and Mat is 5.52. A
   * more up-to-date  and (hopefully) accurate value is 5.513 taken from the Nasa space facts website.
   *
   * @note unit is grams per centimeter cubed.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val EARTH_DENSITY: Double = 5.513
  /**
   * Earth Gravity in cm/sec2. Represents the nominal gravitational acceleration of an object in a vacuum
   * near the surface of the Earth. Referred to as the standard acceleration due to gravity. Original value used by
   * Carl and Mat is 981.0. A more up-to-date  and (hopefully) accurate value is 980.665 taken from the Nasa
   * space facts website and converted from kilometers to centimetres.
   *
   * @note unit is centimetres per second squared.
   * @note Standard Gravity (usually denoted by ?0 or ?n) is usually measured in m/sec2. 9.80665 m/sec2.
   *
   * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
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
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val EARTH_AXIAL_TILT: Double = 23.4393
  /**
   * Earth's Exosphere temperature. Temperature in kelvin.
   *
   * @note unit is degrees kelvin.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val EARTH_EXOSPHERE_TEMP: Double = 1273.0
  /**
   * Earth's Effective temperature. Temperature in kelvin.
   *
   * @note unit is degrees kelvin.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val EARTH_EFFECTIVE_TEMP: Double = 255.0
  /**
   * Earth's Albedo. It represents the ratio of reflected radiation from the surface to incident radiation upon it. The
   * Albedo is expressed as a percentage and is measured on a scale from zero for no reflection of a perfectly black
   * surface to 1 for perfect reflection of a white surface.
   *
   * @note scale of 0.0 to 1.0.
   *
   */
  val EARTH_ALBEDO: Double = 0.3
  /**
   * The Cloud Coverage Factor is the amount of surface area on Earth covered by one Kg. of cloud. Assumed to be
   * defined on pg.46 of "Introduction to Planetary Geology" by Billy P.Glass which is now sadly out of print with
   * no digital copy extant.
   *
   * @note unit is Km2/kg.
   *
   * @see cloud_fraction method in envio.c in Mat Burdick's source code.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val CLOUD_COVERAGE_FACTOR: Double = 1.839E-8
  /**
   * Mass of Water on Earth for each km2 of area of the Planet. Assumed to be defined on pg.46 of "Introduction to
   * Planetary Geology" by Billy P.Glass which is now sadly out-of-print with no digital copy extant.
   *
   * @note unit is grams/km2.
   *
   * @see cloud_fraction method in envio.c in Mat Burdick's source code.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val EARTH_WATER_MASS_PER_AREA: Double = 3.83E15
  /**
   * Atmospheric air pressure is often given in millibars where standard sea level pressure is defined as 1000 mbar
   * or 1 bar. This should be distinguished from the now deprecated unit of pressure, known as the "atmosphere" (atm),
   * which is equal to 1.01325 bar. hectopascal is the numerically SI equivalent.
   *
   * @note unit is millibar.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  val EARTH_SURF_PRES_IN_MILLIBARS: Double = 1000.0
  /**
   * Used to represent Heat Transfer by Convection on Earth during Greenhouse calculations. Value is taken from
   * "The Evolution of the Atmosphere of the Earth" by Michael H. Hart, Icarus, Vol 33, pp. 23 - 39, 1978.
   *
   * @note I am assuming a scale of 0.0 to 1.0.
   *
   * @see equation 20 in "The Evolution of the Atmosphere of the Earth - Michael H. Hart.pdf"
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
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
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val DAYS_IN_A_YEAR: Double = 365.26
  /**
   * Number of kilometres in a Astronomical Unit. An AU is the distance between the Earth and the Sun.
   *
   * @note unit is kilometres.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  val KM_PER_AU: Double = 1.495978707E8

}