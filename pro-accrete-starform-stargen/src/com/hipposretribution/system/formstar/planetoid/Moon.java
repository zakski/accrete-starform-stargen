package com.hipposretribution.system.formstar.planetoid;

/**
 * Class to represent a moon or failed moon
 * 
 * @author zakski
 *
 */
public class Moon extends Planetoid {
	
	public Moon next; // the next closest moon
	public Planetoid innermost; // the planet's first moon

}
