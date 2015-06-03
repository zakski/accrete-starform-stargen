package com.szadowsz.formstar.calc;

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

	/**
	 * Method to calculate the orbital period in terms of Earth days.
	 *
	 * @param separation - the distance between the two masses
	 * @param small      - the mass rotating around the large mass
	 * @param large      - the anchor for the small mass to rotate around
	 * @return the orbital period
	 */
	public static double period(double separation, double small, double large) {
		double period_in_years;

		period_in_years = Math.sqrt(Math.pow(separation, 3) / (small + large));
		return (period_in_years * SolarConst.DAYS_IN_A_YEAR);
	}


	/**
	 * Method to calculate the orbital zone of the planet
	 *
	 * @param axis              - the orbital radius of a planet in AU
	 * @param stellarLuminosity - luminosity of the star
	 * @return the orbital 'zone' of the planet
	 */
	public static int orbitalZone(double axis, double stellarLuminosity) {
		if (axis < 4.0 * Math.sqrt(stellarLuminosity)) {
			return 1;
		} else if ((axis >= 4.0 * Math.sqrt(stellarLuminosity)) && (axis < 15.0 * Math.sqrt(stellarLuminosity))) {
			return 2;
		} else {
			return 3;
		}
	}
}
