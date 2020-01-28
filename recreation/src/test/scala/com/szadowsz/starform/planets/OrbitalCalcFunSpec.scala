package com.szadowsz.starform.planets


import org.scalatest.matchers.should.Matchers
import org.scalatest.funspec.AnyFunSpec

class OrbitalCalcFunSpec extends StarformFunSpec {
  val calc: OrbitalCalc = new OrbitalCalc {}
  
  describe("Aphelion Calculation") {
  
    describe("when axis == 0.0") {
    
      it("should return 0.0") {
        calc.aphelionDistance(0.0,0.5) shouldBe 0.0
      }
    }
  
    describe("when eccentricity == 1.0 (Parabolic Escape Orbit)") {
    
      it("should return double the axis value") {
        calc.aphelionDistance(0.50,1.0) shouldBe 1.0
      }
    }
  
    describe("when eccentricity > 1.0 (Hyperbolic Escape Orbit)") {
    
      it("should return more than double the axis value") {
        calc.aphelionDistance(0.50,1.1) should be > 1.0
      }
    }
  
    describe("when using Solar System Values") {
      
      it("should calculate Mecury's Aphelion Correctly") {
        calc.aphelionDistance(0.387098,0.205630) shouldBe (0.466697 +- orbitalTolerance)
      }
      
      it("should calculate Venus' Aphelion Correctly") {
        calc.aphelionDistance(0.72333,0.0068) shouldBe (0.7282 +- orbitalTolerance)
      }
      
      it("should calculate Earth's Aphelion Correctly") {
        calc.aphelionDistance(1.0,0.0167086) shouldBe (1.0167 +- orbitalTolerance)
      }
  
      it("should calculate Mar's Aphelion Correctly") {
        calc.aphelionDistance(1.5237,0.0934) shouldBe (1.6660 +- orbitalTolerance)
      }
  
      it("should calculate Jupiter's Aphelion Correctly") {
        calc.aphelionDistance(5.2044,	0.0489) shouldBe (5.4588 +- orbitalTolerance)
      }
  
      it("should calculate Saturn's Aphelion Correctly") {
        calc.aphelionDistance(9.5826,	0.0565) shouldBe (10.1238 +- orbitalTolerance)
      }
  
      it("should calculate Uranus' Aphelion Correctly") {
        calc.aphelionDistance(19.2184,	0.046381) shouldBe (20.11 +- orbitalTolerance)
      }
  
      it("should calculate Neptune's Aphelion Correctly") {
        calc.aphelionDistance(30.11,	0.009456) shouldBe (30.4 +- orbitalTolerance)
      }
  
      it("should calculate Pluto's Aphelion Correctly") {
        calc.aphelionDistance(39.482,	0.2488) shouldBe (49.305 +- orbitalTolerance)
      }
    }
  }
  
  describe("Perihelion Calculation") {
    
    describe("when axis == 0.0") {
      
      it("should return 0.0") {
        calc.perihelionDistance(0.0,0.5) shouldBe 0.0
      }
    }
  
    describe("when eccentricity == 1.0 (Parabolic Escape Orbit)") {
    
      it("should return 0.0") {
        calc.perihelionDistance(0.50,1.0) shouldBe 0.0
      }
    }
  
    describe("when eccentricity > 1.0 (Hyperbolic Escape Orbit)") {
    
      it("should return a negative value") {
        calc.perihelionDistance(0.50,1.1) should be < 0.0
      }
    }
  
    describe("when using Solar System Values") {
      
      it("should calculate Mecury's Perihelion Correctly") {
        calc.perihelionDistance(0.387098,0.205630) shouldBe (0.307499 +- orbitalTolerance)
      }
      
      it("should calculate Venus' Perihelion Correctly") {
        calc.perihelionDistance(0.72333,0.0068) shouldBe (0.71843 +- orbitalTolerance)
      }
      
      it("should calculate Earth's Perihelion Correctly") {
        calc.perihelionDistance(1.0,0.0167086) shouldBe (0.98329 +- orbitalTolerance)
      }
  
      it("should calculate Mar's Perihelion Correctly") {
        calc.perihelionDistance(1.5237,0.0934) shouldBe (1.3814 +- orbitalTolerance)
      }
  
      it("should calculate Jupiter's Perihelion Correctly") {
        calc.perihelionDistance(5.2044,	0.0489) shouldBe (4.95 +- orbitalTolerance)
      }
  
      it("should calculate Saturn's Perihelion Correctly") {
        calc.perihelionDistance(9.5826,	0.0565) shouldBe (9.0412 +- orbitalTolerance)
      }
  
      it("should calculate Uranus' Perihelion Correctly") {
        calc.perihelionDistance(19.2184,	0.046381) shouldBe (18.33 +- orbitalTolerance)
      }
  
      it("should calculate Neptune's Perihelion Correctly") {
        calc.perihelionDistance(30.11,	0.009456) shouldBe (29.81 +- orbitalTolerance)
      }
  
      it("should calculate Pluto's Perihelion Correctly") {
        calc.perihelionDistance(39.482,	0.2488) shouldBe (29.658 +- orbitalTolerance)
      }
    }
  }
}
