package com.hipposretribution.system.formstar.star;

import java.util.Random;

import com.hipposretribution.system.formstar.SolarConst;
import com.hipposretribution.utils.random.RandomUtil;

/**
 * Class to do the heavy calculations of generating a star
 * 
 * @author zakski
 * 
 */
final class StarCalc {

	/**
	 * Constructor Not Needed
	 */
	private StarCalc() {
	}

	/**
	 * Method to calculate Star's Surface Temperature in kelvin. Equation is derived from the
	 * Stefan–Boltzmann equation.
	 * 
	 * @param stellarLuminosity - star's luminosity in terms of solar luminosity
	 * @param stellarRadius - star's radius in terms of solar radius
	 * @return star's surface temperature in terms of kelvin
	 */
	private static double temperature(double stellarLuminosity, double stellarRadius) {
		return Math.floor(SolarConst.SUN_SURFACE_TEMP * Math.sqrt(Math.sqrt(stellarLuminosity) / stellarRadius));
	}

	/**
	 * Method to approximate the star's radius in terms of solar radius
	 * 
	 * 
	 * Solar radius is a unit of distance used to express the size of stars in astronomy equal to the current
	 * radius of the Sun.
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return star's radius in terms of solar radius
	 */
	private static double radius(Random rand, double stellarMass) {
		return RandomUtil.variation(rand, Math.pow(stellarMass, 1.0 / 3.0), 0.05);
	}

	/**
	 * Method to calculate the aproximate greenhouse limit of the star
	 * 
	 * TODO: WORK OUT IF THIS FORMULA CANNOT BE IMPROVED, SMELLS LIKE MAGIC NUMBERS!!!
	 * 
	 * @param stellarLuminosity - star's luminosity in terms of solar luminosity
	 * @return inner habitable limit in what I want to say is AU
	 */
	private static double innerHabitableLimit(double radiusEcosphere) {
		return radiusEcosphere * SolarConst.GREENHOUSE_EFFECT_CONST;
	}

	/**
	 * Method to calculate the aproximate ecosphere limit of the star
	 * 
	 * TODO: WORK OUT IF THIS FORMULA CANNOT BE IMPROVED, SMELLS LIKE MAGIC NUMBERS!!!
	 * 
	 * @param stellarLuminosity - star's luminosity in terms of solar luminosity
	 * @return outer habitable limit in what I want to say is AU
	 */
	private static double outerHabitableLimit(double stellarLuminosity) {
		return Math.sqrt(stellarLuminosity);
	}

	/**
	 * Method to generate the star's approximate age based on the main sequence lifespan
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param mainSeqLife - the main sequence lifespan for upper limit of the generated star' age.
	 * @return the star's generated age
	 */
	private static double age(Random rand, double mainSeqLife) {
		if (mainSeqLife > SolarConst.AGE_OUTER_LIMIT)
			return RandomUtil.nextDouble(rand, SolarConst.AGE_INNER_LIMIT, SolarConst.AGE_OUTER_LIMIT);
		else if (mainSeqLife > SolarConst.AGE_INNER_LIMIT)
			return RandomUtil.nextDouble(rand, SolarConst.AGE_INNER_LIMIT, mainSeqLife);
		else
			return RandomUtil.nextDouble(rand, mainSeqLife / 10, mainSeqLife);
	}

	/**
	 * Method to calculate the star's approximate lifespan on the main sequence
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @param stellarLuminosity - star's luminosity in terms of solar luminosity
	 * @return star's Main Sequence Lifespan in terms of years
	 */
	private static double mainSequenceLife(double stellarMass, double stellarLuminosity) {
		return SolarConst.SUN_MS_LIFESPAN * (stellarMass / stellarLuminosity);
	}

	/**
	 * Method to calculate the luminosity of a star (in solar luminosity) for the star of a given mass (in
	 * solar masses).
	 * 
	 * TODO: THIS FORMULA IS ONLY ACCURATE FOR STARS WITH A MASS CLOSE TO THAT OF THE SUN'S.IT IS A HOLDOVER
	 * FROM ACCRETE-STARFOM AND NEEDS REPLACING WITH SOMETHING BETTER.!!!
	 * 
	 * The solar luminosity, L☉, is a unit of radiant flux (power emitted in the form of photons)
	 * conventionally used by astronomers to measure the luminosity of stars. One solar luminosity is equal to
	 * the current accepted luminosity of the Sun, which is 3.839×1026 W, or 3.839×1033 erg/s. The value is
	 * slightly higher, 3.939×1026 W (equivalent to 4.382×109 kg/s or 1.9×10−16 M☉/d) if the solar
	 * neutrino radiation is included as well as electromagnetic radiation. The Sun is a weakly variable star
	 * and its luminosity therefore fluctuates.[4] The major fluctuation is the eleven-year solar cycle
	 * (sunspot cycle), which causes a periodic variation of about ±0.1%. Any other variation over the last
	 * 200–300 years is thought to be much smaller than this.
	 * 
	 * @param stellarMass - star's mass in terms of solar mass
	 * @return star's luminosity in terms of solar luminosity
	 */
	private static double luminosity(double stellarMass) {
		double n;

		if (stellarMass < 1.0)
			n = 1.75 * (stellarMass - 0.1) + 3.325;
		else
			n = 0.5 * (2.0 - stellarMass) + 4.4;
		return (Math.pow(stellarMass, n));
	}

	/**
	 * Method to procedurally generate the mass of a star in solar mass.
	 * 
	 * The solar mass (M☉) is a standard unit of mass in astronomy that is used to indicate the masses of
	 * other stars, as well as clusters, nebulae and galaxies. It is equal to the mass of the Sun, about two
	 * nonillion kilograms:
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @return generated mass in terms of solar mass
	 */
	private static double mass(Random rand) {
		return RandomUtil.nextDouble(rand, 0.6, 1.3);
	}

	/**
	 * Method to procedurally generate information for a star
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @return - the generated star
	 */
	static Star formStar(Random rand) {
		Star star = new Star();
		star.stellarMass = mass(rand);
		star.stellarLuminosity = luminosity(star.stellarMass);

		star.mainSeqLife = mainSequenceLife(star.stellarMass, star.stellarLuminosity);
		star.age = StarCalc.age(rand, star.mainSeqLife);

		star.radiusEcosphere = outerHabitableLimit(star.stellarLuminosity);
		star.radiusGreenhouse = innerHabitableLimit(star.radiusEcosphere);

		star.stellarRadius = StarCalc.radius(rand, star.stellarMass);

		star.stellarTemp = StarCalc.temperature(star.stellarLuminosity, star.stellarRadius);

		// TODO: Now get the star's class

		return star;
	}
}
