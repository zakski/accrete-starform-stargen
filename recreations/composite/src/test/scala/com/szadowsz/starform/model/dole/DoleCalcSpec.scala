package com.szadowsz.starform.model.dole

import com.szadowsz.starform.sim.calc.accrete.AccreteCalc
import com.szadowsz.starform.sim.calc.planetismal.PlanetismalCalc
import com.szadowsz.starform.sim.constants.AccreteConstants
import com.szadowsz.starform.sim.constants.dole.DoleConstants
import org.scalatest.flatspec.*
import org.scalatest.matchers.should.*

/**
  * Tests to make sure that a (1.0,1.0) Star in Fogg's equations is functionally equivalent to Dole's equations, so that we may collapse the two variations
  * in the Composite module.
  *
  * Created on 09/08/2017.
  */
class DoleCalcSpec extends AnyFlatSpec with Matchers {

  val aConst : AccreteConstants = new DoleConstants

  val pCalc : PlanetismalCalc = PlanetismalCalc(aConst)

  val acrete: AccreteCalc = AccreteCalc(pCalc,aConst)


  /**
    * Method to calculate dust cloud density at a given radius. Formula taken from "III. Experimental Simulation section a) Initial Conditions in the Cloud" in
    * "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @note formula is updated for Starform in [[AccreteCalc]]
    *
    * @see p. 14, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see method DustDensity, line 96 in DoleParams.java - Ian Burrell (accrete)
    * @see method distribute_planetary_masses, line 417 in accrete.c - Mat Burdick (accrete)
    * @see method Density, line 122 in Dole.c - Andrew Folkins (accretion)
    * @see method Density, line 132 in dole.c - Keris (accretion v1)
    * @see method Density, line 217 in dole.cc - Keris (accretion v2)
    * @see method dist_planetary_masses, line 449 in accrete.c - Keris (starform)
    * @see method dist_planetary_masses, line 419 in accrete.c - Mat Burdick (starform)
    * @see method dist_planetary_masses, line 154 in  Star.java - Carl Burke (starform)
    *
    * @param radius - the current distance from the stellar mass in AU
    * @return Dust density at that radius of the cloud
    */
  def dustDensity(radius: Double): Double = aConst.DUST_DENSITY_COEFF * Math.exp(-aConst.ALPHA * Math.pow(radius, 1.0 / aConst.N))


  /**
    * Method to calculate whether a planetesimal has gained enough mass to accrete gas as well as dust, see "III. Experimental Simulation, section c)
    * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation".
    *
    * @note formula is updated for Starform in [[PlanetesimalCalc]]
    * @note unit of return value is solar mass.
    *
    * @see bottom of p. 21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see figure (7), p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method CriticalMass, line 29 in DoleParams.java - Ian Burrell (accrete)
    * @see method critical_limit, line 257 in accrete.c - Mat Burdick (accrete)
    * @see method EvolvePlanet, line 359 in Dole.c - Andrew Folkins (accretion)
    * @see method EvolvePlanet, line 435 in dole.c - Keris (accretion v1)
    * @see method EvolvePlanet, line 526 in dole.cc - Keris (accretion v2)
    * @see method critical_limit, line 283 in accrete.c - Keris (starform)
    * @see method critical_limit, line 256 in accrete.c - Mat Burdick (starform)
    * @see method critical_limit, line 243 in  Star.java - Carl Burke (starform)
    *
    * @param perihelion closest the planetesimal gets to the sun in AU.
    * @return critical mass in solar mass.
    */
  def criticalMass(perihelion: Double): Double = aConst.B * Math.pow(perihelion, -0.75)


  behavior of "No Star vs Earth Star"

  it should "have the same Dust Density" in {
    acrete.dustDensity(1.0,1.0) should be (dustDensity(1.0))
  }

  it should "have the same Critical Mass" in {
    pCalc.criticalMass(1.0,1.0) should be (criticalMass(1.0))
  }
}
