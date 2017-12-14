package com.szadowsz.starform2.model.accrete.calc

/**
  * Basic Calculations for Combining to planetesimals into one.
  *
  * @author Zakski : 21/07/2015.
  */
case class CollisionCalc(pCalc : PlanetesimalCalc) {

  /**
    * Convenience Method used as part of the combined eccentricity of coalescing planetesimals calculation.
    *
    * @see [[coalesceEccentricity()]] for more info.
    */
  protected def eccTerm(axis: Double, ecc: Double, mass: Double): Double = mass * Math.sqrt(axis) * Math.sqrt(1.0 - ecc * ecc)

  /**
    * Method to calculate whether two coalescing planetesimals have collided. Alluded to in  "III. Experimental Simulation section d) Coalescence of Planets"
    * in "Formation of Planetary Systems by Aggregation: A Computer Simulation", but not explicitly so I have some questions over this.
    *
    * @see bottom of p. 21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method CoalescePlanetismals, line 304 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, lines 305-322 in accrete.c - Mat Burdick (accrete)
    * @see method CheckCoalesence, lines 433-453 in Dole.c - Andrew Folkins (accretion)
    * @see method CheckCoalesence, lines 519-557 in dole.c - Keris (accretion v1)
    * @see method CheckCoalesence, lines 622-651 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, lines 332-349 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, lines 304-321 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, lines 67-84 in  Protosystem.java - Carl Burke (starform)
    *
    * @param mass1 mass of closest protoplanet in Solar Mass.
    * @param axis1 axis of closest protoplanet in AU.
    * @param ecc1  eccentricity of closest protoplanet.
    * @param mass2 mass of furthest protoplanet in Solar Mass.
    * @param axis2 axis of furthest protoplanet in AU.
    * @param ecc2  eccentricity of furthest protoplanet.
    * @return coalesced axis in AU.
    */
  def hasCollision(mass1: Double, axis1: Double, ecc1: Double, mass2: Double, axis2: Double, ecc2: Double): Boolean = {

    val dist: Double = axis2 - axis1
    val outer = pCalc.outerGravLimit(axis1, ecc1, mass1) - axis1
    val inner = axis2 - pCalc.innerGravLimit(axis2, ecc2, mass2)

    (Math.abs(dist) <= outer) || (Math.abs(dist) <= inner)
  }

  /**
    * Method to calculate the combined axis of two coalescing planetesimals. It returns the maximum value the new orbit axis can have due to the principle of
    * the conservation of energy, see "III. Experimental Simulation section d) Coalescence of Planets" in "Formation of Planetary Systems by Aggregation:
    * A Computer Simulation".
    *
    * @see pp. 22-23, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method CoalesceTwoPlanets, line 333 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, line 329 in accrete.c - Mat Burdick (accrete)
    * @see method MergePlanets, line 412 in Dole.c - Andrew Folkins (accretion)
    * @see method MergePlanets, line 500 in dole.c - Keris (accretion v1)
    * @see method MergePlanets, line 595 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, line 356 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, line 328 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, line 87 in  Protosystem.java - Carl Burke (starform)
    *
    * @param mass1 mass of first protoplanet in Solar Mass.
    * @param axis1 axis of first protoplanet in AU.
    * @param mass2 mass of second protoplanet in Solar Mass.
    * @param axis2 axis of second protoplanet in AU.
    * @return coalesced axis in AU.
    */
  def coalesceAxis(mass1: Double, axis1: Double, mass2: Double, axis2: Double): Double = (mass1 + mass2) / (mass1 / axis1 + mass2 / axis2)

  /**
    * Method to calculate the combined eccentricity of two coalescing planetesimals. It returns the value of the new eccentricity due to the principle of the
    * conservation of angular momentum, see "III. Experimental Simulation section d) Coalescence of Planets" in "Formation of Planetary Systems by Aggregation:
    * A Computer Simulation".
    *
    * @see p. 23, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method CoalesceTwoPlanets, lines 334-338 in Accrete.java - Ian Burrell (accrete)
    * @see method coalesce_planetesimals, lines 330-336 in accrete.c - Mat Burdick (accrete)
    * @see method MergePlanets, lines 413 in Dole.c - Andrew Folkins (accretion)
    * @see method MergePlanets, line 501 in dole.c - Keris (accretion v1)
    * @see method MergePlanets, line 596 in dole.cc - Keris (accretion v2)
    * @see method coalesce_planetesimals, lines 357-363 in accrete.c - Keris (starform)
    * @see method coalesce_planetesimals, lines 329-335 in accrete.c - Mat Burdick (starform)
    * @see method coalesce_planetesimals, line 88-93 in  Protosystem.java - Carl Burke (starform)
    *
    * @param mass1 mass of first protoplanet in Solar Mass.
    * @param axis1 axis of first protoplanet in AU.
    * @param ecc1  eccentricity of first protoplanet.
    * @param mass2 mass of second protoplanet in Solar Mass.
    * @param axis2 axis of second protoplanet in AU.
    * @param ecc2  eccentricity of second protoplanet.
    * @param axis3 combined axis of protoplanets in AU.
    * @return coalesced eccentricity.
    */
  def coalesceEccentricity(mass1: Double, axis1: Double, ecc1: Double, mass2: Double, axis2: Double, ecc2: Double, axis3: Double): Double = {

    val term1: Double = eccTerm(axis1, ecc1, mass1) + eccTerm(axis2, ecc2, mass2)
    val term2: Double = term1 / ((mass1 + mass2) * Math.sqrt(axis3))
    val term3: Double = 1.0 - term2 * term2

    Math.sqrt(Math.abs(term3))
  }
}
