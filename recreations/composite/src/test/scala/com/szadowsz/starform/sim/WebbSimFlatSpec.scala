//package com.szadowsz.starform.sim
//
//import com.szadowsz.starform.profile.starform.{FoggProfile, FolkinsProfile}
//import org.scalatest.{FlatSpec, Matchers}
//
///**
//  * Created on 02/05/2017.
//  */
//class WebbSimFlatSpec extends FlatSpec with Matchers {
//
//  behavior of "The Webb Implementation of Accrete Simulation"
//
//  it should "be able to replicate results" in {
//    val starform = WebbSimulation(new FoggProfile())
//    val system1 = starform.generateSystem()
//    val system2 = starform.generateSystem(Option(system1.seed))
//
//    system2.seed should be (system1.seed)
//
//    system2.planets.length should be (system1.planets.length)
//
//    system2.planets should contain theSameElementsAs system1.planets
//  }
//}
