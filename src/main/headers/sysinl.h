inline double innermost_planet(double stellar_mass_ratio)
{
	  return(0.3 * pow(stellar_mass_ratio,(1.0 / 3.0)));
}

inline double outermost_planet(double stellar_mass_ratio)
{
	  return(50.0 * pow(stellar_mass_ratio,(1.0 / 3.0)));
}

inline double starSystem::inner_effect_limit(double a, double e, double mass)
{
	return (a * (1.0 - e) * (1.0 - mass) / (1.0 + cloudEccentricity));
}

inline double starSystem::outer_effect_limit(double a, double e, double mass)
{
// Suspected incorrect use of this value:  reduced_mass is undefined at the time
// it is used in distribute_planetary_masses
//	return (a * (1.0 + e) * (1.0 + reduced_mass) / (1.0 - cloud_eccentricity));
	return (a * (1.0 + e) * (1.0 + mass) / (1.0 - cloudEccentricity));
}

inline double random_eccentricity (void)
{
	  return(1.0 - pow(random_number(0.0, 1.0),ECCENTRICITY_COEFF));
}
