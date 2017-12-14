package com.szadowsz.starform2.rand.gen

import org.apache.commons.math3.random.AbstractRandomGenerator

object GilhamRandGen {

 private val I216 = 65536
}

/**
  * linear congruential random numbers - algorithm as per VMS MTH$RANDOM function
  *
  * Created on 11/04/2017.
  */
class GilhamRandGen extends AbstractRandomGenerator with RandGenTrait {

  private var seed: Long = 50957

  def this(seed : Long) ={
    this()
    setSeed(seed)
  }

  def this(seed: Int) ={
    this()
    setSeed(seed.toLong)
  }

  def this(seed: Array[Int]) = {
    this()
    setSeed(seed)
  }

  override def setSeed(nseed: Long): Unit = {
    seed = nseed
  }

  override def nextDouble(): Double = {
    // linear congruential pseudo random numbers
    // seed -> (1+seed*69069) % (2^32)
    var high = seed / GilhamRandGen.I216
    var low = seed - (high * GilhamRandGen.I216)
    var temp = low

    // split into two quantities of 16 bytes + overflow room
    low = (low * 3533) + 1; // 69069 = 3533+65536
    var work = low / GilhamRandGen.I216
    low = low - work * GilhamRandGen.I216 // carry high word

    // lower word + carry + 65536*low  all shifted down 1 word
    high = (high * 3533) + work + temp
    work = high / GilhamRandGen.I216
    high -= (work * GilhamRandGen.I216)
    seed = high * GilhamRandGen.I216 + low

    // extract return value
    temp = high / 256
    val x1 = temp // truncate first
    val x2 = high - temp * 256
    val x3 = low / 256; // truncate first
    ((((x3 / 256.0) + x2) / 256.0) + x1) / 256.0
  }

  override def getSeed: Long = seed
}
