package com.szadowsz.starform.system.planets


import com.szadowsz.starform.StarformFunSpec
import com.szadowsz.starform.unit.{UnitConstants, UnitConverter}

class OrbitalCalcFunSpec extends StarformFunSpec {
  val calc: OrbitalCalc = new OrbitalCalc with UnitConstants {}
  
  describe("Aphelion Calculation") {
    
    describe("when axis == 0.0") {
      
      it("should return 0.0") {
        calc.aphelionDistance(0.0, 0.5) shouldBe (0.0 +-orbitalDistanceTolerance)
      }
    }
    
    describe("when eccentricity == 1.0 (Parabolic Escape Orbit)") {
      
      it("should return double the axis value") {
        calc.aphelionDistance(0.50, 1.0) shouldBe (1.0 +-orbitalDistanceTolerance)
      }
    }
    
    describe("when eccentricity > 1.0 (Hyperbolic Escape Orbit)") {
      
      it("should return more than double the axis value") {
        calc.aphelionDistance(0.50, 1.1) should be > 1.0
      }
    }
    
    describe("when using Solar System Values") {
      
      it("should calculate   Mercury's Aphelion Correctly") {
        calc.aphelionDistance(0.387098, 0.205630) shouldBe (0.466697 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Venus' Aphelion Correctly") {
        calc.aphelionDistance(0.72333, 0.0068) shouldBe (0.7282 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Earth's Aphelion Correctly") {
        calc.aphelionDistance(1.0, 0.0167086) shouldBe (1.0167 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Mars' Aphelion Correctly") {
        calc.aphelionDistance(1.5237, 0.0934) shouldBe (1.6660 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Jupiter's Aphelion Correctly") {
        calc.aphelionDistance(5.2044, 0.0489) shouldBe (5.4588 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Saturn's Aphelion Correctly") {
        calc.aphelionDistance(9.5826, 0.0565) shouldBe (10.1238 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Uranus' Aphelion Correctly") {
        calc.aphelionDistance(19.2184, 0.046381) shouldBe (20.11 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Neptune's Aphelion Correctly") {
        calc.aphelionDistance(30.11, 0.009456) shouldBe (30.4 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Pluto's Aphelion Correctly") {
        calc.aphelionDistance(39.482, 0.2488) shouldBe (49.305 +- orbitalDistanceTolerance)
      }
    }
  }
  
  describe("Perihelion Calculation") {
    
    describe("when axis == 0.0") {
      
      it("should return 0.0") {
        calc.perihelionDistance(0.0, 0.5) shouldBe (0.0 +-orbitalDistanceTolerance)
      }
    }
    
    describe("when eccentricity == 1.0 (Parabolic Escape Orbit)") {
      
      it("should return 0.0") {
        calc.perihelionDistance(0.50, 1.0) shouldBe (0.0 +-orbitalDistanceTolerance)
      }
    }
    
    describe("when eccentricity > 1.0 (Hyperbolic Escape Orbit)") {
      
      it("should return a negative value") {
        calc.perihelionDistance(0.50, 1.1) should be < 0.0
      }
    }
    
    describe("when using Solar System Values") {
      
      it("should calculate   Mercury's Perihelion Correctly") {
        calc.perihelionDistance(0.387098, 0.205630) shouldBe (0.307499 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Venus' Perihelion Correctly") {
        calc.perihelionDistance(0.72333, 0.0068) shouldBe (0.71843 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Earth's Perihelion Correctly") {
        calc.perihelionDistance(1.0, 0.0167086) shouldBe (0.98329 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Mars' Perihelion Correctly") {
        calc.perihelionDistance(1.5237, 0.0934) shouldBe (1.3814 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Jupiter's Perihelion Correctly") {
        calc.perihelionDistance(5.2044, 0.0489) shouldBe (4.95 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Saturn's Perihelion Correctly") {
        calc.perihelionDistance(9.5826, 0.0565) shouldBe (9.0412 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Uranus' Perihelion Correctly") {
        calc.perihelionDistance(19.2184, 0.046381) shouldBe (18.33 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Neptune's Perihelion Correctly") {
        calc.perihelionDistance(30.11, 0.009456) shouldBe (29.81 +- orbitalDistanceTolerance)
      }
      
      it("should calculate Pluto's Perihelion Correctly") {
        calc.perihelionDistance(39.482, 0.2488) shouldBe (29.658 +- orbitalDistanceTolerance)
      }
    }
  }
  
  describe("Orbital Period Calculation (In Days)") {
    
    describe("when using Solar System Values") {
      
      it("should calculate Mercury's Period Correctly") {
        calc.orbitLength(0.387098, 0.0, 1.0) shouldBe (87.9693 +- orbitalPeriodTolerance)
      }
      
      it("should calculate Venus' Period Correctly") {
        calc.orbitLength(0.72333, 0.0, 1.0) shouldBe (224.7008 +- orbitalPeriodTolerance)
      }
      
      it("should calculate Earth's Period Correctly") {
        calc.orbitLength(1.0, 0.0, 1.0) shouldBe (365.25 +- orbitalPeriodTolerance)
      }
      
      it("should calculate Mars' Period Correctly") {
        calc.orbitLength(1.5237, 0.0, 1.0) shouldBe (686.9796 +- orbitalPeriodTolerance)
      }
      
      it("should calculate Jupiter's Period Correctly") {pendingUntilFixed{
        calc.orbitLength(5.2044, 0.0, 1.0) shouldBe (4333.84 +- orbitalPeriodTolerance)
      }}
      
      it("should calculate Saturn's Period Correctly") {pendingUntilFixed{
        calc.orbitLength(9.5826, 0.0, 1.0) shouldBe (10775.599 +- orbitalPeriodTolerance)
      }}
  
      it("should calculate Uranus' Period Correctly") {pendingUntilFixed{
        calc.orbitLength(19.2184, 0.0, 1.0) shouldBe (30687.153 +- orbitalPeriodTolerance)
      }}
  
      it("should calculate Neptune's Period Correctly") {pendingUntilFixed{
        calc.orbitLength(30.11, 0.0, 1.0) shouldBe (60190.03 +- orbitalPeriodTolerance)
      }}
    }
  }
}
