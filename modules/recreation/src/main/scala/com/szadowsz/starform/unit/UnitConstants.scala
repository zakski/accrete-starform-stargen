package com.szadowsz.starform.unit

import com.szadowsz.starform.model.eco.calc.EcoCalc

/**
  * Constants File inherits the fully fledged unit categories and declares constants that don't quite fit into them.
  *
  * @author Zakski : 31/05/2015.
  */
trait UnitConstants extends DistanceConstants with MassConstants {

  /**
    * Earth Density in g/cm3. The average density of the earth. Original value used by Carl, Ian and Mat is 5.52. A more up-to-date  and (hopefully) accurate
    * value is 5.513 taken from the Nasa space facts website. Used to express planetary density in terms of earth when trying to determine angular velocity
    * deceleration due to the planet's star.
    *
    * @note see [[EcoCalc.deltaAngularVelocity()]] for more info.
    * @note unit is g / cm^3^.
    *
    * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth&Display=Facts
    * @see var EARTH_DENSITY, line 19 in const.h - Mat Burdick (accrete)
    * @see var EARTH_DENSITY, line 20 in const.h - Keris (starform)
    * @see var EARTH_DENSITY, line 17 in const.h - Mat Burdick (starform)
    * @see var EARTH_DENSITY, line 67 in  PhysicalConstants.java - Carl Burke (starform)
    */
  final val EARTH_DENSITY: Double = 5.513

  /**
    * The Universal Gravity Constant is denoted by letter G and its an empirical physical constant involved in the calculation(s) of gravitational force
    * between two bodies. It usually appears in Sir Isaac Newton's law of universal gravitation, and in Albert Einstein's general theory of relativity.
    *
    * @note N⋅m^2^/kg^2^
    *
    * @see var GRAV_CONSTANT, line 49 in const.h - Mat Burdick (accrete)
    * @see var GRAV_CONSTANT, line 50 in const.h - Keris (starform)
    * @see var GRAV_CONSTANT, line 47 in const.h - Mat Burdick (starform)
    * @see var GRAV_CONSTANT, line 96 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val GRAV_CONSTANT = 6.674E-11


  /**
    * Billion Years
    */
  final val BILLION_YEARS = 1E9

  /**
    * Number of Days in an earth year.
    *
    * @note unit is days.
    *
    * @see var DAYS_IN_A_YEAR, line 42 in const.h - Mat Burdick (accrete)
    * @see var DAYS_IN_A_YEAR, line 33 in const.h - Keris (starform)
    * @see var DAYS_IN_A_YEAR, line 40 in const.h - Mat Burdick (starform)
    * @see var DAYS_IN_A_YEAR, line 89 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val DAYS_IN_EARTH_YEAR: Double = 365.25

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
    * Number of Hours in a Day. Used in calculating rotation length in hours.
    *
    * @note unit is hours.
    *
    */
  final val HOURS_PER_DAY: Double = 24.0

  /**
    * The gas constant (also known as the molar, universal, or ideal gas constant, denoted by the symbol R or R). A
    * physical constant which is featured in many fundamental equations in the physical sciences, such as the ideal gas
    * law and the Nernst equation.
    *
    * Used in RMS calculation which is equivalent to Fogg's eq 16.
    *
    * @note unit is J K−1 mol−1.
    *
    * @see line 51 in const.h - Mat Burdick (accrete)
    * @see line 49 in const.h - Mat Burdick (starform)
    * @see line 98 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val MOLAR_GAS_CONST = 8.3144621

  /**
    * Base Exosphere temperature. Temperature in kelvin.
    *
    * @note unit is degrees kelvin.
    *
    * @see line 23 in const.h - Mat Burdick (accrete)
    * @see line 21 in const.h - Mat Burdick (starform)
    * @see line 71 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val EXOSPHERE_TEMP: Double = 1273.0

  /**
    * Gravitational Acceleration of Earth.
    *
    * @note unit is metres / sec^2^.
    *
    * @see line 21 in const.h - Mat Burdick (accrete)
    * @see line 19 in const.h - Mat Burdick (starform)
    * @see line 69 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val EARTH_GRAVITY: Double = 9.81


  /**
    * Molecular Weight of Nitrogen or N2. See "Habitable Planets for Man", p. 38.
    *
    * @see Habitable Planets for Man - Dole
    * @see line 73 in const.h - Mat Burdick (accrete)
    * @see line 71 in const.h - Mat Burdick (starform)
    * @see line 120 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val MOLECULAR_NITROGEN: Double = 28.0

  /**
    * Molecular Weight of Nitrogen or N2. See "Habitable Planets for Man", p. 38.
    *
    * @see Habitable Planets for Man - Dole
    * @see line 73 in const.h - Mat Burdick (accrete)
    * @see line 71 in const.h - Mat Burdick (starform)
    * @see line 120 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val MOLECULAR_HYDROGEN: Double = 2.0


  /**
    * Earth's Effective temperature. Temperature in kelvin.
    *
    * @note unit is degrees kelvin.
    *
    * @see line 25 in const.h - Mat Burdick (accrete)
    * @see line 23 in const.h - Mat Burdick (starform)
    * @see line 73 in PhysicalConstants.java - Carl Burke (starform)
    */
  final val EARTH_EFFECTIVE_TEMP: Double = 255.0


  final val MILLIBARS_PER_BAR = 1000.0

  final val EARTH_SURF_PRES_IN_MILLIBARS = 1000.0

  final val FREEZING_POINT_OF_WATER = 273.0
}
