/*----------------------------------------------------------------------*/
/*							 BIBLIOGRAPHY								*/
/*	Dole, Stephen H.  "Formation of Planetary Systems by Aggregation:	*/
/*		a Computer Simulation"	October 1969,  Rand Corporation Paper	*/
/*		P-4226.															*/
/*----------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	"const.h"
#include	"structs.h"
#include 	"accrete.h"
#include 	"stargen.h"
#include 	"utils.h"

#include	"Dumas.h"

/* Now for some variables global to the accretion process:	    */
int 			dust_left;
long double		r_inner;
long double		r_outer;
long double		reduced_mass;
long double		dust_density;
long double		cloud_eccentricity;
dust_pointer	dust_head	= NULL;
planet_pointer	planet_head	= NULL;
gen_pointer		hist_head	= NULL;

void set_initial_conditions(long double inner_limit_of_dust, 
							long double outer_limit_of_dust)
{
    gen_pointer hist;
    hist = (gen_pointer)malloc(sizeof(generation));
    hist->dusts = dust_head;
    hist->planets = planet_head;
    hist->next = hist_head;
    hist_head = hist;
    
	dust_head = (dust *)malloc(sizeof(dust));
	planet_head = NULL;
	dust_head->next_band = NULL;
	dust_head->outer_edge = outer_limit_of_dust;
	dust_head->inner_edge = inner_limit_of_dust;
	dust_head->dust_present = TRUE;
	dust_head->gas_present = TRUE;
	dust_left = TRUE;
	cloud_eccentricity = 0.2;
}

long double stellar_dust_limit(long double stell_mass_ratio)
{
	return(200.0 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

long double nearest_planet(long double stell_mass_ratio)
{
	return(0.3 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

long double farthest_planet(long double stell_mass_ratio)
{
	return(50.0 * pow(stell_mass_ratio,(1.0 / 3.0)));
}

long double inner_effect_limit(long double a, long double e, long double mass)
{
	return (a * (1.0 - e) * (1.0 - mass) / (1.0 + cloud_eccentricity));
}

long double outer_effect_limit(long double a, long double e, long double mass)
{
	return (a * (1.0 + e) * (1.0 + mass) / (1.0 - cloud_eccentricity));
}

int dust_available(long double inside_range, long double outside_range)
{
	dust_pointer current_dust_band;
	int dust_here;
	
	current_dust_band = dust_head;
	while ((current_dust_band != NULL)
		&& (current_dust_band->outer_edge < inside_range))
		current_dust_band = current_dust_band->next_band;
	if (current_dust_band == NULL)
		dust_here = FALSE;
	else dust_here = current_dust_band->dust_present;
	while ((current_dust_band != NULL)
		&& (current_dust_band->inner_edge < outside_range)) {
			dust_here = dust_here || current_dust_band->dust_present;
			current_dust_band = current_dust_band->next_band;
		}
	return(dust_here);
}

void update_dust_lanes(long double min, long double max, long double mass, 
					   long double crit_mass, long double body_inner_bound, 
					   long double body_outer_bound)
{
	int 			gas; 
	dust_pointer	node1;
	dust_pointer	node2;
	dust_pointer	node3;
	
	dust_left = FALSE;
	if ((mass > crit_mass))
		gas = FALSE;
	else 
		gas = TRUE;
	node1 = dust_head;
	while ((node1 != NULL))
	{
		if (((node1->inner_edge < min) && (node1->outer_edge > max)))
		{
			node2 = (dust *)malloc(sizeof(dust));
			node2->inner_edge = min;
			node2->outer_edge = max;
			if ((node1->gas_present == TRUE))
				node2->gas_present = gas;
			else 
				node2->gas_present = FALSE;
			node2->dust_present = FALSE;
			node3 = (dust *)malloc(sizeof(dust));
			node3->inner_edge = max;
			node3->outer_edge = node1->outer_edge;
			node3->gas_present = node1->gas_present;
			node3->dust_present = node1->dust_present;
			node3->next_band = node1->next_band;
			node1->next_band = node2;
			node2->next_band = node3;
			node1->outer_edge = min;
			node1 = node3->next_band;
		}
		else 
			if (((node1->inner_edge < max) && (node1->outer_edge > max)))
			{
				node2 = (dust *)malloc(sizeof(dust));
				node2->next_band = node1->next_band;
				node2->dust_present = node1->dust_present;
				node2->gas_present = node1->gas_present;
				node2->outer_edge = node1->outer_edge;
				node2->inner_edge = max;
				node1->next_band = node2;
				node1->outer_edge = max;
				if ((node1->gas_present == TRUE))
					node1->gas_present = gas;
				else 
					node1->gas_present = FALSE;
				node1->dust_present = FALSE;
				node1 = node2->next_band;
			}
			else 
				if (((node1->inner_edge < min) && (node1->outer_edge > min)))
				{
					node2 = (dust *)malloc(sizeof(dust));
					node2->next_band = node1->next_band;
					node2->dust_present = FALSE;
					if ((node1->gas_present == TRUE))
						node2->gas_present = gas;
					else 
						node2->gas_present = FALSE;
					node2->outer_edge = node1->outer_edge;
					node2->inner_edge = min;
					node1->next_band = node2;
					node1->outer_edge = min;
					node1 = node2->next_band;
				}
				else 
					if (((node1->inner_edge >= min) && (node1->outer_edge <= max)))
					{
						if ((node1->gas_present == TRUE))
							node1->gas_present = gas;
						node1->dust_present = FALSE;
						node1 = node1->next_band;
					}
					else 
						if (((node1->outer_edge < min) || (node1->inner_edge > max)))
							node1 = node1->next_band;
	}
	node1 = dust_head;
	while ((node1 != NULL))
	{
		if (((node1->dust_present)
			&& (((node1->outer_edge >= body_inner_bound)
				&& (node1->inner_edge <= body_outer_bound)))))
			dust_left = TRUE;
		node2 = node1->next_band;
		if ((node2 != NULL))
		{
			if (((node1->dust_present == node2->dust_present)
				&& (node1->gas_present == node2->gas_present)))
			{
				node1->outer_edge = node2->outer_edge;
				node1->next_band = node2->next_band;
				free(node2);
			}
		}
		node1 = node1->next_band;
	}
}

long double collect_dust(long double last_mass, long double *new_dust, 
						 long double *new_gas,
						 long double a, long double e, 
						 long double crit_mass, dust_pointer dust_band)
{
	long double	mass_density;
	long double	temp1;
	long double	temp2;
	long double	temp;
	long double	temp_density;
	long double	bandwidth;
	long double	width;
	long double	volume;
	long double	gas_density = 0.0;
	long double	new_mass;
	long double	next_mass;
	long double	next_dust = 0;
	long double	next_gas = 0;
			
	
	temp = last_mass / (1.0 + last_mass);
	reduced_mass = pow(temp,(1.0 / 4.0));
	r_inner = inner_effect_limit(a, e, reduced_mass);
	r_outer = outer_effect_limit(a, e, reduced_mass);
	
	if ((r_inner < 0.0))
		r_inner = 0.0;
	
	if ((dust_band == NULL))
		return(0.0);
	else 
	{
		if ((dust_band->dust_present == FALSE))
			temp_density = 0.0;
		else 
			temp_density = dust_density;
			
		if (((last_mass < crit_mass) || (dust_band->gas_present == FALSE)))
			mass_density = temp_density;
		else
		{
			mass_density = K * temp_density / (1.0 + sqrt(crit_mass / last_mass)
										* (K - 1.0));
			gas_density = mass_density - temp_density;
		}
		
		if (((dust_band->outer_edge <= r_inner)
		  || (dust_band->inner_edge >= r_outer)))
		{
			return(collect_dust(last_mass, new_dust, new_gas,
								a,e,crit_mass, dust_band->next_band));
		}
		else
		{
			bandwidth = (r_outer - r_inner);
			
			temp1 = r_outer - dust_band->outer_edge;
			if (temp1 < 0.0)
				temp1 = 0.0;
			width = bandwidth - temp1;
			
			temp2 = dust_band->inner_edge - r_inner;
			if (temp2 < 0.0)
				temp2 = 0.0;
			width = width - temp2;
			
			temp = 4.0 * PI * pow(a,2.0) * reduced_mass
				* (1.0 - e * (temp1 - temp2) / bandwidth);
			volume = temp * width;

			new_mass  = volume * mass_density;
			*new_gas  = volume * gas_density;
			*new_dust = new_mass - *new_gas;
			
			next_mass = collect_dust(last_mass, &next_dust, &next_gas,
									 a,e,crit_mass, dust_band->next_band);
			
			*new_gas  = *new_gas + next_gas;
			*new_dust = *new_dust + next_dust;
			
			return(new_mass + next_mass);
		}
	}
}


/*--------------------------------------------------------------------------*/
/*	 Orbital radius is in AU, eccentricity is unitless, and the stellar		*/
/*	luminosity ratio is with respect to the sun.  The value returned is the */
/*	mass at which the planet begins to accrete gas as well as dust, and is	*/
/*	in units of solar masses.												*/
/*--------------------------------------------------------------------------*/

long double critical_limit(long double orb_radius, long double eccentricity, 
						   long double stell_luminosity_ratio)
{
	long double	temp;
	long double	perihelion_dist;
	
	perihelion_dist = (orb_radius - orb_radius * eccentricity);
	temp = perihelion_dist * sqrt(stell_luminosity_ratio);
	return(B * pow(temp,-0.75));
}



void accrete_dust(long double *seed_mass, long double *new_dust, long double *new_gas,
				  long double a, long double e, long double crit_mass,
				  long double body_inner_bound, long double body_outer_bound)
{
	long double	new_mass = (*seed_mass);
	long double	temp_mass;
	
	do
	{
		temp_mass = new_mass;
		new_mass = collect_dust(new_mass, new_dust, new_gas, 
								a,e,crit_mass, dust_head);
	}
	while (!(((new_mass - temp_mass) < (0.0001 * temp_mass))));
	
	(*seed_mass) = (*seed_mass) + new_mass;
	update_dust_lanes(r_inner,r_outer,(*seed_mass),crit_mass,body_inner_bound,body_outer_bound);
}



void coalesce_planetesimals(long double a, long double e, long double mass, long double crit_mass,
							long double dust_mass, long double gas_mass,
							long double stell_luminosity_ratio,
							long double body_inner_bound, long double body_outer_bound,
							int			do_moons)
{
	planet_pointer	the_planet;
	planet_pointer	next_planet;
	planet_pointer	prev_planet;
	int 			finished; 
	long double 	temp;
	long double 	diff;
	long double 	dist1;
	long double 	dist2;
	
	finished = FALSE;
	prev_planet = NULL;

// First we try to find an existing planet with an over-lapping orbit.
	
	for (the_planet = planet_head;
		 the_planet != NULL;
		 the_planet = the_planet->next_planet)
	{
		diff = the_planet->a - a;
		
		if ((diff > 0.0))
		{
			dist1 = (a * (1.0 + e) * (1.0 + reduced_mass)) - a;
			/* x aphelion	 */
			reduced_mass = pow((the_planet->mass / (1.0 + the_planet->mass)),(1.0 / 4.0));
			dist2 = the_planet->a
				- (the_planet->a * (1.0 - the_planet->e) * (1.0 - reduced_mass));
		}
		else 
		{
			dist1 = a - (a * (1.0 - e) * (1.0 - reduced_mass));
			/* x perihelion */
			reduced_mass = pow((the_planet->mass / (1.0 + the_planet->mass)),(1.0 / 4.0));
			dist2 = (the_planet->a * (1.0 + the_planet->e) * (1.0 + reduced_mass))
				- the_planet->a;
		}
		
		if (((fabs(diff) <= fabs(dist1)) || (fabs(diff) <= fabs(dist2))))
		{
			long double new_dust = 0;
			long double	new_gas = 0;
			long double new_a = (the_planet->mass + mass) / 
								((the_planet->mass / the_planet->a) + (mass / a));
			
			temp = the_planet->mass * sqrt(the_planet->a) * sqrt(1.0 - pow(the_planet->e,2.0));
			temp = temp + (mass * sqrt(a) * sqrt(sqrt(1.0 - pow(e,2.0))));
			temp = temp / ((the_planet->mass + mass) * sqrt(new_a));
			temp = 1.0 - pow(temp,2.0);
			if (((temp < 0.0) || (temp >= 1.0)))
				temp = 0.0;
			e = sqrt(temp);
			
			if (do_moons)
			{
				long double existing_mass = 0.0;
				
				if (the_planet->first_moon != NULL)
				{
					planet_pointer	m;
					
					for (m = the_planet->first_moon;
						 m != NULL;
						 m = m->next_planet)
					{
						existing_mass += m->mass;
					}
				}

				if (mass < crit_mass)
				{
					if ((mass * SUN_MASS_IN_EARTH_MASSES) < 2.5
					 && (mass * SUN_MASS_IN_EARTH_MASSES) > .0001
					 && existing_mass < (the_planet->mass * .05)
					   )
					{
						planet_pointer	the_moon = (planets *)malloc(sizeof(planets));
						
						the_moon->type 			= tUnknown;
	/* 					the_moon->a 			= a; */
	/* 					the_moon->e 			= e; */
						the_moon->mass 			= mass;
						the_moon->dust_mass 	= dust_mass;
						the_moon->gas_mass 		= gas_mass;
						the_moon->atmosphere 	= NULL;
						the_moon->next_planet 	= NULL;
						the_moon->first_moon 	= NULL;
						the_moon->gas_giant 	= FALSE;
						the_moon->atmosphere	= NULL;
						the_moon->albedo		= 0;
						the_moon->gases			= 0;
						the_moon->surf_temp		= 0;
						the_moon->high_temp		= 0;
						the_moon->low_temp		= 0;
						the_moon->max_temp		= 0;
						the_moon->min_temp		= 0;
						the_moon->greenhs_rise	= 0;
						the_moon->minor_moons 	= 0;
	
						if ((the_moon->dust_mass + the_moon->gas_mass)
						  > (the_planet->dust_mass + the_planet->gas_mass))
						{
							long double	temp_dust = the_planet->dust_mass;
							long double temp_gas  = the_planet->gas_mass;
							long double temp_mass = the_planet->mass;
							
							the_planet->dust_mass = the_moon->dust_mass;
							the_planet->gas_mass  = the_moon->gas_mass;
							the_planet->mass      = the_moon->mass;
							
							the_moon->dust_mass   = temp_dust;
							the_moon->gas_mass    = temp_gas;
							the_moon->mass        = temp_mass;
						}
	
						if (the_planet->first_moon == NULL)
							the_planet->first_moon = the_moon;
						else
						{
							the_moon->next_planet = the_planet->first_moon;
							the_planet->first_moon = the_moon;
						}
						
						finished = TRUE;
						
						if (flag_verbose & 0x0100)
							fprintf (stderr, "Moon Captured... "
									 "%5.3Lf AU (%.2LfEM) <- %.2LfEM\n",
									the_planet->a, the_planet->mass * SUN_MASS_IN_EARTH_MASSES, 
									mass * SUN_MASS_IN_EARTH_MASSES
									);
					}
					else 
					{
						if (flag_verbose & 0x0100)
							fprintf (stderr, "Moon Escapes... "
									 "%5.3Lf AU (%.2LfEM)%s %.2LfEM%s\n",
									the_planet->a, the_planet->mass * SUN_MASS_IN_EARTH_MASSES, 
									existing_mass < (the_planet->mass * .05) ? "" : " (big moons)",
									mass * SUN_MASS_IN_EARTH_MASSES,
									(mass * SUN_MASS_IN_EARTH_MASSES) >= 2.5 ? ", too big" : 
									  (mass * SUN_MASS_IN_EARTH_MASSES) <= .0001 ? ", too small" : ""
									);
					}
				}
			}

			if (!finished)
			{
				if (flag_verbose & 0x0100)
						fprintf (stderr, "Collision between two planetesimals! "
								"%4.2Lf AU (%.2LfEM) + %4.2Lf AU (%.2LfEM = %.2LfEMd + %.2LfEMg [%.3LfEM])-> %5.3Lf AU (%5.3Lf)\n",
								the_planet->a, the_planet->mass * SUN_MASS_IN_EARTH_MASSES, 
								a, mass * SUN_MASS_IN_EARTH_MASSES, 
								dust_mass * SUN_MASS_IN_EARTH_MASSES, gas_mass * SUN_MASS_IN_EARTH_MASSES, 
								crit_mass * SUN_MASS_IN_EARTH_MASSES,
								new_a, e);
			
				temp = the_planet->mass + mass;
				accrete_dust(&temp, &new_dust, &new_gas,
							 new_a,e,stell_luminosity_ratio,
							 body_inner_bound,body_outer_bound);
	
				the_planet->a = new_a;
				the_planet->e = e;
				the_planet->mass = temp;
				the_planet->dust_mass += dust_mass + new_dust;
				the_planet->gas_mass += gas_mass + new_gas;
				if (temp >= crit_mass)
					the_planet->gas_giant = TRUE;
					
				while (the_planet->next_planet != NULL && the_planet->next_planet->a < new_a)
				{
					next_planet = the_planet->next_planet;
					
					if (the_planet == planet_head)
						planet_head = next_planet;
					else
						prev_planet->next_planet = next_planet;
					
					the_planet->next_planet = next_planet->next_planet;
					next_planet->next_planet = the_planet;
					prev_planet = next_planet;
				}
			}

			finished = TRUE;
			break;
		}
		else 
		{
			prev_planet = the_planet;
		}
	}
	
	if (!(finished))			// Planetesimals didn't collide. Make it a planet.
	{
		the_planet = (planets *)malloc(sizeof(planets));
		
		the_planet->type 			= tUnknown;
		the_planet->a 				= a;
		the_planet->e 				= e;
		the_planet->mass 			= mass;
		the_planet->dust_mass 		= dust_mass;
		the_planet->gas_mass 		= gas_mass;
		the_planet->atmosphere 		= NULL;
		the_planet->first_moon 		= NULL;
		the_planet->atmosphere		= NULL;
		the_planet->albedo			= 0;
		the_planet->gases			= 0;
		the_planet->surf_temp		= 0;
		the_planet->high_temp		= 0;
		the_planet->low_temp		= 0;
		the_planet->max_temp		= 0;
		the_planet->min_temp		= 0;
		the_planet->greenhs_rise	= 0;
		the_planet->minor_moons 	= 0;
		
		if ((mass >= crit_mass))
			the_planet->gas_giant = TRUE;
		else 
			the_planet->gas_giant = FALSE;
		
		if ((planet_head == NULL))
		{
			planet_head = the_planet;
			the_planet->next_planet = NULL;
		}
		else if ((a < planet_head->a))
		{
			the_planet->next_planet = planet_head;
			planet_head = the_planet;
		}
		else if ((planet_head->next_planet == NULL))
		{
			planet_head->next_planet = the_planet;
			the_planet->next_planet = NULL;
		}
		else 
		{
			next_planet = planet_head;
			while (((next_planet != NULL) && (next_planet->a < a)))
			{
				prev_planet = next_planet;
				next_planet = next_planet->next_planet;
			}
			the_planet->next_planet = next_planet;
			prev_planet->next_planet = the_planet;
		}
	}
}


planet_pointer dist_planetary_masses(long double stell_mass_ratio,
									 long double stell_luminosity_ratio, 
									 long double inner_dust, 
									 long double outer_dust,
									 long double outer_planet_limit,
									 long double dust_density_coeff,
									 planet_pointer seed_system,
									 int		 do_moons)
{
	long double 	a; 
	long double 	e; 
	long double 	mass;
	long double		dust_mass;
	long double		gas_mass;
	long double 	crit_mass; 
	long double 	planet_inner_bound; 
	long double 	planet_outer_bound;
	planet_pointer 	seeds = seed_system;
	
	set_initial_conditions(inner_dust,outer_dust);
	planet_inner_bound = nearest_planet(stell_mass_ratio);
	
	if (outer_planet_limit == 0)
		planet_outer_bound = farthest_planet(stell_mass_ratio);
	else
		planet_outer_bound = outer_planet_limit;
		
	while (dust_left)
	{
		if (seeds != NULL)
		{
			a = seeds->a;
			e = seeds->e;
			seeds = seeds->next_planet;
		}
		else
		{
			a = random_number(planet_inner_bound,planet_outer_bound);
			e = random_eccentricity( );
		}
		
		mass      = PROTOPLANET_MASS;
		dust_mass = 0;
		gas_mass  = 0;
		
		if (flag_verbose & 0x0200)
			fprintf (stderr, "Checking %Lg AU.\n",a);
			
		if (dust_available(inner_effect_limit(a, e, mass),
						   outer_effect_limit(a, e, mass))) 
		{
			if (flag_verbose & 0x0100)
				fprintf (stderr, "Injecting protoplanet at %Lg AU.\n", a);
			
			dust_density = dust_density_coeff * sqrt(stell_mass_ratio)
						   * exp(-ALPHA * pow(a,(1.0 / N)));
			crit_mass = critical_limit(a,e,stell_luminosity_ratio);
			accrete_dust(&mass, &dust_mass, &gas_mass,
						 a,e,crit_mass,
						 planet_inner_bound,
						 planet_outer_bound);
			
			dust_mass += PROTOPLANET_MASS;
			
			if (mass > PROTOPLANET_MASS)
				coalesce_planetesimals(a,e,mass,crit_mass,
									   dust_mass, gas_mass,
									   stell_luminosity_ratio,
									   planet_inner_bound,planet_outer_bound,
									   do_moons);
			else if (flag_verbose & 0x0100)
				fprintf (stderr, ".. failed due to large neighbor.\n");
		}
		else if (flag_verbose & 0x0200)
			fprintf (stderr, ".. failed.\n");
	}
	return(planet_head);
}

void free_dust (dust_pointer head)
{
	dust_pointer	node;
	dust_pointer	next;
	
	for(node = head;
		node != NULL;
		node = next)
	{
		next = node->next_band;
		free (node);
	}
	
}

void free_planet (planet_pointer head)
{
	planet_pointer	node;
	planet_pointer	next;
	
	for(node = head;
		node != NULL;
		node = next)
	{
		next = node->next_planet;

		free (node);
	}
}

void free_generations()
{
	gen_pointer	node;
	gen_pointer	next;
	
	for(node = hist_head;
		node != NULL;
		node = next)
	{
		next = node->next;
		
		if (node->dusts)
			free_dust (node->dusts);
			
		if (node->planets)
			free_planet (node->planets);

		free (node);
	}
	
	if (dust_head != NULL)
		free_dust (dust_head);

	if (planet_head != NULL)
		free_planet (planet_head);

	dust_head = NULL;
	planet_head = NULL;
	hist_head = NULL;
}

void free_atmosphere(planet_pointer head)
{
	planet_pointer	node;
	
	for (node = head;
		 node != NULL;
		 node = node->next_planet)
	{
		if (node->atmosphere != NULL)
		{
			free(node->atmosphere);
			
			node->atmosphere = NULL;
		}

		if (node->first_moon != NULL)
		{
			free_atmosphere(node->first_moon);
		}
	}
}

