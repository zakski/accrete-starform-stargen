package com.szadowsz.stargen.impl.dole.calc

import com.szadowsz.stargen.base.accrete.calc._
import com.szadowsz.stargen.base.accrete.constants.AccreteConstants

/**
  * General Trait to marshall together all the calculations used in the Dole version of the program.
  *
  * @author Zakski : 06/09/2016.
  */
trait DoleCalc extends AccreteCalc with PlanetesimalCalc with RandomCalc with CollisionCalc with AccreteConstants

