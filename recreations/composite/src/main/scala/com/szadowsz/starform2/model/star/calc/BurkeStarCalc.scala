package com.szadowsz.starform2.model.star.calc

import com.szadowsz.starform2.system.body.star.BurkesStar
import com.szadowsz.starform2.model.star.consts.BurkeStarConstants
import com.szadowsz.starform2.rand.NormalDeviate
import com.szadowsz.starform2.rand.gen.RandGenTrait



/**
  * Star Generation Calculations based on Burke's Simulation.
  *
  * @param sConst Burke's Star Constants.
  *
  *               Created on 15/08/2017.
  */
case class BurkeStarCalc(override val sConst: BurkeStarConstants) extends StarCalc[BurkesStar, BurkeStarConstants] {

  /**
    * Separates stellar classification index in a tupole representation of its class and subclass.
    *
    * @see method classCode, line 102 in  Star.java - Carl Burke (starform)
    *
    * @param st numerical representation of the harvard style stellar classification code.
    * @return tuple of stellar class and subclass
    */
  def classCode(st: Int): (Char, Int) = (sConst.CLASS_CODE(st / 10 + 1), st % 10)

  /**
    * Gets the base temperature from Burke's table.
    *
    * @see constructor, line 129 in Star.java - Carl Burke (starform)
    *
    * @param st numerical representation of the harvard style stellar classification code.
    * @return base temperature value for that stellar class in Kelvin.
    */

  def baseTemp(st: Int): Double = sConst.SPECT(st)

  /**
    * Gets the temperature + some deviation.
    *
    * @see constructor, line 138 in Star.java - Carl Burke (starform)
    *
    *
    * @param rand psuedo-random generator
    * @param temp base temperature
    * @param norm normal deviation class
    * @return the stellar temperature in Kelvin.
    */
  def tempDeviate(rand: RandGenTrait, temp: Double, norm: NormalDeviate): Double = temp + (temp / 200.0) * norm.nextDouble(rand)


  /**
    * Calculate absolute visual magnitude of a main sequence star given the temperature and appropriate bolometric correction. Generated from table of stellar
    * magnitudes by fitting to a cubic curve; there are some known problems with the fit, e.g. the curve isn't steep enough at the high and low ends.
    *
    * @see method MAINSEQ, line 168 in Star.java - Carl Burke (starform)
    * @see constructor, line 129 in Star.java - Carl Burke (starform)
    *
    * @return Absolute visual magnitude
    */
  def stellarMagnitude(temp: Double, st: Int): Double = {
    val ltemp = Math.log(temp / 100.0)
    val base = sConst.A0 + sConst.A1 * ltemp + sConst.A2 * Math.pow(ltemp, 2) + sConst.A3 * Math.pow(ltemp, 3)
    base - sConst.BC(st)
  }

  /**
    * Calculates stellar luminosity based on visual magnitude.
    *
    * @see method LUMINOSITY, line 182 in Star.java - Carl Burke (starform)
    *
    * @param magnitude visual magnitude
    * @return luminosity in solar luminosity.
    */
  def stellarLuminosity(magnitude: Double): Double = Math.exp((4.7 - magnitude) / 2.5)

  /**
    * Calculates stellar mass using mass-luminosity relationship.
    *
    * @see method MASS, line 191 in Star.java - Carl Burke (starform)
    *
    * @param luminosity luminosity in solar luminosity.
    * @return mass in Solar masses.
    */
  def stellarMass(luminosity: Double): Double = Math.exp(Math.log(luminosity) / 3.5)

  /**
    * Calculates stellar radius using luminosity and temperature.
    * I [Carl] forget where I got this; maybe derived from an astronomy text?
    *
    * @return Radius in Solar radii
    */
  def stellarRadius(luminosity: Double, temperature: Double): Double = {
    Math.sqrt(luminosity) * ((6100.0 / temperature) * (6100.0 / temperature))
  }


  override def buildStar(rand: RandGenTrait): BurkesStar = {
    val code = rand.nextInt(60)
    val (cl, sub) = classCode(code)
    val bTemp = baseTemp(code)
    val mag = stellarMagnitude(bTemp, code)
    val lum = stellarLuminosity(mag)
    val mass = stellarMass(lum)
    val temp = tempDeviate(rand, bTemp, NormalDeviate(0, 1)) // TODO reuse Normal Deviate
    val msLife = stellarMSLifespan(mass, lum)
    val age = stellarAge(rand, msLife)
    val radius = stellarRadius(lum, temp)
    val mean = ecosphereRadius(lum)
    val inner = greenhouseRadius(mean)
    new BurkesStar(cl, sub, "V", mag, mass, lum, radius, temp, msLife, age, inner, mean)
  }
}