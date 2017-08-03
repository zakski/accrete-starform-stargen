/**
 * This class provides an object representing a planetary body,
 * complete with atmosphere.  Two separate sets of methods are
 * provided.  The first set is empirical, usually simplistic, and
 * built for use in various games I was experimenting with at the
 * time.  The second set is based more on physics, using calculations
 * presented in journals such as Icarus.
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
public class Planet extends Blackbody
    implements PhysicalConstants
{
    public double a;			// semi-major axis of the orbit (in AU)
    public double e;			// eccentricity of the orbit	     
    public double where_in_orbit;	// position along orbit (in radians) 
    public double mass;			// mass (in Earth masses)	     
    public boolean gas_giant;		// true if the planet is a gas giant 
    public int orbit_zone;		// the 'zone' of the planet          
    public double radius;		// equatorial radius (in km)	     
    public double density;		// density (in g/cc)		     
    public double orb_period;   	// length of the local year (days)   
    public double day;			// length of the local day (hours)   
    public int resonant_period;		// true if in resonant rotation   
    public int axial_tilt;		// units of degrees		     
    public double esc_velocity;		// units of cm/sec		     
    public double surf_accel;  		// units of cm/sec2		     
    public double surf_grav;   		// units of Earth gravities	     
    public double rms_velocity;		// units of cm/sec		     
    public double molec_weight;		// smallest molecular weight retained
    public double volatile_gas_inventory;
    public double GH2, GH2O, GN2, GO2, GCO2;  // gas retention percentages
    public double surf_pressure;	// units of millibars (mb)	     
    public boolean greenhouse_effect;	// runaway greenhouse effect?	
    public double boil_point;		// the boiling point of water (Kelvin)
    public double albedo;		// albedo of the planet		     
    public double surf_temp;   		// surface temperature in Kelvin     
    public double min_temp, max_temp;	// surface temperature ranges 
    public double avg_temp;		// weighted average of iterations 
    public double hydrosphere;		// fraction of surface covered	     
    public double cloud_cover;		// fraction of surface covered	     
    public double ice_cover;		// fraction of surface covered	     
    public char plan_class;		// general type classification
    public Planet next_planet;
    public Planet first_moon;
    // these data elements are star related, but are stored here for my use
    public double r_ecosphere;
    public double resonance;
    public double stell_mass_ratio;
    public double age;
    // albedo factors
    public double cloud_factor, water_factor, rock_factor, airless_rock_factor,
    ice_factor, airless_ice_factor;
    public int its;
    public boolean temp_unstable;

    //
    // EMPIRICAL METHODS (SET 1)
    //

    /**
     * Generates a rough-and-ready calculation into Terrestrial and
     * Gas Giant categories based on temperature.
     * @returns 'T' for Terrestrial, 'G' for Gas Giant.
     */
    public char classify_by_temperature()  // based on temperature
    {
	if ( TEMP>200.0 )
	{
	    gas_giant = false;
	    return 'T';
	}
	else
	{
	    gas_giant = true;
	    return 'G';
	}
    }

    /**
     * Generates a rough-and-ready calculation into Terrestrial and
     * Gas Giant categories based on whether the protoplanet accreted gas.
     * @returns 'T' for Terrestrial, 'G' for Gas Giant.
     */
    public char classify_by_accretion()  // based on accretion status
    {
	return (gas_giant ? 'G' : 'T');
    }

    /**
     * Determines planetary mass through a quick 'accretion' of
     * mass within a portion of a disc. Gives a mass profile similar
     * to the solar system when used with Bode's Law calculations.
     * @param MASS Mass of primary in Solar masses
     * @param DIST Semi-major axis of orbit in AU
     * @param PLAN_CLASS 'T' or 'G' denoting 'class' of planet
     * @returns Planetary mass in Solar masses
     */
    public double mass_by_integration(double MASS, double DIST, char PLAN_CLASS)
    {
	double BV;
	double RF;
	
	RF = LognormalDeviate(1.0);
	if ( PLAN_CLASS=='T' )
	{
	    BV = DIST*DIST; // accretion from a disk 
	    return 2.7*MASS*Math.exp(-DIST*Math.sqrt(DIST))*BV*RF;
	}
	else
	{
	    BV = DIST*DIST*DIST; // accretion from a volume 
	    return 2.7*Math.exp(-DIST/(2.7*MASS))*BV*RF;
	}
    }

    /**
     * Estimates planetary density by planetary class, randomly
     * distributed around central values.
     * @param PLAN_CLASS 'T' for Terrestrial, 'G' for Gas Giant
     * @returns Density in grams per cubic centimeter
     */
    public double density_by_temperature(char PLAN_CLASS)
    {
	if ( PLAN_CLASS=='T' )
	{
	    return LognormalDeviate(0.1)*5.5;
	}
	else
	{
	    if ( PLAN_CLASS=='G' )
		return LognormalDeviate(0.1);
	    else
		return 0.0;
	}
    }

    /**
     * Returns radius of the planet in kilometers.  Almost identical
     * to 'volume_radius()', but remains here by historical accident.
     * @param MASS Mass in Earth masses
     * @param DENSITY Average density in grams per cubic centimeter
     * @param PLAN_CLASS 'T' for Terrestrial, 'G' for Gas Giant
     * @returns Planetary radius in kilometers
     */
    public double planet_radius(double MASS,double DENSITY, char PLAN_CLASS)
    {
    if ( PLAN_CLASS=='-' )
	return 0.0;
    else
	return Math.exp(Math.log(MASS*6.0E+12/(DENSITY*(4.0/3.0)*Math.PI))/3.0);
    }

    /**
     * Calculates surface gravity in cm/sec^2
     * @param MASS Mass in Earth masses
     * @param RAD Radius in kilometers
     * @returns Surface gravity (acceleration) in cm/sec^2.
     */
    public double surface_gravity(double MASS, double RAD)
    {
	if ( RAD==0.0 )
	    return 0.0;
	else
	    return (G * MASS * MEARTH) / (RAD * RAD * 1.0E10);
    }

    /**
     * Calculates 'escape energy'. Escape energy was an idea I [Carl] was
     * toying with for a game, and this routine tries to find planetary
     * escape energy in the same units as constant accelleration travel
     * across the star system.  Probably not useful to anybody else (and
     * may not be useful to me if I can't find those PBEM notes :)
     * @param MASS Mass in Earth masses
     * @param RADIUS Radius in kilometers
     * @returns Energy of escape, in 'standard' units
     */ 
    public double PESCAPE(double MASS, double RADIUS)
    {
	double  GME, AU, RE, A;
	
	GME=2.0 * 6.67E-08 * 6.0E+27 * MASS;
	AU=1.5E+13; // 1 AU IN CM 
	RE=RADIUS*1.0E5; // RADIUS IN CM 
	RE=RE/AU;
	A=Math.sqrt(GME/RE)-RE;
	return A/AU;
    }

    /**
     * Estimates blackbody temperature of a planet. The temperature is
     * calculated for a planet with a given albedo at a specific distance
     * from a primary of the specified luminosity.
     * @param DIST Semi-major axis of orbit in AU
     * @param LUM Luminosity of primary (relative to Sol???)
     * @returns Temperature in degrees Kelvin
     */
    public double planet_temperature(double DIST, double LUM)
    {
	double PTEMP=(((1.0-albedo)/(DIST*DIST)) * LUM * (1370000.0/SIGMA));
	return Math.exp(Math.log(PTEMP)/4.0);
    }

    /**
     * Calculates the approximate ratio (from none to all) of a gas
     * which is retained in the atmosphere of this planet.  Does not
     * attempt to decide just how much gas that really is, or the
     * resulting contribution to atmospheric pressure.
     * @param WT Molecular weight of gas in question
     * @param TEMP Blackbody temperature
     * @param MASS Mass in Earth masses
     * @param RAD Radius in centimeters
     * @returns Unitless ratio between 0.0 and 1.0
     */
    public double gas_retention(double WT, double TEMP, double MASS, double RAD)
    {
	// 6*(MEAN VELOCITY)/(ESCAPE VELOCITY)
	// (modified to a factor of 8 because I liked the results better)
	double SPD, ESC;
	
	if ( RAD==0.0 ) { return 10.0; };
	SPD=Math.sqrt((3.0*BK*TEMP)/(WT*MH));
	ESC=Math.sqrt((2.0*G*MASS)/RAD);
	return 8.0*(SPD/ESC); 
    }

    /**
     * Simplistic constructor, intended for use with Bode's Law routines
     * @param AuDist Semi-major axis of orbit in AU
     * @param EM Emission of the star relative to Sol
     * @param SM Stellar mass relative to Sol
     */
    public Planet(double AuDist, double EM, double SM)
    {
	double PT;
	
	next_planet = null;
	first_moon = null;
	a = AuDist;  // is AU * BODE[I]
	e = 0.0;
	where_in_orbit = (nextDouble()*360.0) * DEG_TO_RAD;
	albedo = 0.0;      // start with albedo of 0
	TEMP = planet_temperature(AuDist, EM);
	plan_class = classify_by_temperature();
	mass = mass_by_integration(SM, a, plan_class);
	if ( mass<1.0E-6 )
	{
	    mass = 0.0;
	    plan_class = '-';
	}
	density = density_by_temperature(plan_class);
	radius = planet_radius(mass, density, plan_class);
	GH2 = gas_retention(H2, TEMP, mass*MEARTH, radius*1.0E+5);
	GH2O = gas_retention(H2O, TEMP, mass*MEARTH, radius*1.0E+5);
	GN2 = gas_retention(N2, TEMP, mass*MEARTH, radius*1.0E+5);
	GO2 = gas_retention(O2, TEMP, mass*MEARTH, radius*1.0E+5);
	GCO2 = gas_retention(CO2, TEMP, mass*MEARTH, radius*1.0E+5);
	// classification scheme needs to be redone
	while (true)
	{
	    if ( plan_class=='T' )
	    {
		albedo = 1.0 - GH2O;
		if ( albedo<0.0 ) { albedo=0.0; };
		if ( GH2<1.0 ) { plan_class = 'E'; };
		if ( GN2>1.0 ) { plan_class = 'O'; };
		if ( GO2>1.0 ) { plan_class = 'C'; };
		if ( GCO2>1.0 ) { plan_class = 'V'; };  // venus type
		if ( (plan_class != 'V') && (TEMP>340.0) )
		{
		    plan_class = 'R'; // RUNAWAY GREENHOUSE EFFECT
		    albedo = 0.0;
		}
		if ( (plan_class != 'V') && (TEMP<230.0) )
		{
		    plan_class = 'I'; // ICE BALL/ICE AGE
		    albedo = 0.95;
		}
	    }
	    else
	    {
		if ( plan_class=='G' ) { albedo = 0.5; };
	    }
	    PT = planet_temperature(AuDist, EM);
	    if (PT==TEMP) break;  // temperature converged to a steady value
	    // it is actually fairly common for Earthlike planets to have chaotic
	    // fluctuations in temperature around the freezing or boiling points;
	    // those fluctuations cause an infinite loop here.  Need to terminate
	    // the loop with a special flag if chaotic variations are discovered.
	    TEMP = PT;
	}
	surf_grav = surface_gravity(mass, radius);
	
	// other adjustments get done in System, based on neighbors
    }

    /**
     * Constructor from an accreted protoplanet.
     * @param p Protoplanet that forms the basis of this planet
     */
    public Planet(Protoplanet p)
    {
	next_planet = null;
	first_moon = null;
	a = p.a; e = p.e; mass = p.mass*SUN_MASS_IN_EARTH_MASSES;
	gas_giant = p.gas_giant;
	where_in_orbit = (nextDouble()*360.0) * DEG_TO_RAD;
	albedo = 0.0;      // start with albedo of 0
	plan_class = classify_by_accretion();
	if ( mass<1.0E-6 )
	{
	    mass = 0.0;
	    plan_class = '-';
	}
	density = density_by_temperature(plan_class);
	radius = planet_radius(mass, density, plan_class);
    }

    //
    // *** CALCULATION METHODS (SET 2)
    //

    /**
     * Calculates radius based on volume, calibrated to Earth.
     * @param mass Mass in Earth masses
     * @param density Average density in grams per cubic centimeter
     * @returns Radius in kilometers
     */
    public double volume_radius(double mass, double density)
    {
	double volume;
	
	if (density == 0.0) return 0.0;  // sometimes it happens, for grit
	mass *= EARTH_MASS_IN_GRAMS;
	volume = mass / density;
	return(Math.pow((3.0 * volume) / (4.0 * Math.PI),(1.0 / 3.0)) / CM_PER_KM);
    }

    /**
     * Calculates the equatorial radius of the planet given mass, 'zone', and
     * whether it's a gas giant or not.
     * This formula is listed as eq.9 in Fogg's article, although some typos  
     * crop up in that eq.  See "The Internal Constitution of Planets", by    
     * Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 
     * pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  
     * eq.23, which appears on page 840.
     * @param mass Mass in Earth masses
     * @param giant True if planet is a gas giant
     * @param zone Orbital zone, 1 to 3
     * @returns Equatorial radius in kilometers
     */
    public double kothari_radius(double mass, boolean giant, int zone)
    {
	double temp, temp2, atomic_weight, atomic_num;
	
	if (mass == 0.0) return 0.0;  // for grit belts (see constructor, mass_by_integration)
	
	if (zone == 1)
	{
	    if (giant)
	    {
		atomic_weight = 9.5;
		atomic_num = 4.5;
	    }
	    else 
	    {
		atomic_weight = 15.0;
		atomic_num = 8.0;
	    }
	}
	else if (zone == 2)
	{
	    if (giant)
	    {
		atomic_weight = 2.47;
		atomic_num = 2.0;
	    }
	    else 
	    {
		atomic_weight = 10.0;
		atomic_num = 5.0;
	    }
	    }
	    else 
	    {
	    if (giant)
	    {
		atomic_weight = 7.0;
		atomic_num = 4.0;
	    }
	    else 
	    {
		atomic_weight = 10.0;
		atomic_num = 5.0;
	    }
	}
	temp = atomic_weight * atomic_num;
	temp = (2.0 * BETA_20 * Math.pow(EARTH_MASS_IN_GRAMS,(1.0 / 3.0))) / (A1_20 * Math.pow(temp,(1.0 / 3.0)));
	temp2 = A2_20 * Math.pow(atomic_weight,(4.0 / 3.0)) * Math.pow(EARTH_MASS_IN_GRAMS,(2.0 / 3.0));
	temp2 = temp2 * Math.pow(mass,(2.0 / 3.0));
	temp2 = temp2 / (A1_20 * atomic_num * atomic_num);
	temp2 = 1.0 + temp2;
	temp /= temp2;
	temp *= Math.pow(mass,(1.0 / 3.0)) / CM_PER_KM;
	return (temp);
    }

    /**
     * Empirically determine density based on distance from primary.
     * @param mass Mass in Earth masses
     * @param orb_radius Semi-major axis of orbit in AU
     * @param gas_giant True if planet is a gas giant
     * @returns Density in grams per cubic centimeter
     */
    public double empirical_density(double mass, double orb_radius, boolean gas_giant)
    {
	double temp;
	
	if (mass == 0.0) return 0.0;  // for grit belts (see constructor, mass_by_integration)
	
	temp = Math.pow(mass,(1.0 / 8.0));
	temp = temp * Math.pow(r_ecosphere / orb_radius, 0.25);
	if (gas_giant)
	    return(temp * 1.2);
	else 
	    return(temp * 5.5);
    }

    /**
     * Calculates average density of body, given mass and radius.
     * @param mass Mass in Earth masses.
     * @param equat_radius Equatorial radius in kilometers.
     * @returns Average density in grams per cubic centimeter.
     */
    public double volume_density(double mass, double equat_radius)
    {
	double volume;
	
	if (equat_radius == 0.0) return 0.0;
	
	mass *= EARTH_MASS_IN_GRAMS;
	equat_radius *= CM_PER_KM;
	volume = (4.0 * Math.PI * equat_radius * equat_radius * equat_radius) / 3.0;
	return(mass / volume);
    }

    /**
     * Calculates orbital period (year) of the two bodies.
     * @param separation Distance in AU between bodies
     * @param small_mass Mass of smaller body in Solar masses
     * @param large_mass Mass of larger body in Solar masses
     * @returns Orbital period in Earth days.
     */
    public double period(double separation, double small_mass, double large_mass)
    {
	double period_in_years;
	
	period_in_years = Math.sqrt(separation*separation*separation /
				    (small_mass + large_mass));
	return(period_in_years * DAYS_IN_A_YEAR);
    }

    /**
     * Estimates length of the planet's day.
     * Fogg's information for this routine came from Dole "Habitable Planets  
     * for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    
     * up with his eq.12, which is the equation for the 'base_angular_velocity' 
     * below.  He then used an equation for the change in angular velocity per  
     * time (dw/dt) from P. Goldreich and S. Soter's paper "Q in the Solar      
     * System" in Icarus, vol 5, pp.375-389 (1966).  Using as a comparison the  
     * change in angular velocity for the Earth, Fogg has come up with an	    
     * approximation for our new Planet (his eq.13) and take that into account. 
     * This is used to find 'change_in_angular_velocity' below.
     * @param mass Mass in Earth masses.
     * @param radius Equatorial radius in kilometers.
     * @param eccentricity Eccentricity of orbit
     * @param density Average planetary density in grams per cubic centimeter
     * @param orb_radius Semi-major axis of orbit in AU
     * @param orb_period Orbital period (year) in Earth days. (???)
     * @param giant True if this planet is a gas giant
     * @returns Length of day in Earth hours.
     */
    public double day_length(
	double mass,
	double radius,
	double eccentricity,
	double density,
	double orb_radius,
	double orb_period,
	boolean giant)
    {
	double base_angular_velocity, planetary_mass_in_grams,
	    k2, ang_velocity,
	    equatorial_radius_in_cm, change_in_angular_velocity,
	    spin_resonance_factor, year_in_hours, day_in_hours;
	boolean stopped = false;
	
	resonance = 0.0;
	if (giant)
	    k2 = 0.24;
	else 
	    k2 = 0.33;
	planetary_mass_in_grams = mass * EARTH_MASS_IN_GRAMS;
	equatorial_radius_in_cm = radius * CM_PER_KM;
	day_in_hours = year_in_hours = orb_period * 24.0;
	
	if (mass == 0.0) return year_in_hours;
	if (radius == 0.0) return year_in_hours;
	
	base_angular_velocity = Math.sqrt(2.0 * J * (planetary_mass_in_grams) /
		      (k2 * equatorial_radius_in_cm*equatorial_radius_in_cm));
	//  This next calculation determines how much the Planet's rotation is
	//  slowed by the presence of the star.
	change_in_angular_velocity = CHANGE_IN_EARTH_ANG_VEL *
		      (density / EARTH_DENSITY) *
		      (equatorial_radius_in_cm / EARTH_RADIUS) *
		      (EARTH_MASS_IN_GRAMS / planetary_mass_in_grams) *
		      (stell_mass_ratio*stell_mass_ratio) *
		      (1.0 / Math.pow(orb_radius, 6.0));
	ang_velocity = base_angular_velocity + (change_in_angular_velocity * age);
	// Now we change from rad/sec to hours/rotation.			    
	if (ang_velocity <= 0.0)
	    stopped = true;
	else day_in_hours = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * ang_velocity);
	if ((day_in_hours >= year_in_hours) || stopped)
	{
	    resonance = 1.0;  // had been only w/large eccentricity, but...
	    if (eccentricity > 0.1)
	    {
		spin_resonance_factor = (1.0 - eccentricity) / (1.0 + eccentricity);
		return (spin_resonance_factor * year_in_hours);
	    }
	    else 
		return (year_in_hours);
	}
	return (day_in_hours);
    }
    
    /**
     * Estimates planetary inclination (axial tilt).  Calibrated to Earth.
     * @param orb_radius Semi-major axis of orbit in AU
     * @returns Tilt in degrees
     */
    public int inclination(double orb_radius)
    {
	int temp; 
	
	temp = (int)(Math.pow(orb_radius,0.2) * about(EARTH_AXIAL_TILT,0.4));
	return(temp % 360);
    }

    /**
     * This function implements the escape velocity calculation.  Note that   
     * it appears that Fogg's eq.15 is incorrect.
     * @param mass Mass in Earth masses.
     * @param radius Radius in kilometers.
     * @returns Escape velocity in cm/sec.
     */
    public double escape_vel(double mass, double radius)
    {
	double mass_in_grams, radius_in_cm;
    
	if (radius == 0.0) return 0.0;
    
	mass_in_grams = mass * EARTH_MASS_IN_GRAMS;
	radius_in_cm = radius * CM_PER_KM;
	return(Math.sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm));
    }

    /**
     * Calculates Root Mean Square (RMS) velocity of a molecule or atom.
     * This is Fogg's eq.16.  Calibrated to Earth exospheric temperature,
     * which implies that the orbital radius has been preadjusted so that
     * temperature comparisons are meaningful.
     * @param molecular_weight The molecular weight (usually assumed to be N2)
     *     of the molecule or atom in question.
     * @param orb_radius Semi-major axis of orbit in AU
     * @returns RMS velocity in cm/sec^2
     */
    public double rms_vel(double molecular_weight, double orb_radius)
    {
	double exospheric_temp;
	
	exospheric_temp = EARTH_EXOSPHERE_TEMP / (orb_radius*orb_radius);
	return(Math.sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) /
			 molecular_weight)
	    * CM_PER_METER);
    }

    /**
     * Calculates the smallest molecular weight retained by the    
     * body, which is useful for determining the atmosphere composition.
     * @param mass Planetary mass in Earth masses.
     * @param equat_radius Equatorial radius in kilometers.
     * @returns Molecular weight (in ???)
     */
    public double molecule_limit(double mass, double equat_radius)
    {
	double esc_velocity;
	
	esc_velocity = escape_vel(mass,equat_radius);
	if (esc_velocity == 0.0) return 0.0;
	return ((3.0 * Math.pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) *
		(MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP)) /
	       (esc_velocity*esc_velocity));
    }

    /**
     * Calculates the surface acceleration of a Planet.
     * @param mass Planetary mass in Earth masses.
     * @param radius Equatorial radius in kilometers.
     * @returns Acceleration in cm/sec^2
     */
    public double acceleration(double mass, double radius)
    {
    if (radius == 0.0) return 0.0;
    return(GRAV_CONSTANT * (mass * EARTH_MASS_IN_GRAMS) /
	    Math.pow(radius * CM_PER_KM, 2.0));
    }

    /**
     * Calculates the surface gravity of the planet.
     * @param acceleration Surface gravity in cm/sec^2
     * @returns Surface gravity in Earth gravities.
     */
    public double gravity(double acceleration)
    {
	return(acceleration / EARTH_ACCELERATION);
    }

    /**
     * Determines if the planet suffers from runaway greenhouse effect.
     * Note that if the orbital radius of the Planet is greater than or equal  
     * to R_inner, 99% of it's volatiles are assumed to have been deposited in 
     * surface reservoirs (otherwise, it suffers from the greenhouse effect).
     * @param zone Orbital 'zone'.
     * @param orb_radius Semi-major axis of orbit, in AU
     * @param r_greenhouse 'Greenhouse effect' radius in AU
     * @returns 'true' if planet is a greenhouse.
     */
    public boolean grnhouse(int zone, double orb_radius, double r_greenhouse)
    {
	if ((orb_radius < r_greenhouse) && (zone == 1))
	    return(true);
	else 
	    return(false);
    }

    /**
     * Calculates the unitless 'volatile gas inventory'.
     * This implements Fogg's eq.17.
     * @param mass Planetary mass in Earth masses.
     * @param escape_vel Escape velocity in kilometers/second.
     * @param rms_vel Average velocity at molecules at top of atmosphere.
     * @param stellar_mass Stellar mass ration in Solar masses.
     * @param zone Orbital 'zone', between 1 and 3.
     * @param greenhouse_effect True if planet has runaway greenhouse effect.
     * @returns A unitless 'inventory' calibrated to Earth=1000.
     */
    public double vol_inventory(double mass, double escape_vel, double rms_vel,
						double stellar_mass, int zone, boolean greenhouse_effect)
    {
	double velocity_ratio, proportion_const=1.0, temp1, temp2, earth_units;
	
	if (rms_vel == 0.0) return 0.0;
	velocity_ratio = escape_vel / rms_vel;
	if (velocity_ratio >= GAS_RETENTION_THRESHOLD)
	{
	    switch (zone)
	    {
	    case 1:
		proportion_const = 100000.0;
		break;
	    case 2:
		proportion_const = 75000.0;
		break;
	    case 3:
		proportion_const = 250.0;
		break;
	    default:
		System.out.println("Error: orbital zone not initialized correctly!\n");
		break;
	    }
	    earth_units = mass;
	    temp1 = (proportion_const * earth_units) / stellar_mass;
	    temp2 = about(temp1,0.2);
	    if (greenhouse_effect)
		return(temp2);
	    else 
		return(temp2 / 100.0);
	}
	else return(0.0);
    }

    /**
     * Calculates surface pressure on this planet. Uses volatile gas inventory,
     * equatorial radius, and surface gravity, and is calibrated so that Earth
     * (with a gas inventory of 1000 and gravity of 1 G) has a pressure of 1000
     * millibars. This implements Fogg's eq.18.
     * @param equat_radius Equatorial radius in kilometers.
     * @param gravity Surface gravity in units of Earth gravities.
     * @returns Surface pressure in millibars.
     */
    public double pressure(double equat_radius, double gravity)
    {
	if (equat_radius == 0.0) return 0.0;
	equat_radius = KM_EARTH_RADIUS / equat_radius;
	return (volatile_gas_inventory * gravity / (equat_radius*equat_radius));
    }

    /**
     * Calculates the boiling point of water in this planet's atmosphere,   
     * stored in millibars. This is Fogg's eq.21.
     * @returns Boiling point in degrees Kelvin.
     */
    public double boiling_point()
    {
	double surface_pressure_in_bars;
    
	surface_pressure_in_bars = surf_pressure / MILLIBARS_PER_BAR;
	if (surface_pressure_in_bars == 0) return 0.0;
	return(1.0 / (Math.log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
    }

    /**
     * Calculates the fraction of planet surface covered by water.
     * This function is Fogg's eq.22. Uses the volatile gas inventory 
     * (a dimensionless quantity, calibrated to Earth==1000) and   
     * planetary radius in Km.                             
     * I [Matt] have changed the function very slightly:  the fraction of Earth's    
     * surface covered by water is 71%, not 75% as Fogg used.                 
     */
    public double hydro_fraction()
    {
	double temp;
    
	if (radius == 0.0) return 0.0;
	temp = (0.71 * volatile_gas_inventory / 1000.0) * Math.pow(KM_EARTH_RADIUS / radius, 2.0);
	if (temp >= 1.0)
	    return(1.0);
	else 
	    return(temp);
    }

    /**
     *   Given the surface temperature of a Planet (in Kelvin), this function   
     *   returns the fraction of cloud cover available.  This is Fogg's eq.23.  
     *   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     
     *   This equation is Hart's eq.3.                                          
     *   I [Matt] have modified it slightly using constants and relationships from     
     *   Glass's book "Introduction to Planetary Geology", p.46.                
     *   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     
     *   covered by one Kg. of cloud.					    
     */
    public double cloud_fraction()
    {
	double water_vapor_in_kg, fraction, surf_area, hydro_mass;
    
	if (radius == 0.0) return 0.0;
	if (surf_pressure == 0.0) return 0.0;
	if (molec_weight > WATER_VAPOR) return(0.0);
    
	surf_area = 4.0 * PI * (radius*radius);
	hydro_mass = hydrosphere * surf_area * EARTH_WATER_MASS_PER_AREA;
	if (hydro_mass <= 0.0) return 0.0;
	// log is used to reduce chance of overflow, which had happened
	// in some previous implementations on some systems.
	water_vapor_in_kg = Math.log(0.00000001 * hydro_mass);
	water_vapor_in_kg += (Q2_36 * (surf_temp - 288.0));
	fraction = Math.log(CLOUD_COVERAGE_FACTOR) + water_vapor_in_kg - Math.log(surf_area);
	if (fraction >= 0.0)
	    return(1.0);
	else 
	    return(Math.exp(fraction));
    }

    /**
     *   Given the surface temperature of a Planet (in Kelvin), this function   
     *   returns the fraction of the Planet's surface covered by ice.  This is  
     *   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. 
     *   I [Matt] have changed a constant from 70 to 90 in order to bring it more in   
     *   line with the fraction of the Earth's surface covered with ice, which  
     *   is approximatly .016 (=1.6%).                                          
     */
    public double ice_fraction()
    {
	double temp = surf_temp; // don't change actual temperature here!
	
	if (temp > 328.0) temp = 328.0;
	temp = Math.pow(((328.0 - temp) / 90.0),5.0);
	if (temp > (1.5 * hydrosphere)) temp = (1.5 * hydrosphere);
	if (temp >= 1.0) temp=1.0;
	return(temp);
    }

    /**
     * Calculates effective temperature of the planet, based on semi-major
     * axis, albedo, and provided ecosphere radius.  The equation is calibrated
     * to the effective temperature of Earth.
     * This is Fogg's eq.19.		    
     * @param ecosphere_radius Radius of ecosphere in AU
     * @returns Effective temperature in degrees Kelvin
     */
    public double eff_temp(double ecosphere_radius)
    {
	return(Math.sqrt(ecosphere_radius / a)
	     * Math.pow((1.0 - albedo) / 0.7, 0.25)
	     * EARTH_EFFECTIVE_TEMP);
    }

    /**
     * Calculates the rise in temperature due to greenhouse effect.
     * This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     
     * Earth's Atmosphere" article.                                   
     * @param optical depth Dimensionless quantity representing atmospheric absorption
     * @param effective_temp Temperature in Kelvin of a blackbody here
     * @returns Temperature rise in degrees Kelvin
     */
    public double green_rise(double optical_depth, double effective_temp)
    {
	double convection_factor;
    
	convection_factor = EARTH_CONVECTION_FACTOR * Math.pow(surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS, 0.25);
	return(Math.pow(1.0 + 0.75 * optical_depth, 0.25) - 1.0) * effective_temp * convection_factor;
    }

    /**
     *   Calculates the albedo of the planet, which is the fraction of light
     *   reflected rather than absorbed.
     *   The cloud adjustment is the fraction of cloud cover obscuring each     
     *   of the three major components of albedo that lie below the clouds.     
     */
    public double planet_albedo()
    {
	double water_fraction = hydrosphere;
	double cloud_fraction = cloud_cover;
	double ice_fraction = ice_cover;
	double rock_fraction, cloud_adjustment, components, cloud_part, rock_part, water_part, ice_part;
    
	rock_fraction = (1.0 - water_fraction - ice_fraction);
	components = 0.0;
	if (water_fraction > 0.0) components += 1.0;
	if (ice_fraction > 0.0) components += 1.0;
	if (rock_fraction > 0.0) components += 1.0;
	cloud_adjustment = cloud_fraction / components;
	if (rock_fraction >= cloud_adjustment) rock_fraction -= cloud_adjustment;
	else rock_fraction = 0.0;
	if (water_fraction > cloud_adjustment) water_fraction -= cloud_adjustment;
	else water_fraction = 0.0;
	if (ice_fraction > cloud_adjustment) ice_fraction -= cloud_adjustment;
	else ice_fraction = 0.0;
	cloud_part = cloud_fraction * about(CLOUD_ALBEDO,0.2);
	rock_part = rock_fraction * 
	((surf_pressure == 0.0) ? about(ROCKY_AIRLESS_ALBEDO,0.3) : about(ROCKY_ALBEDO,0.1));
	water_part = water_fraction * about(WATER_ALBEDO,0.2);
	ice_part = ice_fraction * 
	    ((surf_pressure == 0.0) ? about(AIRLESS_ICE_ALBEDO,0.4) : about(ICE_ALBEDO,0.1));
	return(cloud_part + rock_part + water_part + ice_part);
    }

    /**
     * Calculates the albedo of the planet, which is the fraction of light
     * reflected rather than absorbed.  This routine expects the albedo
     * contribution for each of the components to be precalculated rather
     * than randomly varied on each call; this is to accellerate execution
     * of the planetary temperature loop.</p>
     * The cloud adjustment is the fraction of cloud cover obscuring each     
     * of the three major components of albedo that lie below the clouds.     
     * We assume that each surface component is obscured to an equal degree.
     */
    public double new_planet_albedo()
    {
	double water_fraction = hydrosphere;
	double cloud_fraction = cloud_cover;
	double ice_fraction = ice_cover;
	double rock_fraction, cloud_adjustment, components, cloud_part, rock_part, water_part, ice_part;
	double rock_adjustment, water_adjustment, ice_adjustment;
	double result;
	
	rock_fraction = 1.0 - water_fraction - ice_fraction;
	if (rock_fraction < 0.0) rock_fraction = 0.0;
	rock_adjustment = cloud_fraction * rock_fraction;
	water_adjustment = cloud_fraction * water_fraction;
	ice_adjustment = cloud_fraction * ice_fraction;
	rock_fraction = (rock_fraction >= rock_adjustment) ? (rock_fraction - rock_adjustment) : 0.0;
	water_fraction = (water_fraction >= water_adjustment) ? (water_fraction - water_adjustment) : 0.0;
	ice_fraction = (ice_fraction >= ice_adjustment) ? (ice_fraction - ice_adjustment) : 0.0;
	cloud_part = cloud_fraction * cloud_factor;
	rock_part = rock_fraction * ((surf_pressure == 0.0) ? airless_rock_factor : rock_factor);
	ice_part = ice_fraction * ((surf_pressure == 0.0) ? airless_ice_factor : ice_factor);
	water_part = water_fraction * water_factor;
	result = (cloud_part + rock_part + water_part + ice_part);
	if (result < 0.0) result = 0.0;
	return result;
    }

    /**
     *   This function returns the dimensionless quantity of optical depth,     
     *   which is useful in determining the amount of greenhouse effect on a    
     *   Planet.                                                                
     */
    public double opacity()
    {
	double optical_depth = 0.0;
	double molecular_weight = molec_weight;
	if ((molecular_weight > 0.0) && (molecular_weight < 10.0)) optical_depth += 3.0;
	if ((molecular_weight >= 10.0) && (molecular_weight < 20.0)) optical_depth += 2.34;
	if ((molecular_weight >= 20.0) && (molecular_weight < 30.0)) optical_depth += 1.0;
	if ((molecular_weight >= 30.0) && (molecular_weight < 45.0)) optical_depth += 0.15;
	if ((molecular_weight >= 45.0) && (molecular_weight < 100.0)) optical_depth += 0.05;
	if (surf_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 8.333;
	else if (surf_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 6.666;
	else if (surf_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 3.333;
	else if (surf_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 2.0;
	else if (surf_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 1.5;
	return(optical_depth);
    }

    static protected final int CHAOTIC_ITERATIONS = 100;
    /**
     * Iteratively calculates the temperature of the atmosphere.
     * For most planets, this iteration terminates very quickly, but for
     * some planets the state is chaotic.  Typically, at least one planet
     * will be discovered within a few hundred systems for which this
     * equation <em>never</em> converges. These are primarily Earthlike planets
     * where surface temperature is near the freezing point of water,
     * but it has also occurred in planets near the boiling point as well
     * (typically high pressure worlds with large oceans).  Adjust the
     * CHAOTIC_ITERATIONS parameter to change the cutoff point.
     * <p>It may be desirable to iteratively calculate the volatiles inventory
     * as well, to simulate atmospheric evolution; doing this <em>correctly</em>
     * is beyond what I [Carl] feel comfortable with.
     */
    public void iterate_surface_temp()
    {
	double effective_temp, greenhs_rise, previous_temp;
	double total_temp;
    
	// albedo factors; declared constant for each planet
	cloud_factor = about(CLOUD_ALBEDO,0.2);
	airless_rock_factor = about(ROCKY_AIRLESS_ALBEDO,0.3);
	rock_factor = about(ROCKY_ALBEDO,0.1);
	water_factor = about(WATER_ALBEDO,0.2);
	airless_ice_factor = about(AIRLESS_ICE_ALBEDO,0.4);
	ice_factor = about(ICE_ALBEDO,0.1);
    
	its = 0;
	temp_unstable = false;
	albedo = EARTH_ALBEDO;
	effective_temp = eff_temp(r_ecosphere);
	greenhs_rise = green_rise(opacity(),effective_temp);
	surf_temp = effective_temp + greenhs_rise;
	total_temp = surf_temp;
	previous_temp = surf_temp - 5.0;		// force the while loop the first time 
	while ((Math.abs(surf_temp - previous_temp) > 1.0))
	{
	    previous_temp = surf_temp;
	    hydrosphere = hydro_fraction();
	    cloud_cover = cloud_fraction();
	    ice_cover = ice_fraction();
	    if ((surf_temp >= boil_point) || (surf_temp <= FREEZING_POINT_OF_WATER))
		hydrosphere = 0.0;
	    albedo = new_planet_albedo();
	    effective_temp = eff_temp(r_ecosphere);
	    greenhs_rise = green_rise(opacity(),effective_temp);
	    surf_temp = effective_temp + greenhs_rise;
	    if (its == 0)
	    {
		min_temp = surf_temp;
		max_temp = surf_temp;
	    }
	    if (surf_temp < min_temp) min_temp = surf_temp;
	    if (surf_temp > max_temp) max_temp = surf_temp;
	    its++;
	    total_temp += surf_temp;
	    if (its > CHAOTIC_ITERATIONS)
	    {
		temp_unstable = true;
		break;  // abandon search here; declare unstable
	    }
	}
	avg_temp = total_temp / ((double)(its+1));
    }

    /**
     * Calculates planetary characteristics. At this point the body
     * of the planet has already been calculated (mass, orbital characteristics,
     * whether it accreted gas as well as dust); remaining characteristics
     * are calculated using stellar characteristics provided as parameters.
     * @param smr Stellar mass ratio (in Solar masses)
     * @param r_gr Greenhouse radius (in AU)
     * @param r_ec Ecosphere radius (in AU)
     * @param age Age of star (in gigayears)
     */
    public void set_vital_stats(double smr, double r_gr, double r_ec, double age)
    {
	r_ecosphere = r_ec;
	stell_mass_ratio = smr;
	age = a;
	resonance = 0.0;
	
	if (gas_giant)
	{
	    density = empirical_density(mass,a,gas_giant);
	    radius = volume_radius(mass,density);
	}
	else 
	{
	    radius = kothari_radius(mass,gas_giant,orbit_zone);
	    density = volume_density(mass,radius);
	}
	orb_period = period(a,mass/SUN_MASS_IN_EARTH_MASSES,smr);
	day = day_length(mass,radius,e,density,a,orb_period,gas_giant);
	resonant_period = (int)resonance;
	axial_tilt = inclination(a);
	esc_velocity = escape_vel(mass,radius);
	surf_accel = acceleration(mass,radius);
	rms_velocity = rms_vel(MOL_NITROGEN,a);
	molec_weight = molecule_limit(mass,radius);
	if ((gas_giant))
	{
	    surf_grav = INCREDIBLY_LARGE_NUMBER;
	    greenhouse_effect = false;
	    volatile_gas_inventory = INCREDIBLY_LARGE_NUMBER;
	    surf_pressure = INCREDIBLY_LARGE_NUMBER;
	    boil_point = INCREDIBLY_LARGE_NUMBER;
	    hydrosphere = INCREDIBLY_LARGE_NUMBER;
	    albedo = about(GAS_GIANT_ALBEDO,0.1);
	    surf_temp = INCREDIBLY_LARGE_NUMBER;
	}
	else 
	{
	    surf_grav = gravity(surf_accel);
	    greenhouse_effect = grnhouse(orbit_zone,a,r_gr);
	    volatile_gas_inventory = vol_inventory(mass,esc_velocity,rms_velocity,smr,orbit_zone,greenhouse_effect);
	    surf_pressure = pressure(radius,surf_grav);
	    // sometimes airless rocks are showing a greenhouse effect;
	    // remove that effect if the rock has very little air.
	    if (surf_pressure < 0.01) greenhouse_effect = false;
	    boil_point = (surf_pressure == 0.0) ? 0.0 : boiling_point();
	    iterate_surface_temp();
	}
    }

    /**
     * Calculates distance to closest moon, if any.  I {Carl] am unsure
     * about the logic behind this routine, and it is currently unused.
     * It might be related to the size of the Roche lobes of this planet,
     * but I don't have the time right now to check it.
     * @returns Distance in AU
     */
    public double nearest_moon()
    {
	return(0.3/40.0 * Math.pow(mass/SUN_MASS_IN_EARTH_MASSES,(1.0 / 3.0)));
    }

    /**
     * Calculates distance to farthest moon, if any.  I {Carl] am unsure
     * about the logic behind this routine, and it is currently unused.
     * It might be related to the size of the accretion disk around this planet.
     * @returns Distance in AU
     */
    public double farthest_moon()
    {
	return(50.0/40.0 * Math.pow(mass/SUN_MASS_IN_EARTH_MASSES,(1.0 / 3.0)));
    }
}

