package com.szadowsz.accrete.base.process

import java.util.Random

import com.szadowsz.accrete.base.calc.{AccreteCalc, CollisionCalc, OrbitalCalc, PlanetesimalCalc}
import com.szadowsz.accrete.base.constants.AccreteConstants
import org.slf4j.{Logger, LoggerFactory}

class DoleAccretion(random: Random) extends AbstractProcess(random) with AccreteCalc with
PlanetesimalCalc with OrbitalCalc with CollisionCalc with AccreteConstants {

  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[DoleAccretion])
}