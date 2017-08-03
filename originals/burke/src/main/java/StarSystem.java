/**
 *
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
public class StarSystem extends AccreteObject implements PhysicalConstants
{
    public double x, y, z;
    public Star primary;
    public Planet planets;

    /**
     * Public constructor builds a star system with a random star.
     */
    public StarSystem()
    {
    	primary = new Star((int)(nextDouble()*60));  // more variety
    	//primary = new Star(random_number(0.6, 1.3)); // starform method
    	Initialize();
    }

    /**
     * Creates the planets of this system using Dole's accretion algorithm.
     */
    private void Initialize()
    {
	Planet last_planet = null, cur_planet = null;
	Protoplanet p;
	int I;

	Protosystem ps = new Protosystem(primary);
    	ps.dist_planetary_masses();
    	p = ps.planet_head;
    	while (p!=null)
    	{
	    if (p.mass > 0.0)
	    {
		cur_planet = new Planet(p);
		cur_planet.orbit_zone = primary.orb_zone(cur_planet.a);
		cur_planet.set_vital_stats(primary.SM,
		primary.r_greenhouse, primary.r_ecosphere, primary.age);
		// could generate moons here
		// 1. generate a new protosystem based on the planet and star
		// 2. pull out all of the protoplanets and create moons from them
		// 3. delete the protosystem
		if (last_planet == null)
		{
		    planets = cur_planet;
		}
		else
		{
		    last_planet.next_planet = cur_planet;
		}
		last_planet = cur_planet;
	    }
	    p = p.next_planet;
    	}
    	ps = null;
    }

    /**
     * Creates the planets of this system using a diddled Bode's Law.
     */
    public void initializeBode()
    {
	/* BODE - BODE-TITIUS SEQUENCE FOR SATELLITE ORBITS */
	double[]  BODE  = {0.4, 0.7, 1.0, 1.6, 2.8, 5.2, 10.0, 19.6, 29.2, 38.8};
	Planet last_planet = null, cur_planet = null;
	int I;

    	for (I=0;I<10;I++)
    	{
	    cur_planet = new Planet(primary.AU*BODE[I], primary.EM, primary.SM);
	    cur_planet.orbit_zone = primary.orb_zone(cur_planet.a);
	    cur_planet.set_vital_stats(primary.SM,
		    primary.r_greenhouse, primary.r_ecosphere, primary.age);
	    if (I==0) planets = cur_planet;
	    else last_planet.next_planet = cur_planet;
	    last_planet = cur_planet;
    	}

    	// the following loop adjusts planet types based on system layout
    	// beyond a certain mass ratio, assume the smaller planet couldn't form
    	cur_planet = planets;
    	last_planet = null;
    	while (cur_planet != null)
    	{
	    if ( cur_planet.plan_class != '-' ) 
	    {
		if ( last_planet != null ) 
		{
		    if ( last_planet.plan_class != '-' ) 
		    {
			if ( (cur_planet.mass/last_planet.mass)<0.005 )
			{
				cur_planet.plan_class = 'B';
			}
		    }
		}
		if ( cur_planet.next_planet != null )
		{
		    if ( cur_planet.next_planet.plan_class != '-' )
		    {
			if ( (cur_planet.mass/cur_planet.next_planet.mass)<0.005 )
			{
				cur_planet.plan_class = 'B';
			}
		    }
		}
	    }
	    last_planet = cur_planet;
	    cur_planet = cur_planet.next_planet;
    	}
    }
}

