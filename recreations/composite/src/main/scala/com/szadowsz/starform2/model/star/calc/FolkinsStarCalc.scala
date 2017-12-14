package com.szadowsz.starform2.model.star.calc

import com.szadowsz.starform2.system.body.star.FolkinsStar
import com.szadowsz.starform2.rand.gen.RandGenTrait
import com.szadowsz.starform2.model.star.consts.FolkinsStarConstants



/**
  * These calculations are taken from Andrew Folkin's codeline prior to Keris' changes to it.
  *
  * Created on 13/04/2017.
  */
case class FolkinsStarCalc(override val sConst: FolkinsStarConstants) extends StarCalc[FolkinsStar, FolkinsStarConstants] {

  /**
    *
    *
    * @see method GenStar, line 241 in genstar.cc - Folkins (accrete)
    *
    * @param rand the psuedorandom number generator
    * @return tuple of class, subclass and absolute magnitude
    */
  def spectralClassAndMag(rand: RandGenTrait): (Char, Int, Double) = {
    val rnd = rand.nextDouble()

    val (i, j) = (for {
      i <- sConst.cumulStarCounts.indices.toIterator
      j <- sConst.cumulStarCounts(i).indices.toIterator
      if sConst.cumulStarCounts(i)(j) >= rnd
    } yield (i, j)).next()

    val spcClass = sConst.spectralClasses(j)
    val rnd2 = rand.nextDouble()
    val subClass = Math.min(9, Math.round(rnd2 * 10).toInt)

    // TODO check if approps
    val magnitude = sConst.MINMAG + i + rnd2
    (spcClass, subClass, magnitude)
  }

  def stellarLuminosity(spcClass: Char, magnitude: Double): (Double, String) = {
    val lum = Math.pow(2.5118, 4.7 - magnitude)
    val lumIndex = sConst.magLumClass(sConst.spectralClasses.indexOf(spcClass)).indexWhere(l => l >= magnitude)
    (lum, sConst.luminosityClasses(lumIndex))
  }


  def stellarMass(rand: RandGenTrait, lum: Double, lumClass: String): Double = {
    lumClass match {
      case "Ia" | "Ib" | "II" | "III" =>
        /* Supergiants & giants */
        val rnd = Math.log(lum) + (rand.nextDouble() / 5.0)
        Math.exp(rnd / 3.0)
      case "IV" | "V" | "VI" =>
        /* subgiants, dwarfs, subdwarfs */
        val rnd = Math.log(lum) + 0.1 + (rand.nextDouble() / 5.0 - 0.1)
        Math.exp(rnd / 4.1)
      case "VII" =>
        /* white dwarfs */
        0.7 * rand.nextDouble() + 0.6
    }
  }

  override def buildStar(rand: RandGenTrait): FolkinsStar = {
    val (cl, sub, mag) = spectralClassAndMag(rand)
    val (lum, lumCl) = stellarLuminosity(cl, mag)
    val mass = stellarMass(rand, lum, lumCl)

    // TODO Folkins doesnt actually implement these two of Fogg's variables because he trys to generate star not on the main sequence.
    val lifespan: Double = stellarMSLifespan(mass, lum)
    val age: Double = stellarAge(rand, lifespan)

    val meanHabitableRadius: Double = ecosphereRadius(lum)
    val innerHabitableRadius: Double = greenhouseRadius(meanHabitableRadius)
    new FolkinsStar(cl, sub, lumCl, mag, mass, lum, lifespan, age, innerHabitableRadius, meanHabitableRadius)
  }
}
