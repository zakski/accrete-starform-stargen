#include <assert.h>
#include <stdio.h>

#include "system.h"
#include "sysinl.h"


/*--------------------------------------------------------------------------*/
/*   Orbital radius is in AU, eccentricity is unitless, and the stellar     */
/*  luminosity ratio is with respect to the sun.  The value returned is the */
/*  mass at which the planet begins to accrete gas as well as dust, and is  */
/*  in units of solar masses.                                               */
/*--------------------------------------------------------------------------*/
double critical_limit(double orbital_radius, double eccentricity, double stellar_luminosity_ratio)
{
	double
		temp,
		perihelion_dist;

	perihelion_dist = (orbital_radius - orbital_radius * eccentricity);
	temp = perihelion_dist * sqrt(stellar_luminosity_ratio);

	return(B * pow(temp,-0.75));
}

starSystem::starSystem(double stellarMass, double stellarLuminosity)
{
	starMass=stellarMass;
	starLuminosity=stellarLuminosity;

	mainSeqLife = 1.0E10 * (starMass / starLuminosity);

	age= (mainSeqLife >=6.0E9) ? random_number(1.0E9,6.0E9) : random_number(0.7*mainSeqLife,mainSeqLife);

	rEcosphere = sqrt(starLuminosity);
	rGreenhouse = rEcosphere * GREENHOUSE_EFFECT_CONST;
}

void starSystem::make(int diam, int atm, int hyd)
{
	planetList=distributePlanetaryMasses(0.0,stellarMaxDust(starMass));
	planets *planet_head=planetList;
	while (planet_head)
	{
		planet_head->buildPlanet(starMass,starLuminosity,rEcosphere,rGreenhouse,age);
// attempt to build moons!
		planet_head->addMoons(starMass, starLuminosity, rEcosphere, rGreenhouse, age);
//		distributeMoonMasses(*planet_head,planet_head->radius*2.0/1E6,stellarMaxDust(planet_head->mass));

		planet_head = planet_head->nextPlanet;
	}

	if(diam>-1)
	{
		planets* mainworld=new planets;
		mainworld->buildMainworld(diam,atm,hyd,random_eccentricity(),starMass,starLuminosity,rEcosphere,age);
		insertMainworld(mainworld);
	}
}

void starSystem::display(void)
{
	planets *node1 = planetList;
	int counter=1;

	FILE *f = fopen("Newsys.txt", "wt");

	fprintf(f,"                         SYSTEM  CHARACTERISTICS\n");
	fprintf(f,"Mass of central star (Sol = 1.0)              : %5.2lf\n", starMass);
	fprintf(f,"Luminosity of central star (Sol = 1.0)        : %5.2lf\n",starLuminosity);
//	fprintf(f,"Total main sequence lifetime (in million yrs) : %10.3lf\n", (mainSeqLife / 1.0E6));
//	fprintf(f,"Current age of stellar system (in million yrs): %10.3lf\n",(age / 1.0E6));
	fprintf(f,"Radius of habitable ecosphere (AU)            : %6.3lf\n\n",rEcosphere);

	fprintf(f,"Num     Orbit (AU) UWP___      Num Orbit (diam) UWP___\n");
	while(node1!=NULL)
	{
		fprintf(f,"%2d  ",counter++);
		node1->showUPP(f);
		node1=node1->nextPlanet;
	}

	fprintf(f,"\n\n");
	node1=planetList;
	counter=1;
	while (node1 != NULL)
	{
		fprintf(f,"\nPlanet #%d:  ",counter++);

		node1->showStats(f);

		node1 = node1->nextPlanet;
	}

	fclose(f);
}


double starSystem::collectDust(double last_mass, double a, double e, double crit_mass,
	dust_bands* dust_band)
{
	double
		mass_density,
		temp1,
		temp2,
		temp,
		temp_density,
		bandwidth,
		width,
		volume;

	temp = last_mass / (1.0 + last_mass);
	reduced_mass = pow(temp,(1.0 / 4.0));
	r_inner = inner_effect_limit(a, e, reduced_mass);
	r_outer = outer_effect_limit(a, e, reduced_mass);

	if ((r_inner < 0.0)) r_inner = 0.0;

	if ((dust_band == NULL)) return(0.0);
	else
	{
		if ((dust_band->isDustPresent == FALSE))
			temp_density = 0.0;
		else
			temp_density = dustDensity;
		if (((last_mass < crit_mass) || (dust_band->isGasPresent == FALSE)))
			mass_density = temp_density;
		else
			mass_density = K * temp_density / (1.0 + sqrt(crit_mass / last_mass) * (K - 1.0));
		if (((dust_band->outerEdge <= r_inner)
			|| (dust_band->innerEdge >= r_outer)))
			return(collectDust(last_mass,a,e,crit_mass, dust_band->next_band));
		else
		{
			bandwidth = (r_outer - r_inner);
			temp1 = r_outer - dust_band->outerEdge;

			if (temp1 < 0.0) temp1 = 0.0;

			width = bandwidth - temp1;
			temp2 = dust_band->innerEdge - r_inner;
			if (temp2 < 0.0)
				temp2 = 0.0;
			width = width - temp2;
			temp = 4.0 * PI * pow(a,2.0) * reduced_mass * (1.0 - e * (temp1 - temp2) / bandwidth);
			volume = temp * width;
			return(volume * mass_density + collectDust(last_mass,a,e,crit_mass,dust_band->next_band));
		}
	}
}


void starSystem::updateDustLanes(dust_bands *dust_head,double min, double max, double mass, double crit_mass,
				 double body_inner_bound, double body_outer_bound)
{
	int gas;
	dust_bands *node1, *node2, *node3;

	isDustLeft = FALSE;

	gas= (mass > crit_mass) ? FALSE : TRUE;

	node1 = dust_head;

	while ((node1 != NULL))
	{
		if (((node1->innerEdge < min) && (node1->outerEdge > max)))
		{
			node2 = (dust_bands *)malloc(sizeof(dust_bands));
			node2->innerEdge = min;
			node2->outerEdge = max;

			if ((node1->isGasPresent == TRUE))
				node2->isGasPresent = gas;
			else
				node2->isGasPresent = FALSE;
			node2->isDustPresent = FALSE;
			node3 = (dust_bands *)malloc(sizeof(dust_bands));
			node3->innerEdge = max;
			node3->outerEdge = node1->outerEdge;
			node3->isGasPresent = node1->isGasPresent;
			node3->isDustPresent = node1->isDustPresent;
			node3->next_band = node1->next_band;
			node1->next_band = node2;
			node2->next_band = node3;
			node1->outerEdge = min;
			node1 = node3->next_band;
		}
		else
		if (((node1->innerEdge < max) && (node1->outerEdge > max)))
		{
			node2 = (dust_bands *)malloc(sizeof(dust_bands));
			node2->next_band = node1->next_band;
			node2->isDustPresent = node1->isDustPresent;
			node2->isGasPresent = node1->isGasPresent;
			node2->outerEdge = node1->outerEdge;
			node2->innerEdge = max;
			node1->next_band = node2;
			node1->outerEdge = max;
			if ((node1->isGasPresent == TRUE))
				node1->isGasPresent = gas;
			else
				node1->isGasPresent = FALSE;
			node1->isDustPresent = FALSE;
			node1 = node2->next_band;
		}
		else
		if (((node1->innerEdge < min) && (node1->outerEdge > min)))
		{
			node2 = (dust_bands *)malloc(sizeof(dust_bands));
			node2->next_band = node1->next_band;
			node2->isDustPresent = FALSE;

			if ((node1->isGasPresent == TRUE))
				node2->isGasPresent = gas;
			else
				node2->isGasPresent = FALSE;
			node2->outerEdge = node1->outerEdge;
			node2->innerEdge = min;
			node1->next_band = node2;
			node1->outerEdge = min;
			node1 = node2->next_band;
		}
		else
		if (((node1->innerEdge >= min) && (node1->outerEdge <= max)))
		{
			if ((node1->isGasPresent == TRUE))
				node1->isGasPresent = gas;
			node1->isDustPresent = FALSE;
			node1 = node1->next_band;
		}
		else
		if (((node1->outerEdge < min) || (node1->innerEdge > max)))
			node1 = node1->next_band;
	}
	node1 = dust_head;

	while ((node1 != NULL))
	{
		if (((node1->isDustPresent)
			&& (((node1->outerEdge >= body_inner_bound)
			&& (node1->innerEdge <= body_outer_bound)))))
			isDustLeft = TRUE;
		node2 = node1->next_band;
		if ((node2 != NULL))
		{
			if (((node1->isDustPresent == node2->isDustPresent)
				&& (node1->isGasPresent == node2->isGasPresent)))
			{
				node1->outerEdge = node2->outerEdge;
				node1->next_band = node2->next_band;
				free(node2);
			}
		}
		node1 = node1->next_band;
	}
}


void starSystem::accreteDust(dust_bands *dust_head,double &seed_mass, double a, double e, double crit_mass,
		  double body_inner_bound, double body_outer_bound)
{
	double
		new_mass=seed_mass,
		temp_mass;

//	new_mass = seed_mass;
	do
	{
		temp_mass = new_mass;
		new_mass = collectDust(new_mass,a,e,crit_mass,dust_head);
	} while (!((new_mass - temp_mass) < (0.0001 * temp_mass)));

	seed_mass = seed_mass + new_mass;
	updateDustLanes(dust_head,r_inner,r_outer,seed_mass,crit_mass,body_inner_bound,body_outer_bound);
}


void starSystem::coalescePlanetesimals(planets *&planet,dust_bands *dust_head,double a, double e, double mass,
	double crit_mass, double body_inner_bound, double body_outer_bound)
{
	planets *node1, *node2, *node3;
	int coalesced;
	double temp, dist1, dist2, a3;

	coalesced = FALSE;
	node1 = planet;
	while ((node1 != NULL))
	{
		node2 = node1;
		temp = node1->axis - a;
		if ((temp > 0.0))
		{
			dist1 = (a * (1.0 + e) * (1.0 + reduced_mass)) - a;
			// x aphelion
			reduced_mass = pow((node1->mass / (1.0 + node1->mass)),(1.0 / 4.0));
			dist2 = node1->axis - (node1->axis * (1.0 - node1->eccentricity) * (1.0 - reduced_mass));
		}
		else
		{
			dist1 = a - (a * (1.0 - e) * (1.0 - reduced_mass));
			 // x perihelion
			reduced_mass = pow(node1->mass / (1.0 + node1->mass),(1.0 / 4.0));
			dist2 = (node1->axis * (1.0 + node1->eccentricity) * (1.0 + reduced_mass)) - node1->axis;
		}
		if (((fabs(temp) <= fabs(dist1)) || (fabs(temp) <= fabs(dist2))))
		{
#ifdef VERBOSE
			printf("Collision between two planetesimals!\n");
#endif
			a3 = (node1->mass + mass) / ((node1->mass / node1->axis) + (mass / a));
			temp = node1->mass * sqrt(node1->axis) * sqrt(1.0 - pow(node1->eccentricity,2.0));
			temp = temp + (mass * sqrt(a) * sqrt(sqrt(1.0 - pow(e,2.0))));
			temp = temp / ((node1->mass + mass) * sqrt(a3));
			temp = 1.0 - pow(temp,2.0);
			if (((temp < 0.0) || (temp >= 1.0)))
				temp = 0.0;
			e = sqrt(temp);
			temp = node1->mass + mass;
			accreteDust(dust_head,temp,a3,e,starLuminosity,body_inner_bound,body_outer_bound);
			node1->axis = a3;
			node1->eccentricity = e;
			node1->mass = temp;
			node1 = NULL;
			coalesced = TRUE;
		}
		else
			node1 = node1->nextPlanet;
	}
	if (!(coalesced))
	{
		node3 = (planets *)malloc(sizeof(planets));
		node3->axis = a;
		node3->eccentricity = e;

		node3->isGasGiant= (mass>=crit_mass) ? TRUE : FALSE;

		node3->mass = mass;
		if ((planet == NULL))
		{
			planet = node3;
			node3->nextPlanet = NULL;
		}
		else
		{
			node1 = planet;
			if ((a < node1->axis))
			{
				node3->nextPlanet = node1;
				planet = node3;
			}
			else
			if ((planet->nextPlanet == NULL))
			{
				planet->nextPlanet = node3;
				node3->nextPlanet = NULL;
			}
			else
			{
				while (((node1 != NULL) && (node1->axis < a)))
				{
					node2 = node1;
					node1 = node1->nextPlanet;
				}
				node3->nextPlanet = node1;
				node2->nextPlanet = node3;
			}
		}
	}
}


planets * starSystem::distributePlanetaryMasses(double inner_dust, double outer_dust)
{
	double
		a,
		e,
		mass,
		crit_mass,
		planetesimal_inner_bound,
		planetesimal_outer_bound;

	dust_bands* dust_head=new dust_bands(inner_dust,outer_dust);
	planets *planet_head=0;
	planets *&temp=planet_head;
	isDustLeft=TRUE;
	cloudEccentricity=0.2;

	planetesimal_inner_bound = innermost_planet(starMass);
	planetesimal_outer_bound = outermost_planet(starMass);

	while (isDustLeft)
	{
		a = random_number(planetesimal_inner_bound,planetesimal_outer_bound);
		e = random_eccentricity( );
		mass = PROTOPLANET_MASS;
#ifdef VERBOSE
		printf("Checking %10f AU:  ",a);
#endif
		if (dust_head->dustAvailable(inner_effect_limit(a, e, mass),outer_effect_limit(a, e, mass)))
		{
#ifdef VERBOSE
			printf(".. Injecting protoplanet.\n");
#endif
			assert(a>0.0);
			dustDensity = DUST_DENSITY_COEFF * sqrt(starMass) * exp(-ALPHA * pow(a,(1.0 / N)));
			crit_mass = critical_limit(a,e,starLuminosity);
			accreteDust(dust_head,mass,a,e,crit_mass,planetesimal_inner_bound,planetesimal_outer_bound);

			if ((mass != 0.0) && (mass != PROTOPLANET_MASS))
				coalescePlanetesimals(planet_head,dust_head,a,e,mass,crit_mass,
						planetesimal_inner_bound,planetesimal_outer_bound);
#ifdef VERBOSE
			else printf(".. failed due to large neighbor.\n");
#endif
		}
#ifdef VERBOSE
		else printf(".. failed.\n");
#endif
	}
	return temp;
}

void starSystem::insertMainworld(planets *mw)
{
	planets* head=planetList;

	while(head->nextPlanet && head->nextPlanet->axis < mw->axis)
		head=head->nextPlanet;

	if(!head->nextPlanet) // no worlds in or outside of habitable zone!
	{
		head->nextPlanet=mw;
		mw->addMoons(starMass, starLuminosity, rEcosphere, rGreenhouse, age);
	}
	else
	{
		if(fabs(head->axis-mw->axis)>fabs(head->nextPlanet->axis-mw->axis))
		{
		}
		else
		{
			head=head->nextPlanet;
		}

		if(head->isGasGiant)
		{
      	head->insertMainWorld(mw,rEcosphere);
		}
		else
		{
			planets* temp=head->nextPlanet;
			*head=*mw;
         head->nextPlanet=temp;
			head->addMoons(starMass, starLuminosity, rEcosphere, rGreenhouse, age);
		}
	}
}

