#include "enviro.h"
#include <boost/concept_check.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "const.h"
#include "elements.h"
#include "gas_radius_helpers.h"
#include "radius_tables.h"
#include "solid_radius_helpers.h"
#include "star_temps.h"
#include "stargen.h"
#include "utils.h"

using namespace std;

string breathability_phrase[4] =
{
  "none",
  "breathable",
  "unbreathable",
  "poisonous"
};

map<map<long double, long double>, vector<long double> > polynomial_cache;

long double mass_to_luminosity(long double mass)
{
  if (mass <= 0.6224)
  {
    return 0.3815 * pow(mass, 2.5185);
  }
  else if (mass <= 1.0)
  {
    return pow(mass, 4.551);
  }
  else if (mass <= 3.1623)
  {
    return pow(mass, 4.351);
  }
  else if (mass <= 16.0)
  {
    return 2.7563 * pow(mass, 3.4704);
  }
  else
  {
    return 42.321 * pow(mass, 2.4853);
  }
}

long double luminosity_to_mass(long double luminosity)
{
  long double a = luminosity;
  if (a <= (0.3815 * pow(0.6224, 2.5185)))
  {
    return 1.46613 * pow(a, 0.3970617431010522);
  }
  else if (a <= 1)
  {
    return pow(a, 0.2197319270490002);
  }
  else if (a <= pow(3.1623, 4.351))
  {
    return pow(a, 0.2298322224775914);
  }
  else if (a <= (2.7563 * pow(16, 3.4704)))
  {
    return 0.746654 * pow(a, 0.2881512217611803);
  }
  else
  {
    return 0.221579 * pow(a, 0.4023659115599726);
  }
}

int getLumIndex(string spec_type)
{
  const char *strPtr;
  
  strPtr = strstr(spec_type.c_str(), "Ia0");
  if (strPtr != NULL)
  {
    return 2;
  }
  else
  {
    strPtr = strstr(spec_type.c_str(), "Ia");
    if (strPtr != NULL)
    {
      return 2;
    }
    else
    {
      strPtr = strstr(spec_type.c_str(), "Ib");
      if (strPtr != NULL)
      {
	return 2;
      }
      else
      {
	strPtr = strstr(spec_type.c_str(), "III");
	if (strPtr != NULL)
	{
	  return 1;
	}
	else
	{
	  strPtr = strstr(spec_type.c_str(), "II");
	  if (strPtr != NULL)
	  {
	    return 2;
	  }
	  else
	  {
	    strPtr = strstr(spec_type.c_str(), "IV");
	    if (strPtr != NULL)
	    {
	      return 1;
	    }
	    else
	    {
	      strPtr = strstr(spec_type.c_str(), "VI");
	      if (strPtr != NULL)
	      {
		return 0;
	      }
	      else
	      {
		return 0;
	      }
	    }
	  }
	}
      }
    }
  }
}

string getStarType(string spec_type)
{
  spec_type = my_strtoupper(spec_type);
  const char *strPtr;
  
  strPtr = strstr(spec_type.c_str(), "DA");
  if (strPtr != NULL)
  {
    return "WD";
  }
  else
  {
    strPtr = strstr(spec_type.c_str(), "DB");
    if (strPtr != NULL)
    {
      return "WD";
    }
    else
    {
      strPtr = strstr(spec_type.c_str(), "DC");
      if (strPtr != NULL)
      {
	return "WD";
      }
      else
      {
	strPtr = strstr(spec_type.c_str(), "DO");
	if (strPtr != NULL)
	{
	  return "WD";
	}
	else
	{
	  strPtr = strstr(spec_type.c_str(), "DQ");
	  if (strPtr != NULL)
	  {
	    return "WD";
	  }
	  else
	  {
	    strPtr = strstr(spec_type.c_str(), "DZ");
	    if (strPtr != NULL)
	    {
	      return "WD";
	    }
	    else
	    {
	      strPtr = strstr(spec_type.c_str(), "WN");
	      if (strPtr != NULL)
	      {
		return "WN";
	      }
	      else
	      {
		strPtr = strstr(spec_type.c_str(), "WC");
		if (strPtr != NULL)
		{
		  return "WC";
		}
		else
		{
		  strPtr = strstr(spec_type.c_str(), "O");
		  if (strPtr != NULL)
		  {
		    return "O";
		  }
		  else
		  {
		    strPtr = strstr(spec_type.c_str(), "B");
		    if (strPtr != NULL)
		    {
		      return "B";
		    }
		    else
		    {
		      strPtr = strstr(spec_type.c_str(), "A");
		      if (strPtr != NULL)
		      {
			return "A";
		      }
		      else
		      {
			strPtr = strstr(spec_type.c_str(), "F");
			if (strPtr != NULL)
			{
			  return "F";
			}
			else
			{
			  strPtr = strstr(spec_type.c_str(), "G");
			  if (strPtr != NULL)
			  {
			    return "G";
			  }
			  else
			  {
			    strPtr = strstr(spec_type.c_str(), "K");
			    if (strPtr != NULL)
			    {
			      return "K";
			    }
			    else
			    {
			      strPtr = strstr(spec_type.c_str(), "M");
			      if (strPtr != NULL)
			      {
				return "M";
			      }
			      else
			      {
				strPtr = strstr(spec_type.c_str(), "L");
				if (strPtr != NULL)
				{
				  return "L";
				}
				else
				{
				  strPtr = strstr(spec_type.c_str(), "T");
				  if (strPtr != NULL)
				  {
				    return "T";
				  }
				  else
				  {
				    strPtr = strstr(spec_type.c_str(), "Y");
				    if (strPtr != NULL)
				    {
				      return "Y";
				    }
				    else
				    {
				      strPtr = strstr(spec_type.c_str(), "H");
				      if (strPtr != NULL)
				      {
					return "H";
				      }
				      else
				      {
					strPtr = strstr(spec_type.c_str(), "E");
					if (strPtr != NULL)
					{
					  return "E";
					}
					else
					{
					  strPtr = strstr(spec_type.c_str(), "I");
					  if (strPtr != NULL)
					  {
					    return "I";
					  }
					  else
					  {
					    strPtr = strstr(spec_type.c_str(), "R");
					    if (strPtr != NULL)
					    {
					      return "K";
					    }
					    else
					    {
					      strPtr = strstr(spec_type.c_str(), "S");
					      if (strPtr != NULL)
					      {
						return "M";
					      }
					      else
					      {
						strPtr = strstr(spec_type.c_str(), "N");
						if (strPtr != NULL)
						{
						  return "M";
						}
						else
						{
						  strPtr = strstr(spec_type.c_str(), "C");
						  if (strPtr != NULL)
						  {
						    return "M";
						  }
						  else
						  {
						    //cerr << "test1" << endl;
						    cerr << "Unsupported star type: " << spec_type << endl;
						    exit(EXIT_FAILURE);
						    return NULL;
						  }
						}
					      }
					    }
					  }
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

int getSubType(string spec_type)
{
  int total_chars;
  total_chars = spec_type.size();
  string buffer;
  
  for (string::iterator it = spec_type.begin(); it < spec_type.end(); it++)
  {
    if (isdigit(*it))
    {
      buffer += *it;
      return atoi(buffer.c_str());
    }
  }
  return 0;
}

long double spec_type_to_eff_temp(string spec_type)
{
  if (spec_type.empty())
  {
    return 0;
  }
  string star_type;
  int lumIndex;
  int sub_type;
  
  //cout << "test3" << endl;
  star_type = getStarType(spec_type);
  //cout << "test4" << endl;
  sub_type = getSubType(spec_type);
  lumIndex = getLumIndex(spec_type);
  
  if (strcmp(star_type.c_str(), "WD") == 0)
  {
    return tempWD[sub_type];
  }
  else if (strcmp(star_type.c_str(), "WN") == 0)
  {
    return tempWN[sub_type];
  }
  else if (strcmp(star_type.c_str(), "WC") == 0)
  {
    return tempWC[sub_type];
  }
  else if (strcmp(star_type.c_str(), "O") == 0)
  {
    return tempO[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "B") == 0)
  {
    return tempB[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "A") == 0)
  {
    return tempA[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "F") == 0)
  {
    return tempF[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "G") == 0)
  {
    return tempG[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "K") == 0)
  {
    //fprintf(stderr, "%u %u %8.8LG\n", lumIndex, sub_type, tempK[lumIndex][sub_type]);
    //exit(EXIT_FAILURE);
    return tempK[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "M") == 0)
  {
    return tempM[lumIndex][sub_type];
  }
  else if (strcmp(star_type.c_str(), "L") == 0)
  {
    return tempL[sub_type];
  }
  else if (strcmp(star_type.c_str(), "T") == 0)
  {
    return tempT[sub_type];
  }
  else if (strcmp(star_type.c_str(), "Y") == 0)
  {
    return tempY[sub_type];
  }
  else if (strcmp(star_type.c_str(), "H") == 0)
  {
    return tempH[sub_type];
  }
  else if (strcmp(star_type.c_str(), "I") == 0)
  {
    return tempI[sub_type];
  }
  else if (strcmp(star_type.c_str(), "E") == 0)
  {
    return tempE[sub_type];
  }
  else
  {
    //cerr << "test2" << endl;
    cerr << "Unsupported star type: " << star_type << endl;
    exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
}

string eff_temp_to_spec_type(long double eff_temp, long double luminosity)
{
  string clums[] = {"I-a0", "I-a", "I-b", "II", "III", "IV"};
  long double rlums[] = {200000.0, 20000.0, 3000.0, 400.0, 11.5, 4.0};
  string classes[] = {"x", "O", "B", "A", "F", "G", "K", "M", "L", "T", "Y"};
  long double tclass[] = {52000, 30000.0, 10000.0, 7500.0, 6000.0, 5000.0, 3500.0, 2000.0, 1300.0, 700.0, 0.0};
  
  int at;
  long double csiz, cdel, cfrac, dt;
  string aclass, ac, clum;
  char temp[33];
  long double xmag;
  string output;
  
  if (luminosity == 0)
  {
    luminosity = 0.0000001; // avoid getting an undefined answer for log(xlum)
  }
  xmag = 4.83 - (2.5 * (log(luminosity) / log(10.0)));
  
  // determine spectral clas
  output = aclass = "????";
  at = 0;
  for (int i = 1; i <= 10; i++)
  {
    if (eff_temp > tclass[i])
    {
      ac = classes[i];
      csiz = tclass[i-1] - tclass[i];
      cdel = eff_temp - tclass[i];
      cfrac = cdel / csiz;
      dt = 10.0 - (10.0 * cfrac);
      if (dt < 0.0)
      {
      	dt = 0.0;
      }
      at = floor(dt);
      my_itoa(at, temp, 10);
      aclass = ac.append(temp);
      break;
    }
  }
  clum = " ";
  if (eff_temp > 52000) // the hotest a type O star can get is 52000. Any hotter and the star is most likely a Wolf–Rayet star
  {
      ac = "WN";
      csiz = 200000 - 52000;
      cdel = eff_temp - 52000;
      cfrac = cdel / csiz;
      dt = 10.0 - (10.0 * cfrac);
      if (dt < 0.0)
      {
      	dt = 0.0;
      }
      at = floor(dt);
      my_itoa(at, temp, 10);
      aclass = ac.append(temp);
  }
  else
  {
    if (compare_string_char(aclass, 1, "O"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -6)
      {
	aclass.append("Ib");
      }
      else if (xmag < -4.9)
      {
	aclass.append("II");
      }
      else if (xmag < -4)
      {
	aclass.append("III");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "B"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -4.5)
      {
	aclass.append("II");
      }
      else if (xmag < -0.5)
      {
	aclass.append("III");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "A"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -4.5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -2.25)
      {
	aclass.append("II");
      }
      else if (xmag < 0)
      {
	aclass.append("III");
      }
      else if (xmag < 0.125)
      {
	aclass.append("IV");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "F"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -4.5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -2)
      {
	aclass.append("II");
      }
      else if (xmag < 1.75)
      {
	aclass.append("III");
      }
      else if (xmag < 3)
      {
	aclass.append("IV");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "G"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -4.5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -2.25)
      {
	aclass.append("II");
      }
      else if (xmag < 1.75)
      {
	aclass.append("III");
      }
      else if (xmag < 3)
      {
	aclass.append("IV");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "K"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -4.5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -2)
      {
	aclass.append("II");
      }
      else if (xmag < 2)
      {
	aclass.append("III");
      }
      else if (xmag < 4)
      {
	aclass.append("IV");
      }
      else
      {
	aclass.append("V");
      }
    }
    else if (compare_string_char(aclass, 1, "M"))
    {
      if (xmag < -9)
      {
	aclass.append("O");
      }
      else if (xmag < -7)
      {
	aclass.append("Ia");
      }
      else if (xmag < -4.5)
      {
	aclass.append("Ib");
      }
      else if (xmag < -2)
      {
	aclass.append("II");
      }
      else if (xmag < 2.5)
      {
	aclass.append("III");
      }
      else
      {
	aclass.append("V");
      }
    }
    else
    {
      aclass.append("V");
    }
  }
  output = aclass;
  return output;
}

/*--------------------------------------------------------------------------*/
/*	 This function, given the orbital radius of a planet in AU, returns */
/*	 the orbital 'zone' of the particle.                                */
/*--------------------------------------------------------------------------*/

int orb_zone(long double ecosphere_radius, long double orb_radius)
{
  if (orb_radius < (4.0 * ecosphere_radius))
  {
    return 1;
  }
  else if (orb_radius < (15.0 * ecosphere_radius))
  {
    return 2;
  }
  else
  {
    return 3;
  }
}

/*-------------------------------------------------------------------*/
/* The mass is in units of solar masses, and the density is in units */
/* of grams/cc.  The radius returned is in units of km.              */
/*-------------------------------------------------------------------*/

long double volume_radius(long double mass, long double density)
{
  long double volume; 
  
  mass = mass * SOLAR_MASS_IN_GRAMS;
  volume = mass / density;
  return pow((3.0 * volume) / (4.0 * PI), (1.0 / 3.0)) / CM_PER_KM;
}

/*------------------------------------------------------------------------*/
/* The mass passed in is in units of solar masses, and the orbital radius */
/* is in units of AU. The density is returned in units of grams/cc.       */
/*------------------------------------------------------------------------*/

long double empirical_density(long double mass, long double orb_radius, long double r_ecosphere, bool gas_giant)
{
  long double temp; 
  
  temp = pow(mass * SUN_MASS_IN_EARTH_MASSES, 1.0 / 8.0);
  temp = temp * pow1_4(r_ecosphere / orb_radius);
  if (gas_giant)
  {
    return temp * 1.2;
  }
  else
  {
    return temp * 5.5;
  }
}

/*--------------------------------------------------------------------*/
/* The mass passed in is in units of solar masses, and the equatorial */
/* radius is in km.  The density is returned in units of grams/cc.    */
/*--------------------------------------------------------------------*/

long double volume_density(long double mass, long double equat_radius)
{
  long double volume; 
  
  mass = mass * SOLAR_MASS_IN_GRAMS;
  equat_radius = equat_radius * CM_PER_KM;
  volume = (4.0 * PI * pow3(equat_radius)) / 3.0;
  return mass / volume;
}

/*-------------------------------------------------------------------------*/
/* The separation is in units of AU, and both masses are in units of solar */
/* masses. The period returned is in terms of Earth days.                  */
/*-------------------------------------------------------------------------*/

long double period(long double separation, long double small_mass, long double large_mass)
{
  long double period_in_years; 
  
  period_in_years = sqrt(pow3(separation) / (small_mass + large_mass));
  return period_in_years * DAYS_IN_A_YEAR ;
}

/*--------------------------------------------------------------------------*/
/* Fogg's information for this routine came from Dole "Habitable Planets    */
/* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    */
/* up with his eq.12, which is the equation for the 'base_angular_velocity' */
/* below.  He then used an equation for the change in angular velocity per  */
/* time (dw/dt) from P. Goldreich and S. Soter's paper "Q in the Solar      */
/* System" in Icarus, vol 5, pp.375-389 (1966).	 Using as a comparison the  */
/* change in angular velocity for the Earth, Fogg has come up with an       */
/* approximation for our new planet (his eq.13) and take that into account. */
/* This is used to find 'change_in_angular_velocity' below.                 */
/*                                                                          */
/* Input parameters are mass (in solar masses), radius (in Km), orbital     */
/* period (in days), orbital radius (in AU), density (in g/cc),             */
/* eccentricity, and whether it is a gas giant or not.                      */
/* The length of the day is returned in units of hours.                     */
/*--------------------------------------------------------------------------*/

long double day_length(planet *the_planet, long double parent_mass, bool is_moon)
{
  long double planetary_mass_in_grams = the_planet->getMass() * SOLAR_MASS_IN_GRAMS;
  long double equatorial_radius_in_cm = the_planet->getRadius() * CM_PER_KM;
  long double year_in_hours = the_planet->getOrbPeriod() * 24.0;
  bool giant = the_planet->getType() == tGasGiant || the_planet->getType() == tBrownDwarf || the_planet->getType() == tSubGasGiant || the_planet->getType() == tSubSubGasGiant;
  long double k2;
  long double base_angular_velocity;
  long double change_in_angular_velocity;
  long double ang_velocity;
  long double spin_resonance_factor;
  long double day_in_hours;
  
  bool stopped = false;
  
  the_planet->setResonantPeriod(false);
  
  /*if (giant)
  {
    k2 = 0.24;
  }
  else
  {
    k2 = 0.33;
  }*/
  k2 = calculate_moment_of_inertia_coeffient(the_planet);
  
  // Calculate the base angular velocity
  base_angular_velocity = sqrt(2.0 * J * (planetary_mass_in_grams) / (k2 * pow2(equatorial_radius_in_cm)));
  
  // This next calculation determines how much the planet's rotation is
  // slowed by the presence of the parent body.
  if (!is_moon)
  {
    change_in_angular_velocity = CHANGE_IN_EARTH_ANG_VEL * (the_planet->getDensity() / EARTH_DENSITY) * (equatorial_radius_in_cm / EARTH_RADIUS) * (EARTH_MASS_IN_GRAMS / planetary_mass_in_grams) * pow(parent_mass, 2.0) * (1.0 / pow(the_planet->getA(), 6.0)); 
  }
  else
  {
    change_in_angular_velocity = CHANGE_IN_EARTH_ANG_VEL * (the_planet->getDensity() / EARTH_DENSITY) * (equatorial_radius_in_cm / EARTH_RADIUS) * (EARTH_MASS_IN_GRAMS / planetary_mass_in_grams) * pow(parent_mass, 2.0) * (1.0 / pow(the_planet->getMoonA(), 6.0));
  }
  ang_velocity = base_angular_velocity + (change_in_angular_velocity * the_planet->getTheSun().getAge());
  
  if (ang_velocity <= 0.0)
  {
    stopped = true;
    day_in_hours = INCREDIBLY_LARGE_NUMBER;
  }
  else
  {
    day_in_hours = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * ang_velocity);
  }
  
  if (day_in_hours >= year_in_hours || stopped)
  {
    if ((the_planet->getE() > 0.1 && !is_moon) || (the_planet->getMoonE() > 0.1 && is_moon))
    {
      if (!is_moon)
      {
	spin_resonance_factor = getSpinResonanceFactor(the_planet->getE());
      }
      else
      {
	spin_resonance_factor = getSpinResonanceFactor(the_planet->getMoonE());
      }
      the_planet->setResonantPeriod(true);
      return spin_resonance_factor * year_in_hours;
    }
    else
    {
      the_planet->setAxialTilt(0);
      return day_in_hours = year_in_hours;
    }
  }
  
  return day_in_hours;
}

/*---------------------------------------------------------------------*/
/* The orbital radius is expected in units of Astronomical Units (AU). */
/* Inclination is returned in units of degrees. (seb: real)            */
/*---------------------------------------------------------------------*/

long double inclination(long double orb_radius, long double parent_mass)
{
  // seb: Earth's obliquity is not a good test
  // a. want real result, not integer
  // b. obliquity of planets near stars is erroded by tidal heating
  // ref: http://arxiv.org/abs/1101.2156
  // Tidal obliquity evolution of potentialy habitable planets
  // Heller et al. (2011)
  
  long double temp; 
  temp = fabs(gaussian(33.3));
  temp = pow(orb_radius/50.0,0.2) * temp;
  if (orb_radius < parent_mass)
  {
    temp = (orb_radius / parent_mass) * temp;
  }
  
  return temp;
}

/*-----------------------------------------------------------------------*/
/* This function implements the escape velocity calculation. Note that   */
/* it appears that Fogg's eq.15 is incorrect.                            */
/* The mass is in units of solar mass, the radius in kilometers, and the */
/* velocity returned is in cm/sec.                                       */
/*-----------------------------------------------------------------------*/

long double escape_vel(long double mass, long double radius)
{
  long double mass_in_grams, radius_in_cm;
  
  mass_in_grams = mass * SOLAR_MASS_IN_GRAMS;
  radius_in_cm = radius * CM_PER_KM;
  return sqrt(2.0 * GRAV_CONSTANT * mass_in_grams / radius_in_cm);
}

/*------------------------------------------------------------------------*/
/* This is Fogg's eq.16.  The molecular weight (usually assumed to be N2) */
/* is used as the basis of the Root Mean Square (RMS) velocity of the     */
/* molecule or atom.  The velocity returned is in cm/sec.                 */
/* Orbital radius is in A.U.(ie: in units of the earth's orbital radius). */
/*------------------------------------------------------------------------*/

long double rms_vel(long double molecular_weight, long double exospheric_temp)
{
  return sqrt((3.0 * MOLAR_GAS_CONST * exospheric_temp) / molecular_weight) * CM_PER_METER;
}

long double min_molec_weight(planet *the_planet)
{
  long double mass = the_planet->getMass();
  long double radius = the_planet->getRadius();
  long double temp = the_planet->getExosphericTemp();
  long double target = 5.0E9;
  
  long double guess_1 = molecule_limit(mass, radius, temp);
  long double guess_2 = guess_1;
  
  long double life = gas_life(guess_1, the_planet);
  
  int loops = 0;
  
  target = the_planet->getTheSun().getAge();
  
  if (life > target)
  {
    while (life > target && loops++ < 25)
    {
      guess_1 = guess_1 / 2.0;
      life = gas_life(guess_1, the_planet);
    }
  }
  else
  {
    while (life < target && loops++ < 25)
    {
      guess_2 = guess_2 * 2.0;
      life = gas_life(guess_2, the_planet);
    }
  }
  
  loops = 0;
  
  while ((guess_2 - guess_1) > 0.1 && loops++ < 25)
  {
    long double guess_3 = (guess_1 + guess_2) / 2.0;
    life = gas_life(guess_3, the_planet);
    
    if (life < target)
    {
      guess_1 = guess_3;
    }
    else
    {
      guess_2 = guess_3;
    }
  }
  
  life = gas_life(guess_2, the_planet);
  
  return guess_2;
}

/*------------------------------------------------------------------------*/
/* This function returns the smallest molecular weight retained by the    */
/* body, which is useful for determining the atmosphere composition.      */
/* Mass is in units of solar masses, and equatorial radius is in units of */
/* kilometers.                                                            */
/*------------------------------------------------------------------------*/

long double molecule_limit(long double mass, long double equat_radius, long double exospheric_temp)
{
  long double esc_velocity = escape_vel(mass, equat_radius);
  
  return (3.0 * MOLAR_GAS_CONST * exospheric_temp) / (pow2((esc_velocity/ GAS_RETENTION_THRESHOLD) / CM_PER_METER));
}

/*----------------------------------------------------------------------*/
/* This function calculates the surface acceleration of a planet. The   */
/* mass is in units of solar masses, the radius in terms of km, and the */
/* acceleration is returned in units of cm/sec2.                        */
/*----------------------------------------------------------------------*/

long double acceleration(long double mass, long double radius)
{
  return GRAV_CONSTANT * (mass * SOLAR_MASS_IN_GRAMS) / pow2(radius * CM_PER_KM);
}

/*---------------------------------------------------------------------*/
/* This function calculates the surface gravity of a planet. The       */
/* acceleration is in units of cm/sec2, and the gravity is returned in */
/* units of Earth gravities.                                           */
/*---------------------------------------------------------------------*/

long double gravity(long double acceleration)
{
  return(acceleration / EARTH_ACCELERATION);
}

/*---------------------------------------------------------------------------*/
/*	This implements Fogg's eq.17.  The 'inventory' returned is unitless. */
/*---------------------------------------------------------------------------*/

long double vol_inventory(long double mass, long double escape_vel, long double rms_vel, long double stellar_mass, int zone, bool greenhouse_effect, bool accreted_gas)
{
  long double velocity_ratio, proportion_const, temp1, temp2, earth_units;
  
  velocity_ratio = escape_vel / rms_vel;
  if (velocity_ratio >= GAS_RETENTION_THRESHOLD || accreted_gas)
  {
    switch (zone)
    {
      case 1:
	proportion_const = 140000.0;	/* 100 -> 140 JLB */
	break;
      case 2:
	proportion_const = 75000.0;
	break;
      case 3:
	proportion_const = 250.0;
	break;
      default:
	proportion_const = 0.0;
	cout << "Error: orbital zone not initialized correctly!" << endl;
	exit(EXIT_FAILURE);
	return EXIT_FAILURE;
	break;
    }
    earth_units = mass * SUN_MASS_IN_EARTH_MASSES;
    temp1 = (proportion_const * earth_units) / stellar_mass;
    temp2 = about(temp1, 0.2);
    temp2 = temp1;
    if (greenhouse_effect || accreted_gas)
    {
      return temp2;
    }
    else
    {
      return temp2 / 140.0;
    }
  }
  else
  {
    return 0.0;
  }
}

/*------------------------------------------------------------------------------*/
/*	This implements Fogg's eq.18.  The pressure returned is in units of     */
/*	millibars (mb).	 The gravity is in units of Earth gravities, the radius */
/*	in units of kilometers.                                                 */
/*                                                                              */
/*  JLB: Aparently this assumed that earth pressure = 1000mb. I've added a	*/
/*	fudge factor (EARTH_SURF_PRES_IN_MILLIBARS / 1000.) to correct for that */
/*------------------------------------------------------------------------------*/

long double pressure(long double volatile_gas_inventory, long double equat_radius, long double gravity)
{
  equat_radius = KM_EARTH_RADIUS / equat_radius;
  return volatile_gas_inventory * gravity * (EARTH_SURF_PRES_IN_MILLIBARS / 1000.0) / pow2(equat_radius);
}

/*---------------------------------------------------------------------------*/
/* This function returns the boiling point of water in an atmosphere of      */
/* pressure 'surf_pressure', given in millibars.	The boiling point is */
/* returned in units of Kelvin.  This is Fogg's eq.21.                       */
/*---------------------------------------------------------------------------*/

long double boiling_point(long double surf_pressure)
{
  long double surface_pressure_in_bars; 
  
  surface_pressure_in_bars = surf_pressure / MILLIBARS_PER_BAR;
  return 1.0 / ((log(surface_pressure_in_bars) / -5050.5) + (1.0 / 373.0) );
}

/*----------------------------------------------------------------------------*/
/* This function is Fogg's eq.22.	 Given the volatile gas inventory and */
/* planetary radius of a planet (in Km), this function returns the            */
/* fraction of the planet covered with water.                                 */
/* I have changed the function very slightly:	 the fraction of Earth's      */
/* surface covered by water is 71%, not 75% as Fogg used.                     */
/*----------------------------------------------------------------------------*/

long double hydro_fraction(long double volatile_gas_inventory, long double planet_radius)
{
  long double temp;
  
  temp = (0.71 * volatile_gas_inventory / 1000.0) * pow2(KM_EARTH_RADIUS / planet_radius);
  if (temp >= 1.0)
  {
    return 1.0;
  }
  else 
  {
    return temp;
  }
}

/*-----------------------------------------------------------------------*/
/* Given the surface temperature of a planet (in Kelvin), this function  */
/* returns the fraction of cloud cover available. This is Fogg's eq.23.  */
/* See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.    */
/* This equation is Hart's eq.3.                                         */
/* I have modified it slightly using constants and relationships from    */
/* Glass's book "Introduction to Planetary Geology", p.46.               */
/* The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth    */
/* covered by one Kg. of cloud.                                          */
/*-----------------------------------------------------------------------*/

long double cloud_fraction(long double surf_temp, long double smallest_MW_retained, long double equat_radius, long double hydro_fraction)
{
  long double water_vapor_in_kg, fraction, surf_area, hydro_mass;
  
  if (smallest_MW_retained > WATER_VAPOR)
  {
    return 0.0;
  }
  else
  {
    surf_area = 4.0 * PI * pow2(equat_radius);
    hydro_mass = hydro_fraction * surf_area * EARTH_WATER_MASS_PER_AREA;
    water_vapor_in_kg = (0.00000001 * hydro_mass) * exp(Q2_36 * (surf_temp - EARTH_AVERAGE_KELVIN));
    fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surf_area;
    if (fraction >= 1.0)
    {
      return 1.0;
    }
    else
    {
      return fraction;
    }
  }
}

/*------------------------------------------------------------------------------*/
/* Given the surface temperature of a planet (in Kelvin), this function         */
/* returns the fraction of the planet's surface covered by ice.  This is        */
/* Fogg's eq.24.	See Hart[24] in Icarus vol.33, p.28 for an explanation. */
/* I have changed a constant from 70 to 90 in order to bring it more in         */
/* line with the fraction of the Earth's surface covered with ice, which        */
/* is approximatly .016 (=1.6%).                                                */
/*------------------------------------------------------------------------------*/

long double ice_fraction(long double hydro_fraction, long double surf_temp)
{
  long double temp;
  
  if (surf_temp > 328.0)
  {
    surf_temp = 328.0;
  }
  temp = pow(((328.0 - surf_temp) / 90.0), 5.0);
  if (temp > (1.5 * hydro_fraction))
  {
    temp = 1.5 * hydro_fraction;
  }
  if (temp >= 1.0)
  {
    return 1.0;
  }
  else
  {
    return temp;
  }
}

/*--------------------------------------------------------------------------*/
/* This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital  */
/* radius in AU, and the temperature returned is in Kelvin.                 */
/*--------------------------------------------------------------------------*/
long double eff_temp(long double ecosphere_radius, long double orb_radius, long double albedo)
{
  return sqrt(ecosphere_radius / orb_radius) * pow1_4((1.0 - albedo) / (1.0 - EARTH_ALBEDO)) * EARTH_EFFECTIVE_TEMP;
}

long double est_temp(long double ecosphere_radius, long double orb_radius, long double albedo)
{
  return sqrt(ecosphere_radius / orb_radius) * pow1_4((1.0 - albedo) / (1.0 - EARTH_ALBEDO)) * EARTH_AVERAGE_KELVIN;
}

/*-------------------------------------------------------------------------*/
/* Old grnhouse:                                                           */
/* Note that if the orbital radius of the planet is greater than or equal  */
/* to R_inner, 99% of it's volatiles are assumed to have been deposited in */
/* surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
/*-------------------------------------------------------------------------*/
/*	if ((orb_radius < r_greenhouse) && (zone == 1)) */

/*------------------------------------------------------------------------*/
/* The new definition is based on the inital surface temperature and what */
/* state water is in. If it's too hot, the water will never condense out  */
/* of the atmosphere, rain down and form an ocean. The albedo used here   */
/* was chosen so that the boundary is about the same as the old method    */
/* Neither zone, nor r_greenhouse are used in this version. JLB           */
/*------------------------------------------------------------------------*/

bool grnhouse(long double r_ecosphere, long double orb_radius)
{
  long double temp = eff_temp(r_ecosphere, orb_radius, GREENHOUSE_TRIGGER_ALBEDO);
  
  if (temp > FREEZING_POINT_OF_WATER)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*-------------------------------------------------------------------------*/
/* This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
/* Earth's Atmosphere" article.  The effective temperature given is in     */
/* units of Kelvin, as is the rise in temperature produced by the          */
/* greenhouse effect, which is returned.                                   */
/* I tuned this by changing a pow(x,.25) to pow(x,.4) to match Venus - JLB */
/*-------------------------------------------------------------------------*/

long double green_rise(long double optical_depth, long double effective_temp, long double surf_pressure)
{
  long double convection_factor = EARTH_CONVECTION_FACTOR * pow(surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS, 0.4);
  long double rise = (pow1_4(1.0 + 0.75 * optical_depth) - 1.0) * effective_temp * convection_factor;
  
  if (rise < 0.0)
  {
    rise = 0.0;
  }
  
  return rise;
}

/*--------------------------------------------------------------------*/
/* The surface temperature passed in is in units of Kelvin.           */
/* The cloud adjustment is the fraction of cloud cover obscuring each */
/* of the three major components of albedo that lie below the clouds. */
/*--------------------------------------------------------------------*/

long double planet_albedo(planet * the_planet)
{
  long double water_fraction, cloud_fraction, ice_fraction, surf_pressure, rock_fraction, cloud_adjustment, components, cloud_part, rock_part, water_part, ice_part;
  
  sun the_sun = the_planet->getTheSun();
  water_fraction = the_planet->getHydrosphere();
  cloud_fraction = the_planet->getCloudCover();
  ice_fraction = the_planet->getIceCover();
  surf_pressure = the_planet->getSurfPressure();
  
  rock_fraction = 1.0 - water_fraction - ice_fraction;
  components = 0.0;
  if (water_fraction > 0.0)
  {
    components += 1.0;
  }
  if (ice_fraction > 0.0)
  {
    components += 1.0;
  }
  if (rock_fraction > 0.0)
  {
    components += 1.0;
  }
  
  cloud_adjustment = cloud_fraction / components;
  
  if (rock_fraction >= cloud_adjustment)
  {
    rock_fraction -= cloud_adjustment;
  }
  else
  {
    rock_fraction = 0.0;
  }
  
  if (water_fraction > cloud_adjustment)
  {
    water_fraction -= cloud_adjustment;
  }
  else
  {
    water_fraction = 0.0;
  }
  
  if (ice_fraction > cloud_adjustment)
  {
    ice_fraction -= cloud_adjustment;
  }
  else
  {
    ice_fraction = 0.0;
  }
  
  cloud_part = cloud_fraction * CLOUD_ALBEDO;		/* about(...,0.2); */
  
  if (surf_pressure == 0.0)
  {
    rock_part = rock_fraction * ROCKY_AIRLESS_ALBEDO;	/* about(...,0.3); */
    ice_part = ice_fraction * AIRLESS_ICE_ALBEDO;		/* about(...,0.4); */
    water_part = 0;
  }
  else
  {
    if (the_planet->getSph() > 0.0 && (is_habitable(the_planet) || (is_potentialy_habitable(the_planet) && (surf_pressure / EARTH_SURF_PRES_IN_MILLIBARS) > 0.25)))
    {
      rock_part = rock_fraction * getPlantLifeAlbedo(the_sun.getSpecType(), the_sun.getLuminosity());
    }
    else
    {
      rock_part = rock_fraction * ROCKY_ALBEDO; /* about(..., 0.1); */
    }
    water_part = water_fraction * WATER_ALBEDO;	/* about(...,0.2); */
    ice_part = ice_fraction * ICE_ALBEDO;		/* about(...,0.1); */
  }
  
  return cloud_part + rock_part + water_part + ice_part;
}

/*---------------------------------------------------------------------*/
/* This function returns the dimensionless quantity of optical depth,  */
/* which is useful in determining the amount of greenhouse effect on a */
/* planet.                                                             */
/*---------------------------------------------------------------------*/

long double opacity(long double molecular_weight, long double surf_pressure)
{
  long double optical_depth;
  
  optical_depth = 0.0;
  if (molecular_weight >= 0.0 && molecular_weight < 10.0)
  {
    optical_depth += 3.0;
  }
  if (molecular_weight >= 10.0 && molecular_weight < 20.0)
  {
    optical_depth += 2.34;
  }
  if (molecular_weight >= 20.0 && molecular_weight < 30.0)
  {
    optical_depth += 1.0;
  }
  if (molecular_weight >= 30.0 && molecular_weight < 45.0)
  {
    optical_depth += 0.15;
  }
  if (molecular_weight >= 45.0 && molecular_weight < 100.0)
  {
    optical_depth += 0.05;
  }
  
  if (surf_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS))
  {
    optical_depth *= 8.333;
  }
  else
  {
    if (surf_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS))
    {
      optical_depth *= 6.666;
    }
    else
    {
      if (surf_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS))
      {
	optical_depth *= 3.333;
      }
      else
      {
	if (surf_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	{
	  optical_depth *= 2.0;
	}
	else
	{
	  if (surf_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS))
	  {
	    optical_depth *= 1.5;
	  }
	}
      }
    }
  }
  
  return optical_depth;
}

/*
 *	calculates the number of years it takes for 1/e of a gas to escape
 *	from a planet's atmosphere. 
 *	Taken from Dole p. 34. He cites Jeans (1916) & Jones (1923)
 */
long double gas_life(long double molecular_weight, planet *the_planet)
{
  long double v = rms_vel(molecular_weight, the_planet->getExosphericTemp());
  long double g = the_planet->getSurfGrav() * EARTH_ACCELERATION;
  long double r = the_planet->getRadius() * CM_PER_KM;
  long double t = (pow3(v) / (2.0 * pow2(g) * r)) * exp((3.0 * g * r) / pow2(v));
  long double years = t / (SECONDS_PER_HOUR * 24.0 * DAYS_IN_A_YEAR);
  
  if (years > 2.0E10)
  {
    years = INCREDIBLY_LARGE_NUMBER;
  }
  
  return years;
}

/*----------------------------------------------------------------*/
/* The temperature calculated is in degrees Kelvin.               */
/* Quantities already known which are used in these calculations: */
/* planet->molec_weight                                           */
/* planet->surf_pressure                                          */
/* R_ecosphere                                                    */
/* planet->a                                                      */
/* planet->volatile_gas_inventory                                 */
/* planet->radius                                                 */
/* planet->boil_point                                             */
/*----------------------------------------------------------------*/

void calculate_surface_temp(planet *the_planet, bool first, long double last_water, long double last_clouds, long double last_ice, long double last_temp, long double last_albedo, bool do_gasses)
{
  long double effective_temp;
  long double water_raw;
  long double clouds_raw;
  long double greenhouse_temp;
  bool boil_off = false;
  sun the_sun = the_planet->getTheSun();
  long double the_fudged_radius = fudged_radius(the_planet->getMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet);
  
  do_gasses = (flags_arg_clone & fDoGases) != 0;
  
  if (first)
  {
    if (!is_gas_planet(the_planet))
    {
      the_planet->setAlbedo(EARTH_ALBEDO);
    }
    
    effective_temp = eff_temp(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), the_planet->getAlbedo());
    greenhouse_temp = green_rise(opacity(the_planet->getMolecWeight(), the_planet->getSurfPressure()), effective_temp, the_planet->getSurfPressure());
    the_planet->setSurfTemp(effective_temp + greenhouse_temp);
    set_temp_range(the_planet);
  }
  
  if (the_planet->getGreenhouseEffect() && the_planet->getMaxTemp() < the_planet->getBoilPoint())
  {
    if (flag_verbose & 0x0010)
    {
      cerr << "Deluge: " << the_planet->getTheSun().getName() << " " << the_planet->getPlanetNo() << " max (" << toString(the_planet->getMaxTemp()) << ") < boil (" << toString(the_planet->getBoilPoint()) << ")" << endl;
    }
    
    the_planet->setGreenhouseEffect(false);
    
    //the_planet->setVolatileGasInventory(vol_inventory(the_planet->getMass(), the_planet->getEscVelocity(), the_planet->getRmsVelocity(), the_planet->getTheSun().getMass(), the_planet->getOrbitZone(), the_planet->getGreenhouseEffect(), the_planet->getGasMass() > 0.0));
    long double fudged_escape_velocity = escape_vel(the_planet->getMass(), the_fudged_radius);
    the_planet->setVolatileGasInventory(vol_inventory(the_planet->getMass(), fudged_escape_velocity, the_planet->getRmsVelocity(), the_planet->getTheSun().getMass(), the_planet->getOrbitZone(), the_planet->getGreenhouseEffect(), the_planet->getGasMass() > 0.0));
    the_planet->setSurfPressure(pressure(the_planet->getVolatileGasInventory(), the_fudged_radius, the_planet->getSurfGrav()));
    //the_planet->setSurfPressure(pressure(the_planet->getVolatileGasInventory(), the_planet->getRadius(), the_planet->getSurfGrav()));
    
    the_planet->setBoilPoint(boiling_point(the_planet->getBoilPoint()));
  }
  
  //water_raw = hydro_fraction(the_planet->getVolatileGasInventory(), the_planet->getRadius());
  water_raw = hydro_fraction(the_planet->getVolatileGasInventory(), the_fudged_radius);
  the_planet->setHydrosphere(water_raw);
  //clouds_raw = cloud_fraction(the_planet->getSurfTemp(), the_planet->getMolecWeight(), the_planet->getRadius(), the_planet->getHydrosphere());
  clouds_raw = cloud_fraction(the_planet->getSurfTemp(), the_planet->getMolecWeight(), the_fudged_radius, the_planet->getHydrosphere());
  the_planet->setCloudCover(clouds_raw);
  the_planet->setIceCover(ice_fraction(the_planet->getHydrosphere(), the_planet->getSurfTemp()));
  if (the_planet->getImf() > 0.1 && the_planet->getRadius() >= round_threshold(the_planet->getDensity()) && the_planet->getA() >= habitable_zone_distance(the_sun, MAXIMUM_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
  {
    the_planet->setIceCover(1.0);
  }
  else if (the_planet->getImf() && the_planet->getRadius() < round_threshold(the_planet->getDensity()) && the_planet->getA() >= habitable_zone_distance(the_sun, MAXIMUM_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
  {
    the_planet->setIceCover(the_planet->getIceCover() + the_planet->getImf());
  }
  
  if (the_planet->getGreenhouseEffect() && the_planet->getSurfPressure() > 0.0)
  {
    the_planet->setCloudCover(1.0);
  }
  
  if ((the_planet->getHighTemp() >= the_planet->getBoilPoint() && !first && !((int)the_planet->getDay() == (int)(the_planet->getOrbPeriod() * 24.0) || the_planet->getResonantPeriod())) || (the_planet->getMinTemp() >= the_planet->getBoilPoint() && !first))
  {
    the_planet->setHydrosphere(0.0);
    boil_off = true;
    
    if (the_planet->getMolecWeight() > WATER_VAPOR)
    {
      the_planet->setCloudCover(0.0);
    }
    else
    {
      the_planet->setCloudCover(1.0);
    }
  }
  
  if (the_planet->getSurfTemp() < (FREEZING_POINT_OF_WATER - 3.0))
  {
    the_planet->setHydrosphere(0.0);
  }
  
  the_planet->setHzc(calcHzc(the_planet));
  the_planet->setHza(calcHza(the_planet));
  the_planet->setEsi(calcEsi(the_planet));
  the_planet->setSph(calcSph(the_planet));
  
  if (!is_gas_planet(the_planet))
  {
    if (do_gasses)
    {
      calculate_gases(the_sun, the_planet, "");
    }
    the_planet->setAlbedo(planet_albedo(the_planet));
  }
  effective_temp = eff_temp(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), the_planet->getAlbedo());
  greenhouse_temp = green_rise(opacity(the_planet->getMolecWeight(), the_planet->getSurfPressure()), effective_temp, the_planet->getSurfPressure());
  the_planet->setSurfTemp(effective_temp + greenhouse_temp);
  
  if (!first)
  {
    if (!boil_off)
    {
      the_planet->setHydrosphere((the_planet->getHydrosphere() + (last_water * 2.0)) / 3.0);
    }
    the_planet->setCloudCover((the_planet->getCloudCover() + (last_clouds * 2.0)) / 3.0);
    the_planet->setIceCover((the_planet->getIceCover() + (last_ice * 2.0)) / 3.0);
    the_planet->setAlbedo((the_planet->getAlbedo() + (last_albedo * 2.0)) / 3.0);
    the_planet->setSurfTemp((the_planet->getSurfTemp() + (last_temp * 2.0)) / 3);
  }
  
  set_temp_range(the_planet);
  
  if (flag_verbose & 0x0020)
  {
    string greenhouse_string = "";
    if (the_planet->getGreenhouseEffect())
    {
      greenhouse_string = "*";
    }
    cerr << toString(the_planet->getA()) << " AU: " << toString(the_planet->getSurfTemp() - FREEZING_POINT_OF_WATER) << " = " << toString(effective_temp - FREEZING_POINT_OF_WATER) << " ef + " << toString(greenhouse_temp) << " gh" << greenhouse_string << " (W: " << toString(the_planet->getHydrosphere()) << " (" << toString(water_raw) << ") C: " << toString(the_planet->getCloudCover()) << " (" << toString(clouds_raw) << ") I: " << toString(the_planet->getIceCover()) << " A: (" << toString(the_planet->getAlbedo()) << "))" << endl;
  }
}

void iterate_surface_temp(planet* the_planet, bool do_gasses)
{
  int count = 0;
  long double initial_temp = est_temp(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), the_planet->getAlbedo());
  
  long double h2_life = gas_life(MOL_HYDROGEN, the_planet);
  long double h2o_life = gas_life(WATER_VAPOR, the_planet);
  long double n2_life = gas_life(MOL_NITROGEN, the_planet);
  long double n_life = gas_life(ATOMIC_NITROGEN, the_planet);
  
  do_gasses = (flags_arg_clone & fDoGases) != 0;
  
  if (flag_verbose & 0x20000)
  {
    cerr << the_planet->getPlanetNo() << ":                     " << toString(initial_temp) << " it [" << toString(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES)) << " re " << toString(the_planet->getA()) << " a " << toString(the_planet->getAlbedo()) << " alb]" << endl;
  }
  
  if (flag_verbose & 0x0040)
  {
    cerr << endl << "Gas lifetimes: H2 - " << toString(h2_life) << ", H2O - " << toString(h2o_life) << ", N - " << toString(n_life) << ", N2 - " << toString(n2_life) << endl;
  }
  
  calculate_surface_temp(the_planet, true, 0, 0, 0, 0, 0, do_gasses);
  
  for (count = 0; count <= 25; count++)
  {
    long double last_water = the_planet->getHydrosphere();
    long double last_clouds = the_planet->getCloudCover();
    long double last_ice = the_planet->getIceCover();
    long double last_temp = the_planet->getSurfTemp();
    long double last_albedo = the_planet->getAlbedo();
    
    calculate_surface_temp(the_planet, false, last_water, last_clouds, last_ice, last_temp, last_albedo, do_gasses);
    
    if (fabs(the_planet->getSurfTemp() - last_temp) < 0.25)
    {
      break;
    }
  }
  
  the_planet->setGreenhsRise(the_planet->getSurfTemp() - initial_temp);
  
  if (flag_verbose & 0x20000)
  {
    cerr << the_planet->getPlanetNo() << ": " << toString(the_planet->getGreenhsRise()) << " gh = " << toString(the_planet->getSurfTemp()) << " (" << toString(the_planet->getSurfTemp() - FREEZING_POINT_OF_WATER) << " C) st - " << toString(initial_temp) << " it [" << toString(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES)) << " re " << toString(the_planet->getA()) << " a " << toString(the_planet->getAlbedo()) << " alb]" << endl;
  }
}

/*----------------------------------------------------------------------*/
/* Inspired partial pressure, taking into account humidification of the */
/* air in the nasal passage and throat This formula is on Dole's p. 14  */
/*----------------------------------------------------------------------*/

long double inspired_partial_pressure(long double surf_pressure, long double gas_pressure)
{
  long double pH2O = (H20_ASSUMED_PRESSURE);
  long double fraction = gas_pressure / surf_pressure;
  
  return	(surf_pressure - pH2O) * fraction;
}

/*------------------------------------------------------------------------*/
/* This function uses figures on the maximum inspired partial pressures   */
/* of Oxygen, other atmospheric and traces gases as laid out on pages 15, */
/* 16 and 18 of Dole's Habitable Planets for Man to derive breathability  */
/* of the planet's atmosphere. JLB                                        */
/*------------------------------------------------------------------------*/

unsigned int breathability(planet *the_planet)
{
  bool nitrogen_ok = false;
  bool oxygen_ok = false;
  bool co2_ok = false;
  
  if (the_planet->getNumGases() == 0)
  {
    return NONE;
  }
  
  for (int i = 0; i < the_planet->getNumGases(); i++)
  {
    int gas_no = 0;
    
    long double ipp = inspired_partial_pressure(the_planet->getSurfPressure(), the_planet->getGas(i).getSurfPressure());
    for (int j = 0; j < gases.count(); j++)
    {
      if (gases[j].getNum() == the_planet->getGas(i).getNum())
      {
	gas_no = j;
	break;
      }
    }
    
    if (ipp > gases[gas_no].getMaxIpp())
    {
      return POISONOUS;
    }
    
    if (the_planet->getGas(i).getNum() == AN_N)
    {
      nitrogen_ok = ipp >= gases[gas_no].getMinIpp() && ipp <= gases[gas_no].getMaxIpp();
    }
    else if (the_planet->getGas(i).getNum() == AN_O)
    {
      oxygen_ok = ipp >= gases[gas_no].getMinIpp() && ipp <= gases[gas_no].getMaxIpp();
    }
    else if (the_planet->getGas(i).getNum() == AN_CO2)
    {
      co2_ok = ipp >= gases[gas_no].getMinIpp() && ipp <= gases[gas_no].getMaxIpp();
    }
  }
  
  if (nitrogen_ok && oxygen_ok && co2_ok)
  {
    return BREATHABLE;
  }
  else
  {
    return UNBREATHABLE;
  }
}

void set_temp_range(planet *the_planet)
{
  long double pressmod = 1 / sqrt(1 + 20 * the_planet->getSurfPressure() / 1000.0);
  long double ppmod = 1 / sqrt(10 + 5 * the_planet->getSurfPressure() / 1000.0);
  long double tiltmod = fabs(cos(the_planet->getAxialTilt() * PI / 180) * pow(1 + the_planet->getE(), 2));
  long double daymod = 1 / (200 / the_planet->getDay() + 1);
  long double mh = pow(1 + daymod, pressmod);
  long double ml = pow(1 - daymod, pressmod);
  long double hi = mh * the_planet->getSurfTemp();
  long double lo = ml * the_planet->getSurfTemp();
  long double sh = hi + pow((100 + hi) * tiltmod, sqrt(ppmod));
  long double wl = lo - pow((150 + lo) * tiltmod, sqrt(ppmod));
  long double max = the_planet->getSurfTemp() + sqrt(the_planet->getSurfTemp()) * 10;
  long double min = the_planet->getSurfTemp() / sqrt(the_planet->getDay() + 24);
  
  if (lo < min)
  {
    lo = min;
  }
  if (wl < 0)
  {
    wl = 0;
  }
  
  the_planet->setHighTemp(soft(hi, max, min));
  the_planet->setLowTemp(soft(lo, max, min));
  the_planet->setMaxTemp(soft(sh, max, min));
  the_planet->setMinTemp(soft(wl, max, min));
}


long double getSpinResonanceFactor(long double eccentricity)
{
  long double top = 1.0 - eccentricity;
  long double bottom = 1.0 + eccentricity;
  long double fraction = top / bottom;
  if (fraction <= AVE(1.0/10.0, 1.0/9.0))
  {
    return 1.0/10.0;
  }
  else if (fraction <= AVE(1.0/9.0, 1.0/8.0))
  {
    return 1.0/9.0;
  }
  else if (fraction <= AVE(1.0/8.0, 1.0/7.0))
  {
    return 1.0/8.0;
  }
  else if (fraction <= AVE(1.0/7.0, 1.0/6.0))
  {
    return 1.0/7.0;
  }
  else if (fraction <= AVE(1.0/6.0, 1.0/5.0))
  {
    return 1.0/6.0;
  }
  else if (fraction <= AVE(1.0/5.0, 2.0/9.0))
  {
    return 1.0/5.0;
  }
  else if (fraction <= AVE(2.0/9.0, 1.0/4.0))
  {
    return 2.0/9.0;
  }
  else if (fraction <= AVE(1.0/4.0, 2.0/7.0))
  {
    return 1.0/4.0;
  }
  else if (fraction <= AVE(2.0/7.0, 3.0/10.0))
  {
    return 2.0/7.0;
  }
  else if (fraction <= AVE(3.0/10.0, 1.0/3.0))
  {
    return 3.0/10.0;
  }
  else if (fraction <= AVE(1.0/3.0, 3.0/8.0))
  {
    return 1.0/3.0;
  }
  else if (fraction <= AVE(3.0/8.0, 2.0/5.0))
  {
    return 3.0/8.0;
  }
  else if (fraction <= AVE(2.0/5.0, 3.0/7.0))
  {
    return 2.0/5.0;
  }
  else if (fraction <= AVE(3.0/7.0, 4.0/9.0))
  {
    return 3.0/7.0;
  }
  else if (fraction <= AVE(4.0/9.0, 1.0/2.0))
  {
    return 4.0/9.0;
  }
  else if (fraction <= AVE(1.0/2.0, 5.0/9.0))
  {
    return 1.0/2.0;
  }
  else if (fraction <= AVE(5.0/9.0, 4.0/7.0))
  {
    return 5.0/9.0;
  }
  else if (fraction <= AVE(4.0/7.0, 3.0/5.0))
  {
    return 4.0/7.0;
  }
  else if (fraction <= AVE(3.0/5.0, 5.0/8.0))
  {
    return 3.0/5.0;
  }
  else if (fraction <= AVE(5.0/8.0, 2.0/3.0))
  {
    return 5.0/8.0;
  }
  else if (fraction <= AVE(2.0/3.0, 7.0/10.0))
  {
    return 2.0/3.0;
  }
  else if (fraction <= AVE(7.0/10.0, 5.0/7.0))
  {
    return 7.0/10.0;
  }
  else if (fraction <= AVE(5.0/7.0, 3.0/4.0))
  {
    return 5.0/7.0;
  }
  else if (fraction <= AVE(3.0/4.0, 7.0/9.0))
  {
    return 3.0/4.0;
  }
  else if (fraction <= AVE(7.0/9.0, 4.0/5.0))
  {
    return 7.0/9.0;
  }
  else if (fraction <= AVE(4.0/5.0, 5.0/6.0))
  {
    return 4.0/5.0;
  }
  else if (fraction <= AVE(5.0/6.0, 6.0/7.0))
  {
    return 5.0/6.0;
  }
  else if (fraction <= AVE(6.0/7.0, 7.0/8.0))
  {
    return 6.0/7.0;
  }
  else if (fraction <= AVE(7.0/8.0, 8.0/9.0))
  {
    return 7.0/8.0;
  }
  else if (fraction <= AVE(8.0/9.0, 9.0/10.0))
  {
    return 8.0/9.0;
  }
  else
  {
    return 9.0/10.0;
  }
}

long double radius_improved(long double mass, long double imf, long double rmf, long double cmf, bool giant, int zone, planet *the_planet)
{
  long double non_ice_rock_radius = 0.0;;
  long double ice_rock_radius = 0.0;
  long double ice_iron_radius = 0.0;
  long double radius = 0.0;
  long double radius1 = 0.0;
  long double radius2 = 0.0;
  map<long double, long double> non_ice_rock_radii;
  map<long double, long double> ice_rock_radii;
  map<long double, long double> ice_iron_radii;
  long double range, upper_fraction, lower_fraction;
  long double half_mass_factor = 0.0;
  long double iron_ratio = 0.0;
  if (imf < 1.0)
  {
    iron_ratio = (1.0 - imf - rmf) / (1.0 - imf);
  }
  long double average = 0.0;
  mass *= SUN_MASS_IN_EARTH_MASSES;
  if (mass == 0.0)
  {
    mass = PROTOPLANET_MASS;
  }
  non_ice_rock_radii[0.0] = iron_radius(mass, the_planet, solid_iron);
  non_ice_rock_radii[0.5] = half_rock_half_iron_radius(mass, cmf, the_planet, solid_half_rock_half_iron);
  non_ice_rock_radii[1.0] = rock_radius(mass, cmf, the_planet, solid_rock);
  if (imf > 0.0)
  {
    ice_rock_radii[0.0] = rock_radius(mass, cmf, the_planet, solid_rock);
    ice_rock_radii[0.5] = half_rock_half_water_radius(mass, cmf, the_planet, solid_half_rock_half_water);
    ice_rock_radii[0.75] = one_quater_rock_three_fourths_water_radius(mass, cmf, the_planet, solid_one_quater_rock_three_fourths_water);
    ice_rock_radii[1.0] = water_radius(mass, the_planet, solid_water);
    if (imf < 0.5)
    {
      ice_rock_radius = planet_radius_helper(imf, 0.0, ice_rock_radii[0.0], 0.5, ice_rock_radii[0.5], 0.75, ice_rock_radii[0.75], false);
    }
    else if (imf < 0.75)
    {
      //cout << "test1" << endl;
      //cout << toString(mass) << endl;
      radius1 = planet_radius_helper(imf, 0.0, ice_rock_radii[0.0], 0.5, ice_rock_radii[0.5], 0.75, ice_rock_radii[0.75], false);
      radius2 = planet_radius_helper(imf, 0.5, ice_rock_radii[0.5], 0.75, ice_rock_radii[0.75], 1.0, ice_rock_radii[1.0], false);
      ice_rock_radius = rangeAdjust(imf, radius1, radius2, 0.5, 0.75);
    }
    else
    {
      //cout << "test2" << endl;
      //cout << toString(mass) << endl;
      radius1 = planet_radius_helper(imf, 0.5, ice_rock_radii[0.5], 0.75, ice_rock_radii[0.75], 1.0, ice_rock_radii[1.0], false);
      radius2 = planet_radius_helper2(imf, 0.75, ice_rock_radii[0.75], 1.0, ice_rock_radii[1.0]);
      ice_rock_radius = rangeAdjust(imf, radius1, radius2, 0.75, 1.0);
    }
    ice_iron_radii[0.0] = iron_radius(mass, the_planet, solid_iron);
    ice_iron_radii[0.047] = solid_0point953_iron_0point047_water_radius(mass, the_planet, solid_0point953_iron_0point047_water);
    ice_iron_radii[0.49] = solid_0point51_iron_0point49_water_radius(mass, the_planet, solid_0point51_iron_0point49_water);
    ice_iron_radii[0.736] = solid_0point264_iron_0point736_water_radius(mass, the_planet, solid_0point264_iron_0point736_water);
    ice_iron_radii[1.0] = ice_rock_radii[1.0];
    if (imf < 0.047)
    {
      ice_iron_radius = planet_radius_helper(imf, 0.0, ice_iron_radii[0.0], 0.047, ice_iron_radii[0.047], 0.49, ice_iron_radii[0.49], false);
    }
    else if (imf < 0.49)
    {
      radius1 = planet_radius_helper(imf, 0.0, ice_iron_radii[0.0], 0.047, ice_iron_radii[0.047], 0.49, ice_iron_radii[0.49], false);
      radius2 = planet_radius_helper(imf, 0.047, ice_iron_radii[0.047], 0.49, ice_iron_radii[0.49], 0.736, ice_iron_radii[0.736], false);
      ice_iron_radius = rangeAdjust(imf, radius1, radius2, 0.047, 0.49);
    }
    else if (imf < 0.736)
    {
      radius1 = planet_radius_helper(imf, 0.047, ice_iron_radii[0.047], 0.49, ice_iron_radii[0.49], 0.736, ice_iron_radii[0.736], false);
      radius2 = planet_radius_helper(imf, 0.49, ice_iron_radii[0.49], 0.736, ice_iron_radii[0.736], 1.0, ice_iron_radii[1.0], false);
      ice_iron_radius = rangeAdjust(imf, radius1, radius2, 0.49, 0.736);
    }
    else
    {
      radius1 = planet_radius_helper(imf, 0.49, ice_iron_radii[0.49], 0.736, ice_iron_radii[0.736], 1.0, ice_iron_radii[1.0], false);
      radius2 = planet_radius_helper2(imf, 0.736, ice_iron_radii[0.736], 1.0, ice_iron_radii[1.0]);
      ice_iron_radius = rangeAdjust(imf, radius1, radius2, 0.736, 1.0);
    }
    half_mass_factor = 1.0;
    if (mass > 0.0)
    {
      average = AVE(non_ice_rock_radii[0.0], non_ice_rock_radii[1.0]);
      half_mass_factor = non_ice_rock_radii[0.5] / average;
    }
    radius = planet_radius_helper(iron_ratio, 0.0, ice_rock_radius, 0.5, AVE(ice_rock_radius, ice_iron_radius) * half_mass_factor, 1.0, ice_iron_radius, false);
  }
  else
  {
    if (rmf < 0.5)
    {
      non_ice_rock_radius = planet_radius_helper(rmf, 0.0, non_ice_rock_radii[0.0], 0.5, non_ice_rock_radii[0.5], 1.0, non_ice_rock_radii[1.0], false);
    }
    else
    {
      radius1 = planet_radius_helper(rmf, 0.0, non_ice_rock_radii[0.0], 0.5, non_ice_rock_radii[0.5], 1.0, non_ice_rock_radii[1.0], false);
      radius2 = planet_radius_helper2(rmf, 0.5, non_ice_rock_radii[0.5], 1.0, non_ice_rock_radii[1.0]);
      non_ice_rock_radius = rangeAdjust(rmf, radius1, radius2, 0.5, 1.0);
    }
    radius = non_ice_rock_radius;
  }
  radius *= KM_EARTH_RADIUS;
  return radius;
}

long double fudged_radius(long double mass, long double imf, long double rmf, long double cmf, bool giant, int zone, planet *the_planet)
{
  long double range, upper_fraction, lower_fraction, non_ice_rock_radius, ice_rock_radius, radius;
  mass *= SUN_MASS_IN_EARTH_MASSES;
  if (rmf <= 0.5)
  {
    range = 0.5 - 0.0;
    upper_fraction = rmf / range;
    lower_fraction = 1.0 - upper_fraction;
    non_ice_rock_radius = (upper_fraction * half_rock_half_iron_radius(mass, cmf, the_planet, solid_half_rock_half_iron)) + (lower_fraction * iron_radius(mass, the_planet, solid_iron));
  }
  else
  {
    range = 1.0 - 0.5;
    rmf += quad_trend(-3, 4.5, -1.5, rmf);
    upper_fraction = (rmf - 0.5) / range;
    lower_fraction = 1.0 - upper_fraction;
    non_ice_rock_radius = (upper_fraction * rock_radius(mass, cmf, the_planet, solid_rock)) + (lower_fraction * half_rock_half_iron_radius(mass, cmf, the_planet, solid_half_rock_half_iron));
  }
  
  if (imf <= 0.5)
  {
    range = 0.5 - 0.0;
    upper_fraction = imf / range;
    lower_fraction = 1.0 - upper_fraction;
    ice_rock_radius = (upper_fraction * half_rock_half_water_radius(mass, cmf, the_planet, solid_half_rock_half_water)) + (lower_fraction * rock_radius(mass, cmf, the_planet, solid_rock));
  }
  else if (imf <= 0.75)
  {
    range = 0.75 - 0.5;
    upper_fraction = (imf - 0.5) / range;
    lower_fraction = 1.0 - upper_fraction;
    ice_rock_radius = (upper_fraction * one_quater_rock_three_fourths_water_radius(mass, cmf, the_planet, solid_one_quater_rock_three_fourths_water)) + (lower_fraction * half_rock_half_water_radius(mass, cmf, the_planet, solid_half_rock_half_water));
  }
  else
  {
    range = 1.0 - 0.75;
    upper_fraction = (imf - 0.75) / range;
    lower_fraction = 1.0 - upper_fraction;
    ice_rock_radius = (upper_fraction * water_radius(mass, the_planet, solid_water)) + (lower_fraction * one_quater_rock_three_fourths_water_radius(mass, cmf, the_planet, solid_one_quater_rock_three_fourths_water));
  }
  radius = (ice_rock_radius * imf) + (non_ice_rock_radius * (1.0 - imf));
  radius *= KM_EARTH_RADIUS;
  return radius;
}

long double gas_radius(long double temperature, long double core_mass, long double total_mass, long double star_age, planet *the_planet)
{
  long double jupiter_radii = 0.0;
  long double jupiter_radii1 = 0.0;
  long double jupiter_radii2 = 0.0;
  long double core_earth_masses = core_mass * SUN_MASS_IN_EARTH_MASSES;
  long double total_earth_masses = total_mass * SUN_MASS_IN_EARTH_MASSES;
  long double lower_fraction = 0.0;
  long double upper_fraction = 0.0;
  long double range = 0.0;
  long double radius;
  map<int, long double> age_radii;
  age_radii[300.0E6] = gas_radius_300Myr(temperature, core_earth_masses, total_earth_masses, the_planet);
  age_radii[1.0E9] = gas_radius_1Gyr(temperature, core_earth_masses, total_earth_masses, the_planet);
  age_radii[4.5E9] = gas_radius_4point5Gyr(temperature, core_earth_masses, total_earth_masses, the_planet);
  /*if (star_age < 300.0E6)
  {
    upper_fraction = 300.0E6 / star_age;
    jupiter_radii = gas_radius_300Myr(temperature, core_earth_masses, total_earth_masses, the_planet) * sqrt(upper_fraction);
  }
  else if (star_age < 1.0E9)
  {
    range = 1.0E9 - 300.0E6;
    upper_fraction = (star_age - 300.0E6) / range;
    lower_fraction = 1.0 - upper_fraction;
    jupiter_radii = (lower_fraction * gas_radius_300Myr(temperature, core_earth_masses, total_earth_masses, the_planet)) + (upper_fraction * gas_radius_1Gyr(temperature, core_earth_masses, total_earth_masses, the_planet));
  }
  else if (star_age < 4.5E9)
  {
    range = 4.5E9 - 1.0E9;
    upper_fraction = (star_age - 4.5E9) / range;
    lower_fraction = 1.0 - upper_fraction;
    jupiter_radii = (lower_fraction * gas_radius_1Gyr(temperature, core_earth_masses, total_earth_masses, the_planet)) + (upper_fraction * gas_radius_4point5Gyr(temperature, core_earth_masses, total_earth_masses, the_planet));
  }
  else
  {
    jupiter_radii = gas_radius_4point5Gyr(temperature, core_earth_masses, total_earth_masses, the_planet);
  }*/
  /*if (star_age < 300.0E6)
  {
    jupiter_radii = planet_radius_helper2(star_age, 300.0E6, age_radii[300.0E6], 1.0E9, age_radii[1.0E9]);
  }
  else */if (star_age < 1.0E9)
  {
    //jupiter_radii1 = planet_radius_helper2(star_age, 300.0E6, age_radii[300.0E6], 1.0E9, age_radii[1.0E9]);
    //jupiter_radii2 = planet_radius_helper(star_age, 300.0E6, age_radii[300.0E6], 1.0E9, age_radii[1.0E9], 4.5E9, age_radii[4.5E9], false);
    //jupiter_radii = rangeAdjust(star_age, jupiter_radii1, jupiter_radii2, 300.0E6, 1.0E9);
    jupiter_radii = planet_radius_helper(star_age, 300.0E6, age_radii[300.0E6], 1.0E9, age_radii[1.0E9], 4.5E9, age_radii[4.5E9], false);
  }
  else if (star_age < 4.5E9)
  {
    jupiter_radii1 = planet_radius_helper(star_age, 300.0E6, age_radii[300.0E6], 1.0E9, age_radii[1.0E9], 4.5E9, age_radii[4.5E9], false);
    jupiter_radii2 = planet_radius_helper2(star_age, 1.0E9, age_radii[1.0E9], 4.5E9, age_radii[4.5E9]);
    jupiter_radii = rangeAdjust(star_age, jupiter_radii1, jupiter_radii2, 1.0E9, 4.5E9);
  }
  else
  {
    jupiter_radii = planet_radius_helper2(star_age, 1.0E9, age_radii[1.0E9], 4.5E9, age_radii[4.5E9]);
  }
  radius = jupiter_radii * KM_JUPITER_RADIUS;
  
  if (total_earth_masses < 10)
  {
    range = 10.0 - 0.0;
    upper_fraction = pow2((10.0 - total_earth_masses) / range);
    lower_fraction = 1.0 - upper_fraction;
    radius = (lower_fraction * radius) + (upper_fraction * gas_dwarf_radius(the_planet));
  }
  return radius;
}

long double round_threshold(long double density)
{
  return (170.0 * sqrt(ultimateStrength(density)) * pow(density, -1.0)) / 2.0;
}

long double ultimateStrength(long double density)
{
  if (density < 2.5)
  {
    return 1.046601879 * pow(4.294487989, density);
  }
  else
  {
    return 13.50087381 * pow(1.54411359, density);
  }
}

long double calc_stellar_flux(long double a, long double b, long double c, long double d, long double seff, long double star_temp, long double star_lum)
{
  long double t = star_temp - 5780.0;
  //cout << star_temp << endl;
  return (seff) + (a * t) + (b * pow(t, 2.0)) + (c * pow(t, 3.0)) + (d * pow(t, 4.0));
}

long double habitable_zone_distance_helper(long double effTemp, long double luminosity, int mode, long double mass)
{
  long double stellar_flux = 0;
  long double a, b, c, d, seff;
  long double stellar_flux_green1, stellar_flux_green2, stellar_flux_moist1, stellar_flux_earth1, stellar_flux_max1, stellar_flux_max2, diff, percent, temp;
  
  if (mass < 0.1)
  {
    mass = 0.1;
  }
  else if (mass > 10.0)
  {
    mass = 10.0;
  }
  
  a = b = c = d = seff = 0.0;
  if (mode == RECENT_VENUS)
  {
    //stellar_flux = calc_stellar_flux(1.4316E-4, 2.9875E-9, -7.5702E-12, -1.1635E-15, 1.7753, effTemp, luminosity);
    stellar_flux = calc_stellar_flux(2.136E-4, 2.533E-8, -1.332E-11, -3.097E-15, 1.776, effTemp, luminosity);
  }
  else if (mode == RUNAWAY_GREENHOUSE)
  {
    //stellar_flux = calc_stellar_flux(1.3242E-4, 1.5418E-8, -7.9895E-12, -1.8328E-15, 1.0512, effTemp, luminosity);
    if (mass < 1.0)
    {
      a = planet_radius_helper(mass, 0.1, 1.209E-4, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper(mass, 0.1, 1.404E-8, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper(mass, 0.1, -7.418E-12, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper(mass, 0.1, -1.713E-15, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper(mass, 0.1, 0.99, 1.0, 1.107, 5.0, 1.188);
    }
    else
    {
      a = planet_radius_helper2(mass, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper2(mass, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper2(mass, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper2(mass, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper2(mass, 1.0, 1.107, 5.0, 1.188);
    }
    stellar_flux = calc_stellar_flux(a, b, c, d, seff, effTemp, luminosity);
  }
  else if (mode == MOIST_GREENHOUSE)
  {
    //stellar_flux = calc_stellar_flux(8.1774E-5, 1.7063E-9, -4.3241E-12, -6.6462E-16, 1.0140, effTemp, luminosity);
    stellar_flux_green1 = calc_stellar_flux(1.332E-4, 1.58E-8, -8.308E-12, -1.931E-15, 1.107, effTemp, luminosity);
    stellar_flux_moist1 = calc_stellar_flux(8.1774E-5, 1.7063E-9, -4.3241E-12, -6.6462E-16, 1.0140, effTemp, luminosity);
    stellar_flux_max1 = calc_stellar_flux(5.8942E-5, 1.6558E-9, -3.0045E-12, -5.2983E-16, 0.3438, effTemp, luminosity);
    diff = stellar_flux_green1 - stellar_flux_max1;
    percent = (stellar_flux_green1 - stellar_flux_moist1) / diff;
    if (mass < 1.0)
    {
      a = planet_radius_helper(mass, 0.1, 1.209E-4, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper(mass, 0.1, 1.404E-8, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper(mass, 0.1, -7.418E-12, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper(mass, 0.1, -1.713E-15, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper(mass, 0.1, 0.99, 1.0, 1.107, 5.0, 1.188);
    }
    else
    {
      a = planet_radius_helper2(mass, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper2(mass, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper2(mass, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper2(mass, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper2(mass, 1.0, 1.107, 5.0, 1.188);
    }
    stellar_flux_green2 = calc_stellar_flux(a, b, c, d, seff, effTemp, luminosity);
    stellar_flux_max2 = calc_stellar_flux(6.171E-5, 1.698E-9, -3.198E-12, -5.575E-16, 0.356, effTemp, luminosity);
    diff = stellar_flux_green2 - stellar_flux_max2;
    temp = diff * percent;
    stellar_flux = stellar_flux_green2 - (temp * diff);
  }
  else if (mode == EARTH_LIKE)
  {
    //stellar_flux = calc_stellar_flux(8.3104E-5, 1.7677E-9, -4.39E-12, -6.79E-16, 1.0, effTemp, luminosity);
    stellar_flux_green1 = calc_stellar_flux(1.332E-4, 1.58E-8, -8.308E-12, -1.931E-15, 1.107, effTemp, luminosity);
    stellar_flux_earth1 = calc_stellar_flux(8.3104E-5, 1.7677E-9, -4.39E-12, -6.79E-16, 1.0, effTemp, luminosity);
    stellar_flux_max1 = calc_stellar_flux(5.8942E-5, 1.6558E-9, -3.0045E-12, -5.2983E-16, 0.3438, effTemp, luminosity);
    diff = stellar_flux_green1 - stellar_flux_max1;
    percent = (stellar_flux_green1 - stellar_flux_earth1) / diff;
    if (mass < 1.0)
    {
      a = planet_radius_helper(mass, 0.1, 1.209E-4, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper(mass, 0.1, 1.404E-8, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper(mass, 0.1, -7.418E-12, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper(mass, 0.1, -1.713E-15, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper(mass, 0.1, 0.99, 1.0, 1.107, 5.0, 1.188);
    }
    else
    {
      a = planet_radius_helper2(mass, 1.0, 1.332E-4, 5.0, 1.433E-4);
      b = planet_radius_helper2(mass, 1.0, 1.58E-8, 5.0, 1.707E-8);
      c = planet_radius_helper2(mass, 1.0, -8.308E-12, 5.0, -8.968E-12);
      d = planet_radius_helper2(mass, 1.0, -1.931E-15, 5.0, -2.084E-15);
      seff = planet_radius_helper2(mass, 1.0, 1.107, 5.0, 1.188);
    }
    stellar_flux_green2 = calc_stellar_flux(a, b, c, d, seff, effTemp, luminosity);
    stellar_flux_max2 = calc_stellar_flux(6.171E-5, 1.698E-9, -3.198E-12, -5.575E-16, 0.356, effTemp, luminosity);
    diff = stellar_flux_green2 - stellar_flux_max2;
    temp = diff * percent;
    stellar_flux = stellar_flux_green2 - (temp * diff);
  }
  else if (mode == FIRST_CO2_CONDENSATION_LIMIT)
  {
    stellar_flux = calc_stellar_flux(4.4499e-5, 1.4065e-10, 2.2750e-12, -3.3509e-16, 0.5408, effTemp, luminosity);
  }
  else if (mode == MAXIMUM_GREENHOUSE)
  {
    //stellar_flux = calc_stellar_flux(5.8942E-5, 1.6558E-9, -3.0045E-12, -5.2983E-16, 0.3438, effTemp, luminosity);
    stellar_flux = calc_stellar_flux(6.171E-5, 1.698E-9, -3.198E-12, -5.575E-16, 0.356, effTemp, luminosity);
  }
  else if (mode == EARLY_MARS)
  {
    //stellar_flux = calc_stellar_flux(5.4513E-5, 1.5313E-9, -2.7786E-12, -4.8997E-16, 0.3179, effTemp, luminosity);
    stellar_flux = calc_stellar_flux(5.547E-5, 1.526E-9, -2.874E-12, -5.011E-16, 0.32, effTemp, luminosity);
  }
  else if (mode == TWO_AU_CLOUD_LIMIT)
  {
    stellar_flux = calc_stellar_flux(4.2588e-5, 1.1963e-9, -2.1709e-12, -3.8282e-16, 0.2484, effTemp, luminosity);
  }
  return stellar_flux;
}

long double habitable_zone_distance(sun &the_sun, int mode, long double mass)
{
  long double stellar_flux = 0;
  //long double stellar_flux2 = 0;
  //long double combined_stellar_flux = 0;
  if (the_sun.getEffTemp() >= 2600 && the_sun.getEffTemp() <= 7200)
  {
    if (!the_sun.getIsCircumbinary())
    {
      stellar_flux = habitable_zone_distance_helper(the_sun.getEffTemp(), the_sun.getLuminosity(), mode, mass);
    }
    else
    {
      stellar_flux = habitable_zone_distance_helper(the_sun.getCombinedEffTemp(), the_sun.getLuminosity(), mode, mass);
    }
    
    if (stellar_flux <= 0)
    {
      cerr << "Error! Program caluclated an invalid stellar flux!" << endl;
      cerr << "Star Name: " << the_sun.getName() << endl;
      cerr << "Star Mass: " << toString(the_sun.getMass()) << endl;
      cerr << "Star Luminosity: " << toString(the_sun.getLuminosity()) << endl;
      cerr << "Star Temperature: " << toString(the_sun.getEffTemp()) << endl;
      cerr << "Star Type: " << the_sun.getSpecType() << endl;
      cerr << "Zone: ";
      if (mode == RECENT_VENUS)
      {
	cerr << "Recent Venus";
      }
      else if (mode == RUNAWAY_GREENHOUSE)
      {
	cerr << "Runaway Greenhouse";
      }
      else if (mode == MOIST_GREENHOUSE)
      {
	cerr << "Moist Greenhouse";
      }
      else if (mode == EARTH_LIKE)
      {
	cerr << "Earth-like";
      }
      else if (mode == FIRST_CO2_CONDENSATION_LIMIT)
      {
	cerr << "First CO2 Condensation";
      }
      else if (mode == MAXIMUM_GREENHOUSE)
      {
	cerr << "Maximum Greenhouse";
      }
      else if (mode == EARLY_MARS)
      {
	cerr << "Early Mars";
      }
      else if (mode == TWO_AU_CLOUD_LIMIT)
      {
	cerr << "Two AU Cloud Limit" << endl;
      }
      cerr << endl;
      cerr << "Stellar Flux: " << toString(stellar_flux) << endl;
      exit(EXIT_FAILURE);
      return 0;
    }
    
    if (!the_sun.getIsCircumbinary())
    {
      return sqrt(the_sun.getLuminosity() / stellar_flux);
    }
    else
    {
      //stellar_flux2 = habitable_zone_distance_helper(the_sun.getSecondaryEffTemp(), the_sun.getSecondaryLuminosity(), mode);
      //combined_stellar_flux = stellar_flux + stellar_flux2;
      return sqrt(the_sun.getCombinedLuminosity() / stellar_flux);
    }
  }
  else
  {
    if (!the_sun.getIsCircumbinary())
    {
      if (mode == RECENT_VENUS || mode == RUNAWAY_GREENHOUSE || mode == MOIST_GREENHOUSE)
      {
	return sqrt(the_sun.getLuminosity() / 1.51);
      }
      else if (mode == EARTH_LIKE)
      {
	return sqrt(the_sun.getLuminosity());
      }
      else if (mode == FIRST_CO2_CONDENSATION_LIMIT || mode == MAXIMUM_GREENHOUSE || mode == EARLY_MARS || mode == TWO_AU_CLOUD_LIMIT)
      {
	return sqrt(the_sun.getLuminosity() / 0.48);
      }
    }
    else
    {
      if (mode == RECENT_VENUS || mode == RUNAWAY_GREENHOUSE || mode == MOIST_GREENHOUSE)
      {
	return sqrt(the_sun.getCombinedLuminosity() / 1.51);
      }
      else if (mode == EARTH_LIKE)
      {
	return sqrt(the_sun.getCombinedLuminosity());
      }
      else if (mode == FIRST_CO2_CONDENSATION_LIMIT || mode == MAXIMUM_GREENHOUSE || mode == EARLY_MARS || mode == TWO_AU_CLOUD_LIMIT)
      {
	return sqrt(the_sun.getCombinedLuminosity() / 0.48);
      }
    }
  }
  return 0;
}

long double calcLambda(long double distance, long double mass)
{
  return (pow(mass, 2.0) / pow(distance, 3.0 / 2.0)) * 1.7E16;
}

void gas_giant_temperature_albedo(planet* the_planet, long double parent_mass, bool is_moon)
{
  long double temp1;
  long double temp2;
  long double temp3;
  long double temp4;
  long double temp5;
  long double temp6;
  long double new_albedo;
  long double new_radius;
  long double new_day;
  long double new_obleteness;
  int loops = 0;
  if (the_planet->getTheSun().getAge() == 0.0)
  {
    the_planet->setTheSun(the_sun_clone);
  }
  temp3 = about(GAS_GIANT_ALBEDO, 0.1);
  the_planet->setAlbedo(temp3);
  temp1 = est_temp(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), the_planet->getAlbedo());
  the_planet->setEstimatedTemp(temp1);
  //temp4 = new_radius = gas_radius(temp1, the_planet->getDustMass(), the_planet->getMass(), the_planet->getTheSun().getAge(), the_planet);
  temp4 = new_radius = calcRadius(the_planet);
  the_planet->setRadius(temp4);
  temp5 = new_day = day_length(the_planet, parent_mass, is_moon);
  //the_planet->setDay(temp5);
  temp6 = new_obleteness = calcOblateness(the_planet);
  while (true)
  {
    if (loops >= 1000)
    {
      break;
    }
    if (temp1 > TEMPERATURE_CARBON_GIANT)
    {
      new_albedo = about(CARBON_GIANT_ALBEDO, 0.1);
    }
    else if (temp1 > TEMPERATURE_CLASS_V)
    {
      new_albedo = about(getGasGiantAlbedo("V", the_planet->getTheSun().getSpecType(), the_planet->getTheSun().getLuminosity()), 0.1);
    }
    else if (temp1 > TEMPERATURE_CLASS_IV)
    {
      new_albedo = about(getGasGiantAlbedo("IV", the_planet->getTheSun().getSpecType(), the_planet->getTheSun().getLuminosity()), 0.1);
    }
    else if (temp1 > TEMPERATURE_CLASS_III)
    {
      new_albedo = about(getGasGiantAlbedo("III", the_planet->getTheSun().getSpecType(), the_planet->getTheSun().getLuminosity()), 0.1);
    }
    else if (temp1 > TEMPERATURE_SULFUR_GIANT)
    {
      new_albedo = about(SULFAR_GIANT_ALBEDO, 0.1);
    }
    else if (temp1 > TEMPERATURE_CLASS_II)
    {
      new_albedo = about(getGasGiantAlbedo("II", the_planet->getTheSun().getSpecType(), the_planet->getTheSun().getLuminosity()), 0.1);
    }
    else if (temp1 > TEMPERATURE_CLASS_I) // visually, this is where it starts to turn blue in selden's version of StarGen
    {
      new_albedo = about(getGasGiantAlbedo("I", the_planet->getTheSun().getSpecType(), the_planet->getTheSun().getLuminosity()), 0.3);
    }
    else
    {
      new_albedo = about(METHANE_GIANT_ALBEDO, 0.1);
    }
    temp3 = ((new_albedo * 2.0) + temp3) / 3.0;
    temp2 = est_temp(the_planet->getTheSun().getREcosphere(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES), the_planet->getA(), temp3);
    temp1 = (temp2 + (temp1 * 2.0)) / 3.0;
    the_planet->setEstimatedTemp(temp1);
    //new_radius = gas_radius(temp1, the_planet->getDustMass(), the_planet->getMass(), the_planet->getTheSun().getAge(), the_planet);
    new_radius = calcRadius(the_planet);
    temp4 = (new_radius + (temp4 * 2.0)) / 3.0;
    the_planet->setRadius(temp4);
    new_day = day_length(the_planet, parent_mass, is_moon);
    temp5 = (temp5 + (new_day * 2.0)) / 3.0;
    //the_planet->setDay(temp5);
    new_obleteness = calcOblateness(the_planet);
    temp6 = (temp6 + (new_obleteness * 2.0)) / 3.0;
    if (temp1 > 900 && temp1 < 1400)
    {
      //cout << "blada" << endl;
      if (fabs(temp1 - temp2) < 0.0025 && fabs(the_planet->getAlbedo() - new_albedo) < 0.001)
      {
	break;
      }
    }
    else
    {
      //cout << temp1 << " " << temp2 << " " << fabs(temp1 - temp2) << endl;
      if (fabs(temp1 - temp2) < 0.25)
      {
	break;
      }
    }
    loops++;
  }
  the_planet->setAlbedo(temp3);
  the_planet->setEstimatedTemp(temp1);
  the_planet->setRadius(temp4);
   //the_planet->setDay(temp5);
  the_planet->setOblateness(temp6);
}

long double getGasGiantAlbedo(string sudusky_class, string star_type, long double luminosity)
{
  int num = star_type_to_num(star_type, luminosity);
  
  if (sudusky_class == "I")
  {
    return logistal_trend(0.0081213045, -0.0696581881, 0.6651148941, (long double)num);
  }
  else if (sudusky_class == "II")
  {
    return logistal_trend(0.0045058891, -0.0760456409, 0.9129152579, (long double)num);
  }
  else if (sudusky_class == "III")
  {
    return logistal_trend(0.00077110769, -0.14678595, 0.1751842946, (long double)num);
  }
  else if (sudusky_class == "IV")
  {
    return logistal_trend(0.00094635821, -0.1476824696, 0.0417580996, (long double)num);
  }
  else if (sudusky_class == "V")
  {
    return logistal_trend(0.0205970047, -0.0332241697, 0.6005902693, (long double)num);
  }
  else
  {
    cout << "Error!" << endl;
    exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
}

void calculate_gases(sun &the_sun, planet* the_planet, string planet_id)
{
  the_sun = the_planet->getTheSun();
  if ((the_planet->getSurfPressure() > 0 || the_planet->getGasGiant()) && the_sun.getAge() > 0)
  {
    //cout << "test 1" << endl;
    //cout << planet_id << endl;
    long double *amount = NULL;
    long double totalamount = 0;
    long double pressure  = the_planet->getSurfPressure() / MILLIBARS_PER_BAR;
    amount = new long double[gases.count()];
    int n;
    //vector<gas> temp_vector; // just incase for what ever reason, it doesn't replace the gases in the atmosphere
    
    if (the_planet->getNumGases() > 0)
    {
      the_planet->clearGases();
    }
    
    if (is_gas_planet(the_planet))
    {
      the_planet->setSurfPressure(10.0 * EARTH_SURF_PRES_IN_MILLIBARS);
      iterate_surface_temp(the_planet, true);
      pressure = the_planet->getSurfPressure() / MILLIBARS_PER_BAR;
    }
    
    for (int i = 0; i < gases.count(); i++)
    {
      long double yp = gases[i].getBoil() / (373. * ((log((pressure) + 0.001) / -5050.5) + (1.0 / 373.0)));
      //cout << planet_id << endl;
      //cout << gases[i].getName() << " boiling point: " << yp << endl;
      if (((yp >= 0 && yp < the_planet->getLowTemp()) || is_gas_planet(the_planet)) && (gases[i].getWeight() >= the_planet->getMolecWeight()))
      {
	long double vrms = rms_vel(gases[i].getWeight(), the_planet->getExosphericTemp());
	long double pvrms = pow(1.0 / (1.0 + vrms / the_planet->getEscVelocity()), the_sun.getAge() / 1e9);
	long double abund = gases[i].getAbunds();
	long double react = 1.0;
	long double fract = 1.0;
	long double pres2 = 1.0;
	
	if (gases[i].getSymbol() == "Ar")
	{
	  react = 0.15 * the_sun.getAge() / 4e9;
	}
	else if (gases[i].getSymbol() == "He")
	{
	  abund = abund * (0.001 + (the_planet->getGasMass() / the_planet->getMass()));
	  pres2 = (0.75 + pressure);
	  react = pow(1.0 / (1.0 + gases[i].getReactivity()), the_sun.getAge() / 2e9 * pres2);
	}
	else if ((gases[i].getSymbol() == "O" || gases[i].getSymbol() == "O2") && the_sun.getAge() > 2e9 && (the_planet->getGasGiant() || (the_planet->getSurfTemp() > 270 && the_planet->getSurfTemp() < 400)))
	{
	  pres2 = (0.89 + pressure/4);
	  react = pow(1.0 / (1.0 + gases[i].getReactivity()), pow(the_sun.getAge() / 2e9, 0.25) * pres2);
	}
	else if (gases[i].getSymbol() == "CO2" && the_sun.getAge() > 2e9 && (the_planet->getGasGiant() || (the_planet->getSurfTemp() > 270 && the_planet->getSurfTemp() < 400)))
	{
	  pres2 = (0.75 + pressure);
	  react = pow(1.0 / (1.0 + gases[i].getReactivity()), pow(the_sun.getAge() / 2e9, 0.5) * pres2);
	  react *= 1.5;
	}
	else
	{
	  pres2 = (0.75 + pressure);
	  react = pow(1.0 / (1.0 + gases[i].getReactivity()), the_sun.getAge() / 2e9 * pres2);
	}
	
	fract = 1.0 - (the_planet->getMolecWeight() / gases[i].getWeight());
	
	amount[i] = abund * pvrms * react * fract;
	
	//cout << toString(amount[i]) <<  " " << toString(vrms) << " " << toString(pvrms) << " " << toString(abund) << " " << toString(react) << " " << toString(fract) << " " << toString(pres2) << endl;
	
	if (flag_verbose & 0x4000 && (gases[i].getSymbol() == "O" || gases[i].getSymbol() == "N" || gases[i].getSymbol() == "Ar" || gases[i].getSymbol() == "He" || gases[i].getSymbol() == "CO2"))
	{
	  cerr << toString(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) << " " << gases[i].getSymbol() << ", " << toString(amount[i]) << " = a " << toString(abund) << " * p " << toString(pvrms) << " * r " << toString(react) << " * p2 " << toString(pres2) << " * f " << toString(fract) << "\t(" << toString(100.0 * (the_planet->getGasMass() / the_planet->getMass())) << "%)" << endl;
	}
	
	totalamount += amount[i];
	if (amount[i] > 0.0)
	{
	  n++;
	}
	else
	{
	  /*cout << planet_id << endl;
	  cout << "No " << gases[i].getName() << endl;
	  cout << "abund: " << abund << endl;
	  cout << "pvrms: " << pvrms << endl;
	  cout << "react: " << react << endl;
	  cout << "fract: " << fract << endl;*/
	}
      }
      else
      {
	amount[i] = 0.0;
      }
    }
    
    long double original_total = totalamount;
    long double increase_factor = 1.0;
    //long double pressure = 0.0;
    map<int, long double> new_values;
    map<int, bool> do_overs_more, do_overs_less;
    long double the_amount = 0.0;
    long double ipp = 0.0;
    bool bad_air = false;
    int counter = 0;
    
    if (n > 0)
    {
      do
      {
	original_total = totalamount;
	increase_factor = 1.0;
	for (int i = 0; i < gases.count(); i++)
	{
	  new_values[i] = 0;
	  if (is_potentialy_habitable(the_planet))
	  {
	    if (planet_id == "")
	    {
	      stringstream ss;
	      ss.str("");
	      ss << toString(the_planet->getA()) << " " << toString(the_planet->getMoonA());
	      planet_id = ss.str();
	      ss.str("");
	    }
	    if (the_planet->getSurfPressure() >= (1.2 * MIN_O2_IPP) && the_planet->getSurfPressure() <= MAX_HABITABLE_PRESSURE)
	    {
	      //the_amount = the_planet->getSurfPressure() * amount[i] / original_total;
	      the_amount = amount[i];
	      pressure = the_planet->getSurfPressure() * (amount[i] / totalamount);
	      ipp = inspired_partial_pressure(the_planet->getSurfPressure(), pressure);
	      if (ipp > gases[i].getMaxIpp())
	      {
		//cout << "test1 too high " << gases[i].getSymbol() << " " << planet_id << endl;
		//cout << toString(amount[i]) << endl;
		while (ipp > gases[i].getMaxIpp())
		{
		  the_amount = amount[i];
		  amount[i] *= 0.99;
		  totalamount -= the_amount;
		  totalamount += amount[i];
		  ipp = inspired_partial_pressure(the_planet->getSurfPressure(), the_planet->getSurfPressure() * (amount[i] / totalamount));
		}
	      }
	      else if (ipp < gases[i].getMinIpp())
	      {
		//cout << "test1 too low " << gases[i].getSymbol() << " " << planet_id << endl;
		//if (planet_id == "1.05853286955409876162 0.00153819919909735927041")
		{
		  for (int i = 0; i < gases.count(); i++)
		  {
		    //cout << gases[i].getName() << ": " << toString(amount[i]) << endl;
		  }
		  //exit(EXIT_FAILURE);
		}
		//cout << toString(amount[i]) << " " << toString(ipp) << " " << toString(the_planet->getSurfPressure()) << endl;
		while (ipp < gases[i].getMinIpp())
		{
		  the_amount = amount[i];
		  if (amount[i] <= 0.0)
		  {
		    amount[i] = 1.0E-9;
		  }
		  else
		  {
		    amount[i] *= 1.01;
		    totalamount -= the_amount;
		  }
		  totalamount += amount[i];
		  ipp = inspired_partial_pressure(the_planet->getSurfPressure(), the_planet->getSurfPressure() * (amount[i] / totalamount));
		}
	      }
	    }
	  }
	}
	original_total = totalamount;
	long double old_amount = 0.0;
	for (int i = 0, n = 0; i < gases.count(); i++)
	{
	  if (is_potentialy_habitable(the_planet))
	  {
	    if (the_planet->getSurfPressure() >= (1.2 * MIN_O2_IPP) && the_planet->getSurfPressure() <= MAX_HABITABLE_PRESSURE)
	    {
	      //cout << "test2 " << planet_id << endl;
	      if (new_values[i] > 0.0)
	      {
		amount[i] = new_values[i] * totalamount;
	      }
	      ipp = inspired_partial_pressure(the_planet->getSurfPressure(), the_planet->getSurfPressure() * amount[i] / totalamount);
	      if (ipp > gases[i].getMaxIpp())
	      {
		bad_air = true;
		do_overs_less[i] = true;
		do_overs_more[i] = false;
		//cout << i << ". " << gases[i].getName() << " Too high: " << ipp << " (Max allowed: " << gases[i].getMaxIpp() << ")" << endl;
		break;
	      }
	      else if (ipp < gases[i].getMinIpp() && gases[i].getNum() == AN_O)
	      {
		bad_air = true;
		do_overs_less[i] = false;
		do_overs_more[i] = true;
		//cout << i << ". " << gases[i].getName() << " Too low: " << ipp << " (Min allowed: " << gases[i].getMinIpp() << ")" << endl;
		break;
	      }
	      else
	      {
		do_overs_less[i] = false;
		do_overs_more[i] = false;
		bad_air = false;
	      }
	    }
	  }
	}
	counter++;
	if (counter > 1000)
	{
	  break;
	}
      }
      while (bad_air);
      
      for (int i = 0, n = 0; i < gases.count(); i++)
      {
	if (amount[i] > 0.0)
	{
	  //cout << "test 2" << endl;
	  //cout << planet_id << endl;
	  gas substance;
	  substance.setNum(gases[i].getNum());
	  if (new_values[i] > 0.0)
	  {
	    substance.setSurfPressure(the_planet->getSurfPressure() * new_values[i]);
	  }
	  else
	  {
	    substance.setSurfPressure(the_planet->getSurfPressure() * amount[i] / totalamount);
	  }
	  the_planet->addGas(substance);
	  
	  if (flag_verbose & 0x2000)
	  {
	    if ((the_planet->getGas(n).getNum() == AN_O) && inspired_partial_pressure(the_planet->getSurfPressure(), the_planet->getGas(n).getSurfPressure()) > gases[i].getMaxIpp())
	    {
	      cerr << planet_id << "\t Poisoned by O2" << endl;
	    }
	  }
	}
	n++;
      }
    }
    delete [] amount;
    /*if (the_planet->getNumGases() == 0 && temp_vector.size() > 0)
    {
      for (int i = 0; i < temp_vector.size(); i++)
      {
	the_planet->addGas(temp_vector[i]);
      }
      temp_vector.clear();
    }*/
    
    if (the_planet->getNumGases() && (the_planet->getSurfPressure() / EARTH_SURF_PRES_IN_MILLIBARS) > 0.001)
    {
      //cerr << "We have a serious air! The atmosphere of " << planet_id << " contains no gases!" << endl;
    }
  }
}

void assign_composition(planet *the_planet, sun &the_sun, bool is_moon)
{
  long double lambda = calcLambda(the_planet->getA(), the_planet->getMass());
  
  if (lambda >= 1 || ((the_planet->getDustMass() * SUN_MASS_IN_EARTH_MASSES) > 0.005 && is_moon))
  {
    if (the_planet->getImf() == 0 && the_planet->getRmf() == 0)
    {
      long double rock_max;
      the_planet->setImf(0);
      if (the_planet->getOrbitZone() == 2)
      {
	the_planet->setImf(random_number(0, 0.5));
      }
      else if (the_planet->getOrbitZone() == 3)
      {
	the_planet->setImf(random_number(0, 1));
      }
      if (the_planet->getA() < habitable_zone_distance(the_sun, RECENT_VENUS, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
      {
	rock_max = 0.5;
      }
      else
      {
	rock_max = 1.0 - the_planet->getImf();
      }
      the_planet->setRmf(random_number(0, rock_max));
    }
    if (the_planet->getCmf() == 0)
    {
      the_planet->setCmf(pow(random_number(0, 1), 8.0));
    }
  }
  else
  {
    long double rand;
    rand = random_number(0.0, 100.0);
    if (the_planet->getOrbitZone() == 1)
    {
      if (the_planet->getRmf() == 0)
      {
	if (rand <= 92.9292929)
	{
	  the_planet->setRmf(random_number(0.2, 1));
	}
	else
	{
	  the_planet->setRmf(random_number(0, 0.2));
	}
      }
      if (the_planet->getCmf() == 0)
      {
	if (rand <= 75.757575758)
	{
	  the_planet->setCmf(random_number(0.75, 1));
	}
	else
	{
	  the_planet->setCmf(random_number(0, 0.75));
	}
      }
    }
    else
    {
      if (the_planet->getImf() == 0)
      {
	if (rand > 99.0)
	{
	  the_planet->setImf(random_number(0.5, 1.0));
	}
	else
	{
	  the_planet->setImf(pow(random_number(0, pow(0.5, 1.0 / 8.0)), 1.0 / 8.0));
	}
      }
      if (the_planet->getRmf() == 0)
      {
	if (rand > 99)
	{
	  the_planet->setRmf(random_number(0.0, 1.0 - the_planet->getImf()));
	}
	else if (rand <= 92)
	{
	  the_planet->setRmf(random_number(0.2, 1.0 - the_planet->getImf()));
	}
	else
	{
	  the_planet->setRmf(random_number(0, 0.2));
	}
      }
      if (the_planet->getCmf() == 0)
      {
	if (rand > 92)
	{
	  the_planet->setCmf(pow(random_number(0.0, 1.0), 8.0));
	}
	else if (rand <= 75)
	{
	  the_planet->setCmf(random_number(0.75, 1.0));
	}
	else
	{
	  the_planet->setCmf(pow(random_number(0.0, pow(0.75, 1.0 / 8.0)), 8.0));
	}
      }
    }
  }
  while ((the_planet->getImf() + the_planet->getRmf()) > 1.0)
  {
    // this shouldn't happened but it sometimes does
    long double max = 1.0 - the_planet->getImf();
    the_planet->setRmf(random_number(0.0, max));
  }
}

bool is_gas_planet(planet* the_planet)
{
  if (the_planet->getGasMass() == 0)
  {
    return false;
  }
  if (the_planet->getType() == tSubSubGasGiant || the_planet->getType() == tSubGasGiant || the_planet->getType() == tGasGiant || the_planet->getType() == tBrownDwarf)
  {
    return true;
  }
  return false;
}

bool is_earth_like_size(planet* the_planet)
{
  if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.5 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 2.0) || ((convert_km_to_eu(the_planet->getRadius())) >= 0.8 && (convert_km_to_eu(the_planet->getRadius())) <= 1.25))
  {
    return true;
  }
  return false;
}

bool is_earth_like(planet* the_planet)
{
  long double rel_temp = (the_planet->getSurfTemp() - FREEZING_POINT_OF_WATER) - EARTH_AVERAGE_CELSIUS;
  long double seas = the_planet->getHydrosphere() * 100.0;
  long double clouds = the_planet->getCloudCover() * 100.0;
  long double pressure = the_planet->getSurfPressure() / EARTH_SURF_PRES_IN_MILLIBARS;
  long double ice = the_planet->getIceCover() * 100.0;
  long double gravity = the_planet->getSurfGrav();
  long double iron = (1.0 - (the_planet->getRmf() + the_planet->getImf())) * 100.0;
  
  if (!is_habitable(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Not habitable" << endl;
    return false;
  }
  else if (!is_earth_like_size(the_planet))
  {
    return false;
  }
  else if (the_planet->getEsi() < 0.8)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Low ESI" << endl;
    return false;
  }
  else if (the_planet->getImf() > 0.0)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Has too much ice" << endl;
    return false;
  }
  else if (iron < 20 || iron > 60)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too big or too small a core" << endl;
    return false;
  }
  else if (gravity < 0.8 || gravity > 1.2)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too low or too high gravity" << endl;
    return false;
  }
  else if (rel_temp < -2.0 || rel_temp > 3.0)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too cold or too hot" << endl;
    return false;
  }
  else if (seas < 50.0 || seas > 80.0)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too dry or too wet" << endl;
    return false;
  }
  else if (ice > 10)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too much surface ice" << endl;
    return false;
  }
  else if (clouds < 40.0 || clouds > 80.0)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too few or too many clouds" << endl;
    return false;
  }
  else if (pressure < 0.5 || pressure > 2.0)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Too low or too high a surface pressure" << endl;
    return false;
  }
  else if (the_planet->getType() == tWater)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Water world!" << endl;
    return false;
  }
  else if (the_planet->getType() == tOil)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Carbon planet!" << endl;
    return false;
  }
  else if (the_planet->getMaxTemp() >= the_planet->getBoilPoint())
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Sometime too hot!" << endl;
    return false;
  }
  return true;
}

bool is_habitable_jovian_conservative(planet *the_planet)
{
  if (!is_habitable_jovian(the_planet))
  {
    return false;
  }
  else if (the_planet->getA() < habitable_zone_distance(the_sun_clone, MOIST_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) || the_planet->getA() > habitable_zone_distance(the_sun_clone, MAXIMUM_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
  {
    return false;
  }
  return true;
}

bool is_habitable_jovian(planet* the_planet)
{
  sun the_sun = the_planet->getTheSun();
  
  //if (is_gas_planet(the_planet) && the_planet->getEstimatedTerrTemp() >= FREEZING_POINT_OF_WATER && the_planet->getEstimatedTerrTemp() <= (EARTH_AVERAGE_KELVIN + 10.0)/* && the_sun.getAge() > 2.0E9*/)
  if (!is_gas_planet(the_planet))
  {
    return false;
  }
  else if (fabs(the_planet->getHzd()) > 1.0)
  {
    return false;
  }
  return true;
}

bool is_terrestrial(planet* the_planet)
{
  if (the_planet->getType() == tTerrestrial || the_planet->getType() == tWater || ((the_planet->getType() == t1Face || the_planet->getType() == tIce || the_planet->getType() == tMartian || the_planet->getType() == tVenusian) && fabs(the_planet->getHzd()) < 1.0) || breathability(the_planet) == BREATHABLE || (!is_gas_planet(the_planet) && the_planet->getSurfPressure() > 0.001 && the_planet->getSurfTemp() > (FREEZING_POINT_OF_WATER - 15.0) && the_planet->getSurfTemp() < (EARTH_AVERAGE_KELVIN + 15.0)))
  {
    return true;
  }
  return false;
}

long double calcOblateness(planet* the_planet)
{
  long double multiplier = 0;
  long double oblateness = 0;
  long double mass_in_eu = 0;
  long double planetary_mass_in_grams = 0;
  long double equatorial_radius_in_cm = 0;
  long double k2 = 0;
  long double ang_velocity = 0;
  if (is_gas_planet(the_planet))
  {
    mass_in_eu = the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES;
    if (the_planet->getType() == tSubGasGiant || the_planet->getType() == tSubSubGasGiant)
    {
      multiplier = 4.94E-12;
    }
    else if (the_planet->getType() == tGasGiant)
    {
      multiplier = 5.56E-12;
    }
    oblateness = multiplier * (pow(the_planet->getRadius(), 3.0) / (mass_in_eu * pow(the_planet->getDay(), 2.0)));
  }
  else
  {
    planetary_mass_in_grams = the_planet->getMass() * SOLAR_MASS_IN_GRAMS;
    equatorial_radius_in_cm = the_planet->getRadius() * CM_PER_KM;
    k2 = calculate_moment_of_inertia_coeffient(the_planet);
    while (the_planet->getDay() == 0)
    {
      cerr << "Error! The day is 0 hours long!" << endl;
      exit(EXIT_FAILURE);
    }
    ang_velocity = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * the_planet->getDay());
    oblateness = calcOblateness_improved(ang_velocity, planetary_mass_in_grams, equatorial_radius_in_cm, k2);
  }
  if (oblateness > 0.5)
  {
    oblateness = 0.5;
  }
  return oblateness;
}

long double calcPhlPressure(planet* the_planet)
{
  return (100 * 0.87 * pow2(the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES)) / (87.0 * pow3(convert_km_to_eu(the_planet->getRadius())));
}

bool is_habitable_optimistic(planet* the_planet)
{
  if (!is_potentialy_habitable_optimistic(the_planet))
  {
    return false;
  }
  else if (breathability(the_planet) != BREATHABLE)
  {
    return false;
  }
  return true;
}

long double calcHzd(planet* the_planet)
{
  sun the_sun = the_planet->getTheSun();
  long double inner_edge = habitable_zone_distance(the_sun, RECENT_VENUS, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES);
  long double outer_edge = habitable_zone_distance(the_sun, EARLY_MARS, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES);
  return ((2.0 * the_planet->getA()) - outer_edge - inner_edge) / (outer_edge - inner_edge);
}

long double calcHzcHelper(long double m1, long double r1, long double k1, long double k2, long double k3, long double m)
{
  return r1 * pow(10.0, k1 + (log10(m / m1) / 3.0) - (k2 * pow(m / m1, k3)));
}

long double calcHzc(planet* the_planet)
{
  //long double ro = calcHzcHelper(5.52, 4.43, -0.209396, 0.0807, 0.375, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES);
  //long double ri = calcHzcHelper(5.80, 2.52, -0.209490, 0.0804, 0.394, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES);
  long double r = convert_km_to_eu(the_planet->getRadius());
  long double ro = convert_km_to_eu(radius_improved(the_planet->getMass(), 1.0, 0, 0, false, the_planet->getOrbitZone(), the_planet));
  long double ri = convert_km_to_eu(radius_improved(the_planet->getMass(), 0.0, 0, 0, false, the_planet->getOrbitZone(), the_planet));
  return ((2.0 * r) - ro - ri) / (ro - ri);
}

long double calcV(long double t, long double m)
{
  return sqrt((2E-2 * t) / m);
}

long double calcHza(planet* the_planet)
{
  long double veh = calcV(the_planet->getEstimatedTerrTemp(), 1.0);
  long double ven = calcV(the_planet->getEstimatedTerrTemp(), 14.0);
  return ((2.0 * sqrt((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) / (the_planet->getRadius() / KM_EARTH_RADIUS))) - veh - ven) / (veh - ven);
}

long double calcEsiHelper(long double value, long double ref_value, long double weight, long double n)
{
  return pow(1.0 - fabs((value - ref_value) / (value + ref_value)), weight / n);
}

long double calcEsi(planet* the_planet)
{
  long double esir = calcEsiHelper(convert_km_to_eu(the_planet->getRadius()), 1.0, 0.57);
  long double esid = calcEsiHelper(the_planet->getDensity() / EARTH_DENSITY, 1.0, 1.07);
  long double esiv = calcEsiHelper((the_planet->getEscVelocity() / CM_PER_KM) / 11.186, 1.0, 0.70);
  long double esit = calcEsiHelper(the_planet->getSurfTemp(), EARTH_AVERAGE_KELVIN, 5.58);
  return esir * esid * esiv * esit;
}

long double calcSphHelper(long double min, long double max, long double opt, long double x, long double w)
{
  if (x > min && x < max)
  {
    return pow(fabs(((x - min) * (x - max)) / (((x - min) * (x - max)) - pow(x - opt, 2.0))), w);
  }
  else
  {
    return 0;
  }
}

long double calcSph(planet* the_planet)
{
  long double ht = calcSphHelper(-8.3, 39.0, 24.1, the_planet->getSurfTemp() - FREEZING_POINT_OF_WATER, 3.0);
  //long double hrh = 1.0;
  long double hrh = calcSphHelper(9.2, 100.0, 77.5, calcRelHumidity(the_planet), 2.0);
  return ht * hrh;
}

bool is_potentialy_habitable_optimistic_size(planet *the_planet)
{
  /*if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 10.0 || (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) < 0.1) // The Plantary Habitablity Laboratory believes habitable planets have to be in the range of 0.1 to 10 earth masses in size.
   *  {
   *    return false;
   }
   else if ((the_planet->radius / KM_EARTH_RADIUS) > 2.5 || (the_planet->radius / KM_EARTH_RADIUS) < 0.5)  // The Plantary Habitablity Laboratory believes habitable planets have to be in the range of 0.5 to 2.5 earth radii in size.
   {
     return false;
   }*/
  if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.1 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 10.0) || ((convert_km_to_eu(the_planet->getRadius())) >= 0.5 && (convert_km_to_eu(the_planet->getRadius())) <= 2.5))
  {
    return true;
  }
  return false;
}

bool is_potentialy_habitable_optimistic(planet* the_planet)
{
  sun the_sun = the_planet->getTheSun();
  string spec_type = the_sun.getSpecType();
  if (compare_string_char(spec_type, 1, "?"))
  {
    the_planet->setTheSun(the_sun_clone);
    the_sun = the_planet->getTheSun();
    spec_type = the_sun.getSpecType();
  }
  string star_type = getStarType(spec_type);
  if (the_sun.getMass() < 0.3) // the Plantary Habitablity Laboratory feels that stars less that it is very unlikey 0.3 solar masses due to the tidal heating planets would expirence before their orbits stablize.
  {
    return false;
  }
  else if (star_type == "O" || star_type == "B" || star_type == "A") // Types O, B, and A don't live long enough to produce habitable worlds and are two bright for photosysisis to occure.
  {
    return false;
  }
  //else if ((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) > 10.0 || (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) < 0.1) // The Plantary Habitablity Laboratory believes habitable planets have to be in the range of 0.1 to 10 earth masses in size.
  else if (!is_potentialy_habitable_optimistic_size(the_planet))
  {
    return false;
  }
  else if (fabs(the_planet->getHzd()) > 1.0) // The planet has to be in the zone where water would in theory be a liquid.
  {
    return false;
  }
  else if (fabs(the_planet->getHzc()) > 1.0) // The planet can't have too much iron or too much water or gas making up its mass.
  {
    return false;
  }
  else if (fabs(the_planet->getHza()) > 1.0) // The planet can't have the potential of having a too thick or too thin atmosphere. 
  {
    return false;
  }
  else if (the_planet->getEsi() < 0.5) // The planet must be similar enough to Earth to at least support extremeophiles.
  {
    return false;
  }
  return true;
}

long double calcRelHumidity(planet *the_planet)
{
  long double surf_area, hydro_mass, staturated_mass, water_vapor_in_kg, max_possible_water_vapor_in_kg;
  if (the_planet->getMolecWeight() > WATER_VAPOR)
  {
    return 0.0;
  }
  else
  {
    surf_area = 4.0 * PI * pow2(the_planet->getRadius());
    hydro_mass = the_planet->getHydrosphere() * surf_area * EARTH_WATER_MASS_PER_AREA;
    staturated_mass = 1.0 * surf_area * EARTH_WATER_MASS_PER_AREA;
    water_vapor_in_kg = (0.00000001 * hydro_mass) * exp(Q2_36 * (the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN));
    max_possible_water_vapor_in_kg = (0.00000001 * staturated_mass) * exp(Q2_36 * (the_planet->getSurfTemp() - EARTH_AVERAGE_KELVIN));
    return (water_vapor_in_kg / max_possible_water_vapor_in_kg) * 100.0;
  }
}

long double getPlantLifeAlbedo(string star_type, long double luminosity)
{
  int num = star_type_to_num(star_type, luminosity);
  
  if (num >= 31 && num <= 33)
  {
    return linear_trend(-0.05, 2.45, num);
  }
  else if (num >= 34 && num <= 37)
  {
    return linear_trend(-1.0 / 30.0, 29.0 / 15.0, num);
  }
  else if (num >= 38 && num <= 40)
  {
    return linear_trend(-0.1, 4.5, num);
  }
  else if (num >= 41 && num <= 53)
  {
    return linear_trend(-0.025, 1.525, num);
  }
  else if (num >= 54 && num <= 57)
  {
    return linear_trend(-1.0 / 30.0, 2.0, num);
  }
  else if (num >= 58 && num <= 64)
  {
    return linear_trend(-5.0 / 600.0, 7.0 / 12.0, num);
  }
  else if (num >= 65 && num <= 68)
  {
    return linear_trend(-1.0 / 300.0, 29.0 / 60.0, num);
  }
  return ROCKY_ALBEDO;
}

long double calcFlux(long double temperature, long double wavelength)
{
  wavelength /= 1000.0;
  wavelength /= 1000000.0;
  long double first = 2.0 * (long double)H * pow((long double)C, 2.0);
  long double second = pow(wavelength, 5);
  long double third = (long double)H * (long double)C;
  long double fourth = wavelength * (long double)KB * temperature;
  long double fifth = third / fourth;
  long double sixth = exp(fifth);
  long double seventh = sixth - 1.0;
  //cout << toString(wavelength) << ": " << toString(first) << " " << toString(second) << " " << toString(third) << " " << toString(fourth) << " " << toString(fifth) << " " << toString(sixth) << " " << toString(seventh) << endl;
  return (first / second) * (1.0 / seventh);         
}

long double calculate_moment_of_inertia_coeffient(planet* the_planet)
{
  long double result;
  result = calculate_moment_of_inertia(the_planet) / (the_planet->getMass() * pow2(the_planet->getRadius()));
  return result;
}

long double calculate_moment_of_inertia(planet* the_planet)
{
  long double result;
  result = (2.0 / 5.0) * the_planet->getMass() * pow2(the_planet->getRadius());
  return result;
}

long double calcOblateness_improved(long double angular_velocity, long double planetary_mass_in_grams, long double equatorial_radius_in_cm, long double k2)
{
  long double result;
  result = ((pow2(angular_velocity) * pow3(equatorial_radius_in_cm)) / (GRAV_CONSTANT * planetary_mass_in_grams)) * pow((5.0 / 2.0) * pow2(1.0 - ((3.0 / 2.0) * k2)) + (2.0 / 5.0), -1.0);
  return result;
}

long double calcLuminosity(planet *the_planet)
{
  long double star_luminosity = the_planet->getTheSun().getLuminosity();
  if (star_luminosity == 0.0)
  {
    the_planet->setTheSun(the_sun_clone);
    star_luminosity = the_planet->getTheSun().getLuminosity();
  }
  return pow2(1.0 / the_planet->getA()) * star_luminosity;
}

long double calcGasRadius(planet *the_planet)
{
  long double lower, upper, result, density;
  if (the_planet->getCoreRadius() <= 0.0)
  {
    the_planet->setCoreRadius(radius_improved(the_planet->getDustMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet));;
  }
  if (the_planet->getTheSun().getAge() == 0)
  {
    the_planet->setTheSun(the_sun_clone);
  }
  if (convert_su_to_eu(the_planet->getMass()) < 17.0)
  {
    result = mini_neptune_radius(the_planet);
  }
  else if (convert_su_to_eu(the_planet->getMass()) < 20.0)
  {
    lower = mini_neptune_radius(the_planet);
    upper = gas_radius(the_planet->getEstimatedTemp(), the_planet->getDustMass(), the_planet->getMass(), the_planet->getTheSun().getAge(), the_planet);
    result = rangeAdjust(convert_su_to_eu(the_planet->getMass()), lower, upper, 17.0, 20.0);
  }
  else
  {
    result = gas_radius(the_planet->getEstimatedTemp(), the_planet->getDustMass(), the_planet->getMass(), the_planet->getTheSun().getAge(), the_planet);
  }
  if (the_planet->getCoreRadius() <= 0.0)
  {
    the_planet->setCoreRadius(radius_improved(the_planet->getDustMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet));;
  }
  if (result < the_planet->getCoreRadius())
  {
    result = mini_neptune_radius(the_planet);
    //result = gas_dwarf_radius(the_planet);
  }
  density = volume_density(the_planet->getMass(), result);
  while ((density / EARTH_DENSITY) < 0.01)
  {
    result *= 0.99;
    density = volume_density(the_planet->getMass(), result);
  }
  return result;
}

long double calcSolidRadius(planet *the_planet)
{
  return radius_improved(the_planet->getMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet);
}

long double calcRadius(planet *the_planet)
{
  long double result;
  if (the_planet->getCoreRadius() <= 0.0)
  {
    the_planet->setCoreRadius(radius_improved(the_planet->getDustMass(), the_planet->getImf(), the_planet->getRmf(), the_planet->getCmf(), the_planet->getGasGiant(), the_planet->getOrbitZone(), the_planet));;
  }
  if (the_planet->getGasGiant() || the_planet->getGasMass() > 0.0)
  {
    result = calcGasRadius(the_planet);
  }
  else
  {
    result = calcSolidRadius(the_planet);
  }
  return result;
}

long double planet_radius_helper(long double planet_mass, long double mass1, long double radius1, long double mass2, long double radius2, long double mass3, long double radius3, bool use_cache)
{
  // some imput validation for debuging purposes
  bool show_debug = false;
  if (mass1 != 0.0 && radius1 == 0.0)
  {
    cout << "invalid radius for " << mass1 << endl;
    show_debug = true;
  }
  else if (mass2 != 0.0 && radius2 == 0.0)
  {
    cout << "invalid radius for " << mass2 << endl;
    show_debug = true;
  }
  else if (mass3 != 0.0 && radius3 == 0.0)
  {
    cout << "invalid radius for " << mass3 << endl;
    show_debug = true;
  }
  if (show_debug)
  {
    cout << endl;
    cout << "Please send an email to omega13a@yahoo.com of this problem with the following debug info: " << endl;
    cout << "Input was:" << endl;
    cout << "planet_mass = " << planet_mass << endl;
    cout << "mass1 = " << toString((long double)mass1) << endl;
    cout << "radius1 = " << toString((long double)radius1) << endl;
    cout << "mass2 = " << toString((long double)mass2) << endl;
    cout << "radius2 = " << toString((long double)radius2) << endl;
    cout << "mass3 = " << toString((long double)mass3) << endl;
    cout << "radius3 = " << toString((long double)radius3) << endl;
    exit(EXIT_FAILURE);
  }
  long double radius = 0.0;
  long double a = 0.0;
  long double b = 0.0;
  long double c = 0.0;
  map<long double, long double> cache_name;
  long double coeff[3];
  vector<long double> coeff_cache;
  if (use_cache)
  {
    cache_name[mass1] = radius1;
    cache_name[mass2] = radius2;
    cache_name[mass3] = radius3;
    coeff_cache = polynomial_cache[cache_name];
    if (!coeff_cache.empty())
    {
      for (int i = 0; i < 3; i++)
      {
	coeff[i] = coeff_cache[i];
      }
      a = coeff[0];
      b = coeff[1];
      c = coeff[2];
    }
    else
    {
      quadfix(mass1, radius1, mass2, radius2, mass3, radius3, a, b, c);
      coeff[0] = a;
      coeff[1] = b;
      coeff[2] = c;
      while (!coeff_cache.empty())
      {
	coeff_cache.pop_back();
      }
      for (int i = 0; i < 3; i++)
      {
	coeff_cache.push_back(coeff[i]);
      }
      polynomial_cache[cache_name] = coeff_cache;
    }
  }
  else
  {
    quadfix(mass1, radius1, mass2, radius2, mass3, radius3, a, b, c);
  }
  radius = quad_trend(a, b, c, planet_mass);
  return radius;
}

long double planet_radius_helper2(long double planet_mass, long double mass1, long double radius1, long double mass2, long double radius2)
{
  long double radius = 0.0;
  long double a = 0.0;
  long double b = 0.0;
  logfix(mass1, radius1, mass2, radius2, a, b);
  radius = ln_trend(a, b, planet_mass);
  return radius;
}

long double planet_radius_helper3(long double temperature, long double temperature1, long double radius1, long double temperature2, long double radius2)
{
  long double a = 0.0;
  long double b = 0.0;
  long double radius = 0.0;
  long double adjusted_temperature = temperature / 1000.0;
  long double adjusted_temperature1 = temperature1 / 1000.0;
  long double adjusted_temperature2 = temperature2 / 1000.0;
  e_fix(adjusted_temperature1, radius1, adjusted_temperature2, radius2, a, b);
  radius = e_trend(a, b, temperature);
  return radius;
}

// these should be in utils.cpp but because of a some sort of class between const.h and the boost libary, it is here instead.
long double convert_su_to_eu(long double mass)
{
  return mass * SUN_MASS_IN_EARTH_MASSES;
}

long double convert_au_to_km(long double au)
{
  return au * KM_PER_AU;
}

bool is_potentialy_habitable_conservative_size(planet *the_planet)
{
  if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.5 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 5.0) || ((convert_km_to_eu(the_planet->getRadius())) >= 0.8 && (convert_km_to_eu(the_planet->getRadius())) <= 1.5))
  {
    return true;
  }
  return false;
}

bool is_potentialy_habitable_conservative(planet *the_planet)
{
  if (!is_potentialy_habitable_optimistic(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not potentionally habitable by optimistic" << endl;
    return false;
  }
  else if (!is_potentialy_habitable_conservative_size(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not conservative size" << endl;
    return false;
  }
  else if (the_planet->getA() < habitable_zone_distance(the_sun_clone, RUNAWAY_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) || the_planet->getA() > habitable_zone_distance(the_sun_clone, MAXIMUM_GREENHOUSE, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": wrong distance for extended" << endl;
    return false;
  }
  return true;
}

bool is_habitable_conservative(planet *the_planet)
{
  if (!is_potentialy_habitable_conservative(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not potentionally habitable by conservative" << endl;
    return false;
  }
  else if (breathability(the_planet) != BREATHABLE)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Not breathable for conservative" << endl;
    return false;
  }
  return true;
}

bool is_potentialy_habitable_extended_size(planet *the_planet)
{
  if (((the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) >= 0.1 && (the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) <= 10.0) || ((convert_km_to_eu(the_planet->getRadius())) >= 0.5 && (convert_km_to_eu(the_planet->getRadius())) <= 2.5))
  {
    return true;
  }
  return false;
}

bool is_potentialy_habitable_extended(planet *the_planet)
{
  sun the_sun = the_planet->getTheSun();
  string star_type = the_sun.getSpecType();
  if (!is_potentialy_habitable_extended_size(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not extended size" << endl;
    return false;
  }
  else if (the_sun.getMass() < 0.3) // the Plantary Habitablity Laboratory feels that stars less that it is very unlikey 0.3 solar masses due to the tidal heating planets would expirence before their orbits stablize.
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": too small a star for extended" << endl;
    return false;
  }
  else if (star_type == "O" || star_type == "B" || star_type == "A") // Types O, B, and A don't live long enough to produce habitable worlds and are two bright for photosysisis to occure.
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": wrong star for extended" << endl;
    return false;
  }
  else if (fabs(the_planet->getHzc()) > 1.0) // The planet can't have too much iron or too much water or gas making up its mass.
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": wrong composition for extended" << endl;
    return false;
  }
  else if (fabs(the_planet->getHza()) > 1.0) // The planet can't have the potential of having a too thick or too thin atmosphere. 
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": potential for too thick or thin an atmosphere for extended" << endl;
    return false;
  }
  else if (the_planet->getA() < habitable_zone_distance(the_sun_clone, RECENT_VENUS, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES) || the_planet->getA() > habitable_zone_distance(the_sun_clone, TWO_AU_CLOUD_LIMIT, the_planet->getMass() * SUN_MASS_IN_EARTH_MASSES))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": wrong distance for extended" << endl;
    return false;
  }
  return true;
}

bool is_habitable_extended(planet *the_planet)
{
  if (!is_potentialy_habitable_extended(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not potentionally extended" << endl;
    return false;
  }
  else if (breathability(the_planet) != BREATHABLE)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Not breathable for extended" << endl;
    return false;
  }
  return true;
}

bool is_potentialy_habitable_earth_like(planet *the_planet)
{
  if (!is_potentialy_habitable_conservative(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not potentionally habitable by conservative" << endl;
    return false;
  }
  else if (!is_earth_like_size(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": not earth-like size" << endl;
    return false;
  }
  else if (the_planet->getEsi() < 0.8)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": too low esi for earth-like" << endl;
    return false;
  }
  return true;
}

bool is_habitable_earth_like(planet* the_planet)
{
  if (!is_potentialy_habitable_earth_like(the_planet))
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Not potentialy earth-like" << endl;
    return false;
  }
  else if (breathability(the_planet) != BREATHABLE)
  {
    //cout << flag_seed << "-" << the_planet->getPlanetNo() << ": Not breathable for earth-like" << endl;
    return false;
  }
  return true;
}

bool is_potentialy_habitable(planet *the_planet)
{
  if (is_potentialy_habitable_earth_like(the_planet))
  {
    return true;
  }
  else if (is_potentialy_habitable_conservative(the_planet))
  {
    return true;
  }
  else if (is_potentialy_habitable_optimistic(the_planet))
  {
    return true;
  }
  else if (is_potentialy_habitable_extended(the_planet))
  {
    return true;
  }
  return false;
}

bool is_habitable(planet *the_planet)
{
  if (is_habitable_earth_like(the_planet))
  {
    return true;
  }
  else if (is_habitable_conservative(the_planet))
  {
    return true;
  }
  else if (is_habitable_optimistic(the_planet))
  {
    return true;
  }
  else if (is_habitable_extended(the_planet))
  {
    return true;
  }
  return false;
}

long double convert_km_to_eu(long double km)
{
  return km / KM_EARTH_RADIUS;
}

void makeHabitable(sun &the_sun, planet *the_planet, string planet_id, bool is_moon, bool do_gases)
{
  //cout << planet_id << " " << the_planet->getA() << endl;
  if (!is_gas_planet(the_planet) && is_potentialy_habitable(the_planet) && the_planet->getMinTemp() < the_planet->getBoilPoint() && (the_planet->getSurfPressure() < (1.2 * MIN_O2_IPP) || the_planet->getSurfPressure() > MAX_HABITABLE_PRESSURE))
  {
    //cout << "test3 " << planet_id << endl;
    the_planet->setSurfPressure(calcPhlPressure(the_planet) * EARTH_SURF_PRES_IN_MILLIBARS);
    while (the_planet->getSurfPressure() > 6000)
    {
      the_planet->setSurfPressure(the_planet->getSurfPressure() - 1.0);
    }
    iterate_surface_temp(the_planet, do_gases);
    if (do_gases)
    {
      the_planet->clearGases();
      calculate_gases(the_sun, the_planet, planet_id);
    }
    //cout << "test4 " << planet_id << endl;
    assign_type(the_sun, the_planet, planet_id, is_moon, do_gases, true);
    //cout << "test5 " << planet_id << endl;
  }
}