package com.hipposretribution.system.formstar;

public class SolarConst {

	/**
	 * Constructor Not Needed
	 */
	private SolarConst() {
	}

	/* Star Age & Main Sequence Lifespan */
	public static final double SUN_MS_LIFESPAN = 1.0E10; // the lifespan of our own sun on the ms.
	public static final double AGE_OUTER_LIMIT = 6.0E9;
	public static final double AGE_INNER_LIMIT = 1.0E9;

	/* Habitable Zones */
	public static final double GREENHOUSE_EFFECT_CONST = 0.93; /* affects inner radius.. */

	/* Temperature */
	public static final double SUN_SURFACE_TEMP = 5650; // in kelvins

}
