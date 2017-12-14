package com.szadowsz.starform2.sim

import com.szadowsz.starform2.BurdickSimulation
import com.szadowsz.starform2.profile.FoggProfile
import org.scalatest.{FlatSpec, Matchers}

/**
  * 03/10/2016.
  */
class FoggSimFlatSpec extends FlatSpec with Matchers {

  behavior of "The Fogg Implementation of Accrete Simulation"

  it should "be able to replicate results" in {
    val starform = BurdickSimulation(new FoggProfile())
    val system1 = starform.generateSystem()
    val system2 = starform.generateSystem(Option(system1.seed))

    system2.seed should be (system1.seed)

    system2.planets.length should be (system1.planets.length)

    system2.planets should contain theSameElementsAs system1.planets
  }
}
