package com.szadowsz.gen.accrete.fogg.bodies

import com.szadowsz.gen.accrete.base.bodies.{Planet, ProtoPlanet}
import com.szadowsz.gen.accrete.fogg.FoggConstants
import com.szadowsz.gen.accrete.fogg.calc.{FoggPlanCalc, FoggStarCalc}
import com.szadowsz.gen.util.unit.UnitConverter


object FoggPlanet {

  def apply(calc: FoggPlanCalc with FoggStarCalc with FoggConstants, proto: ProtoPlanet): FoggPlanet = {
    new FoggPlanet(calc, proto)
  }
}

/**
  * Class to represent an accreting proto planetary body. Uses an internal linked-list structure to maintain the
  * ordering of the protoplanets.
  *
  * @see Planetismal.java - Ian Burrell (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (starform)
  * @see Protoplanet.java - Carl Burke (starform)
  *
  * @constructor Constructor is used make all subsequent dust bands during the splitting process, in which we
  *              acknowledge dust and gas being removed from part of existing bands.
  *
  * @param calc inner limit of the dust band in AU.
  * @param proto the basic characteristics of the accreted planetary body.

  * @author Zakski : 20/07/2015.
  */
class FoggPlanet(calc: FoggPlanCalc with FoggStarCalc with FoggConstants, proto: ProtoPlanet) extends Planet(proto) {

  /**
    * the orbital zone of a planet extrapolated from "5. Planetary Characteristics" in Extra-Solar
    * Planetary Systems: A Microcomputer Simulation by Martyn J. Fogg.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    *
    * @note between 1-3, inclusive
    */
  val orbitalZone = calc.orbitalZone(axis)

  /**
    * the average radius of a planet, calculated using eq.9 in Fogg's article, although some typos
    * crop up in that eq. Originally from eq 23 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see The Internal Constitution of Planets - D. S. Kothari
    *
    * @note unit is km rather than in terms of earth.
    */
  val equatorialRadius = calc.kothariRadius(mass, isGas, orbitalZone)

  val density = calc.empiricalDensity(mass, axis, calc.getStarEcosphereRadius)

  val angularVelocity = calc.totalAngularVelocity(mass, equatorialRadius, axis, isGas, density)

  val orbitLength = calc.orbitLength(axis, mass, calc.getStarMass)

  val dayLength = calc.dayLength(angularVelocity, orbitLength, ecc)

  val gravity = calc.surfaceGravity(mass, equatorialRadius)

  val escapeVelocity = calc.escapeVelocity(gravity, equatorialRadius)

  val rmsSpeed = calc.speedRMS(calc.MOLECULAR_NITROGEN, equatorialRadius)

  val volatileGasInventory = calc.vGasInventory(mass, escapeVelocity, rmsSpeed, orbitalZone,
    calc.suffersGreenhouseEffect(axis, calc.getStarGreenhouseRadius), calc.getStarMass)

  val surfacePressure = calc.surfacePressure(volatileGasInventory, equatorialRadius, gravity_inGs)

  def gravity_inGs: Double = UnitConverter.mSec2ToGs(gravity)

  //  double molecule_weight;	/* smallest molecular weight retained*/
  //  double boil_point;		/* the boiling point of water (Kelvin)*/
  //  double albedo;		/* albedo of the planet		     */
  //  double surf_temp;   	/* surface temperature in Kelvin     */
  //  double hydrosphere;		/* fraction of surface covered	     */
  //  double cloud_cover;		/* fraction of surface covered	     */
  //  double ice_cover;		/* fraction of surface covered	     */

}
