package com.szadowsz.starform.model.uwp

/**
  * Useful for at a glance categorization.
  *
  *   Starport -1st digit
  *   Size -2nd digit
  *   Atmosphere -3rd digit
  *   Hydrographics -4th digit
  *   Population -5th digit
  *   Government -6th digit
  *   Law level -7th digit
  *   Tech level -8th digit
  *
  *   As in A678945-9 or A-867974-8
  *
  * See Traveller SRD doc for more details and licence.
  *
  * Created on 16/04/2017.
  */
trait UWPCalc {
  //
  //  if (isGasGiant)
  //    fprintf(f,"%s gas giant\n",(isGasGiant==1) ? "Small" : ((isGasGiant==2) ? "Large" : "Brown Dwarf"));
  //  else
  //  fprintf(f,"%X%X%XXXX\n",(int)(radius/800.0),getAtmRate(),(int)((hydrosphere+iceCover)*10.0));
  //
  //  while(node2)
  //  {
  //    fprintf(f,"                               %3d %7.3f   ",moonCount++,node2->axis*CM_PER_AU/CM_PER_KM/radius/2.0);
  //    if(node2->radius >800.0 ||node2->isPlanetoid ) fprintf(f,"   %X%X%XXXX\n",(int)(node2->radius/800.0),node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));
  //    else fprintf(f,"   S%X%XXXX\n",node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));
  //
  //    node2=node2->nextPlanet;
  //  }
  //  fprintf(f,"\n");

  /**
    * Original Algorithm uses (int)(radius/800.0)
    *
    * @param radius
    * @return
    */
  protected def calcUWPSize(radius: Double): Char = {
    radius match {
      case r if r <= 800.0 => '0'
      case r if r <= 1600.0 => '1'
      case r if r <= 3200.0 => '2'
      case r if r <= 4800.0 => '3'
      case r if r <= 6400.0 => '4'
      case r if r <= 8000.0 => '5'
      case r if r <= 9600.0 => '6'
      case r if r <= 11200.0 => '7'
      case r if r <= 12800.0 => '8'
      case r if r <= 14400.0 => '9'
      case _ => 'A'
    }
  }

  /**
    * Original Algorithm uses
    * int planets::getAtmRate(void) {
    * if(surfacePressure<10.0) return 0;
    * else if(surfacePressure<100.0) return 1;
    * else if(surfacePressure<=400.0) return 3;
    * else if(surfacePressure<=750.0) return 5;
    * else if(surfacePressure<1500.0) return 6;
    * else if(surfacePressure<2500.0) return 8;
    * else return 14;
    * }
    *
    * @param surfacePressure
    * @return
    */
  protected def calcUWPAtmos(surfacePressure: Double): Char = {
    if (surfacePressure < 10.0) '0'
    else if (surfacePressure < 100.0) '1'
    else if (surfacePressure <= 400.0) '3'
    else if (surfacePressure <= 750.0) '5'
    else if (surfacePressure < 1500.0) '6'
    else if (surfacePressure < 2500.0) '8'
    else 'D'
  }

  /**
    * original alg(int)((node2->hydrosphere+node2->iceCover)*10.0)
    *
    * @param hydrosphere
    * @param iceCover
    * @return
    */
  protected def calcUWPHydrographics(hydrosphere: Double, iceCover: Double): Char = {
    val lvl = ((hydrosphere + iceCover) * 10.0).floor.toInt
    lvl match {
      case percent if percent <= 5 => '0'
      case percent if percent <= 15 => '1'
      case percent if percent <= 25 => '2'
      case percent if percent <= 35 => '3'
      case percent if percent <= 45 => '4'
      case percent if percent <= 55 => '5'
      case percent if percent <= 65 => '6'
      case percent if percent <= 75 => '7'
      case percent if percent <= 85 => '8'
      case percent if percent <= 95 => '9'
      case _ => 'A'
    }
  }
}
