package com.hipposretribution.system.formstar.planetoid;

/**
 * Abstract Class to store all planetoid information
 * 
 * @author zakski
 *
 */
abstract class Planetoid {
	public double axis; /* semi-major axis of the orbit (in AU) */
	public int axialTilt; /* units of degrees */
	public double ecc; /* eccentricity of the orbit */
	public int orbitZone; /* the 'zone' of the planet */

	public double mass; /* mass (in solar masses) */
	public double density; /* density (in g/cc) */
	public double radius; /* equatorial radius (in km) */

	public boolean gasGiant; /* TRUE if the planet is a gas giant */
	public boolean resonant; /* TRUE if in resonant rotation */
	public boolean greenhouseEffect; /* runaway greenhouse effect? */

	public double orbitPeriod; /* length of the local year (days) */
	public double dayLength; /* length of the local day (hours) */

	public double escVelocity; /* units of cm/sec */
	public double surfAccel; /* units of cm/sec2 */
	public double rmsVelocity; /* units of cm/sec */
	public double molec_weight; /* smallest molecular weight retained */
	public double surfGravity; /* units of Earth gravities */
	
	public double volatileGasInventory;
	public double surfPressure; /* units of millibars (mb) */
	public double boilPoint; /* the boiling point of water (Kelvin) */
	public double albedo; /* albedo of the planet */
	public double surf_temp; /* surface temperature in Kelvin */
	
	public double hydrosphere; /* fraction of surface covered */
	public double cloud_cover; /* fraction of surface covered */
	public double ice_cover; /* fraction of surface covered */
}
