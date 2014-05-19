package com.hipposretribution.system.formstar;

import java.util.Random;

import com.hipposretribution.system.formstar.accrete.AccretionProcess;
import com.hipposretribution.system.formstar.planetoid.Planet;
import com.hipposretribution.system.formstar.star.Star;

public class SystemGen {

	private SystemGen() {
	}

	
	public static SolarSystem generate(Random rand, boolean moons, boolean verbose) {
		
		// Create the Star
		SolarSystem sys = new SolarSystem(Star.generate(rand));

		
		// Create the Planets and Moons, if applicable
		AccretionProcess accrete = new AccretionProcess(rand, moons, verbose);
		sys.innermost = accrete.accretePlanetMoons(sys.sun);
		
		if (verbose){
			for(Planet plan = sys.innermost; plan != null; plan = plan.next){
				System.out.println(plan.toString());
			}
		}
		
		return sys;
	}
	
	public static void main(String args[]){
		SystemGen.generate(new Random(1), false, true);
	}
}
