package com.hipposretribution.system.formstar.star;

import java.util.Random;

/**
 * Class to Represent a Star
 * 
 * @author zakski
 *
 */
public class Star {

	String stellarClass; // the class of the sun. TODO Get Methods to calculate this / create startype enums

	public double stellarMass; // weight of the star in Solar Mass
	public double stellarLuminosity; // brightness of the star in Solar Luminosity
	public double stellarRadius; // radius of the star in Solar Radius
	public double stellarTemp; // temperature of the star in kelvin

	public double mainSeqLife; // Major Sequence Lifespan in terms of years
	public double age; // age of the star

	public double radiusEcosphere; // outer limit of the Star's Habitable zone
	public double radiusGreenhouse; // inner limit of the Star's Habitable zone

	
	/**
	 * Method to procedurally generate a star
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @return - the generated star
	 */
	public static Star generate(Random rand){
		return StarCalc.formStar(rand);
	}
	
}
