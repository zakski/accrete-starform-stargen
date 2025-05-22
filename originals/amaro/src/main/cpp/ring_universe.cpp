#include "ring_universe.h"
#include "const.h"
#include "planets.h"
#include "ring_universe2.h"

catalog ring_universe;

void initRingUniverse()
{
  ring_universe.setArg("R");
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,		0,		mercury,	"Sol",		true,	"The Solar System");
  ring_universe.addStar(sol);
  for (int i = 0; i < total_ring_universe_stars; i++)
  {
    star temp(ring_universe_stars[i]);
    ring_universe.addStar(temp);
  }
}
