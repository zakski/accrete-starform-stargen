package com.szadowsz.formstar.planetoid;


/**
 * Class to represent a planet or failed planet
 * 
 * @author zakski
 *
 */
public class Planet extends Planetoid {
	
	public Planet next; // the next closest planet
	public Moon innermost; // the planet's first moon

}
