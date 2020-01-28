package com.szadowsz.starform.planets

trait OrbitalCalc {
  
  /**
   * Method to get the Perihelion distance between an orbiting planetary body and its star. The Perihelion distance is
   * the closest that the planetary body will be from its Star. Used to find the outer dust sweep limit, see "III.
   * Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer
   * Simulation".
   *
   * @note equivalent of a - ae in dole's paper.
   * @note unit of return value is AU
   * @note versions that don't use it explicitly, put it as part of their equivalent of [[innerGravLimit]].
   *
   * @see p. 17, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method PerihelionDistance, line 37 in DoleParams.java - Ian Burrell (accrete)
   * @see method EvolvePlanet, lines 356 in Dole.c - Andrew Folkins (accretion)
   * @see method EvolvePlanet, lines 432 in dole.c - Keris (accretion v1)
   * @see method EvolvePlanet, line 523 in dole.cc - Keris (accretion v2)
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @return the closest distance between the body and its host star in AU.
   */
  def perihelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 - ecc)
  
  /**
   * Method to get the Aphelion distance between an orbiting planetary body and its star. The Aphelion distance is the
   * furthest away that the planetary body will be from its Star. Used to find the outer dust sweep limit, see "III.
   * Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer
   * Simulation".
   *
   * @note equivalent of a + ae in dole's paper.
   * @note unit of return value is AU.
   * @note versions that don't use it explicitly, put it as part of their equivalent of [[outerGravLimit]].
   *
   * @see p. 17, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
   * @see method AphelionDistance, line 41 in DoleParams.java - Ian Burrell (accrete)
   * @see method EvolvePlanet, lines 357 in Dole.c - Andrew Folkins (accretion)
   * @see method EvolvePlanet, lines 433 in dole.c - Keris (accretion v1)
   * @see method EvolvePlanet, line 524 in dole.cc - Keris (accretion v2)
   *
   * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
   * @param ecc - the eccentricity of the planetary body's orbit
   * @return the greatest distance between the body and its host star in AU.
   */
  def aphelionDistance(axis: Double, ecc: Double): Double = axis * (1.0 + ecc)
  
  
}
