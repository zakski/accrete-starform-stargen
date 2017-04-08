/**
 * A DustDisc manages the collection of DustBands representing
 * the dust and gas components of a protoplanetary disc.
 * <p><strong><center>Copyright information</center></strong></p>
 * <p>This Java class is copyright 1998 by Carl Burke. All rights reserved.
 * Substantial sections of this code were previously distributed in
 * different form as part of 'starform' (copyright 1989 Matthew Burdick)<p>
 * <p>This software is provided absolutely free and without warranty,
 * including but not limited to the implied warranties of merchantability
 * and fitness for a purpose.  You may use this code for any legal purpose
 * provided that you do not charge for it; this implies that you <em>may</em>
 * use this code as a component of a commercial system as long as the additional
 * functionality of the commercial system is greater than what this code
 * provides and that the commercial system is not primarily intended as
 * a simulation of solar system formation.  In other words, if you want to
 * write a science-fiction computer game that uses the code in this package
 * to build objects which are used in the game, that's great and permitted;
 * if you use this code to make a kickass solar-system-builder, you are not
 * allowed to distribute that software except for free.
 * <p>You are allowed and encouraged to modify this software, provided that
 * this copyright notice remains intact.  This notice may be reformatted,
 * but not removed.
 * <p>If you do use this software, I and the contributing authors listed
 * under "Acknowledgements" would appreciate some recognition.  If you make
 * changes, I would appreciate it if you would pass those changes back to me
 * for possible inclusion in the master.  At the time this notice was prepared,
 * my email address is <a href="mailto:cburke@mitre.org">cburke@mitre.org</a> and the home page for this software is
 * <a href="http://www.geocities.com/Area51/6902/w_accr.html">http://www.geocities.com/Area51/6902/w_accr.html</a>.
 * <a name="ack"><strong><center>Acknowledgements</center></strong></a>
 * <p>Matt Burdick, the author of 'starform' (freeware copyright 1989);
 * much of the code (particularly planetary environments) was adapted from this.</p>
 * <p>Andrew Folkins, the author of 'accretion' (public domain) for the Amiga; I used chunks
 * of his code when creating my displays.</p>
 * <p>Ed Taychert of <a href="http://www.irony.com/">Irony Games</a>, for the algorithm he uses 
 * to classify terrestrial planets in his tabular CGI implementation of 'starform'.</p>
 * <p>Paul Schlyter, who provided information about 
 * <a href="http://spitfire.ausys.se/psr/comp/ppcomp.html">computing planetary positions</a>.</p>
 */
public class DustDisc
{
    public boolean dust_left;
    public boolean gas;	// true if gas available in current working band
    public double cloud_eccentricity;
    public DustBand dust_head;
    public double body_inner_bound;
    public double body_outer_bound;

    /**
     * Determines whether dust is present within the effect radius of
     * a specific Protoplanet.
     * @param p Protoplanet within the disc
     * @returns true if there is a band containing dust which this body
     * can accrete.
     */
    public boolean dust_available(Protoplanet p)
    {
     	double inside_range = p.inner_effect_limit(cloud_eccentricity);
     	double outside_range = p.outer_effect_limit(cloud_eccentricity);
     	DustBand current_dust_band;
     	boolean dust_here = false;
     
     	current_dust_band = dust_head;
     	while ((current_dust_band != null) && (current_dust_band.outer_edge < inside_range))
	  		current_dust_band = current_dust_band.next_band;
     	if (current_dust_band == null) dust_here = false;
     	else dust_here = current_dust_band.dust_present;
     	while ((current_dust_band != null) && (current_dust_band.inner_edge < outside_range))
	{
	    dust_here = dust_here || current_dust_band.dust_present;
	    current_dust_band = current_dust_band.next_band;
	}
     	return(dust_here);
    }

    /**
     * Removes a band of dust from the specified DustBand, supplementing it
     * with 2 new bands.
     * @param node1 Band from which dust has been removed
     * @param min Inner limit of cleared lane (in AU)
     * @param max Outer limit of cleared lane (in AU)
     * @returns Next band in disc, outside affected band 'node1'.
     */
    public DustBand splitband(DustBand node1, double min, double max)
    {
    	DustBand node2 = new DustBand(node1);
    	DustBand node3 = new DustBand(node1);
    	node2.dust_present = false;  // dust sucked up by planetesimal
    	node2.gas_present = node1.gas_present && gas;
    	node2.inner_edge = min;
    	node2.outer_edge = max;
    	node3.inner_edge = max;
    	node1.outer_edge = min;
    	node1.next_band = node2;
    	node2.next_band = node3;
    	return node3.next_band;
    }

    /**
     * Removes outer portion of the specified DustBand, following it
     * with a new band.
     * @param node1 Band from which dust has been removed
     * @param outer Inner limit of cleared lane (in AU)
     * @returns Next band in disc, outside affected band 'node1'.
     */
    public DustBand splithigh(DustBand node1, double outer)
    {
    	DustBand node2 = new DustBand(node1);
    	node1.next_band = node2;
    	node1.dust_present = false;
    	node1.gas_present = node1.gas_present && gas;
    	node2.inner_edge = outer;
    	node1.outer_edge = outer;
    	return node2.next_band;
    }

    /**
     * Removes inner portion of the specified DustBand, preceding it
     * with a new band.
     * @param node1 Band from which dust has been removed
     * @param inner Outer limit of cleared lane (in AU)
     * @returns Next band in disc, outside affected band 'node1'.
     */
    public DustBand splitlow(DustBand node1, double inner)
    {
    	DustBand node2 = new DustBand(node1);
    	node1.next_band = node2;
    	node2.dust_present = false;
    	node2.gas_present = node1.gas_present && gas;
    	node2.inner_edge = inner;
    	node1.outer_edge = inner;
    	return node2.next_band;
    }

    /**
     * Identifies dust bands which may be affected by the specified protoplanet,
     * then modifies the disc accordingly.  Adjacent bands with identical
     * characteristics are merged to help reduce fragmentation of the disc.
     * @param min Inner limit of cleared lane (in AU)
     * @param max Outer limit of cleared lane (in AU)
     */
    public void update_dust_lanes(double min, double max)
    {
     	DustBand node1, node2;

     	dust_left = false;
     	// update dust bands under influence of Protoplanet
     	node1 = dust_head;
     	while (node1 != null)
     	{
	    int intval = node1.intersect(min, max);
	    if (intval == (DustBand.DBI_INNER_OK | DustBand.DBI_OUTER_OK))
	    {
		node1 = splitband(node1, min, max);
	    }
	    else if (intval == DustBand.DBI_OUTER_OK)
	    {
		node1 = splithigh(node1, max);
	    }
	    else if (intval == DustBand.DBI_INNER_OK)
	    {
		node1 = splitlow(node1, min);
	    }
	    else if (intval == DustBand.DBI_CONTAINED)
	    {
		node1.dust_present = false;
		node1.gas_present = node1.gas_present && gas;
		node1 = node1.next_band;
	    }
	    else
		node1 = node1.next_band;
     	}
     	// calculate whether accretable dust is left
     	for (node1=dust_head; node1!=null; node1=node1.next_band)
     	{
	    dust_left |=
	       (node1.dust_present &&
	       (node1.outer_edge >= body_inner_bound) &&
	       (node1.inner_edge <= body_outer_bound));
	    while (node1.mergeNext()) ;	// merge fragmented dust bands, if any
     	}
    }

    /**
     * Accretes dust and/or gas from all bands onto the specified protoplanet,
     * iterating until the marginal mass increase approaches zero.  Once the
     * new mass has been calculated, the dust bands are updated to reflect the
     * accretion of dust and/or gas onto the protoplanet.
     * @param p Protoplanet accreting in this cycle
     */
    public void accrete_dust(Protoplanet p)
    {
     	double temp_mass;
     	double start_mass = p.mass;
	double minimum_accretion = 0.0001 * start_mass;
     	double r_inner, r_outer, gatherLast, gatherNow;
	DustBand db;

	gatherNow = 0.0;
     	do
     	{
	    gatherLast = gatherNow;
	    // calculate new mass of protoplanet, considering last calculated
	    // quantity of accreted matter, then calculate region to be swept
	    // based on the updated mass.
	    p.mass = start_mass + gatherLast;
	    p.reduce_mass();
	    gas = !p.accretes_gas();
	    r_inner = p.inner_reduced_limit(cloud_eccentricity);
	    r_outer = p.outer_reduced_limit(cloud_eccentricity);
	    if (r_inner < 0.0) r_inner = 0.0;
	    // sweep through all dust bands, collecting matter within the
	    // effective reach of the protoplanet's gravity.
	    gatherNow = 0.0;
	    for (db=dust_head; db != null; db=db.next_band)
	    {
		gatherNow += db.collect_dust(r_inner, r_outer, p);
	    }
     	}
     	while ((gatherNow - gatherLast) >= minimum_accretion);
     	update_dust_lanes(
	    p.inner_effect_limit(cloud_eccentricity),
	    p.outer_effect_limit(cloud_eccentricity));
    }

    /**
     * Public constructor.
     * @param inner_limit_of_dust Innermost limit of dust
     * @param outer_limit_of_dust Outermost limit of dust
     * @param inner_bound Innermost limit of planetary orbits
     * @param outer_bound Outermost limit of planetary orbits
     */
    public DustDisc(
	double inner_limit_of_dust,
	double outer_limit_of_dust,
	double inner_bound,
	double outer_bound)
    {
     	dust_head = new DustBand(inner_limit_of_dust, outer_limit_of_dust);
     	body_inner_bound = inner_bound;
     	body_outer_bound = outer_bound;
     	dust_left = true;
    }
}

