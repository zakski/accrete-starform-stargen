package com.szadowsz.gen.accrete.fogg.calc

import com.szadowsz.gen.accrete.base.calc.{OrbitalCalc, PlanetesimalCalc}
import com.szadowsz.gen.accrete.fogg.FoggConstants
import com.szadowsz.gen.util.unit.UnitConverter

/**
  * @author Zakski : 21/07/2015.
  */
trait FoggPlanCalc extends PlanetesimalCalc {
  this: OrbitalCalc with FoggStarCalc with FoggConstants =>

  /**
    * function to calculate the orbital zone of a planet extrapolated from "5. Planetary Characteristics" in Extra-Solar
    * Planetary Systems: A Microcomputer Simulation by Mat Burdick.
    *
    * @note range of 1-3
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method orb_zone, line 28 in enviro.c_1998-06-04 - Mat Burdick (accrete)
    * @see method orb_zone, line 28 in enviro.c - Mat Burdick (starform)
    * @see method orb_zone, line 272 in Star.java - Carl Burke (starform)
    *
    * @param axis mean habitable radius in AU.
    * @return a value between 1 and 3
    */
  def orbitalZone(axis: Double): Int = {
    if (axis < (4.0 * Math.sqrt(getStarLuminosity))) {
      1
    } else if (axis < (15.0 * Math.sqrt(getStarLuminosity))) {
      2
    } else {
      3
    }
  }

  /**
    * function to calculate the radius of a planet, listed as eq.9 in Fogg's article, although some typos
    * crop up in that eq. Taken from eq 23 in "The Internal Constitution of Planets", by Dr. D. S. Kothari.
    *
    * @note unit is km.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see The Internal Constitution of Planets - D. S. Kothari
    * @see method orb_zone, line 28 in enviro.c_1998-06-04 - Mat Burdick (accrete)
    * @see method orb_zone, line 28 in enviro.c - Mat Burdick (starform)
    * @see method orb_zone, line 272 in Star.java - Carl Burke (starform)
    *
    * @param mass the planetary mass
    * @param isGiant if the planet is considered a gas giant.
    * @param zone the orbital zone.
    * @return radius of the planet in km.
    */
  def kothariRadius(mass: Double, isGiant: Boolean, zone: Int): Double = {
    val atomic = zone match {
      case 1 => if (isGiant) (9.5, 4.5) else (15.0, 8.0)

      case 2 => if (isGiant) (2.47, 2.0) else (10.0, 5.0)

      case _ => if (isGiant) (7.0, 4.0) else (10.0, 5.0)
    }

    val atomic_weight = atomic._1
    val atomic_num = atomic._2

    var temp = atomic_weight * atomic_num
    temp = (2.0 * BETA * Math.pow(EARTH_MASS_IN_GRAMS, 1.0 / 3.0)) / (A1 * Math.pow(temp, 1.0 / 3.0))

    var temp2 = A2 * Math.pow(atomic_weight, 4.0 / 3.0) * Math.pow(EARTH_MASS_IN_GRAMS, 2.0 / 3.0)
    temp2 = temp2 * Math.pow(mass, 2.0 / 3.0)
    temp2 = temp2 / (A1 * atomic_num * atomic_num)
    temp2 = 1.0 + temp2

    temp /= temp2
    temp *= Math.pow(mass, 1.0 / 3.0) / CM_PER_KM

    temp
  }

  /**
    * Empirically determine density based on distance from primary. listed as eq. 10 in Fogg's article.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method orb_zone, line 28 in enviro.c_1998-06-04 - Mat Burdick (accrete)
    * @see method orb_zone, line 28 in enviro.c - Mat Burdick (starform)
    * @see method orb_zone, line 272 in Star.java - Carl Burke (starform)

    * @param mass planet mass in solar Mass.
    * @param axis Semi-major axis of orbit in AU
    * @param ecosphere mean habitable radius in AU.
    * @return Density in grams per cubic centimeter
    */
  def empiricalDensity(mass: Double, axis: Double, ecosphere: Double): Double = {
    val mass_in_em = UnitConverter.solarMassToEarthMass(mass) // convert to be in terms of the mass of earth
    val temp = Math.pow(mass_in_em, 1.0 / 8.0)
    temp * Math.pow(ecosphere / axis, 0.25) * 5.5
  }

  /**
    * function to determine the total angular velocity of a planet. uses eq. 12 and 13 in Fogg's article. Derived from
    * an empirical calculation on page 46 of Habitable Planets For Man and an analysis by Goldreich and Soter.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see Habitable Planets For Man - Stephen H. Dole
    * @see Q in the Solar System - Goldreich and Soter
    * @see method day_length, line 195 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 195 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 515 in Planet.java - Carl Burke (starform)

    * @param mass Mass in Solar Mass.
    * @param radius equatorial radius in km.
    * @param axis Semi-major axis of orbit in AU.
    * @param isGiant true if it is a gas giant, false otherwise
    * @param density planetary density.
    * @return current angular momentum of the newly formed planet
    */
  def totalAngularVelocity(mass: Double, radius: Double, axis: Double, isGiant: Boolean, density: Double): Double = {
    val mass_in_g = UnitConverter.solarMassToGrams(mass)
    val radius_in_cm = UnitConverter.kmToCm(radius)
    val delta = deltaAngularVelocity(mass_in_g, radius_in_cm, axis, density) * getStarAge
    baseAngularVelocity(mass_in_g, radius_in_cm, isGiant) + delta
  }

  /**
    * function to empirically determine the base angular velocity of a planet. listed as eq. 12 in Fogg's article. Derived from
    * an empirical calculation on page 46 of Habitable Planets For Man.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see Habitable Planets For Man - Stephen H. Dole
    * @see method day_length, line 195 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 195 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 515 in Planet.java - Carl Burke (starform)

    * @param mass_in_grams Mass in grams.
    * @param radius_in_cm equatorial radius in cm.
    * @param isGiant true if it is a gas giant, false otherwise.
    * @return initial angular momentum of the newly formed planet
    */
  def baseAngularVelocity(mass_in_grams: Double, radius_in_cm: Double, isGiant: Boolean): Double = {
    val k2 = if (isGiant) K2_GIANT else K2_TERRESTRIAL / 2.0
    Math.sqrt(J * mass_in_grams / (k2 * Math.pow(radius_in_cm, 2)))
  }

  /**
    * function to empirically determine the decrease in angular velocity of a planet based on the age of the
    * central star. listed as eq. 13 in Fogg's article. Derived from an analysis by Goldreich and Soter.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see Q in the Solar System - Goldreich and Soter
    * @see method day_length, line 195 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 195 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 515 in Planet.java - Carl Burke (starform)

    * @param mass_in_grams Mass in grams.
    * @param radius_in_cm equatorial radius in cm.
    * @param axis Semi-major axis of orbit in AU.
    * @param density planetary density.
    * @return the decrease in angular momentum of the body based on the age of the central star.
    */
  def deltaAngularVelocity(mass_in_grams: Double, radius_in_cm: Double, axis: Double, density: Double): Double = {
    val densityRatio = density / EARTH_DENSITY
    val radiusRatio = radius_in_cm / EARTH_RADIUS_IN_CM
    val massRatio = EARTH_MASS_IN_GRAMS / mass_in_grams
    val stellarMassRatio = Math.pow(getStarMass, 2.0)
    val orbitalRatio = 1.0 / Math.pow(axis, 6.0)
    CHANGE_IN_EARTH_ANG_VEL * densityRatio * radiusRatio * massRatio * stellarMassRatio * orbitalRatio
  }

  /**
    * function to determine the length of the orbit of a small body around a large body sun in hours. Though orbit length is used by
    * Fogg he doesn't explicitly mention how he calculates it so we take a leaf out of Mat Burdick's code and use a
    * derivation of Kepler's 3rd law, for when the orbiting body has a non-negligible mass.
    *
    * @note If using units of AU and Solar Mass, we can ignore the 4 *pi^2^ / G part of the equation and the result is
    *       in earth years.
    * @note the unit is earth days.
    *
    * @see method period, line 168 in enviro.c - Mat Burdick (accrete)
    * @see method period, line 168 in enviro.c - Mat Burdick (starform)
    * @see method period, line 486 in Planet.java - Carl Burke (starform)

    * @param smallMass small body mass in Solar Mass. Typically the Planet.
    * @param largeMass larger body mass in Solar Mass. Typically the Sun.
    * @param axis Semi-major axis of orbit in AU.
    * @return Orbit length in Earth Days.
    */
  def orbitLength(axis: Double, smallMass: Double, largeMass: Double): Double = {
    Math.sqrt(Math.pow(axis, 3) / (smallMass + largeMass)) * DAYS_IN_A_YEAR
  }

  def dayLength(angularVelocity: Double, orbitLength: Double, ecc: Double): Double = {
    val dayLength = UnitConverter.radSecToHoursPerRotation(angularVelocity)
    val orbitInHours = orbitLength * HOURS_PER_DAY

    if (dayLength >= orbitInHours) {
      val resonance = spinResonancePeriod(ecc)
      resonance * orbitInHours
    } else {
      dayLength
    }
  }

  /**
    * function to empirically determine the decrease in angular velocity of a planet based on the age of the
    * central star. listed as part of eq. 12 in Fogg's article. Derived from an empirical calculation on page 46 of Habitable
    * Planets For Man.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see Habitable Planets For Man - Stephen H. Dole
    * @see method day_length, line 195 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 195 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 515 in Planet.java - Carl Burke (starform)

    * @param ecc Mass in grams
    * @return the resonance
    */
  def spinResonancePeriod(ecc: Double): Double = {
    (1.0 - ecc) / (1.0 + ecc)
  }

  /**
    * method to calculate Surface gravity using Newton's Law of Gravitation.
    *
    * @note unit is m / sec^2^.

    * @see Habitable Planets For Man - Stephen H. Dole
    * @see method acceleration, line 319 in enviro.c - Mat Burdick (accrete)
    * @see method acceleration, line 317 in enviro.c - Mat Burdick (starform)
    * @see method acceleration, line 649 in Planet.java - Carl Burke (starform)
    *
    * @param mass the mass of the planet in solar mass.
    * @param radius the radius of the planet in kilometers.
    * @return surface gravity of the planet in m per sec squared.
    */
  def surfaceGravity(mass: Double, radius: Double): Double = {
    val massInKG = UnitConverter.solarMassToKilograms(mass)
    val radInMeters = UnitConverter.kmToM(radius)
    (GRAV_CONSTANT * massInKG) / Math.pow(radInMeters, 2)
  }


  /**
    * This is Fogg's eq.15. It is used as part of the equation to determine whether the planetary body is capable of
    * retaining an atmosphere.
    *
    * It is known as the Root- Mean-Square-Speed formula. Root-mean-square speed is the measure
    * of the speed of particles in a gas that is most convenient for problem solving within the kinetic theory of
    * gases. It is defined as the square root of the average velocity-squared of the molecules in a gas.
    *
    * @note unit is km / sec.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see Habitable Planets For Man - Stephen H. Dole
    * @see method rms_vel, line 285 in enviro.c - Mat Burdick (accrete)
    * @see method rms_vel, line 282 in enviro.c - Mat Burdick (starform)
    * @see method rms_vel, line 612 in Planet.java - Carl Burke (starform)
    *
    * @param surfaceGravity surface gravity of the planet in m / sec^2^.
    * @param radius the radius of the planet in kilometers.
    * @return escape velocity of the planet in km per sec.
    */
  def escapeVelocity(surfaceGravity: Double, radius: Double): Double = {
    val grav = UnitConverter.mToKm(surfaceGravity)
    Math.sqrt(2.0 * grav * radius)
  }


  /**
    * This is Fogg's eq.16. It is used as part of the equation to determine whether the planetary body is capable of
    * retaining an atmosphere.
    *
    * It is known as the Root- Mean-Square-Speed formula. Root-mean-square speed is the measure of the speed of
    * particles in a gas that is most convenient for problem solving within the kinetic theory of gases. It is defined
    * as the square root of the average velocity-squared of the molecules in a gas.
    *
    * @note unit is km / sec.
    * @note Modified from Fogg eq. 16 to use Molar Gas Constant variant.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method rms_vel, line 285 in enviro.c - Mat Burdick (accrete)
    * @see method rms_vel, line 282 in enviro.c - Mat Burdick (starform)
    * @see method rms_vel, line 612 in Planet.java - Carl Burke (starform)
    *
    * @param molecularWeight kg per mole of the molecule, we use N2(Nitrogen) as ours.
    * @param orbitalRadius used to calculate a value for the exospheric temperature.
    * @return root mean square velocity of the molecule in the exosphere.
    */
  def speedRMS(molecularWeight: Double, orbitalRadius: Double): Double = {
    val exosphericTemp = EARTH_EXOSPHERE_TEMP / Math.pow(orbitalRadius, 2) // in kelvin
    Math.sqrt((3.0 * MOLAR_GAS_CONST * exosphericTemp) / molecularWeight)
  }


  /**
    * Quick check to see if a planet suffers from a runnaway greenhouse effect
    *
    * @see method greenhouse, line 346 in enviro.c - Mat Burdick (accrete)
    * @see method grnhouse, line 344 in enviro.c - Mat Burdick (starform)
    *
    * @param orbit semi-major axis in AU.
    * @param greenhouse greenhouse radius in AU.
    * @return true if there is a runnaway greenhouse effect, false otherwise
    */
  def suffersGreenhouseEffect(orbit: Double, greenhouse: Double): Boolean = {
    if (orbit < greenhouse) true else false
  }


  /**
    * Calculates the volatile gas inventory of the planet.Uses Fog's assumption that the initial inventory is directly
    * proportional to the mass of the planet and inversely proportional to the mass of the central star. This is taken
    * from Fogg's equation 17.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method vol_inventory, line 361 in enviro.c - Mat Burdick (accrete)
    * @see method vol_inventory, line 359 in enviro.c - Mat Burdick (starform)
    * @see method vol_inventory, line 692 in Planet.java - Carl Burke (starform)
    *
    * @param mass planetary mass in terms of solar mass.
    * @param escapeVel velocity required to escaped planet's gravity
    * @param rmsVel root mean square speed of escaping molecules
    * @param zone the zone the planet is classified within (1-3)
    * @param isGE true if the planet is too close to the sun, false otherwise (Greenhouse Effect)
    * @param stellarMass mass of the central star in terms of solar mass.
    * @return volatile gas inventory.
    */
  def vGasInventory(mass: Double, escapeVel: Double, rmsVel: Double, zone: Int, isGE: Boolean, stellarMass: Double): Double = {
    val velocity_ratio = escapeVel / rmsVel
    if (velocity_ratio >= GAS_RETENTION_THRESHOLD) {
      val q = zone match {
        case 1 => 100000.0
        case 2 => 75000.0
        case 3 => 250.0
      }
      val massInEM = UnitConverter.solarMassToEarthMass(mass) // equation calls for earth mass.
      val temp1 = (q * massInEM) / stellarMass
      val temp2 = temp1 //about(temp1, 0.2)
      if (isGE) {
        temp2
        // matt and everyone that follows him applies this to all planets outside the greenhouse zone unlike fogg.
      } else if (zone == 1) {
        temp2 / 100.0
      } else {
        temp2
      }
    } else {
      0.0
    }
  }


  /**
    * This implements Fogg's eq.18.  The pressure returned is in units of millibars (mb).  The gravity is in units
    * of Earth gravities.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method pressure, line 404 in enviro.c - Mat Burdick (accrete)
    * @see method pressure, line 401 in enviro.c - Mat Burdick (starform)
    * @see method pressure, line 736 in Planet.java - Carl Burke (starform)
    *
    * @param vGas the volatile gas inventory.
    * @param radius the radius of the planet in kilometers.
    * @param gravity the gravity of the planet in terms of earth gs.
    * @return pressure in units of millibars (mb).
    */
  def surfacePressure(vGas: Double, radius: Double, gravity: Double): Double = {
    val equatorialRadius = radius / EARTH_RADIUS_IN_KM
    vGas * gravity / Math.pow(equatorialRadius, 2)
  }

  /**
    * This is Fogg's eq.19, intended to calculate the effective surface temperature in Kelvin.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method pressure, line 511 in enviro.c - Mat Burdick (accrete)
    * @see method pressure, line 509 in enviro.c - Mat Burdick (starform)
    * @see method pressure, line 836 in Planet.java - Carl Burke (starform)
    *
    * @param ecosphereRadius the mean habitable radius for the parent star in AU.
    * @param orbitalRadius the orbiting axis of the planet in AU.
    * @param albedo the albedo of the planet.
    * @return the effective surface temperature in kelvin.
    */
  def effectiveTemperature(ecosphereRadius: Double, orbitalRadius: Double, albedo: Double): Double = {
    Math.sqrt(ecosphereRadius / orbitalRadius) * Math.pow((1.0 - albedo) / 0.7, 0.25) * EARTH_EFFECTIVE_TEMP
  }

  //
  //  /*--------------------------------------------------------------------------*/
  //  /*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
  //  /*  Earth's Atmosphere" article.  The effective temperature given is in     */
  //  /*  units of Kelvin, as is the rise in temperature produced by the          */
  //  /*  greenhouse effect, which is returned.                                   */
  //  /*--------------------------------------------------------------------------*/
  /**
    *
    *
    * @param opticalDepth
    * @param effectiveTemp the current effective suface temperature in dgerees kelvin.
    * @param surfacePressure the atmosphere pressure in millibars.
    * @return the rise in temperature produced by the greenhouse effect in degrees kelvin.
    */
  def greenhouseEffectDelta(opticalDepth: Double, effectiveTemp: Double, surfacePressure: Double): Double = {
    val convection_factor = EARTH_CONVECTION_FACTOR * Math.pow(surfacePressure / EARTH_SURF_PRES_IN_MILLIBARS, 0.25)
    (Math.pow(1.0 + 0.75 * opticalDepth, 0.25) - 1.0) * effectiveTemp * convection_factor;
  }

  /**
    * Method to calculate whether a protoplanet has gained enough mass to accrete gas as well as dust, see "c)
    * Aggregation" in "Formation of Planetary Systems by Aggregation: A Computer Simulation". Modified by Fogg in eq. 7
    * to take solar luminosity into account.
    *
    * @see Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    *
    * @param perihelion closest protoplanet gets to the sun.
    * @return critical mass in solar mass.
    */
  override def criticalMass(perihelion: Double): Double = B * Math.pow(perihelion * Math.sqrt(getStarLuminosity), -0.75)

  //  def isIterative(isGasGiant: Boolean, vGasInventory: Double, greenhouseRadius: Double, axis: Double,
  //                  ecoRadius: Double): Boolean = {
  //    vGasInventory > 0 && !isGasGiant && axis > greenhouseRadius && axis < ecoRadius * 4
  //  }
}
