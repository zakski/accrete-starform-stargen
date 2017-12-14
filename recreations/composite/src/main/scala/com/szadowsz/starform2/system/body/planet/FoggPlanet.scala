package com.szadowsz.starform2.system.body.planet

import java.text.DecimalFormat

import com.szadowsz.starform2.system.body.Planetismal

/**
  * Class to represent TODO.
  *
  * @param proto the basic characteristics of the accreted planetary body.
  *
  * @author Zakski : 20/07/2015.
  */
class FoggPlanet(
                  proto: Planetismal,
                  val equatorialRadius: Double,
                  val density: Double,
                  val orbitLength: Double,
                  val dayLength: Double,
                  val gravity: Double,
                  val surfacePressure: Double,
                  val hydrosphere: Double,
                  val cloudCover: Double,
                  val iceCover: Double,
                  val albedo: Double,
                  val surfaceTemperature: Double,
                  val tilt: Double
                )
  extends Planetismal {

  /**
    * The mass of the body.
    *
    * @note unit of value is Solar Masses.
    */
  override val mass: Double = proto.mass

  /**
    * The semi-major axis of the body's orbit.
    *
    * @note unit of value is AU.
    */
  override val axis: Double = proto.axis

  /**
    * The Eccentricity of the body's orbit. How wildly it deviates from the semi-major axis during the course of one
    * revolution around its planetary body.
    *
    * @note value between 0.0 (inclusive) and 1.0 (exclusive), this range is essential for the body to stay
    *       in the system.
    */
  override val ecc: Double = proto.ecc

  /**
    * The closest to the star that the planet will be during its orbit.
    *
    * @note unit of value is AU.
    */
  override val perihelion: Double = proto.perihelion

  /**
    * The furthest from the star that the planet will be during its orbit..
    *
    * @note unit of value is AU.
    */
  override val aphelion: Double = proto.aphelion

  /**
    * Whether the planet has surpassed its critical mass limit and become a gas giant.
    */
  override val isGasGiant: Boolean = proto.isGasGiant


  /**
    * Method to supply String representation of the proto planet.
    *
    * @return current status of the  proto planet in String form.
    */
  override def toString: String = { // TODO finish off
    val df: DecimalFormat = new DecimalFormat("#.00000")
    val df2: DecimalFormat = new DecimalFormat("#.00000E00")
    val df3: DecimalFormat = new DecimalFormat("#.000")

    s"""
  |  axis: ${df.format(axis)} AU
  |  eccentricity: ${df.format(ecc)}
  |  mass: ${df2.format(mass)}M☉
  |  gasGiant: ${if (isGasGiant) "Y" else "N"}
  |  equatorial radius: ${df3.format(equatorialRadius)} km
  |  density: ${df3.format(density)} g/cc
  |  gravity: ${df3.format(gravity)} m/sec2
  |  axial tilt: ${df3.format(tilt)}
  |  albedo: ${df3.format(albedo)}
  |  year: ${df3.format(orbitLength)} days
  |  day: ${df3.format(dayLength)} hours
    """.stripMargin
    //  if (!(node1->gas_giant))
    //  {
    //  build.append(" Surface Gravity (in Earth gees): %5.2lf\n",node1->surface_grav);
    //  build.append(" Boiling point of water (celcius): %4.1lf\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
    //  build.append(" Surface Pressure (in atmospheres): %5.3lf",(node1->surface_pressure / 1000.0));
    //  if ((node1->greenhouse_effect) && (node1->surface_pressure > 0.0))
    //    build.append("   RUNAWAY GREENHOUSE EFFECT\n");
    //  else
    //    build.append("\n");
    //  build.append(" Surface temperature (Celcius): %4.2lf\n",(node1->surface_temp - KELVIN_CELCIUS_DIFFERENCE));
    //  build.append(" Hydrosphere percentage: %6.2lf\n",(node1->hydrosphere * 100.0));
    //  build.append(" Cloud cover percentage: %6.2lf\n",(node1->cloud_cover * 100));
    //  build.append(" Ice cover percentage: %6.2lf\n",(node1->ice_cover * 100));
    //  }
  }
}
