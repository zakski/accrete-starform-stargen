package com.szadowsz.starform.model.eco.calc

/**
  * Created on 26/07/2017.
  */
class KerisEcoCalc extends BurdickEcoCalc {

  protected def kerisLimit(x: Double): Double = {
    x / Math.sqrt(Math.sqrt(1 + x * x * x * x))
  }

  protected def kerisSoft(v: Double, max: Double, min: Double): Double = {
    val dv = v - min
    val dm = max - min
    (kerisLimit(2 * dv / dm - 1) + 1) / 2 * dm + min
  }

  def calcTempLimits(ecc : Double, surf_pressure : Double, surf_temp : Double, axial_tilt : Double, day : Double): (Double, Double, Double, Double) = {
    val pressmod = 1 / Math.sqrt(1 + 20 * surf_pressure / 1000.0)
    val ppmod = 1 / Math.sqrt(10 + 5 * surf_pressure / 1000.0)
    val tiltmod = Math.cos(axial_tilt * Math.PI / 180) * Math.pow(1 + ecc, 2)
    val daymod = 1 / (200 / day + 1)
    val mh = Math.pow(1 + daymod, pressmod)
    val ml = Math.pow(1 - daymod, pressmod)
    val max = surf_temp + Math.sqrt(surf_temp) * 10
    val min = surf_temp / Math.sqrt(day + 24)

    val hi = mh * surf_temp
    val lo = Math.max(ml * surf_temp,min)
    val sh = hi + Math.pow((100 + hi) * tiltmod, Math.sqrt(ppmod))
    val wl = Math.max(lo - Math.pow((150 + lo) * tiltmod, Math.sqrt(ppmod)),0)

    (kerisSoft(hi, max, min),kerisSoft(lo, max, min),kerisSoft(sh, max, min),kerisSoft(wl, max, min))
  }
}
