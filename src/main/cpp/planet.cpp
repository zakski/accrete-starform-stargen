// PLANET.CPP, by Christopher Webb
// Contains code for struct planets
#include <math.h>
#include <stdio.h>

#include "system.h"
const double radians_per_rotation=2.0*PI;

#include "inlines.h"

/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  */
/*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     */
/*   This equation is Hart's eq.3.                                          */
/*   I have modified it slightly using constants and relationships from     */
/*   Glass's book "Introduction to Planetary Geology", p.46.                */
/*   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     */
/*   covered by one Kg. of cloud.					    */
/*--------------------------------------------------------------------------*/
double cloud_fraction(double surface_temp, double smallest_MW_retained,
	double equatorial_radius, double hydrosphere_fraction)
{
	if (smallest_MW_retained > WATER_VAPOR)
		return(0.0);
	else
	{
		double
			water_vapor_in_kg,
			fraction,
			surface_area = 4.0 * PI * pow(equatorial_radius, 2.0),
			hydrosphere_mass = hydrosphere_fraction * surface_area * EARTH_WATER_MASS_PER_AREA;

//		surface_area = 4.0 * PI * pow(equatorial_radius, 2.0);
//		hydrosphere_mass = hydrosphere_fraction * surface_area * EARTH_WATER_MASS_PER_AREA;
		water_vapor_in_kg = (0.00000001 * hydrosphere_mass) * exp(Q2_36 * (surface_temp - 288.0));
		fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surface_area;

		return (fraction>=1.0) ? 1.0 : fraction;
//		if (fraction >= 1.0)
//			return(1.0);
//		else
//			return(fraction);
	}
}


/*--------------------------------------------------------------------------*/
/*   Given the surface temperature of a planet (in Kelvin), this function   */
/*   returns the fraction of the planet's surface covered by ice.  This is  */
/*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. */
/*   I have changed a constant from 70 to 90 in order to bring it more in   */
/*   line with the fraction of the Earth's surface covered with ice, which  */
/*   is approximatly .016 (=1.6%).                                          */
/*--------------------------------------------------------------------------*/
double ice_fraction(double hydrosphere_fraction, double surface_temp)
{
	double temp = pow(((328.0 - min(328.0,surface_temp)) / 90.0),5.0);

//	if (surface_temp > 328.0)
//		surface_temp = 328.0;

//	temp = pow(((328.0 - surface_temp) / 90.0),5.0);
	if (temp > (1.5 * hydrosphere_fraction))
		temp = (1.5 * hydrosphere_fraction);

	return (temp>=1.0) ? 1.0 : temp;
//	if (temp >= 1.0)
//		return(1.0);
//	else
//		return(temp);
}


/*--------------------------------------------------------------------------*/
/*   The surface temperature passed in is in units of Kelvin.               */
/*   The cloud adjustment is the fraction of cloud cover obscuring each     */
/*   of the three major components of albedo that lie below the clouds.     */
/*--------------------------------------------------------------------------*/
double planet_albedo(double water_fraction, double cloud_fraction,
	double ice_fraction, double surface_pressure)
{
	double
		rock_fraction = 1.0 - water_fraction - ice_fraction,
		cloud_adjustment,
		components,
		cloud_contribution,
		rock_contribution,
		water_contribution,
		ice_contribution;

	components=1.0*(water_fraction>0.0)+1.0*(ice_fraction>0.0)+1.0*(rock_fraction>0.0);

	cloud_adjustment = cloud_fraction / components;

	if (rock_fraction >= cloud_adjustment)
		rock_fraction = rock_fraction - cloud_adjustment;
	else
		rock_fraction = 0.0;

	if (water_fraction > cloud_adjustment)
		water_fraction = water_fraction - cloud_adjustment;
	else
		water_fraction = 0.0;

	if (ice_fraction > cloud_adjustment)
		ice_fraction = ice_fraction - cloud_adjustment;
	else
		ice_fraction = 0.0;

	cloud_contribution = cloud_fraction * about(CLOUD_ALBEDO,0.2);

	if (surface_pressure == 0.0)
		rock_contribution = rock_fraction * about(AIRLESS_ROCKY_ALBEDO,0.3);
	else
		rock_contribution = rock_fraction * about(ROCKY_ALBEDO,0.1);

	water_contribution = water_fraction * about(WATER_ALBEDO,0.2);

	if (surface_pressure == 0.0)
		ice_contribution = ice_fraction * about(AIRLESS_ICE_ALBEDO,0.4);
	else
		ice_contribution = ice_fraction * about(ICE_ALBEDO,0.1);

	return(cloud_contribution + rock_contribution + water_contribution + ice_contribution);
}


/*--------------------------------------------------------------------------*/
/*   This function returns the dimensionless quantity of optical depth,     */
/*   which is useful in determining the amount of greenhouse effect on a    */
/*   planet.                                                                */
/*--------------------------------------------------------------------------*/
double planets::opacity(void)
{
	double optical_depth=0.0;

	if ((minMoleculeWeight >= 0.0) && (minMoleculeWeight < 10.0)) optical_depth += 3.0;

	if ((minMoleculeWeight >= 10.0) && (minMoleculeWeight < 20.0)) optical_depth += 2.34;

	if ((minMoleculeWeight >= 20.0) && (minMoleculeWeight < 30.0)) optical_depth += 1.0;

	if ((minMoleculeWeight >= 30.0) && (minMoleculeWeight < 45.0)) optical_depth += 0.15;

	if ((minMoleculeWeight >= 45.0) && (minMoleculeWeight < 100.0)) optical_depth += 0.05;

	if (surfacePressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 8.333;
	else
		if (surfacePressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 6.666;
		else
			if (surfacePressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 3.333;
			else
				if (surfacePressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 2.0;
				else
					if (surfacePressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS)) optical_depth *= 1.5;

	return(optical_depth);
}


/*--------------------------------------------------------------------------*/
/*  This implements Fogg's eq.17.  The 'inventory' returned is unitless.    */
/*--------------------------------------------------------------------------*/
//double vol_inventory(double mass, double escape_vel, double rms_vel,
//	double stellar_mass, int zone, int greenhouse_effect)
double planets::volInventory(double stellar_mass)
{
	double
		proportion_const,
		temp1,
		temp2,
		mass_in_earth_units;

	if (escapeVelocity / RMSvelocity >= GAS_RETENTION_THRESHOLD)
	{
		switch (orbitalZone)
		{
			case 1:
//			proportion_const = 10000.0;
			proportion_const = 100000.0;
			break;
			case 2:
//			proportion_const = 7500.0;
			proportion_const = 75000.0;
			break;
			case 3:
			proportion_const = 250.0;
			break;
			default:
			printf("Error: orbital zone not initialized correctly!\n");
			break;
		}
		mass_in_earth_units = mass * EARTH_MASSES_PER_SOLAR_MASS;
		temp1 = (proportion_const * mass_in_earth_units) / stellar_mass;
		temp2 = about(temp1,0.2);

		return (isGreenhouseEffect) ? temp2 : (temp2/100.0);
	}
	else
		return(0.0);
}


/*--------------------------------------------------------------------------*/
/*   Fogg's information for this routine came from Dole "Habitable Planets  */
/* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    */
/* up with his eq.12, which is the equation for the base_angular_velocity   */
/* below.  Going a bit further, he found an equation for the change in      */
/* angular velocity per time (dw/dt) from P. Goldreich and S. Soter's paper */
/* "Q in the Solar System" in Icarus, vol 5, pp.375-389 (1966).  Comparing  */
/* to the change in angular velocity for the Earth, we can come up with an  */
/* approximation for our new planet (his eq.13) and take that into account. */
/*--------------------------------------------------------------------------*/
double planets::dayLength(int &spin_resonance, double age)
{
	double
		base_angular_velocity,
		planetary_mass_in_grams=mass * SOLAR_MASS_IN_GRAMS,
		k2=(isGasGiant) ? .24 : .33,
		temp,
		equatorial_radius_in_cm= radius * CM_PER_KM,
		change_in_angular_velocity,
		spin_resonance_period;

	spin_resonance = FALSE;
	base_angular_velocity = sqrt(2.0 * J * (planetary_mass_in_grams) / (k2 * pow(equatorial_radius_in_cm, 2.0)));

	//   This next term describes how much a planet's rotation is slowed by
	//  it's moons.  Find out what dw/dt is after figuring out Goldreich and
	//  Soter's Q'.
	change_in_angular_velocity = 0.0;
	temp = base_angular_velocity + (change_in_angular_velocity * age);

	//   'temp' is now the angular velocity. Now we change from rad/sec to
	//  hours/rotation.
	temp = 1.0 / ((temp / radians_per_rotation) * SECONDS_PER_HOUR);
	if (temp >= orbitalPeriod*24.0)
	{
		spin_resonance_period = ((1.0 - eccentricity) / (1.0 + eccentricity)) * 24.0* orbitalPeriod;
		if (eccentricity > 0.1)
		{
			temp = spin_resonance_period;
			spin_resonance = TRUE;
		}
		else
			temp = orbitalPeriod*24.0;
	}

	return(temp);
}


/*--------------------------------------------------------------------------*/
/*   This function, given the orbital radius of a planet in AU, returns     */
/*   the orbital 'zone' of the particle.                                    */
/*--------------------------------------------------------------------------*/
int orbital_zone(double orbital_radius, double starLuminosity)
{
	if (orbital_radius < (4.0 * sqrt(starLuminosity)))
		return(1);
	else
	{
		return ((orbital_radius >= (4.0 * sqrt(starLuminosity))) && (orbital_radius < (15.0 * sqrt(starLuminosity))))
			? 2 : 3;
	}
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the orbital radius  */
/*  is in units of AU.  The density is returned in units of grams/cc.       */
/*--------------------------------------------------------------------------*/
double planets::empiricalDensity(double rEcosphere)
{
	double temp=pow(mass * EARTH_MASSES_PER_SOLAR_MASS,(1.0 / 8.0)) * pow(rEcosphere / axis,(1.0 / 4.0));
//	temp = pow(mass * EARTH_MASSES_PER_SOLAR_MASS,(1.0 / 8.0));
//	temp = temp * pow(r_ecosphere / orbital_radius,(1.0 / 4.0));

	return (isGasGiant) ? (temp*1.2) : (temp*5.5);
}


/*--------------------------------------------------------------------------*/
/*    Returns the radius of the planet in kilometers.                       */
/*   The mass passed in is in units of solar masses, the orbital radius     */
/*   in A.U.                                                                */
/*   This formula is listed as eq.9 in Fogg's article, although some typos  */
/*   crop up in that eq.  See "The Internal Constitution of Planets", by    */
/*   Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 */
/*   pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  */
/*   eq.23, which appears on page 840.                                      */
/*--------------------------------------------------------------------------*/
double planets::kothariRadius(void)
{
	double
		temp, temp2, atomic_weight, atomic_num;

	switch(orbitalZone)
	{
		case 1:
			atomic_weight = (isGasGiant) ? 9.5 : 15.0;
			atomic_num = (isGasGiant) ? 4.5 : 8.0;
			break;
		case 2:
			atomic_weight = (isGasGiant) ? 2.47 : 10.0;
			atomic_num = (isGasGiant) ? 2.0 : 5.0;
			break;
		case 3:
			atomic_weight = (isGasGiant) ? 7.0 : 10.0;
			atomic_num = (isGasGiant) ? 4.0 : 5.0;
			break;
	};
//	  temp = atomic_weight * atomic_num;
//	  temp = (2.0 * BETA_20 * pow(SOLAR_MASS_IN_GRAMS,(1.0 / 3.0))) / (A1_20 * pow(temp,(1.0 / 3.0)));
	temp = (2.0 * BETA_20 * pow(SOLAR_MASS_IN_GRAMS,(1.0 / 3.0))) / (A1_20 * pow(atomic_weight * atomic_num,(1.0 / 3.0)));
//	  temp2 = A2_20 * pow(atomic_weight,(4.0 / 3.0)) * pow(SOLAR_MASS_IN_GRAMS,(2.0 / 3.0));
//	  temp2 = temp2 * pow(mass,(2.0 / 3.0));
//	  temp2 = temp2 / (A1_20 * pow(atomic_num, 2.0));
//	  temp2 = 1.0 + temp2;
	temp2 = 1.0 + (A2_20 * pow(atomic_weight,(4.0 / 3.0)) * pow(SOLAR_MASS_IN_GRAMS,(2.0 / 3.0)) * pow(mass,(2.0 / 3.0))) / (A1_20 * pow(atomic_num, 2.0));
//	  temp2 = temp2 * pow(mass,(2.0 / 3.0));
//	  temp2 = temp2 / (A1_20 * pow(atomic_num, 2.0));
//	  temp2 = 1.0 + temp2;
//	  temp = temp / temp2;
//	  temp = (temp / temp2 * pow(mass,(1.0 / 3.0))) / CM_PER_KM;
//	  return(temp);
	return ((temp / temp2 * pow(mass,(1.0 / 3.0))) / CM_PER_KM);
}


/*--------------------------------------------------------------------------*/
/*  The mass passed in is in units of solar masses, and the equatorial      */
/*  radius is in km.  The density is returned in units of grams/cc.         */
/*--------------------------------------------------------------------------*/
double planets::volumeDensity()
{
//	double volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;

//	mass = mass * SOLAR_MASS_IN_GRAMS;
//	equatorial_radius = equatorial_radius * CM_PER_KM;
//	volume = (4.0 * PI * pow(CM_PER_KM*equatorial_radius,3.0)) / 3.0;
	return(mass*SOLAR_MASS_IN_GRAMS / ((4.0 * PI * pow(CM_PER_KM*radius,3.0)) / 3.0));
}


void planets::buildPlanet(double starMass, double starLuminosity, double rEcosphere,double rGreenhouse, double age)
{
	int spin_resonance;

	orbitalZone = orbital_zone(axis, starLuminosity);

	if (isGasGiant)
	{
		density = empiricalDensity(rEcosphere);
		radius = volumeRadius();
		if(radius>80000.0) isGasGiant++; // Based on MT's World Tamers HB
		if(mass>0.02) isGasGiant++; // assume Brown Dwarfs > 0.02M(Sol)
	}
	else
	{
		radius = kothariRadius();
		density = volumeDensity();
	}

	orbitalPeriod = period(axis,mass,starMass);
	day = dayLength(spin_resonance,age);

	isResonantPeriod = spin_resonance;
	axialTilt = inclination(axis);
	escapeVelocity = escape_vel(mass,radius);
	surfaceAccel = acceleration(mass,radius);
	RMSvelocity = rms_vel(MOLECULAR_NITROGEN,axis);
	minMoleculeWeight = molecule_limit(axis,mass,radius);

	if ((isGasGiant))
	{
		surfaceGrav = INCREDIBLY_LARGE_NUMBER;
		isGreenhouseEffect = FALSE;
		volatileGasInventory = INCREDIBLY_LARGE_NUMBER;
		surfacePressure = INCREDIBLY_LARGE_NUMBER;
		boilPoint = INCREDIBLY_LARGE_NUMBER;
		hydrosphere = INCREDIBLY_LARGE_NUMBER;
		albedo = about(GAS_GIANT_ALBEDO,0.1);
		surfaceTemp = INCREDIBLY_LARGE_NUMBER;
		isPlanetoid=FALSE;
	}
	else
	{
		isPlanetoid=(radius<800.0);
		surfaceGrav = gravity(surfaceAccel);
		isGreenhouseEffect = greenhouse(orbitalZone,axis,rGreenhouse);
		volatileGasInventory = volInventory(starMass);
//		volatileGasInventory = vol_inventory(mass,escapeVelocity,RMSvelocity,starMass,orbitalZone,isGreenhouseEffect);
		surfacePressure = pressure(volatileGasInventory,radius,surfaceGrav);

		if ((surfacePressure == 0.0))
			boilPoint = 0.0;
		else
			boilPoint = boiling_point(surfacePressure);

		iterateSurfaceTemp(axis,rEcosphere);
	}
}

/*--------------------------------------------------------------------------*/
/*   The temperature calculated is in degrees Kelvin.                       */
/*   Quantities already known which are used in these calculations:         */
/*	 planet->molecule_weight					    */
/*	 planet->surface_pressure					    */
/*       R_ecosphere                                                        */
/*	 planet->a							    */
/*	 planet->volatile_gas_inventory					    */
/*	 planet->radius							    */
/*	 planet->boil_point						    */
/*--------------------------------------------------------------------------*/
void planets::iterateSurfaceTemp(double dist, double rEcosphere)
{
	double
//		surface_temp,
		effective_temp = eff_temp(rEcosphere,dist,EARTH_ALBEDO),
		greenhouse_rise,
		previous_temp,
		optical_depth = opacity(),
//		albedo,
		water,
		clouds,
		ice;

//	optical_depth = opacity((*planet)->molecule_weight,(*planet)->surface_pressure);
//	effective_temp = eff_temp(r_ecosphere,(*planet)->a,EARTH_ALBEDO);
	greenhouse_rise = green_rise(optical_depth,effective_temp,surfacePressure);
	surfaceTemp = effective_temp + greenhouse_rise;
//	previous_temp = surface_temp - 5.0;		/* force the while loop the first time */
//	while ((fabs(surface_temp - previous_temp) > 1.0))
	do
	{
		previous_temp = surfaceTemp;
		water = hydrosphere_fraction(volatileGasInventory,radius);
		clouds = cloud_fraction(surfaceTemp,minMoleculeWeight,radius,water);
		ice = ice_fraction(water,surfaceTemp);
		if ((surfaceTemp >= boilPoint) || (surfaceTemp <= FREEZING_POINT_OF_WATER))
			water = 0.0;
		albedo = planet_albedo(water,clouds,ice,surfacePressure);
		optical_depth = opacity();
		effective_temp = eff_temp(rEcosphere,dist,albedo);
		greenhouse_rise = green_rise(optical_depth,effective_temp,surfacePressure);
		surfaceTemp = effective_temp + greenhouse_rise;
	}while ((fabs(surfaceTemp - previous_temp) > 1.0));

	hydrosphere = water;
	cloudCover = clouds;
	iceCover = ice;
//	albedo = albedo;
//	surface_temp = surface_temp;
}

int planets::getAtmRate(void)
{
	if(surfacePressure<10.0) return 0;
	else if(surfacePressure<100.0) return 1;
	else if(surfacePressure<=400.0) return 3;
	else if(surfacePressure<=750.0) return 5;
	else if(surfacePressure<1500.0) return 6;
	else if(surfacePressure<2500.0) return 8;
	else return 14;
}

void planets::showUPP(FILE *f)
{
	planets *node2=firstMoon;

	fprintf(f,"    %7.3f    ",axis);

	if (isGasGiant)
		fprintf(f,"%s gas giant\n",(isGasGiant==1) ? "Small" : ((isGasGiant==2) ? "Large" : "Brown Dwarf"));
	else
		fprintf(f,"%X%X%XXXX\n",(int)(radius/800.0),getAtmRate(),(int)((hydrosphere+iceCover)*10.0));

	while(node2)
	{
		fprintf(f,"                               %7.3f   ",node2->axis*CM_PER_AU/CM_PER_KM/radius/2.0);
		if(node2->radius >800.0 ||node2->isPlanetoid ) fprintf(f,"   %X%X%XXXX\n",(int)(node2->radius/800.0),node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));
		else fprintf(f,"   S%X%XXXX\n",node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));

		node2=node2->nextPlanet;
	}
	fprintf(f,"\n");
}

void planets::showStats(FILE *f)
{
	planets *node2=firstMoon;
	int moonCount=1;

	if (isGasGiant)
		fprintf(f,"%s gas giant\n",(isGasGiant==1) ? "Small" : ((isGasGiant==2) ? "Large" : "Brown Dwarf"));
	else
		fprintf(f," %X%X%XXXX\n",(int)(radius/800.0),getAtmRate(),(int)((hydrosphere+iceCover)*10.0));
	if(isPlanetoid)
		fprintf(f," Asteroid Belt...\n");

	if (isResonantPeriod)
		fprintf(f,"In resonant period with primary.\n");

	fprintf(f,"   Distance from primary star (in A.U.): %7.3lf\n",axis);
	fprintf(f,"   Eccentricity of orbit: %5.3lf\n",eccentricity);
	fprintf(f,"   Mass (in Earth masses): %7.3lf\n",mass * EARTH_MASSES_PER_SOLAR_MASS);
	fprintf(f,"   Equatorial radius (in Km): %10.1lf\n",radius);
	fprintf(f,"   Density (in g/cc): %6.3lf\n",density);
	fprintf(f,"   Escape Velocity (in km/sec): %5.2lf\n",escapeVelocity / CM_PER_KM);
	fprintf(f,"   Escape Velocity (in G-Hrs) : %6.3lf\n",escapeVelocity / CM_PER_KM/36.0);
	fprintf(f,"   Smallest molecular weight retained: %5.2lf\n",minMoleculeWeight);
	fprintf(f,"   Surface acceleration (in  m/sec2) : %6.2lf\n",surfaceAccel/CM_PER_METER);
	if (!(isGasGiant) && !isPlanetoid)
	{
		fprintf(f,"   Surface Gravity (in Earth gees): %5.2lf\n",surfaceGrav);
		fprintf(f,"   Boiling point of water (celcius): %4.1lf\n",(boilPoint - KELVIN_CELCIUS_DIFFERENCE));
		fprintf(f,"   Surface Pressure (in atmospheres): %5.3lf",(surfacePressure / 1000.0));
		if ((isGreenhouseEffect) && (surfacePressure > 0.0))
			fprintf(f,"     RUNAWAY GREENHOUSE EFFECT\n");
		else
			fprintf(f,"\n");
		fprintf(f,"   Surface temperature (Celcius): %4.2lf\n",(surfaceTemp - KELVIN_CELCIUS_DIFFERENCE));
		fprintf(f,"   Hydrosphere percentage: %6.2lf%%\n",(hydrosphere * 100.0));
		fprintf(f,"   Cloud cover percentage: %6.2lf%%\n",(cloudCover * 100.0));
		fprintf(f,"   Ice cover percentage  : %6.2lf%%\n",(iceCover * 100.0));
	}
	fprintf(f,"   Axial tilt (in degrees): %d\n",axialTilt);
	fprintf(f,"   Planetary albedo: %4.3lf\n",albedo);
	fprintf(f,"   Length of year (in days): %7.2lf\n",orbitalPeriod);
	fprintf(f,"   Length of day (in hours): %7.2lf\n",day);

	if(node2) fprintf(f,"\n");
	else fprintf(f,"   Has no moons.\n\n");
	while(node2)
	{
		fprintf(f,"   Moon %d:  ",moonCount++);
		if(node2->radius >800.0 ||node2->isPlanetoid ) fprintf(f,"   %X%X%XXXX\n",(int)(node2->radius/800.0),node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));
		else fprintf(f,"   S%X%XXXX\n",node2->getAtmRate(),(int)((node2->hydrosphere+node2->iceCover)*10.0));
		if(node2->isPlanetoid) fprintf(f,"    Rings!\n");
		if (node2->isResonantPeriod)
			fprintf(f,"In resonant period with planet.\n");

		fprintf(f,"    Distance from world (in km): %7.3lf\n",node2->axis*CM_PER_AU/CM_PER_KM);
		fprintf(f,"    Eccentricity of orbit: %5.3lf\n",node2->eccentricity);
		fprintf(f,"    Mass (in Earth masses): %7.3lf\n",node2->mass * EARTH_MASSES_PER_SOLAR_MASS);
		fprintf(f,"    Equatorial radius (in Km): %10.1lf\n",node2->radius);
		fprintf(f,"    Density (in g/cc): %6.3lf\n",node2->density);
		fprintf(f,"    Escape Velocity (in km/sec): %5.2lf\n",node2->escapeVelocity / CM_PER_KM);
		fprintf(f,"    Escape Velocity (in G-Hrs) : %6.3lf\n",node2->escapeVelocity / CM_PER_KM/36.0);
		fprintf(f,"    Smallest molecular weight retained: %5.2lf\n",node2->minMoleculeWeight);
		fprintf(f,"    Surface acceleration (in m/sec2)  : %6.2lf\n",node2->surfaceAccel/CM_PER_METER);
		if(!node2->isPlanetoid)
		{
			fprintf(f,"    Surface Gravity (in Earth gees): %5.2lf\n",node2->surfaceGrav);
			fprintf(f,"    Boiling point of water (celcius): %4.1lf\n",(node2->boilPoint - KELVIN_CELCIUS_DIFFERENCE));
			fprintf(f,"    Surface Pressure (in atmospheres): %5.3lf",(node2->surfacePressure / 1000.0));
			if ((node2->isGreenhouseEffect) && (node2->surfacePressure > 0.0))
				fprintf(f,"     RUNAWAY GREENHOUSE EFFECT\n");
			else
				fprintf(f,"\n");
			fprintf(f,"    Surface temperature (Celcius): %4.2lf\n",(node2->surfaceTemp - KELVIN_CELCIUS_DIFFERENCE));
			fprintf(f,"    Hydrosphere percentage: %6.2lf%%\n",(node2->hydrosphere * 100.0));
			fprintf(f,"    Cloud cover percentage: %6.2lf%%\n",(node2->cloudCover * 100.0));
			fprintf(f,"    Ice cover percentage  : %6.2lf%%\n",(node2->iceCover * 100.0));
		}
		fprintf(f,"    Axial tilt (in degrees): %d\n",node2->axialTilt);
		fprintf(f,"    Planetary albedo: %4.3lf\n",node2->albedo);
		fprintf(f,"    Length of month (in hours): %7.2lf\n",node2->orbitalPeriod*24.0);
		fprintf(f,"    Length of day (in hours): %7.2lf\n\n",node2->day);

		node2=node2->nextPlanet;
	}
}

// Current arbitrary values for max mass of a moon of a planet:
// For moons of a GG, max of 0.50 M (Earth)
// For all others, max of .125 M (parent world)
void planets::buildMoonData(double minOrbit, double maxOrbit, double starMass, double starLuminosity, double rEcosphere, double rGreenhouse, double age)
{
	int spin_resonance;
	planets * pl=new planets;
// pick a mass & orbit!
	pl->isGasGiant=FALSE;
	if(isGasGiant)
	{
		pl->mass=random_number(0.0,.5/EARTH_MASSES_PER_SOLAR_MASS);
		pl->axis=random_number(minOrbit,maxOrbit)*1e06*CM_PER_KM/CM_PER_AU;
	}
	else
	{
		pl->mass=random_number(0.0,mass/8.0);
		pl->axis=random_number(minOrbit,maxOrbit)*1e06*CM_PER_KM/CM_PER_AU;
	}

	pl->orbitalZone = orbital_zone(axis, starLuminosity);

	pl->radius = pl->kothariRadius();
	pl->density = pl->volumeDensity();

	pl->orbitalPeriod = period(pl->axis,pl->mass,mass);
	pl->day = pl->dayLength(spin_resonance,age);

	pl->isResonantPeriod = spin_resonance;
	pl->axialTilt = inclination(axis);
	pl->escapeVelocity = escape_vel(pl->mass,pl->radius);
	pl->surfaceAccel = acceleration(pl->mass,pl->radius);
	pl->RMSvelocity = rms_vel(MOLECULAR_NITROGEN,axis);
	pl->minMoleculeWeight = molecule_limit(axis,pl->mass,pl->radius);

	pl->isPlanetoid=(radius<100.0);
	pl->surfaceGrav = gravity(pl->surfaceAccel);
	pl->isGreenhouseEffect = greenhouse(pl->orbitalZone,axis,rGreenhouse);
	pl->volatileGasInventory = pl->volInventory(starMass);

	pl->surfacePressure = pressure(pl->volatileGasInventory,pl->radius,pl->surfaceGrav);

	if ((pl->surfacePressure == 0.0))
		pl->boilPoint = 0.0;
	else
		pl->boilPoint = boiling_point(pl->surfacePressure);

// How to add effects of Brown Dwarfs?
	pl->iterateSurfaceTemp(axis,rEcosphere);

// now insert into link list
	if(!firstMoon)
	{
		pl->nextPlanet=0;
      firstMoon=pl;
	}
	else
	{
		if(pl->axis<firstMoon->axis)
		{
			pl->nextPlanet=firstMoon;
			firstMoon=pl;
		}
		else
		{
			planets* here=firstMoon;
			while(here->nextPlanet && here->nextPlanet->axis < pl->axis)
				here=here->nextPlanet;
			pl->nextPlanet=here->nextPlanet;
         here->nextPlanet=pl;
		}
	}
}

// added CEW:  minOrbit & maxOrbit are in Mkm
// The number of moons generated are based on Traveller's values:
// Sm GG 2D6-2,
// Lg GG 2D6
// Planets of at least size 2, 50% chance 1D3 moons
void planets::addMoons(double minOrbit, double maxOrbit,double starMass, double starLuminosity, double rEcosphere, double rGreenhouse, double age)
{
	firstMoon=0;

	printf("%5.1lf: %7.0lfkm radius\n",axis,radius);
//	showUPP(stdout);

	if(isPlanetoid) return;

	register int i, end;

	if(isGasGiant)
	{
		// automatic get moons!
		end=random(6)+random(6)+2*(isGasGiant>1);
		for(i=0;i<end;i++)
			buildMoonData(minOrbit,maxOrbit,starMass, starLuminosity, rEcosphere, rGreenhouse, age);
	}
	else
	{
		// Fifty-fifty of 1-3 moons
		if((radius>1600.0) && random(2))
		{
			end=random(3)+1;
			for(i=0;i<end;i++)
				buildMoonData(minOrbit,maxOrbit,starMass, starLuminosity, rEcosphere, rGreenhouse, age);
		}
	}
}
