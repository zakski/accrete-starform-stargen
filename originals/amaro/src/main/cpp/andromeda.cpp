#include "andromeda.h"
#include "const.h"
#include "planets.h"
#include "andromeda2.h"

catalog andromeda;

void initAndromeda()
{
  andromeda.setArg("U");
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,		0,		mercury,	"Sol",		true,	"The Solar System");
  andromeda.addStar(sol);
  for (int i = 0; i < total_andromeda_stars; i++)
  {
    star temp(andromeda_stars[i]);
    andromeda.addStar(temp);
  }
}
