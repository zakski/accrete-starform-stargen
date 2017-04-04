(*----------------------------------------------------------------------*)
(* Copywrite (C) 1988 Matthew Burdick					*)
(* This code may be freely distributed.					*)
(*----------------------------------------------------------------------*)
   Function Luminosity (mass_ratio : real) : real;
      VAR N : real;
      Begin
         If (mass_ratio < 1.0)
            then N:= 1.75*(mass_ratio - 0.1) + 3.325
            else N:= 0.5*(2.0 - mass_ratio) + 4.4;
         Luminosity:= Power (mass_ratio, N);
      End;

   Function Orbital_zone (orbital_radius : real) : integer;
(*--------------------------------------------------------------------------*)
(*   This function, given the orbital radius of a planet in AU, returns     *)
(*   the orbital 'zone' of the particle.                                    *)
(*--------------------------------------------------------------------------*)
      Begin
         If (orbital_radius < (4 * sqrt(Stellar_luminosity_ratio)))
            then Orbital_zone:= 1
            else begin
                    if (orbital_radius >= (4 * sqrt(Stellar_luminosity_ratio)))
                        and (orbital_radius < (15 * sqrt(Stellar_luminosity_ratio)))
                       then Orbital_zone:= 2
                       else Orbital_zone:= 3;
                 end;
      End;

   Function Volume_radius (mass, density : real) : real;
(*--------------------------------------------------------------------------*)
(*   The mass is in units of solar masses, and the density is in units      *)
(*   of grams/cc.  The radius returned is in units of km.                   *)
(*--------------------------------------------------------------------------*)
      VAR volume : real;
      Begin
         mass:= mass * solar_mass_in_grams;
         volume:= mass / density;
         Volume_radius:= power((3.0 * volume)/(4.0 * Pi),1/3) / cm_per_km;
      End;

   Function Kothari_radius (mass, orbital_radius : real;
                           giant : boolean;
                           zone : integer) :real;
(*--------------------------------------------------------------------------*)
(*    Returns the radius of the planet in kilometers.                       *)
(*   The mass passed in is in units of solar masses, the orbital radius     *)
(*   in A.U.                                                                *)
(*   This formula is listed as eq.9 in Fogg's article, although some typos  *)
(*   crop up in that eq.  See "The Internal Constitution of Planets", by    *)
(*   Dr. D. S. Kothari, Mon. Not. of the Royal Astronomical Society, vol 96 *)
(*   pp.833-843, 1936 for the derivation.  Specifically, this is Kothari's  *)
(*   eq.23, which appears on page 840.                                      *)
(*--------------------------------------------------------------------------*)
      VAR temp, temp2, atomic_weight, atomic_num : real;
      CONST a1 = 6.485E12;      (* All units are in cgs system.  *)
            a2 = 4.0032E-8;     (*   ie: cm, g, dynes, etc.      *)
            Beta = 5.71E12;
      Begin
         If (zone = 1)
            then begin
                    If giant then begin
                                     atomic_weight:= 9.5;
                                     atomic_num:= 4.5;
                                  end
                             else begin
                                     atomic_weight:= 15.0;
                                     atomic_num:= 8.0;
                                  end;
                 end
            else if (zone = 2)
                    then begin
                            If giant then begin
                                             atomic_weight:= 2.47;
                                             atomic_num:= 2.0;
                                          end
                                      else begin
                                              atomic_weight:= 10.0;
                                              atomic_num:= 5.0;
                                           end;
                         end
                    else begin
                            If giant then begin
                                             atomic_weight:=7.0;
                                             atomic_num:= 4.0;
                                          end
                                     else begin
                                             atomic_weight:= 10.0;
                                             atomic_num:= 5.0;
                                          end;
                         end;
         temp:= atomic_weight*atomic_num;
         temp:= (2.0*Beta*power(Solar_mass_in_grams, 1/3))/(a1*power(temp, 1/3));
         temp2:= a2*power(atomic_weight, 4/3)*power(Solar_mass_in_grams, 2/3);
         temp2:= temp2 * power(mass, 2/3);
         temp2:= temp2 / (a1*Sqr(atomic_num));
         temp2:= 1 + temp2;
         temp:= temp / temp2;
         temp:= (temp * power(mass, 1/3)) / cm_per_km;
         Kothari_radius:= temp;
      End;

   Function Empirical_density (mass, Orbital_radius : real;
                            gas_giant : boolean ) : real;
(*--------------------------------------------------------------------------*)
(*  The mass passed in is in units of solar masses, and the orbital radius  *)
(*  is in units of AU.  The density is returned in units of grams/cc.       *)
(*--------------------------------------------------------------------------*)
      VAR temp : real;
      Begin
         temp:= power (mass*Earth_masses_per_solar_mass, 1/8);
         temp:= temp * power(R_ecosphere/Orbital_radius, 1/4);
         If (gas_giant)
            then Empirical_density:= temp * 1.2
            else Empirical_density:= temp * 5.5;
      End;

   Function Volume_density (mass, equatorial_radius : real) : real;
(*--------------------------------------------------------------------------*)
(*  The mass passed in is in units of solar masses, and the equatorial      *)
(*  radius is in km.  The density is returned in units of grams/cc.         *)
(*--------------------------------------------------------------------------*)
      VAR volume : real;
      Begin
         mass:= mass * solar_mass_in_grams;
         equatorial_radius:= equatorial_radius * cm_per_km;
         volume:= (4.0 * Pi * power(equatorial_radius, 3.0))/3.0;
         Volume_density:= mass / volume;
      End;

   Function Period (separation, small_mass, large_mass : real) : real;
(*--------------------------------------------------------------------------*)
(*  The separation is in units of AU, and both masses are in units of solar *)
(*  masses.  The period returned is in terms of Earth days.                 *)
(*--------------------------------------------------------------------------*)
      VAR period_in_years : real;
      Begin
         period_in_years:= sqrt ( power(separation, 3.0) /
                                  (small_mass + large_mass) );
         Period:= period_in_years * days_in_a_year;
      End;

   Function Day_length (mass, radius, orbital_period, eccentricity : real;
                        giant : boolean) : real;
(*--------------------------------------------------------------------------*)
(*   Fogg's information for this routine came from Dole "Habitable Planets  *)
(* for Man", Blaisdell Publishing Company, NY, 1964.  From this, he came    *)
(* up with his eq.12, which is the equation for the base_angular_velocity   *)
(* below.  Going a bit further, he found an equation for the change in      *)
(* angular velocity per time (dw/dt) from P. Goldreich and S. Soter's paper *)
(* "Q in the Solar System" in Icarus, vol 5, pp.375-389 (1966).  Comparing  *)
(* to the change in angular velocity for the Earth, we can come up with an  *)
(* approximation for our new planet (his eq.13) and take that into account. *)
(*--------------------------------------------------------------------------*)
      VAR base_angular_velocity, planetary_mass_in_grams,
          k2, equatorial_radius_in_cm, change_in_angular_velocity,
          spin_resonance_period, temp : real;
      Begin
         spin_resonance:= FALSE;
         If giant
            then k2:= 0.24
            else k2:= 0.33;
         planetary_mass_in_grams:= mass * Solar_mass_in_grams;
         equatorial_radius_in_cm:= radius * cm_per_km;
         base_angular_velocity:= sqrt(2.0 * j * (planetary_mass_in_grams)
                                      / (k2 * sqr(equatorial_radius_in_cm)));
(* not done here.  Try to add the dw/dt stuff after finding out what Q' is *)
         change_in_angular_velocity:= 0.0;
         temp:= base_angular_velocity + (change_in_angular_velocity * age);
(* temp is now the angular velocity. Change from rad/sec now to hours/rotation *)
         temp:= 1.0 / ((temp / radians_per_rotation) * seconds_per_hour);
         If (temp >= orbital_period)
            then begin
                    spin_resonance_period:= ((1.0 - eccentricity) /
                          (1.0 + eccentricity)) * orbital_period;
                   if (eccentricity > 0.1)
                       then begin
                               temp:= spin_resonance_period;
                               spin_resonance:= TRUE;
                            end
                       else temp:= orbital_period;
                 end;
         Day_length:= temp;
      End;

   Function inclination (orbital_radius : real) : integer;
(*--------------------------------------------------------------------------*)
(*   The orbital radius is expected in units of Astronomical Units (AU).    *)
(*   Inclination is returned in units of degrees.                           *)
(*--------------------------------------------------------------------------*)
      VAR temp : integer;
      Begin
         temp:= trunc(power(orbital_radius, 0.2) * about(Earth_axial_tilt, 0.4));
         inclination:= (temp mod 360);
      End;

   Function Escape_vel (mass, radius : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function implements the escape velocity calculation.  Note that   *)
(*  it appears that Fogg's eq.15 is incorrect.                              *)
(*  The mass is in units of solar mass, the radius in kilometers, and the   *)
(*  velocity returned is in cm/sec.                                         *)
(*--------------------------------------------------------------------------*)
      VAR mass_in_grams, radius_in_cm : real;
      Begin
         mass_in_grams:= mass * Solar_mass_in_grams;
         radius_in_cm:= radius * cm_per_km;
         Escape_vel:= sqrt(2 * Grav_constant * mass_in_grams / radius_in_cm);
      End;

   Function RMS_vel (molecular_weight, orbital_radius : real) : real;
(*--------------------------------------------------------------------------*)
(*  This is Fogg's eq.16.  The molecular weight (usually assumed to be N2)  *)
(*  is used as the basis of the Root Mean Square velocity of the molecule   *)
(*  or atom.  The velocity returned is in cm/sec.                           *)
(*--------------------------------------------------------------------------*)
   VAR exospheric_temp : real;
   Begin
      exospheric_temp:= Earth_exosphere_temp / Sqr(orbital_radius);
      RMS_vel:= Sqrt((3.0 * Molar_Gas_const * exospheric_temp)/
                molecular_weight) * cm_per_meter;
   End;

   Function Molecule_limit (orbital_radius, mass, equatorial_radius : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function returns the smallest molecular weight retained by the    *)
(*  body, which is useful for determining the atmosphere composition.       *)
(*  Orbital radius is in A.U.(ie: in units of the earth's orbital radius),  *)
(*  mass is in units of solar masses, and equatorial radius is in units of  *)
(*  kilometers.                                                             *)
(*--------------------------------------------------------------------------*)
      VAR numerator, denominator1, denominator2,
          escape_velocity, temp : real;
      Begin
         escape_velocity:= escape_vel(mass, equatorial_radius);
         molecule_limit:= (3.0 * sqr(gas_retention_threshold * cm_per_meter)
                          * Molar_gas_const * earth_exosphere_temp)
                          /sqr(escape_velocity);
{         numerator:= (2.0 * sqr(gas_retention_threshold) * Bolzmann_const *
                     earth_exosphere_temp);
         denominator1:= sqr(orbital_radius);
         denominator2:= sqr(escape_velocity);
         temp:= numerator/denominator1;
         Molecule_limit:= temp/denominator2;}
      End;

   Function Acceleration (mass, radius : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function calculates the surface acceleration of a planet.  The    *)
(*  mass is in units of solar masses, the radius in terms of km, and the    *)
(*  acceleration is returned in units of cm/sec2.                           *)
(*--------------------------------------------------------------------------*)
   Begin
      acceleration:= Grav_constant * (mass * solar_mass_in_grams)
                           /sqr(radius * cm_per_km);
   End;

   Function gravity (acceleration : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function calculates the surface gravity of a planet.  The         *)
(*  acceleration is in units of cm/sec2, and the gravity is returned in     *)
(*  units of Earth gravities.                                               *)
(*--------------------------------------------------------------------------*)
   Begin
      gravity:= acceleration / Earth_acceleration;
   End;

   Function Greenhouse (zone : integer;
                        orbital_radius, greenhouse_radius : real) : boolean;
(*--------------------------------------------------------------------------*)
(*  Note that if the orbital radius of the planet is greater than or equal  *)
(*  to R_inner, 99% of it's volatiles are assumed to have been deposited in *)
(*  surface reservoirs (otherwise, it suffers from the greenhouse effect).  *)
(*--------------------------------------------------------------------------*)
      Begin
         If ((orbital_radius < greenhouse_radius) and (zone = 1))
            then greenhouse:= true
            else greenhouse:= false;
      End;

   Function Vol_inventory (mass, escape_vel, RMS_vel, stellar_mass : real;
                           zone : integer;
                           greenhouse_effect : boolean ) : real;
(*--------------------------------------------------------------------------*)
(*  This implements Fogg's eq.17.  The 'inventory' returned is unitless.    *)
(*--------------------------------------------------------------------------*)
      VAR velocity_ratio, proportion_const, temp1, temp2,
          mass_in_earth_units : real;
      Begin
         velocity_ratio:= escape_vel / RMS_vel;
         If (velocity_ratio >= gas_retention_threshold)
            then begin
                    CASE zone of
                      1 : proportion_const:= 100000.0;
                      2 : proportion_const:= 75000.0;
                      3 : proportion_const:= 250.0;
                      else writeln(^G,'Error: orbital zone not initialized correctly!');
                    END;
                    mass_in_earth_units:= mass * earth_masses_per_solar_mass;
                    temp1:=(proportion_const * mass_in_earth_units) / stellar_mass;
                    temp2:= about(temp1, 0.2);
                    If (greenhouse_effect)
                       then vol_inventory:= temp2
                       else vol_inventory:= temp2 / 100.0;
                 end
            else vol_inventory:= 0.0;
      End;

   Function Pressure (volatile_gas_inventory, equatorial_radius,
                      gravity : real) : real;
(*--------------------------------------------------------------------------*)
(*  This implements Fogg's eq.18.  The pressure returned is in units of     *)
(*  millibars (mb).  The gravity is in units of Earth gravities, the radius *)
(*  in units of kilometers.                                                 *)
(*--------------------------------------------------------------------------*)
   Begin
      equatorial_radius:= earth_radius_in_km / equatorial_radius;
      Pressure:= volatile_gas_inventory * gravity / Sqr(equatorial_radius);
   End;

{   Function Atmosphere_type (pressure, age : real;
                             giant : boolean) : integer;
      Begin
         If (giant)
            then atmosphere_type:= 8
            else If (pressure = 0.0)
                    then Atmosphere_type:= 0
                    else begin
                         end;
      End;}

   Function Boiling_point (surface_pressure : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function returns the boiling point of water in an atmosphere of   *)
(*   pressure 'surface_pressure', given in millibars.  The boiling point is *)
(*   returned in units of Kelvin.  This is Fogg's eq.21.                    *)
(*--------------------------------------------------------------------------*)
      VAR surface_pressure_in_bars : real;
      Begin
         surface_pressure_in_bars:= surface_pressure / millibars_per_bar;
         boiling_point:= 1.0 / (Ln(surface_pressure_in_bars)/-5050.5
                                    + 1.0/373);
      End;

   Function hydrosphere_fraction (volatile_gas_inventory, planetary_radius : real) : real;
(*--------------------------------------------------------------------------*)
(*   This function is Fogg's eq.22.  Given the volatile gas inventory and   *)
(*   planetary radius of a planet (in Km), this function returns the        *)
(*   fraction of the planet covered with water.                             *)
(*   I have changed the function very slightly:  the fraction of Earth's    *)
(*   surface covered by water is 71%, not 75% as Fogg used.                 *)
(*--------------------------------------------------------------------------*)
      VAR temp : real;
      Begin
         temp:= (0.71 * volatile_gas_inventory / 1000.0) *
               Sqr(Earth_radius_in_km / planetary_radius);
         If (temp >= 1.0)
            then hydrosphere_fraction:= 1.0
            else hydrosphere_fraction:= temp;
      End;

   Function Cloud_fraction (surface_temp,
                            smallest_molecular_weight_retained,
                            equatorial_radius,
                            hydrosphere_fraction : real) : real;
(*--------------------------------------------------------------------------*)
(*   Given the surface temperature of a planet (in Kelvin), this function   *)
(*   returns the fraction of cloud cover available.  This is Fogg's eq.23.  *)
(*   See Hart in "Icarus" (vol 33, pp23 - 39, 1978) for an explanation.     *)
(*   This equation is Hart's eq.3.                                          *)
(*   I have modified it slightly using constants and relationships from     *)
(*   Glass's book "Introduction to Planetary Geology", p.46.                *)
(*--------------------------------------------------------------------------*)
      CONST Q1 = 1.258E19;   { grams    }
            Q2 = 0.0698;     { 1/Kelvin }
      VAR water_vapor_in_kg, fraction, surface_area,
          hydrosphere_mass : real;
      Begin
         If (smallest_molecular_weight_retained > water_vapor)
            then cloud_fraction:= 0.0
            else begin
                    surface_area:= 4.0 * Pi * Sqr(equatorial_radius);
{                    water_vapor_in_grams:= Q1 * exp(Q2 * (surface_temp - 288.0));}
                    hydrosphere_mass:= hydrosphere_fraction * surface_area
                                       * Earth_water_mass_per_area;
                    water_vapor_in_kg:= (0.00000001 * hydrosphere_mass)
                                            * exp(Q2 * (surface_temp - 288.0));
                    fraction:= Earth_area_covered_per_kg_of_cloud *
                              water_vapor_in_kg / surface_area;
                    if (fraction >= 1.0)
                       then cloud_fraction:= 1.0
                       else cloud_fraction:= fraction;
                 end;
      End;

   Function Ice_fraction (hydrosphere_fraction, surface_temp : real) : real;
(*--------------------------------------------------------------------------*)
(*   Given the surface temperature of a planet (in Kelvin), this function   *)
(*   returns the fraction of the planet's surface covered by ice.  This is  *)
(*   Fogg's eq.24.  See Hart[24] in Icarus vol.33, p.28 for an explanation. *)
(*   I have changed a constant from 70 to 90 in order to bring it more in   *)
(*   line with the fraction of the Earth's surface covered with ice, which  *)
(*   is approximatly .016 (=1.6%).                                          *)
(*--------------------------------------------------------------------------*)
      VAR temp : real;
      Begin
{         temp:= power(((328.0 - surface_temp) / 70.0),5.0);}
         temp:= power(((328.0 - surface_temp) / 90.0),5.0);
         if (temp > (1.5 * hydrosphere_fraction))
            then temp:= (1.5 * hydrosphere_fraction);
         if (temp >= 1.0)
            then ice_fraction:= 1.0
            else ice_fraction:= temp;
      End;

   Function Eff_temp (ecosphere_radius, orbital_radius, albedo : real) : real;
(*--------------------------------------------------------------------------*)
(*  This is Fogg's eq.19.  The ecosphere radius is given in AU, the orbital *)
(*  in AU, and the temperature returned is in Kelvin.                       *)
(*--------------------------------------------------------------------------*)
      Begin
         Eff_temp:= Sqrt(ecosphere_radius / orbital_radius) *
            power((1-albedo)/0.7, 0.25) * Earth_effective_temp;
      End;

   Function Green_rise (optical_depth, effective_temp,
                        surface_pressure : real) : real;
(*--------------------------------------------------------------------------*)
(*  This is Fogg's eq.20, and is also Hart's eq.20 in his "Evolution of     *)
(*  Earth's Atmosphere" article.  The effective temperature given is in     *)
(*  units of Kelvin, as is the rise in temperature produced by the          *)
(*  greenhouse effect, which is returned.                                   *)
(*--------------------------------------------------------------------------*)
      VAR convection_factor : real;
      Begin
         convection_factor:= Earth_convection_factor
           * power((surface_pressure / Earth_surface_pressure_in_millibars), 0.25);
         Green_rise:= (power((1 + 0.75*optical_depth), 0.25) - 1) *
                           effective_temp * convection_factor;
      End;

   Function Planet_albedo (water_fraction, cloud_fraction, ice_fraction,
                           surface_pressure : real) : real;
(*--------------------------------------------------------------------------*)
(*   The surface temperature passed in is in units of Kelvin.               *)
(*   The cloud adjustment is the fraction of cloud cover obscuring each     *)
(*   of the three major components of albedo that lie below the clouds.     *)
(*--------------------------------------------------------------------------*)
      VAR rock_fraction, cloud_adjustment, components, cloud_contribution,
          rock_contribution, water_contribution, ice_contribution : real;
      Begin
         rock_fraction:= 1.0 - water_fraction - ice_fraction;
         components:= 0.0;
         if (water_fraction > 0.0) then components:= components + 1;
         if (ice_fraction > 0.0) then components:= components + 1;
         if (rock_fraction > 0.0) then components:= components + 1;
         cloud_adjustment:= cloud_fraction / components;
         if (rock_fraction >= cloud_adjustment)
            then rock_fraction:= rock_fraction - cloud_adjustment
            else rock_fraction:= 0.0;
         if (water_fraction > cloud_adjustment)
            then water_fraction:= water_fraction - cloud_adjustment
            else water_fraction:= 0.0;
         if (ice_fraction > cloud_adjustment)
            then ice_fraction:= ice_fraction - cloud_adjustment
            else ice_fraction:= 0.0;
         cloud_contribution:= cloud_fraction * about(cloud_albedo, 0.2);
         if (surface_pressure = 0.0)
            then rock_contribution:= rock_fraction * about(airless_rocky_albedo, 0.3)
            else rock_contribution:= rock_fraction * about(rocky_albedo, 0.1);
         water_contribution:= water_fraction * about(water_albedo, 0.2);
         if (surface_pressure = 0.0)
            then ice_contribution:= ice_fraction * about(airless_ice_albedo, 0.4)
            else ice_contribution:= ice_fraction * about(ice_albedo, 0.1);
         planet_albedo:= cloud_contribution + rock_contribution
                         + water_contribution + ice_contribution;
      End;

   Function Opacity (molecular_weight, surface_pressure : real) : real;
(*--------------------------------------------------------------------------*)
(*   This funtion returns the dimensionless quantity of optical depth,      *)
(*   which is usefull in determining the amount of greenhouse effect on a   *)
(*   planet.                                                                *)
(*--------------------------------------------------------------------------*)
      VAR optical_depth : real;
      Begin
         optical_depth:= 0.0;
         if ((molecular_weight >= 0.0) and (molecular_weight < 10.0))
            then optical_depth:= optical_depth + 3.0;
         if ((molecular_weight >= 10.0) and (molecular_weight < 20.0))
            then optical_depth:= optical_depth + 2.34;
         if ((molecular_weight >= 20.0) and (molecular_weight < 30.0))
            then optical_depth:= optical_depth + 1.0;
         if ((molecular_weight >= 30.0) and (molecular_weight < 45.0))
            then optical_depth:= optical_depth + 0.15;
         if ((molecular_weight >= 45.0) and (molecular_weight < 100.0))
            then optical_depth:= optical_depth + 0.05;
         if (surface_pressure >= (70 * Earth_surface_pressure_in_millibars))
            then optical_depth:= optical_depth * 8.333
            else if (surface_pressure >= (50 * Earth_surface_pressure_in_millibars))
               then optical_depth:= optical_depth * 6.666
            else if (surface_pressure >= (30 * Earth_surface_pressure_in_millibars))
               then optical_depth:= optical_depth * 3.333
            else if (surface_pressure >= (10 * Earth_surface_pressure_in_millibars))
               then optical_depth:= optical_depth * 2.0
            else if (surface_pressure >= (5 * Earth_surface_pressure_in_millibars))
               then optical_depth:= optical_depth * 1.5;
         opacity:= optical_depth;
      End;

   Procedure Determine_albedo_and_surface_temp (VAR planet : planet_pointer);
(*--------------------------------------------------------------------------*)
(*   The temperature calculated is in degrees Kelvin.                       *)
(*   Quantities already known which are used in these calculations:         *)
(*       planet^.molecule_weight                                            *)
(*       planet^.surface_pressure                                           *)
(*       R_ecosphere                                                        *)
(*       planet^.a                                                          *)
(*       planet^.volatile_gas_inventory                                     *)
(*       planet^.radius                                                     *)
(*       planet^.boil_point                                                 *)
(*--------------------------------------------------------------------------*)
      VAR surface_temp, effective_temp, greenhouse_rise, previous_temp,
          optical_depth, albedo, water, clouds, ice : real;
      Begin
         optical_depth:= opacity(planet^.molecule_weight, planet^.surface_pressure);
         effective_temp:= Eff_temp(R_ecosphere, planet^.a, Earth_albedo);
         greenhouse_rise:= Green_rise(optical_depth, effective_temp,
                           planet^.surface_pressure);
         surface_temp:= effective_temp + greenhouse_rise;
         Repeat
            previous_temp:= surface_temp;
            water:= hydrosphere_fraction(planet^.volatile_gas_inventory, planet^.radius);
            clouds:= Cloud_fraction(surface_temp, planet^.molecule_weight,
                               planet^.radius, water);
            ice:= Ice_fraction(water, surface_temp);
            If (  (surface_temp >= planet^.boil_point)
               or (surface_temp <= freezing_point_of_water))
              then water:= 0.0;
            albedo:= planet_albedo(water, clouds, ice, planet^.surface_pressure);
            optical_depth:= opacity(planet^.molecule_weight, planet^.surface_pressure);
            effective_temp:= Eff_temp(R_ecosphere, planet^.a, albedo);
            greenhouse_rise:= Green_rise(optical_depth, effective_temp,
                              planet^.surface_pressure);
            surface_temp:= effective_temp + greenhouse_rise;
         Until (abs(surface_temp - previous_temp) <= 1.0);
         Planet^.hydrosphere:= water;
         Planet^.cloud_cover:= clouds;
         Planet^.ice_cover:= ice;
         Planet^.albedo:= albedo;
         Planet^.surface_temp:= surface_temp;
      End;


