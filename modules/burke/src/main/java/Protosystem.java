public class Protosystem extends Object implements PhysicalConstants
{
    public Star star;
    public Planet planet;
    public DustDisc disc;
    public Protoplanet planet_head;
    public double body_inner_bound;
    public double body_outer_bound;

    /**
     * Star system contructor.  Builds an accretion disc for the
     * specified star.
     * @param s Primary for this system.
     */
    public Protosystem(Star s)
    {
	star = s;
	planet = null;
	planet_head = null;
	body_inner_bound = star.nearest_planet();
	body_outer_bound = star.farthest_planet();
	disc = new DustDisc(0.0, star.stellar_dust_limit(),
			    star.nearest_planet(), star.farthest_planet());
	disc.cloud_eccentricity = 0.2;
    }

    /**
     * Planetary system contructor.  Builds an accretion disc for the
     * specified planet around the specified star.  This has not been
     * exercised to any significant degree, because moon formation
     * doesn't seem to follow Dole's model quite as well.
     * @param s Primary for this system.
     * @param p Planet around which these moons will form.
     */
    public Protosystem(Star s, Planet p)
    {
	star = s;
	planet = p;
	planet_head = null;
	body_inner_bound = planet.nearest_moon();
	body_outer_bound = planet.farthest_moon();
	disc = new DustDisc(0.0, star.stellar_dust_limit(),
			    planet.nearest_moon(), planet.farthest_moon());
	disc.cloud_eccentricity = 0.2;
    }

    /**
     * Searches the planetesimals already present in this system
     * for a possible collision.  Does not run any long-term simulation
     * of orbits, doesn't try to eject bodies...
     * @param p Newly injected accreting protoplanet to test
     */
    public void coalesce_planetesimals(Protoplanet p)
    {
     	// note that p is not consumed by this routine...
     	Protoplanet node1, node2, node3;
     	boolean finished; 
     	double temp, dist1, dist2, a3;
     	double reduced_mass = p.mass;
     
     	finished = false;
     	// try to merge Protoplanets
     	node2 = node1 = planet_head;
     	while (node1 != null)
     	{
	    node2 = node1;
	    temp = node1.a - p.a;
	    if ((temp > 0.0))
	    {
		dist1 = (p.a * (1.0 + p.e) * (1.0 + p.mass)) - p.a;
		/* x aphelion   */
		if (node1.mass <= 0.0) reduced_mass = 0.0;
		else reduced_mass = Math.pow((node1.mass / (1.0 + node1.mass)),(1.0 / 4.0));
		dist2 = node1.a - (node1.a * (1.0 - node1.e) * (1.0 - reduced_mass));
	    }
	    else 
	    {
		dist1 = p.a - (p.a * (1.0 - p.e) * (1.0 - p.mass));
		/* x perihelion */
		if (node1.mass <= 0.0) reduced_mass = 0.0;
		else reduced_mass = Math.pow(node1.mass / (1.0 + node1.mass),(1.0 / 4.0));
		dist2 = (node1.a * (1.0 + node1.e) * (1.0 + reduced_mass)) - node1.a;
	    }
	    if (((Math.abs(temp) <= Math.abs(dist1)) || (Math.abs(temp) <= Math.abs(dist2))))
	    {
		//System.out.println("Collision between two planetesimals!");
		a3 = (node1.mass + p.mass) / ((node1.mass / node1.a) + (p.mass / p.a));
		temp = node1.mass * Math.sqrt(node1.a) * Math.sqrt(1.0 - (node1.e*node1.e));
		temp += (p.mass * Math.sqrt(p.a) * Math.sqrt(Math.sqrt(1.0 - (p.e*p.e))));
		temp /= ((node1.mass + p.mass) * Math.sqrt(a3));
		temp = 1.0 - (temp*temp);
		if (((temp < 0.0) || (temp >= 1.0))) temp = 0.0;
		p.e = Math.sqrt(temp);
		temp = node1.mass + p.mass;
		node1.a = a3;
		node1.e = p.e;
		node1.mass = temp;
		disc.accrete_dust(node1);
		node1 = null;
		finished = true;
	    }
	    else 
	    node1 = node1.next_planet;
     	}
     	if (!finished)
     	{
	    // add copy of planetesimal to planets list
	    node3 = new Protoplanet(p);
	    node3.gas_giant = (p.mass >= p.crit_mass);
	    if ((planet_head == null))
	    {
		planet_head = node3;
	    }
	    else 
	    {
		node1 = planet_head;
		if ((p.a < node1.a))
		{
		    node3.next_planet = node1;
		    planet_head = node3;
		}
		else if ((planet_head.next_planet == null))
		{
		    planet_head.next_planet = node3;
		}
		else 
		{
		    while (((node1 != null) && (node1.a < p.a)))
		    {
			node2 = node1;
			node1 = node1.next_planet;
		    }
		    node3.next_planet = node1;
		    node2.next_planet = node3;
		}
	    }
     	}
    }

    /**
     * Accretes protoplanets from the dust disc in this system.
     * @returns First protoplanet of accreted system, as the head
     *     element of a list of protoplanets.
     */
    public Protoplanet dist_planetary_masses()
    {
     	Protoplanet p0;

     	while (disc.dust_left)
     	{
	    p0 = new Protoplanet(disc.body_inner_bound, disc.body_outer_bound);
	    if (disc.dust_available(p0))
	    {
		p0.dust_density =
		    DUST_DENSITY_COEFF * Math.sqrt(star.SM)
		    * Math.exp(-ALPHA * Math.pow(p0.a,(1.0 / N)));
		p0.crit_mass = star.critical_limit(p0.a,p0.e);
		disc.accrete_dust(p0);
		if (p0.massOK()) coalesce_planetesimals(p0);
		else
		{
		    //System.out.println(".. failed due to large neighbor.");
		}
	    }
     	}
     	return(planet_head);
    }

    /**
     * Accretes protoplanets from the dust disc in this system.
     * This ought to work, but has not been extensively tested.
     * @returns First protoplanet of accreted system, as the head
     *     element of a list of protoplanets.
     */
    public Protoplanet dist_moon_masses()
    {
     	Protoplanet p0;

     	while (disc.dust_left)
     	{
	    p0 = new Protoplanet(disc.body_inner_bound, disc.body_outer_bound);
	    if (disc.dust_available(p0))
	    {
		p0.dust_density =
		    DUST_DENSITY_COEFF * Math.sqrt(planet.mass/SUN_MASS_IN_EARTH_MASSES)
		    * Math.exp(-ALPHA * Math.pow(p0.a,(1.0 / N)));
		p0.crit_mass = star.critical_limit(planet.a,planet.e);
		disc.accrete_dust(p0);
		if (p0.massOK()) coalesce_planetesimals(p0);
		else
		{
		    //System.out.println(".. failed due to large neighbor.");
		}
	    }
     	}
     	return(planet_head);
    }

    public void print_Protoplanets()
    {
    	Protoplanet p = planet_head;
    	while (p!=null) {p.print(); p = p.next_planet;}
    }
}

