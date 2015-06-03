package com.szadowsz.formstar.accrete;

import com.szadowsz.formstar.calc.AccreteCalc;
import com.szadowsz.formstar.calc.SolarConst;
import com.szadowsz.formstar.planetoid.Moon;
import com.szadowsz.formstar.planetoid.Planet;
import com.szadowsz.formstar.star.Star;
import com.szadowsz.utils.LoggerCategory;
import com.szadowsz.utils.RandomUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Random;

public class AccretionProcess {
    private Logger _logger = LoggerFactory.getLogger(LoggerCategory.FORMSTAR);

    /* Now for some variables global to the accretion process: */
    private Random _rand; // pseudo-random number generator

    private double _innerSweep, _outerSweep; // current dust sweep bounds

    private DustBand _dustHead; // head of the dustband linked list
    private double _dustDensity; // current default dust density

    private Planet _innermost; // closest to the sun, Planets are basically a linked list also
    private double _criticalMass; // limit before planet becomes a gass giant
    private int _planetCount; // planet count

    private boolean _hasDust; // flag for the existence of dust
    private boolean _genMoons; // whether or not we should generate moons

    /**
     * Default Constructor Just sets the verbose flag
     *
     * @param random   - pseudo-random number generator
     * @param genmoons - w
     */
    public AccretionProcess(Random random, boolean genmoons) {
        _rand = random;
        _genMoons = genmoons;
    }

    /**
     * Steps through list of dust bands checking to see if any of those that bands that overlap the given
     * range have dust present. This was originally done as a quick check with the swept limits using the full
     * mass for newly injected nuclei.
     *
     * @param insideRange  - the nearest to the star that the protoplanet can pull dust from
     * @param outsideRange - the farthest from the star that the protoplanet can pull dust from
     * @return whether or not there is still dust between inside_range and outside_range in this current
     * accretion process.
     */
    private boolean isDustAvailable(double insideRange, double outsideRange) {
        DustBand current = _dustHead;
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
     * @param axis         - the current semi-major axis of the latest protoplanet
     * @param ecc          - the current eccentricity of the latest protoplanet
     * @param mass         - the current mass of the latest protoplanet
     * @param criticalMass - gas giant mass limit
     * @return the new calculated mass
     */
    private double accreteDust(double axis, double ecc, double mass, double criticalMass) {
        /* fixed point algorithm: accumulate more mass until the difference is less than .01% of the old mass */
        double currMass = mass, lastMass;
        do {
            lastMass = currMass;
            currMass = collectDust(axis, ecc, currMass, criticalMass, _dustHead);
        } while (!(((currMass - lastMass) < (0.0001 * lastMass))));

        // return the new mass added to the seed mass
        return mass + currMass;
    }

    /**
     * Method to turn all available DustBands into mass for the protoplanet
     *
     * @param axis         - the current semi-major axis of the latest protoplanet
     * @param ecc          - the current eccentricity of the latest protoplanet
     * @param mass         - the current mass of the latest protoplanet
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
        _innerSweep = AccreteCalc.innerSweepLimit(axis, ecc, reducedMass);
        _outerSweep = AccreteCalc.outerSweepLimit(axis, ecc, reducedMass);

        // clamp the inner radius to be at least zero
        if (_innerSweep < 0.0) {
            _innerSweep = 0.0;
        }

        // if the outer edge is less than the accretion inner limit
        if (band.outerEdge <= _innerSweep) {
            return collectDust(axis, ecc, mass, criticalMass, band.next);
        }// or if the inner edge is greater than the outer limit, don't collect any more dust.
        else if (band.innerEdge >= _outerSweep) {
            return 0.0;
        }

        // if we have dust, use the dust density, otherwise zero
        double dust_density = (band.hasDust) ? _dustDensity : 0.0;

        // if the mass is below the critical mass, or there's no gas in this
        // dust band, the density is the overall accretion density;
        // otherwise, use the mass density formula
        double density = (!band.hasGas || (mass < criticalMass)) ? dust_density : AccreteCalc.massDensity(dust_density,
                criticalMass, mass);

        // account for any gaps between the dust edges and the start of
        // the accretion radius
        double bandwidth = (_outerSweep - _innerSweep);

        double outside = _outerSweep - band.outerEdge;
        if (outside < 0.0)
            outside = 0.0;

        double inside = band.innerEdge - _innerSweep;
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
     * @param band   - the band to split
     * @param hasGas - whether there is gas
     * @return next band
     */
    private DustBand splitForSubPlanet(DustBand band, boolean hasGas) {
        // make a new dust lane with min and max for the middle chunk
        DustBand middle = new DustBand(_innerSweep, _outerSweep, false, band.hasGas && hasGas);

        // make another new dust lane that proceeds from max to the outer edge of band
        DustBand right = new DustBand(_outerSweep, band.outerEdge, band.hasDust, band.hasGas);
        right.next = band.next;
        middle.next = right;

        // condense node1's outer edge to the minimum
        band.next = middle;
        band.outerEdge = _innerSweep;

        return right.next;
    }

    /**
     * Method to split a band into 2 based on overlapping a proto-planet's outer edge
     *
     * @param band   - the band to split
     * @param hasGas - whether there is gas
     * @return next band
     */
    private DustBand splitOnPlanetMaxEdge(DustBand band, boolean hasGas) {
        DustBand right = new DustBand(_outerSweep, band.outerEdge, band.hasDust, band.hasGas);
        right.next = band.next;
        band.next = right;
        band.outerEdge = _outerSweep;
        band.hasDust = false;
        band.hasGas = hasGas;
        return right.next;
    }

    /**
     * Method to split a band into 2 based on overlapping a proto-planet's inner edge
     *
     * @param band   - the band to split
     * @param hasGas - whether there is gas
     * @return next band
     */
    private DustBand splitOnPlanetMinEdge(DustBand band, boolean hasGas) {
        DustBand right = new DustBand(_innerSweep, band.outerEdge, false, band.hasGas && hasGas);
        right.next = band.next;
        band.next = right;
        band.outerEdge = _innerSweep;
        return right.next;
    }

    /**
     * Split a dust lane into several dust lanes, and mark the dust as used. Returns the next dust lane in the
     * list.
     */
    private DustBand splitBands(DustBand band, boolean hasGas) {
        // Case 1: this node subsumes min and max
        if (band.innerEdge < _innerSweep && band.outerEdge > _outerSweep) {
            return splitForSubPlanet(band, hasGas);

            // Case 2: the node spans across the maximum
        } else if (band.innerEdge < _outerSweep && band.outerEdge > _outerSweep) {
            return splitOnPlanetMaxEdge(band, hasGas);

            // Case 3: the node spans across the minimum
        } else if (band.innerEdge < _innerSweep && band.outerEdge > _innerSweep) {
            return splitOnPlanetMinEdge(band, hasGas);

            // Case 4: the node is within or equal to the range
        } else if (band.innerEdge >= _innerSweep && band.outerEdge <= _outerSweep) {
            // Use up the dust
            band.hasDust = false;

            // if gas was present, it may not be now.
            if (band.hasGas) {
                band.hasGas = hasGas;
            }

            // proceed
            return band.next;

            // Case 5: No overlap whatsoever
            // in this case, just move on to the next dust band
        } else if (band.outerEdge < _innerSweep || band.innerEdge > _outerSweep) {
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

        for (DustBand lane = _dustHead; lane != null; lane = lane.next) {
            // if this node has dust and the node is within the body's inner and outer
            // boundaries, then there is dust left in this simulation.
            if (lane.hasDust && lane.outerEdge >= innerBound && lane.innerEdge <= outerBound) {
                _hasDust = true;
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
     * @param mass              - mass of the proto-planet
     * @param planetInnerBound  - closest to the sun that we can form a star
     * @param planetOuterBound- furthest from the sun that we can form a star
     */
    private void updateDustLanes(double mass, double planetInnerBound, double planetOuterBound) {

        // begin asserting that there's no dust left. coalesce_dust_lanes will set
        // this value to true if it finds any dust during its coalescing maneuver
        _hasDust = false;

        // this tracks whether or not this planetoid is growing up to be a gas giant
        // or if it is sufficiently massive that it's going to be a planetoid
        boolean gas = (mass <= _criticalMass);

        // this loop examines every dust band. it splits dust band such that our min
        // and max values lie at the boundaries of the band. it also consumes the dust
        // and gas in each band within the limits as it goes.
        for (DustBand lane = _dustHead; lane != null; lane = splitBands(lane, gas)) ;

        // this loop detects whether or not there is still dust present in the
        // simulation within the overall bounds and simultaneously coalesces neighbor
        // dust lanes that have or do not have dust and/or gas
        mergeDustBands(planetInnerBound, planetOuterBound);
    }

    /**
     * Method to merge a newly coalesced planet with an existing one
     *
     * @param planet            - the existing planet
     * @param axis              - new planet's axis
     * @param ecc               - new planet's eccentricity
     * @param mass              - new planet's mass
     * @param criticalMass      - new planet's critical mass
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
     * @param ecc  - new planet's eccentricity
     * @param mass - new planet's mass
     */
    private void insertPlanet(double axis, double ecc, double mass) {
        Planet planet = new Planet();
        planet.axis = axis;
        planet.ecc = ecc;
        planet.mass = mass;
        if (planet.mass >= _criticalMass) {
            planet.gasGiant = true;
        }

        if (_innermost == null) {
            _innermost = planet;
        } else if (planet.axis < _innermost.axis) {
            planet.next = _innermost;
            _innermost = planet;
        } else {
            Planet prev = _innermost;
            Planet curr = _innermost.next;
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
     * @param axis              - new planet's axis
     * @param ecc               - new planet's eccentricity
     * @param mass              - new planet's mass
     * @param criticalMass      - new planet's critical mass
     * @param stellarLuminosity - star's luminosity
     * @return true if planets collided, false if not
     */
    private boolean coalescePlanetesimals(double axis, double ecc, double mass, double criticalMass,
                                          double stellarLuminosity) {
        for (Planet curr = _innermost; curr != null; curr = curr.next) {
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
                _logger.info("Collision between two planetesimals!");
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
        _hasDust = true;
        _dustHead = new DustBand(0.0, AccreteCalc.outerDustLimit(star.stellarMass));

		/* Get Closest and Further bounds on where Planets can form */
        double planetInnerBound = AccreteCalc.nearestPlanet(star.stellarMass);
        double planetOuterBound = AccreteCalc.farthestPlanet(star.stellarMass);

        while (_hasDust) {

            // give us a random proto planet within the inner and outer bounds
            double axis = RandomUtil.nextDouble(rand, planetInnerBound, planetOuterBound);
            double ecc = AccreteCalc.eccentricity(rand);
            double mass = SolarConst.PROTOPLANET_MASS;

            // notification of what orbit we are checking
            _logger.info("Checking " + axis + " AU for suitability.");

            // Get the limits of our search to suck up dust
            _innerSweep = AccreteCalc.innerSweepLimit(axis, ecc, mass);
            _outerSweep = AccreteCalc.outerSweepLimit(axis, ecc, mass);

            // if we have dust inside the limits we have the ability and should try to inject
            if (isDustAvailable(_innerSweep, _outerSweep)) {

                // notify of our attempt to inject a planet
                _logger.info("Injection of protoplanet at " + axis + " AU.");

                // get defaults for this axis
                _dustDensity = AccreteCalc.dustDensity(star.stellarMass, axis);
                _criticalMass = AccreteCalc.criticalMass(axis, ecc, star.stellarLuminosity);

                // covert dust into mass and update the dust bands
                mass = accreteDust(axis, ecc, mass, _criticalMass);
                updateDustLanes(mass, planetInnerBound, planetOuterBound);

                if ((mass != 0.0) && (mass != SolarConst.PROTOPLANET_MASS)) {
                    if (!coalescePlanetesimals(axis, ecc, mass, _criticalMass, star.stellarLuminosity)) {
                        insertPlanet(axis, ecc, mass);
                        _planetCount++;
                        _logger.info("Injecting protoplanet at " + axis + " AU Successful.");
                    }
                } else {
                    _logger.info("Injection of protoplanet at " + axis + " AU failed due to large neighbor.");
                }
            } else { // notify of failure due to lack of dust
                _logger.info("Injection of protoplanet at " + axis + " AU failed due to no available dust.");
            }
        }
        return (_innermost);
    }

    /**
     * Method to form moons by accretion
     * <p>
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
        double mindist = prad * RandomUtil.nextDouble(_rand, 2.5, 10);

        int maxcount = (int) Math.sqrt(pmass * 10 + 5) + 1;
        double lastrad = mindist;
        int count = 0;

        pmass *= RandomUtil.nextDouble(_rand, 0.01, 0.2);
        maxcount = RandomUtil.nextInt(_rand, maxcount / 10, maxcount);
        maxdist *= RandomUtil.nextDouble(_rand, 0.5, 1.5);

        _logger.info("\npmass = %g Me, prad = %g AU\n", pmass, prad);
        _logger.info("mindist = %g AU, maxdist = %g AU\n", mindist, maxdist);
        _logger.info("maxcount = %d\n", maxcount);


		/* Begin to produce moons */
        while (pmass > 0.001 && count < maxcount && lastrad < maxdist) {
            double maxfac = Math.sqrt((lastrad - prad) / maxdist) / 8;

            double massmin = 1e17 / SolarConst.EARTH_MASS_IN_GRAMS;
            double massmax = RandomUtil.nextDouble(_rand, pmass / 1e6, pmass * maxfac);
            double mmin = Math.pow(massmin, 1.0 / 4);
            double mmax = Math.pow(massmax, 1.0 / 4);
            double mass = Math.pow(RandomUtil.nextDouble(_rand, mmin, mmax), 4);

            double dist = Math.sqrt(mass) * 50000 / SolarConst.KM_PER_AU;
            _logger.info("mmin = %g Me, mmax = %g Me, mass = %g Me\n", massmin, massmax, mass);

            if (mass > massmin) {
                count++;
                Moon moon = new Moon();
                moon.mass = mass / SolarConst.SUN_MASS_IN_EARTH_MASSES;
                moon.axis = RandomUtil.nextDouble(_rand, lastrad, lastrad * 1.3);
                lastrad = moon.axis + dist;
                moon.ecc = AccreteCalc.eccentricity(_rand);
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
     * Method to return the number of planets generated
     *
     * @return the _planetCount
     */
    public int getPlanetCount() {
        return _planetCount;
    }

    /**
     * Method to form planets and moons by accretion
     * <p>
     * NOTE: moon code never really existed in any of the versions I have thus far discovered so
     * we currently do not have a good solution for this and I would not recommend setting it to true.
     *
     * @param star - sun of the solar system
     * @return head of the planet for this system
     */
    public Planet accretePlanetAndMoons(Star star) {
        Planet innermost = accretePlanets(_rand, star);
        if (_genMoons) {
            for (Planet planet = innermost; planet != null; planet = planet.next) {
                planet.innermost = accreteMoons(planet.mass, planet.radius);
            }
        }
        return innermost;
    }
}
