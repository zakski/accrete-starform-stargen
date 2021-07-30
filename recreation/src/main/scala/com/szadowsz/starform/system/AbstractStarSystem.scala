package com.szadowsz.starform.system

import com.szadowsz.starform.model.accrete.AccreteStats
import com.szadowsz.starform.system.planets.Planetismal
import com.szadowsz.starform.system.star.Star

/**
  * Created on 03/10/2016.
  */
abstract class AbstractStarSystem[S <: Star, R <: AccreteStats, P <: Planetismal] {

  val star: S

  val seed: Long

  val stats: R

  val planets: List[P]

  override def toString: String = {
    s"""
       |$stats
       |${planets.zipWithIndex.map { case (pl, i) => s"\nPlanet $i: $pl" }.mkString}
    """.stripMargin
  }
}
