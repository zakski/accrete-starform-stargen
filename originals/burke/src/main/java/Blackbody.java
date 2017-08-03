/**
 * A Blackbody represents a body which radiates energy in a predictable
 * curve based solely on temperature.  Main sequence stars follow this
 * curve fairly well, as do most planets.
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
public class Blackbody extends AccreteObject implements PhysicalConstants
{
    //  Global constants

    static final public double SIGMA = 5.669E-5;

    // EM radiation: approximate frequency ranges
    // radio: 10 - 1000m
    // TV: 1 - 10m
    // microwaves; 10e-3 - 1
    // IR: 7e-7 - 1e-3
    // vis: 4e-7 - 7e-7
    // UV: 1e-8 - 4e-7
    // Xray: 5e-12 - 1e-8
    // gamma: 1e-15 - 5e-12

    /**
     * Temperature of the body, in degrees Kelvin.
     */
    public double TEMP;

    /**
     * Returns blackbody emission of this body in ergs
     * per square centimeter by solving the emission equation
     * at a specified wavelength.
     * @param LAMBDA Wavelength in angstroms
     */
    public double E(double LAMBDA)  // emission at wavelength
    {
	double TERM1, TERM2, LAMBDA1, LAMBDA5;
	double H,K0,C;

	H=(6.626E-27);		// ERG/S
	K0=(1.380E-16);		// ERG/DEG
	C=(2.997925E+10);	// CM/S2
	TERM1 = 2.0*H*C*C;
	LAMBDA5 = Math.exp(Math.log(LAMBDA*ANGSTROM)*5.0);
	TERM2 = H*C/(LAMBDA*ANGSTROM*K0*TEMP);
	return (TERM1/LAMBDA5)*(1.0/(Math.exp(TERM2)-1.0));
    }

    /**
     * Returns visible light blackbody emission of this body in ergs
     * per square centimeter by integrating the emission equation
     * between 4,000 and 7,000 angstroms.
     */
    public double VISEMIT()
    {
	int I;
	double SUM = 0.0;

	for(I=4000; I<7000; I+=50)
	{
	    SUM += 50.0*ANGSTROM*(E((double)I)+E((double)(I+50.0)))/2.0;
	}
	return SUM;
    }

    /**
     * Returns infrared blackbody emission of this body in ergs
     * per square centimeter by integrating the emission equation
     * between 7,000 and 10,000,000 angstroms.
     */
    public double IREMIT()
    {
	int I;
	double SUM = 0.0;

	for(I=7000; I<10000; I+=50)  // to 1e-6
	{
	    SUM += 50.0*ANGSTROM*(E((double)I)+E((double)(I+50.0)))/2.0;
	}
	for(I=10000; I<100000; I+=500)  // to 1e-5
	{
	    SUM += 500.0*ANGSTROM*(E((double)I)+E((double)(I+500.0)))/2.0;
	}
	for(I=100000; I<1000000; I+=5000)  // to 1e-4
	{
	    SUM += 5000.0*ANGSTROM*(E((double)I)+E((double)(I+5000.0)))/2.0;
	}
	for(I=1000000; I<10000000; I+=50000)  // to 1e-3
	{
	    SUM += 50000.0*ANGSTROM*(E((double)I)+E((double)(I+50000.0)))/2.0;
	}
	return SUM;
    }

    /**
     * Returns ultraviolet blackbody emission of this body in ergs
     * per square centimeter by integrating the emission equation
     * between 100 and 4,000 angstroms.
     */
    public double UVEMIT()
    {
	double SUM = 0.0;

	for(int I=100; I<4000; I+=20)
	{
	    SUM += 20.0*ANGSTROM*(E((double)I)+E((double)(I+20.0)))/2.0;
	}
	return SUM;
    }

    /**
     * Returns total blackbody emission of this body in ergs
     * per square centimeter.
     */
    public double EMIT()
    {
	return SIGMA*(TEMP*TEMP*TEMP*TEMP);
    }
}

