/*----------------------------------------------------------------------*/
/*                           BIBLIOGRAPHY                               */
/*  Dole, Stephen H.  "Formation of Planetary Systems by Aggregation:   */
/*      a Computer Simulation"  October 1969,  Rand Corporation Paper   */
/*      P-4226.                                                         */
/*----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "display.h"
#include "accrete.h"
#include "const.h"

dust* make_dust(double inner_edge, double outer_edge);

/**
 * Constructor for the accretion struct type. Caller is responsible for calling
 * free_accretion() when done.
 * 
 * @param inner_limit_of_dust  the inner range for dust
 * @param outer_limit_of_dust  the outer range for dust
 */
accretion* make_accretion(double inner_limit_of_dust, double outer_limit_of_dust)
{
  accretion* result = malloc(sizeof(accretion));

  result->planet_head = NULL;

  result->dust_head = make_dust(inner_limit_of_dust, outer_limit_of_dust);
  result->dust_head->has_dust = true;
  result->dust_head->has_gas = true;
  
  result->dust_left = true;
  result->cloud_eccen = 0.2;
  
  return result;
}

/**
 * Frees the accretion process.
 */
void free_accretion(accretion* accreting)
{
  // should probably free the dust lanes etc. here as well.
  free(accreting);
}

/**
 * Constructs a new dust lane with the given range.
 */
dust* make_dust(double inner_edge, double outer_edge)
{
  dust* lane = malloc(sizeof(dust));
  
  lane->inner_edge   = inner_edge;
  lane->outer_edge   = outer_edge;
  
  // defaults 
  lane->has_dust     = false;
  lane->has_gas      = false;
  lane->next_band    = NULL;
  
  return lane;
}

/**
 * Frees a dust lane.
 */
void free_dust(dust* dust_lane)
{
  free(dust_lane);
}

/**
 * Returns the stellar dust limit for this star's mass ratio.
 */
double stellar_dust_limit(double star_mass_r)
{
  return 200.0 * pow(star_mass_r, (1.0 / 3.0));
}

/**
 * Returns the nearest a planet can be to this star, based on the mass ratio.
 */
double nearest_planet(double star_mass_r)
{
  return 0.3 * pow(star_mass_r, (1.0 / 3.0));
}

/**
 * Returns the farthest a planet can be from this star, based on the mass ratio.
 */
double farthest_planet(double star_mass_r)
{
  return 50.0 * pow(star_mass_r, (1.0 / 3.0));
}

double inner_effect_limit(accretion* accreting, double a, double e, double mass)
{
  return a * (1.0 - e) * (1.0 - mass) / (1.0 + accreting->cloud_eccen);
}

double outer_effect_limit(accretion* accreting, double a, double e, double mass)
{
  return a * (1.0 + e) * (1.0 + mass) / (1.0 - accreting->cloud_eccen);
}

/**
 * Returns whether or not there is still dust between inside_range and 
 * outside_range in this current accretion process.
 */
bool dust_available(accretion* accreting, double inside_range, double outside_range)
{
  dust* current;
  bool         dust_here;

  // this loop finds the dust band whose outer edge is within our inside range.
  for (current = accreting->dust_head;
       current != NULL && current->outer_edge < inside_range;
       current = current->next_band);

  // if we have no dust band, there's no dust here; otherwise, it depends on the
  // dust record
  dust_here = current == NULL ? false : current->has_dust;

  // this loop ORs together all of the dust bands between the first one we found
  // and the dust band whose inner edge is outside our outside range.
  while (current != NULL && current->inner_edge < outside_range)
  {
    dust_here = dust_here || current->has_dust;
    current = current->next_band;
  }

  // return whether or not we found a dust band in our range that still had dust
  return dust_here;
}

// Case 1: this node subsumes min and max
//
//  node1:     [       ]
//  min/max:     [   ]
//
// We must split this node up into two nodes like so:
//
// *node1:     [       ]
// *min/max:     [   ]
// 
//  node1:     [ ]
//  node2:       [   ]
//  node3:           [ ]
dust* split_subsumed_node(dust* node1, double min, double max, bool gas)
{
  dust *node2, *node3;
  
  // make a new dust lane with min and max for the middle chunk
  node2 = make_dust(min, max);

  // handle gas possibility
  node2->has_gas = node1->has_gas ? gas : false;

  // make another new dust lane that proceeds from max to the outer edge of
  // node 1, the right edge
  node3 = make_dust(max, node1->outer_edge);
  node3->has_gas = node1->has_gas;
  node3->has_dust = node1->has_dust;
  node3->next_band = node1->next_band;

  // condense node1's outer edge to the minimum and hook up these nodes in
  // the order
  node1->next_band = node2;
  node2->next_band = node3;
  node1->outer_edge = min;

  // for the next iteration, begin considering the third node from max to 
  // the outer edge, node3
  return node3->next_band;
}

// Case 2: the node spans across the maximum
//
//  node1:       [     ]
//  min/max:   [    ]
//
// This must be split up into two nodes as follows:
//
// *node1:       [     ]
// *min/max:   [    ]
//  node1:       [  ]
//  node2:          [  ]
dust* split_spanning_maximum_node(dust* node1, double max, bool gas)
{
  dust* node2;
  
  // make a new node for the second half from max to outer_edge
  node2 = make_dust(max, node1->outer_edge);
  node2->next_band = node1->next_band;
  node2->has_dust = node1->has_dust;
  node2->has_gas = node1->has_gas;

  // arrange for the old node to go from the inner edge to max
  node1->next_band = node2;
  node1->outer_edge = max;
  node1->has_gas = node1->has_gas ? gas : false;
  node1->has_dust = false;

  // the new right dust band is where we resume
  return node2->next_band;
}

// Case 3: the node spans across the minimum
//
//  node1:     [      ]
//  min/max:      [       ]
//
// This must be split up into two nodes as follows:
//  
// *node1:     [      ]
// *min/max:      [       ]
//  node1:     [  ]
//  node2:        [   ]
dust* split_spanning_minimum_node(dust* node1, double min, bool gas)
{
  dust* node2;
  
  // make the second node
  node2 = make_dust(min, node1->outer_edge);
  node2->next_band = node1->next_band;
  node2->has_gas = node1->has_gas ? gas : false;

  // rearrange first node and prepare to resume with the new right dust band
  node1->next_band = node2;
  node1->outer_edge = min;
  return node2->next_band;
}

/**
 * Split a dust lane into several dust lanes, and mark the dust as used. Returns
 * the next dust lane in the list.
 * 
 * @param lane     the dust lane to be split, possibly
 * @param min      the minimum range
 * @param max      the maximum range
 * @param has_gas  whether or not there is gas present
 * @return         the next dust lane, for iteration
 */
dust* split_node(dust* lane, double min, double max, bool has_gas)
{
  // Case 1: this node subsumes min and max
  if (lane->inner_edge < min && lane->outer_edge > max)
    return split_subsumed_node(lane, min, max, has_gas);

  // Case 2: the node spans across the maximum
  else if (lane->inner_edge < max && lane->outer_edge > max)
    return split_spanning_maximum_node(lane, max, has_gas);

  // Case 3: the node spans across the minimum
  else if (lane->inner_edge < min && lane->outer_edge > min)
    return split_spanning_minimum_node(lane, min, has_gas);

  // Case 4: the node is within or equal to the range
  //
  //  node1:      [  ]
  //  min/max:  [      ]
  else if (lane->inner_edge >= min && lane->outer_edge <= max)
  {
    // Use up the dust
    lane->has_dust = false;

    // if gas was present, it may not be now.
    if (lane->has_gas == true)
      lane->has_gas = has_gas;
    
    // proceed
    return lane->next_band;
  }

  // Case 5: No overlap whatsoever
  // Two possibilities:
  //
  //  node1:    [     ]
  //  min/max:          [    ]
  //
  // or:
  //
  //  node1:             [  ]
  //  min/max:   [    ]
  //
  // in this case, just move on to the next dust band
  else if (lane->outer_edge < min || lane->inner_edge > max)
    return lane->next_band;
  
  // if we make it here, perhaps we have modified this lane sufficiently to
  // the liking of the controlling loop
  return lane;
}

// this function coalesces neighbor dust lanes that have or do not have dust
// and/or gas
void coalesce_dust_lanes(accretion* accreting, double body_inner_bound, double body_outer_bound)
{
  dust* next_lane;
  
  for (dust* lane = accreting->dust_head; lane != NULL; lane = lane->next_band)
  {
    // if this node has dust and the node is within the body's inner and outer 
    // boundaries, then there is dust left in this simulation.
    if (lane->has_dust && 
        lane->outer_edge >= body_inner_bound && 
        lane->inner_edge <= body_outer_bound)
      accreting->dust_left = true;
    
    // get the next lane if possible
    next_lane = lane->next_band;
    if (next_lane != NULL)
    {
      // coalesce these two adjacent dust lanes if they have the same 
      // combination of having or lacking dust and gas
      if (lane->has_dust == next_lane->has_dust && 
          lane->has_gas  == next_lane->has_gas)
      {
        lane->outer_edge = next_lane->outer_edge;
        lane->next_band = next_lane->next_band;
        free(next_lane);
      }
    }
  }
}

void update_dust_lanes(accretion *accreting, 
        double min, double max, 
        double mass, double crit_mass, 
        double body_inner_bound, double body_outer_bound)
{
  // begin asserting that there's no dust left. coalesce_dust_lanes will set
  // this value to true if it finds any dust during its coalescing maneuver
  accreting->dust_left = false;
  
  // this tracks whether or not this planetoid is growing up to be a gas giant
  // or if it is sufficiently massive that it's going to be a planetoid
  bool gas = (mass <= crit_mass);
  
  // this loop examines ever dust lane. it splits dust lanes such that our min
  // and max values lie at the boundaries of the lane. it also consumes the dust
  // and gas in each lane within the limits as it goes.
  for (dust* lane = accreting->dust_head; 
       lane != NULL; 
       lane = split_node(lane, min, max, gas));
  
  // this loop detects whether or not there is still dust present in the 
  // simulation within the overall bounds and simultaneously coalesces neighbor
  // dust lanes that have or do not have dust and/or gas
  coalesce_dust_lanes(accreting, body_inner_bound, body_outer_bound);
}

// based on the last mass and the a and e of the new mass, fix the reduced mass 
// and inner/outer effect limits of the accretion process.
void fixup_accretion_parameters(accretion *acc, 
        double last_mass, double a, double e)
{
  double temperature;

  temperature = last_mass / (1.0 + last_mass);
  
  // 4th root of the last mass / 1 + last mass: reduced mass
  acc->reduced_mass = pow(temperature, (1.0 / 4.0));
  
  // recalculate the inner and outer radii based on the reduced mass
  acc->r_inner = inner_effect_limit(acc, a, e, acc->reduced_mass);
  acc->r_outer = outer_effect_limit(acc, a, e, acc->reduced_mass);
  
  // fix up the inner radius to be no less than zero
  if (acc->r_inner < 0.0)
    acc->r_inner = 0.0;
}
  
double collect_dust(accretion *accreting, 
        double last_mass, 
        double a, double e, 
        double crit_mass, 
        dust* dust_band)
{
  fixup_accretion_parameters(accreting, last_mass, a, e);

  // base case: if this is the last dust band, return 0
  if (dust_band == NULL) return 0.0;
  
    // if we have dust, use the dust density, otherwise zero
  double dust_density = dust_band->has_dust ? accreting->dust_density : 0.0;
    
    // if the last mass is below the critical mass, or there's no dust in this 
    // dust band, the density is the overall accretion density;
    // otherwise, the mass density is this horrifying formula
    double mass_density = dust_density;
    if (last_mass >= crit_mass && dust_band->has_gas)
      mass_density = K * dust_density / (1.0 + sqrt(crit_mass / last_mass)
                                         * (K - 1.0));
    
  // if the outer edge exceeds the accretion inner limit or the inner edge is 
  // outside the outer limit, just collect the dust from the next band
    if (dust_band->outer_edge <= accreting->r_inner || 
        dust_band->inner_edge >= accreting->r_outer)
      return collect_dust(accreting, last_mass, a, e, crit_mass, dust_band->next_band);
    else
    {
      double bandwidth = (accreting->r_outer - accreting->r_inner);
      double outer_gap = accreting->r_outer - dust_band->outer_edge;
      
      double width = bandwidth - (outer_gap < 0.0 ? 0.0 : outer_gap);

      // account for the gap between the inner edge and the start of 
      // the accretion radius
      double gap = dust_band->inner_edge - accreting->r_inner;
      width = width - (gap < 0.0 ? 0.0 : gap);

      // calculate the area of a cross-section, and the volume
      double area = 4.0 * PI * pow(a, 2.0) * accreting->reduced_mass
          * (1.0 - e * ((outer_gap < 0.0 ? 0.0 : outer_gap) - (gap < 0.0 ? 0.0 : gap)) / bandwidth);
      double volume = area * width;

      // calculate the total mass of this lane plus the mass of the next lane
      return volume * mass_density
             + collect_dust(accreting, last_mass, a, e, crit_mass,
                             dust_band->next_band);
    }
  }

/*--------------------------------------------------------------------------*/
/*   Orbital radius is in AU, eccentricity is unitless, and the stellar     */
/*  luminosity ratio is with respect to the sun.  The value returned is the */
/*  mass at which the planet begins to accrete gas as well as dust, and is  */
/*  in units of solar masses.                                               */
/*--------------------------------------------------------------------------*/
double critical_limit(double orb_radius, double eccentricity, double star_lum_r)
{
  double      temperature,
              perihelion_dist;

  perihelion_dist = (orb_radius - orb_radius * eccentricity);
  temperature = perihelion_dist * sqrt(star_lum_r);
  return B * pow(temperature, -0.75);
}

/**
 * ACCRETE, the algorithm. Accrete some dust for the current process, using the 
 * supplied mass, the planetoid properties given, and the inner and outer bounds
 * of the new body.
 */
void accrete_dust(accretion *accreting, 
        double *seed_mass, 
        double a, double e, double crit_mass, 
        double body_inner_bound, double body_outer_bound)
{
  double temp_mass;

  // fixed point algorithm: accumulate more mass until the difference is less 
  // than .01% of the old mass
  double new_mass = (*seed_mass);
  do
  {
    temp_mass = new_mass;
    new_mass = collect_dust(accreting, new_mass, a, e, crit_mass,
                            accreting->dust_head);
  }
  while (!(new_mass - temp_mass < 0.0001 * temp_mass));
  
  // add the new mass to the seed mass
  *seed_mass = *seed_mass + new_mass;
  
  // update the dust lanes with the new seed mass
  update_dust_lanes(accreting, accreting->r_inner, accreting->r_outer, 
                    *seed_mass, crit_mass, body_inner_bound, body_outer_bound);
}

void coalesce_planetesimals(accretion *accreting, 
        double a, double e, double mass, 
        double crit_mass, double star_lum_r, 
        double body_inner_bound, double body_outer_bound)
{
  planet* node1 = NULL;
  planet* node2 = NULL;
  bool         finished = false;
  double      dist1;
  double      dist2;
  double      a3;

  node1 = accreting->planet_head;
  while (node1 != NULL)
  {
    node2 = node1;
    double delta_a = node1->a - a;
    
    if (delta_a > 0.0)
    {
      dist1 = (a * (1.0 + e) * (1.0 + accreting->reduced_mass)) - a;
      /* x aphelion   */
      accreting->reduced_mass = pow((node1->mass / (1.0 + node1->mass)), (1.0 / 4.0));
      dist2 = node1->a
          - (node1->a * (1.0 - node1->e) * (1.0 - accreting->reduced_mass));
    }
    else
    {
      dist1 = a - (a * (1.0 - e) * (1.0 - accreting->reduced_mass));
      /* x perihelion */
      accreting->reduced_mass = pow(node1->mass / (1.0 + node1->mass), (1.0 / 4.0));
      dist2 = (node1->a * (1.0 + node1->e) * (1.0 + accreting->reduced_mass))
          - node1->a;
    }
    
    if (fabs(delta_a) <= fabs(dist1) || fabs(delta_a) <= fabs(dist2))
    {
      verbose_print("Collision between two planetesimals!\n");

      a3 = (node1->mass + mass) / ((node1->mass / node1->a) + (mass / a));
      double temperature = node1->mass * sqrt(node1->a) * sqrt(1.0 - pow(node1->e, 2.0));
      temperature = temperature + (mass * sqrt(a) * sqrt(sqrt(1.0 - pow(e, 2.0))));
      temperature = temperature / ((node1->mass + mass) * sqrt(a3));
      temperature = 1.0 - pow(temperature, 2.0);
      if (temperature < 0.0 || temperature >= 1.0)
        temperature = 0.0;
      e = sqrt(temperature);
      
      double seed_mass = node1->mass + mass;
      accrete_dust(accreting, &seed_mass, a3, e, star_lum_r,
                   body_inner_bound, body_outer_bound);
      
      node1->a = a3;
      node1->e = e;
      node1->mass = seed_mass;
      node1 = NULL;
      finished = true;
    }
    else
      node1 = node1->next_planet;
  }
  
  if (!finished)
  {
    planet* node3 = malloc(sizeof(planet));
    node3->a = a;
    node3->e = e;
    if (mass >= crit_mass)
      node3->gas_giant = true;
    else
      node3->gas_giant = false;
    node3->mass = mass;
    if (accreting->planet_head == NULL)
    {
      accreting->planet_head = node3;
      node3->next_planet = NULL;
    }
    else
    {
      node1 = accreting->planet_head;
      if (a < node1->a)
      {
        node3->next_planet = node1;
        accreting->planet_head = node3;
      }
      else if (accreting->planet_head->next_planet == NULL)
      {
        accreting->planet_head->next_planet = node3;
        node3->next_planet = NULL;
      }
      else
      {
        planet* previous = NULL;
        while (node1 != NULL && node1->a < a)
        {
          previous = node1;
          node1 = node1->next_planet;
        }
        node3->next_planet = node1;
        previous->next_planet = node3;
      }
    }
  }
}

// this appears to be the entry point into the entire module - DKL
planet* distribute_planetary_masses(
        stellar_system *system, 
        double inner_dust, double outer_dust)
{
  accretion* accreting = make_accretion(inner_dust, outer_dust);

  double star_mass_r = system->star_mass_r;
  double star_lum_r = system->star_lum_r; 

  double planet_inner_bound = nearest_planet(star_mass_r);
  double planet_outer_bound = farthest_planet(star_mass_r);
  
  // while there's still dust left...
  while (accreting->dust_left)
  {
    // give us a random proto planet within the inner and outer bounds
    double a = random_number(planet_inner_bound, planet_outer_bound);
    double e = random_eccentricity();
    double mass = PROTOPLANET_MASS;
    
    // output verbose message
    char message[23];
    snprintf(message, 22, "Checking %g AU.\n", a);
    verbose_print(message);
    
    // if we have dust inside the limits...
    if (dust_available(accreting,
                       inner_effect_limit(accreting, a, e, mass),
                       outer_effect_limit(accreting, a, e, mass)))
    {
      verbose_print(".. Injecting protoplanet.\n");
      accreting->dust_density = DUST_DENSITY_COEFF * sqrt(star_mass_r)
          * exp(-ALPHA * pow(a, (1.0 / N)));

      double crit_mass = critical_limit(a, e, star_lum_r);
      accrete_dust(accreting, &(mass), a, e, crit_mass,
                   planet_inner_bound,
                   planet_outer_bound);
      if (mass != 0.0 && mass != PROTOPLANET_MASS)
        coalesce_planetesimals(accreting, a, e, mass, crit_mass,
                               star_lum_r,
                               planet_inner_bound, planet_outer_bound);
      else
        verbose_print(".. failed due to large neighbor.\n");
    }
    verbose_print(".. failed.\n");
  }
  
  planet* result = accreting->planet_head;
  free_accretion(accreting);
  
  return result;
}

planet* do_dist_moon_masses(double planetary_mass, double plan_radius)
{
  planet* head;
  planet* moon;
  planet* last;
  double pmass = planetary_mass * SUN_MASS_IN_EARTH_MASSES;
  double prad = plan_radius / KM_PER_AU;
  double maxdist = sqrt(pmass) / 200;  /* max. moon distance in AU */
  double mindist = prad * random_number(2.5, 10);
  double lastrad = mindist;
  int         maxcount = (int)sqrt(pmass * 10 + 5) + 1;
  int         count = 0;

  head = last = NULL;

  pmass *= random_number(0.01, 0.2);

  maxcount = (int)random_number(maxcount / 10, maxcount);
  maxdist *= random_number(0.5, 1.5);

  if (args.verbose)
  {
    printf("\npmass = %g Me, prad = %g AU\n", pmass, prad);
    printf("mindist = %g AU, maxdist = %g AU\n", mindist, maxdist);
    printf("maxcount = %d\n", maxcount);
  }

  while (pmass > 0.001 && count < maxcount && lastrad < maxdist)
  {
    double maxfac = sqrt((lastrad - prad) / maxdist) / 8;
    double massmin = 1e17 / EARTH_MASS_IN_GRAMS;
    double massmax = random_number(pmass / 1e6,
                                            pmass * maxfac);
    double mmin = pow(massmin, 1.0 / 4);
    double mmax = pow(massmax, 1.0 / 4);
    double mass = pow(random_number(mmin, mmax), 4);

    double dist = sqrt(mass) * 50000 / KM_PER_AU;

    if (args.verbose)
    {
      printf("mmin = %g Me, mmax = %g Me, mass = %g Me\n",
             massmin, massmax, mass);
    }

    if (mass > massmin)
    {
      count++;
      moon = (planet *) calloc(1, sizeof(planet));
      moon->mass = mass / SUN_MASS_IN_EARTH_MASSES;
      moon->a = random_number(lastrad, lastrad * 1.3);
      lastrad = moon->a + dist;
      moon->e = random_eccentricity();
      moon->first_moon = NULL;
      pmass -= mass * 2;
      if (last)
        last->next_planet = moon;
      else
        head = moon;
      last = moon;
    }
  }
  return head;
}
