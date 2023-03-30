package com.szadowsz.starform.rand

import java.util.Random
import java.util.concurrent.atomic.AtomicLong

import org.apache.commons.math3.random.JDKRandomGenerator

/**
  * Created on 11/04/2017.
  */
class JDKRandGen extends JDKRandomGenerator with RandGenTrait {

  def this(seed : Long) ={
    this()
    setSeed(seed)
  }

  def this(seed: Int) ={
    this()
    setSeed(seed)
  }

  def this(seed: Array[Int]) = {
    this()
    setSeed(seed)
  }

  override def getSeed: Long = {
    val rClass = getClass.getSuperclass.getSuperclass.asInstanceOf[Class[Random]]
    val seedField = rClass.getDeclaredField("seed")
    seedField.setAccessible(true)
    val scrambledSeed = seedField.get(this).asInstanceOf[AtomicLong].get()

    val multField = rClass.getDeclaredField("multiplier")
    multField.setAccessible(true)
    val multiplier = multField.get(this).asInstanceOf[Long]

    scrambledSeed ^ multiplier
  }
}
