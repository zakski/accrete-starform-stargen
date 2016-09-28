package com.szadowsz.stargen.base.starform.calc

import com.szadowsz.stargen.base.starform.constants.StarformConstants
import com.szadowsz.stargen.base.starform.constants.Atmosphere._
import com.szadowsz.stargen.base.starform.constants.unit.UnitConstants
import com.szadowsz.stargen.base.starform.util.UnitConverter


/**
  * Calculations introduced by Starform in order to postulate about the ecosystem of an accreted planet.
  *
  * @author Zakski : 11/09/2016.
  */
trait EcoCalc {
  this: StarformConstants with UnitConstants =>


  /**
    * Function to calculate the orbital zone of a planet extrapolated from "5. Planetary Characteristics" in "Extra-Solar Planetary Systems: A Microcomputer
    * Simulation" by Martyn J. Fogg.
    *
    * @note range of 1-3
    *
    * @see p.505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method kothari_radius, lines 74-113 in enviro.c - Mat Burdick (accrete)
    * @see method orb_zone, line 28 in enviro.c - Keris (starform)
    * @see method orb_zone, line 28 in enviro.c - Mat Burdick (starform)
    * @see method orb_zone, line 272 in Star.java - Carl Burke (starform)
    *
    * @param stellarLuminosity the brightness of the star.
    * @param axis              mean habitable radius in AU.
    * @return a value between 1 and 3
    */
  def orbitalZone(stellarLuminosity: Double, axis: Double): Int = {
    if (axis < (4.0 * Math.sqrt(stellarLuminosity))) {
      1
    } else if (axis < (15.0 * Math.sqrt(stellarLuminosity))) {
      2
    } else {
      3
    }
  }

  /**
    * Function to calculate the radius of a planet, listed as eq.9 in Fogg's article. Taken from eq 23 in "The Internal Constitution of Planets", by
    * Dr. D. S. Kothari.
    *
    * @note unit is km.
    *
    * @see eq. 9, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see eq. 23, p. 840, The Internal Constitution of Planets - D. S. Kothari
    * @see method kothari_radius, lines 114-122 in enviro.c - Mat Burdick (accrete)
    * @see method kothari_radius, line 68 in enviro.c - Keris (starform)
    * @see method kothari_radius, line 68 in enviro.c - Mat Burdick (starform)
    * @see method kothari_radius, line 684 in Planet.java - Carl Burke (starform)
    *
    * @param mass    the planetary mass
    * @param isGiant if the planet is considered a gas giant.
    * @param zone    the orbital zone.
    * @return radius of the planet in km.
    */
  def kothariRadius(mass: Double, isGiant: Boolean, zone: Int): Double = {
    val (atomicWeight, atomicNum) = zone match {
      case 1 => if (isGiant) (9.5, 4.5) else (15.0, 8.0)

      case 2 => if (isGiant) (2.47, 2.0) else (10.0, 5.0)

      case _ => if (isGiant) (7.0, 4.0) else (10.0, 5.0)
    }
    val numeratorP1 = (2.0 * BETA) / A1 // 1.7650695517774344
    val numeratorP2 = 1 / Math.pow(atomicWeight * atomicNum, 1.0 / 3.0)
    val numerator = numeratorP1 * numeratorP2 * Math.pow(SOLAR_MASS_IN_GRAMS, 1.0 / 3.0)

    val denominatorP1 = A2 / A1
    val denominatorP2 = Math.pow(atomicWeight, 4.0 / 3.0) / Math.pow(atomicNum, 2.0)
    val denominator = 1.0 + denominatorP1 * denominatorP2 * Math.pow(SOLAR_MASS_IN_GRAMS, 2.0 / 3.0) * Math.pow(mass, 2.0 / 3.0)

    val frac = numerator / denominator * Math.pow(mass, 1.0 / 3.0)
    UnitConverter.cmToKm(frac)
  }


  /**
    * Empirical formulae to determine density based on distance from primary. listed as eq. 10 in Fogg's article.
    *
    * @note unit is g/cm3.
    *
    * @see eq. 10, p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method empirical_density, line 131 in enviro.c - Mat Burdick (accrete)
    * @see method empirical_density, line 133 in enviro.c - Keris (starform)
    * @see method empirical_density, line 131 in enviro.c - Mat Burdick (starform)
    * @see method empirical_density, line 447 in Planet.java - Carl Burke (starform)
    *
    * @param mass      planet mass in solar Mass.
    * @param axis      Semi-major axis of orbit in AU
    * @param ecosphere mean habitable radius in AU.
    * @return Density in grams per cubic centimeter
    */
  def empiricalDensity(mass: Double, axis: Double, ecosphere: Double): Double = {
    val massInEM = UnitConverter.solarMassToEarthMass(mass) // convert to be in terms of the mass of earth
    val temp = Math.pow(massInEM, 0.125)
    temp * Math.pow(ecosphere / axis, 0.25) * 5.5
  }

  /**
    * Function to calculate the average density of a planet, listed as eq. 10 in "The Internal Constitution of Planets", by Dr. D. S. Kothari. This is used by
    * Fogg instead of [[empiricalDensity()]] once the planet has exceeded critical mass and become a gas giant. See "5. Planetary Characteristics" in
    * "Extra-Solar Planetary Systems: A Microcomputer Simulation" by Martyn J. Fogg.
    *
    * @note unit is g/cm3.
    *
    * @see p. 505, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see eq. 10, p. 838, The Internal Constitution of Planets - D. S. Kothari
    * @see method volume_density, line 151 in enviro.c - Mat Burdick (accrete)
    * @see method volume_density, line 153 in enviro.c - Keris (starform)
    * @see method volume_density, line 151 in enviro.c - Mat Burdick (starform)
    * @see method volume_density, line 467 in Planet.java - Carl Burke (starform)
    *
    * @param mass     the planetary mass in solar mass.
    * @param eqRadius Equatorial radius in kilometers.
    * @return Average density in grams per cubic centimeter.
    */
  def volumeDensity(mass: Double, eqRadius: Double): Double = {
    val massInGrams = UnitConverter.solarMassToGrams(mass)
    val eqRadiusInCM = UnitConverter.kmToCm(eqRadius)
    val volume = ((4.0 * Math.PI) / 3.0) * Math.pow(eqRadiusInCM, 3)
    massInGrams / volume
  }

  /**
    * Function to determine the length of the orbit of a small body around a large body sun in hours. Though orbit length in days is reported by Fogg he
    * doesn't explicitly mention its calculation, so we take a leaf out of Mat Burdick's code and use a derivation of Newton's version of Kepler's 3rd law,
    * for when the orbiting body has a non-negligible mass.
    *
    * @note the unit is earth days.
    *
    * @see method period, line 168 in enviro.c - Mat Burdick (accrete)
    * @see method period, line 167 in enviro.c - Keris (starform)
    * @see method period, line 168 in enviro.c - Mat Burdick (starform)
    * @see method period, line 486 in Planet.java - Carl Burke (starform)
    *
    * @param smallMass small body mass in Solar Mass. Typically the Planet.
    * @param largeMass larger body mass in Solar Mass. Typically the Sun.
    * @param axis      Semi-major axis of orbit in AU.
    * @return Orbit length in Earth Days.
    */
  def orbitLength(axis: Double, smallMass: Double, largeMass: Double): Double = Math.sqrt(Math.pow(axis, 3) / (smallMass + largeMass)) * DAYS_IN_EARTH_YEAR

  /**
    * Function to determine the approximate base angular velocity of a planet. listed as eq. 12 in Fogg's article. Derived from an empirical relationship on
    * page 46 of Habitable Planets For Man.
    *
    * @see eq. 12, p. 506, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see p. 46, Habitable Planets For Man - Stephen H. Dole
    * @see method day_length, lines 206-213 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, lines 209-218 in enviro.c - Keris (starform)
    * @see method day_length, lines 206-213 in enviro.c - Mat Burdick (starform)
    * @see method day_length, lines 531-542 in Planet.java - Carl Burke (starform)
    *
    * @param massInGrams Planetary Mass in grams.
    * @param radiusInCm  equatorial radius in cm.
    * @param isGiant     true if it is a gas giant, false otherwise.
    * @return initial angular momentum of the newly formed planet
    */
  def baseAngularVelocity(massInGrams: Double, radiusInCm: Double, isGiant: Boolean): Double = {
    val k2 = (if (isGiant) K2_GIANT else K2_TERRESTRIAL) / 2.0
    Math.sqrt(J * massInGrams / (k2 * Math.pow(radiusInCm, 2)))
  }

  /**
    * Function to empirically determine the decrease in angular velocity of a planet based on the age of the
    * central star. listed as eq. 13 in Fogg's article. Derived from an analysis by Goldreich and Soter.
    *
    * @see eq. 13, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see eq .15?, Q in the Solar System - Goldreich and Soter
    * @see method day_length, line 218 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 222 in enviro.c - Keris (starform)
    * @see method day_length, line 218 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 546 in Planet.java - Carl Burke (starform)
    *
    * @param stellarMass Mass of the Star in Solar Mass.
    * @param massInGrams Planetary Mass in grams.
    * @param radiusInCm  equatorial radius in cm.
    * @param axis        Semi-major axis of orbit in AU.
    * @param density     planetary density.
    * @return the decrease in angular momentum of the body based on the age of the central star.
    */
  def deltaAngularVelocity(stellarMass: Double, massInGrams: Double, radiusInCm: Double, axis: Double, density: Double): Double = {
    val densityRatio = density / EARTH_DENSITY
    val radiusRatio = UnitConverter.cmToEarthRadius(radiusInCm)
    val massRatio = EARTH_MASS_IN_GRAMS / massInGrams
    val stellarMassRatio = Math.pow(stellarMass, 2.0)
    val orbitalRatio = 1.0 / Math.pow(axis, 6.0)
    CHANGE_IN_EARTH_ANG_VEL * densityRatio * radiusRatio * massRatio * stellarMassRatio * orbitalRatio
  }

  /**
    * Function to determine the approximate total angular velocity of a planet. It uses eq. 12 and 13 in Fogg's article.
    *
    * @see [[baseAngularVelocity()]]
    * @see [[deltaAngularVelocity()]]
    * @see eq. 12/13, p. 506, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see p. 46, Habitable Planets For Man - Stephen H. Dole
    * @see Q in the Solar System - Goldreich and Soter
    * @see method day_length, lines 206-224 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, lines 209-228 in enviro.c - Keris (starform)
    * @see method day_length, lines 206-223 in enviro.c - Mat Burdick (starform)
    * @see method day_length, lines 531-552 in Planet.java - Carl Burke (starform)
    *
    * @param stellarMass Mass of the Star in Solar Mass.
    * @param stellarAge  Age of the Star.
    * @param mass        Mass of the planet in Solar Mass.
    * @param radius      equatorial radius in km.
    * @param axis        Semi-major axis of orbit in AU.
    * @param isGiant     true if it is a gas giant, false otherwise
    * @param density     planetary density.
    * @return current angular momentum of the newly formed planet
    */
  def totalAngularVelocity(stellarMass: Double, stellarAge: Double, mass: Double, radius: Double, axis: Double, density: Double, isGiant: Boolean): Double = {
    val massInGrams = UnitConverter.solarMassToGrams(mass)
    val radiusInCm = UnitConverter.kmToCm(radius)
    val delta = deltaAngularVelocity(stellarMass, massInGrams, radiusInCm, axis, density) * UnitConverter.byrToYears(stellarAge)
    baseAngularVelocity(massInGrams, radiusInCm, isGiant) + delta
  }

  /**
    * Function to determine the spin lock resonance period of a planet, if it has be tidally despun and it's eccentricity > 0.1
    *
    * @see eq. 14, p. 506, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method day_length, line 235 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 241 in enviro.c - Keris (starform)
    * @see method day_length, line 232 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 562 in Planet.java - Carl Burke (starform)
    *
    * @param ecc eccentricity of the planet's orbit.
    * @return the resonance
    */
  def spinResonancePeriod(ecc: Double): Double = (1.0 - ecc) / (1.0 + ecc)

  /**
    * Function to Determine the length of the Planet's day based on [[totalAngularVelocity]].
    *
    * @see method day_length, line 195 in enviro.c - Mat Burdick (accrete)
    * @see method day_length, line 193 in enviro.c - Keris (starform)
    * @see method day_length, line 195 in enviro.c - Mat Burdick (starform)
    * @see method day_length, line 515 in Planet.java - Carl Burke (starform)
    *
    * @param angVelocity the rotation rate of the planet in radians per second.
    * @param orbitLength length of the planet's orbit in years, upper bound day length.
    * @param ecc         eccentricity of the planet's orbit.
    * @return length of the planet's day in hours.
    */
  def dayLength(angVelocity: Double, orbitLength: Double, ecc: Double): (Boolean, Boolean, Double) = {
    val yearInHours = UnitConverter.daysToHours(orbitLength)

    // Now we change from rad/sec to hours/rotation.
    val (stopped, dayInHours) = if (angVelocity <= 0.0) {
      (true, 0.0)
    } else {
      (false, UnitConverter.radSecToHoursPerRotation(angVelocity))
    }

    if (stopped || (dayInHours >= yearInHours)) {
      if (ecc > 0.1) {
        (false, true, spinResonancePeriod(ecc) * yearInHours)
      } else {
        (true, false, yearInHours)
      }
    } else {
      (false, false, dayInHours)
    }
  }

  /**
    * Function to calculate surface gravity of the planet using Newton's Law of Gravitation. This version does not use the Earth as a comparison point,
    * so instead we use the gravitational constant.
    *
    * @note unit is m / sec^2^. Just like Secondary School Physics books.
    *
    * @see method acceleration, line 319 in enviro.c - Mat Burdick (accrete)
    * @see method acceleration, line 324 in enviro.c - Keris (starform)
    * @see method acceleration, line 317 in enviro.c - Mat Burdick (starform)
    * @see method acceleration, line 646 in Planet.java - Carl Burke (starform)
    *
    * @param mass   the mass of the planet in solar mass.
    * @param radius the radius of the planet in kilometers.
    * @return surface gravity of the planet in m per sec squared.
    */
  def surfaceGravity(mass: Double, radius: Double): Double = {
    val massInKG = UnitConverter.solarMassToKg(mass)
    val radInMeters = UnitConverter.kmToM(radius)
    (GRAV_CONSTANT * massInKG) / Math.pow(radInMeters, 2)
  }


  /**
    * This is Fogg's eq.15. It is used as part of the equation to determine whether the planetary body is capable of retaining an atmosphere. It is a formula
    * to find the barycentric escape velocity.
    *
    * @note unit is m / sec.
    *
    * @see eq. 15, p. 506, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method escape_vel, line 268 in enviro.c - Mat Burdick (accrete)
    * @see method escape_vel, line 290 in enviro.c - Keris (starform)
    * @see method escape_vel, line 282 in enviro.c - Mat Burdick (starform)
    * @see method escape_vel, line 612 in Planet.java - Carl Burke (starform)
    *
    * @param surfaceGravity surface gravity of the planet in m / sec^2^.
    * @param radius         the radius of the planet in kilometers.
    * @return escape velocity of the planet in km per sec.
    */
  def escapeVelocity(surfaceGravity: Double, radius: Double): Double = {
    Math.sqrt(2.0 * surfaceGravity * radius)
  }

  /**
    * This is sort of Fogg's eq.16. It is used as part of the equation to determine whether the planetary body is capable of  retaining an atmosphere. We use
    * a different equivalent formula.
    *
    * It is known as the Root- Mean-Square-Speed formula. Root-mean-square speed is the measure of the speed of particles in a gas that is most convenient
    * for problem solving within the kinetic theory of gases. It is defined as the square root of the average velocity-squared of the molecules in a gas.
    *
    * @note unit is m / sec.
    * @note Modified from Fogg eq. 16 to use Molar Gas Constant variant.
    *
    * @see eq. 16, p. 507, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method rms_vel, line 285 in enviro.c - Mat Burdick (accrete)
    * @see method rms_vel, line 290 in enviro.c - Keris (starform)
    * @see method rms_vel, line 282 in enviro.c - Mat Burdick (starform)
    * @see method rms_vel, line 612 in Planet.java - Carl Burke (starform)
    *
    * @param molecularWeight    kg per mole of the molecule, we use N2(Nitrogen) as ours.
    * @param perihelionDistance closest the planet gets to the sun, used to calculate a value for the exospheric temperature.
    * @return root mean square velocity of the molecule in the exosphere.
    */
  def speedRMS(molecularWeight: Double, perihelionDistance: Double): Double = {
    val exosphericTemp = EXOSPHERE_TEMP / Math.pow(perihelionDistance, 0.5) // in kelvin
    Math.sqrt((3.0 * MOLAR_GAS_CONST * exosphericTemp) / molecularWeight)
  }

  /**
    * Quick check to see if a planet can retain an atmosphere.
    *
    * @see p. 507, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method vol_inventory, lines 367-368 in enviro.c - Mat Burdick (accrete)
    * @see method vol_inventory, lines 372-373 in enviro.c - Keris (starform)
    * @see method vol_inventory, lines 365-366 in enviro.c - Mat Burdick (starform)
    * @see method vol_inventory, lines 698-699 in Planet.java - Carl Burke (starform)
    *
    * @param escapeVel semi-major axis in AU.
    * @param rmsVel    greenhouse radius in AU.
    * @return true if the planet can retain gas, false otherwise
    */
  def hasGasRetention(escapeVel: Double, rmsVel: Double): Boolean = escapeVel / rmsVel >= GAS_RETENTION_THRESHOLD

  /**
    * Quick check to see if a planet suffers from a runnaway greenhouse effect
    *
    * @see p. 507, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method greenhouse, line 346 in enviro.c - Mat Burdick (accrete)
    * @see method grnhouse, line 350 in enviro.c - Keris (starform)
    * @see method grnhouse, line 344 in enviro.c - Mat Burdick (starform)
    * @see method grnhouse, line 367 in Planet.java - Carl Burke (starform)
    *
    * @param orbit      semi-major axis in AU.
    * @param greenhouse greenhouse radius in AU.
    * @return true if there is a runnaway greenhouse effect, false otherwise
    */
  def suffersGreenhouseEffect(orbit: Double, greenhouse: Double): Boolean = orbit < greenhouse

  /**
    * This implements Fogg's eq.18.
    *
    * @note The pressure returned is in units of millibars (mb).
    *
    * @see eq. 18, p. 507, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method pressure, line 404 in enviro.c - Mat Burdick (accrete)
    * @see method pressure, line 409 in enviro.c - Keris (starform)
    * @see method pressure, line 401 in enviro.c - Mat Burdick (starform)
    * @see method pressure, line 736 in Planet.java - Carl Burke (starform)
    *
    * @param vGas    the volatile gas inventory.
    * @param radius  the radius of the planet in kilometers.
    * @param gravity the gravity of the planet in m/s2.
    * @return pressure in units of millibars (mb).
    */
  def surfacePressure(vGas: Double, radius: Double, gravity: Double): Double = {
    val gees = UnitConverter.mSec2ToGs(gravity)
    val equatorialRadius = radius / EARTH_RADIUS_IN_KM
    vGas * gees / Math.pow(equatorialRadius, 2)
  }


  def atmosphere(zone: Int, suffersGreenHouse: Boolean, retainsAtmos: Boolean, isGiant: Boolean): Atmosphere = {
    (zone, suffersGreenHouse, retainsAtmos, isGiant) match {
      case (_, _, _, true) => GAS_GIANT // gas giants all have the same atmosphere
      case (_, _, false, false) => AIRLESS // handle airless terrestrials separately to those with an atmosphere
      case (1, true, true, false) => ATMOS_II_VENUS // greenhouse effected terrestrials have atmosphere II (Venusian)
      case (1, false, true, false) => ATMOS_I_II_OR_V // terrestrials between greenhouse radius and 4 x eco are subject to climate feedback
      case (2, false, true, false) => ATMOS_III // zone 2 terrestrials that retain N2 but not H2 have atmosphere III
      case (3, false, true, false) => ATMOS_VII // zone 3 terrestrials have atmosphere VII
    }
  }

  /** This is Fogg's eq.19, intended to calculate the effective surface temperature in kelvin.
    *
    * @note The effective surface temperature is returned in units of kelvin.
    *
    * @see Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see method eff_temp, line 511 in enviro.c - Mat Burdick (accrete)
    * @see method eff_temp, line 516 in enviro.c - Keris (starform)
    * @see method eff_temp, line 509 in enviro.c - Mat Burdick (starform)
    * @see method eff_temp, line 836 in Planet.java - Carl Burke (starform)
    *
    * @param ecosphereRadius the mean habitable radius for the parent star in AU.
    * @param orbitalRadius   the orbiting axis of the planet in AU.
    * @param albedo          the albedo of the planet.
    * @return the effective surface temperature in kelvin.
    */
  def effectiveTemperature(ecosphereRadius: Double, orbitalRadius: Double, albedo: Double): Double = {
    Math.sqrt(ecosphereRadius / orbitalRadius) * Math.pow((1.0 - albedo) / 0.7, 0.25) * EARTH_EFFECTIVE_TEMP
  }


  /**
    * This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of  Earth's Atmosphere" article. It determines the rise in temperature produced by the
    * greenhouse effect.
    *
    * @note The increase in surface temperature is returned in units of kelvin.
    *
    * @param opticalDepth    the optical depth of the component greenhouse gases.
    * @param effectiveTemp   the current effective suface temperature in dgerees kelvin.
    * @param surfacePressure the atmosphere pressure in millibars.
    * @return the rise in temperature produced by the greenhouse effect in degrees kelvin.
    */
  def greenhouseEffectDelta(opticalDepth: Double, effectiveTemp: Double, surfacePressure: Double): Double = {
    (Math.pow(1.0 + 0.75 * opticalDepth, 0.5) - 1.0) * effectiveTemp * CONVECTION_FACTOR
  }


  /*--------------------------------------------------------------------------*/
  /*   This function returns the boiling point of water in an atmosphere of   */
  /*   pressure 'surface_pressure', given in millibars.  The boiling point is    */
  /*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
  /*--------------------------------------------------------------------------*/

  /**
    * This is Fogg's eq.21. it returns the boiling point of water in an atmosphere of pressure 'surface_pressure'.
    *
    * @param surfPressure he atmosphere pressure in millibars.
    * @return
    */
  def boilingPoint(surfPressure: Double): Double = {
    val surfPressureInBars = UnitConverter.millibarsToBars(surfPressure)
    Math.pow(Math.log(surfPressureInBars) / -5050.5 + 1.0 / 373.0, -1) - 273
  }


  //  //  /*--------------------------------------------------------------------------*/
  //  //  /*   This function is Fogg's eq.22.  Given the volatile gas inventory and   */
  //  //  /*   planetary radius of a planet (in Km), this function returns the        */
  //  //  /*   fraction of the planet covered with water.                             */
  //  //  /*   I have changed the function very slightly:  the fraction of Earth's    */
  //  //  /*   surface covered by water is 71%, not 75% as Fogg used.                 */
  //  //  /*--------------------------------------------------------------------------*/
  //  //
  //  //  double hydrosphere_fraction(volatile_gas_inventory, planet_radius)
  //  //  double volatile_gas_inventory, planet_radius;
  //  //  {
  //  //    double temp;
  //  //
  //  //    temp = (0.71 * volatile_gas_inventory / 1000.0) * pow2(EARTH_RADIUS_IN_KM / planet_radius);
  //  //    if (temp >= 1.0)
  //  //      return(1.0);
  //  //    else
  //  //      return(temp);
  //  //  }
  //  //
  //  //
  //  //  /*--------------------------------------------------------------------------*/
  //  //  /*   Given the surface temperature of a planet (in Kelvin), this function   */
  //  //  /*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  */
  //  //  /*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     */
  //  //  /*   This equation is Hart's eq.3.                                          */
  //  //  /*   I have modified it slightly using constants and relationships from     */
  //  //  /*   Glass's book "Introduction to Planetary Geology", p.46.                */
  //  //  /*   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     */
  //  //  /*   covered by one Kg. of cloud.					    */
  //  //  /*--------------------------------------------------------------------------*/
  //  //
  //  //  double cloud_fraction(surf_temp, smallest_MW_retained, equatorial_radius, hydrosphere_fraction)
  //  //  double surf_temp, smallest_MW_retained, equatorial_radius,
  //  //  hydrosphere_fraction;
  //  //  {
  //  //    double water_vapor_in_kg, fraction, surface_area, hydrosphere_mass;
  //  //
  //  //    if (smallest_MW_retained > WATER_VAPOR)
  //  //      return(0.0);
  //  //    else
  //  //    {
  //  //      surface_area = 4.0 * PI * pow2(equatorial_radius);
  //  //      hydrosphere_mass = hydrosphere_fraction * surface_area * EARTH_WATER_MASS_PER_AREA;
  //  //      water_vapor_in_kg = (0.00000001 * hydrosphere_mass) * exp(Q2_36 * (surf_temp - 288.0));
  //  //      fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surface_area;
  //  //      if (fraction >= 1.0)
  //  //        return(1.0);
  //  //      else
  //  //        return(fraction);
  //  //    }
  //  //  }
  //  //
  //  //
  //  //  /*--------------------------------------------------------------------------*/
  //  //  /*   Given the surface temperature of a planet (in Kelvin), this function   */
  //  //  /*   returns the fraction of the planet's surface covered by ice.  This is  */
  //  //  /*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. */
  //  //  /*   I have changed a constant from 70 to 90 in order to bring it more in   */
  //  //  /*   line with the fraction of the Earth's surface covered with ice, which  */
  //  //  /*   is approximatly .016 (=1.6%).                                          */
  //  //  /*--------------------------------------------------------------------------*/
  //  //
  //  //  double ice_fraction(hydrosphere_fraction, surf_temp)
  //  //  double hydrosphere_fraction, surf_temp;
  //  //  {
  //  //    double temp;
  //  //
  //  //    if (surf_temp > 328.0)
  //  //      surf_temp = 328.0;
  //  //    temp = pow(((328.0 - surf_temp) / 90.0),5.0);
  //  //    if (temp > (1.5 * hydrosphere_fraction))
  //  //      temp = (1.5 * hydrosphere_fraction);
  //  //    if (temp >= 1.0)
  //  //      return(1.0);
  //  //    else
  //  //      return(temp);
  //  //  }

}
