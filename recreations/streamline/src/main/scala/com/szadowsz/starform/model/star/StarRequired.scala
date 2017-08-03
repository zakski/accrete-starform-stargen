package com.szadowsz.starform.model.star

import com.szadowsz.starform.system.bodies.Star

/**
  * Created on 13/04/2017.
  */
trait StarRequired {

  protected var star : Star = _

  def getStar: Star = star

  def setStar(s : Star): Unit = {
    star = s
  }
}
