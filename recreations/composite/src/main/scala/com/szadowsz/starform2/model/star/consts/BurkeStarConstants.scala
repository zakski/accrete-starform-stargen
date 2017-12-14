// scalastyle:off method.name
package com.szadowsz.starform2.model.star.consts

/**
  * Created on 15/08/2017.
  */
class BurkeStarConstants extends StarConstants {

  /**
    * Primary Stellar Classes used by Havard and Yerkes Classification System.
    *
    * @note Remember by Oh Be A Fine Girl, Kiss Me
    */
  val CLASS_CODE: Array[Char] = Array('O', 'B', 'A', 'F', 'G', 'K', 'M')


  // SPECT - TEMPERATURE TABLE BY SPECTRAL PLAN_CLASS (new version)
  /**
    * Temperature Table By Spectral Class
    *
    * @see var SPECT, line 58 in Star.Java - Carl Burke (starform)
    */
  val SPECT: Array[Double] = Array(
    25000.0, 23600.0, 22200.0, 20800.0, 19400.0, 18000.0, 16600.0, 15200.0, 13800.0, 12400.0,
    11000.0, 10650.0, 10300.0, 9950.0, 9600.0, 9250.0, 8900.0, 8550.0, 8200.0, 7850.0,
    7500.0, 7350.0, 7200.0, 7050.0, 6900.0, 6750.0, 6600.0, 6450.0, 6300.0, 6150.0,
    6000.0, 5900.0, 5800.0, 5700.0, 5600.0, 5500.0, 5400.0, 5300.0, 5200.0, 5100.0,
    5000.0, 4850.0, 4700.0, 4550.0, 4400.0, 4250.0, 4100.0, 3950.0, 3800.0, 3650.0,
    3500.0, 3200.0, 2900.0, 2600.0, 2300.0, 2000.0, 1700.0, 1400.0, 1100.0, 800.0
  )

  /**
    * bc - 'bolometric correction', established by calculation of ratio of overall energy to visible energy, and shifting the magnitudes to agree with g2
    * star at g2 temperature. add this to visual magnitude curve has been manually trimmed at the lower end
    *
    * @see var BC, line 70 in Star.Java - Carl Burke (starform)
    */
  val BC: Array[Double] = Array(
    1.8770E+0, 1.7344E+0, 1.5864E+0, 1.4329E+0, 1.2737E+0,
    1.1089E+0, 9.3888E-1, 7.6439E-1, 5.8704E-1, 4.0991E-1,
    2.3869E-1, 1.9790E-1, 1.5835E-1, 1.2030E-1, 8.4102E-2,
    5.0144E-2, 1.8896E-2, -9.0779E-3, -3.3103E-2, -5.2363E-2,
    -6.5867E-2, -6.9601E-2, -7.1950E-2, -7.2793E-2, -7.1999E-2,
    -6.9424E-2, -6.4909E-2, -5.8280E-2, -4.9344E-2, -3.7890E-2,
    -2.3682E-2, -1.2553E-2, -8.8050E-8, 1.4066E-2, 2.9742E-2,
    4.7134E-2, 6.6354E-2, 8.7522E-2, 1.1077E-1, 1.3624E-1,
    1.6409E-1, 2.1068E-1, 2.6363E-1, 3.2363E-1, 3.9149E-1,
    4.6814E-1, 5.5465E-1, 6.5224E-1, 7.6234E-1, 8.8663E-1,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
  )

  /**
    * constant variable that is part of cubic curve for absolute visual magnitude
    *
    * @see method MAINSEQ, line 168 in Star.Java - Carl Burke (starform)
    */
  val A0: Double = 26.281

  /**
    * constant variable that is part of cubic curve for absolute visual magnitude
    *
    * @see method MAINSEQ, line 169 in Star.Java - Carl Burke (starform)
    */
  val A1: Double = -3.4495

  /**
    * constant variable that is part of cubic curve for absolute visual magnitude
    *
    * @see method MAINSEQ, line 170 in Star.Java - Carl Burke (starform)
    */
  val A2: Double = -0.77271

  /**
    * constant variable that is part of cubic curve for absolute visual magnitude
    *
    * @see method MAINSEQ, line 171 in Star.Java - Carl Burke (starform)
    */
  val A3: Double = 0.076305
}
