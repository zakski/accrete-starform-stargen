package com.szadowsz.starform.model

import com.szadowsz.starform.system.bodies.base.Star

/**
  * Created on 13/04/2017.
  */
trait StarRequired {

  protected var star : Star = null

  def getStar: Star = star

  def setStar(s : Star): Unit = {
    star = s
  }
}
