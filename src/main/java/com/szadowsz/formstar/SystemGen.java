package com.szadowsz.formstar;

import com.szadowsz.formstar.accrete.AccretionProcess;
import com.szadowsz.formstar.planetoid.Planet;
import com.szadowsz.formstar.star.Star;
import com.szadowsz.formstar.terraform.TerraformProcess;
import com.szadowsz.utils.LoggerCategory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Random;

public class SystemGen {
    public static final double EARTH_RADIUS_CM = 6.378e6;
    public static final double EARTH_RADIUS_KM = 6378.0;
    private static Logger _logger = LoggerFactory.getLogger(LoggerCategory.FORMSTAR);
    private SystemGen() {
    }

    public static SolarSystem generate(Random rand, boolean moons) {
        // Create the Star
        SolarSystem sys = new SolarSystem(Star.generate(rand));

        // Create the Planets and Moons, if applicable
        AccretionProcess accrete = new AccretionProcess(rand, moons);
        sys.innermost = accrete.accretePlanetAndMoons(sys.sun);
        TerraformProcess.terraformPlanetsAndMoons(rand, sys.sun, sys.innermost);
        sys.planetCount = accrete.getPlanetCount();

        int count = 0;
        for (Planet plan = sys.innermost; plan != null; plan = plan.next) {
            _logger.info("Planet " + (count++) + ": " + plan.toString());
        }


        return sys;
    }

    public static void main(String args[]) {
        System.out.println(EARTH_RADIUS_CM == EARTH_RADIUS_KM * 1000);
        SystemGen.generate(new Random(1), false);
    }
}
