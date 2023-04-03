package com.szadowsz.starform.sim.folkins

import com.szadowsz.starform.config.folkins.FolkinsProfile
import org.scalatest.flatspec.*
import org.scalatest.matchers.should.*
/**
  * 03/10/2016.
  */
class FolkinsSimFlatSpec extends AnyFlatSpec with Matchers {

  behavior of "The Folkins Implementation of Accrete Simulation"

  it should "be able to replicate results" in {
    val starform = FolkinsSimulation(new FolkinsProfile())
    val system1 = starform.generateSystem()
    val system2 = starform.generateSystem(Option(system1.seed))

    system2.seed should be (system1.seed)

    system2.planets.length should be (system1.planets.length)

    system2.planets should contain theSameElementsAs system1.planets
  }
}
