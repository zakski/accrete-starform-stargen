package com.szadowsz.stargen.base.accrete.util

import java.util.concurrent.atomic.AtomicLong

import java.util.Random

/**
  * 03/10/2016.
  */
object RandUtil {
  private val multiplier: Long = 0x5DEECE66DL

  def extractSeed(rand : Random): Long = {
    val rClass = rand.getClass.asInstanceOf[Class[Random]]
    val field = rClass.getDeclaredField("seed")
    field.setAccessible(true)
    val scrambledSeed = field.get(rand).asInstanceOf[AtomicLong].get()
    scrambledSeed ^ multiplier
  }
//  Random r = ...;  //this is the random you want to clone
//  long theSeed;
//  try
//  {
//
//  field.setAccessible(true);
//  AtomicLong scrambledSeed = (AtomicLong) field.get(r);   //this needs to be XOR'd with 0x5DEECE66DL
//  theSeed = scrambledSeed.get();
//  }
//  catch (Exception e)
//  {
//    //handle exception
//  }
//  Random clonedRandom = new Random(theSeed ^ 0x5DEECE66DL);

}
