package com.hipposretribution.random;

import java.util.Random;

public class RandomUtil {

	private RandomUtil() {
	}
	
	public static int nextInt(Random rand, int low, int high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextInt() * (high - low) + low;
	}

	public static float nextFloat(Random rand, float low, float high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextFloat() * (high - low) + low;
	}

	public static double nextDouble(Random rand, double low, double high) {
		if (high < low) {
			throw new IllegalArgumentException("high must be greater than low");
		}

		return rand.nextDouble() * (high - low) + low;
	}

	public static double variation(Random rand, double value, double variation) {
		return (value + (value * nextDouble(rand, -variation, variation)));
	}
	
	
	public static <O> void shuffle(Random rand, O[] array) {
		for (int i = array.length - 1; i > 0; i--) {
			int j = rand.nextInt(i + 1);
			O temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

	public static void shuffle(Random rand, short[] array) {
		for (int i = array.length - 1; i > 0; i--) {
			int j = rand.nextInt(i + 1);
			short temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
}
