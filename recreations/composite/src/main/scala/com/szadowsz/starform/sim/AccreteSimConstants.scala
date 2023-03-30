// scalastyle:off method.name
package com.szadowsz.starform.sim

import com.szadowsz.starform.sim.constants.AccreteConstants

/**
  * Created on 13/04/2017.
  */
trait AccreteSimConstants extends AccreteConstants {

  protected val aConsts: AccreteConstants

  override def DUST_DENSITY_COEFF: Double = aConsts.DUST_DENSITY_COEFF

  override def N: Double = aConsts.N

  override def ALPHA: Double = aConsts.ALPHA

  override def K: Double = aConsts.K

  override def INNERMOST_PLANET: Double = aConsts.INNERMOST_PLANET

  override def OUTERMOST_PLANET: Double = aConsts.OUTERMOST_PLANET

  override def ECCENTRICITY_COEFF: Double = aConsts.ECCENTRICITY_COEFF

  override def CLOUD_ECCENTRICITY: Double = aConsts.CLOUD_ECCENTRICITY

  override def PROTOPLANET_MASS: Double = aConsts.PROTOPLANET_MASS

   override def B: Double = aConsts.B
}
