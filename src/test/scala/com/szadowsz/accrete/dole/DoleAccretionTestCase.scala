package com.szadowsz.accrete.dole

import java.util.Random

import com.szadowsz.accrete.base.bodies.ProtoPlanet
import com.szadowsz.accrete.base.process.{AbstractProcess, DoleAccretion}
import org.slf4j.{Logger, LoggerFactory}

object DoleAccretionTestCase {

  private val _logger: Logger = LoggerFactory.getLogger(classOf[DoleAccretion])

  def main(args: Array[String]) {
    generate(new Random(1))
  }

  def generate(rand: Random): Unit = {
    val process: AbstractProcess = new DoleAccretion(rand)
    val innermost = process.accrete()
    val planetCount = process.getPlanetCount

    var plan: ProtoPlanet = innermost
    for (count <- 0 until planetCount) {
      _logger.info("Planet {}: {}", count, plan.toString)
      plan = plan.next.orNull
    }
  }
}