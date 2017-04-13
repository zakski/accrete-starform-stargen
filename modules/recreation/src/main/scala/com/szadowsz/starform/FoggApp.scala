package com.szadowsz.starform

import java.util.Random

import com.szadowsz.starform.model.accrete.calc.insert.RandInsertStrat
import com.szadowsz.starform.profile.FoggProfile
import com.szadowsz.starform.sim.FoggSimulation
import org.slf4j.{Logger, LoggerFactory}

/**
  * A Modification of DoleAccretionTestCase. Simple Application to generate and print off planets to the logs.
  *
  * @author Zakski : 06/07/2015.
  */
object FoggApp {

  private val logger: Logger = LoggerFactory.getLogger(getClass)

  def main(args: Array[String]) {
    val starform = FoggSimulation(new FoggProfile())
    val system = starform.generateSystem(Some(1))
    system.planets.zipWithIndex.foreach{case (pl,i) => logger.info("Planet {}: {}", i, pl)}
  }
}