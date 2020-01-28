package com.szadowsz.starform.planets

import com.szadowsz.starform.unit.UnitConstants

trait OrbitalCalc {
  this : UnitConstants =>
  
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
  
  /**
   * Function to determine the length of the orbit of a small body around a large body sun in hours. Though orbit length
   * in days is reported by Fogg he doesn't explicitly mention its calculation, so we take a leaf out of Mat Burdick's
   * code and use a derivation of Newton's version of Kepler's 3rd law, for when the orbiting body has a non-negligible
   * mass.
   *
   * @note the unit is earth days.
   *
   * @see method period, line 168 in enviro.c - Mat Burdick (accrete)
   * @see method period, line 167 in enviro.c - Keris (starform)
   * @see method period, line 168 in enviro.c - Mat Burdick (starform)
   * @see method period, line 486 in Planet.java - Carl Burke (starform)
   *
   * @param smallMass small body mass in Solar Mass. Typically the Planet.
   * @param largeMass larger body mass in Solar Mass. Typically the Sun.
   * @param axis      Semi-major axis of orbit in AU.
   * @return Orbit length in Earth Days.
   */
  def orbitLength(axis: Double, smallMass: Double, largeMass: Double): Double = {
    // TODO consider optimisation by removing smallMass as the mass of the planet in solar mass should actually be negligible
    Math.sqrt(Math.pow(axis, 3) / (smallMass + largeMass)) * DAYS_IN_EARTH_YEAR
  }
}
