#include "dole.h"
#include "const.h"
#include "planets.h"

catalog dole;

void initDole()
{
  dole.setArg("D");
  // 			L			Mass			Eff_Temp	Spec Type	Mass2			Eccen.	SMAxis	 		Planets		Designation	InCel	Name
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,0,	mercury,	"Sol",		true,	"The Solar System");
  star ALFCenA(		1.519,			1.10,			5790,		"G2V",		0.907,			0.52,	23.7,		0,0,	NULL,		"ALF Cen A",	true,	"Alpha Centauri A");
  star ALFCenB(		0.5,			0.907,			5260,		"K1V",		1.10,			0.52,	23.7,		0,0,	alfcentbb,	"ALF Cen B",	true,	"Alpha Centauri B");
  star EPSEri(		0.34,			0.82,			5084,		"K2V",		0,			0,	0,		0,0,	eriEpsI,	"EPS Eri",	true,	"Epsilon Eridani");
  star TAUCet(		0.52,			0.783,			5344,		"G8V",		0,			0,	0,		0,0,	taucetb,	"TAU Cet",	true,	"Tau Ceti");
  star Oph70(		0.43,			0.90,			5300,		"K0V",		0.70,			0.499,	23.2,		0,0,	NULL,		"70 Oph",	true,	"70 Ophiuchi A");
  star ETACas(		1.29,			0.972,			6087,		"G0V",		0.57,			0.497,	AVE(69.0,71.0),	0,0,	NULL,		"ETA Cas",	true,	"Eta Cassiopeiae A");
  star SIGDra(		0.428,			0.87,			5299,		"G9V",		0,			0,	0,		0,0,	NULL,		"SIG Dra",	true,	"Sigma Draconis");
  star Oph36(		0.28,			0.85,			4843,		"K2V",		0.85,			0.922,	88.,		0,0,	NULL,		"36 Oph",	true,	"36 Ophiuchi A");
  star Oph36B(		0.27,			0.85,			5100,		"K1V",		0.85,			0.922,	88.,		0,0,	NULL,		"36 Oph B",	false,	"36 Ophiuchi B");
  star HD191408(	0.23,			0.82,			4900,		"K2V",		0.2,			.5,	43.,		0,0,	NULL,		"HD 191408",	true,	"HR 7703 A");
  star DELPav(		1.22,			0.991,			5604,		"G8IV",		0,			0,	0,		0,0,	NULL,		"DEL Pav",	true,	"Delta Pavonis");
  star Eri82(		0.74,			0.70,			5401,		"G8V",		0,			0,	0,		0,0,	NULL,		"82 Eri",	true,	"82 Eridani");
  star BETHyi(		3.494,			1.08,			5872,		"G2IV",		0,			0,	0,		0,0,	NULL,		"BET Hyi",	true,	"Beta Hydri");
  star HD219134(	0,			0.794,			4710,		"K3V",		0,			0,	0,		0,0,	NULL,		"HD 219134",	true,	"HR 8832");
  star HD16160(		0.21,			0.81,			4841,		"K3V",		(0.21 + 0.08),		0,	1200.,		0,0,	NULL,		"HD 16160",	true,	"HR 753 A");
  dole.addStar(sol);
  dole.addStar(ALFCenA);
  dole.addStar(ALFCenB);
  dole.addStar(EPSEri);
  dole.addStar(TAUCet);
  dole.addStar(Oph70);
  dole.addStar(ETACas);
  dole.addStar(SIGDra);
  dole.addStar(Oph36);
  dole.addStar(Oph36B);
  dole.addStar(HD191408);
  dole.addStar(DELPav);
  dole.addStar(Eri82);
  dole.addStar(BETHyi);
  dole.addStar(HD219134);
  dole.addStar(HD16160);
}