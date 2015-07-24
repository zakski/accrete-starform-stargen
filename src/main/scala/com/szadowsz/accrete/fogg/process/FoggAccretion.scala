package com.szadowsz.accrete.fogg.process

import java.util.Random

import com.szadowsz.accrete.base.calc.{CollisionCalc, OrbitalCalc}
import com.szadowsz.accrete.fogg.calc.{FoggAccrCalc, FoggPlanCalc}
import com.szadowsz.accrete.fogg.constants.FoggConstants
import org.slf4j.{Logger, LoggerFactory}

class FoggAccretion(random: Random) extends FoggProcess(random) with FoggAccrCalc with
FoggPlanCalc with OrbitalCalc with CollisionCalc with FoggConstants {

  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[FoggAccretion])
}