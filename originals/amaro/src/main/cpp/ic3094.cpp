#include "ic3094.h"
#include "const.h"
#include "planets.h"
#include "ic3094_2.h"

catalog ic3094;

void initIC3094()
{
  ic3094.setArg("R");
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,		0,		mercury,	"Sol",		true,	"The Solar System");
  ic3094.addStar(sol);
  for (int i = 0; i < total_ic3094_stars; i++)
  {
    star temp(ic3094_stars[i]);
    ic3094.addStar(temp);
  }
}
