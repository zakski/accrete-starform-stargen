package com.szadowsz.formstar.calc;

import java.util.Random;

/**
 * Class to store the heavy static calculations of the accretion process
 * 
 * @author zakski
 * 
 */
public final class AccreteCalc {

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
	public static double reducedMargin(double mass) {
		return Math.pow(reducedMass(mass), 1.0 / 4.0);
	}

	public static double calcMergedEccTerm(double axis, double eccn, double mass) {
		return mass * Math.sqrt(axis * (1.0 - eccn * eccn));
	}

	/**
	 * Method to calculate the farthest a planet can be from this star, based on the mass ratio.
	 *
	 * @param mass - star's mass in terms of solar mass
	 * @return the farthesr a planet can exist from a star
	 */
	public static double farthestPlanet(double mass) {
		return scaleCubeRootMass(50.0, mass);
	}

	/**
	 * Method to calculate the nearest a planet can be to this star, based on the mass ratio.
	 *
	 * @param mass - star's mass in terms of solar mass
	 * @return the nearest a planet can exist from a star
	 */
	public static double nearestPlanet(double mass) {
		return scaleCubeRootMass(0.3, mass);
	}

	/**
	 * Method to generate an eccentricity for a planet's orbit
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @return the generated eccentricity
	 */
	public static double eccentricity(Random rand) {
		return (1.0 - Math.pow(rand.nextDouble(), SolarConst.ECCENTRICITY_COEFF));
	}

	/**
	 * Method to calculate the stellar dust limit for this star's mass.
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return the stellar dust limit for the star
	 */
	public static double outerDustLimit(double stellarMass) {
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
	public static double innerEffectLimit(double axis, double ecc, double mass) {
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
	public static double outerEffectLimit(double axis, double ecc, double mass) {
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
	public static double criticalMass(double axis, double ecc, double luminosity) {
		return (SolarConst.B * Math.pow(OrbitalCalc.perihelionDistance(axis, ecc) * Math.sqrt(luminosity), -0.75));
	}

	/**
	 * Method to calculate the default dust density
	 * 
	 * @param axis - the current semi-major axis of the latest protoplanet
	 * @param stellarMass - the mass of the star
	 * @return default dust density
	 */
	public static double dustDensity(double stellarMass, double axis) {
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
	public static double massDensity(double dustDensity, double criticalMass, double mass) {
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
	public static double innerSweepLimit(double axis, double ecc, double mass) {
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
	public static double outerSweepLimit(double axis, double ecc, double mass) {
		return outerEffectLimit(axis, ecc, mass) / (1.0 - SolarConst.CLOUD_ECCENTRICITY);
	}
}
