package com.szadowsz.starform.planets

import org.scalatest.funspec.AnyFunSpec
import org.scalatest.matchers.should.Matchers

class StarformFunSpec extends AnyFunSpec with Matchers {
  
  /**
   * Higher than I would like due to approximate values of the orbital statistics found online
   */
  protected val orbitalTolerance : Double = 0.05
}
