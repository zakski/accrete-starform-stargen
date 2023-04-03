package com.szadowsz.starform.system.bodies.folkins

import com.szadowsz.starform.system.bodies.fogg.FoggStar

/**
  * Created on 15/04/2017.
  */
class FolkinsStar(
                   specClass: Char,
                   specSubclass: Int,
                   lumClass: String,
                   mag: Double,
                   mass: Double,
                   luminosity: Double,
                   lSpan: Double,
                   exist: Double,
                   inner: Double,
                   mean: Double
                 ) extends FoggStar(mass, luminosity, lSpan, exist, inner, mean){
  /**
    * The Spectral Class of the Star.
    *
    * @note Havard System - O, B, A, F, G, K, or M - Brightest to Dimmest, based on surface temp.
    */
  val spectralClass: Char = specClass

  /**
    * The Spectral Subclass of the Star
    *
    * @note 0-9, how close it is to being in a higher Spectral class, 9 being highest.
    */
  val spectralSubclass: Int = specSubclass

  /**
    * Yerkes luminosity class.
    *
    * @note Ia, Ib, II, III, IV, V, VI or VII - Brightest to Dimmest, based on luminosity.
    */
  val luminosityClass: String = lumClass

  /**
    * Magnitude of brightness.
    *
    * @note starts at -1 magnitude. Dimmer stars are zero or positive numbers.
    */
  val magnitude: Double = mag
}
