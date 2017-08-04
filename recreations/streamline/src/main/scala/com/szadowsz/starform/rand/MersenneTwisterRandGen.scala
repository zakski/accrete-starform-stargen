package com.szadowsz.starform.rand

import org.apache.commons.math3.random.MersenneTwister

/**
  * Created on 11/04/2017.
  */
class MersenneTwisterRandGen extends MersenneTwister with RandGenTrait {

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
    val rClass = getClass.getSuperclass.asInstanceOf[Class[MersenneTwister]]
    val bytePoolField = rClass.getDeclaredField("mt")
    bytePoolField.setAccessible(true)
    val bytePool = bytePoolField.get(this).asInstanceOf[Array[Int]]

    val indexField = rClass.getDeclaredField("mti")
    indexField.setAccessible(true)
    val index = indexField.get(this).asInstanceOf[Int]
    if (index < bytePool.length) bytePool(index) else bytePool(0)
  }
}
