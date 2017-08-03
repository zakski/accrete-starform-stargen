/**
 * This class handles elements which are global to every object
 * in the simulation.  In particular, it provides consistent access
 * to the central random number generator.
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
public class AccreteObject
{

    /**
     * Produces a Gaussian random variate with mean=0, standard deviation=1.
     * Provides a local method with access to global random number generator.
     */
    static public double NormalDeviate()
    {
	return cr.NormalDeviate();
    }

    /**
     * Produces a random variate whose natural logarithm is from the
     * Gaussian with mean=0 and the specified standard deviation.
     * Provides a local method with access to global random number generator.
     * @param sigma Standard deviation
     */
    static public double LognormalDeviate(double sigma)
    {
	return cr.LognormalDeviate(sigma);
    }

    /**
     * Returns a uniformly distributed random real number between the specified
     * inner and outer bounds.
     * Provides a local method with access to global random number generator.
     * @param inner Minimum value desired
     * @param outer Maximum value desired
     */
    static public double random_number(double inner, double outer)
    {
	return cr.random_number(inner, outer);
    }

    /**
     *   Returns a value within a certain uniform variation
     *   from the central value.
     * Provides a local method with access to global random number generator.
     *   @param value Central value
     *   @param variation Maximum (uniform) variation above or below center
     */
    static public double about(double value, double variation)
    {
	return cr.about(value, variation);
    }

    /**
     * Returns a value for orbital eccentricity between 0.0 and 1.0.
     * Provides a local method with access to global random number generator.
     */ 
    static public double random_eccentricity()
    {
	return cr.random_eccentricity();
    }

    /**
     * Returns a pseudo-random value between 0.0 and 1.0.
     * Provides a local method with access to global random number generator.
     */ 
    static public double nextDouble()
    {
	return cr.nextDouble();
    }

    static public CustomRandom cr;
    static
    {
        cr = new CustomRandom();
    }
}
