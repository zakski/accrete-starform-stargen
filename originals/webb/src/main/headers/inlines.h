/*--------------------------------------------------------------------------*/
/*   This function calculates the surface acceleration of a planet.  The    */
/*  mass is in units of solar masses, the radius in terms of km, and the    */
/*  acceleration is returned in units of cm/sec2.                           */
/*--------------------------------------------------------------------------*/
inline double acceleration(double mass, double radius)
{
	  return(GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / pow(radius * CM_PER_KM, 2.0));
}

/*--------------------------------------------------------------------------*/
/*   This function calculates the surface gravity of a planet.  The         */
/*  acceleration is in units of cm/sec2, and the gravity is returned in     */
/*  units of Earth gravities.                                               */
/*--------------------------------------------------------------------------*/
inline double gravity(double acceleration)
{
	  return(acceleration / EARTH_ACCELERATION);
}

/*--------------------------------------------------------------------------*/
/*  Note that if the orbital radius of the planet is greater than or equal  */
/*  to R_inner, 99% of it's volatiles are assumed to have been deposited in */
/*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
/*--------------------------------------------------------------------------*/
inline int greenhouse(int zone, double orbital_radius, double greenhouse_radius)
{
	return ((orbital_radius < greenhouse_radius) && (zone == 1));
}

inline double stellar_dust_limit(double stellar_mass_ratio)
{
	  return(200.0 * pow(stellar_mass_ratio,(1.0 / 3.0)));
}

inline double luminosity(double mass_ratio)
{
//	double n;
	double n = (mass_ratio < 1.0) ? (1.75 * (mass_ratio - 0.1) + 3.325) : (0.5 * (2.0 - mass_ratio) + 4.4);

//	if (mass_ratio < 1.0)
//		n = 1.75 * (mass_ratio - 0.1) + 3.325;
//	else
//		n = 0.5 * (2.0 - mass_ratio) + 4.4;

	return(pow(mass_ratio,n));
}


/*--------------------------------------------------------------------------*/
/*   The mass is in units of solar masses, and the density is in units      */
/*   of grams/cc.  The radius returned is in units of km.                   */
/*--------------------------------------------------------------------------*/
inline double volume_radius(double mass, double density)
{
//	double volume = mass * SOLAR_MASS_IN_GRAMS / density;

//	mass = mass * SOLAR_MASS_IN_GRAMS;
//	volume = mass * SOLAR_MASS_IN_GRAMS / density;
	return(pow((3.0 * mass * SOLAR_MASS_IN_GRAMS / density) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
//	return(pow((3.0 * volume) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/
inline double volume_density(double mass, double equatorial_radius)
{
//	double volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;

//	mass = mass * SOLAR_MASS_IN_GRAMS;
//	equatorial_radius = equatorial_radius * CM_PER_KM;
//	volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;
	return(mass*SOLAR_MASS_IN_GRAMS / ((4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0));
}


/*--------------------------------------------------------------------------*/
/*   The orbital radius is expected in units of Astronomical Units (AU).    */
/*   Inclination is returned in units of degrees.                           */
/*--------------------------------------------------------------------------*/
inline int inclination(double orbital_radius)
{
//	int temp;

//	temp = (int)(pow(orbital_radius,0.2) * about(EARTH_AXIAL_TILT,0.4));
	return(((int)(pow(orbital_radius,0.2) * about(EARTH_AXIAL_TILT,0.4))) % 360);
}


/*--------------------------------------------------------------------------*/
/*   This function implements the escape velocity calculation.  Note that   */
/*  it appears that Fogg's eq.15 is incorrect.                              */
/*  The mass is in units of solar mass, the radius in kilometers, and the   */
/*  velocity returned is in cm/sec.                                         */
/*--------------------------------------------------------------------------*/
inline double escape_vel(double mass, double radius)
{
//	double
//		mass_in_grams = mass * SOLAR_MASS_IN_GRAMS,
//		radius_in_cm = radius * CM_PER_KM;

//	mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
//	radius_in_cm = radius * CM_PER_KM;

	return(sqrt(2.0 * GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / (radius * CM_PER_KM)));
//	return(sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm));
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.16.  The molecular weight (usually assumed to be N2)  */
/*  is used as the basis of the Root Mean Square velocity of the molecule   */
/*  or atom.  The velocity returned is in cm/sec.                           */
/*--------------------------------------------------------------------------*/
inline double rms_vel(double molecular_weight, double orbital_radius)
{
//	double
//		exospheric_temp= EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0);

//	exospheric_temp = EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0);
	return(sqrt((3.0 * MOLAR_GAS_CONST * (EARTH_EXOSPHERE_TEMP / pow(orbital_radius, 2.0))) / molecular_weight) * CM_PER_METER);
//	return(sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight) * CM_PER_METER);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the smallest molecular weight retained by the    */
/*  body, which is useful for determining the atmosphere composition.       */
/*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  */
/*  mass is in units of solar masses, and equatorial radius is in units of  */
/*  kilometers.                                                             */
/*--------------------------------------------------------------------------*/
inline double molecule_limit(double /*orbital_radius*/, double mass, double equatorial_radius)
{
//	double
//		numerator,
//		denominator1,
//		denominator2,
//		temp,
//		escape_velocity = escape_vel(mass,equatorial_radius);

//	escape_velocity = escape_vel(mass,equatorial_radius);
	return((3.0 * pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow(escape_vel(mass,equatorial_radius), 2.0));
//	return((3.0 * pow(GAS_RETENTION_THRESHOLD * CM_PER_METER, 2.0) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow(escape_velocity, 2.0));
}


/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.18.  The pressure returned is in units of     */
/*  millibars (mb).  The gravity is in units of Earth gravities, the radius */
/*  in units of kilometers.                                                 */
/*--------------------------------------------------------------------------*/
inline double pressure(double volatile_gas_inventory, double equatorial_radius, double gravity)
{
//	equatorial_radius = EARTH_RADIUS_IN_KM / equatorial_radius;
	return(volatile_gas_inventory * gravity / pow(EARTH_RADIUS_IN_KM/equatorial_radius, 2.0));
}


/*--------------------------------------------------------------------------*/
/*   This function returns the boiling point of water in an atmosphere of   */
/*   pressure 'surface_pressure', given in millibars.  The boiling point is */
/*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
/*--------------------------------------------------------------------------*/
inline double boiling_point(double surface_pressure)
{
//	double
//		surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;

//	surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;
	return(1.0 / (log(surface_pressure / MILLIBARS_PER_BAR) / -5050.5 + 1.0 / 373.0));
//	return(1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
}


/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital */
/*  radius in AU, and the temperature returned is in Kelvin.		    */
/*--------------------------------------------------------------------------*/
inline double eff_temp(double ecosphere_radius, double orbital_radius, double albedo)
{
	  return(sqrt(ecosphere_radius / orbital_radius) * pow((1.0 - albedo) / 0.7,0.25) * EARTH_EFFECTIVE_TEMP);
}
/*--------------------------------------------------------------------------*/
/*   This function is Fogg's eq.22.  Given the volatile gas inventory and   */
/*   planetary radius of a planet (in Km), this function returns the        */
/*   fraction of the planet covered with water.                             */
/*   I have changed the function very slightly:  the fraction of Earth's    */
/*   surface covered by water is 71%, not 75% as Fogg used.                 */
/*--------------------------------------------------------------------------*/
inline double hydrosphere_fraction(double volatile_gas_inventory, double planetary_radius)
{
	double temp = (0.71 * volatile_gas_inventory / 1000.0) * pow(EARTH_RADIUS_IN_KM / planetary_radius, 2.0);

//	temp = (0.71 * volatile_gas_inventory / 1000.0) * pow(EARTH_RADIUS_IN_KM / planetary_radius, 2.0);

	return (temp>=1.0) ? 1.0 : temp;
//	if (temp >= 1.0)
//		return(1.0);
//	else
//	  return(temp);
}

/*--------------------------------------------------------------------------*/
/*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
/*  Earth's Atmosphere" article.  The effective temperature given is in     */
/*  units of Kelvin, as is the rise in temperature produced by the          */
/*  greenhouse effect, which is returned.                                   */
/*--------------------------------------------------------------------------*/
inline double green_rise(double optical_depth, double effective_temp, double surface_pressure)
{
//	double
//		convection_factor = EARTH_CONVECTION_FACTOR * pow((surface_pressure / EARTH_SURF_PRES_IN_MILLIBARS),0.25);

//	  convection_factor = EARTH_CONVECTION_FACTOR * pow((surface_pressure / EARTH_SURF_PRES_IN_MILLIBARS),0.25);
	return(pow((1.0 + 0.75 * optical_depth),0.25) - 1.0) * effective_temp * EARTH_CONVECTION_FACTOR * pow((surface_pressure / EARTH_SURF_PRES_IN_MILLIBARS),0.25);
//	return(pow((1.0 + 0.75 * optical_depth),0.25) - 1.0) * effective_temp * convection_factor;
}


/*--------------------------------------------------------------------------*/
/*   The mass is in units of solar masses, and the density is in units      */
/*   of grams/cc.  The radius returned is in units of km.                   */
/*--------------------------------------------------------------------------*/
inline double planets::volumeRadius(void)
{
	return(pow((3.0 * mass * SOLAR_MASS_IN_GRAMS / density) / (4.0 * PI),(1.0 / 3.0)) / CM_PER_KM);
}

