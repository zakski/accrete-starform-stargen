package com.szadowsz.starform.unit

import com.szadowsz.starform.model.eco.calc.EcoCalc

/**
  * Constants File inherits the fully fledged unit categories and declares constants that don't quite fit into them.
  *
  *  These values should not be alterable.
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
  *  @author Zakski : 31/05/2015.
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
    */
  final val EARTH_DENSITY: Double = 5.513

  /**
    * The Universal Gravity Constant is denoted by letter G and its an empirical physical constant involved in the calculation(s) of gravitational force
    * between two bodies. It usually appears in Sir Isaac Newton's law of universal gravitation, and in Albert Einstein's general theory of relativity.
    *
    * @note N⋅m^2^/kg^2^
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
    */
  final val DAYS_IN_EARTH_YEAR: Double = 365.25

  /**
    * Number of Seconds in an hour. Used in calculating rotation length in hours.
    *
    * @note unit is sec.
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
    */
  final val MOLAR_GAS_CONST = 8.3144621

  /**
    * Base Exosphere temperature. Temperature in kelvin.
    *
    * @note unit is degrees kelvin.
    */
  final val EXOSPHERE_TEMP: Double = 1273.0

  /**
    * Gravitational Acceleration of Earth.
    *
    * @note unit is metres / sec^2^.
    */
  final val EARTH_GRAVITY: Double = 9.81


  /**
    * Molecular Weight of Nitrogen or N2. See "Habitable Planets for Man", p. 38.
    *
    * @see Habitable Planets for Man - Dole
    */
  final val MOLECULAR_NITROGEN: Double = 28.0

  /**
    * Molecular Weight of Nitrogen or N2. See "Habitable Planets for Man", p. 38.
    *
    * @see Habitable Planets for Man - Dole
    */
  final val MOLECULAR_HYDROGEN: Double = 2.0


  /**
    * Earth's Effective temperature.
    *
    * @note unit is degrees kelvin.
    */
  final val EARTH_EFFECTIVE_TEMP: Double = 255.0

  /**
    * Freezing point of water on Earth.
    *
    * @note unit is degrees kelvin.
    */
  final val FREEZING_POINT_OF_WATER = 273.0

  /**
    * The Difference between 0 degrees celsius and 0 degrees kelvin
    */
  final val KELVIN_CELSIUS_DIFFERENCE = 273.0


  /**
    * Number of millibars per bar, a unit of atmospheric pressure.
    *
    * @note unit is millibars.
    */
  final val MILLIBARS_PER_BAR = 1000.0

  /**
    * Average atmospheric pressure of Earth's Surface.
    *
    * @note unit is millibars.
    */
  final val EARTH_SURF_PRES_IN_MILLIBARS = 1000.0
}
