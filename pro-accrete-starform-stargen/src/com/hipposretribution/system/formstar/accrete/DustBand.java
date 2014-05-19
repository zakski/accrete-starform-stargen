package com.hipposretribution.system.formstar.accrete;

/**
 * 
 * Stores the data for a band of dust of gas. Contains the inner and outer edge, and whether it has dust or
 * gas present. Uses an internal linked-list structure to maintain the list of bands.
 * 
 * Internals are exposed for manipulation.
 *
 * @author zakski
 */
class DustBand {

	double innerEdge; // inner edge (in AU)
	double outerEdge; // outer edge (in AU)
	boolean hasDust; // dust present
	boolean hasGas; // gas present
	DustBand next; // next DustBand, LinkedList style

	/**
	 * Initial Constructor during Accretion
	 * 
	 * @param inner_limit inner limit of the dust band
	 * @param outer_limit outer limit of the dust band
	 */
	DustBand(double inner_limit, double outer_limit) {
		this(inner_limit, outer_limit, true, true);
	}

	/**
	 * Subsequent Constructor for all Dustbands during Accretion
	 * 
	 * @param inner_limit inner limit of the dust band
	 * @param outer_limit outer limit of the dust band
	 * @param dust_present if dust is present
	 * @param gas_present if gas is present
	 */
	DustBand(double inner_limit, double outer_limit, boolean dust_present, boolean gas_present) {
		innerEdge = inner_limit;
		outerEdge = outer_limit;
		hasDust = dust_present;
		hasGas = gas_present;
		next = null;
	}
}
