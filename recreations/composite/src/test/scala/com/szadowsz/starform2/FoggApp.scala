package com.szadowsz.starform2

import com.szadowsz.starform2.profile.FoggProfile
import org.slf4j.{Logger, LoggerFactory}

/**
  * A Modification of DoleAccretionTestCase. Simple Application to generate and print off planets to the logs.
  *
  * @author Zakski : 06/07/2015.
  */
object FoggApp {

  private val logger: Logger = LoggerFactory.getLogger(getClass)

  def main(args: Array[String]) {
    val starform = BurdickSimulation(new FoggProfile())
    val system = starform.generateSystem(Some(1))
    logger.info(system.toString)
  }
}