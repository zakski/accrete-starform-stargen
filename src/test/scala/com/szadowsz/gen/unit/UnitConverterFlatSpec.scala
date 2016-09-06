package com.szadowsz.gen.unit

import com.szadowsz.accrete.constants.UnitConverter
import org.junit.runner.RunWith
import org.scalatest.FlatSpec
import org.scalatest.junit.JUnitRunner

/**
  * Test Suite for the CPluggable trait.
  *
  * @author Zakski : 29/09/2015.
  */
@RunWith(classOf[JUnitRunner])
class UnitConverterFlatSpec extends FlatSpec {

  behavior of "The Unit Converter Object"

    it should "should successfully conver Solar Mass to Earth Mass" in {
      val km = 1
      val cm = 100000
      assertResult(1)(UnitConverter.solarMassToEarthMass(UnitConverter.EARTH_MASS_IN_KG / UnitConverter.SOLAR_MASS_IN_KG))
    }
}