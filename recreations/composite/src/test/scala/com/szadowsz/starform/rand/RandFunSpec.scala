package com.szadowsz.starform.rand

import org.scalatest.funspec.AnyFunSpec
import org.scalatest.matchers.should.*
/**
  * 03/10/2016.
  */
class RandFunSpec extends AnyFunSpec with Matchers {

   describe("A JDKRandGen Instance") {

     it("should extract the seed from a fresh instance") {
       val seed = 1L
       val rand = new JDKRandGen(seed)

       rand.getSeed should be(seed)
     }

     it("should extract a maximum of 48 bits for a seed from a fresh instance") {
       val seed = Long.MaxValue
       val rand = new JDKRandGen(seed)
       val mask: Long = (1L << 48) - 1

       val result = rand.getSeed
       result should be < seed
       result should be(seed & mask)
     }

     it("should extract a different seed from a used instance") {
       val seed = 1L
       val rand = new JDKRandGen(seed)
       rand.nextDouble()

       rand.getSeed should not be seed
     }
   }

  describe("A MersenneTwisterRandGen Instance") {

    it("should extract the integer seed from a fresh instance") {
      val seed = 1
      val rand = new MersenneTwisterRandGen(seed)

      rand.getSeed should be(seed)
    }

    it("should extract a different seed from a used instance") {
      val seed = 1
      val rand = new MersenneTwisterRandGen(seed)
      rand.nextDouble()

      rand.getSeed should not be seed
    }
  }
}
