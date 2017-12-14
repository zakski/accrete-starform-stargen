package com.szadowsz.starform2.model.star.calc

import com.szadowsz.starform2.system.body.star.KerisStar
import com.szadowsz.starform2.model.star.consts.KerisStarConstants
import com.szadowsz.starform2.rand.RandUtil._
import com.szadowsz.starform2.rand.gen.RandGenTrait



/**
  * Created on 15/08/2017.
  */
class KerisStarCalc[C <: KerisStarConstants](c: C) extends FoggStarCalc[KerisStar, C](c) {


  def stellarRadius(rand: RandGenTrait, mass: Double): Double = {
    val rad = rand.about(Math.pow(mass, 1.0 / 3.0), 0.05)
    /* for some unknown reason, only 3 digits wanted... */
    Math.floor(rad * 1000.0) / 1000.0
  }

  /**
    * luminosity is proportional to T^4 and to area of star so temp is Tsol * 4th-root ( Lum / r^2 )
    *
    * @param luminosity
    * @param radius
    * @return
    */
  def stellarTemp(luminosity: Double, radius: Double): Double = {
    5650 * Math.sqrt(Math.sqrt(luminosity) / radius)
  }

  def findClass(temp: Double): (Char, Int) = {
    val p = c.starType.find(t => temp > t._2).get
    val index = c.starType.indexOf(p)

    /* p2 -> star class with more temp than temp */
    val p2 = c.starType(index - 1)

    val dm = p2._2 - p._2 // should be negative

    val sub = Math.floor(((p2._2 - temp) / dm) * 10).toInt
    (p2._1, sub)
  }

  override def buildStar(rand: RandGenTrait): KerisStar = {
    val mass: Double = stellarMass(rand)
    val luminosity: Double = stellarLuminosity(mass)
    val lifespan: Double = stellarMSLifespan(mass, luminosity)
    val age: Double = stellarAge(rand, lifespan)
    val meanHabitableRadius: Double = ecosphereRadius(luminosity)
    val innerHabitableRadius: Double = greenhouseRadius(meanHabitableRadius)
    val radius = stellarRadius(rand, mass)
    val temp = stellarTemp(luminosity, radius)
    val (cl, sub) = findClass(temp)
    new KerisStar(cl, sub, "V", mass, luminosity, radius, temp, lifespan, age, innerHabitableRadius, meanHabitableRadius)
  }
}
