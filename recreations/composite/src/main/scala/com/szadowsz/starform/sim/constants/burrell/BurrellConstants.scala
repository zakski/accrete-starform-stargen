// scalastyle:off method.name
package com.szadowsz.starform.sim.constants.burrell

import com.szadowsz.starform.sim.constants.AccreteConstants

/**
  * Created on 11/04/2017.
  */
class BurrellConstants extends AccreteConstants {

  /**
    * The Cloud Eccentricity coefficient. Represent the average eccentricity of particles in the cloud. Used in dust band width calculations to more accurately
    * simulate particle orbits in the cloud. Represented by W in "Formation of Planetary Systems by Aggregation: A Computer Simulation" in "c) Aggregation".
    *
    * Most use 0.2, but Ian Burrell uses 0.25 for its value.
    *
    * @note tested between 0.0 and 0.25
    * @note Dole recommends 0.2 or 0.25 for solar systems resembling our own.
    * @note input parameter for the accretion process. value was chosen for its ability to produce sensible eccentricities; other values may not produce
    *       desired output.
    *
    * @see pp. 20-21, Formation of Planetary Systems by Aggregation: A Computer Simulation - Stephen H. Dole
    * @see const var CLOUD_ECCENTRICITY, in DoleParams.java - Burrell.1997
    */
  override def CLOUD_ECCENTRICITY : Double = 0.25
}
