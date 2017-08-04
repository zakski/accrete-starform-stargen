package com.szadowsz.starform.system

import com.szadowsz.starform.model.SimulationStats
import com.szadowsz.starform.system.bodies.{Planet, Star}

/**
  * Created on 03/10/2016.
  */
case class StarSystem(seed: Long, stats: SimulationStats, star : Star, planets : List[Planet])