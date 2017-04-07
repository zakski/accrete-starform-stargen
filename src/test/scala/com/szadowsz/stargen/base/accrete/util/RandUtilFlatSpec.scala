package com.szadowsz.stargen.base.accrete.util

import org.scalatest.{FlatSpec, Matchers}

import java.util.Random

/**
  * 03/10/2016.
  */
class RandUtilFlatSpec extends FlatSpec with Matchers {

  behavior of "The RandUtil Object"

  it should "extract the seed from a fresh Random instance" in {
    val seed = 1L
    val rand = new Random(seed)

    val result = RandUtil.extractSeed(rand)
    result should be (seed)
  }

  it should "extract a maximum of 48 bits for a seed from a fresh Random instance" in {
    val seed = Long.MaxValue
    val rand = new Random(seed)
    val mask: Long = (1L << 48) - 1

    val result = RandUtil.extractSeed(rand)
    result should be < seed
    result should be (seed & mask)
  }

  it should "extract a different seed from a used Random instance" in {
    val seed = 1L
    val rand = new Random(seed)
    rand.nextDouble()

    val result = RandUtil.extractSeed(rand)
    result should not be seed
  }
}
