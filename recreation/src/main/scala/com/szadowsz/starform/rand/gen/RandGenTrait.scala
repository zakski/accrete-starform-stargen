package com.szadowsz.starform.rand.gen

import org.apache.commons.math3.random.RandomGenerator

/**
  * Created on 11/04/2017.
  */
trait RandGenTrait extends RandomGenerator {

  def getSeed: Long

}
