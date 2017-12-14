package com.szadowsz.starform2.model.star.calc

import com.szadowsz.starform2.model.star.consts.KerisStarConstants
import org.scalatest.{FlatSpec, Matchers}

/**
  * 03/10/2016.
  */
class KerisStarCalcFlatSpec extends FlatSpec with Matchers {

  behavior of "The Keris Star Calculator"

  val calc = new KerisStarCalc(new KerisStarConstants)

  it should "return O0 when stellar Temperature is 1e10K" in {
    val temp = 1e10
    val (c, sub) = calc.findClass(temp)

    c should be('O')
    sub should be(0)
  }

  it should "return B5 when stellar Temperature is 21,000K" in {
    val temp = 21000
    val (c, sub) = calc.findClass(temp)

    c should be('B')
    sub should be(5)
  }

  it should "return A9 when stellar Temperature is 7,501K" in {
    val temp = 7501
    val (c, sub) = calc.findClass(temp)

    c should be('A')
    sub should be(9)
  }
}
