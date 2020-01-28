package com.szadowsz.starform.planets

import org.scalatest.funspec.AnyFunSpec
import org.scalatest.matchers.should.Matchers

class UWPFunSpec extends StarformFunSpec {
  
  describe("A Universal World Profile") {
    
    describe("when unknown") {
      val uwp = new UWP
  
      it("should be represented by X-XXXXXX-X") {
        uwp.toString should be ("X-XXXXXX-X")
      }
      
      it("should return 'X' for Starport Class") {
         uwp.getStarportClass shouldBe 'X'
      }
  
      it("should return 'X' for Size") {
        uwp.getSize shouldBe 'X'
      }
  
      it("should return 'X' for Atmosphere") {
        uwp.getAtmosphere shouldBe 'X'
      }
  
      it("should return 'X' for Hydrographics") {
        uwp.getHydrographics shouldBe 'X'
      }
  
      it("should return 'X' for Population") {
        uwp.getPopulation shouldBe 'X'
      }
  
      it("should return 'X' for Government") {
        uwp.getGovernment shouldBe 'X'
      }
  
      it("should return 'X' for Law Level") {
        uwp.getLawLevel shouldBe 'X'
      }
  
      it("should return 'X' for Tech Level") {
        uwp.getTechLevel shouldBe 'X'
      }
    }
  
    describe("when Eq Radius is 8517.6Km, Surface Pressure is 5.496 Atmospheres and Hydro + Ice Cover is 92.07%") {
      val uwp = new UWP(8517.6,5496.0,0.9051,0.0156)
  
      it("should be represented by X-XD9XXX-X") {
        uwp.toString should be ("X-AD9XXX-X")
      }
    
      it("should return 'X' for Starport Class") {
        uwp.getStarportClass shouldBe 'X'
      }
    
      it("should return 'A' for Size") {
        uwp.getSize shouldBe 'A'
      }
    
      it("should return 'D' for Atmosphere") {
        uwp.getAtmosphere shouldBe 'D'
      }
    
      it("should return '9' for Hydrographics") {
        uwp.getHydrographics shouldBe '9'
      }
    
      it("should return 'X' for Population") {
        uwp.getPopulation shouldBe 'X'
      }
    
      it("should return 'X' for Government") {
         uwp.getGovernment shouldBe 'X'
      }
    
      it("should return 'X' for Law Level") {
         uwp.getLawLevel shouldBe 'X'
      }
    
      it("should return 'X' for Tech Level") {
        uwp.getTechLevel shouldBe 'X'
      }
    }
  }
  
  describe("when Eq Radius is 2328.8Km, Surface Pressure is 0.002 Atmospheres and Hydro + Ice Cover is 36.54%") {
    val uwp = new UWP(2328.8,2.0,0.0,0.3654)
    
    it("should be represented by X-304XXX-X") {
      uwp.toString should be ("X-304XXX-X")
    }
    
    it("should return 'X' for Starport Class") {
      uwp.getStarportClass shouldBe 'X'
    }
    
    it("should return '3' for Size") {
      uwp.getSize shouldBe '3'
    }
    
    it("should return '0' for Atmosphere") {
      uwp.getAtmosphere shouldBe '0'
    }
    
    it("should return '4' for Hydrographics") {
      uwp.getHydrographics shouldBe '4'
    }
    
    it("should return 'X' for Population") {
      uwp.getPopulation shouldBe 'X'
    }
    
    it("should return 'X' for Government") {
      uwp.getGovernment shouldBe 'X'
    }
    
    it("should return 'X' for Law Level") {
      uwp.getLawLevel shouldBe 'X'
    }
    
    it("should return 'X' for Tech Level") {
      uwp.getTechLevel shouldBe 'X'
    }
  }
}
