#include "Planetary_Habitability_Laboratory.h"
#include "const.h"
#include "planets.h"

using namespace std;

catalog phl;

void initPlanetaryHabitabilityLaboratory()
{
  phl.setArg("PHL");
  // 			L			Mass			Eff_Temp	Spec Type	Mass2			Eccen.	SMAxis	 	inclination	ascending node	Planets			Designation		InCel	Name
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,		0,		mercury,		"Sol",			true,	"The Solar System");
  phl.addStar(sol);
  star gliese667C(	0.0137,			0.33,			3350,		"M2V",		(0.73 + 0.69),		0,	230,		0,		0,		gliese667Cb,		"GJ 667C",		true,	"Gliese 667C");
  phl.addStar(gliese667C);
  star kepler62(	0.200138,		0.69,			4869,		"K2V",		0,			0,	0,		0,		0,		kepler62b,		"Kepler-62",		true,	"Kepler-62");
  phl.addStar(kepler62);
  star kepler283(	0.1045,			0.596,			4351,		"",		0,			0,	0,		0,		0,		kepler283b,		"Kepler-283",		true,	"Kepler-283");
  phl.addStar(kepler283);
  star kepler296(	0.091709,		0.61,			4292,		"",		0,			0,	0,		0,		0,		kepler296b,		"Kepler-296",		true,	"Kepler-296");
  phl.addStar(kepler296);
  star TAUCet(		0.52,			0.783,			5344,		"G8V",		0,			0,	0,		0,		0,		taucetb,		"TAU Cet",		true,	"Tau Ceti");
  phl.addStar(TAUCet);
  star gliese180(	0.013018,		0.43,			3371,		"M2V",		0,			0,	0,		0,		0,		gliese180b,		"GJ 180",		true,	"Gliese 180");
  phl.addStar(gliese180);
  star gliese581(	0.01209,		0.31,			3498,		"M3V",		0,			0,	0,	 	0,		0,		gliese581e,		"Gl 581",		true,	"Gliese 581");
  phl.addStar(gliese581);
  star gliese163(	0.021975,		0.4,			3500,		"M4V",		0,			0,	0,		0,		0,		gliese163b,		"GJ 163",		true,	"Gliese 163");
  phl.addStar(gliese163);
  star hd40307(		0.233304,		0.77,			4977,		"K2V",		0,			0,	0,		0,		0,		hd40307b,		"HD 40307",		true,	"HIP 27887");
  phl.addStar(hd40307);
  star kepler61(	0.089801,		0.64,			4017,		"K7V",		0,			0,	0,		0,		0,		kepler61b,		"Kepler-61",		true,	"Kepler-61");
  phl.addStar(kepler61);
  star gliese422(	0.011015,		0.32,			3323,		"M4V",		0,			0,	0,		0,		0,		gliese422b,		"GJ 422",		true,	"Gliese 422");
  phl.addStar(gliese422);
  star kepler22(	0.797227,		0.97,			5518,		"G5V",		0,			0,	0,		0,		0,		kepler22b,		"Kepler-22",		true,	"Kepler-22");
  phl.addStar(kepler22);
  star kepler298(	0.119959,		0.65,			4465,		"",		0,			0,	0,		0,		0,		kepler298b,		"Kepler-298",		true,	"Kepler-298");
  phl.addStar(kepler298);
  star kapteyn(		0.011984,		0.28,			3550,		"M1V",		0,			0,	0,		0,		0,		kapteynb,		"Kapteyn",		true,	"Kapteyn's Star");
  phl.addStar(kapteyn);
  star kepler186(	0.0412,			0.48,			3788,		"M0V",		0,			0,	0,		0,		0,		kepler186b,		"Kepler-186",		true,	"Kepler-186");
  phl.addStar(kepler186);
  star kepler174(	0.195593,		0.68,			4880,		"",		0,			0,	0,		0,		0,		kepler174b,		"Kepler-174",		true,	"Kepler-174");
  phl.addStar(kepler174);
  star gliese682(	0.002003,		0.27,			3028,		"M4V",		0,			0,	0,		0,		0,		gliese682b,		"GJ 682",		true,	"Gliese 682");
  phl.addStar(gliese682);
  // These are stars that have gas giants that could have habitable moons
  star hd38529(		5.626708,		1.48,			5697,		"G4IV",		0,			0,	0,		0,		0,		hd38529b,		"HD 38529",		true,	"HIP 27253");
  phl.addStar(hd38529);
  star hd202206(	1.020379,		1.13,			5750,		"G6V",		0,			0,	0,		0,		0,		hd202206b,		"HD 202206",		true,	"HIP 104903");
  phl.addStar(hd202206);
  star hd8673(		3.598954,		1.31,			6413,		"F7V",		0,			0,	0,		0,		0,		hd8673b,		"HD 8673",		true,	"HIP 6702");
  phl.addStar(hd8673);
  star hd22781(		0.310872,		0.74,			5072,		"K0V",		0,			0,	0,		0,		0,		hd22781b,		"HD 22781",		true,	"HIP 17187");
  phl.addStar(hd22781);
  star hd217786(	1.833286,		1.02,			5966,		"F8V",		0,			0,	0,		0,		0,		hd217786b,		"HD 217786",		true,	"HIP 113834");
  phl.addStar(hd217786);
  star hd106270(	5.665917,		1.32,			5638,		"G5IV",		0,			0,	0,		0,		0,		hd106270b,		"HD 106270",		true,	"HIP 59625");
  phl.addStar(hd106270);
  star hd38801(		4.270497,		1.36,			5222,		"K0IV",		0,			0,	0,		0,		0,		hd38801b,		"HD 38801",		true,	"HIP 27384");
  phl.addStar(hd38801);
  star hd39091(		4.755538,		1.1,			5888,		"G1IV",		0,			0,	0,		0,		0,		hd39091b,		"HD 39091",		true,	"HIP 26394");
  phl.addStar(hd39091);
  star upsand(		3.55405,		1.27,			6212,		"F8V",		mass(0.00163),		0,	750,	 	0,		0,		UPSAndAb,		"UPS And A",		true,	"Upsilon Andromedae A");
  phl.addStar(upsand);
  star hd141937(	1.242381,		1.1,			5925,		"G2V",		0,			0,	0,		0,		0,		hd141937b,		"HD 141937",		true,	"HIP 77740");
  phl.addStar(hd141937);
  star hd33564(		1.656514,		1.25,			6250,		"F6V",		0,			0,	0,		0,		0,		hd33564b,		"HD 33564",		true,	"HIP 25110");
  phl.addStar(hd33564);
  star hd23596(		4.710355,		1.27,			5888,		"F8V",		0,			0,	0,		0,		0,		hd23596b,		"HD 23596",		true,	"HIP 17747");
  phl.addStar(hd23596);
  star hd222582(	1.219453,		0.99,			5662,		"G5V",		0,			0,	0,		0,		0,		hd222582b,		"HD 222582",		true,	"HIP 116906");
  phl.addStar(hd222582);
  star hd86264(		4.715981,		1.42,			6210,		"F7V",		0,			0,	0,		0,		0,		hd86264b,		"HD 86264",		true,	"HIP 48780");
  phl.addStar(hd86264);
  star hd196067(	6.680477,		1.28,			5940,		"G0V",		0,			0,	0,		0,		0,		hd196067b,		"HD 196067",		true,	"HIP 102125");
  phl.addStar(hd196067);
  star hd10697(		2.68764,		1.15,			5641,		"G5IV",		0,			0,	0,		0,		0,		hd10697b,		"HD 10697",		true,	"HIP 8159");
  phl.addStar(hd10697);
  star hd28185(		0.859647,		1.24,			5482,		"G5V",		0,			0,	0,		0,		0,		hd28185b,		"HD 28185",		true,	"HIP 20723");
  phl.addStar(hd28185);
  star hd132406(	1.830276,		1.09,			5885,		"G0V",		0,			0,	0,		0,		0,		hd132406b,		"HD 132406",		true,	"HIP 73146");
  phl.addStar(hd132406);
  star hd13908(		4.026799,		1.29,			6255,		"F8V",		0,			0,	0,		0,		0,		hd13908b,		"HD 13908",		true,	"HIP 10743");
  phl.addStar(hd13908);
  star hd2039(		1.643056,		0.98,			5947,		"G2V",		0,			0,	0,		0,		0,		hd2039b,		"HD 2039",		true,	"HIP 1931");
  phl.addStar(hd2039);
  star hd82943(		1.339867,		1.18,			5874,		"G0V",		0,			0,	0,		0,		0,		hd82943c,		"HD 82943",		true,	"HIP 47007");
  phl.addStar(hd82943);
  star moa2011blg293l(	0.547008,		0.86,			5180,		"",		0,			0,	0,		0,		0,		moa2011blg293lb,	"MOA-2011-BLG-293L",	true,	"MOA-2011-BLG-293L");
  phl.addStar(moa2011blg293l);
  star hd213240(	2.572906,		1.22,			5975,		"G4IV",		0,			0,	0,		0,		0,		hd213240b,		"HD 213240",		true,	"HIP 111143");
  phl.addStar(hd213240);
}