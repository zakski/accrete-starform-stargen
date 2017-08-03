/**
 * DustBands represent sections of the protoplanetary disc which
 * contain gas and/or dust to be accreted.
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
public class DustBand extends Object
{
    static public final int DBI_NO_INTERSECTION	 = 0;
    static public final int DBI_INNER_OK	 = 1;
    static public final int DBI_OUTER_OK	 = 2;
    static public final int DBI_CONTAINED	 = 4;
	
    public double inner_edge;
    public double outer_edge;
    public boolean dust_present;
    public boolean gas_present;
    public DustBand next_band;

    /**
     * Public constructor.
     * @param inner_limit_of_dust Inner edge of the dust band (in AU)
     * @param outer_limit_of_dust Outer edge of the dust band (in AU)
     */
    public DustBand(double inner_limit_of_dust, double outer_limit_of_dust)
    {
     	next_band = null;
     	outer_edge = outer_limit_of_dust;
     	inner_edge = inner_limit_of_dust;
     	dust_present = true;
     	gas_present = true;
    }

    /**
     * Copy constructor.
     * @param db Parent DustBand from which to extract values.
     */
    public DustBand(DustBand db) // copy constructor
    {
    	if (db==null) return;
    	inner_edge = db.inner_edge;
    	outer_edge = db.outer_edge;
    	dust_present = db.dust_present;
    	gas_present = db.gas_present;
    	next_band = db.next_band;
    }

    /**
     * Calculates the intersection of this dust band with a range of
     * distances and returns a mask constructed from the DBI_xxx flags
     * exported by this class.  Typically used to identify bands which
     * overlap the effect radius of a protoplanet.
     * @param inner Inner edge of the intersecting band (in AU)
     * @param outer Outer edge of the intersecting band (in AU)
     */
    public int intersect(double inner, double outer)
    {
    	int intval = 0;
    	if (outer_edge <= inner || inner_edge >= outer) return DBI_NO_INTERSECTION;
    	if (inner_edge < inner) intval |= DBI_INNER_OK;
    	if (outer_edge > outer) intval |= DBI_OUTER_OK;
    	if (inner_edge >= inner && outer_edge <= outer) intval |= DBI_CONTAINED;
    	return intval;
    }

    /**
     * Compares two dust bands for compatibility.
     * @returns true if the two bands agree on the presence of dust and gas.
     * @param db DustBand to be compared to this one.
     */
    public boolean isCompatibleWith(DustBand db)
    {
	return (dust_present == db.dust_present) &&
	       (gas_present == db.gas_present);
    }

    /**
     * Merge a dust band with its successor, allowing the successor to be
     * garbage collected.
     * @returns true is the merge was successful 
     */
    public boolean mergeNext()
    {
	if (next_band != null)
	{
	    if (isCompatibleWith(next_band))
	    {
		outer_edge = next_band.outer_edge;
		next_band = next_band.next_band;
		return true;
	    }
	}
	return false;
    }

    /**
     * Calculate the amount of dust which the specified protoplanet can
     * accrete from this dust band, if any.
     * @returns Quantity of dust, in units of solar masses. 
     */
    public double collect_dust(double r_inner, double r_outer, Protoplanet p)
    {
     	double gather = 0.0;

     	/* as last_mass increases, temp approaches 1.
	 * reduced_mass approaches 1 even quicker.
	 * as reduced_mass approaches 1, r_inner approaches 0 and
	 * r_outer approaches 2*a*(1.0 + e).  Apparently the integration
	 * is from 0 to 2a.
	 * The masses are expressed in terms of solar masses; temp is therefore
	 * the ratio of the planetary mass to the total system (sun + planet)
	 */
     	if (intersect(r_inner, r_outer) != DBI_NO_INTERSECTION)
     	{
	    double bandwidth = (r_outer - r_inner);
	    double temp1 = r_outer - outer_edge;
	    double temp2 = inner_edge - r_inner;
	    double width;
	    double temp;
	    double volume;
	    double retval;
    
	    if (bandwidth <= 0.0) bandwidth = 0.0;
	    if (temp1 < 0.0) temp1 = 0.0;
	    width = bandwidth - temp1;
	    if (temp2 < 0.0) temp2 = 0.0;
	    width -= temp2;
	    if (width < 0.0) width = 0.0;
	    temp = 4.0 * Math.PI * Math.pow(p.a,2.0) * p.reduced_mass * 
		    (1.0 - p.e * (temp1 - temp2) / bandwidth);
	    volume = temp * width;
	    gather = (volume * p.mass_density(dust_present, gas_present));
     	}
	return gather;
    }
}

