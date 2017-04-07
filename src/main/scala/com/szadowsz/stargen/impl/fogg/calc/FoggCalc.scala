package com.szadowsz.stargen.impl.fogg.calc

import com.szadowsz.stargen.base.accrete.calc.CollisionCalc
import com.szadowsz.stargen.base.starform.calc._
import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.constants.unit.UnitConstants
import com.szadowsz.stargen.base.starform.system.bodies.Star

/**
  * General Trait to marshall together all the calculations used in the Fogg version of the program.
  *
  * @author Zakski : 06/09/2016.
  */
trait FoggCalc[S <: Star]
  extends StarformAccrCalc[S]
    with StarformPlanCalc[S]
    with StarformRandCalc[S]
    with EcoCalc[S]
    with StarCalc[S]
    with CollisionCalc
    with StarformConstants[S]
    with UnitConstants

