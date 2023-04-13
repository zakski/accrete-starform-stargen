#define VERBOSE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"

struct dust_bands
{
	double innerEdge;
	double outerEdge;
	int isDustPresent;
	int isGasPresent;
	dust_bands* next_band;

	int dustAvailable(double innerRng, double outerRng);

	dust_bands(double inner, double outer):innerEdge(inner),outerEdge(outer)
		{ next_band=0; isDustPresent=isGasPresent=TRUE; }
};

struct planets
{
	double
		axis,		// semi-major axis of the orbit (in AU)
		eccentricity,	// eccentricity of the orbit
		mass,		// mass (in solar masses)
		radius,	// equatorial radius (in km)
		density,	// density (in g/cc)
		orbitalPeriod,	// length of the local year (days)
		day,	  	// length of the local day (hours)
		escapeVelocity,// units of cm/sec
		surfaceAccel,	// units of cm/sec2
		surfaceGrav,	// units of Earth gravities
		RMSvelocity,	// units of cm/sec
		minMoleculeWeight,	// smallest molecular weight retained
		volatileGasInventory,
		surfacePressure,	// units of millibars (mb)
		boilPoint,	// the boiling point of water (Kelvin)
		albedo,		// albedo of the planet
		surfaceTemp,// surface temperature in Kelvin
		hydrosphere,// fraction of surface covered
		cloudCover,	// fraction of surface covered
		iceCover;	// fraction of surface covered

	int
		isPlanetoid,
		isGasGiant,		// TRUE if the planet is a gas giant
		orbitalZone,   // the 'zone' of the planet (1=inner, 2=habitable)
		isResonantPeriod,	// TRUE if in resonant rotation
		axialTilt,		// units of degrees
		isGreenhouseEffect;	// runaway greenhouse effect?

	planets
		*firstMoon,
		*nextPlanet;

	double
		volumeRadius(void),
		kothariRadius(void),
		volumeDensity(void),
		dayLength(int &spin_resonance, double age),
		volInventory(double starMass),
		createVolInventory(int atm, double starMass),
		opacity(void),
		getInv4Press(double press),
		empiricalDensity(double rEcosphere);

	int
		getAtmRate(void); // uses surfacePress in millibars

	void
		buildMoonData(double minOrbit, double maxOrbit,double starMass, double starLuminosity, double rEcosphere, double rGreenhouse, double age),
		addMoons(double starMass, double starLuminosity, double rEcosphere, double rGreenhouse, double age),
		showStats(FILE *f),
		showUPP(FILE *f),
      insertMainWorld(planets* who, double rEcosphere),
		iterateSurfaceTemp(double distance, double rEcosphere,double hyd=-1.0),
		buildMainworld(int diam, int atm, int hyd, double ecc, double starMass, double starLuminosity, double rEcosphere, double age),
		buildPlanet(double starMass, double starLuminosity, double rEcosphere, double rGreenhouse, double age);
};

class starSystem
{
	protected:
		planets *planetList;
//      dust_bands *dust_head;
		double
			starMass,
			starLuminosity,

			mainSeqLife,
			age,
			rEcosphere,
			rGreenhouse,

			dustDensity,
         reduced_mass,

			cloudEccentricity;
		double
			r_inner, r_outer;

		int
			spinResonance,
			isDustLeft;

		double stellarMaxDust(double mass)
			{ return(200.0 * pow(mass,(1.0 / 3.0))); }

		planets * distributePlanetaryMasses(double inner, double outer);

		double inner_effect_limit(double a, double e, double mass);

		double outer_effect_limit(double a, double e, double mass);

		void accreteDust(dust_bands *dust_head,double &seed_mass, double a, double e, double crit_mass,
			double body_inner_bound, double body_outer_bound);
		void coalescePlanetesimals(planets *&planet,dust_bands *dust_head,double a, double e, double mass, double crit_mass,
			double body_inner_bound, double body_outer_bound);
		double collectDust(double last_mass, double a, double e, double crit_mass,
			dust_bands* dust_band);
		void updateDustLanes(dust_bands *dust_head, double min, double max, double mass, double crit_mass,
			 double body_inner_bound, double body_outer_bound);
		void insertMainworld(planets*mainworld);
		
	public:
		starSystem(double stellarMass, double stellarLuminosity);

		void
			make(int diam, int atm, int hyd), // mainworld vals, -1 means randomize
         display(void);
};


/*--------------------------------------------------------------------------*/
/*  The separation is in units of AU, and both masses are in units of solar */
/*  masses.  The period returned is in terms of Earth days.                 */
/*--------------------------------------------------------------------------*/
inline double period(double separation, double small_mass, double large_mass)
{
//	  double period_in_years;

//     period_in_years = sqrt(pow(separation,3.0) / (small_mass + large_mass));
	return(sqrt(pow(separation,3.0) / (small_mass + large_mass)) * DAYS_IN_A_YEAR);
}

// Globally used inline functions
/*----------------------------------------------------------------------*/
/*  This function returns a random real number between the specified    */
/* inner and outer bounds.                                              */
/*----------------------------------------------------------------------*/
inline double random_number(double inner, double outer)
{
	  double range = outer - inner;
	  return((((double)rand()) / (double)(RAND_MAX)) * range + inner);
}

/*----------------------------------------------------------------------*/
/*   This function returns a value within a certain variation of the    */
/*   exact value given it in 'value'.                                   */
/*----------------------------------------------------------------------*/
inline double about (double value, double variation)
{
	  return(value + (value * random_number(-variation,variation)));
}
