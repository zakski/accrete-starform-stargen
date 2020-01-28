// scalastyle:off method.name
package com.szadowsz.starform

import com.szadowsz.starform.model.accrete.AccreteConstants
import com.szadowsz.starform.model.accrete.insert.AccreteInsertStrat
import com.szadowsz.starform.rand.gen.RandGenTrait


/**
  * Created on 11/04/2017.
  */
abstract class AccreteProfile(a: Option[Double] = None, k: Option[Double] = None, w: Option[Double] = None) {


  protected val DUST_DENSITY_COEFF: Option[Double] = a.map(v => Math.min(3.0E-3, Math.max(v, 0.5E-3)))

  protected val K: Option[Double] = k.map(v => Math.min(100.0, Math.max(v, 10.0)))

  protected val CLOUD_ECCENTRICITY: Option[Double] = w.map(v => Math.min(0.999999, Math.max(v, 0.0)))

  protected val accConsts: AccreteConstants

  def buildRand(): RandGenTrait

  /**
    * Generates a new insertion strategy, using the Accrete Constants to specify the closest and furthest from the central star a planetismal can form.
    *
    * @param aConst the Accrete Simulation Constants
    * @return the initialised insertion strategy.
    */
  def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat

  final def buildConstants(): AccreteSimConstants = AccreteSimConstants(accConsts, DUST_DENSITY_COEFF, K, CLOUD_ECCENTRICITY)
}
