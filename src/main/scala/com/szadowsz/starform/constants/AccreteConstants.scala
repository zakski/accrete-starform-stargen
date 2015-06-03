package com.szadowsz.starform.constants

/**
 * @author Zakski : 03/06/2015.
 */
trait AccreteConstants {


  /**
   * Coefficient used in dust cloud density calculations during determination of the initial conditions of the
   * extra-solar planetary system. Represented by 'A' in "Formation of Planetary Systems by Aggregation: A
   * Computer Simulation" in section a) Initial Conditions in the Cloud. Equation 8 in Extra-Solar Planetary Systems
   * proposes that 'A' should be modified to scale with stellar mass. Fogg states that A should be proportional
   * to (Mass of Star/Mass of Sun)-2.
   *
   * @todo Confirm if the change from 1.5 to 2.0 was made by Dole in susequent paper. until then leave original value.
   *
   * @note Original value from Dole is 1.5E-3 which is the value that Ian uses. Mat and Carl alter this to 2.0E-3.
   * @note unit is solar masses per cubic AU.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see Extra-Solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke
   */
  val DUST_DENSITY_COEFF = 1.5E-3

  /**
   * Value of the inverted exponent applied to the distance from the stellar mass (in AU) in dust cloud density
   * calculations during determination of the initial conditions of the extra-solar planetary system. Introduced in
   * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 3.0 which all subsequent programmers use.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system;
   *       other values may not produce desired output.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke
   */
  val N = 3.0

  /**
   * Value of the negative coefficient multiplied by the distance from the stellar mass (in AU) in dust cloud density
   * calculations during determination of the initial conditions of the extra-solar planetary system. Introduced in
   * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 5.0 which all subsequent programmers use.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system;
   *       other values may not produce desired output.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke
   */
  val ALPHA: Double = 5.0

  /**
   * Gas to Dust Ratio of the nebula surrounding the Star. Used in dust cloud density calculations during determination
   * of the initial conditions of the extra-solar planetary system. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 50.0 which all subsequent programmers use.
   * @note Scale should probably be between 50.0 and 100.0.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system;
   *       other values may not produce desired output.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke

   */
  val K: Double = 50.0


  /**
   * Smallest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations
   * to calculate the semi-major axis of the planetismal's orbit. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation" in "b) The Planetary Nuclei".
   *
   * @todo Note specific version that Ian, Mat and Carl use.
   *
   * @note Original value from Dole is 0.3.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   */
  val INNERMOST_PLANET: Double = 0.3

  /**
   * Furthest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations
   * to calculate the semi-major axis of the planetismal's orbit. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation" in "b) The Planetary Nuclei".
   *
   * @todo Note specific version that Ian, Mat and Carl use.
   *
   * @note Original value from Dole is 0.3.
   *
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   */
  val OUTERMOST_PLANET: Double = 50.0

  /**
   * The eccentricity coefficient. Used in planetismal orbit calculations to calculate the elliptical nature of the
   * planetismal's orbit. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "b)
   * The Planetary Nuclei". Has its roots in "Habitable Planets for Man"'s Probability That The Planet's Eccentricity
   * Is Sufficiently Low equation.
   *
   * @note Original value from Dole is 0.077.
   * @note parameter for the accretion process. value was chosen for its ability to produce sensible eccentricities;
   *       other values may not produce desired output.
   *
   * @see Habitable Planets for Man - Stephen H. Dole
   * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   *
   * @author Ian Burrell
   * @author Mat Burdick
   * @author Carl Burke
   */
  val ECCENTRICITY_COEFF: Double = 0.077
}
