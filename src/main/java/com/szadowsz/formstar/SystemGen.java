package com.szadowsz.formstar;

import com.szadowsz.formstar.accrete.AccretionProcess;
import com.szadowsz.formstar.planetoid.Planet;
import com.szadowsz.formstar.star.Star;
import com.szadowsz.utils.LoggerCategory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Random;

public class SystemGen {
    private static Logger _logger = LoggerFactory.getLogger(LoggerCategory.FORMSTAR);

    private SystemGen() {
    }


    public static SolarSystem generate(Random rand, boolean moons) {

        // Create the Star
        SolarSystem sys = new SolarSystem(Star.generate(rand));


        // Create the Planets and Moons, if applicable
        AccretionProcess accrete = new AccretionProcess(rand, moons);
        sys.innermost = accrete.accretePlanetMoons(sys.sun);
        sys.planetCount = accrete.getPlanetCount();

        int count = 0;
        for (Planet plan = sys.innermost; plan != null; plan = plan.next) {
            _logger.info("Planet " + (count++) + ": " + plan.toString());
        }


        return sys;
    }

    public static void main(String args[]) {
        SystemGen.generate(new Random(1), false);
    }
}
