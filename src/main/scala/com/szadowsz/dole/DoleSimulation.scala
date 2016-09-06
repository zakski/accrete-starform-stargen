// scalastyle:off method.name
package com.szadowsz.dole

import java.util.Random

import com.szadowsz.accrete.AbstractSimulation

case class DoleSimulation(
                           override protected val rand: Random,
                           private val a: Option[Double] = None,
                           private val k: Option[Double] = None,
                           private val w: Option[Double] = None
                         ) extends AbstractSimulation with DoleCalc {

  override def DUST_DENSITY_COEFF: Double = a.getOrElse(super.DUST_DENSITY_COEFF)

  override def K: Double = k.getOrElse(super.K)

  override def CLOUD_ECCENTRICITY: Double = w.getOrElse(super.CLOUD_ECCENTRICITY)
}