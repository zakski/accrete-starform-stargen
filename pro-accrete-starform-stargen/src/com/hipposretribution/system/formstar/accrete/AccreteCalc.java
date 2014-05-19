package com.hipposretribution.system.formstar.accrete;

import java.util.Random;

import com.hipposretribution.system.formstar.SolarConst;
import com.hipposretribution.system.formstar.planetoid.OrbitalCalc;

/**
 * Class to store the heavy static calculations of the accretion process
 * 
 * @author zakski
 * 
 */
final class AccreteCalc {

	/**
	 * Constructor Not Needed
	 */
	private AccreteCalc() {
	}

	/**
	 * Internal method to scale the cube root of the star's mass
	 * 
	 * @param scale the scalar to multiply by
	 * @param mass the mass to cube root
	 * @return scaled cube root of the mass
	 */
	private static double scaleCubeRootMass(double scale, double mass) {
		return scale * Math.pow(mass, 1.0 / 3.0);
	}

	/**
	 * Method to get the reduced mass
	 * 
	 * @param mass - the current mass of the latest protoplanet
	 * @return the reduced mass
	 */
	private static double reducedMass(double mass) {
		return mass / (1.0 + mass);
	}

	/**
	 * 
	 * @param mass - the current mass of the latest protoplanet
	 * @return the reduced mass to the 1/4th power
	 */
	static double reducedMargin(double mass) {
		return Math.pow(reducedMass(mass), 1.0 / 4.0);
	}

	static double calcMergedEccTerm(double axis, double eccn, double mass) {
		return mass * Math.sqrt(axis * (1.0 - eccn * eccn));
	}

	/**
	 * Method to calculate the farthest a planet can be from this star, based on the mass ratio.
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return the farthesr a planet can exist from a star
	 */
	static double farthestPlanet(double mass) {
		return scaleCubeRootMass(50.0, mass);
	}

	/**
	 * Method to calculate the nearest a planet can be to this star, based on the mass ratio.
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return the nearest a planet can exist from a star
	 */
	static double nearestPlanet(double mass) {
		return scaleCubeRootMass(0.3, mass);
	}

	/**
	 * Method to generate an eccentricity for a planet's orbit
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @return the generated eccentricity
	 */
	static double eccentricity(Random rand) {
		return (1.0 - Math.pow(rand.nextDouble(), SolarConst.ECCENTRICITY_COEFF));
	}

	/**
	 * Method to calculate the stellar dust limit for this star's mass.
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return the stellar dust limit for the star
	 */
	static double outerDustLimit(double stellarMass) {
		return scaleCubeRootMass(200.0, stellarMass);
	}

	/**
	 * Utility Method
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @return The inner bound of the protoplanet's ability to affect things
	 */
	static double innerEffectLimit(double axis, double ecc, double mass) {
		return OrbitalCalc.perihelionDistance(axis, ecc) * (1.0 - mass);
	}

	/**
	 * Utility Method
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @return The outer bound of the protoplanet's ability to affect things
	 */
	static double outerEffectLimit(double axis, double ecc, double mass) {
		return OrbitalCalc.aphelionDistance(axis, ecc) * (1.0 + mass);
	}

	/**
	 * Method to calculate the critical mass limit, where the planet begins to accrete gas as well as dust.
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param luminosity - star's luminosity in terms of solar luminosity
	 * @return The critical mass limit of the current protoplanet
	 */
	static double criticalMass(double axis, double ecc, double luminosity) {
		return (SolarConst.B * Math.pow(OrbitalCalc.perihelionDistance(axis, ecc) * Math.sqrt(luminosity), -0.75));
	}

	/**
	 * Method to calculate the default dust density
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param stellarMass - the mass of the star
	 * @return default dust density
	 */
	static double dustDensity(double stellarMass, double axis) {
		return SolarConst.DUST_DENSITY_COEFF * Math.sqrt(stellarMass)
				* Math.exp(-SolarConst.ALPHA * Math.pow(axis, 1.0 / SolarConst.N));
	}

	/**
	 * Method to calculate Mass Density
	 * 
	 * @param dustDensity - the current dust density value
	 * @param criticalMass - the current critical mass limit for becoming a dust giant
	 * @param mass - the current mass of the latest protoplanet
	 * @return the current Mass density
	 */
	static double massDensity(double dustDensity, double criticalMass, double mass) {
		return SolarConst.K * dustDensity / (1.0 + Math.sqrt(criticalMass / mass) * (SolarConst.K - 1.0));
	}

	/**
	 * Method to calculate the inner distance of the protoplanet's ability to accrete
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @return The inner bound of the protoplanet's ability to accrete
	 */
	static double innerSweepLimit(double axis, double ecc, double mass) {
		return innerEffectLimit(axis, ecc, mass) / (1.0 + SolarConst.CLOUD_ECCENTRICITY);
	}

	/**
	 * Method to calculate the outer distance of the protoplanet's ability to accrete
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param ecc - the current eccentricity of the latest protoplanet
	 * @param mass - the current mass of the latest protoplanet
	 * @return The outer bound of the protoplanet's ability to accrete
	 */
	static double outerSweepLimit(double axis, double ecc, double mass) {
		return outerEffectLimit(axis, ecc, mass) / (1.0 - SolarConst.CLOUD_ECCENTRICITY);
	}

	/**
	 * Method to calculate the orbital zone of the planet
	 * 
	 * @param axis - the orbital radius of a planet in AU
	 * @param stellarLuminosity - luminosity of the star
	 * @return the orbital 'zone' of the planet
	 */
	static int orbitalZone(double axis, double stellarLuminosity) {
		if (axis < 4.0 * Math.sqrt(stellarLuminosity)) {
			return 1;
		} else if ((axis >= 4.0 * Math.sqrt(stellarLuminosity)) && (axis < 15.0 * Math.sqrt(stellarLuminosity))) {
			return 2;
		} else {
			return 3;
		}
	}

	/**
	 * Method to calculate a planet's radius using volume in units of km
	 * 
	 * @param mass - the mass of the planet
	 * @param density - the density of the planet
	 * @return the equatorial radius of the planet
	 */
	static double volumeRadius(double mass, double density) {
		double volume;

		mass = mass * SolarConst.SOLAR_MASS_IN_GRAMS;
		volume = mass / density;
		return (Math.pow((3.0 * volume) / (4.0 * Math.PI), (1.0 / 3.0)) / SolarConst.CM_PER_KM);
	}

	/**
	 * Method to calculate a planet's density using volume in units of grams/cc.
	 * 
	 * @param mass - the mass of the planet
	 * @param radius - the equatorial radius of the planet
	 * @return the density of the planet
	 */
	static double volumeDensity(double mass, double equat_radius) {
		double volume;

		mass = mass * SolarConst.SOLAR_MASS_IN_GRAMS;
		equat_radius = equat_radius * SolarConst.CM_PER_KM;
		volume = (4.0 * Math.PI * Math.pow(equat_radius, 3)) / 3.0;
		return (mass / volume);
	}

	/**
	 * This formula is listed as eq.9 in Fogg's article, although some typos crop up in that eq. See
	 * "The Internal Constitution of Planets", by Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical
	 * Society, vol 96 pp.833-843, 1936 for the derivation. Specifically, this is Kothari's eq.23, which
	 * appears on page 840.
	 * 
	 * @param mass - the mass of the planet
	 * @param giant - is the planet a gas giant
	 * @param zone - orbital zone of the planet
	 * @return the equatorial radius of the planet
	 */
	static double kothariRadius(double mass, boolean giant, int zone) {
		double temp, temp2, atomic_weight, atomic_num;

		if (zone == 1) {
			if (giant) {
				atomic_weight = 9.5;
				atomic_num = 4.5;
			} else {
				atomic_weight = 15.0;
				atomic_num = 8.0;
			}
		} else if (zone == 2) {
			if (giant) {
				atomic_weight = 2.47;
				atomic_num = 2.0;
			} else {
				atomic_weight = 10.0;
				atomic_num = 5.0;
			}
		} else {
			if (giant) {
				atomic_weight = 7.0;
				atomic_num = 4.0;
			} else {
				atomic_weight = 10.0;
				atomic_num = 5.0;
			}
		}
		temp = atomic_weight * atomic_num;
		temp = (2.0 * SolarConst.BETA_20 * Math.pow(SolarConst.SOLAR_MASS_IN_GRAMS, (1.0 / 3.0)))
				/ (SolarConst.A1_20 * Math.pow(temp, (1.0 / 3.0)));
		temp2 = SolarConst.A2_20 * Math.pow(atomic_weight, (4.0 / 3.0))
				* Math.pow(SolarConst.SOLAR_MASS_IN_GRAMS, (2.0 / 3.0));
		temp2 = temp2 * Math.pow(mass, (2.0 / 3.0));
		temp2 = temp2 / (SolarConst.A1_20 * Math.pow(atomic_num, 2));
		temp2 = 1.0 + temp2;
		temp = temp / temp2;
		temp = (temp * Math.pow(mass, (1.0 / 3.0))) / SolarConst.CM_PER_KM;
		return (temp);
	}

	/**
	 * Method to calculate the Empirical Density in units of grams/cc
	 * 
	 * @param axis - semi-major axis of the planet
	 * @param mass - the mass of the planet
	 * @param isGiant - is the planet a gas giant
	 * @param ecosphere - system's ecosphere radius
	 * @return the density
	 */
	static double empiricalDensity(double axis, double mass, boolean isGiant, double ecosphere) {
		double density;

		density = Math.pow(mass * SolarConst.SUN_MASS_IN_EARTH_MASSES, (1.0 / 8.0));
		density = density * Math.pow(ecosphere / axis, 1 / 4);
		if (isGiant)
			return (density * 1.2);
		else
			return (density * 5.5);
	}

}
