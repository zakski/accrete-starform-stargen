package com.szadowsz.starform.sim

import java.util.Random

import com.szadowsz.starform.model.accrete.calc.insert.RandInsertStrat
import com.szadowsz.starform.profile.starform.FoggProfile
import org.scalatest.{FlatSpec, Matchers}

/**
  * 03/10/2016.
  */
class FoggSimFlatSpec extends FlatSpec with Matchers {

  behavior of "The Fogg Implementation of Accrete Simulation"

  it should "be able to replicate results" in {
    val starform = FoggSimulation(new FoggProfile())
    val system1 = starform.generateSystem()
    val system2 = starform.generateSystem(Option(system1.seed))

    system2.seed should be (system1.seed)

    system2.planets.length should be (system1.planets.length)

    system2.planets should contain theSameElementsAs system1.planets
  }
}
