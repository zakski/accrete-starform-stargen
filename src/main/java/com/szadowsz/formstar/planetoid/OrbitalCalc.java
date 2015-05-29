package com.szadowsz.formstar.planetoid;

/**
 * Class to provide planetoid orbital calculations
 * 
 * @author zakski
 *
 */
public final class OrbitalCalc {

	/**
	 * Constructor Not Needed
	 */
	private OrbitalCalc() {
	}

	/**
	 * Method to get the Aphelion distance between an orbiting planetary body and its star. The Aphelion
	 * distance is the furthest away that the planetary body will be from its Star.
	 * 
	 * @param radius - the radius of the planetary body's orbit AKA the semi-major axis
	 * @param eccentricity - the eccentricity of the planetary body's orbit
	 * @return the greatest distance between the body and its host star
	 */
	public static double aphelionDistance(double radius, double eccentricity) {
		return radius * (1.0 + eccentricity);
	}

	/**
	 * Method to get the Perihelion distance between an orbiting planetary body and its star. The Perihelion
	 * distance is the closest that the planetary body will be from its Star.
	 * 
	 * @param radius - the radius of the planetary body's orbit AKA the semi-major axis
	 * @param eccentricity - the eccentricity of the planetary body's orbit
	 * @return the closest distance between the body and its host star
	 */
	public static double perihelionDistance(double radius, double eccentricity) {
		return radius * (1.0 - eccentricity);
	}

}
