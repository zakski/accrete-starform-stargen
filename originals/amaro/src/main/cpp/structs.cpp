#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "const.h"
#include "enviro.h"
#include "star_temps.h"
#include "structs.h"
#include "utils.h"

using namespace std;

star::star(long double l, long double m, long double et, string t, long double m2, long double e, long double d, long double i, long double a, planet *kp, string des, bool cel, string n)
{
  luminosity = l;
  mass = m;
  eff_temp = et;
  spec_type = t;
  mass2 = m2;
  luminosity2 = 0;
  eff_temp2 = 0;
  spec_type2 = "";
  eccentricity = e;
  distance = d;
  inc = i;
  an = a;
  known_planets = kp;
  desig = des;
  in_celestia = cel;
  name = n;
  if (luminosity == 0)
  {
    calcLuminosity();
  }
  if (mass == 0)
  {
    calcMass();
  }
  if (eff_temp == 0)
  {
    calcEffTemp();
  }
  if (spec_type.empty())
  {
    spec_type = eff_temp_to_spec_type(eff_temp, luminosity);
  }
  isCircumbinary = false;
}

star::star(star2& data)
{
  luminosity = data.luminosity;
  mass = data.mass;
  eff_temp = data.eff_temp;
  spec_type = data.spec_type;
  mass2 = data.m2;
  eccentricity = data.e;
  distance = data.a;
  inc = data.inc;
  an = data.an;
  known_planets = NULL;
  desig = data.desig;
  if (data.in_celestia == 0)
  {
    in_celestia = false;
  }
  else
  {
    in_celestia = true;
  }
  name = data.name;
  if (luminosity == 0)
  {
    calcLuminosity();
  }
  if (mass == 0)
  {
    calcMass();
  }
  if (eff_temp == 0)
  {
    calcEffTemp();
  }
  if (spec_type.empty())
  {
    spec_type = eff_temp_to_spec_type(eff_temp, luminosity);
  }
  isCircumbinary = false;
}

star::~star()
{
  luminosity = 0;
  mass = 0;
  eff_temp = 0;
  spec_type = "";
  mass2 = 0;
  eccentricity = 0;
  distance = 0;
  inc = 0;
  an = 0;
  desig = "";
  in_celestia = false;
  name = "";
  isCircumbinary = false;
}


void star::calcLuminosity()
{
  luminosity = mass_to_luminosity(mass);
}

void star::calcMass()
{
  mass = luminosity_to_mass(luminosity);
}

void star::calcEffTemp()
{
  eff_temp = spec_type_to_eff_temp(spec_type);
}

star::star(star &right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  eff_temp = right.eff_temp;
  spec_type = right.spec_type;
  mass2 = right.mass2;
  eccentricity = right.eccentricity;
  distance = right.distance;
  inc = right.inc;
  an = right.an;
  known_planets = right.known_planets;
  desig = right.desig;
  in_celestia = right.in_celestia;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  luminosity2 = right.luminosity2;
  eff_temp2 = right.eff_temp2;
  spec_type2 = right.spec_type2;
  if (luminosity == 0)
  {
    calcLuminosity();
  }
  if (mass == 0)
  {
    calcMass();
  }
  if (eff_temp == 0)
  {
    calcEffTemp();
  }
  if (spec_type.empty())
  {
    spec_type = eff_temp_to_spec_type(eff_temp, luminosity);
  }
}

star::star(const star &right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  eff_temp = right.eff_temp;
  spec_type = right.spec_type;
  mass2 = right.mass2;
  eccentricity = right.eccentricity;
  distance = right.distance;
  inc = right.inc;
  an = right.an;
  known_planets = right.known_planets;
  desig = right.desig;
  in_celestia = right.in_celestia;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  luminosity2 = right.luminosity2;
  eff_temp2 = right.eff_temp2;
  spec_type2 = right.spec_type2;
  if (luminosity == 0)
  {
    calcLuminosity();
  }
  if (mass == 0)
  {
    calcMass();
  }
  if (eff_temp == 0)
  {
    calcEffTemp();
  }
  if (spec_type.empty())
  {
    spec_type = eff_temp_to_spec_type(eff_temp, luminosity);
  }
}

star star::operator=(star &right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  eff_temp = right.eff_temp;
  spec_type = right.spec_type;
  mass2 = right.mass2;
  eccentricity = right.eccentricity;
  distance = right.distance;
  inc = right.inc;
  an = right.an;
  known_planets = right.known_planets;
  desig = right.desig;
  in_celestia = right.in_celestia;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  luminosity2 = right.luminosity2;
  eff_temp2 = right.eff_temp2;
  spec_type2 = right.spec_type2;
  if (luminosity == 0)
  {
    calcLuminosity();
  }
  if (mass == 0)
  {
    calcMass();
  }
  if (eff_temp == 0)
  {
    calcEffTemp();
  }
  if (spec_type.empty())
  {
    spec_type = eff_temp_to_spec_type(eff_temp, luminosity);
  }
  return *this;
}

ostream& operator<<(ostream &strm, star &obj)
{
  string is_in_celestia = "";
  
  if (obj.in_celestia)
  {
    is_in_celestia = "+P";
  }
  
  strm << setprecision(4);
  strm << left << setw(30 + obj.extra_spaces) << obj.name << fixed << right << setw(3) << is_in_celestia << setw(8) << obj.mass << setw(12) << obj.luminosity << setw(13) << obj.eff_temp << setw(11) << obj.spec_type;
  return strm;
}

string star::getName()
{
  return name;
}

void star::setExtraSpaces(int e)
{
  extra_spaces = e;
}

int star::getExtraSpaces()
{
  return extra_spaces;
}

long double star::getAn()
{
  return an;
}

long double star::getInc()
{
  return inc;
}

planet* star::getKnownPlanets()
{
  return known_planets;
}

bool star::getInCelestia()
{
  return in_celestia;
}

long double star::getEffTemp()
{
  return eff_temp;
}

long double star::getLuminosity()
{
  return luminosity;
}

long double star::getMass()
{
  return mass;
}

string star::getSpecType()
{
  return spec_type;
}

string star::getDesig()
{
  return desig;
}

long double star::getDistance()
{
  return distance;
}

long double star::getEccentricity()
{
  return eccentricity;
}

long double star::getMass2()
{
  return mass2;
}

long double star::getEffTemp2()
{
  return eff_temp2;
}

bool star::getIsCircumbinary()
{
  return isCircumbinary;
}

long double star::getLuminosity2()
{
  return luminosity2;
}

string star::getSpecType2()
{
  return spec_type2;
}

void star::setDistance(long double d)
{
  distance = d;
}

void star::setEccentricity(long double e)
{
  eccentricity = e;
}

void star::setEffTemp2(long double e)
{
  eff_temp2 = e;
}

void star::setIsCircumbinary(bool b)
{
  isCircumbinary = b;
}

void star::setLuminosity2(long double l)
{
  luminosity2 = l;
}

void star::setMass2(long double m)
{
  mass2 = m;
}

void star::setSpecType2(string s)
{
  spec_type2 = s;
}

bool star::operator<(star& right)
{
  if (desig == "Sol" && right.desig == "Sol")
  {
    return false;
  }
  else if (desig == "Sol")
  {
    return true;
  }
  else if (right.desig == "Sol")
  {
    return false;
  }
  else if (name < right.name)
  {
    return true;
  }
  return false;
}

bool star::operator==(star& right)
{
  if (name == right.name)
  {
    return true;
  }
  return false;
}

catalog::catalog()
{
  extra_spaces = 0;
}

catalog::catalog(string a)
{
  arg = a;
  extra_spaces = 0;
}

int catalog::count()
{
  return stars.size();
}

void catalog::addStar(star &the_star)
{
  string star_name;
  int name_length;
  int diff;
  
  stars.push_back(the_star);
  
  star_name = the_star.getName();
  name_length = star_name.length();
  if (name_length > 30)
  {
    diff = name_length - 30;
    if (diff > extra_spaces)
    {
      extra_spaces = diff;
    }
  }
}

star &catalog::operator[](const int& sub)
{
  if (sub < 0 || sub > (stars.size() - 1))
  {
    cerr << "Non existant star!" << endl;
    exit(EXIT_FAILURE);
  }
  return stars[sub];
}

catalog::~catalog()
{
  /*planet *planets = NULL;
  planet *node = NULL;
  planet *next = NULL;
  for (int i = 0; i < stars.size(); i++)
  {
    planets = stars[i].getKnownPlanets();
    if (planets != NULL)
    {
      for (node = planets; node != NULL; node = next)
      {
	next = node->next_planet;
	delete node;
      }
    }
  }*/
  stars.clear();
}

ostream& operator<<(ostream& strm, catalog& obj)
{
  int total_stars = obj.count();
  strm << setw(14) << "Name" << setw(37 + obj.extra_spaces) << "Mass" << setw(12) << "Luminosity" << setw(13) << "Temperature" << setw(11) << "Star Type" << endl;
  strm << fixed;
  
  for (int i = 0; i < total_stars; i++)
  {
    obj[i].setExtraSpaces(obj.extra_spaces);
    strm << setw(8) << right << i << ". " << obj[i] << endl;
  }
  
  return strm;
}

catalog catalog::operator=(catalog &right)
{
  arg = right.arg;
  stars.clear();
  int new_stars = right.count();
  for (int i = 0; i < new_stars; i++)
  {
    stars.push_back(right[i]);
  }
  return *this;
}

void catalog::setArg(string a)
{
  arg = a;
}

string catalog::getArg()
{
  return arg;
}

void catalog::sort()
{
  //writeVector(stars, "\n");
  quicksort(stars, 0, stars.size());
}

Chemicle::Chemicle()
{
  num = 0;
  symbol = "";
  htmlSymbol = "";
  name = "";
  weight = 0;
  melt = 0;
  boil = 0;
  density = 0;
  pzero = 0;
  c = 0;
  n = 0;
  abunde = 0;
  abunds = 0;
  reactivity = 0;
  maxIpp = 0;
  minIpp = 0;
  fixBoil();
  fixMelt();
  fixAbunde();
  fixAbunds();
  fixMaxIpp();
  fixMaxIpp();
  setSpaces();
}

Chemicle::Chemicle(int nu, string s, string h, string na, long double w, long double m, long double b, long double d, long double p, long double c2, long double n2, long double ae, long double as, long double r, long double ma, long double mi)
{
  num = nu;
  symbol = s;
  htmlSymbol = h;
  name = na;
  weight = w;
  melt = m;
  boil = b;
  density = d;
  pzero = p;
  c = c2;
  n = n2;
  abunde = ae;
  abunds = as;
  reactivity = r;
  maxIpp = ma;
  minIpp = mi;
  fixBoil();
  fixMelt();
  fixAbunde();
  fixAbunds();
  fixMaxIpp();
  fixMaxIpp();
  setSpaces();
}

Chemicle::Chemicle(Chemicle &right)
{
  num = right.num;
  symbol = right.symbol;
  htmlSymbol = right.htmlSymbol;
  name = right.name;
  weight = right.weight;
  melt = right.melt;
  boil = right.boil;
  density = right.density;
  pzero = right.pzero;
  c = right.c;
  n = right.n;
  abunde = right.abunde;
  abunds = right.abunds;
  reactivity = right.reactivity;
  maxIpp = right.maxIpp;
  minIpp = right.minIpp;
  fixBoil();
  fixMelt();
  fixAbunde();
  fixAbunds();
  fixMaxIpp();
  fixMaxIpp();
  setSpaces();
}

Chemicle::Chemicle(const Chemicle &right)
{
  num = right.num;
  symbol = right.symbol;
  htmlSymbol = right.htmlSymbol;
  name = right.name;
  weight = right.weight;
  melt = right.melt;
  boil = right.boil;
  density = right.density;
  pzero = right.pzero;
  c = right.c;
  n = right.n;
  abunde = right.abunde;
  abunds = right.abunds;
  reactivity = right.reactivity;
  maxIpp = right.maxIpp;
  minIpp = right.minIpp;
  fixBoil();
  fixMelt();
  fixAbunde();
  fixAbunds();
  fixMaxIpp();
  fixMaxIpp();
  setSpaces();
}

Chemicle::~Chemicle()
{
  num = 0;
  symbol = "";
  htmlSymbol = "";
  name = "";
  weight = 0;
  melt = 0;
  boil = 0;
  density = 0;
  pzero = 0;
  c = 0;
  n = 0;
  abunde = 0;
  abunds = 0;
  reactivity = 0;
  maxIpp = 0;
  minIpp = 0;
  nameSpaces = 0;
  symbolSpaces = 0;
}

long double Chemicle::getAbunde()
{
  return abunde;
}

long double Chemicle::getAbunds()
{
  return abunds;
}

long double Chemicle::getBoil()
{
  return boil;
}

long double Chemicle::getC()
{
  return c;
}

long double Chemicle::getDensity()
{
  return density;
}

string Chemicle::getHtmlSymbol()
{
  return htmlSymbol;
}

long double Chemicle::getMaxIpp()
{
  return maxIpp;
}

long double Chemicle::getMelt()
{
  return melt;
}

long double Chemicle::getMinIpp()
{
  return minIpp;
}

long double Chemicle::getN()
{
  return n;
}

string Chemicle::getName()
{
  return name;
}

int Chemicle::getNum()
{
  return num;
}

long double Chemicle::getPzero()
{
  return pzero;
}

long double Chemicle::getReactivity()
{
  return reactivity;
}

string Chemicle::getSymbol()
{
  return symbol;
}

long double Chemicle::getWeight()
{
  return weight;
}

Chemicle Chemicle::operator=(Chemicle& right)
{
  num = right.num;
  symbol = right.symbol;
  htmlSymbol = right.htmlSymbol;
  name = right.name;
  weight = right.weight;
  melt = right.melt;
  boil = right.boil;
  density = right.density;
  pzero = right.pzero;
  c = right.c;
  n = right.n;
  abunde = right.abunde;
  abunds = right.abunds;
  reactivity = right.reactivity;
  maxIpp = right.maxIpp;
  minIpp = right.minIpp;
  fixBoil();
  fixMelt();
  fixAbunde();
  fixAbunds();
  fixMaxIpp();
  fixMaxIpp();
  setSpaces();
  return *this;
}

void Chemicle::setBoil(long double b)
{
  boil = b;
  fixBoil();
}

void Chemicle::setMelt(long double m)
{
  melt = m;
  fixMelt();
}

void Chemicle::setMaxIpp(long double ma)
{
  maxIpp = ma;
  fixMaxIpp();
}

void Chemicle::setMinIpp(long double mi)
{
  minIpp = mi;
  fixMinIpp();
}

void Chemicle::setAbunde(long double a)
{
  abunde = a;
  fixAbunde();
}

void Chemicle::setAbunds(long double a)
{
  abunds = a;
  fixAbunds();
}

void Chemicle::fixAbunde()
{
  if (abunde <= 0)
  {
    if (num > 92)
    {
      abunde = 1.0E-41;
    }
    else
    {
      abunde = 1.0E-21;
    }
  }
}

void Chemicle::fixAbunds()
{
  if (abunds <= 0)
  {
    if (num > 92)
    {
      abunds = 1.0E-41;
    }
    else
    {
      abunds = 1.0E-21;
    }
  }
}

void Chemicle::fixBoil()
{
  if (boil <= 0)
  {
      boil = melt + 100.0;
  }
}

void Chemicle::fixMaxIpp()
{
  if (maxIpp <= 0)
  {
    maxIpp = INCREDIBLY_LARGE_NUMBER;
  }
}

void Chemicle::fixMelt()
{
  if (boil > 0 && melt <= 0)
  {
    melt = boil * (2.0 / 3.0);
  }
  else if (melt <= 0)
  {
    melt = 1100.0;
  }
}

void Chemicle::fixMinIpp()
{
  // do nothing
}

void Chemicle::setSpaces()
{
  nameSpaces = 18 - name.length();
  symbolSpaces = 15 - symbol.length();
}

int Chemicle::getNameSpaces()
{
  return nameSpaces;
}

int Chemicle::getSymbolSpaces()
{
  return symbolSpaces;
}

bool Chemicle::operator<(Chemicle &right)
{
  long double xx = abunds * abunde;
  long double yy = right.abunds * right.abunde;
  
  //cout << xx << " < " << yy << endl;
  
  if (xx > yy)
  {
    return true;
  }
  else if (xx == yy)
  {
    if (weight < right.weight)
    {
      return true;
    }
    else if (weight == right.weight)
    {
      if (boil < right.boil)
      {
	return true;
      }
      else if (boil == right.boil)
      {
	if (num < right.num)
	{
	  return true;
	}
      }
    }
  }
  return false;
}

bool Chemicle::operator==(Chemicle &right)
{
  long double xx = abunds * abunde;
  long double yy = right.abunds * right.abunde;
  
  if (xx == yy && weight == right.weight && boil == right.boil && num == right.num)
  {
    return true;
  }
  return false;
}

ostream& operator<<(ostream& strm, Chemicle& obj)
{
  strm  << left << obj.getNum() << ".\t" << right << obj.getSymbol();
  for (int i = 0; i < obj.getSymbolSpaces(); i++)
  {
    strm << " ";
  }
  strm << obj.getName();
  for (int i = 0; i < obj.getNameSpaces(); i++)
  {
    strm << " ";
  }
  strm << fixed << right << setprecision(4) << setw(10) << obj.getWeight() << setw(22) << obj.getMinIpp() << setw(20) << obj.getMaxIpp() << setw(15) << scientific << (obj.getAbunde() * obj.getAbunds());
  return strm;
}


void ChemTable::addChemicle(Chemicle chem)
{
  chemicles.push_back(chem);
  quicksort(chemicles, 0, chemicles.size());
}

int ChemTable::count()
{
  return chemicles.size();
}

Chemicle& ChemTable::operator[](const int& index)
{
  if (index < 0 || index >= chemicles.size())
  {
    cerr << "ERROR: Subscript out of range." << endl;
    exit(EXIT_FAILURE);
  }
  return chemicles[index];
}

ostream& operator<<(ostream& strm, ChemTable& obj)
{
  cout << "Num\t" << setw(6) << "Symbol" << setw(13) << "Name" << setw(24) << "Weight" << setw(22) << "Min breathable IPP" << setw(20) << "Max Breathable IPP" << setw(15) << "Abund" << endl;
  strm << fixed;
  for (int i = 0; i < obj.count(); i++)
  {
    strm << setprecision(0) << obj[i] << endl;
  }
  return strm;
}

sun::sun()
{
  luminosity = 0;
  mass = 0;
  effTemp = 0;
  specType = "";
  age = 0;
  name = "";
  isCircumbinary = false;
  secondaryMass = 0;
  secondaryLuminosity = 0;
  secondaryEffTemp = 0;
  secondarySpecType = "";
  combinedEffTemp = 0;
}

sun::sun(long double l, long double m, long double t, string s, long double a, string n)
{
  luminosity = l;
  mass = m;
  effTemp = t;
  specType = s;
  age = a;
  name = n;
  isCircumbinary = false;
  secondaryMass = 0;
  secondaryLuminosity = 0;
  secondaryEffTemp = 0;
  secondarySpecType = "";
  combinedEffTemp = 0;
  if (luminosity == 0)
  {
    luminosity = mass_to_luminosity(mass);
  }
  if (mass == 0)
  {
    mass = luminosity_to_mass(luminosity);
  }
  if (effTemp == 0)
  {
    effTemp == spec_type_to_eff_temp(specType);
  }
  if (specType.empty())
  {
    specType = eff_temp_to_spec_type(effTemp, luminosity);
  }
}

sun::sun(sun& right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  effTemp = right.effTemp;
  specType = right.specType;
  age = right.age;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  secondaryMass = right.secondaryMass;
  secondaryLuminosity = right.secondaryLuminosity;
  secondaryEffTemp = right.secondaryEffTemp;
  secondarySpecType = right.secondarySpecType;
  seperation = right.seperation;
  eccentricity = right.eccentricity;
  combinedEffTemp = right.combinedEffTemp;
  if (luminosity == 0)
  {
    luminosity = mass_to_luminosity(mass);
  }
  if (mass == 0)
  {
    mass = luminosity_to_mass(luminosity);
  }
  if (effTemp == 0)
  {
    effTemp == spec_type_to_eff_temp(specType);
  }
  if (specType.empty())
  {
    specType = eff_temp_to_spec_type(effTemp, luminosity);
  }
}

sun::sun(const sun& right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  effTemp = right.effTemp;
  specType = right.specType;
  age = right.age;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  secondaryMass = right.secondaryMass;
  secondaryLuminosity = right.secondaryLuminosity;
  secondaryEffTemp = right.secondaryEffTemp;
  secondarySpecType = right.secondarySpecType;
  seperation = right.seperation;
  eccentricity = right.eccentricity;
  combinedEffTemp = right.combinedEffTemp;
  if (luminosity == 0)
  {
    luminosity = mass_to_luminosity(mass);
  }
  if (mass == 0)
  {
    mass = luminosity_to_mass(luminosity);
  }
  if (effTemp == 0)
  {
    effTemp == spec_type_to_eff_temp(specType);
  }
  if (specType.empty())
  {
    specType = eff_temp_to_spec_type(effTemp, luminosity);
  }
}

/*sun sun::operator=(sun& right)
{
  luminosity = right.luminosity;
  mass = right.mass;
  effTemp = right.effTemp;
  specType = right.specType;
  age = right.age;
  name = right.name;
  isCircumbinary = right.isCircumbinary;
  secondaryMass = right.secondaryMass;
  secondaryLuminosity = right.secondaryLuminosity;
  secondaryEffTemp = right.secondaryEffTemp;
  secondarySpecType = right.secondarySpecType;
  seperation = right.seperation;
  eccentricity = right.eccentricity;
}*/

long double sun::getAge()
{
  return age;
}

long double sun::getEffTemp()
{
  if (effTemp == 0)
  {
    effTemp = spec_type_to_eff_temp(specType);
  }
  return effTemp;
}

long double sun::getLife()
{
  return 1.0E10 * (mass / luminosity);
}

long double sun::getSecondaryLife()
{
  return 1.0E10 * (secondaryMass / secondaryLuminosity);
}

long double sun::getLuminosity()
{
  return luminosity;
}

long double sun::getMass()
{
  return mass;
}

string sun::getName()
{
  return name;
}

long double sun::getREcosphere(long double mass)
{
  return habitable_zone_distance(*this, EARTH_LIKE, mass);
}

string sun::getSpecType()
{
  if (specType.empty())
  {
    specType = eff_temp_to_spec_type(effTemp, luminosity);
  }
  return specType;
}

void sun::setAge(long double a)
{
  age = a;
}

void sun::setEffTemp(long double e)
{
  effTemp = e;
  if (specType.empty())
  {
    specType = eff_temp_to_spec_type(effTemp, luminosity);
  }
}

void sun::setLuminosity(long double l)
{
  luminosity = l;
}

void sun::setMass(long double m)
{
  mass = m;
}

void sun::setName(string n)
{
  name = n;
}

void sun::setSpecType(string s)
{
  specType = s;
  specType = my_strtoupper(specType);
  if (effTemp == 0)
  {
    effTemp = spec_type_to_eff_temp(specType);
  }
}

bool sun::getIsCircumbinary()
{
  return isCircumbinary;
}

long double sun::getSecondaryEffTemp()
{
  return secondaryEffTemp;
}

long double sun::getSecondaryLuminosity()
{
  return secondaryLuminosity;
}

long double sun::getSecondaryMass()
{
  return secondaryMass;
}

string sun::getSecondarySpecType()
{
  return secondarySpecType;
}

void sun::setIsCircumbinary(bool cb)
{
  isCircumbinary = cb;
  if (isCircumbinary == false)
  {
    combinedEffTemp = 0;
  }
}

void sun::setSecondaryEffTemp(long double et)
{
  secondaryEffTemp = et;
  if (secondarySpecType.empty())
  {
    secondarySpecType = eff_temp_to_spec_type(secondaryEffTemp, secondaryLuminosity);
  }
}

void sun::setSecondaryLuminosity(long double l)
{
  secondaryLuminosity = l;
  if (secondaryMass == 0)
  {
    secondaryMass = luminosity_to_mass(secondaryLuminosity);
  }
}

void sun::setSecondaryMass(long double m)
{
  secondaryMass = m;
  if (secondaryLuminosity == 0)
  {
    secondaryLuminosity = mass_to_luminosity(secondaryMass);
  }
}

void sun::setSecondarySpecType(string t)
{
  secondarySpecType = t;
  if (secondaryEffTemp == 0)
  {
    secondaryEffTemp = spec_type_to_eff_temp(secondarySpecType);
  }
}

long double sun::getCombinedLuminosity()
{
  return luminosity + secondaryLuminosity;
}

long double sun::getCombinedMass()
{
  return mass + secondaryMass;
}

long double sun::getEccentricity()
{
  return eccentricity;
}

long double sun::getSeperation()
{
  return seperation;
}

void sun::setEccentricity(long double e)
{
  eccentricity = e;
}

void sun::setSeperation(long double s)
{
  seperation = s;
}

long double sun::getMinStableDistance()
{
  long double u;
  if (!isCircumbinary)
  {
    return 0;
  }
  else
  {
    u = mass / (mass + secondaryMass);
    return seperation * (1.60 + (5.10 * eccentricity) - (2.22 * pow2(eccentricity)) + (4.12 * u) - (4.27 * eccentricity * u) - (5.09 * pow2(u)) + (4.61 * pow2(eccentricity) * pow2(u)));
  }
}

long double sun::getCombinedEffTemp()
{
  long double f1, f2, prev, curr, peak, temperature, a, m, b;
  if (combinedEffTemp != 0)
  {
    return combinedEffTemp;
  }
  if (!isCircumbinary) // This shouldn't happen but if it does, just return the temp of the star
  {
    combinedEffTemp = effTemp;
    return effTemp;
  }
  else
  {
    //effTemp = 5800;
    //secondaryEffTemp = 4400;
    f1 = f2 = prev = curr = peak = 0;
    for (long double i = 0; i < 1500.0; i += ACCURACY_FOR_PEAK)
    {
      prev = curr;
      f1 = calcFlux(effTemp, i);
      f2 = calcFlux(secondaryEffTemp, i);
      curr = f1 + f2;
      //cout << i << ": " << f1 << " " << f2 << " " << curr << endl;
      if (prev > curr)
      {
	peak = i - ACCURACY_FOR_PEAK;
	break;
      }
    }
    //cout << "Primary Temp: " << toString(effTemp) << endl;
    //cout << "Secondary Temp: " << toString(secondaryEffTemp) << endl;
    //cout << "Peak: " << toString(peak) << endl;;
    a = 0.0;
    m = 1000000000.0;
    b = 1.0;
    peak = pow((peak - a) / m, 1 / b);
    temperature = (0.0028977685 / peak) - 273.15;
    a = 273.15;
    m = 1.0;
    b = 1.0;
    temperature = (pow(temperature, b) * m) + a;
    //cout << "Combined temp: " << toString(temperature) << endl;
    //exit(EXIT_FAILURE);
    combinedEffTemp = temperature;
    return temperature;
  }
}

planet::planet()
{
  planetNo = 0;
  a = 0;
  e = 0;
  axialTilt = 0;
  gasGiant = false;
  dustMass = 0;
  gasMass = 0;
  imf = 0;
  rmf = 0;
  cmf = 0;
  moonA = 0;
  moonE = 0;
  coreRadius = 0;
  radius = 0;
  orbitZone = 0;
  density = 0;
  orbPeriod = 0;
  day = 0;
  resonantPeriod = false;
  escVelocity = 0;
  surfAccel = 0;
  surfGrav = 0;
  rmsVelocity = 0;
  molecWeight = 0;
  volatileGasInventory = 0;
  surfPressure = 0;
  greenhouseEffect = false;
  boilPoint = 0;
  albedo = 0;
  exosphericTemp = 0;
  estimatedTemp = 0;
  estimatedTerrTemp = 0;
  surfTemp = 0;
  greenhsRise = 0;
  highTemp = 0;
  lowTemp = 0;
  maxTemp = 0;
  minTemp = 0;
  hydrosphere = 0;
  cloudCover = 0;
  iceCover = 0;
  inclination = 0;
  ascendingNode = 0;
  longitudeOfPericenter = 0;
  meanLongitude = 0;
  first_moon = NULL;
  next_planet = NULL;
  reconnect_to = NULL;
  first_moon_backup = NULL;
  type = tUnknown;
  deleteable = true;
}

planet::planet(int n, long double a2, long double e2, long double t, bool gg, long double d, long double g, planet* moon, planet* next)
{
  planetNo = n;
  a = a2;
  e = e2;
  axialTilt = t;
  gasGiant = gg;
  dustMass = d;
  gasMass = g;
  imf = 0;
  rmf = 0;
  cmf = 0;
  moonA = 0;
  moonE = 0;
  coreRadius = 0;
  radius = 0;
  orbitZone = 0;
  density = 0;
  orbPeriod = 0;
  day = 0;
  resonantPeriod = false;
  escVelocity = 0;
  surfAccel = 0;
  surfGrav = 0;
  rmsVelocity = 0;
  molecWeight = 0;
  volatileGasInventory = 0;
  surfPressure = 0;
  greenhouseEffect = false;
  boilPoint = 0;
  albedo = 0;
  exosphericTemp = 0;
  estimatedTemp = 0;
  estimatedTerrTemp = 0;
  surfTemp = 0;
  greenhsRise = 0;
  highTemp = 0;
  lowTemp = 0;
  maxTemp = 0;
  minTemp = 0;
  hydrosphere = 0;
  cloudCover = 0;
  iceCover = 0;
  inclination = 0;
  ascendingNode = 0;
  longitudeOfPericenter = 0;
  meanLongitude = 0;
  first_moon = moon;
  next_planet = next;
  reconnect_to = next;
  first_moon_backup = moon;
  type = tUnknown;
  deleteable = true;
}

planet::~planet()
{
  planet *node = NULL;
  planet *next = NULL;
  
  a = 0;
  e = 0;
  axialTilt = 0;
  gasGiant = false;
  dustMass = 0;
  gasMass = 0;
  imf = 0;
  rmf = 0;
  cmf = 0;
  moonA = 0;
  moonE = 0;
  coreRadius = 0;
  radius = 0;
  orbitZone = 0;
  density = 0;
  orbPeriod = 0;
  day = 0;
  resonantPeriod = false;
  escVelocity = 0;
  surfAccel = 0;
  surfGrav = 0;
  rmsVelocity = 0;
  molecWeight = 0;
  volatileGasInventory = 0;
  surfPressure = 0;
  greenhouseEffect = false;
  boilPoint = 0;
  albedo = 0;
  exosphericTemp = 0;
  estimatedTemp = 0;
  estimatedTerrTemp = 0;
  surfTemp = 0;
  greenhsRise = 0;
  highTemp = 0;
  lowTemp = 0;
  maxTemp = 0;
  minTemp = 0;
  hydrosphere = 0;
  cloudCover = 0;
  iceCover = 0;
  inclination = 0;
  ascendingNode = 0;
  longitudeOfPericenter = 0;
  meanLongitude = 0;
  while (!atmosphere.empty())
  {
    atmosphere.pop_back();
  }
  if (first_moon != NULL)
  {
    for (node = first_moon; node != NULL; node = next)
    {
      next = node->next_planet;
      if (node->getDeletable())
      {
	delete node;
      }
      else
      {
	node->next_planet = node->reconnect_to;
      }
    }
  }
  if (first_moon_backup != NULL)
  {
    first_moon = first_moon_backup;
  }
}

void planet::addGas(gas g)
{
  bool unique = true;
  // this shouldn't be necessary but for some weird reason, it is.
  for (int i = 0; i < atmosphere.size(); i++)
  {
    if (g.getNum() == atmosphere[i].getNum())
    {
      unique = false;
      break;
    }
  }
  if (unique)
  {
    atmosphere.push_back(g);
    quicksort(atmosphere, 0, atmosphere.size());
  }
}

/*void planet::addMoon(planet* moon)
{
  temp_moon.push_back(moon);
}*/

void planet::clearGases()
{
  while (!atmosphere.empty())
  {
    atmosphere.pop_back();
  }
}

/*void planet::deleteMoon(int i)
{
  planet *the_moon = temp_moon[i];
  vector<planet *>::iterator it;
  if (temp_moon[i] != NULL)
  {
    if (temp_moon[i]->next_planet == NULL)
    {
      delete temp_moon[i];
    }
    else
    {
      for (it = temp_moon.begin(); it != temp_moon.end(); it++)
      {
	if (*it == the_moon)
	{
	  temp_moon.erase(it);
	  break;
	}
      }
    }
  }
}*/

void planet::estimateMass()
{
  dustMass = quintic_trend(0.126438418015041, -0.971586985798294, 2.30299559510187, 0.0114340742264797, -0.747842501143578, 0.27996106732024, knownRadius);
}

long double planet::getA()
{
  return a;
}

long double planet::getAlbedo()
{
  return albedo;
}

long double planet::getAscendingNode()
{
  return ascendingNode;
}

long double planet::getAxialTilt()
{
  return axialTilt;
}

long double planet::getBoilPoint()
{
  return boilPoint;
}

long double planet::getCloudCover()
{
  return cloudCover;
}

long double planet::getCmf()
{
  return cmf;
}

long double planet::getCoreRadius()
{
  return coreRadius;
}

long double planet::getDay()
{
  return day;
}

bool planet::getDeletable()
{
  return deleteable;
}

long double planet::getDensity()
{
  return density;
}

long double planet::getDustMass()
{
  return dustMass;
}

long double planet::getE()
{
  return e;
}

long double planet::getEquatrorialRadius()
{
  return radius * (1.0 + getOblateness());
}

long double planet::getEscVelocity()
{
  return escVelocity;
}

long double planet::getEsi()
{
  return esi;
}

long double planet::getEstimatedTemp()
{
  return estimatedTemp;
}

long double planet::getEstimatedTerrTemp()
{
  return estimatedTerrTemp;
}

long double planet::getExosphericTemp()
{
  return exosphericTemp;
}

gas planet::getGas(int i)
{
  return atmosphere[i];
}

bool planet::getGasGiant()
{
  return gasGiant;
}

long double planet::getGasMass()
{
  return gasMass;
}

bool planet::getGreenhouseEffect()
{
  return greenhouseEffect;
}

long double planet::getGreenhsRise()
{
  return greenhsRise;
}

long double planet::getHighTemp()
{
  return highTemp;
}

long double planet::getHydrosphere()
{
  return hydrosphere;
}

long double planet::getHza()
{
  return hza;
}

long double planet::getHzc()
{
  return hzc;
}

long double planet::getHzd()
{
  return hzd;
}

long double planet::getIceCover()
{
  return iceCover;
}

long double planet::getImf()
{
  return imf;
}

long double planet::getInclination()
{
  return inclination;
}

long double planet::getKnownRadius()
{
  return knownRadius;
}

long double planet::getLongitudeOfPericenter()
{
  return longitudeOfPericenter;
}

long double planet::getLowTemp()
{
  return lowTemp;
}

long double planet::getMass()
{
  return dustMass + gasMass;
}

long double planet::getMaxTemp()
{
  return maxTemp;
}

long double planet::getMeanLongitude()
{
  return meanLongitude;
}

int planet::getMinorMoons()
{
  return minorMoons;
}

long double planet::getMinTemp()
{
  return minTemp;
}

long double planet::getMolecWeight()
{
  return molecWeight;
}

/*planet* planet::getMoon(int i)
{
  return temp_moon[i];
}*/

long double planet::getMoonA()
{
  return moonA;
}

/*int planet::getMoonCount()
{
  return temp_moon.size();
}*/

long double planet::getMoonE()
{
  return moonE;
}

long double planet::getOblateness()
{
  //return oblateness;
  long double multiplier = 0;
  long double result = 0;
  long double mass_in_eu = 0;
  long double planetary_mass_in_grams = 0;
  long double equatorial_radius_in_cm = 0;
  long double k2 = 0;
  long double ang_velocity = 0;
  planet *the_planet(this);
  
  if (type == tBrownDwarf || type == tGasGiant || type == tSubGasGiant || type == tSubSubGasGiant)
  {
    mass_in_eu = (dustMass + gasMass) * SUN_MASS_IN_EARTH_MASSES;
    if (type == tSubGasGiant || type == tSubSubGasGiant)
    {
      multiplier = 4.94E-12;
    }
    else if (type == tGasGiant)
    {
      multiplier = 5.56E-12;
    }
    result = multiplier * (pow(radius, 3.0) / (mass_in_eu * pow(day, 2.0)));
  }
  else
  {
    planetary_mass_in_grams = getMass() * SOLAR_MASS_IN_GRAMS;
    equatorial_radius_in_cm = radius * CM_PER_KM;
    k2 = calculate_moment_of_inertia_coeffient(the_planet);
    while (day == 0)
    {
      cerr << "Error! The day is 0 hours long!" << endl;
      exit(EXIT_FAILURE);
    }
    ang_velocity = RADIANS_PER_ROTATION / (SECONDS_PER_HOUR * day);
    result = calcOblateness_improved(ang_velocity, planetary_mass_in_grams, equatorial_radius_in_cm, k2);
  }
  if (result > 0.5)
  {
    result = 0.5;
  }
  return result;
}

int planet::getOrbitZone()
{
  return orbitZone;
}

long double planet::getOrbPeriod()
{
  return orbPeriod;
}

int planet::getPlanetNo()
{
  return planetNo;
}

long double planet::getPolarRadius()
{
  return radius * (1.0 - getOblateness());
}

long double planet::getRadius()
{
  return radius;
}

bool planet::getResonantPeriod()
{
  return resonantPeriod;
}

long double planet::getRmf()
{
  return rmf;
}

long double planet::getRmsVelocity()
{
  return rmsVelocity;
}

long double planet::getSph()
{
  return sph;
}

long double planet::getSurfAccel()
{
  return surfAccel;
}

long double planet::getSurfGrav()
{
  return surfGrav;
}

long double planet::getSurfPressure()
{
  return surfPressure;
}

long double planet::getSurfTemp()
{
  return surfTemp;
}

sun& planet::getTheSun()
{
  return theSun;
}

planet_type planet::getType()
{
  return type;
}

long double planet::getVolatileGasInventory()
{
  return volatileGasInventory;
}

void planet::setA(long double a2)
{
  a = a2;
}

void planet::setAlbedo(long double al)
{
  albedo = al;
}

void planet::setAscendingNode(long double as)
{
  ascendingNode = as;
}

void planet::setAxialTilt(long double ax)
{
  axialTilt = fix_inclination(ax);
}

void planet::setBoilPoint(long double b)
{
  boilPoint = b;
}

void planet::setCloudCover(long double c)
{
  cloudCover = c;
}

void planet::setCmf(long double c)
{
  cmf = c;
}

void planet::setCoreRadius(long double c)
{
  coreRadius = c;
}

void planet::setDay(long double d)
{
  day = d;
}

void planet::setDeletable(bool d)
{
  deleteable = d;
}

void planet::setDensity(long double d)
{
  if (d < 0)
  {
    d *= 1;
  }
  density = d;
}

void planet::setDustMass(long double d)
{
  dustMass = d;
}

void planet::setE(long double e2)
{
  e = e2;
}

void planet::setEscVelocity(long double es)
{
  escVelocity = es;
}

void planet::setEsi(long double es)
{
  esi = es;
}

void planet::setEstimatedTemp(long double es)
{
  estimatedTemp = es;
}

void planet::setEstimatedTerrTemp(long double es)
{
  estimatedTerrTemp = es;
}

void planet::setExosphericTemp(long double ex)
{
  exosphericTemp = ex;
}

void planet::setGasGiant(bool g)
{
  gasGiant = g;
}

void planet::setGasMass(long double g)
{
  if (g > 0.0) // make sure the planet is set as a gas giant if gas makes up part of its mass
  {
    gasGiant = true;
  }
  else
  {
    gasGiant = false;
  }
  gasMass = g;
}

void planet::setGreenhouseEffect(bool g)
{
  greenhouseEffect = g;
}

void planet::setGreenhsRise(long double g)
{
  greenhsRise = g;
}

void planet::setHighTemp(long double h)
{
  highTemp = h;
}

void planet::setHydrosphere(long double h)
{
  hydrosphere = h;
}

void planet::setHza(long double h)
{
  hza = h;
}

void planet::setHzc(long double h)
{
  hzc = h;
}

void planet::setHzd(long double h)
{
  hzd = h;
}

void planet::setIceCover(long double i)
{
  if (i > 1.0)
  {
    i = 0.0;
  }
  iceCover = i;
}

void planet::setImf(long double i)
{
  if (i > 1.0)
  {
    i = 0.0;
  }
  imf = i;
}

void planet::setInclination(long double in)
{
  inclination = fix_inclination(in);
}

void planet::setKnownRadius(long double k)
{
  long double water_min, water_max, rock_min, rock_max;
  water_min = rock_min = 0.0;
  water_max = rock_max = 1.0;
  knownRadius = k;
  estimateMass();
  if (dustMass > EM(2.0))
  {
  }
  else
  {
    
  }
}

void planet::setLongitudeOfPericenter(long double lon)
{
  longitudeOfPericenter = lon;
}

void planet::setLowTemp(long double l)
{
  lowTemp = l;
}

void planet::setMaxTemp(long double m)
{
  maxTemp = m;
}

void planet::setMeanLongitude(long double me)
{
  meanLongitude = me;
}

void planet::setMinorMoons(int m)
{
  minorMoons = m;
}


void planet::setMinTemp(long double m)
{
  minTemp = m;
}

void planet::setMolecWeight(long double m)
{
  molecWeight = m;
}

void planet::setMoonA(long double m)
{
  moonA = m;
}

void planet::setMoonE(long double m)
{
  moonE = m;
}

int planet::getNumGases()
{
  return atmosphere.size();
}

void planet::setOblateness(long double o)
{
  oblateness = o;
}

void planet::setOrbitZone(int o)
{
  orbitZone = o;
}

void planet::setOrbPeriod(long double o)
{
  orbPeriod = o;
}

void planet::setPlanetNo(int n)
{
  planetNo = n;
}

void planet::setRadius(long double r)
{
  if (r < 0)
  {
    r *= -1;
  }
  radius = r;
}

void planet::setResonantPeriod(bool r)
{
  resonantPeriod = r;
}

void planet::setRmf(long double r)
{
  rmf = r;
}

void planet::setRmsVelocity(long double r)
{
  rmsVelocity = r;
}

void planet::setSph(long double s)
{
  sph = s;
}

void planet::setSurfAccel(long double s)
{
  surfAccel = s;
}

void planet::setSurfGrav(long double s)
{
  surfGrav = s;
}

void planet::setSurfPressure(long double s)
{
  surfPressure = s;
}

void planet::setSurfTemp(long double s)
{
  surfTemp = s;
}

void planet::setTheSun(sun& s)
{
  theSun = s;
}

void planet::setType(planet_type t)
{
  type = t;
}

void planet::setVolatileGasInventory(long double v)
{
  volatileGasInventory = v;
}

void planet::sortMoons()
{
  planet *prev = NULL;
  planet *next = NULL;
  planet *node = NULL;
  //planet *temp = NULL;
  vector <planet *> temp_vector;
  long double roche_limit = 0;
  long double hill_sphere = 0;
  for (node = first_moon; node != NULL; node = next)
  {
    next = node->next_planet;
    node->next_planet = NULL;
    temp_vector.push_back(node);
  }
  first_moon = NULL;
  for (int i = 0; i < temp_vector.size(); i++)
  {
    // we shouldn't have to do this here but some moons that shouldn't 
    // be possible somehow slip throw the cracks...
    hill_sphere = a * KM_PER_AU * pow(getMass() / (3.0 * theSun.getMass()), 1.0 / 3.0);
    roche_limit = 2.44 * radius * pow(density / temp_vector[i]->getDensity(), 1.0 / 3.0);
    if ((roche_limit * 1.5) >= (hill_sphere / 3.0))
    {
      delete temp_vector[i];
    }
    else if ((temp_vector[i]->getMoonA() * KM_PER_AU) < (roche_limit * 1.5))
    {
      delete temp_vector[i];
    }
    else if ((temp_vector[i]->getMoonA() * KM_PER_AU) > (hill_sphere / 3.0))
    {
      delete temp_vector[i];
    }
    // if it passed all those tests, we can place the moon.
    else
    {
      if (first_moon == NULL)
      {
	first_moon = temp_vector[i];
      }
      else if (temp_vector[i]->getMoonA() < first_moon->getMoonA())
      {
	temp_vector[i]->next_planet = first_moon;
	first_moon = temp_vector[i];
      }
      else if (first_moon->next_planet == NULL)
      {
	first_moon->next_planet = temp_vector[i];
	temp_vector[i]->next_planet = NULL;
      }
      else
      {
	next = first_moon;
	while (next != NULL && next->getMoonA() < temp_vector[i]->getMoonA())
	{
	  prev = next;
	  next = next->next_planet;
	}
	temp_vector[i]->next_planet = next;
	if (prev != NULL)
	{
	  prev->next_planet = temp_vector[i];
	}
      }
    }
  }
}

bool planet::operator<(planet& right)
{
  if (a < right.a)
  {
    return true;
  }
  else if (moonA < right.moonA)
  {
    return true;
  }
  else if (e < right.e)
  {
    return true;
  }
  else if (moonE < right.moonE)
  {
    return true;
  }
  return false;
}

bool planet::operator==(planet& right)
{
  if (a == right.a && moonA == right.moonA && e == right.e && moonE == right.moonE)
  {
    return true;
  }
  return false;
}

dust::dust()
{
  innerEdge = 0;
  outerEdge = 0;
  dustPresent = true;
  gasPresent = true;
  next_band = NULL;
}

dust::~dust()
{
  innerEdge = 0;
  outerEdge = 0;
  dustPresent = false;
  gasPresent = false;
  //next_band = NULL;
}

bool dust::getDustPresent()
{
  return dustPresent;
}

bool dust::getGasPresent()
{
  return gasPresent;
}

long double dust::getInnerEdge()
{
  if (innerEdge < outerEdge)
  {
    return innerEdge;
  }
  else
  {
    innerEdge = 0;
    return innerEdge;
  }
}

long double dust::getOuterEdge()
{
  return outerEdge;
}

void dust::setDustPresent(bool d)
{
  dustPresent = d;
}

void dust::setGasPresent(bool g)
{
  gasPresent = g;
}

void dust::setInnerEdge(long double i)
{
  innerEdge = i;
}

void dust::setOuterEdge(long double o)
{
  outerEdge = o;
}

gen::gen()
{
  dusts = NULL;
  planets = NULL;
  next = NULL;
}

gen::~gen()
{
  //dusts = NULL;
  //planets = NULL;
  //next = NULL;
}

gas::gas()
{
  num = 0;
  surfPressure = 0;
}

int gas::getNum()
{
  return num;
}

long double gas::getSurfPressure()
{
  return surfPressure;
}

void gas::setNum(int n)
{
  num = n;
}

void gas::setSurfPressure(long double s)
{
  surfPressure = s;
}

bool gas::operator<(gas& right)
{
  if (surfPressure > right.surfPressure)
  {
    return true;
  }
  return false;
}

bool gas::operator==(gas& right)
{
  if (surfPressure == right.surfPressure)
  {
    return true;
  }
  return false;
}

ostream& operator<<(ostream& strm, gas& obj)
{
  strm << obj.getNum() << " - " << obj.getSurfPressure() << endl;
  return strm;
}