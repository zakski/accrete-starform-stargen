package com.szadowsz.starform2.model.star.consts


/**
  * Created on 15/08/2017.
  */
class KerisStarConstants extends FoggStarConstants {

  /**
    * Trimmed down list as Keris does not use full stellar class description like Folkins Did
    *
    * @note temperature is the maximum for that class.
    *
    * @see var StellarType, line 20 in steltype.c - Keris (starform)
    */
  val starType: Array[(Char, Double)] = Array(
    ('O', 1e10),
    ('B', 30000),
    ('A', 12000),
    ('F', 7500),
    ('G', 6000),
    ('K', 5000),
    ('M', 3500),
    ('D', 1500)
  )
}
