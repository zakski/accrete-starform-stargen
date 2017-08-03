package com.szadowsz.starform.model.keris

import com.szadowsz.starform.model.eco.calc.{FoggEcoCalc, KerisEcoCalc}
import com.szadowsz.starform.model.star.calc.FoggStarCalc
import com.szadowsz.starform.model.star.constants.FoggStarConstants
import com.szadowsz.starform.unit.UnitConverter
import org.scalatest.{FunSpec, Matchers}

/**
  * Test the Recreated Fogg Calculations Against Data provided by Fogg with tolerance for more accurate values and floating point changes.
  *
  * Created on 21/09/2016.
  */
class KerisSampleSystemSpec extends FunSpec with Matchers {
  val tolerancePercentage = 0.05 // 5% of the expected value for tolerance. To account for floating point calculations on modern systems.

  val eCalc = new KerisEcoCalc()

  val star = KerisTestStar(FoggStarCalc(new FoggStarConstants))

  describe("Sample System Planet 1 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.079)
    val pAxis = 0.34
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.099
    val tilt = 17.0
    val surfPress = 0.0
    val surfTemp = UnitConverter.celsiusToKelvin(219.41)
    val expectedEqRadius = 2779.3
    val expectedDensity = 5.28
    val expectedYear = 70.79
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)
    val expectedDayTemp = UnitConverter.celsiusToKelvin(429.67)
    val expectedNightTemp = UnitConverter.celsiusToKelvin(-185.92)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(431.13)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-196.48)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Day Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedDayTemp * tolerancePercentage
      day should be(expectedDayTemp +- tolerance)
    }

    it("it's Night Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedNightTemp * tolerancePercentage
      night should be(expectedNightTemp +- tolerance)
    }


    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }

  describe("Sample System Planet 2 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.325)
    val pAxis = 0.479
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.032
    val tilt = 19.0
    val surfPress = 0.0
    val surfTemp = UnitConverter.celsiusToKelvin(140.74)
    val expectedEqRadius = 4429.5
    val expectedDensity = 5.334
    val expectedYear = 118.79
    val expectedSynch = true
    val expectedDayLength = UnitConverter.daysToHours(expectedYear)
    // Day and night are within 10 of min and max so keris does not display them
    //val expectedDayTemp = UnitConverter.celsiusToKelvin(335.03)
    //val expectedNightTemp = UnitConverter.celsiusToKelvin(-217.15)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(335.03)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-217.15)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }

  describe("Sample System Planet 3 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(1.154)
    val pAxis = 1.097
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.1
    val tilt = 18.0
    val surfPress = UnitConverter.barsToMillibars(1.029)
    val surfTemp = UnitConverter.celsiusToKelvin(18.75)
    val expectedEqRadius = 6709.1
    val expectedDensity = 5.452
    val expectedYear = 411.03
    val expectedSynch = false
    val expectedDayLength = 15.43
    val expectedDayTemp = UnitConverter.celsiusToKelvin(23.11)
    val expectedNightTemp = UnitConverter.celsiusToKelvin(14.11)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(45.22)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-7.67)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Day Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedDayTemp * tolerancePercentage
      day should be(expectedDayTemp +- tolerance)
    }

    it("it's Night Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedNightTemp * tolerancePercentage
      night should be(expectedNightTemp +- tolerance)
    }


    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }

  describe("Sample System Planet 4 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(8.063)
    val pAxis = 1.631
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 20116.0
    val expectedDensity = 1.413
    val expectedYear = 745.44
    val pEcc = 0.041
    val expectedSynch = false
    val expectedDayLength = 14.50

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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

  describe("Sample System Planet 5 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(11.990)
    val pAxis = 2.661
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 23524.7
    val expectedDensity = 1.314
    val expectedYear = 1553.59
    val pEcc = 0.236
    val expectedSynch = false
    val expectedDayLength = 13.90

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(116.779)
    val pAxis = 5.131
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 48262.0
    val expectedDensity = 1.482
    val expectedYear = 4158.12
    val pEcc = 0.067
    val expectedSynch = false
    val expectedDayLength = 9.14

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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

  describe("Sample System Planet 7 Calculations") {
    val isGasGiant = true
    val pMass = UnitConverter.earthMassToSolarMass(787.769)
    val pAxis = 10.032
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 89057.7
    val expectedDensity = 1.591
    val expectedYear = 11356.22
    val pEcc = 0.082
    val expectedSynch = false
    val expectedDayLength = 6.49

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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
    val pMass = UnitConverter.earthMassToSolarMass(8.221)
    val pAxis = 22.007
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 25129.3
    val expectedDensity = 0.739
    val expectedYear = 36941.60
    val pEcc = 0.015
    val expectedSynch = false
    val expectedDayLength = 17.94

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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
    val pMass = UnitConverter.earthMassToSolarMass(7.127)
    val pAxis = 31.563
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val expectedEqRadius = 24839.4
    val expectedDensity = 0.664
    val expectedYear = 63448.63
    val pEcc = 0.026
    val expectedSynch = false
    val expectedDayLength = 19.04

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
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
    val pMass = UnitConverter.earthMassToSolarMass(0.117)
    val pAxis = 39.459
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.029
    val tilt = 60.0
    val surfPress = 0.0
    val surfTemp = UnitConverter.celsiusToKelvin(-228.06)
    val expectedEqRadius = 4224.8
    val expectedDensity = 2.213
    val expectedYear = 88691.47
    val expectedSynch = false
    val expectedDayLength = 29.65
    val expectedDayTemp = UnitConverter.celsiusToKelvin(-222.26)
    val expectedNightTemp = UnitConverter.celsiusToKelvin(-233.76)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(-168.47)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-260.67)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Day Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedDayTemp * tolerancePercentage
      day should be(expectedDayTemp +- tolerance)
    }

    it("it's Night Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedNightTemp * tolerancePercentage
      night should be(expectedNightTemp +- tolerance)
    }


    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }

  describe("Sample System Planet 11 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.015)
    val pAxis = 42.834
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.005
    val tilt = 33.0
    val surfPress = 0.0
    val surfTemp = UnitConverter.celsiusToKelvin(-230.15)
    val expectedEqRadius = 2146.3
    val expectedDensity = 2.193
    val expectedYear = 100311.36
    val expectedSynch = false
    val expectedDayLength = 41.79
    val expectedDayTemp = UnitConverter.celsiusToKelvin(-222.74)
    val expectedNightTemp = UnitConverter.celsiusToKelvin(-237.40)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(-189.86)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-260.76)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Day Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedDayTemp * tolerancePercentage
      day should be(expectedDayTemp +- tolerance)
    }

    it("it's Night Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedNightTemp * tolerancePercentage
      night should be(expectedNightTemp +- tolerance)
    }


    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }

  describe("Sample System Planet 12 Calculations") {
    val isGasGiant = false
    val pMass = UnitConverter.earthMassToSolarMass(0.067)
    val pAxis = 48.081
    val orbitZone = eCalc.orbitalZone(star.luminosity, pAxis)
    val pEcc = 0.005
    val tilt = 33.0
    val surfPress = 0.0
    val surfTemp = UnitConverter.celsiusToKelvin(-232.32)
    val expectedEqRadius = 3508.4
    val expectedDensity = 2.205
    val expectedYear = 119295.11
    val expectedSynch = false
    val expectedDayLength = 32.60
    val expectedDayTemp = UnitConverter.celsiusToKelvin(-226.62)
    val expectedNightTemp = UnitConverter.celsiusToKelvin(-237.89)
    val expectedMaxTemp = UnitConverter.celsiusToKelvin(-171.05)
    val expectedMinTemp = UnitConverter.celsiusToKelvin(-261.69)

    it("it's Equatorial Radius And Density should match the values in the example") {
      val (equatorialRadius, density) = eCalc.radiusAndDensity(pMass, pAxis, star.meanHabitableRadius, isGasGiant, orbitZone)

      val radiusTolerance = expectedEqRadius * tolerancePercentage
      equatorialRadius should be(expectedEqRadius +- radiusTolerance)

      val densityTolerance = expectedDensity * tolerancePercentage
      density should be(expectedDensity +- densityTolerance)
    }

    it("it's Year Length should match the value in the example") {
      val yearLength = eCalc.orbitLength(pAxis, pMass, star.mass)
      val yearTolerance = expectedYear * tolerancePercentage
      yearLength should be(expectedYear +- yearTolerance)
    }

    it("it's Day Length should match the value in the example") {
      val angularVelocity = eCalc.totalAngularVelocity(star.mass, star.age, pMass, expectedEqRadius, pAxis, expectedDensity, isGasGiant)
      val (synch, resonant, lengthOfDay) = eCalc.dayLength(angularVelocity, expectedYear, pEcc)

      synch should be(expectedSynch)

      val dayTolerance = expectedDayLength * tolerancePercentage
      lengthOfDay should be(expectedDayLength +- dayTolerance)
    }

    it("it's Day Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedDayTemp * tolerancePercentage
      day should be(expectedDayTemp +- tolerance)
    }

    it("it's Night Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedNightTemp * tolerancePercentage
      night should be(expectedNightTemp +- tolerance)
    }


    it("it's Maximum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMaxTemp * tolerancePercentage
      max should be(expectedMaxTemp +- tolerance)
    }

    it("it's Minimum Temperature should match the value in the example") {
      val (day, night, max, min) = eCalc.calcTempLimits(pEcc, surfPress, surfTemp, tilt, expectedDayLength)

      val tolerance = expectedMinTemp * tolerancePercentage
      min should be(expectedMinTemp +- tolerance)
    }
  }
}
