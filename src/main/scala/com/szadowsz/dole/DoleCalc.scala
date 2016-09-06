package com.szadowsz.dole

import com.szadowsz.accrete.calc.{AccreteCalc, CollisionCalc, OrbitalCalc, PlanetesimalCalc}
import com.szadowsz.accrete.constants.AccreteConstants

/**
  * General Trait to marshall together all the calculations used in the Dole version of the program.
  *
  * @author Zakski : 06/09/2016.
  */
trait DoleCalc extends AccreteCalc with PlanetesimalCalc with OrbitalCalc with CollisionCalc with AccreteConstants

