package com.szadowsz.formstar;

import com.szadowsz.formstar.planetoid.Planet;
import com.szadowsz.formstar.star.Star;

/**
 * Class to store system information
 *   
 * @author zakski
 *
 */
public class SolarSystem {

	public Star sun; // the sun TODO look into binary systems
	public Planet innermost; // innermost system planet
	public int planetCount; // number of planets

	public SolarSystem(Star star) {
		sun = star;
	}

}
