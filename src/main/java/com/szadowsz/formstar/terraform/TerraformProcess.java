package com.szadowsz.formstar.terraform;

import com.szadowsz.formstar.calc.OrbitalCalc;
import com.szadowsz.formstar.calc.PlanetoidCalc;
import com.szadowsz.formstar.planetoid.Planet;
import com.szadowsz.formstar.star.Star;

import java.util.Random;

/**
 * @author Zakski : 30/05/2015.
 */
public class TerraformProcess {

    private TerraformProcess() {
    }

    /**
     * Method to calculate the density and radius
     *
     * @param planet          - the planet to calc the density and radius of
     * @param radiusEcosphere - the system ecosphere radius
     */
    private static void calculateDensityAndRadius(Planet planet, double radiusEcosphere) {
        if (planet.gasGiant) {
            planet.density = PlanetoidCalc.empiricalDensity(planet.axis, planet.mass, planet.gasGiant, radiusEcosphere);
            planet.radius = PlanetoidCalc.volumeRadius(planet.mass, planet.density);
        } else {
            planet.radius = PlanetoidCalc.kothariRadius(planet.mass, planet.gasGiant, planet.orbitZone);
            planet.density = PlanetoidCalc.volumeDensity(planet.mass, planet.radius);
        }
    }

    public static void terraformPlanetsAndMoons(Random rand, Star star, Planet innermost) {
        for (Planet planet = innermost; planet != null; planet = planet.next) {
            planet.orbitZone = OrbitalCalc.orbitalZone(planet.axis, star.stellarLuminosity);
            planet.orbitPeriod = OrbitalCalc.period(planet.axis, planet.mass, star.stellarMass);

            calculateDensityAndRadius(planet, star.radiusEcosphere);

            double ang = PlanetoidCalc.angular_velocity(planet.density, planet.radius, planet.mass, planet.axis, star.stellarMass, star.age, planet.gasGiant);
            double year_in_hours = planet.orbitPeriod * 24.0;
            planet.dayLength = PlanetoidCalc.day_length(planet.mass, planet.ecc, planet.radius, ang, year_in_hours);
            planet.resonant = ((planet.dayLength >= year_in_hours) || ang <= 0);

            planet.axialTilt = PlanetoidCalc.inclination(rand, planet.axis);
        }
    }
}