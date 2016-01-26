package com.szadowsz.gen.accrete.fogg

import java.util.Random

import com.szadowsz.gen.accrete.base.AbstractSimulation
import com.szadowsz.gen.accrete.base.bodies.Planet
import com.szadowsz.gen.accrete.base.calc.CollisionCalc
import com.szadowsz.gen.accrete.fogg.bodies.{FoggPlanet, Star}
import com.szadowsz.gen.accrete.fogg.calc.{FoggAccrCalc, FoggPlanCalc, FoggStarCalc}
import org.slf4j.{Logger, LoggerFactory}

/**
  * Created by Zakski on 31/12/2015.
  */
class AbstractFoggSimulation(random: Random) extends AbstractSimulation(random) {
  this: FoggAccrCalc with FoggStarCalc with FoggPlanCalc with CollisionCalc with FoggConstants =>

  protected lazy val _star: Star = createStar()
  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[AbstractFoggSimulation])

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarLuminosity: Double = _star.luminosity

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarMass: Double = _star.mass

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarAge: Double = _star.age

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarEcosphereRadius: Double = _star.meanHabitableRadius

  /**
    * Convenience constant to avoid tying down the calculations to the star class
    */
  override def getStarGreenhouseRadius: Double = _star.innerHabitableRadius

  /**
    * Method to form planets by accretion
    *
    * @return head of the planet for this system
    */
  def accreteWithStar(): (Star, List[FoggPlanet]) = {
    (_star, accrete().map(_.asInstanceOf[FoggPlanet]))
  }

  /**
    * Method to form planets by accretion
    *
    * @return head of the planet for this system
    */
  override def accrete(): List[Planet] = {
    if (_planets.isEmpty) {
      _logger.info("Beginning generation of protoplanets.")
      _planets = accrete(_rand).map(p => FoggPlanet(this, p))
    }
    _planets
  }

  protected def createStar(): Star = {
    new Star(this, _rand)
  }
}
