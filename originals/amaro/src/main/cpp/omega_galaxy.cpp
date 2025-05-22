#include "omega_galaxy.h"
#include "const.h"
#include "planets.h"
#include "omega_galaxy2.h"

catalog omega_galaxy;

void initOmegaGalaxy()
{
  star sol(		1.0,			1.00,			5780,		"G2V",		0,			0,	0,		0,		0,		mercury,	"Sol",		true,	"The Solar System");
  omega_galaxy.addStar(sol);
  for (int i = 0; i < total_omega_stars; i++)
  {
    star temp(omega_stars[i]);
    omega_galaxy.addStar(temp);
  }
}
