package com.szadowsz.starform.model.burdick

import com.szadowsz.starform.model.eco.calc.BurdickEcoCalc
import com.szadowsz.starform.model.star.calc.FoggStarCalc
import com.szadowsz.starform.model.star.constants.FoggStarConstants
import com.szadowsz.starform.unit.UnitConverter
import org.scalatest.{FunSpec, Matchers}

/**
  * Created on 15/04/2017.
  */
class BurdickSampleSystemSpec extends FunSpec with Matchers {

  val tolerancePercentage = 0.05 // 5% of the expected value for tolerance. To account for floating point calculations on modern systems.

  val eCalc = new BurdickEcoCalc()

  val star = BurdickTestStar(FoggStarCalc(new FoggStarConstants))


  describe("Sample System Planet 1 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.220)
    val pAxis = 0.341
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.092
    val expectedEqRadius = 3893.8
    val expectedDensity = 5.314
    val expectedYear = 72.89
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)
    val expectedGravity = 0.59
    val expectedEscapeVel = 6.71
    //Surface pressure:                0.000        Earth atmospheres
    //Surface temperature:                193.31        degrees Celcius
    //Molecular weight retained:        17.63 and above
    //Surface acceleration:        578.24        cm/sec2
    //Axial tilt:                        22        degrees
    //Planetary albedo:                0.081
    //Boiling point of water:        -273.0        degrees Celcius
    //Hydrosphere percentage:        0.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        0.00

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 2 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.202)
    val pAxis = 0.505
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.091
    val expectedEqRadius = 3786.9
    val expectedDensity = 5.310
    val expectedYear = 130.99
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)
    val expectedGravity = 0.57
    val expectedEscapeVel = 6.52
    //Surface pressure:                0.000        Earth atmospheres
    //Surface temperature:                112.78        degrees Celcius
    //Molecular weight retained:        18.65 and above
    //Surface acceleration:        561.97        cm/sec2
    //Axial tilt:                        28        degrees
    //Planetary albedo:                0.060
    //Boiling point of water:        -273.0        degrees Celcius
    //Hydrosphere percentage:        0.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        0.00
    //
    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 3 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.165)
    val pAxis = 0.877
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 3541.1
    val expectedDensity = 5.302
    val expectedYear = 300.44
    val pEcc = 0.015
    val expectedSynch = false
    val expectedDayLength = 40.82
    val expectedGravity = 0.53
    val expectedEscapeVel = 6.10
    //Surface pressure:                2.702        Earth atmospheres        GREENHOUSE EFFECT
    //Surface temperature:                45.57        degrees Celcius
    //Molecular weight retained:        21.36 and above
    //Surface acceleration:        524.69        cm/sec2
    //Axial tilt:                        29        degrees
    //Planetary albedo:                0.038
    //Boiling point of water:        129.5        degrees Celcius
    //Hydrosphere percentage:        100.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        0.00

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 4 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(1.515)
    val pAxis = 1.047
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 7328.1
    val expectedDensity = 5.494
    val expectedYear = 391.74
    val pEcc = 0.017
    val expectedSynch = false
    val expectedDayLength = 14.68
    val expectedGravity = 1.15
    val expectedEscapeVel = 12.84
    //Surface pressure:                1.889        Earth atmospheres
    //Surface temperature:                19.01        degrees Celcius
    //Molecular weight retained:        4.81 and above
    //Surface acceleration:        1125.13        cm/sec2
    //Axial tilt:                        22        degrees
    //Planetary albedo:                0.297
    //Boiling point of water:        118.4        degrees Celcius
    //Hydrosphere percentage:        67.12
    //Cloud cover percentage:        61.38
    //Ice cover percentage:        1.06

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 5 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(6.262)
    val pAxis = 1.793
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 18997.9
    val expectedDensity = 1.303
    val expectedYear = 877.67
    val pEcc = 0.002
    val expectedSynch = false
    val expectedDayLength = 15.54
    //Escape Velocity:                16.21        Km/sec
    //Molecular weight retained:        3.02 and above
    //Surface acceleration:        691.87        cm/sec2
    //Axial tilt:                        29        degrees
    //Planetary albedo:                0.500

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }


  describe("Sample System Planet 6 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.453)
    val pAxis = 2.956
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 4941.6
    val expectedDensity = 5.356
    val expectedYear = 1857.62
    val pEcc = 0.140
    val expectedSynch = false
    val expectedDayLength = 17.62
    val expectedGravity = 0.75
    val expectedEscapeVel = 8.55
    //Surface pressure:                0.207        Earth atmospheres
    //Surface temperature:                -136.53        degrees Celcius
    //Molecular weight retained:        10.86 and above
    //Surface acceleration:        739.66        cm/sec2
    //Axial tilt:                        18        degrees
    //Planetary albedo:                0.634
    //Boiling point of water:        61.1        degrees Celcius
    //Hydrosphere percentage:        0.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        81.12
    //
    //

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 7 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(69.313)
    val pAxis = 5.160
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 41830.7
    val expectedDensity = 1.351
    val expectedYear = 4284.26
    val pEcc = 0.299
    val expectedSynch = false
    val expectedDayLength = 10.28
    //Escape Velocity:                36.35        Km/sec
    //Molecular weight retained:        0.60 and above
    //Surface acceleration:        1579.66        cm/sec2
    //Axial tilt:                        42        degrees
    //Planetary albedo:                0.512

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 8 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(11.727)
    val pAxis = 8.852
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 26059.7
    val expectedDensity = 0.946
    val expectedYear = 9626.17
    val pEcc = 0.182
    val expectedSynch = false
    val expectedDayLength = 15.57
    //Escape Velocity:                18.95        Km/sec
    //Molecular weight retained:        2.21 and above
    //Surface acceleration:        688.64        cm/sec2
    //Axial tilt:                        47        degrees
    //Planetary albedo:                0.509

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 9 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(557.816)
    val pAxis = 13.121
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 83066.4
    val expectedDensity = 1.389
    val expectedYear = 17357.91
    val pEcc = 0.083
    val expectedSynch = false
    val expectedDayLength = 7.20
    //Escape Velocity:                73.18        Km/sec
    //Molecular weight retained:        0.15 and above
    //Surface acceleration:        3223.89        cm/sec2
    //Axial tilt:                        33        degrees
    //Planetary albedo:                0.454

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 10 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.372)
    val pAxis = 28.450
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 6182.7
    val expectedDensity = 2.246
    val expectedYear = 55468.32
    val pEcc = 0.000
    val expectedSynch = false
    val expectedDayLength = 24.33
    val expectedGravity = 0.40
    val expectedEscapeVel = 6.93
    //Surface pressure:                0.000        Earth atmospheres
    //Surface temperature:                -222.05        degrees Celcius
    //Molecular weight retained:        16.54 and above
    //Surface acceleration:        388.05        cm/sec2
    //Axial tilt:                        57        degrees
    //Planetary albedo:                0.149
    //Boiling point of water:        -38.3        degrees Celcius
    //Hydrosphere percentage:        0.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        0.10

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }

  describe("Sample System Planet 11 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.283)
    val pAxis = 46.864
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 5653.0
    val expectedDensity = 2.236
    val expectedYear = 117268.25
    val pEcc = 0.047
    val expectedSynch = false
    val expectedDayLength = 25.50
    val expectedGravity = 0.36
    val expectedEscapeVel = 6.32
    //Surface pressure:                0.000        Earth atmospheres
    //Surface temperature:                -233.50        degrees Celcius
    //Molecular weight retained:        19.88 and above
    //Surface acceleration:        353.22        cm/sec2
    //Axial tilt:                        54        degrees
    //Planetary albedo:                0.157
    //Boiling point of water:        -45.5        degrees Celcius
    //Hydrosphere percentage:        0.00
    //Cloud cover percentage:        0.00
    //Ice cover percentage:        0.08

    it("it's Equatorial Radius And Density should match the values in the sample system") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the sample system") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the sample system") {
      val angularVelocity = eCalc.totalAngularVelocity(
        star.mass,
        star.age,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("its surface gravity should match the value in the sample system") {
      val gravity = UnitConverter.mSec2ToGs(eCalc.surfaceGravity(pMass, expectedEqRadius))

      val gravTolerance = expectedGravity * tolerancePercentage
      gravity should be(expectedGravity +- gravTolerance)
    }

    it("its escape velocity should match the value in the sample system") {
      val gravInKm = UnitConverter.mToKm(UnitConverter.GsToMetreSec2(expectedGravity))
      val escapeVel = eCalc.escapeVelocity(gravInKm, expectedEqRadius)

      val escapeVelTolerance = expectedEscapeVel * tolerancePercentage
      escapeVel should be(expectedEscapeVel +- escapeVelTolerance)
    }
  }
}