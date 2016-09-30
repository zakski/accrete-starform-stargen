package com.szadowsz.stargen.base.starform

import com.szadowsz.stargen.base.starform.util.UnitConverter
import org.scalatest.{FunSpec, Matchers}

/**
  * Test the Recreated Fogg Calculations Against Data provided by Fogg with tolerance for more accurate values and floating point changes.
  *
  * Created on 21/09/2016.
  */
class FoggCalcSpec extends FunSpec with Matchers {
  val tolerancePercentage = 0.05 // 5% of the expected value for tolerance. To account for floating point calculations on modern systems as we

  describe("Sample System Planet 1 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.kgToSolarMass(4.9E23)
    val pAxis = 0.34
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val pEcc = 1E-2
    val expectedEqRadius = 2810.0
    val expectedDensity = 5.26
    val expectedYear = 72.0
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(FoggTestCalc.getStarMass, FoggTestCalc.getStarAge, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 2 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.kgToSolarMass(1.08E24)
    val pAxis = 0.58
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val pEcc = 5E-2
    val expectedEqRadius = 3704.0
    val expectedDensity = 5.08
    val expectedYear = 162.0
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 3 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.kgToSolarMass(1.09E25)
    val pAxis = 0.96
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 7568.0
    val expectedDensity = 5.93
    val expectedYear = 345.0
    val pEcc = 0.14
    val expectedSynch = false
    val expectedDayLength = 14.81

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 4 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.kgToSolarMass(1.83E25)
    val pAxis = 1.92
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 12949.0
    val expectedDensity = 2.02
    val expectedYear = 967.0
    val pEcc = 3E-2
    val expectedSynch = false
    val expectedDayLength = 15.13

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 5 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.kgToSolarMass(3.92E25)
    val pAxis = 3.7
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 18682.0
    val expectedDensity = 1.44
    val expectedYear = 2598.0
    val pEcc = 5E-2
    val expectedSynch = false
    val expectedDayLength = 14.92

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 6 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.kgToSolarMass(1.98E26)
    val pAxis = 5.75
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 33937.0
    val expectedDensity = 1.21
    val expectedYear = 5022.0
    val pEcc = 5E-2
    val expectedSynch = false
    val expectedDayLength = 12.02

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 7 Calculations") {
    val isGasGiant = true
   val pMass = UnitConverter.kgToSolarMass(2.31E27)
    val pAxis = 10.34
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 72400.0
    val expectedDensity = 1.45
    val expectedYear = 12112.0
    val pEcc = 2E-2
    val expectedSynch = false
    val expectedDayLength = 7.54

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 8 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.kgToSolarMass(2.9E26)
    val pAxis = 22.8
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 43843.0
    val expectedDensity = 0.82
    val expectedYear = 39682.0
    val pEcc = 0.14
    val expectedSynch = false
    val expectedDayLength = 12.87

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }

  describe("Sample System Planet 9 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.kgToSolarMass(9.63E23)
    val pAxis = 43.54
    val orbitZone = FoggTestCalc.orbitalZone(FoggTestCalc.getStarLuminosity,pAxis)
    val expectedEqRadius = 5130.0
    val expectedDensity = 1.7
    val expectedYear = 104706.0
    val pEcc = 2E-2
    val expectedSynch = false
    val expectedDayLength = 31.13

    it("it's Equatorial Radius And Density should match the values in the paper") {
      val (equatorialRadius,density) = FoggTestCalc.radiusAndDensity(pMass, pAxis, FoggTestCalc.getStarEcosphereRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the paper") {
      val yearLength = FoggTestCalc.orbitLength(pAxis, pMass, FoggTestCalc.getStarMass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the paper") {
      val angularVelocity = FoggTestCalc.totalAngularVelocity(
        FoggTestCalc.getStarMass,
        FoggTestCalc.getStarAge,
        pMass,
        expectedEqRadius,
        pAxis,
        expectedDensity,
        isGasGiant
      )
      val (synch, resonant, lengthOfDay) = FoggTestCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be (expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }
  }
}
