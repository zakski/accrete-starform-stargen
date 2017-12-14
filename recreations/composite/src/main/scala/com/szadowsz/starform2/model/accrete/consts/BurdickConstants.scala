// scalastyle:off method.name
package com.szadowsz.starform2.model.accrete.consts

/**
  * Created on 22/08/2017.
  */
class BurdickConstants extends AccreteConstants {

  /**
    * Coefficient used in dust cloud density calculations during determination of the initial conditions of the extra-solar planetary system. Represented by
    * 'A' in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "section a) Initial Conditions in the Cloud".
    *
    * @note Original value from Dole is 1.5E-3. Mat Burdick alter this to 2.0E-3.
    * @note Doubling this can cause catastrophic results; borderline binary systems
    * @note unit is solar masses per cubic AU.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see const var DUST_DENSITY_COEFF, line 47 in const.h - Mat Burdick (accrete)
    * @see const var DUST_DENSITY_COEFF, line 52 in const.h - Mat Burdick (starform)
    * @see const var DUST_DENSITY_COEFF, line 101 in PhysicalConstants.java - Carl Burke (starform)
    * @see const var DUST_DENSITY_COEFF, line 88 in DoleParams.java - Ian Burrell (accrete)
    * @see const var DUST_DENSITY_COEFF, line 55 in const.h - Keris (starform)
    * @see const var DUST_DENSITY_COEFF, line 46 in const.h - Webb (starform)
    * @see const var Ao, line 141 in dole.cc - Keris2/Folkins (accrete) (in form of Msol / AU**3)
    */
  override def DUST_DENSITY_COEFF: Double = 2.0E-3
}
