package com.szadowsz.starform.model.star.calc

import com.szadowsz.starform.model.star.constants.FoggBaseStarConst
import com.szadowsz.starform.rand.RandGenTrait
import com.szadowsz.starform.system.bodies.star.FoggStar

/**
  * Created on 13/04/2017.
  */
case class FoggStarCalc(override val sConst: FoggBaseStarConst) extends StarCalc[FoggStar] {

  /**
    * Method to pseudo-randomly generate the mass of a star in solar mass.
    *
    * @note The solar mass is a standard unit of mass in astronomy that is used to indicate the masses of other stars, as well as clusters, nebulae and
    *       galaxies. It is equal to the mass of the Sun, about two nonillion kilograms. As per section "2. The Microcomputer Model" in "Extra-solar Planetary
    *       Systems: A Microcomputer Simulation", we are aiming for a star of a mass between 0.6 and 1.3 solar masses.
    *
    * @see p. 502, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method generate_stellar_system, line 89 in main.c - Mat Burdick (accrete)
    * @see method generate_stellar_system, line 68 in gensys.c - Keris (starform)
    * @see method generate_stellar_system, line 81 in starform.c - Mat Burdick (starform)
    * @see constructor StarSystem, line 50 in  StarSystem.java - Carl Burke (starform)
    *
    * @param rand pseudo-random number generator interface
    * @return generated mass in terms of solar mass
    */
  def stellarMass(rand: RandGenTrait): Double = (sConst.UPPER_SOLAR_MASS - sConst.LOWER_SOLAR_MASS) * rand.nextDouble() + sConst.LOWER_SOLAR_MASS


  /**
    * Method to approximate the luminosity of a star for a given mass. See eq. 1-3 in section "3. Characteristics of The Primary Star" in Extra-solar Planetary
    * Systems: A Microcomputer Simulation.
    *
    * @note The solar luminosity, is a unit of radiant flux (power emitted in the form of photons) conventionally used by astronomers to measure the luminosity
    *       of stars. One solar luminosity is equal to the current accepted luminosity of the Sun, which is 3.839×1026 W, or 3.839×1033 erg/s. The value is
    *       slightly higher, 3.939×1026 W (equivalent to 4.382×109 kg/s or 1.9×10?16 M?/d) if the solar neutrino radiation is included as well as
    *       electromagnetic radiation. The Sun is a weakly variable star and its luminosity therefore fluctuates. The major fluctuation is the eleven-year
    *       solar cycle (sunspot cycle), which causes a periodic variation of about ±0.1%. Any other variation over the last 200–300 years is thought to be
    *       much smaller than this.
    *
    * @see p. 502 Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method luminosity, line 10 in enviro.c - Mat Burdick (accrete)
    * @see method luminosity, line 11 in accrete.c - Keris (starform)
    * @see method luminosity, line 10 in accrete.c - Mat Burdick (starform)
    * @see method LUMINOSITY, line 182 in  Star.java - Carl Burke (starform)
    *
    * @param stellarMass star's mass in terms of solar mass
    * @return star's luminosity in terms of solar luminosity
    */
  def stellarLuminosity(stellarMass: Double): Double = {
    if (stellarMass < 1.0) {
      Math.pow(stellarMass, 1.75 * (stellarMass - 0.1) + 3.325)
    } else {
      Math.pow(stellarMass, 0.5 * (2.0 - stellarMass) + 4.4)
    }
  }

  override def initStar(rand: RandGenTrait): FoggStar = {
    val mass: Double = stellarMass(rand)
    val luminosity: Double = stellarLuminosity(mass)
    val lifespan: Double = stellarMSLifespan(mass, luminosity)
    val age: Double = stellarAge(rand, lifespan)
    val meanHabitableRadius: Double = ecosphereRadius(luminosity)
    val innerHabitableRadius: Double = greenhouseRadius(meanHabitableRadius)
    new FoggStar(mass, luminosity, lifespan, age, innerHabitableRadius, meanHabitableRadius)
  }
}
