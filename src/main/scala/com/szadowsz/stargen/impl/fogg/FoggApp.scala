package com.szadowsz.stargen.impl.fogg

import java.util.Random

import com.szadowsz.stargen.base.accrete.calc.insert.RandInsertStrat
import org.slf4j.{Logger, LoggerFactory}

/**
  * A Modification of DoleAccretionTestCase. Simple Application to generate and print off planets to the logs.
  *
  * @author Zakski : 06/07/2015.
  */
object FoggApp {

  private val logger: Logger = LoggerFactory.getLogger(getClass)

  def main(args: Array[String]) {
    val starform = FoggSimulation(new Random(1),new RandInsertStrat())
    val system = starform.generateSystem()
    system.planets.zipWithIndex.foreach{case (pl,i) => logger.info("Planet {}: {}", i, pl)}
  }
}