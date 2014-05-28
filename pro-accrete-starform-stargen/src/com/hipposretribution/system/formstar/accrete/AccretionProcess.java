package com.hipposretribution.system.formstar.accrete;

import java.util.Random;

import com.hipposretribution.system.formstar.SolarConst;
import com.hipposretribution.system.formstar.planetoid.Moon;
import com.hipposretribution.system.formstar.planetoid.Planet;
import com.hipposretribution.system.formstar.star.Star;
import com.hipposretribution.utils.random.RandomUtil;

public class AccretionProcess {

	/* Now for some variables global to the accretion process: */
	private boolean verbose; // flag to print off debug info
	private Random rand; // pseudo-random number generator
	private double dustDensity; // current default dust density
	private double innerSweep, outerSweep; // current dust sweep bounds
	private boolean dustRemains; // flag for the existence of dust
	private double criticalMass; // current critical mass limit
	private DustBand dustHead; // head of the dustband linked list
	private Planet innermost; // closest to the sun
	private int planetCount; // planet count
	private boolean moons; // whether or not we should generate moons

	/**
	 * Default Constructor Just sets the verbose flag
	 * 
	 * @param random - pseudo-random number generator
	 * @param genmoons - w
	 * @param debug - debug message flag
	 */
	public AccretionProcess(Random random, boolean genmoons, boolean debug) {
		rand = random;
		moons = genmoons;
		verbose = debug;
	}

	/**
	 * Steps through list of dust bands checking to see if any of those that bands that overlap the given
	 * range have dust present. This was originally done as a quick check with the swept limits using the full
	 * mass for newly injected nuclei.
	 * 
	 * 
	 * 
	 * @param insideRange - the nearest to the star that the protoplanet can pull dust from
	 * @param outsideRange - the farthest from the star that the protoplanet can pull dust from
	 * @return whether or not there is still dust between inside_range and outside_range in this current
	 *         accretion process.
	 */
	private boolean isDustAvailable(double insideRange, double outsideRange) {
		DustBand current = dustHead;
		boolean hasDust = false;

		// this loop finds the dust band whose outer edge is within our inside range.
		while (current != null && current.outerEdge < insideRange) {
			current = current.next;
		}

		// this loop ORs together all of the dust bands from the first one we found
		// until the dust band whose inner edge is outside our outside range.
		while ((current != null) && (current.innerEdge < outsideRange)) {
			hasDust = hasDust || current.hasDust;
			current = current.next;
		}

		return hasDust;
	}

	/**
	 * Method to calculate the mass for the protoplanet
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @param criticalMass - gas giant mass limit
	 * @return the new calculated mass
	 */
	private double accreteDust(double axis, double ecc, double mass, double criticalMass) {
		/* fixed point algorithm: accumulate more mass until the difference is less than .01% of the old mass */
		double currMass = mass, lastMass;
		do {
			lastMass = currMass;
			currMass = collectDust(axis, ecc, currMass, criticalMass, dustHead);
		} while (!(((currMass - lastMass) < (0.0001 * lastMass))));

		// return the new mass added to the seed mass
		return mass + currMass;
	}

	/**
	 * Method to turn all available DustBands into mass for the protoplanet
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @param criticalMass - gas giant mass limit
	 * @return the new calculated mass
	 */
	private double collectDust(double axis, double ecc, double mass, double criticalMass, DustBand band) {
		// base case: if we have gone beyond the last dust band, return 0
		if (band == null) {
			return 0.0;
		}

		// recalculate the inner and outer radii based on the reduced mass
		double reducedMass = AccreteCalc.reducedMargin(mass);
		innerSweep = AccreteCalc.innerSweepLimit(axis, ecc, reducedMass);
		outerSweep = AccreteCalc.outerSweepLimit(axis, ecc, reducedMass);

		// clamp the inner radius to be at least zero
		if (innerSweep < 0.0) {
			innerSweep = 0.0;
		}

		// if the outer edge is less than the accretion inner limit
		if (band.outerEdge <= innerSweep) {
			return collectDust(axis, ecc, mass, criticalMass, band.next);
		}// or if the inner edge is greater than the outer limit, don't collect any more dust.
		else if (band.innerEdge >= outerSweep) {
			return 0.0;
		}

		// if we have dust, use the dust density, otherwise zero
		double dust_density = (band.hasDust) ? dustDensity : 0.0;

		// if the mass is below the critical mass, or there's no gas in this
		// dust band, the density is the overall accretion density;
		// otherwise, use the mass density formula
		double density = (!band.hasGas || (mass < criticalMass)) ? dust_density : AccreteCalc.massDensity(dust_density,
			criticalMass, mass);

		// account for any gaps between the dust edges and the start of
		// the accretion radius
		double bandwidth = (outerSweep - innerSweep);

		double outside = outerSweep - band.outerEdge;
		if (outside < 0.0)
			outside = 0.0;

		double inside = band.innerEdge - innerSweep;
		if (inside < 0.0)
			inside = 0.0;

		double width = bandwidth - outside - inside;

		double term1 = 4.0 * Math.PI * axis * axis;
		double term2 = term1 * reducedMass * (1.0 - ecc * (outside - inside) / bandwidth);
		double volume = term2 * width;

		return (volume * density + collectDust(axis, ecc, mass, criticalMass, band.next));
	}

	/**
	 * Method to split a band into 3 based on a subsumed proto-planet
	 * 
	 * @param band - the band to split
	 * @param hasGas - whether there is gas
	 * @return next band
	 */
	private DustBand splitForSubPlanet(DustBand band, boolean hasGas) {
		// make a new dust lane with min and max for the middle chunk
		DustBand middle = new DustBand(innerSweep, outerSweep, false, band.hasGas && hasGas);

		// make another new dust lane that proceeds from max to the outer edge of band
		DustBand right = new DustBand(outerSweep, band.outerEdge, band.hasDust, band.hasGas);
		right.next = band.next;
		middle.next = right;

		// condense node1's outer edge to the minimum
		band.next = middle;
		band.outerEdge = innerSweep;

		return right.next;
	}

	/**
	 * Method to split a band into 2 based on overlapping a proto-planet's outer edge
	 * 
	 * @param band - the band to split
	 * @param hasGas - whether there is gas
	 * @return next band
	 */
	private DustBand splitOnPlanetMaxEdge(DustBand band, boolean hasGas) {
		DustBand right = new DustBand(outerSweep, band.outerEdge, band.hasDust, band.hasGas);
		right.next = band.next;
		band.next = right;
		band.outerEdge = outerSweep;
		band.hasDust = false;
		band.hasGas = hasGas;
		return right.next;
	}

	/**
	 * Method to split a band into 2 based on overlapping a proto-planet's inner edge
	 * 
	 * @param band - the band to split
	 * @param hasGas - whether there is gas
	 * @return next band
	 */
	private DustBand splitOnPlanetMinEdge(DustBand band, boolean hasGas) {
		DustBand right = new DustBand(innerSweep, band.outerEdge, false, band.hasGas && hasGas);
		right.next = band.next;
		band.next = right;
		band.outerEdge = innerSweep;
		return right.next;
	}

	/**
	 * Split a dust lane into several dust lanes, and mark the dust as used. Returns the next dust lane in the
	 * list.
	 */
	private DustBand splitBands(DustBand band, boolean hasGas) {
		// Case 1: this node subsumes min and max
		if (band.innerEdge < innerSweep && band.outerEdge > outerSweep) {
			return splitForSubPlanet(band, hasGas);

			// Case 2: the node spans across the maximum
		} else if (band.innerEdge < outerSweep && band.outerEdge > outerSweep) {
			return splitOnPlanetMaxEdge(band, hasGas);

			// Case 3: the node spans across the minimum
		} else if (band.innerEdge < innerSweep && band.outerEdge > innerSweep) {
			return splitOnPlanetMinEdge(band, hasGas);

			// Case 4: the node is within or equal to the range
		} else if (band.innerEdge >= innerSweep && band.outerEdge <= outerSweep) {
			// Use up the dust
			band.hasDust = false;

			// if gas was present, it may not be now.
			if (band.hasGas == true)
				band.hasGas = hasGas;

			// proceed
			return band.next;

			// Case 5: No overlap whatsoever
			// in this case, just move on to the next dust band
		} else if (band.outerEdge < innerSweep || band.innerEdge > outerSweep) {
			return band.next;
		}

		// if we make it here, perhaps we have modified this lane sufficiently to
		// the liking of the controlling loop
		return band;
	}

	/**
	 * this function coalesces neighbor dust lanes that have or do not have dust and/or gas
	 * 
	 * @param innerBound - closest to the sun a planet can exist
	 * @param outerBound - furtherest from the sun a planet can exist
	 */
	private void mergeDustBands(double innerBound, double outerBound) {

		for (DustBand lane = dustHead; lane != null; lane = lane.next) {
			// if this node has dust and the node is within the body's inner and outer
			// boundaries, then there is dust left in this simulation.
			if (lane.hasDust && lane.outerEdge >= innerBound && lane.innerEdge <= outerBound) {
				dustRemains = true;
			}

			// get the next lane if possible
			// coalesce these two adjacent dust lanes if they have the same
			// combination of having or lacking dust and gas
			if (lane.next != null && lane.hasDust == lane.next.hasDust && lane.hasGas == lane.next.hasGas) {
				lane.outerEdge = lane.next.outerEdge;
				lane.next = lane.next.next;
			}
		}
	}

	/**
	 * Method to Update (Split/Merge) dust bands based on an inserted planet
	 * 
	 * @param mass - mass of the proto-planet
	 * @param planetInnerBound - closest to the sun that we can form a star
	 * @param planetOuterBound- furthest from the sun that we can form a star
	 */
	private void updateDustLanes(double mass, double planetInnerBound, double planetOuterBound) {

		// begin asserting that there's no dust left. coalesce_dust_lanes will set
		// this value to true if it finds any dust during its coalescing maneuver
		dustRemains = false;

		// this tracks whether or not this planetoid is growing up to be a gas giant
		// or if it is sufficiently massive that it's going to be a planetoid
		boolean gas = (mass <= criticalMass);

		// this loop examines every dust band. it splits dust band such that our min
		// and max values lie at the boundaries of the band. it also consumes the dust
		// and gas in each band within the limits as it goes.
		for (DustBand lane = dustHead; lane != null; lane = splitBands(lane, gas))
			;

		// this loop detects whether or not there is still dust present in the
		// simulation within the overall bounds and simultaneously coalesces neighbor
		// dust lanes that have or do not have dust and/or gas
		mergeDustBands(planetInnerBound, planetOuterBound);
	}

	/**
	 * Method to merge a newly coalesced planet with an existing one
	 * 
	 * @param planet - the existing planet
	 * @param axis - new planet's axis
	 * @param ecc - new planet's eccentricity
	 * @param mass - new planet's mass
	 * @param criticalMass - new planet's critical mass
	 * @param stellarLuminosity - star's luminosity
	 */
	private void mergeTwoPlanets(Planet planet, double axis, double ecc, double mass, double criticalMass,
			double stellarLuminosity) {
		double new_mass = planet.mass + mass;
		double new_axis = new_mass / ((planet.mass / planet.axis) + (mass / axis));
		double term1 = AccreteCalc.calcMergedEccTerm(planet.axis, planet.ecc, planet.mass);
		double term2 = AccreteCalc.calcMergedEccTerm(axis, ecc, mass);
		double term3 = (term1 + term2) / (new_mass * Math.sqrt(new_axis));
		double term4 = 1.0 - term3 * term3;
		double new_ecc = Math.sqrt(Math.abs(term4));
		planet.axis = new_axis;
		planet.ecc = new_ecc;
		planet.gasGiant = planet.gasGiant || mass >= criticalMass;
		criticalMass = AccreteCalc.criticalMass(planet.axis, planet.ecc, stellarLuminosity);
		planet.mass = accreteDust(new_axis, new_ecc, new_mass, criticalMass);
	}

	/**
	 * Method to add a newly coalesced planet
	 * 
	 * @param axis - new planet's axis
	 * @param ecc - new planet's eccentricity
	 * @param mass - new planet's mass
	 */
	private void insertPlanet(double axis, double ecc, double mass) {
		Planet planet = new Planet();
		planet.axis = axis;
		planet.ecc = ecc;
		planet.mass = mass;
		if (planet.mass >= criticalMass) {
			planet.gasGiant = true;
		}

		if (innermost == null) {
			innermost = planet;
		} else if (planet.axis < innermost.axis) {
			planet.next = innermost;
			innermost = planet;
		} else {
			Planet prev = innermost;
			Planet curr = innermost.next;
			while ((curr != null) && (curr.axis < planet.axis)) {
				prev = curr;
				curr = curr.next;
			}
			planet.next = curr;
			prev.next = planet;
		}
	}

	/**
	 * Method to check for collisions between planets and merge them
	 * 
	 * @param axis - new planet's axis
	 * @param ecc - new planet's eccentricity
	 * @param mass - new planet's mass
	 * @param criticalMass - new planet's critical mass
	 * @param stellarLuminosity - star's luminosity
	 * @return true if planets collided, false if not
	 */
	private boolean coalescePlanetesimals(double axis, double ecc, double mass, double criticalMass,
			double stellarLuminosity) {
		for (Planet curr = innermost; curr != null; curr = curr.next) {
			double dist = curr.axis - axis;

			double dist1, dist2;
			if (dist > 0.0) {
				dist1 = AccreteCalc.outerEffectLimit(axis, ecc, mass) - axis;
				dist2 = curr.axis - AccreteCalc.innerEffectLimit(curr.axis, curr.ecc, curr.mass);
			} else {
				dist1 = axis - AccreteCalc.innerEffectLimit(axis, ecc, mass);
				dist2 = AccreteCalc.outerEffectLimit(curr.axis, curr.ecc, curr.mass) - curr.axis;
			}
			if ((Math.abs(dist) <= dist1) || (Math.abs(dist) <= dist2)) {
				if (verbose) {
					System.err.println("Collision between two planetesimals!");
				}
				mergeTwoPlanets(curr, axis, ecc, mass, criticalMass, stellarLuminosity);
				return true;
			}
		}
		return false;
	}

	/**
	 * Method to form planets by accretion
	 * 
	 * @param rand - pseudo-random number generator
	 * @param star - sun of the solar system
	 * @return head of the planet for this system
	 */
	private Planet accretePlanets(Random rand, Star star) {

		// initialise dust
		dustRemains = true;
		dustHead = new DustBand(0.0, AccreteCalc.outerDustLimit(star.stellarMass));

		/* Get Closest and Further bounds on where Planets can form */
		double planetInnerBound = AccreteCalc.nearestPlanet(star.stellarMass);
		double planetOuterBound = AccreteCalc.farthestPlanet(star.stellarMass);

		while (dustRemains) {

			// give us a random proto planet within the inner and outer bounds
			double axis = RandomUtil.nextDouble(rand, planetInnerBound, planetOuterBound);
			double ecc = AccreteCalc.eccentricity(rand);
			double mass = SolarConst.PROTOPLANET_MASS;

			if (verbose) { // if flag is set, notify of what orbit we are checking
				System.err.print("Checking " + axis + " AU ...");
			}
			// Get the limits of our search to suck up dust
			innerSweep = AccreteCalc.innerSweepLimit(axis, ecc, mass);
			outerSweep = AccreteCalc.outerSweepLimit(axis, ecc, mass);

			// if we have dust inside the limits...
			if (isDustAvailable(innerSweep, outerSweep)) {

				if (verbose) {// if flag is set, notify of our attempt to inject a planet
					System.err.println("injecting protoplanet.");
				}

				// defaults for this axis
				dustDensity = AccreteCalc.dustDensity(star.stellarMass, axis);
				criticalMass = AccreteCalc.criticalMass(axis, ecc, star.stellarLuminosity);

				// covert dust into mass and update the dust bands
				mass = accreteDust(axis, ecc, mass, criticalMass);
				updateDustLanes(mass, planetInnerBound, planetOuterBound);

				if ((mass != 0.0) && (mass != SolarConst.PROTOPLANET_MASS)) {
					if (!coalescePlanetesimals(axis, ecc, mass, criticalMass, star.stellarLuminosity)) {
						insertPlanet(axis, ecc, mass);
						planetCount++;
						if (verbose) {
							System.err.println(" Injection Successful.");
						}
					}
				} else if (verbose) {
					System.err.println(" failed due to large neighbor.");
				}
			} else if (verbose) { // if flag is set, notify of failure due to lack of dust
				System.err.println(" failed due to no available dust.");
			}
		}
		return (innermost);
	}

	/**
	 * Method to form moons by accretion
	 * 
	 * TODO: Update this code to use a better moon generation process
	 * 
	 * @param planetary_mass
	 * @param plan_radius
	 * @return head of the moons for that planet
	 */
	private Moon accreteMoons(double planetary_mass, double plan_radius) {
		Moon head = null, last = null;

		/* max. moon distance in AU */
		double pmass = planetary_mass * SolarConst.SUN_MASS_IN_EARTH_MASSES;
		double maxdist = Math.sqrt(pmass) / 200;

		/* Find the minimum moon distance in AU */
		double prad = plan_radius / SolarConst.KM_PER_AU;
		double mindist = prad * RandomUtil.nextDouble(rand, 2.5, 10);

		int maxcount = (int) Math.sqrt(pmass * 10 + 5) + 1;
		double lastrad = mindist;
		int count = 0;

		pmass *= RandomUtil.nextDouble(rand, 0.01, 0.2);
		maxcount = RandomUtil.nextInt(rand, maxcount / 10, maxcount);
		maxdist *= RandomUtil.nextDouble(rand, 0.5, 1.5);

		if (verbose) {
			System.out.printf("\npmass = %g Me, prad = %g AU\n", pmass, prad);
			System.out.printf("mindist = %g AU, maxdist = %g AU\n", mindist, maxdist);
			System.out.printf("maxcount = %d\n", maxcount);
		}

		/* Begin to produce moons */
		while (pmass > 0.001 && count < maxcount && lastrad < maxdist) {
			double maxfac = Math.sqrt((lastrad - prad) / maxdist) / 8;

			double massmin = 1e17 / SolarConst.EARTH_MASS_IN_GRAMS;
			double massmax = RandomUtil.nextDouble(rand, pmass / 1e6, pmass * maxfac);
			double mmin = Math.pow(massmin, 1.0 / 4);
			double mmax = Math.pow(massmax, 1.0 / 4);
			double mass = Math.pow(RandomUtil.nextDouble(rand, mmin, mmax), 4);

			double dist = Math.sqrt(mass) * 50000 / SolarConst.KM_PER_AU;
			if (verbose) {
				System.out.printf("mmin = %g Me, mmax = %g Me, mass = %g Me\n", massmin, massmax, mass);
			}

			if (mass > massmin) {
				count++;
				Moon moon = new Moon();
				moon.mass = mass / SolarConst.SUN_MASS_IN_EARTH_MASSES;
				moon.axis = RandomUtil.nextDouble(rand, lastrad, lastrad * 1.3);
				lastrad = moon.axis + dist;
				moon.ecc = AccreteCalc.eccentricity(rand);
				pmass -= mass * 2;
				if (last != null) {
					last.next = moon;
				} else {
					head = moon;
				}
				last = moon;
			}
		}
		return head;
	}

	/**
	 * Method to calculate the density and radius
	 * 
	 * @param planet - the planet to calc the density and radius of
	 * @param radiusEcosphere - the system ecosphere radius
	 */
	private void calculateDensityAndRadius(Planet planet, double radiusEcosphere) {
		if (planet.gasGiant) {
			planet.density = AccreteCalc.empiricalDensity(planet.axis, planet.mass, planet.gasGiant, radiusEcosphere);
			planet.radius = AccreteCalc.volumeRadius(planet.mass, planet.density);
		} else {
			planet.radius = AccreteCalc.kothariRadius(planet.mass, planet.gasGiant, planet.orbitZone);
			planet.density = AccreteCalc.volumeDensity(planet.mass, planet.radius);
		}
	}

	/**
	 * Method to return the number of planets generated
	 * 
	 * @return the planetCount
	 */
	public int getPlanetCount() {
		return planetCount;
	}

	/**
	 * Method to form planets and moons by accretion
	 * 
	 * @param star - sun of the solar system
	 * @return head of the planet for this system
	 */

	public Planet accretePlanetMoons(Star star) {
		Planet innermost = accretePlanets(rand, star);
		for (Planet planet = innermost; planet != null; planet = planet.next) {
			planet.orbitZone = AccreteCalc.orbitalZone(planet.axis, star.stellarLuminosity);
			calculateDensityAndRadius(planet, star.radiusEcosphere);
			planet.orbitPeriod = AccreteCalc.period(planet.axis, planet.mass, star.stellarMass);
			// if (moons) {
			// planet.innermost = accreteMoons(planet.mass, planet.radius);
			// }
		}

		return innermost;
	}
}
