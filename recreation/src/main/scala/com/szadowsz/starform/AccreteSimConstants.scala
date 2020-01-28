// scalastyle:off method.name
package com.szadowsz.starform

import com.szadowsz.starform.model.accrete.AccreteConstants

/**
  * Created on 13/04/2017.
  */
case class AccreteSimConstants(
                                protected val aConsts: AccreteConstants,
                                protected val a: Option[Double] = None,
                                protected val k: Option[Double] = None,
                                protected val w: Option[Double] = None
                              ) extends AccreteConstants {

  override val DUST_DENSITY_COEFF: Double = a.getOrElse(aConsts.DUST_DENSITY_COEFF)

  override val K: Double = k.getOrElse(aConsts.K)

  override val CLOUD_ECCENTRICITY: Double = w.getOrElse(aConsts.CLOUD_ECCENTRICITY)

  override def N: Double = aConsts.N

  override def ALPHA: Double = aConsts.ALPHA

  override def INNERMOST_PLANET: Double = aConsts.INNERMOST_PLANET

  override def OUTERMOST_PLANET: Double = aConsts.OUTERMOST_PLANET

  override def ECCENTRICITY_COEFF: Double = aConsts.ECCENTRICITY_COEFF

  override def B: Double = aConsts.B
}
