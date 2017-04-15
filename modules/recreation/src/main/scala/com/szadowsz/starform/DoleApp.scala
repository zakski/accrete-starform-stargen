package com.szadowsz.starform

import java.util.Random

import com.szadowsz.starform.model.accrete.calc.insert.RandInsertStrat
import com.szadowsz.starform.profile.accrete.DoleProfile
import com.szadowsz.starform.sim.DoleSimulation
import org.slf4j.{Logger, LoggerFactory}

/**
  * A Modification of DoleAccretionTestCase. Simple Application to generate and print off planets to the logs.
  *
  * @author Zakski : 06/07/2015.
  */
object DoleApp {

  private val logger: Logger = LoggerFactory.getLogger(getClass)

  def main(args: Array[String]) {
    val acrete = DoleSimulation(new DoleProfile)
    val system = acrete.generateSystem()
    system.planets.zipWithIndex.foreach{case (pl,i) => logger.info("Planet {}: {}", i, pl)}
  }
}