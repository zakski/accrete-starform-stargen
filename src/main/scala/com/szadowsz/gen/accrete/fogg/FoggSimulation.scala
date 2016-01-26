package com.szadowsz.gen.accrete.fogg

import java.util.Random

import com.szadowsz.gen.accrete.base.calc.{CollisionCalc, OrbitalCalc}
import com.szadowsz.gen.accrete.fogg.calc.{FoggAccrCalc, FoggPlanCalc, FoggStarCalc}
import org.slf4j.{Logger, LoggerFactory}

class FoggSimulation(random: Random) extends AbstractFoggSimulation(random)
with FoggAccrCalc with FoggStarCalc with FoggPlanCalc with OrbitalCalc with CollisionCalc with FoggConstants {

  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[FoggSimulation])
}