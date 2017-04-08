/**
 * Implements a Star object for building alternative solar systems.
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
public class Star extends Blackbody implements PhysicalConstants
{
    static private final double GREENHOUSE_EFFECT_CONST = (0.93);	// affects inner radius..
    static private final double B = (1.2E-5);	// Used in Crit_mass calc

    static public final String CLASS_CODE = "OBAFGKM";

    // NOTE: Stellar temperatures were calculated using some pretty rough-and-ready measures,
    // so they could be quite far off (particularly at the high and low ends)

    // SPECT - TEMPERATURE TABLE BY SPECTRAL CLASS (old version)
    static private final double[] OLDSPECT = {
    25000.0, 23600.0, 22200.0, 20800.0, 19400.0, 18000.0, 16600.0, 15200.0, 13800.0, 12400.0,
    11000.0, 10650.0, 10300.0, 9950.0, 9600.0, 9250.0, 8900.0, 8550.0, 8200.0, 7850.0,
    7500.0, 7350.0, 7200.0, 7050.0, 6900.0, 6750.0, 6600.0, 6450.0, 6300.0, 6150.0,
    6000.0, 5900.0, 5800.0, 5700.0, 5600.0, 5500.0, 5400.0, 5300.0, 5200.0, 5100.0,
    5000.0, 4850.0, 4700.0, 4550.0, 4400.0, 4250.0, 4100.0, 3950.0, 3800.0, 3650.0,
    3500.0, 3150.0, 2800.0, 2450.0, 2100.0, 1750.0, 1400.0, 1050.0, 700.0, 350.0};

    // SPECT - TEMPERATURE TABLE BY SPECTRAL PLAN_CLASS (new version) 
    static private final double[] SPECT = {
    25000.0, 23600.0, 22200.0, 20800.0, 19400.0, 18000.0, 16600.0, 15200.0, 13800.0, 12400.0,
    11000.0, 10650.0, 10300.0, 9950.0, 9600.0, 9250.0, 8900.0, 8550.0, 8200.0, 7850.0,
    7500.0, 7350.0, 7200.0, 7050.0, 6900.0, 6750.0, 6600.0, 6450.0, 6300.0, 6150.0,
    6000.0, 5900.0, 5800.0, 5700.0, 5600.0, 5500.0, 5400.0, 5300.0, 5200.0, 5100.0,
    5000.0, 4850.0, 4700.0, 4550.0, 4400.0, 4250.0, 4100.0, 3950.0, 3800.0, 3650.0,
    3500.0, 3200.0, 2900.0, 2600.0, 2300.0, 2000.0, 1700.0, 1400.0, 1100.0, 800.0};

    // BC - 'BOLOMETRIC CORRECTION', ESTABLISHED BY CALCULATION OF RATIO OF
    // OVERALL ENERGY TO VISIBLE ENERGY, AND SHIFTING THE MAGNITUDES TO AGREE
    // WITH G2 STAR AT G2 TEMPERATURE. ADD THIS TO VISUAL MAGNITUDE 
    // CURVE HAS BEEN MANUALLY TRIMMED AT THE LOWER END 
    static private final double[] BC = 
    { 1.8770E+0, 1.7344E+0, 1.5864E+0, 1.4329E+0, 1.2737E+0,
      1.1089E+0, 9.3888E-1, 7.6439E-1, 5.8704E-1, 4.0991E-1,
      2.3869E-1, 1.9790E-1, 1.5835E-1, 1.2030E-1, 8.4102E-2,
      5.0144E-2, 1.8896E-2,-9.0779E-3,-3.3103E-2,-5.2363E-2,
     -6.5867E-2,-6.9601E-2,-7.1950E-2,-7.2793E-2,-7.1999E-2,
     -6.9424E-2,-6.4909E-2,-5.8280E-2,-4.9344E-2,-3.7890E-2,
     -2.3682E-2,-1.2553E-2,-8.8050E-8, 1.4066E-2, 2.9742E-2,
      4.7134E-2, 6.6354E-2, 8.7522E-2, 1.1077E-1, 1.3624E-1,
      1.6409E-1, 2.1068E-1, 2.6363E-1, 3.2363E-1, 3.9149E-1,
      4.6814E-1, 5.5465E-1, 6.5224E-1, 7.6234E-1, 8.8663E-1,
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    public int ST;	// stellar class code
    public double VM;	// absolute visual magnitude
    public double LUM;	// luminosity
    public double EM;	// emission
    public double SM;	// Stellar masses
    public double AU;	// putative distance for 1 "AU"
    public double main_seq_life;
    public double age;
    public double radius;
    public double r_ecosphere;
    public double r_greenhouse;

    /**
     * Creates a string representation of the star's 'class code'.
     * For Star objects built with the 'starform'-style constructor,
     * the results are undefined.  At some future time, additional
     * code may be added to calculate main sequence class given the
     * stellar mass; that day is not today.
     */
    public String classCode()
    {
	return CLASS_CODE.substring(ST/10+1,ST/10+2)+Integer.toString(ST%10);
    }

    /**
     * Performs calculations common to both constructors.
     */
    protected void commonConstructor()
    {
     	main_seq_life = 1.0E10 * (SM / LUM);
     	if ((main_seq_life >= 6.0E9))
	    age = random_number(1.0E9,6.0E9);
     	else 
	    age = random_number(1.0E9,main_seq_life);
	radius = RADIUS();
     	r_ecosphere = Math.sqrt(LUM);
     	r_greenhouse = r_ecosphere * GREENHOUSE_EFFECT_CONST;
    }

    /**
     * Makes a new star given the integer 'Class Code'.  There are 60 classes
     * which can be handled (B0 through M9); 'O' class stars and non-main-sequence
     * stars are not currently handled.
     * @param StellarClassCode Integer code (0-59) corresponding to stellar
     *     class (B0 - M9)
     */
    public Star(int StellarClassCode)
    {
    	ST = StellarClassCode;
    	TEMP = SPECT[ST];
    	VM = MAINSEQ() - BC[ST];
    	LUM = LUMINOSITY();
    	EM = LUM;
    	SM = MASS();
    	AU = AUSTAR(SM);
    	TEMP += NormalDeviate()*(TEMP/200.0);
    	commonConstructor();
    }

    /**
     * Constructor using the 'starform' star generation method.  That method
     * involves a simple selection of stellar mass ratio relative to Sol,
     * which allows the user to focus on stars likely to have habitable planets.
     * @param StellarMassRatio Ratio of star's mass to Sol
     */
    public Star(double StellarMassRatio)
    {
    	// ought to guess at stellar class here...
    	// also need to estimate temperature here...
     	SM = StellarMassRatio;
     	LUM = luminosity();
     	EM = LUM;
     	AU = AUSTAR(SM);
    }

    /**
     * Calculate absolute visual magnitude of a main sequence star given
     * the temperature.  Generated from table of stellar magnitudes by
     * fitting to a cubic curve; there are some known problems with the
     * fit, e.g. the curve isn't steep enough at the high and low ends,
     * but I [Carl] don't want to work through it yet again.
     * @returns Absolute visual magnitude
     */
    public double MAINSEQ()
    {
	double A0 = 26.281;
	double A1 = -3.4495;
	double A2 = -0.77271;
	double A3 = 0.076305;
	double LTEMP;

	LTEMP = Math.log(TEMP/100.0);	// scaled by 100 as an artifact of the fit
	return A0+A1*LTEMP+A2*LTEMP*LTEMP+A3*LTEMP*LTEMP*LTEMP;
    }

    /**
     * Calculates stellar luminosity based on visual magnitude.
     * @returns Luminosity of star relative to Sol
     */
    public double LUMINOSITY()
    {
	return Math.exp((4.7-VM)/2.5);
    }

    /**
     * Calculates stellar mass using mass-luminosity relationship.
     * @returns Mass in Solar masses
     */
    public double MASS()
    {
	return Math.exp(Math.log(LUM)/3.5);
    }

    /**
     * Calculates stellar radius using luminosity and temperature.
     * I [Carl] forget where I got this; maybe derived from an astronomy text?
     * @returns Radius in Solar radii
     */
    public double RADIUS()
    {
	return Math.sqrt(LUM)*((6100.0/TEMP)*(6100.0/TEMP));
    }

    /**
     * Calculates distance to farthest edge of proplyd.
     * I [Carl] am unsure where this calculation is derived from.
     * @returns Maximum dust distance in AU
     */
    public double stellar_dust_limit()
    {
	return(200.0 * Math.pow(SM,(1.0 / 3.0)));
    }

    /**
     * Calculates distance to nearest possible planetary orbit.
     * I [Carl] am unsure where this calculation is derived from.
     * @returns Minimum planet distance in AU
     */
    public double nearest_planet()
    {
	return(0.3 * Math.pow(SM,(1.0 / 3.0)));
    }

    /**
     * Calculates distance to farthest possible planetary orbit.
     * I [Carl] am unsure where this calculation is derived from.
     * @returns Maximum planet distance in AU
     */
    public double farthest_planet()
    {
	return(50.0 * Math.pow(SM,(1.0 / 3.0)));
    }

    /**
     * Calculates the mass at which a protoplanet orbiting this star
     * will accrete gas as well as dust.
     * @param orb_radius Semi-major axis of protoplanet
     * @param eccentricity Orbital eccentricity of protoplanet
     * @returns Critical mass of protoplanet, in Solar masses
     */
    public double critical_limit(double orb_radius, double eccentricity)
    {
     	double perihelion_dist = (orb_radius - orb_radius * eccentricity);
     	double temp = perihelion_dist * Math.sqrt(LUM);
     	return(B * Math.pow(temp,-0.75));
    }

    /**
     * Estimates luminosity of star.  Probably generated through curve fitting.
     * @returns Luminosity of star
     */
    public double luminosity()
    {
     	double n;
     
     	if (SM < 1.0)
	    n = 1.75 * (SM - 0.1) + 3.325;
     	else 
	    n = 0.5 * (2.0 - SM) + 4.4;
     	return(Math.pow(SM,n));
    }

    /**
     * Calculates the 'orbital zone' of a particle (1, 2, or 3) based
     * on distance from the star.  Orbital zone is a rough measure of
     * composition for dust particles.
     * @param orb_radius Distance fom star in AU
     * @returns Zone of particle (1, 2, or 3)
     */
    public int orb_zone(double orb_radius)
    {
     	if (orb_radius < (4.0 * Math.sqrt(LUM)))
	    return(1);
     	else 
     	{
	    if ((orb_radius >= (4.0 * Math.sqrt(LUM))) &&
		(orb_radius < (15.0 * Math.sqrt(LUM))))
		return(2);
	    else 
		return(3);
     	}
    }

    /**
     * Provides an estimation of 1 'Astronomical Unit' for other planets
     * around other stars. Purely invented.
     * @param MASS Mass in Solar masses
     */
    public double AUSTAR(double MASS)
    {
	// an alternative approach is to use r_ecosphere, which is 1 AU for Sol.
	return 1.0/Math.sqrt(1.0/MASS);
    }

    /**
     * Provides an estimation of 1 'Astronomical Unit' for moons
     * around other planets. Purely invented.
     * @param MASS Mass in Earth masses
     */
    public double AUPLAN(double MASS)
    {
	return 150000000.0/(6.8*Math.sqrt(333000.0/MASS));
    }
}


