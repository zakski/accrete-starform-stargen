package com.szadowsz.gen.unit

import com.szadowsz.gen.util.unit.UnitConverter
import org.junit.runner.RunWith
import org.scalatest.FunSpec
import org.scalatest.junit.JUnitRunner

/**
  * Test Suite for the CPluggable trait.
  *
  * @author Zakski : 29/09/2015.
  */
@RunWith(classOf[JUnitRunner])
class UnitConverterSpec extends FunSpec {

  describe("The Unit Converter Object") {

    it("should successfully kilometres to centimetres") {
      val km = 1
      val cm = 100000
      assertResult(cm)(UnitConverter.kmToCm(km))
    }

    it("should successfully kilometres to metres") {
      val km = 1
      val m = 1000
      assertResult(m)(UnitConverter.kmToM(km))
    }
  }
}