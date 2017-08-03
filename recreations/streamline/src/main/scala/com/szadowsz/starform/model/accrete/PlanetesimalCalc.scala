package com.szadowsz.starform.model.accrete

import com.szadowsz.starform.model.star.StarRequired


/**
  * Calculations need to model Planetesimal objects.
  *
  * @author Zakski : 21/07/2015.
  */
case class PlanetesimalCalc (aConst: AccreteConstants) extends StarRequired {

  /**
    * Method to get the Perihelion distance between an orbiting planetary body and its star. The Perihelion distance is the closest that the planetary body will
    * be from its Star. Used to find the outer dust sweep limit, see "III. Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems
    * by Aggregation: A Computer Simulation".
    *
    * @note equivalent of a - ae in dole's paper.
    * @note unit of return value is AU
    * @note versions that don't use it explicitly, put it as part of their equivilant of [[innerGravLimit]].
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
    * Method to get the Aphelion distance between an orbiting planetary body and its star. The Aphelion distance is the furthest away that the planetary body
    * will be from its Star. Used to find the outer dust sweep limit, see "III. Experimental Simulation, section c) Aggregation" in "Formation of Planetary
    * Systems by Aggregation: A Computer Simulation".
    *
    * @note equivalent of a + ae in dole's paper.
    * @note unit of return value is AU.
    * @note versions that don't use it explicitly, put it as part of their equivilant of [[outerGravLimit]].
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
    * Method to calculate whether a planetesimal has gained enough mass to accrete gas as well as dust, see "III. Experimental Simulation, section c)
    * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". Modified by Fogg in his eq. 7 to take solar luminosity into
    * account.
    *
    * @note original formula is located in [[PlanetesimalCalc]]
    * @note unit of return value is solar mass.
    *
    * @see eq (7), p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method critical_limit, line 257 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 359 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 435 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 526 in dole.cc - Keris (accretion v2)
    * @see method critical_limit, line 283 in accrete.c - Keris (starform)
    * @see method critical_limit, line 256 in accrete.c - Mat Burdick (starform)
    * @see method critical_limit, line 243 in  Star.java - Carl Burke (starform)
    *
    * @param perihelion closest protoplanet gets to the sun.
    * @return critical mass in solar mass.
    */
  def criticalMass(perihelion: Double): Double = aConst.B * Math.pow(perihelion * Math.sqrt(star.luminosity), -0.75)

  /**
    * Method is function of mass used in calculation to get the distance at which the protoplanet nuclei will attract particles by gravitation attraction. Used
    * to find the dust sweep limits, see "III. Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer
    * Simulation".
    *
    * @note equivalent of mu/μ in dole's paper.
    *
    * @see p. 17, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see [[innerGravLimit()]] / [[outerGravLimit()]]
    *
    * @param mass - the mass of the protoplanetary body in solar mass (M?).
    * @return coeffecient applied to perihelion and aphelion distances.
    */
  def muMassFunction(mass: Double): Double = Math.pow(mass / (1.0 + mass), 0.25)

  /**
    * Method is used to calculate the inner distance at which the protoplanet nuclei will attract particles by gravitation attraction. Formula taken from
    * "III. Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". It was originally chosen
    * because of its simplicity and its a reasonable approximation to certain limits derived from the restricted three body problem.
    *
    * @note equivalent of rp - xp in dole's paper.
    * @note Burdick uses it as part of his equivalent of [[innerBandLimit]] in accrete/starform, additionally he does not reduce the mass using the mu function.
    * @note Burke uses it as part of his equivalent of [[innerBandLimit]] in starform, he only sometimes reduces the mass using the mu function.
    * @note Keris uses it as part of his equivalent of [[innerBandLimit]] in starform.
    * @note Other versions that don't use two separate methods explicitly, use a method called Reach to calculate the gravitational pull separately.
    * @note unit of return value is AU.
    *
    * @see figure 6, p. 19 , Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method InnerEffectLimit, line 70 in DoleParams.java - Ian Burrell (accrete)
    * @see method Reach, line 129 / method EvolvePlanet, lines 368-370 in Dole.c - Andrew Folkins (accretion)
    * @see method Reach, line 139 / method EvolvePlanet, lines 447-449 in dole.c - Keris (accretion v1)
    * @see method Reach, line 234 / method EvolvePlanet, lines 538-540 in dole.cc - Keris (accretion v2)
    *
    * @param perihelion the closest distance between the body and its host star in AU.
    * @param mass the mass of the body in solar mass (M?).
    * @return the (perihelion - gravitational pull) distance in AU.
    */
  def innerGravLimit(perihelion: Double, mass: Double) : Double = perihelion * (1.0 - muMassFunction(mass))

  /**
    * Method is used to calculate the outer distance at which the protoplanet nuclei will attract particles by gravitation attraction.
    *
    * @note unit of return value is AU.
    *
    * @see [[innerGravLimit]] above for more info.
    *
    * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
    * @param ecc - the eccentricity of the planetary body's orbit
    * @param mass the mass of the body in solar mass (M?).
    * @return the greatest distance between the body and its host star in AU.
    */
  def innerGravLimit(axis: Double, ecc: Double, mass: Double): Double = innerGravLimit(perihelionDistance(axis, ecc), mass)

  /**
    * Method is used to calculate the outer distance at which the protoplanet nuclei will attract particles by gravitation attraction.Formula taken from
    * "III. Experimental Simulation, section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". It was originally chosen
    * because of its simplicity and its a reasonable approximation to certain limits derived from the restricted three body problem.
    *
    * @note equivalent of ra + xa in dole's paper.
    * @note Burdick uses it as part of his equivalent of [[outerBandLimit]] in accrete/starform, additionally he does not reduce the mass using the mu function.
    * @note Burke uses it as part of his equivalent of [[outerBandLimit]] in starform, he only sometimes reduces the mass using the mu function.
    * @note Keris uses it as part of his equivalent of [[outerBandLimit]] in starform.
    * @note Other versions that don't use two separate methods explicitly, use a method called Reach to calculate the gravitational pull separately.
    * @note unit of return value is AU.
    *
    * @see figure 6, p. 19 , Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method OuterEffectLimit, line 74 in DoleParams.java - Ian Burrell (accrete)
    * @see method Reach, line 129 / method EvolvePlanet, lines 368-370 in Dole.c - Andrew Folkins (accretion)
    * @see method Reach, line 139 / method EvolvePlanet, lines 447-449 in dole.c - Keris (accretion v1)
    * @see method Reach, line 234 / method EvolvePlanet, lines 538-540 in dole.cc - Keris (accretion v2)
    *
    * @param aphelion the furthest distance between the body and its host star in AU.
    * @param mass the mass of the body in solar mass (M?).
    * @return the aphelion + the gravitational pull distance in AU.
    */
  def outerGravLimit(aphelion: Double, mass: Double): Double = aphelion * (1.0 + muMassFunction(mass))


  /**
    * Method is used to calculate the outer distance at which the protoplanet nuclei will attract particles by gravitation attraction.
    *
    * @note unit of return value is AU.
    *
    * @see [[outerGravLimit]] above for more info.
    *
    * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
    * @param ecc - the eccentricity of the planetary body's orbit
    * @param mass the mass of the body in solar mass (M?).
    * @return the closest distance between the body and its host star in AU.
    */
  def outerGravLimit(axis: Double, ecc: Double, mass: Double): Double = outerGravLimit(aphelionDistance(axis, ecc), mass)

  /**
    * Method is used to calculate the inner distance at which the protoplanet nuclei will attract particles by gravitation attraction, accounting for the dust
    * cloud's eccentricity.Formula taken from figure 6, p. 19 in "III. Experimental Simulation, section c) Aggregation" of "Formation of Planetary Systems by
    * Aggregation: A Computer Simulation".
    *
    * @note equivalent of (rp - xp)/(1.0 + W) in dole's paper.
    * @note unit of return value is AU.
    *
    * @see pp. 19-20 , Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method InnerSweptLimit, line 78 in DoleParams.java - Ian Burrell (accrete)
    * @see method inner_effect_limit, line 62 in accrete.c - Mat Burdick (accrete)
    * @see method swept_mass, line 240 in Dole.c - Andrew Folkins (accretion)
    * @see method swept_mass, line 296 in dole.c - Keris (accretion v1)
    * @see method swept_mass, line 374 in dole.cc - Keris (accretion v2)
    * @see method inner_effect_limit, line 85 in accrete.c - Keris (starform)
    * @see method inner_effect_limit, line 62 in accrete.c - Mat Burdick (starform)
    * @see method inner_reduced_limit, line 83 in   Protoplanet.java - Carl Burke (starform)
    *
    * @param innerGravLimit  the perihelion - the gravitational pull distance in AU.
    * @return The inner bound of the protoplanet's ability to accrete in AU.
    */
  def innerBandLimit(innerGravLimit: Double): Double = innerGravLimit / (1.0 + aConst.CLOUD_ECCENTRICITY)

  /**
    * Method is used to calculate the inner distance at which the protoplanet nuclei will attract particles by gravitation attraction, accounting for the dust
    * cloud's eccentricity.
    *
    * @note unit of return value is AU.
    *
    * @see [[innerBandLimit]] above for more information.
    *
    * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
    * @param ecc - the eccentricity of the planetary body's orbit
    * @param mass the mass of the body in solar mass (M?).
    * @return the greatest distance between the body and its host star in AU.
    */
  def innerBandLimit(axis: Double, ecc: Double, mass: Double): Double = innerBandLimit(innerGravLimit(axis, ecc, mass))


  /**
    * Method is used to calculate the outer distance  at which the protoplanet nuclei will attract particles by gravitation attraction, accounting for the dust
    * cloud's eccentricity.Formula taken from figure 6, p. 19 in "III. Experimental Simulation, section c) Aggregation" of "Formation of Planetary Systems by
    * Aggregation: A Computer Simulation".
    *
    * @note equivalent of (ra + xa)/(1.0 - W) in dole's paper.
    * @note unit of return value is AU.
    *
    * @see pp. 19-20 , Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method OuterSweptLimit, line 82 in DoleParams.java - Ian Burrell (accrete)
    * @see method outer_effect_limit, line 69 in accrete.c - Mat Burdick (accrete)
    * @see method swept_mass, lines 241 in Dole.c - Andrew Folkins (accretion)
    * @see method swept_mass, lines 297 in dole.c - Keris (accretion v1)
    * @see method swept_mass, line 375 in dole.cc - Keris (accretion v2)
    * @see method outer_effect_limit, line 91 in accrete.c - Keris (starform)
    * @see method outer_effect_limit, line 68 in accrete.c - Mat Burdick (starform)
    * @see method outer_reduced_limit, line 97 in  Protoplanet.java - Carl Burke (starform)
    *
    * @param outerGravLimit the aphelion + the gravitational pull distance in AU.
    * @return The outer bound of the protoplanet's ability to accrete
    */
  def outerBandLimit(outerGravLimit: Double): Double = outerGravLimit / (1.0 - aConst.CLOUD_ECCENTRICITY)


  /**
    * Method is used to calculate the outer distance  at which the protoplanet nuclei will attract particles by gravitation attraction, accounting for the dust
    * cloud's eccentricity.
    *
    * @note unit of return value is AU.
    *
    * @see [[outerBandLimit]] above for more information.
    *
    * @param axis - the radius of the planetary body's orbit AKA the semi-major axis in AU.
    * @param ecc - the eccentricity of the planetary body's orbit
    * @param mass the mass of the body in solar mass (M?).
    * @return the closest distance between the body and its host star in AU.
    */
  def outerBandLimit(axis: Double, ecc: Double, mass: Double): Double = outerBandLimit(outerGravLimit(axis, ecc, mass))
}
