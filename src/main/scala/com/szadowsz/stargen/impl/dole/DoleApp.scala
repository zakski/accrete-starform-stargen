package com.szadowsz.stargen.impl.dole

import java.util.Random


import org.slf4j.{Logger, LoggerFactory}

/**
  * A Modification of DoleAccretionTestCase. Simple Application to generate and print off planets to the logs.
  *
  * @author Zakski : 06/07/2015.
  */
object DoleApp {

  private val logger: Logger = LoggerFactory.getLogger(getClass)

  def main(args: Array[String]) {
    val acrete = DoleSimulation(new Random(1))
    val planets = acrete.generate()
    planets.zipWithIndex.foreach{case (pl,i) => logger.info("Planet {}: {}", i, pl)}
  }
}