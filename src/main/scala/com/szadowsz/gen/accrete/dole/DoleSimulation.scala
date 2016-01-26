package com.szadowsz.gen.accrete.dole

import java.util.Random

import com.szadowsz.gen.accrete.base.calc.{AccreteCalc, CollisionCalc, OrbitalCalc, PlanetesimalCalc}
import com.szadowsz.gen.accrete.base.{AbstractSimulation, AccreteConstants}
import org.slf4j.{Logger, LoggerFactory}

class DoleSimulation(random: Random, a: Option[Double], k: Option[Double], w: Option[Double]) extends AbstractSimulation(random) with AccreteCalc with
PlanetesimalCalc with OrbitalCalc with CollisionCalc with AccreteConstants {

  protected override val _logger: Logger = LoggerFactory.getLogger(classOf[DoleSimulation])

  private val _A: Option[Double] = a

  private val _K: Option[Double] = k

  private val _W: Option[Double] = w

  override def DUST_DENSITY_COEFF: Double = _A.getOrElse(super.DUST_DENSITY_COEFF)

  override def K: Double = _K.getOrElse(super.K)

  override def CLOUD_ECCENTRICITY: Double = _W.getOrElse(super.CLOUD_ECCENTRICITY)
}