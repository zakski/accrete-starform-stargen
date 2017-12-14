// TODO utilise law of large numbers better
package com.szadowsz.starform2.model.accrete.calc.insert

import com.szadowsz.starform2.DoleSimulation
import com.szadowsz.starform2.model.accrete.AccreteProfile
import com.szadowsz.starform2.model.accrete.calc.AccreteInsertStrat
import com.szadowsz.starform2.model.accrete.consts.{AccreteConstants, DoleConstants}
import com.szadowsz.starform2.profile.DoleProfile
import com.szadowsz.starform2.rand.gen.{JDKRandGen, RandGenTrait}
import com.szadowsz.starform2.system.AccreteSystem
import org.scalatest.{FunSpec, Matchers}

/**
  *
  *
  * Created on 21/08/2017.
  */
class InsertionFunSpec extends FunSpec with Matchers {


  val doleProfile = new DoleProfile()

  val doleSystem: AccreteSystem = DoleSimulation(doleProfile).generateSystem(Some(1))

  val bandProfile = new AccreteProfile() {

    override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = BandInsertStrat(aConst)

    override def buildRand(): RandGenTrait = new JDKRandGen()

    override protected val accConsts: AccreteConstants = new DoleConstants
  }

  val bandSystem: AccreteSystem = DoleSimulation(bandProfile).generateSystem(Some(1))


  val folkinsProfile = new AccreteProfile() {

    override def buildInsertStrat(aConst: AccreteConstants): AccreteInsertStrat = new FolkinsInsertStrat(aConst)

    override def buildRand(): RandGenTrait = new JDKRandGen()

    override protected val accConsts: AccreteConstants = new DoleConstants
  }

  val folkinsSystem: AccreteSystem = DoleSimulation(folkinsProfile).generateSystem(Some(1))


  describe("Random Insertion Strategy") {

    it("should have injected more planetismals than the band strategy") {
      doleSystem.stats.injectedNuclei should be >= bandSystem.stats.injectedNuclei
    }

    it("should have injected more planetismals than the folkins strategy") {
      doleSystem.stats.injectedNuclei should be >= folkinsSystem.stats.injectedNuclei
    }

    it("should have rejected more planetismals than the band strategy") {
      doleSystem.stats.rejectedNuclei should be >= bandSystem.stats.rejectedNuclei
    }

    it("should have rejected more planetismals than the folkins strategy") {
      doleSystem.stats.rejectedNuclei should be >= folkinsSystem.stats.rejectedNuclei
    }

    it("should have more merged planetismals than the band strategy") {
      doleSystem.stats.mergedNuclei should be >= bandSystem.stats.mergedNuclei
    }

    it("should have more merged planetismals than the folkins strategy") {
      doleSystem.stats.mergedNuclei should be >= folkinsSystem.stats.mergedNuclei
    }

    it("should have taken longer than the band strategy") {
      doleSystem.stats.timeElapsed should be >= bandSystem.stats.timeElapsed
    }

    it("should have taken longer than the folkins strategy") {
      doleSystem.stats.timeElapsed should be >= folkinsSystem.stats.timeElapsed
    }

    it("should have a higher max mass than the band strategy") {
      doleSystem.stats.maxMass should be >= bandSystem.stats.maxMass
    }

    it("should have a higher max mass than the folkins strategy") {
      doleSystem.stats.maxMass should be >= folkinsSystem.stats.maxMass
    }

    it("should have a lower min mass than the band strategy") {
      doleSystem.stats.minMass should be <= bandSystem.stats.minMass
    }

    it("should have a lower min mass than the folkins strategy") {
      doleSystem.stats.minMass should be <= folkinsSystem.stats.minMass
    }


    it("should have a lower avg mass than the band strategy") {
      doleSystem.stats.avgMass should be <= bandSystem.stats.avgMass
    }

    it("should have a lower avg mass than the folkins strategy") {
      doleSystem.stats.avgMass should be <= folkinsSystem.stats.avgMass
    }

    it("should have a lower std mass than the band strategy") {
      doleSystem.stats.stdMass should be <= bandSystem.stats.stdMass
    }

    it("should have a lower std mass than the folkins strategy") {
      doleSystem.stats.stdMass should be <= folkinsSystem.stats.stdMass
    }
  }

  describe("Folkins Insertion Strategy") {

    it("should have injected more planetismals than the band strategy") {
      folkinsSystem.stats.injectedNuclei should be >= bandSystem.stats.injectedNuclei
    }

    it("should have rejected more planetismals than the band strategy") {
      folkinsSystem.stats.rejectedNuclei should be >= bandSystem.stats.rejectedNuclei
    }

    it("should have more merged planetismals than the band strategy") {
      folkinsSystem.stats.mergedNuclei should be >= bandSystem.stats.mergedNuclei
    }

    it("should have taken longer than the band strategy") {
      folkinsSystem.stats.timeElapsed should be >= bandSystem.stats.timeElapsed
    }

    it("should have a higher max mass than the band strategy") {
      folkinsSystem.stats.maxMass should be >= bandSystem.stats.maxMass
    }

    it("should have a lower avg mass than the band strategy") {
      folkinsSystem.stats.avgMass should be <= bandSystem.stats.avgMass
    }

    it("should have a lower std mass than the band strategy") {
      folkinsSystem.stats.stdMass should be <= bandSystem.stats.stdMass
    }

  }
}
