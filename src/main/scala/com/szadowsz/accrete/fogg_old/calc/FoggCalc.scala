//  //  /*--------------------------------------------------------------------------*/
//  //  /*   This function returns the smallest molecular weight retained by the    */
//  //  /*  body, which is useful for determining the atmosphere composition.       */
//  //  /*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  */
//  //  /*  mass is in units of solar masses, and equatorial radius is in units of  */
//  //  /*  kilometers.                                                             */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double molecule_limit(mass, equatorial_radius)
//  //  double mass, equatorial_radius;
//  //  {
//  //    double escape_velocity;
//  //
//  //    escape_velocity = escape_vel(mass,equatorial_radius);
//  //    return((3.0 * pow2(GAS_RETENTION_THRESHOLD * CM_PER_METER) * MOLAR_GAS_CONST * EARTH_EXOSPHERE_TEMP) / pow2(escape_velocity));
//  //  }

//  //  /*--------------------------------------------------------------------------*/
//  //  /*  Note that if the orbital radius of the planet is greater than or equal  */
//  //  /*  to R_inner, 99% of it's volatiles are assumed to have been deposited in */
//  //  /*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  int greenhouse(zone, orbital_radius, greenhouse_radius)
//  //  int zone;
//  //  double orbital_radius, greenhouse_radius;
//  //  {
//  //    if ((orbital_radius < greenhouse_radius) && (zone == 1))
//  //      return(TRUE);
//  //    else
//  //      return(FALSE);
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   This function returns the boiling point of water in an atmosphere of   */
//  //  /*   pressure 'surface_pressure', given in millibars.  The boiling point is    */
//  //  /*   returned in units of Kelvin.  This is Fogg's eq.21.                    */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double boiling_point(surface_pressure)
//  //  double surface_pressure;
//  //  {
//  //    double surface_pressure_in_bars;
//  //
//  //    surface_pressure_in_bars = surface_pressure / MILLIBARS_PER_BAR;
//  //    return(1.0 / (log(surface_pressure_in_bars) / -5050.5 + 1.0 / 373.0));
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   This function is Fogg's eq.22.  Given the volatile gas inventory and   */
//  //  /*   planetary radius of a planet (in Km), this function returns the        */
//  //  /*   fraction of the planet covered with water.                             */
//  //  /*   I have changed the function very slightly:  the fraction of Earth's    */
//  //  /*   surface covered by water is 71%, not 75% as Fogg used.                 */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double hydrosphere_fraction(volatile_gas_inventory, planet_radius)
//  //  double volatile_gas_inventory, planet_radius;
//  //  {
//  //    double temp;
//  //
//  //    temp = (0.71 * volatile_gas_inventory / 1000.0) * pow2(EARTH_RADIUS_IN_KM / planet_radius);
//  //    if (temp >= 1.0)
//  //      return(1.0);
//  //    else
//  //      return(temp);
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   Given the surface temperature of a planet (in Kelvin), this function   */
//  //  /*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  */
//  //  /*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     */
//  //  /*   This equation is Hart's eq.3.                                          */
//  //  /*   I have modified it slightly using constants and relationships from     */
//  //  /*   Glass's book "Introduction to Planetary Geology", p.46.                */
//  //  /*   The 'CLOUD_COVERAGE_FACTOR' is the amount of surface area on Earth     */
//  //  /*   covered by one Kg. of cloud.					    */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double cloud_fraction(surf_temp, smallest_MW_retained, equatorial_radius, hydrosphere_fraction)
//  //  double surf_temp, smallest_MW_retained, equatorial_radius,
//  //  hydrosphere_fraction;
//  //  {
//  //    double water_vapor_in_kg, fraction, surface_area, hydrosphere_mass;
//  //
//  //    if (smallest_MW_retained > WATER_VAPOR)
//  //      return(0.0);
//  //    else
//  //    {
//  //      surface_area = 4.0 * PI * pow2(equatorial_radius);
//  //      hydrosphere_mass = hydrosphere_fraction * surface_area * EARTH_WATER_MASS_PER_AREA;
//  //      water_vapor_in_kg = (0.00000001 * hydrosphere_mass) * exp(Q2_36 * (surf_temp - 288.0));
//  //      fraction = CLOUD_COVERAGE_FACTOR * water_vapor_in_kg / surface_area;
//  //      if (fraction >= 1.0)
//  //        return(1.0);
//  //      else
//  //        return(fraction);
//  //    }
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   Given the surface temperature of a planet (in Kelvin), this function   */
//  //  /*   returns the fraction of the planet's surface covered by ice.  This is  */
//  //  /*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. */
//  //  /*   I have changed a constant from 70 to 90 in order to bring it more in   */
//  //  /*   line with the fraction of the Earth's surface covered with ice, which  */
//  //  /*   is approximatly .016 (=1.6%).                                          */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double ice_fraction(hydrosphere_fraction, surf_temp)
//  //  double hydrosphere_fraction, surf_temp;
//  //  {
//  //    double temp;
//  //
//  //    if (surf_temp > 328.0)
//  //      surf_temp = 328.0;
//  //    temp = pow(((328.0 - surf_temp) / 90.0),5.0);
//  //    if (temp > (1.5 * hydrosphere_fraction))
//  //      temp = (1.5 * hydrosphere_fraction);
//  //    if (temp >= 1.0)
//  //      return(1.0);
//  //    else
//  //      return(temp);
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     */
//  //  /*  Earth's Atmosphere" article.  The effective temperature given is in     */
//  //  /*  units of Kelvin, as is the rise in temperature produced by the          */
//  //  /*  greenhouse effect, which is returned.                                   */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double green_rise(optical_depth, effective_temp, surface_pressure)
//  //  double optical_depth, effective_temp, surface_pressure;
//  //  {
//  //    double convection_factor;
//  //
//  //    convection_factor = EARTH_CONVECTION_FACTOR * pow1_4(surface_pressure / EARTH_SURF_PRES_IN_MILLIBARS);
//  //    return(pow1_4(1.0 + 0.75 * optical_depth) - 1.0) * effective_temp * convection_factor;
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   The surface temperature passed in is in units of Kelvin.               */
//  //  /*   The cloud adjustment is the fraction of cloud cover obscuring each     */
//  //  /*   of the three major components of albedo that lie below the clouds.     */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double planet_albedo(water_fraction, cloud_fraction, ice_fraction, surface_pressure)
//  //  double water_fraction, cloud_fraction, ice_fraction, surface_pressure;
//  //  {
//  //    double rock_fraction, cloud_adjustment, components, cloud_contribution,
//  //    rock_contribution, water_contribution, ice_contribution;
//  //
//  //    rock_fraction = 1.0 - water_fraction - ice_fraction;
//  //    components = 0.0;
//  //    if (water_fraction > 0.0)
//  //      components = components + 1.0;
//  //    if (ice_fraction > 0.0)
//  //      components = components + 1.0;
//  //    if (rock_fraction > 0.0)
//  //      components = components + 1.0;
//  //    cloud_adjustment = cloud_fraction / components;
//  //    if (rock_fraction >= cloud_adjustment)
//  //      rock_fraction = rock_fraction - cloud_adjustment;
//  //    else
//  //      rock_fraction = 0.0;
//  //    if (water_fraction > cloud_adjustment)
//  //      water_fraction = water_fraction - cloud_adjustment;
//  //    else
//  //      water_fraction = 0.0;
//  //    if (ice_fraction > cloud_adjustment)
//  //      ice_fraction = ice_fraction - cloud_adjustment;
//  //    else
//  //      ice_fraction = 0.0;
//  //    cloud_contribution = cloud_fraction * about(CLOUD_ALBEDO,0.2);
//  //    if (surface_pressure == 0.0)
//  //      rock_contribution = rock_fraction * about(AIRLESS_ROCKY_ALBEDO,0.3);
//  //    else
//  //      rock_contribution = rock_fraction * about(ROCKY_ALBEDO,0.1);
//  //    water_contribution = water_fraction * about(WATER_ALBEDO,0.2);
//  //    if (surface_pressure == 0.0)
//  //      ice_contribution = ice_fraction * about(AIRLESS_ICE_ALBEDO,0.4);
//  //    else
//  //      ice_contribution = ice_fraction * about(ICE_ALBEDO,0.1);
//  //    return(cloud_contribution + rock_contribution + water_contribution + ice_contribution);
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   This function returns the dimensionless quantity of optical depth,     */
//  //  /*   which is useful in determining the amount of greenhouse effect on a    */
//  //  /*   planet.                                                                */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  double opacity(molecular_weight, surface_pressure)
//  //  double molecular_weight, surface_pressure;
//  //  {
//  //    double optical_depth;
//  //
//  //    optical_depth = 0.0;
//  //    if ((molecular_weight >= 0.0) && (molecular_weight < 10.0))
//  //      optical_depth = optical_depth + 3.0;
//  //    if ((molecular_weight >= 10.0) && (molecular_weight < 20.0))
//  //      optical_depth = optical_depth + 2.34;
//  //    if ((molecular_weight >= 20.0) && (molecular_weight < 30.0))
//  //      optical_depth = optical_depth + 1.0;
//  //    if ((molecular_weight >= 30.0) && (molecular_weight < 45.0))
//  //      optical_depth = optical_depth + 0.15;
//  //    if ((molecular_weight >= 45.0) && (molecular_weight < 100.0))
//  //      optical_depth = optical_depth + 0.05;
//  //
//  //    if (surface_pressure >= (70.0 * EARTH_SURF_PRES_IN_MILLIBARS))
//  //      optical_depth = optical_depth * 8.333;
//  //    else if (surface_pressure >= (50.0 * EARTH_SURF_PRES_IN_MILLIBARS))
//  //      optical_depth = optical_depth * 6.666;
//  //    else if (surface_pressure >= (30.0 * EARTH_SURF_PRES_IN_MILLIBARS))
//  //      optical_depth = optical_depth * 3.333;
//  //    else if (surface_pressure >= (10.0 * EARTH_SURF_PRES_IN_MILLIBARS))
//  //      optical_depth = optical_depth * 2.0;
//  //    else if (surface_pressure >= (5.0 * EARTH_SURF_PRES_IN_MILLIBARS))
//  //      optical_depth = optical_depth * 1.5;
//  //    return(optical_depth);
//  //  }
//  //
//  //
//  //  /*--------------------------------------------------------------------------*/
//  //  /*   The temperature calculated is in degrees Kelvin.                       */
//  //  /*   Quantities already known which are used in these calculations:         */
//  //  /*       ecosphere_radius                                                   */
//  //  /*	 planet->molecule_weight		        		    */
//  //  /*	 planet->surface_pressure				            */
//  //  /*	 planet->a							    */
//  //  /*	 planet->volatile_gas_inventory					    */
//  //  /*	 planet->radius							    */
//  //  /*	 planet->boil_point						    */
//  //  /*--------------------------------------------------------------------------*/
//  //
//  //  void iterate_surface_temp(planet)
//  //  planet_pointer *planet;
//  //  {
//  //    double surf1_temp, effective_temp, greenhouse_rise, previous_temp,
//  //    optical_depth, albedo, water, clouds, ice;
//  //
//  //    optical_depth = opacity((*planet)->molecule_weight,(*planet)->surface_pressure);
//  //    effective_temp = eff_temp(ecosphere_radius,(*planet)->a,EARTH_ALBEDO);
//  //    greenhouse_rise = green_rise(optical_depth,effective_temp,(*planet)->surface_pressure);
//  //    surf1_temp = effective_temp + greenhouse_rise;
//  //    previous_temp = surf1_temp - 5.0;		/* force the while loop the first time */
//  //    while ((fabs(surf1_temp - previous_temp) > 1.0)) {
//  //      previous_temp = surf1_temp;
//  //      water = hydrosphere_fraction((*planet)->volatile_gas_inventory,(*planet)->radius);
//  //      clouds = cloud_fraction(surf1_temp,(*planet)->molecule_weight,(*planet)->radius,water);
//  //      ice = ice_fraction(water,surf1_temp);
//  //      if ((surf1_temp >= (*planet)->boil_point) || (surf1_temp <= FREEZING_POINT_OF_WATER))
//  //        water = 0.0;
//  //      albedo = planet_albedo(water,clouds,ice,(*planet)->surface_pressure);
//  //      optical_depth = opacity((*planet)->molecule_weight,(*planet)->surface_pressure);
//  //      effective_temp = eff_temp(ecosphere_radius,(*planet)->a,albedo);
//  //      greenhouse_rise = green_rise(optical_depth,effective_temp,(*planet)->surface_pressure);
//  //      surf1_temp = effective_temp + greenhouse_rise;
//  //    }
//  //    (*planet)->hydrosphere = water;
//  //    (*planet)->cloud_cover = clouds;
//  //    (*planet)->ice_cover = ice;
//  //    (*planet)->albedo = albedo;
//  //    (*planet)->surf_temp = surf1_temp;
//  //  }
//}
