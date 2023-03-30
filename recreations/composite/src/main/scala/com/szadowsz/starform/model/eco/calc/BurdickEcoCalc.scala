//package com.szadowsz.starform.model.eco.calc
//
//import com.szadowsz.starform.model.eco.constants.EcoConstants
//import com.szadowsz.starform.unit.UnitConverter
//
///**
//  * Created on 16/04/2017.
//  */
//class BurdickEcoCalc extends EcoCalc with EcoConstants {
//
//  override def calcAveragedAtomicValues(zone: Int): (Double, Double) = {
//    zone match {
//      case 1 =>
//        (15.0, 8.0)
//      case 2 =>
//        (10.0, 5.0)
//      case _ =>
//        (10.0, 5.0)
//    }
//  }
//
//  override def empiricalDensity(mass: Double, axis: Double, ecosphere: Double): Double = {
//    val massInEM = UnitConverter.solarMassToEarthMass(mass) // convert to be in terms of the mass of earth
//    val temp = Math.pow(massInEM, 0.125)
//    temp * Math.pow(ecosphere / axis, 0.25) * 1.2
//
//  }
//
//  override def radiusAndDensity(mass: Double, axis: Double, meanHabitableRadius: Double, isGiant: Boolean, zone: Int): (Double, Double) = {
//    if (!isGiant) {
//      val (atomicWeight, atomicNum) = calcAveragedAtomicValues(zone) // TODO build better composition modelling
//      val equatorialRadius = kothariRadius(mass, atomicWeight, atomicNum)
//      val density = volumeDensity(mass, equatorialRadius)
//      (equatorialRadius, density)
//    } else {
//      val density = empiricalDensity(mass, axis, meanHabitableRadius)
//      val equatorialRadius = volumeRadius(mass, density)
//      (equatorialRadius, density)
//    }
//  }
//}
