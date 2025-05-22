#include "star_trek.h"
#include "const.h"
#include "planets.h"

catalog star_trek;

void initStarTrek()
{
  star_trek.setArg("G");
  // 			L					Mass						Eff_Temp	Spec Type	Mass2			Eccen.	SMAxis	 	inclination	ascending node	Planets		Designation	InCel	Name
  star sol(		1.0,					1.00,						5780,		"G2V",		0,			0,	0,		0,		0,		mercury,	"Sol",		true,	"The Solar System");
  star_trek.addStar(sol);
  star bajor(		abs2luminosity(4.7),			mass(abs2luminosity(4.7)),			5780,		"G2V",		0,			0,	0,		0,		0,		bajorI,		"Bajor",	true,	"B'hava'el");
  star_trek.addStar(bajor);
  star cardassia(	abs2luminosity((-1.1)),			mass(abs2luminosity((-1.1))),			0,		"K0V",		0,			0,	0,		0,		0,		NULL,		"Cardassia",	true,	"Cardassia");
  star_trek.addStar(cardassia);
  star talos(		abs2luminosity(0.1),			mass(abs2luminosity(0.1)),			0,		"M0IV",		0,			0,	0,		0,		0,		NULL,		"Talos",	true,	"Talos Prime");
  star_trek.addStar(talos);
  star deneb_kaitos(	139.1,					2.8,						4797,		"K0III",	0,			0,	0,		0,		0,		NULL,		"Deneb Kaitos",	true,	"Deneb");
  star_trek.addStar(deneb_kaitos);
  star Eri40(		0.46,					0.84,						5300,		"K1V",		(0.2+0.5),    		0,	418.,		0,		0,		NULL,		"40 Eri",	true,	"Vulcan");
  star_trek.addStar(Eri40);
  star beta_rigel(	abs2luminosity(6.2),			mass(abs2luminosity(6.2)),			0,		"A5V",		0,			0,	0,		0,		0,		NULL,		"BET Rig",	true,	"Beta Rigel");
  star_trek.addStar(beta_rigel);
  star aldebaran(	518,					1.7,						3910,		"K5III",	0,			0,	0,		0,		0,		NULL,		"ALF Tau",	true,	"Aldebran");
  star_trek.addStar(aldebaran);
  star altair(		10.6,					1.79,						6900,		"A7V",		0,			0,	0,		0,		0,		NULL,		"ALF Aql",	true,	"Altair");
  star_trek.addStar(altair);
  star antaresa(	57500,					12.4,						3400,		"M1I-b",	10,			0,	529,		0,		0,		NULL,		"ALF Sco A",	true,	"Antares A");
  star_trek.addStar(antaresa);
  star antaresb(	0,					10,						18500,		"B2V",		12.4,			0,	529,		0,		0,		NULL,		"ALF Sco B",	true,	"Antares B");
  star_trek.addStar(antaresb);
  star arcturus(	170,					1.1,						4290,		"K1III",	0,			0,	0,		0,		0,		NULL,		"ALF Boo",	true,	"Arcturus");
  star_trek.addStar(arcturus);
  star aaamazzara(	abs2luminosity(2.04),			1.85,						8400,		"A2V",		0,			0,	0,		0,		0,		NULL,		"EPS Sep",	true,	"Aaamazzara");
  star_trek.addStar(aaamazzara);
  star sirius(		25.4,					2.02,						9940,		"A1V",		0.978,			0.5923,	19.8,		0,		0,		NULL,		"ALF CMa",	true,	"Sirius");
  star_trek.addStar(sirius);
  star ALFCenA(		1.519,					1.10,						5790,		"G2V",		0.907,			0.52,	23.7,		0,		0,		NULL,		"ALF Cen A",	true,	"Alpha Centauri A");
  star_trek.addStar(ALFCenA);
  star ALFCenB(		0.5,					0.907,						5260,		"K1V",		1.10,			0.52,	23.7,		0,		0,		alfcentbb,	"ALF Cen B",	true,	"Alpha Centauri B");
  star_trek.addStar(ALFCenB);
  star procyon(		6.93,					1.42,						6530,		"F5V",		0.602,			0.407,	15,		0,		0,		NULL,		"ALF CMi",	true,	"Andoria");
  star_trek.addStar(procyon);
  star antos(		abs2luminosity(vis2abs(5.2, 98)),	mass(abs2luminosity(vis2abs(5.2, 98))),		0,		"G2IV",		0,			0,	0,		0,		0,		NULL,		"KAP Del",	true,	"Antos");
  star_trek.addStar(antos);
  star ardana(		abs2luminosity(vis2abs(3.88, 124)),	mass(abs2luminosity(vis2abs(3.88, 124))),	0,		"K2III",	0,			0,	0,		0,		0,		NULL,		"MU Leo",	true,	"Ardana");
  star_trek.addStar(ardana);
  star argelius(	11.5,					AVE(1.62, 1.7),					6739,		"F3V",		0,			0,	0,		0,		0,		NULL,		"IOT Leo",	true,	"Argelius");
  star_trek.addStar(argelius);
  star aurelia(		62,					2.26,						4963,		"G8III",	0,			0,	0,		0,		0,		NULL,		"XI Her",	true,	"Aurelia");
  star_trek.addStar(aurelia);
  star axanar(		0.34,					0.82,						5084,		"K2V",		0,			0,	0,		0,		0,		NULL,		"EPS Eri",	true,	"Axanar");
  star_trek.addStar(axanar);
  
  star_trek.sort();
}