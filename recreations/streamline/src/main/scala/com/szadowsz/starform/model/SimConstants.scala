// scalastyle:off method.name
package com.szadowsz.starform.model

import com.szadowsz.starform.model.accrete.AccreteConstants

/**
  * Created on 13/04/2017.
  */
case class SimConstants(
                         k: Option[Double],
                         inner: Option[Double],
                         outer: Option[Double],
                         ecc : Option[Double],
                         cloudEcc : Option[Double]
                       ) extends AccreteConstants {

  // TODO consider these for paremeterization
  //  override def DUST_DENSITY_COEFF: Double = super.DUST_DENSITY_COEFF
  //
  //  override def N: Double = super.N
  //
  //  override def ALPHA: Double = super.ALPHA
  //
  //   override def B: Double = super.B

  override def K: Double = k.getOrElse(super.K)

  override def INNERMOST_PLANET: Double = inner.getOrElse(super.INNERMOST_PLANET)

  override def OUTERMOST_PLANET: Double = outer.getOrElse(super.OUTERMOST_PLANET)

  override def ECCENTRICITY_COEFF: Double = ecc.getOrElse(super.ECCENTRICITY_COEFF)

  override def CLOUD_ECCENTRICITY: Double = cloudEcc.getOrElse(super.CLOUD_ECCENTRICITY)
}
