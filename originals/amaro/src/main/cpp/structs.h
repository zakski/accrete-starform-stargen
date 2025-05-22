#ifndef STRUCTS_H
#define STRUCTS_H
#pragma once

#include <string>
#include <vector>
//#include <boost/concept_check.hpp>
#include "c_structs.h"

using namespace std;

typedef enum planet_type
{
  tUnknown,
  tRock,
  tVenusian,
  tTerrestrial,
  tGasGiant,
  tMartian,
  tWater,
  tIce,
  tSubGasGiant,
  tSubSubGasGiant,
  tAsteroids,
  t1Face,
  tBrownDwarf,  //seb
  tIron,
  tCarbon,
  tOil
}
planet_type;

class gas;
ostream &operator<<(ostream &, gas &);

class gas
{
private:
  int num;
  long double surfPressure;
public:
  gas();
  void setNum(int);
  int getNum();
  void setSurfPressure(long double);
  long double getSurfPressure();
  bool operator<(gas &);
  bool operator==(gas &);
  friend ostream &operator<<(ostream &, gas &);
};

class sun
{
private:
  long double luminosity;
  long double mass;
  long double effTemp;
  string specType;
  long double age;
  string name;
  bool isCircumbinary;
  long double secondaryMass;
  long double secondaryLuminosity;
  long double secondaryEffTemp;
  long double combinedEffTemp;
  string secondarySpecType;
  long double seperation;
  long double eccentricity;
public:
  sun();
  sun(long double, long double, long double, string, long double, string);
  sun(sun &);
  sun(const sun&);
  void setLuminosity(long double);
  long double getLuminosity();
  void setMass(long double);
  long double getMass();
  void setEffTemp(long double);
  long double getEffTemp();
  void setSpecType(string);
  string getSpecType();
  long double getLife();
  void setAge(long double);
  long double getAge();
  void setName(string);
  string getName();
  long double getREcosphere(long double);
  void setIsCircumbinary(bool);
  bool getIsCircumbinary();
  void setSecondaryMass(long double);
  long double getSecondaryMass();
  void setSecondaryLuminosity(long double);
  long double getSecondaryLuminosity();
  void setSecondaryEffTemp(long double);
  long double getSecondaryEffTemp();
  void setSecondarySpecType(string);
  string getSecondarySpecType();
  long double getCombinedLuminosity();
  long double getCombinedMass();
  void setSeperation(long double);
  long double getSeperation();
  void setEccentricity(long double);
  long double getEccentricity();
  long double getSecondaryLife();
  long double getMinStableDistance();
  long double getCombinedEffTemp();
  //sun operator=(sun &);
};

class planet
{
private:
  int planetNo;
  long double a;					/* semi-major axis of solar orbit (in AU)*/
  long double e;					/* eccentricity of solar orbit		 */
  long double axialTilt;			/* units of degrees					 */
  bool gasGiant;			/* TRUE if the planet is a gas giant */
  long double dustMass;			/* mass, ignoring gas				 */
  long double gasMass;			/* mass, ignoring dust				 */
  long double imf;				/* ice mass fraction */
  long double rmf;				/* rock mass fraction */
  long double cmf;				/* fraction of rock that's carbon instead of silicate*/
  long double moonA;				/* semi-major axis of lunar orbit (in AU)*/
  long double moonE;				/* eccentricity of lunar orbit		 */
  long double coreRadius;		/* radius of the rocky core (in km)	 */
  long double radius;				/* equatorial radius (in km)		 */
  int orbitZone;			/* the 'zone' of the planet			 */
  long double density;			/* density (in g/cc)				 */
  long double orbPeriod;			/* length of the local year (days)	 */
  long double day;				/* length of the local day (hours)	 */
  bool resonantPeriod;	/* TRUE if in resonant rotation		 */
  long double escVelocity;		/* units of cm/sec					 */
  long double surfAccel;			/* units of cm/sec2					 */
  long double surfGrav;			/* units of Earth gravities			 */
  long double rmsVelocity;		/* units of cm/sec					 */
  long double molecWeight;		/* smallest molecular weight retained*/
  long double volatileGasInventory;
  long double surfPressure;		/* units of millibars (mb)			 */
  bool greenhouseEffect;	/* runaway greenhouse effect?		 */
  long double boilPoint;			/* the boiling point of water (Kelvin)*/
  long double albedo;				/* albedo of the planet				 */
  long double exosphericTemp;	/* units of degrees Kelvin			 */
  long double estimatedTemp;     /* quick non-iterative estimate (K)  */
  long double estimatedTerrTemp;/* for terrestrial moons and the like*/
  long double surfTemp;			/* surface temperature in Kelvin	 */
  long double greenhsRise;		/* Temperature rise due to greenhouse */
  long double highTemp;			/* Day-time temperature              */
  long double lowTemp;			/* Night-time temperature			 */
  long double maxTemp;			/* Summer/Day						 */
  long double minTemp;			/* Winter/Night						 */
  long double hydrosphere;		/* fraction of surface covered		 */
  long double cloudCover;		/* fraction of surface covered		 */
  long double iceCover;			/* fraction of surface covered		 */
  sun theSun;
  vector<gas> atmosphere;
  planet_type type;				/* Type code						 */
  int minorMoons;
  long double inclination;
  long double ascendingNode;
  long double longitudeOfPericenter;
  long double meanLongitude;
  long double hzd;
  long double hzc;
  long double hza;
  long double esi;
  long double sph;
  long double oblateness;
  bool deleteable;
  long double knownRadius;
  void estimateMass();
  //vector<planet *> temp_moon;
public:
  planet();
  planet(int, long double, long double, long double, bool, long double, long double, planet*, planet*);
  ~planet();
  void setPlanetNo(int);
  int getPlanetNo();
  void setA(long double);
  long double getA();
  void setE(long double);
  long double getE();
  void setAxialTilt(long double);
  long double getAxialTilt();
  long double getMass();
  void setGasGiant(bool);
  bool getGasGiant();
  void setDustMass(long double);
  long double getDustMass();
  void setGasMass(long double);
  long double getGasMass();
  void setImf(long double);
  long double getImf();
  void setRmf(long double);
  long double getRmf();
  void setCmf(long double);
  long double getCmf();
  void setMoonA(long double);
  long double getMoonA();
  void setMoonE(long double);
  long double getMoonE();
  void setCoreRadius(long double);
  long double getCoreRadius();
  void setRadius(long double);
  long double getRadius();
  void setOrbitZone(int);
  int getOrbitZone();
  void setDensity(long double);
  long double getDensity();
  void setOrbPeriod(long double);
  long double getOrbPeriod();
  void setDay(long double);
  long double getDay();
  void setResonantPeriod(bool);
  bool getResonantPeriod();
  void setEscVelocity(long double);
  long double getEscVelocity();
  void setSurfAccel(long double);
  long double getSurfAccel();
  void setSurfGrav(long double);
  long double getSurfGrav();
  void setRmsVelocity(long double);
  long double getRmsVelocity();
  void setMolecWeight(long double);
  long double getMolecWeight();
  void setVolatileGasInventory(long double);
  long double getVolatileGasInventory();
  void setSurfPressure(long double);
  long double getSurfPressure();
  void setGreenhouseEffect(bool);
  bool getGreenhouseEffect();
  void setBoilPoint(long double);
  long double getBoilPoint();
  void setAlbedo(long double);
  long double getAlbedo();
  void setExosphericTemp(long double);
  long double getExosphericTemp();
  void setEstimatedTemp(long double);
  long double getEstimatedTemp();
  void setEstimatedTerrTemp(long double);
  long double getEstimatedTerrTemp();
  void setSurfTemp(long double);
  long double getSurfTemp();
  void setGreenhsRise(long double);
  long double getGreenhsRise();
  void setHighTemp(long double);
  long double getHighTemp();
  void setLowTemp(long double);
  long double getLowTemp();
  void setMaxTemp(long double);
  long double getMaxTemp();
  void setMinTemp(long double);
  long double getMinTemp();
  void setHydrosphere(long double);
  long double getHydrosphere();
  void setCloudCover(long double);
  long double getCloudCover();
  void setIceCover(long double);
  long double getIceCover();
  void setType(planet_type);
  planet_type getType();
  void setTheSun(sun &);
  sun &getTheSun();
  int getNumGases();
  void addGas(gas);
  gas getGas(int);
  void setMinorMoons(int);
  int getMinorMoons();
  void setInclination(long double);
  long double getInclination();
  void setAscendingNode(long double);
  long double getAscendingNode();
  void setLongitudeOfPericenter(long double);
  long double getLongitudeOfPericenter();
  void setMeanLongitude(long double);
  long double getMeanLongitude();
  void clearGases();
  void setHzd(long double);
  long double getHzd();
  void setHzc(long double);
  long double getHzc();
  void setHza(long double);
  long double getHza();
  void setEsi(long double);
  long double getEsi();
  void setSph(long double);
  long double getSph();
  void setOblateness(long double);
  long double getOblateness();
  long double getEquatrorialRadius();
  long double getPolarRadius();
  //void addMoon(planet *);
  //planet *getMoon(int);
  //int getMoonCount();
  //void deleteMoon(int);
  void setDeletable(bool);
  bool getDeletable();
  void setKnownRadius(long double);
  long double getKnownRadius();
  void sortMoons();
  bool operator<(planet &);
  bool operator==(planet &);
  planet *first_moon;
  planet *next_planet;
  planet *reconnect_to;
  planet *first_moon_backup;
};

class dust
{
private:
  long double innerEdge;
  long double outerEdge;
  bool dustPresent;
  bool gasPresent;
public:
  dust();
  ~dust();
  void setInnerEdge(long double);
  long double getInnerEdge();
  void setOuterEdge(long double);
  long double getOuterEdge();
  void setDustPresent(bool);
  bool getDustPresent();
  void setGasPresent(bool);
  bool getGasPresent();
  dust *next_band;
};

class star;

ostream &operator<<(ostream &, star &);

class star
{
private:
  long double luminosity;
  long double mass;
  long double eff_temp;
  string spec_type;
  long double mass2;
  long double eccentricity;
  long double distance;
  long double inc;
  long double an;
  planet *known_planets;
  string desig;
  bool in_celestia;
  string name;
  int extra_spaces;
  void calcLuminosity();
  void calcMass();
  void calcEffTemp();
  bool isCircumbinary;
  long double eff_temp2;
  string spec_type2;
  long double luminosity2;
public:
  star()
  {}
  star(long double, long double, long double, string, long double, long double, long double, long double, long double, planet *, string, bool, string);
  star(star &);
  star(const star &);
  star(star2 &);
  ~star();
  void setExtraSpaces(int);
  string getName();
  int getExtraSpaces();
  long double getInc();
  long double getAn();
  planet *getKnownPlanets();
  bool getInCelestia();
  long double getMass();
  long double getLuminosity();
  long double getEffTemp();
  string getSpecType();
  string getDesig();
  void setDistance(long double);
  long double getDistance();
  void setEccentricity(long double);
  long double getEccentricity();
  void setMass2(long double);
  long double getMass2();
  void setLuminosity2(long double);
  long double getLuminosity2();
  void setEffTemp2(long double);
  long double getEffTemp2();
  void setSpecType2(string);
  string getSpecType2();
  void setIsCircumbinary(bool);
  bool getIsCircumbinary();
  star operator=(star &);
  //star operator=(const star);
  bool operator<(star &);
  bool operator==(star &);
  friend ostream &operator<<(ostream &, star &);
};

class catalog;
ostream &operator<<(ostream &, catalog &);

class catalog
{
private:
  int extra_spaces;
  string arg;
  vector<star> stars;
public:
  catalog();
  catalog(string);
  ~catalog();
  void setArg(string);
  void addStar(star &);
  string getArg();
  int count();
  star &operator[](const int &);
  catalog operator=(catalog &);
  friend ostream &operator<<(ostream &, catalog &);
  void sort();
};

class gen
{
public:
  gen();
  ~gen();
  dust *dusts;
  planet *planets;
  gen *next;
};

class Chemicle;
ostream &operator<<(ostream &, Chemicle &);

class Chemicle
{
private:
  int num;
  string symbol;
  string htmlSymbol;
  string name;
  long double weight;
  long double melt;
  long double boil;
  long double density;
  long double pzero;
  long double c;
  long double n;
  long double abunde;
  long double abunds;
  long double reactivity;
  long double maxIpp;
  long double minIpp;
  int nameSpaces;
  int symbolSpaces;
  void fixMelt();
  void fixBoil();
  void fixMaxIpp();
  void fixMinIpp();
  void fixAbunde();
  void fixAbunds();
  void setSpaces();
public:
  Chemicle();
  Chemicle(int, string, string, string, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double);
  Chemicle(Chemicle &);
  Chemicle(const Chemicle &);
  ~Chemicle();
  int getNum();
  string getSymbol();
  string getHtmlSymbol();
  string getName();
  long double getWeight();
  void setMelt(long double);
  long double getMelt();
  void setBoil(long double);
  long double getBoil();
  long double getDensity();
  long double getPzero();
  long double getC();
  long double getN();
  void setAbunde(long double);
  long double getAbunde();
  void setAbunds(long double);
  long double getAbunds();
  long double getReactivity();
  void setMaxIpp(long double);
  long double getMaxIpp();
  void setMinIpp(long double);
  long double getMinIpp();
  int getNameSpaces();
  int getSymbolSpaces();
  Chemicle operator=(Chemicle &);
  bool operator<(Chemicle &);
  bool operator==(Chemicle &);
  friend ostream &operator<<(ostream &, Chemicle &);
};

class ChemTable;
ostream &operator<<(ostream &, ChemTable &);

class ChemTable
{
private:
  vector<Chemicle> chemicles;
public:
  ChemTable()
  {}
  void addChemicle(Chemicle);
  int count();
  Chemicle &operator[](const int &);
  friend ostream &operator<<(ostream &, ChemTable &);
};

#endif
