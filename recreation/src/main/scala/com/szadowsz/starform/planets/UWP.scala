package com.szadowsz.starform.planets

object UWP {
  
  /**
   * Diameter in KM
   */
  protected val size: Array[Int] = Array(800, 1600, 3200, 4800, 6400, 8000, 9600, 11200, 12800, 14400)
  
  /**
   * Percentage
   */
  protected val hydrographics: Array[Int] = Array(5, 15, 25, 35, 45, 55, 65, 75, 85, 95)
  
  /**
   * Traveller Values:
   * 0 -> None -> 0.00
   * 1 -> Trace -> 0.001 to 0.09
   * 2 -> Very Thin, Tainted -> 0.1 to 0.42
   * 3 -> Very Thin -> 0.1 to 0.42
   * 4 -> Thin, Tainted -> 0.43 to 0.7
   * 5 -> Thin -> 0.43 to 0.7
   * 6 -> Standard -> 0.71–1.49
   * 7 -> Standard, Tainted -> 0.71–1.49
   * 8 -> Dense 1.5 to 2.49
   * 9 -> Dense, Tainted 1.5 to 2.49 Filter
   * A -> Exotic Varies Air Supply
   * B -> Corrosive Varies Vacc Suit
   * C -> Insidious  Varies Vacc Suit
   * D -> Dense, High 2.5+
   * E -> Thin, Low 0.5 or less
   * F -> Unusual Varies Varies
   */
  protected val pressure: Map[Double, Char] = Map(
    10.0 -> '0',
    100.0 -> '1',
    400.0 -> '3',
    750.0 -> '5',
    1500.0 -> '6',
    2500.0 -> '8'
  )
  
  
  /**
   * Original Algorithm uses (int)(radius/800.0)
   *
   * @param radius
   * @return
   */
  protected def calcUWPSize(radius: Double): Char = size.find(radius*2 <= _).map(bin => size.indexOf(bin).toString.head).getOrElse('A')
  
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
  protected def calcUWPAtmos(surfacePressure: Double): Char = pressure.find { case (p, _) => surfacePressure < p }.map(_._2).getOrElse('D')
  
  /**
   * original alg(int)((node2->hydrosphere+node2->iceCover)*10.0)
   *
   * @param hydrosphere
   * @param iceCover
   * @return
   */
  protected def calcUWPHydrographics(hydrosphere: Double, iceCover: Double): Char = {
    val lvl = ((hydrosphere + iceCover) * 100.0).floor.toInt
    hydrographics.find(lvl <= _).map(bin => hydrographics.indexOf(bin).toString.head).getOrElse('A')
  }
}
  
/**
 * Universal World Profile - Useful for at a glance categorization.
 *
 * Starport -1st digit
 * Size -2nd digit
 * Atmosphere -3rd digit
 * Hydrographics -4th digit
 * Population -5th digit
 * Government -6th digit
 * Law level -7th digit
 * Tech level -8th digit
 *
 * As in A678945-9 or A-867974-8
 *
 * See Traveller SRD doc for more details and licence.
 *
 * Created on 16/04/2017.
 */
class UWP private(s : Char, a : Char, h : Char) {
  
  private var size : Char = s
  private var atmos : Char = a
  private var hydro : Char = h
  
  private var starport : Char = 'X'
  private var pop : Char = 'X'
  private var government : Char = 'X'
  private var law : Char = 'X'
  private var tech : Char = 'X'
  
  def this(equatorialRadius : Double, surfacePressure: Double, hydrosphere : Double, iceCover : Double){
    this(UWP.calcUWPSize(equatorialRadius),UWP.calcUWPAtmos(surfacePressure),UWP.calcUWPHydrographics(hydrosphere,iceCover))
  }
  
  def this(){
    this('X','X','X')
  }
  
  
  def getStarportClass : Char = starport
  
  def getSize : Char = size
  def getAtmosphere : Char = atmos
  
  def getHydrographics : Char = hydro
  
  def getPopulation : Char = pop
  
  def getGovernment : Char = government
  
  def getLawLevel : Char = law
  
  def getTechLevel : Char = tech
  
  override def toString: String = {
    val builder = new StringBuilder()
  
    builder += starport
    builder += '-'
    builder += size
    builder += atmos
    builder += hydro
    builder += pop
    builder += government
    builder += law
    builder += '-'
    builder += tech
    
    builder.toString()
  }
}
