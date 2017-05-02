package com.szadowsz.starform.model.star.calc

import com.szadowsz.starform.model.star.constants.FolkinsBaseStarConst
import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.system.bodies.star.FolkinsStar

/**
  * Created on 13/04/2017.
  */
case class FolkinsStarCalc(override val sConst : FolkinsBaseStarConst) extends StarCalc[FolkinsStar] {

  protected val cumulStarCounts: Array[(Array[(Double, Int)], Int)] = computeProbabilities()

  /**
    * Compute a cumulative distribution from the values in StarCounts[][]
    * by adding up all the values, then dividing each entry in the array
    * by the total.
    */
  def computeProbabilities(): Array[(Array[(Double, Int)], Int)] = {
    val total = sConst.starCounts.foldLeft(0.0) { case (tot, r) => tot + r.foldLeft(0.0) { case (rTot, cell) => rTot + cell } }
    var cumulative = 0.0
    sConst.starCounts.map(r => r.map { cell =>
      cumulative += cell
      cumulative / total
    }.zipWithIndex
    ).zipWithIndex
  }

  def spectralClass(rand: RandGenTrait): (Char, Int, Double) = {
    val rnd = rand.nextDouble()
    val (specs, mag) = cumulStarCounts.find { case (s, _) => s.exists { case (prob, spec) => prob >= rnd } }.get
    val (_, spec) = specs.find { case (prob, spec) => prob >= rnd }.get

    val spcClass = sConst.spectralClasses(spec)
    val rnd2 = rand.nextDouble()
    val subClass = Math.min(9, Math.round(rnd2 * 10).toInt)
    // TODO check if approps
    val magnitude = sConst.MINMAG + mag + rnd2
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
        0.7 * rand.nextDouble() + 0.6;
    }
  }

  //    s->r_ecos = sqrt(s->luminosity);
  //    s->r_inner = 0.93 * s->r_ecos;
  //    s->r_outer = 1.1 * s->r_ecos;  /* approximately */
  //  }
  override def initStar(rand: RandGenTrait): FolkinsStar = {
    val (specClass,specSubClass,magnitude) = spectralClass(rand)
    val (luminosity, lumClass) = stellarLuminosity(specClass,magnitude)
    val mass = stellarMass(rand,luminosity,lumClass)
    val lifespan: Double = stellarMSLifespan(mass, luminosity)
    val age: Double = stellarAge(rand, lifespan)
    val meanHabitableRadius: Double = ecosphereRadius(luminosity)
    val innerHabitableRadius: Double = greenhouseRadius(meanHabitableRadius)
    FolkinsStar(specClass,specSubClass,lumClass,magnitude,mass, luminosity, lifespan, age, innerHabitableRadius, meanHabitableRadius)
  }
}
