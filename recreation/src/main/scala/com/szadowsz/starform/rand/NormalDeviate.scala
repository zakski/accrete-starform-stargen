package com.szadowsz.starform.rand

import com.szadowsz.starform.rand.gen.RandGenTrait


case class NormalDeviate(mu: Double, sigma: Double) {
  private var state = new Array[Double](2)
  private var index = state.length

  def nextDouble(rand : RandGenTrait): Double = {
    index += 1
    if (index >= state.length) {
      val r = Math.sqrt(-2 * Math.log(rand.nextDouble())) * sigma
      val x = 2 * Math.PI * rand.nextDouble()
      state = Array[Double](mu + r * Math.sin(x), mu + r * Math.cos(x))
      index = 0
    }
    state(index)
  }
}