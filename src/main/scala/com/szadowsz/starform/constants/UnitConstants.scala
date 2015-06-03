package com.szadowsz.starform.constants

/**
 * Constants File made up of values taken from all versions of the program. Most have been updated where more
 * accurate values exist. This particular file contains all information specifically to do with units of measurement.
 *
 * @author Zakski : 31/05/2015.
 */
trait UnitConstants {

  /**
   * Number of centimetres in a metre.
   *
   * @note unit is centimetres.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  final val CM_PER_METRE: Double = 100.0

  /**
   * Number of centimetres in a metre.
   *
   * @note unit is metres.
   */
  final val METRES_PER_KM: Double = 1000.0

  /**
   * Number of centimetres in a kilometre.
   *
   * @note unit is centimetres.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   * @author Ian Burrell - accrete
   */
  final val CM_PER_KM: Double = CM_PER_METRE * METRES_PER_KM

  /**
   * Number of millibars in a bar. Unit of pressure. Used to measure atmospheric pressure.
   *
   * @note don't confuse with standard atmosphere (atm) which has the value of 1013.25 millibars.
   * @note unit is millibars.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  final val MILLIBARS_PER_BAR: Double = 1000.0


  /**
   * The freezing point of water in degrees kelvin. Original value used by Mat and Carl was 273.0 which is
   * incorrect.
   *
   * @note unit is degrees kelvin.
   *
   * @author Carl Burke - starform
   * @author Mat Burdick - accrete / starform
   */
  final val FREEZING_POINT_OF_WATER: Double = 273.15
}
