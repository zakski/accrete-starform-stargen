package com.szadowsz.starform.sim.fogg

import com.szadowsz.starform.config.fogg.FoggProfile
import com.szadowsz.starform.sim.calc.dole.planetismal.RandInsertStrat
import com.szadowsz.starform.sim.fogg.FoggSimulation
import org.scalatest.flatspec.*
import org.scalatest.matchers.should.*

import java.util.Random

/**
  * 03/10/2016.
  */
class FoggSimFlatSpec extends AnyFlatSpec with Matchers {

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
