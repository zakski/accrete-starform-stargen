package com.szadowsz.starform.model.accrete.calc

import com.szadowsz.starform.model.accrete.calc.planet.PlanetesimalCalc
import com.szadowsz.starform.model.accrete.constants.AccreteConstants

/**
  * Calculations specific to the formation of the star and the dust cloud.
  *
  * @note dustDensity function was adjusted to be Fogg's Version, if running dole's simulation ensure that values representing earth's star are used to
  *       maintain parity.
  *
  * @author Zakski : 03/06/2015.
  */
case class AccreteCalc(pCalc: PlanetesimalCalc, aConst: AccreteConstants){

  /**
    * Method to calculate outer dust band edge. The Formula that this comes from is unknown, it seems to be introduced in one of the early accrete versions, but
    * I cannot see any reference to it in the research papers. In the base process, this might as well just return 200 since the solar mass is assumed to be 1.
    *
    * @note code derived from Folkins' approach to the problem simply uses a modified outer limit that we expect planets to form at.
    * @note unit of return value is AU
    *
    * @see method OuterDustLimit, line 141 in DoleParams.java - Ian Burrell (accrete)
    * @see method stellar_dust_limit, line 44 in accrete.c - Mat Burdick (accrete)
    * @see method stellar_dust_limit, line 67 in accrete.c - Keris (starform)
    * @see method stellar_dust_limit, line 44 in accrete.c - Mat Burdick (starform)
    * @see method stellar_dust_limit, line 211 in  Star.java - Carl Burke (starform)
    *
    * @param mass - the stellar mass in solar mass.
    * @return the outer radius of the cloud that we will use.
    */
  def outerDustLimit(mass: Double): Double = 200 * Math.pow(mass, 1.0 / 3.0)

  /**
    * Method to calculate dust cloud density at a given radius. Original Formula taken from "III. Experimental Simulation section a) Initial Conditions in the
    * Cloud" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". In the case of simulations (not Dole's) that use a central star that is
    * not identical to ours, we alter the Density by its mass.
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see eq. 8, p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method DustDensity, line 96 in DoleParams.java - Ian Burrell (accrete)
    * @see method distribute_planetary_masses, line 417 in accrete.c - Mat Burdick (accrete)
    * @see method Density, line 122 in Dole.c - Andrew Folkins (accretion)
    * @see method Density, line 132 in dole.c - Keris (accretion v1)
    * @see method Density, line 217 in dole.cc - Keris (accretion v2)
    * @see method dist_planetary_masses, line 449 in accrete.c - Keris (starform)
    * @see method dist_planetary_masses, line 419 in accrete.c - Mat Burdick (starform)
    * @see method dist_planetary_masses, line 154 in  Star.java - Carl Burke (starform)
    *
    * @param starMass - the mass of the central star in Solar Masses.
    * @param radius - the current distance from the stellar mass in AU
    * @return Dust density at that radius of the cloud
    */
  def dustDensity(starMass : Double, radius: Double): Double = {
    (aConst.DUST_DENSITY_COEFF * Math.sqrt(starMass)) * Math.exp(-aConst.ALPHA * Math.pow(radius, 1.0 / aConst.N))
  }

  /**
    * Method to calculate total density in situations where critical mass has been reached and the protoplanet is accreting gas as well as dust. Formula comes
    * from "III. Experimental Simulation section c) Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @see p. 21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method MassDensity, line 105 in DoleParams.java - Ian Burrell (accrete)
    * @see method collect_dust, line 223 in accrete.c - Mat Burdick (accrete)
    * @see method swept_mass, line 245 in Dole.c - Andrew Folkins (accretion)
    * @see method swept_mass, line 301 in dole.c - Keris (accretion v1)
    * @see method swept_mass, line 379 in dole.cc - Keris (accretion v2)
    * @see method collect_dust, line 249 in accrete.c - Keris (starform)
    * @see method collect_dust, line 222 in accrete.c - Mat Burdick (starform)
    * @see method mass_density, line 181 in  Star.java - Carl Burke (starform)
    *
    * @param dustDensity  - the current dust density value
    * @param criticalMass - the critical mass limit of the protoplanet
    * @param mass         - the current mass of the protoplanet
    * @return the dust and gas density
    */
  def dustAndGasDensity(dustDensity: Double, criticalMass: Double, mass: Double): Double = {
    aConst.K * dustDensity / (1.0 + Math.sqrt(criticalMass / mass) * (aConst.K - 1.0))
  }

   /**
    * Method to calculate the total volume of the dust cloud cross section the protoplanet is accreting. A Formula similar to this is alluded to in "III.
     * Experimental Simulation section c) Aggregation" from "Formation of Planetary Systems by Aggregation: A Computer Simulation", but unfortunately I have not
     * been able to discover a source on its transformation into this form earlier than the earliest of recreating simulations.
    *
    * @see bottom of p. 20, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method CollectDust, lines 189-206 in Accrete.java - Ian Burrell (accrete)
    * @see method collect_dust, lines 230-241 in accrete.c - Mat Burdick (accrete)
    * @see method swept_mass, lines 272-298 in Dole.c - Andrew Folkins (accretion)
    * @see method swept_mass, lines 330-359 in dole.c - Keris (accretion v1)
    * @see method swept_mass, lines 404-433 in dole.cc - Keris (accretion v2)
    * @see method collect_dust, lines 256-267 in accrete.c - Keris (starform)
    * @see method collect_dust, lines 229-240 in accrete.c - Mat Burdick (starform)
    * @see method collect_dust, lines 155-163 in  Star.java - Carl Burke (starform)
    *
    * @param mass   mass of closest protoplanet in Solar Mass.
    * @param axis   axis of closest protoplanet in AU.
    * @param ecc    eccentricity of closest protoplanet.
    * @param iSweep inner sweep distance of the protoplanet in AU.
    * @param oSweep outer sweep distance of the protoplant in AU.
    * @param iEdge  inner edge of the dust band in AU.
    * @param oEdge  outer edge of the dust band in AU.
    * @return volume of that portion of the dust cloud.
    */
  def bandVolume(mass: Double, axis: Double, ecc: Double,
                 iSweep: Double, oSweep: Double, iEdge: Double, oEdge: Double): Double = {

    val relativeMass = pCalc.muMassFunction(mass)
    val bandwidth: Double = oSweep - iSweep

    var outside = oSweep - oEdge
    if (outside < 0.0) outside = 0.0

    var inside = iEdge - iSweep
    if (inside < 0.0) inside = 0.0

    val width = bandwidth - outside - inside

    val term1 = 4.0 * Math.PI * axis * axis
    val term2 = term1 * relativeMass * (1.0 - ecc * (outside - inside) / bandwidth)

    term2 * width
  }

  /**
    * Method to calculate whether the Accretion Process for a protoplanet should continue, see "III. Experimental Simulation section c) Aggregation"  from
    * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @see top of p. 21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole.
    * @see method AccreteDust, line 163 in Accrete.java - Ian Burrell (accrete)
    * @see method accrete_dust, line 283 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 384 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 466 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 560 in dole.cc - Keris (accretion v2)
    * @see method accrete_dust, line 310 in accrete.c - Keris (starform)
    * @see method accrete_dust, line 282 in accrete.c - Mat Burdick (starform)
    * @see method accrete_dust, line 219 in  DustDisc.java - Carl Burke (starform)
    *
    * @param oldMass Mass of the previous iteration
    * @param newMass Mass as of this iteration
    * @return True if it is not worthwhile to continue simulation, False otherwise.
    */
  def shouldAccreteContinue(oldMass: Double, newMass: Double): Boolean = !(newMass - oldMass < 0.0001 * oldMass)
}