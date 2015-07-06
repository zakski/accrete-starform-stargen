package com.szadowsz.accrete.base

import java.util.Random

import com.szadowsz.accrete.base.bodies.ProtoPlanet
import com.szadowsz.accrete.base.calc.AccreteCalc
import com.szadowsz.accrete.base.constants.AccreteConstants
import com.szadowsz.accrete.base.process.AccretionProcess
import org.slf4j.{Logger, LoggerFactory}

object DoleAccretionTestCase {

  private val _logger: Logger = LoggerFactory.getLogger(classOf[DoleAccreteTest])

  def main(args: Array[String]) {
    generate(new Random(1))
  }

  def generate(rand: Random): Unit = {
    val accrete: AccretionProcess = new DoleAccreteTest(rand)
    val innermost = accrete.generate()
    val planetCount = accrete.getPlanetCount

    var plan: ProtoPlanet = innermost
    for (count <- 0 until planetCount) {
      _logger.info("Planet {}: {}", count, plan.toString)
      plan = plan.next.orNull
    }
  }

  class DoleAccreteTest(rand: Random) extends AccretionProcess(rand) with AccreteCalc with calc.PlanetaryCalc with AccreteConstants {
  }

}