// scalastyle:off method.name
package com.szadowsz.accrete.constants

/**
  * Constants Required Specifically for the Accrete Simulation
  *
  * @author Zakski : 03/06/2015.
  */
trait AccreteConstants {

  /**
    * Coefficient used in dust cloud density calculations during determination of the initial conditions of the extra-solar planetary system. Represented by
    * 'A' in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "section a) Initial Conditions in the Cloud". Eq. 8 in Fogg's paper
    * proposes that 'A' should be modified to scale with stellar mass. Fogg states that A should be proportional to sqrt of the Stellar Mass Ratio.
    *
    * @note Original value from Dole is 1.5E-3 which is the value that Ian uses. Mat and Carl alter this to 2.0E-3.
    * @note unit is solar masses per cubic AU.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see eq. 8, p. 503, Extra-Solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see var DUST_DENSITY_COEFF, line 88 in DoleParams.java - Ian Burrell (accrete)
    * @see var DUST_DENSITY_COEFF, line 54 in const.h - Mat Burdick (accrete)
    * @see var DUST_DENSITY_COEFF, line 55 in const.h - Keris (starform)
    * @see var DUST_DENSITY_COEFF, line 52 in const.h - Mat Burdick (starform)
    * @see var DUST_DENSITY_COEFF, line 101 in PhysicalConstants.java - Carl Burke (starform)
    */
  def DUST_DENSITY_COEFF: Double = 1.5E-3 // TODO Confirm if the change from 1.5 to 2.0 was made by Dole, otherwise leave the original value.

  /**
    * Value of the inverted exponent applied to the distance from the stellar mass (in AU) in dust cloud density calculations during determination of the
    * initial conditions of the extra-solar planetary system. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @note Original value from Dole is 3.0 which all subsequent programmers use.
    * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system; other values may not produce desired
    *       output.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var N, line 90 in DoleParams.java - Ian Burrell (accrete)
    * @see var N, line 56 in const.h - Mat Burdick (accrete)
    * @see var N, line 57 in const.h - Keris (starform)
    * @see var N, line 54 in const.h - Mat Burdick (starform)
    * @see var N, line 103 in PhysicalConstants.java - Carl Burke (starform)
    */
  def N: Double = 3.0

  /**
    * Value of the negative coefficient multiplied by the distance from the stellar mass (in AU) in dust cloud density calculations during determination of the
    * initial conditions of the extra-solar planetary system. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @note Original value from Dole is 5.0 which all subsequent programmers use.
    * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system; other values may not produce desired
    *       output.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var ALPHA, line 89 in DoleParams.java - Ian Burrell (accrete)
    * @see var ALPHA, line 55 in const.h - Mat Burdick (accrete)
    * @see var ALPHA, line 56 in const.h - Keris (starform)
    * @see var ALPHA, line 53 in const.h - Mat Burdick (starform)
    * @see var ALPHA, line 102 in PhysicalConstants.java - Carl Burke (starform)
    */
  def ALPHA: Double = 5.0

  /**
    * Gas to Dust Ratio of the nebula surrounding the Star. Used in dust cloud density calculations during determination of the initial conditions of the
    * extra-solar planetary system. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @note Original value from Dole is 50.0 which all subsequent programmers use.
    * @note Scale should probably be between 50.0 and 100.0.
    * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar system; other values may not produce desired
    *       output.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var K, line 87 in DoleParams.java - Ian Burrell (accrete)
    * @see var K, line 52 in const.h - Mat Burdick (accrete)
    * @see var K, line 53 in const.h - Keris (starform)
    * @see var K, line 50 in const.h - Mat Burdick (starform)
    * @see var K, line 99 in PhysicalConstants.java - Carl Burke (starform)
    */
  def K: Double = 50.0


  /**
    * Smallest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations to calculate the semi-major axis of the
    * planetismal's orbit. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "III. Experimental Simulation b) The
    * Planetary Nuclei".
    *
    * @note Original value from Dole is 0.3.
    *
    * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method InnermostPlanet, line 145 in DoleParams.java - Ian Burrell (accrete)
    * @see method innermost_planet, line 50 in accrete.c - Mat Burdick (accrete)
    * @see method nearest_planet, line 73 in accrete.c - Keris (starform)
    * @see method nearest_planet, line 50 in accrete.c - Mat Burdick (starform)
    * @see method nearest_planet, line 221 in Star.java - Carl Burke (starform)
    */
  def INNERMOST_PLANET: Double = 0.3

  /**
    * Furthest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations to calculate the semi-major axis of the
    * planetismal's orbit. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "III. Experimental Simulation b) The
    * Planetary Nuclei".
    *
    * @note Original value from Dole is 0.3.
    *
    * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method OutermostPlanet, line 149 in DoleParams.java - Ian Burrell (accrete)
    * @see method outermost_planet, line 56 in accrete.c - Mat Burdick (accrete)
    * @see method farthest_planet, line 79 in accrete.c - Keris (starform)
    * @see method farthest_planet, line 56 in accrete.c - Mat Burdick (starform)
    * @see method farthest_planet, line 231 in Star.java - Carl Burke (starform)
    */
  def OUTERMOST_PLANET: Double = 50.0

  /**
    * The eccentricity coefficient. Used in planetismal orbit calculations to calculate the elliptical nature of the planetismal's orbit. Introduced in
    * "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "III. Experimental Simulation b) The Planetary Nuclei". It has its roots in
    * Dole's "Habitable Planets for Man" book, derived from its "Probability That The Planet's Eccentricity Is Sufficiently Low" equation.
    *
    * @note should be between 0.0 and 1.0
    * @note Original value from Dole is 0.077.
    * @note input parameter for the accretion process. value was chosen for its ability to produce sensible eccentricities; other values may not produce
    *       desired output.
    *
    * @see Habitable Planets for Man - Stephen H. Dole
    * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var ECCENTRICITY_COEFF, line 126 in DoleParams.java - Ian Burrell (accrete)
    * @see var ECCENTRICITY_COEFF, line 12 in const.h - Mat Burdick (accrete)
    * @see var ECCENTRICITY_COEFF, line 13 in const.h - Keris (starform)
    * @see var ECCENTRICITY_COEFF, line 11 in const.h - Mat Burdick (starform)
    * @see var ECCENTRICITY_COEFF, line 106 in PhysicalConstants.java - Carl Burke (starform)
    */
  def ECCENTRICITY_COEFF: Double = 0.077

  /**
    * The Cloud Eccentricity coefficient. Represent the average eccentricity of particles in the cloud. Used in dust band width calculations to more accurately
    * simulate particle orbits in the cloud. Represented by W in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "c) Aggregation".
    * Mat and Carl use 0.2 and Ian uses 0.25 for its value.
    *
    * @note tested between 0.0 and 0.25
    * @note Dole recommends 0.2 or 0.25 for solar systems resembling our own.
    * @note input parameter for the accretion process. value was chosen for its ability to produce sensible eccentricities; other values may not produce
    *       desired output.
    *
    * @see pp. 20-21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var CLOUD_ECCENTRICITY, line 54 in DoleParams.java - Ian Burrell (accrete)
    * @see var cloud_eccentricity, lines 26,41 in const.h - Mat Burdick (accrete)
    * @see var cloud_eccen, lines 49,63 in const.h - Keris (starform)
    * @see var cloud_eccentricity, lines 26,41 in const.h - Mat Burdick (starform)
    * @see var cloud_eccentricity, line 43 in DustDisc.java - Carl Burke (starform)
    */
  def CLOUD_ECCENTRICITY: Double = 0.2

  /**
    * The Starting mass given to all protoplanets.
    *
    * @note unit is solar mass.
    * @note referred to as m0 in Dole's Paper.
    * @note Dole states that the simulation is pretty insensitive to this value becoming smaller.
    *
    * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var PROTOPLANET_MASS, line 41 in Planetismal.java - Ian Burrell (accrete)
    * @see var PROTOPLANET_MASS, line 13 in const.h - Mat Burdick (accrete)
    * @see var PROTOPLANET_MASS, line 14 in const.h - Keris (starform)
    * @see var PROTOPLANET_MASS, line 12 in const.h - Mat Burdick (starform)
    * @see var PROTOPLANET_MASS, line 40 in Protoplanet.java - Carl Burke (starform)
    */
  def PROTOPLANET_MASS: Double = 1.0E-15 /* Starting Mass in solar mass */

  /**
    * The Critical Mass Constant.
    *
    * @note unit is solar mass.
    * @note referred to as B in Dole's Paper.
    *
    * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see var B, line 23 in DoleParams.java - Ian Burrell (accrete)
    * @see var B, line 53 in const.h - Mat Burdick (accrete)
    * @see var B, line 54 in const.h - Keris (starform)
    * @see var B, line 51 in const.h - Mat Burdick (starform)
    * @see var B, line 100 in PhysicalConstants.java - Carl Burke (starform)
    */
  def B: Double = 1.2E-5
}
