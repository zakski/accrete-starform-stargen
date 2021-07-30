package com.szadowsz.starform.system.star

final class Sol extends Star {

  /**
   * The mass of the Star. Naturally the unit of the member is Solar Mass. Most iterations expect a pseudo-random value between 0.6 and 1.3 M☉. This is due to
   * the original simulation calculations and values being extrapolated from research on our own star. This variance is introduced in "Extra-solar Planetary
   * Systems: A Microcomputer Simulation", prior to that the star was assumed to be 1 M☉ and did not need to be factored into our calculations.
   *
   * @note unit of value is Solar Masses.
   */
  override val mass: Double = 1.0

  /**
   * The luminosity of the Star. A measurement of how bright the star is. This value can be approximated from the mass using the mass-luminosity relation, if
   * required.
   *
   * @note unit of value is Solar Luminosity.
   */
  override val luminosity: Double = 1.0
}
