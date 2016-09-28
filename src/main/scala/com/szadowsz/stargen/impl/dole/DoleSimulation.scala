// scalastyle:off method.name
package com.szadowsz.stargen.impl.dole

import java.util.Random

import com.szadowsz.stargen.base.accrete.AccreteSimulation
import com.szadowsz.stargen.base.accrete.bodies.ProtoPlanet
import com.szadowsz.stargen.impl.dole.bodies.DolePlanet
import com.szadowsz.stargen.impl.dole.calc.DoleCalc

case class DoleSimulation(
                           override protected val rand: Random,
                           private val a: Option[Double] = None,
                           private val k: Option[Double] = None,
                           private val w: Option[Double] = None
                         ) extends AccreteSimulation with DoleCalc {

  override protected def createProtoplanet(): ProtoPlanet = {
    new DolePlanet(this, PROTOPLANET_MASS, semiMajorAxis(rand), eccentricity(rand))
  }

  override def DUST_DENSITY_COEFF: Double = a.getOrElse(super.DUST_DENSITY_COEFF)

  override def K: Double = k.getOrElse(super.K)

  override def CLOUD_ECCENTRICITY: Double = w.getOrElse(super.CLOUD_ECCENTRICITY)

}