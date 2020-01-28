// scalastyle:off method.name
package com.szadowsz.starform.model.accrete

/**
 * Constants Required Specifically for the Accrete Simulation as specified by Dole.
 *
 * @author Zakski : 03/06/2015.
 */
class AccreteConstants {
  
  /**
   * The Starting mass given to all protoplanets.
   *
   * @note unit is solar mass.
   * @note referred to as m0 in Dole's Paper.
   * @note Dole states that the simulation is pretty insensitive to this value becoming smaller.
   * @note Sagan states that varying the planetismal seed mass from Dole's original value has no appreciable effect on
   *       the final results.
   *
   * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see p. 10, Computer Simulations of Planetary Accretion: Dynamics Sensitivity to Initial Conditions - Isaacman
   *      & Sagan
   * @see const var PROTOPLANET_MASS, line 10 in const.h - Mat Burdick (accrete)
   * @see const var PROTOPLANET_MASS, line 12 in const.h - Mat Burdick (starform)
   * @see var PROTOPLANET_MASS, line 40 in Protoplanet.java - Carl Burke (starform)
   * @see const var PROTOPLANET_MASS, line 41 in Planetismal.java - Ian Burrell (accrete)
   * @see const var PROTOPLANET_MASS, line 14 in const.h - Keris (starform)
   * @see const var PROTOPLANET_MASS, line 8 in const.h - Webb (starform)
   * @see const var m0, line 156 in dole.cc - Keris2/Folkins (accrete) in KG
   */
  final val PROTOPLANET_MASS: Double = 1.0E-15 /* Starting Mass in solar mass */
  
  /**
   * Coefficient used in dust cloud density calculations during determination of the initial conditions of the
   * extra-solar planetary system. Represented by 'A' in "Formation of Planetary Systems by Aggregation: A Computer
   * Simulation" in "section a) Initial Conditions in the Cloud".
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
  def DUST_DENSITY_COEFF: Double = 1.5E-3
  
  /**
   * Value of the inverted exponent applied to the distance from the stellar mass (in AU) in dust cloud density
   * calculations during determination of the initial conditions of the extra-solar planetary system. Introduced in
   * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 3.0 which all subsequent programmers use.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar
   *       system; other values may not produce desired output.
   *
   * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see const var N, line 49 in const.h - Mat Burdick (accrete)
   * @see const var N, line 54 in const.h - Mat Burdick (starform)
   * @see const var N, line 103 in PhysicalConstants.java - Carl Burke (starform)
   * @see const var N, line 90 in DoleParams.java - Ian Burrell (accrete)
   * @see const var N, line 57 in const.h - Keris (starform)
   * @see const var N, line 48 in const.h - Webb (starform)
   * @see const var gamma, line 147 in dole.cc - Keris2/Folkins (accrete)(already converted to fraction)
   */
  def N: Double = 3.0
  
  /**
   * Value of the negative coefficient multiplied by the distance from the stellar mass (in AU) in dust cloud density
   * calculations during determination of the initial conditions of the extra-solar planetary system. Introduced in
   * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 5.0 which all subsequent programmers use.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar
   *       system; other values may not produce desired output.
   *
   * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see const var ALPHA, line 48 in const.h - Mat Burdick (accrete)
   * @see const var ALPHA, line 53 in const.h - Mat Burdick (starform)
   * @see const var ALPHA, line 102 in PhysicalConstants.java - Carl Burke (starform)
   * @see const var ALPHA, line 89 in DoleParams.java - Ian Burrell (accrete)
   * @see const var ALPHA, line 56 in const.h - Keris (starform)
   * @see const var ALPHA, line 47 in const.h - Webb (starform)
   * @see const var alpha, line 144 in dole.cc - Keris2/Folkins (accrete)
   */
  def ALPHA: Double = 5.0
  
  /**
   * Gas to Dust Ratio of the nebula surrounding the Star. Used in dust cloud density calculations during determination
   * of the initial conditions of the extra-solar planetary system. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation".
   *
   * @note Original value from Dole is 50.0 which all subsequent programmers use.
   * @note Scale should probably be between 50.0 and 100.0. Though K as low as 10 can allow for the generation of
   *       plausible systems.
   * @note input parameter for the accretion process. value was chosen for its ability to replicate our solar
   *       system; other values may not produce desired output.
   *
   * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see p. 12, Computer Simulations of Planetary Accretion: Dynamics Sensitivity to Initial Conditions - Isaacman
   *      & Sagan
   * @see const var K, line 45 in const.h - Mat Burdick (accrete)
   * @see const var K, line 50 in const.h - Mat Burdick (starform)
   * @see const var K, line 99 in PhysicalConstants.java - Carl Burke (starform)
   * @see const var K, line 87 in DoleParams.java - Ian Burrell (accrete)
   * @see const var K, line 53 in const.h - Keris (starform)
   * @see const var K, line 44 in const.h - Webb (starform)
   * @see const var K, line 150 in dole.cc - Keris2/Folkins (accrete)
   */
  def K: Double = 50.0
  
  
  /**
   * Smallest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations to
   * calculate the semi-major axis of the planetismal's orbit. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation" in "III. Experimental Simulation b) The Planetary Nuclei".
   *
   * @note Original value from Dole is 0.3.
   *
   * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method innermost_planet, line 48 in accrete.c - Mat Burdick (accrete)
   * @see method nearest_planet, line 68 in accrete.c - Mat Burdick (starform)
   * @see method nearest_planet, line 221 in Star.java - Carl Burke (starform)
   * @see method InnermostPlanet, line 145 in DoleParams.java - Ian Burrell (accrete)
   * @see method nearest_planet, line 1 in sysinl.h - Keris (starform)
   * @see method innermost_planet, line 21 in accrete.cpp - Webb (starform)
   * @see const var MINRADIUS, line 171 in dole.cc - Keris2/Folkins (accrete)
   */
  def INNERMOST_PLANET: Double = 0.3
  
  /**
   * Furthest distance from the Sun where can we we expect a planet to form. Used in planetismal orbit calculations to
   * calculate the semi-major axis of the planetismal's orbit. Introduced in "Formation of Planetary Systems by
   * Aggregation: A Computer Simulation" in "III. Experimental Simulation b) The Planetary Nuclei".
   *
   * @note Original value from Dole is 50.
   *
   * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method outermost_planet, line 54 in accrete.c - Mat Burdick (accrete)
   * @see method outermost_planet, line 50 in accrete.c - Mat Burdick (starform)
   * @see method farthest_planet, line 231 in Star.java - Carl Burke (starform)
   * @see method OutermostPlanet, line 149 in DoleParams.java - Ian Burrell (accrete)
   * @see method outermost_planet, line 6 in sysinl.h - Keris (starform)
   * @see method outermost_planet, line 26 in accrete.cpp - Webb (starform)
   * @see const var MAXRADIUS, line 172 in dole.cc - Keris2/Folkins (accrete)
   */
  def OUTERMOST_PLANET: Double = 50.0
  
  /**
   * The eccentricity coefficient. Used in planetismal orbit calculations to calculate the elliptical nature of the
   * planetismal's orbit. Introduced in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in
   * "III. Experimental Simulation b) The Planetary Nuclei". It has its roots in Dole's "Habitable Planets for Man"
   * book, derived from its "Probability That The Planet's Eccentricity Is Sufficiently Low" equation.
   *
   * @note should be between 0.0 and 1.0
   * @note Original value from Dole is 0.077.
   * @note input parameter for the accretion process. value was chosen for its ability to produce sensible
   *       eccentricities; other values may not produce desired output.
   *
   * @see Habitable Planets for Man - Stephen H. Dole
   * @see p. 15, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see const var ECCENTRICITY_COEFF, line 45 in const.h - Mat Burdick (accrete)
   * @see const var ECCENTRICITY_COEFF, line 50 in const.h - Mat Burdick (starform)
   * @see const var ECCENTRICITY_COEFF, line 106 in PhysicalConstants.java - Carl Burke (starform)
   * @see const var ECCENTRICITY_COEFF, line 126 in DoleParams.java - Ian Burrell (accrete)
   * @see const var ECCENTRICITY_COEFF, line 53 in const.h - Keris (starform)
   * @see const var ECCENTRICITY_COEFF, line 44 in const.h - Webb (starform)
   * @see method CreatePlanet, line 280 in dole.cc - Keris2/Folkins (accrete)
   */
  def ECCENTRICITY_COEFF: Double = 0.077
  
  /**
   * The Cloud Eccentricity coefficient. Represent the average eccentricity of particles in the cloud. Used in dust band
   * width calculations to more accurately simulate particle orbits in the cloud. Represented by W in "Formation of
   * Planetary Systems by Aggregation: A Computer Simulation" in "c) Aggregation".
   *
   * Most use 0.2.
   *
   * @note tested between 0.0 and 0.25
   * @note Dole recommends 0.2 or 0.25 for solar systems resembling our own.
   * @note input parameter for the accretion process. value was chosen for its ability to produce sensible
   *       eccentricities; other values may not produce desired output.
   *
   * @see pp. 20-21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method set_initial_conditions, line 28 in accrete.c - Mat Burdick (accrete)
   * @see method set_initial_conditions, line 32 in accrete.c - Mat Burdick (starform)
   * @see constructor, line 15 in Protosystem.java - Carl Burke (starform)
   * @see const var CLOUD_ECCENTRICITY, line 54 in DoleParams.java - Ian Burrell (accrete)
   * @see method set_initial_conditions, line 53 in accrete.c - Keris (starform)
   * @see method set_initial_conditions, line 44 in accrete.cpp - Webb (starform)
   * @see const var W, line 153 in dole.cc - Keris2/Folkins (accrete)
   */
  def CLOUD_ECCENTRICITY: Double = 0.2
  
  /**
   * The Critical Mass Constant. A Proportionality factor that should be between 1.0E-5 and 2.0E-5 Solar masses.
   *
   * @note unit is solar mass.
   * @note referred to as B in Dole's Paper.
   *
   * @see p. 21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see const var B, line 46 in const.h - Mat Burdick (accrete)
   * @see const var B, line 51 in const.h - Mat Burdick (starform)
   * @see const var B, line 100 in PhysicalConstants.java - Carl Burke (starform)
   * @see const var B, line 23 in DoleParams.java - Ian Burrell (accrete)
   * @see const var B, line 54 in const.h - Keris (starform)
   * @see const var B, line 45 in const.h - Webb (starform)
   * @see const var B, line 150 in dole.cc - Keris2/Folkins (accrete) (converted to Kg)
   */
  def B: Double = 1.2E-5
}