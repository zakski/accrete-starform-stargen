package com.szadowsz.starform.model.accrete

import com.szadowsz.starform.StarformFunSpec

class AccreteCalcFunSpec extends StarformFunSpec {
  val const: AccreteConstants = new AccreteConstants()
  val calc: AccreteCalc = new AccreteCalc (GravityCalc(const),const)
  
  describe("shouldAccreteContinue Calculation") {
    
    describe("when the New Planetary Mass has grown by < 1/1000th of the Previous Value") {
      
      it("should not continue") {
        calc.shouldAccreteContinue(1000.0,1000.05) shouldBe false
      }
    }
  
    describe("when the New Planetary Mass has grown by 1/1000th of the Previous Value") {
    
      it("should continue") {
        calc.shouldAccreteContinue(1000.0,1001.0) shouldBe true
      }
    }
  
    describe("when the New Planetary Mass has grown by > 1/1000th of the Previous Value") {
    
      it("should continue") {
        calc.shouldAccreteContinue(1000.0,1001.1) shouldBe true
      }
    }
  }
}
