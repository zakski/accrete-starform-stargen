package com.szadowsz.accrete.fogg.process

import java.util.Random

import com.szadowsz.accrete.base.calc.CollisionCalc
import com.szadowsz.accrete.base.process.AbstractProcess
import com.szadowsz.accrete.fogg.bodies.{Planet, Star}
import com.szadowsz.accrete.fogg.calc.{FoggAccrCalc, FoggPlanCalc}
import com.szadowsz.accrete.fogg.constants.FoggConstants
import org.slf4j.{Logger, LoggerFactory}

abstract class FoggProcess(random: Random) extends AbstractProcess(random) {
  this: FoggAccrCalc with FoggPlanCalc with CollisionCalc with FoggConstants =>

  protected lazy val _star: Star = createStar()
  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[FoggProcess])
  protected var _planets: List[Planet] = List()

  /**
   * Method to form planets by accretion
   *
   * @return head of the planet for this system
   */
  def generate(): (Star, List[Planet]) = {
    if (_planets.nonEmpty) {
      (_star, _planets)
    } else {
      if (_innermost == null) {
        accrete(_rand)
      }

      var plan = _innermost
      for (count <- 0 until getPlanetCount) {
        _planets :+ new Planet(this, plan)
        plan = plan.next.orNull
      }
      (_star, _planets)
    }
  }

  protected def createStar(): Star = new Star(this, _rand)

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   *
   */
  protected override def getStarLuminosity: Double = _star.luminosity

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   */
  protected override def getStarMass: Double = _star.mass

  /**
   * Convenience constant to avoid tying down the calculations to the star class
   *
   * @todo consider better way
   */
  protected override def getStarAge: Double = _star.age
}