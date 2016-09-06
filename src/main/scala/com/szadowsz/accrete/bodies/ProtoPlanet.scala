package com.szadowsz.accrete.bodies

import com.szadowsz.dole.calc.DoleCalc

/**
  * Class to represent an accreting proto planetary body. Uses an internal linked-list structure to maintain the
  * ordering of the protoplanets.
  *
  * @see Planetismal.java - Ian Burrell (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (accrete)
  * @see struct planets_record, line 4 in structs.h - Mat Burdick (starform)
  * @see Protoplanet.java - Carl Burke (starform)
  * @constructor Constructor is used make all subsequent dust bands during the splitting process, in which we
  *              acknowledge dust and gas being removed from part of existing bands.
  *
  * @param mass The mass of the body.
  * @param axis The semi-major axis of the body's orbit.
  * @param ecc The Eccentricity of the body's orbit.
  * @author Zakski : 25/06/2015.
  */
abstract class ProtoPlanet(var mass: Double, var axis: Double, var ecc: Double) extends Planetismal
