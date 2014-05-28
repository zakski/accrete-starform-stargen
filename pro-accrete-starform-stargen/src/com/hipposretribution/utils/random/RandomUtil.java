package com.hipposretribution.utils.random;

import java.util.Random;

public class RandomUtil {

	private RandomUtil() {
	}

	/**
	 * Method to generate an int between the lower and upper bound
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param low - lower bound value
	 * @param high - upper bound value
	 * @return an int between the lower and upper bound
	 */
	public static int nextInt(Random rand, int low, int high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextInt() * (high - low) + low;
	}

	/**
	 * Method to generate a float between the lower and upper bound
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param low - lower bound value
	 * @param high - upper bound value
	 * @return a float between the lower and upper bound
	 */
	public static float nextFloat(Random rand, float low, float high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextFloat() * (high - low) + low;
	}

	/**
	 * Method to generate a double between the lower and upper bound
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param low - lower bound value
	 * @param high - upper bound value
	 * @return a double between the lower and upper bound
	 */
	public static double nextDouble(Random rand, double low, double high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextDouble() * (high - low) + low;
	}

	/**
	 * Method to generate a double based on a value between -variation and + varation
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param value - the value to generated a variation on
	 * @param variation - the allowed percent to vary by
	 * @return a variation on the value
	 */
	public static double variation(Random rand, double value, double variation) {
		return (value + (value * nextDouble(rand, -variation, variation)));
	}

	/**
	 * Method to shuffle an array using the modern version of the Fisher–Yates shuffle
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param array - Object Array
	 */
	public static <O> void shuffle(Random rand, O[] array) {
		for (int i = array.length - 1; i > 0; i--) {
			int j = rand.nextInt(i + 1);
			O temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

	/**
	 * Method to shuffle an array using the modern version of the Fisher–Yates shuffle
	 * 
	 * @param rand - pseudo-random number generator interface
	 * @param array - short primitive array
	 */
	public static void shuffle(Random rand, short[] array) {
		for (int i = array.length - 1; i > 0; i--) {
			int j = rand.nextInt(i + 1);
			short temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
}
