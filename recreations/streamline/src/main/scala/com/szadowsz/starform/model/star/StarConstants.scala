// scalastyle:off method.name
package com.szadowsz.starform.model.star

/**
  * Star Generation Constants Specific to Martyn J. Fogg's adaptation of Dole's paper.
  *
  * @author Zakski : 26/06/2015.
  */
class StarConstants {


  val MINMAG : Int = -7

  /**
    * This table gives the approximate relative numbers of stars of the various spectral types and luminosity classes, the units are stars per million cubic
    * parsecs. The program totals this information and computes a cumulative distribution function from it for actual use.  The spectral classes range from O
    * on the left to M on the right, the luminosities from an absolute magnitude of -7 at the top to +16 at the bottom.  Thus, the table looks roughly like
    * the traditional Hertzsprung-Russell diagram.
    *
    * One thing you'll notice about this, there's a *lot* of red dwarfs in a realistic distribution, a star like the sun is in the top 10% of the population.
    * This makes the occurrence of habitable planets pretty low.
    *
    * Most of this information is from a message I recived from John Carr <athena.mit.edu!jfc> on April 19/88, he didn't mention his source though he did
    * make the comment that "the birthrate function is much flatter at high luminosities than the luminosity function, due to the short lifetime of high-mass
    * stars.  This is important for young areas."  I don't think that idea is accounted for here.
    */
  val starCounts: Array[Array[Double]] = Array(
    Array(2E-4, 5E-4, 3E-4, 3E-4, 3E-5, 0, 0),
    Array(5E-4, 2.5E-3, 1E-3, 1E-3, 1E-4, 4E-4, 4E-4),
    Array(.001, .025, .010, .006, .008, .004, .010),
    Array(.003, .16, .01, .016, .025, .012, .012),
    Array(.01, .50, .05, .08, .08, .1, .06),
    Array(.01, 2.5, .08, .2, .3, .6, .4),
    Array(.01, 12.5, 1, 1.6, 1, 2.5, 3),
    Array(.001, 20, 20, 2, 8, 25, 10),
    Array(0, 30, 100, 30, 30, 120, 10),
    Array(0, 20, 200, 160, 50, 110, 0),
    Array(0, 10, 80, 700, 150, 100, 0),
    Array(0, 0, 30, 1200, 700, 100, 0),
    Array(0, 0, 0, 600, 2000, 300, 0),
    Array(0, 0, 0, 200, 1500, 1500, 10),
    Array(0, 0, 0, 100, 800, 3000, 100),
    Array(0, 0, 0, 10, 400, 2500, 1000),
    Array(0, 0, 0, 0, 200, 1500, 3000),
    Array(0, 10, 0, 0, 0, 400, 8000),
    Array(0, 100, 30, 10, 0, 200, 9000),
    Array(0, 200, 400, 100, 0, 100, 10000),
    Array(0, 400, 600, 300, 100, 400, 10000),
    Array(0, 800, 1000, 1000, 600, 800, 10000),
    Array(0, 1500, 2000, 1000, 1500, 1200, 8000),
    Array(0, 3000, 5000, 3000, 3000, 0, 6000)
  )

  /**
    * Absolute magnitude - anything of number or below is that class e.g Class G, mag 5.0 is class V.  Most of this is guesstimates from a H-R diagram.
    */
  val magLumClass: Array[Array[Double]] = Array(
    /* Ia     Ib      II      III      IV      V      VI    VII */
    Array(-6.5, -6.0, -5.0, -4.0, -3.0, -1.0, 1.0, 20.0), /* O */
    Array(-6.5, -6.0, -3.5, -3.0, -2.0, 2.0, 4.0, 20.0), /* B */
    Array(-6.5, -5.0, -3.0, -0.5, 0.5, 2.5, 5.0, 20.0), /* A */
    Array(-6.5, -5.0, -2.0, 1.5, 2.5, 5.0, 9.0, 20.0), /* F */
    Array(-6.5, -5.0, -2.0, 2.5, 3.5, 7.0, 10.0, 20.0), /* G */
    Array(-6.5, -5.0, -2.5, 3.0, 5.5, 10.0, 20.0, 20.0), /* K */
    Array(-6.5, -5.0, -2.5, 2.0, 2.0, 14.0, 20.0, 20.0) /* M */
  )

  val spectralClasses: Array[Char] = Array('O', 'B', 'A', 'F', 'G', 'K', 'M')

  val luminosityClasses: Array[String] = Array("Ia", "Ib", "II", "III", "IV", "V", "VI", "VII")


  /**
    * Optimistic constant specified by Fogg in "3. Characteristics of The Primary Star" in "Extra-solar Planetary Systems: A Microcomputer Simulation", based
    * on greenhouse models by Michael H. Hart.
    *
    * @see p. 503, Extra-solar Planetary Systems: A Microcomputer Simulation - Martyn J. Fogg
    * @see var GREENHOUSE_EFFECT_CONST, line 50 in const.h - Mat Burdick (accrete)
    * @see method GenStar, line 168 in Genstar.c - Andrew Folkins (accretion)
    * @see method GenStar, line 215 in genstar.c - Keris (accretion v1)
    * @see method GenStar, lines 292 in genstar.cc - Keris (accretion v2)
    * @see var GREENHOUSE_EFFECT_CONST, line 51 in const.h - Keris (starform)
    * @see var GREENHOUSE_EFFECT_CONST, line 48 in const.h - Mat Burdick (starform)
    * @see var GREENHOUSE_EFFECT_CONST, line 97 in PhysicalConstants.java - Carl Burke (starform)
    *
    */
  val GREENHOUSE_EFFECT_CONST: Double = 0.93
}
