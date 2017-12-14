package com.szadowsz.starform.validator

import com.szadowsz.starform.system.bodies.planetoid.FoggPlanet
import com.szadowsz.starform.unit.UnitConverter

/**
  * Created on 10/08/2017.
  */
object HabitabilityValidator {

  def isEarthlike(planet: FoggPlanet): Boolean = {
    val gees = UnitConverter.mSec2ToGs(planet.gravity)
    val relPress = planet.surfacePressure / UnitConverter.EARTH_SURF_PRES_IN_MILLIBARS

    (gees >= .8 && gees <= 1.2) &&
      planet.iceCover <= 10.0 &&
      (planet.cloudCover >= 40.0 && planet.cloudCover <= 80.0) &&
      (planet.hydrosphere >= 50.0 && planet.hydrosphere <= 80.0) &&
      (relPress >= 0.5 && relPress <= 2.0)

    //      (rel_temp 	>= -2.0) &&
    //      (rel_temp 	<= 3.0) &&
    //      (planet->type != tWater) &&
    //    (breathe    == BREATHABLE))
  }
}
