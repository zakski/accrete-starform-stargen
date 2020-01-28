package com.szadowsz.starform.rand

import com.szadowsz.starform.rand.gen.RandGenTrait


object RandUtil {


  implicit class RandomImprovements(r : RandGenTrait) {

    /**
      * Returns a uniformly distributed random real number between the specified
      * inner and outer bounds.
      *
      * @param inner Minimum value desired
      * @param outer Maximum value desired
      */
    def nextDouble(inner: Double, outer: Double): Double = {
      val range = Math.abs(outer - inner)
      r.nextDouble() * range + Math.min(inner,outer)
    }

    /**
      * Returns a value within a certain uniform variation
      * from the central value.
      *
      * @param value     Central value
      * @param variation Maximum (uniform) variation above or below center
      */
    def about(value: Double, variation: Double): Double = value + (value * r.nextDouble(-variation, variation))
  }
}