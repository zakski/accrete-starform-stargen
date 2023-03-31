package com.szadowsz.starform.rand

import org.apache.commons.math3.random.JDKRandomGenerator

import java.util.Random
import java.util.concurrent.atomic.AtomicLong

/**
  * Created on 11/04/2017.
  */
class JDKRandGen extends JDKRandomGenerator with RandGenTrait with Serializable {

  private val multiplier = 0x5DEECE66DL

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

    scrambledSeed ^ multiplier
  }
}
