(*----------------------------------------------------------------------*)
(* Copywrite (C) 1988 Matthew Burdick					*)
(* This code may be freely distributed.					*)
(*----------------------------------------------------------------------*)
   Procedure Set_Initial_conditions(Inner_limit_of_dust, Outer_limit_of_dust : real);
      Begin
         New (Dust_head);
         Planet_head:= nil;
         Dust_head^.Next_band:= nil;
         Dust_head^.Outer_edge:= Outer_limit_of_dust;
         Dust_head^.Inner_edge:= Inner_limit_of_dust ;
         Dust_head^.Dust_present:= true;
         Dust_head^.Gas_present:= true;
         Dust_left:= true;
      End;

   Function Stellar_dust_limit (Stellar_mass_ratio : real) : real;
      Begin
	Stellar_dust_limit:= 200.0 * power(Stellar_mass_ratio, 1/3);
      End;

   Function Innermost_planet (stellar_mass_ratio : real) : real;
      Begin
	Innermost_planet:= 0.3 * power(Stellar_mass_ratio, 1/3);
      End;

   Function Outermost_planet (stellar_mass_ratio : real) : real;
      Begin
	Outermost_planet:= 50.0 * power(Stellar_mass_ratio, 1/3);
      End;

   Procedure Update_dust_lanes (min, max, mass, crit_mass,
				body_inner_bound, body_outer_bound : real);
      VAR gas : boolean;
          Node1, Node2, Node3 : Dust_Pointer;
      Begin
         Dust_left:= false;
         If (mass > crit_mass)
            then gas:= false
            else gas:= true;
         Node1:= Dust_head;
         While (node1 <> nil) do
            Begin
               If (Node1^.inner_edge < min) and (node1^.outer_edge > max)
                  then begin
                          New (node2);
                          Node2^.inner_edge:= min;
                          Node2^.outer_edge:= max;
                          If (Node1^.gas_present = true)
                             then Node2^.Gas_present:= gas
                             else Node2^.gas_present:= false;
                          Node2^.dust_present:= false;
                          New (node3);
                          Node3^.inner_edge:= max;
                          Node3^.outer_edge:= Node1^.outer_edge;
                          Node3^.gas_present:= Node1^.gas_present;
                          Node3^.dust_present:= Node1^.dust_present;
                          Node3^.next_band:= Node1^.next_band;
                          Node1^.next_band:= Node2;
                          Node2^.next_band:= Node3;
                          Node1^.outer_edge:= min;
                          Node1:= node3^.next_band;
                       end
               else If (Node1^.inner_edge < max) and (Node1^.outer_edge > max)
                  then begin
                          New (node2);
                          Node2^.next_band:= node1^.next_band;
                          node2^.dust_present:= node1^.dust_present;
                          node2^.gas_present:= node1^.gas_present;
                          node2^.outer_edge:= node1^.outer_edge;
                          node2^.inner_edge:= max;
                          Node1^.next_band:= node2;
                          node1^.outer_edge:= max;
                          If (Node1^.gas_present = true)
                             then Node1^.Gas_present:= gas
                             else Node1^.gas_present:= false;
                          Node1^.dust_present:= false;
                          Node1:= node2^.next_band;
                       end
               else If (Node1^.inner_edge < min) and (Node1^.outer_edge > min)
                  then begin
                          New (node2);
                          Node2^.next_band:= node1^.next_band;
                          node2^.dust_present:= false;
                          If (Node1^.gas_present = true)
                             then Node2^.Gas_present:= gas
                             else Node2^.gas_present:= false;
                          node2^.outer_edge:= node1^.outer_edge;
                          node2^.inner_edge:= min;
                          Node1^.next_band:= node2;
                          node1^.outer_edge:= min;
                          node1:= node2^.next_band;
                       end
               else If (Node1^.inner_edge >= min) and (node1^.outer_edge <= max)
                  then begin
                          If (node1^.gas_present = true)
                             then Node1^.gas_present:= gas;
                          Node1^.dust_present:= false;
                          node1:= node1^.next_band;
                       end
               else if (node1^.outer_edge < min) or (node1^.inner_edge > max)
                  then node1:= node1^.next_band;
            End;
         Node1:= Dust_head;
         While (node1 <> nil) do
            Begin
               If (node1^.dust_present) and ((node1^.outer_edge >= body_inner_bound)
                  and (node1^.inner_edge <= body_outer_bound))
                  then dust_left:= true;
               node2:= node1^.next_band;
               If (node2 <> nil)
                  then begin
                          If (node1^.dust_present = node2^.dust_present)
                             and (node1^.gas_present = node2^.gas_present)
                             then begin
                                     node1^.outer_edge:= node2^.outer_edge;
                                     node1^.next_band:= node2^.next_band;
                                     dispose (node2);
                                  end;
                       end;
               node1:= node1^.next_band;
            End;
      End;

   Function Collect_dust (VAR R_inner, R_outer, reduced_mass : real;
			  last_mass, a, e, dust_density, crit_mass,
			  cloud_eccentricity : real;
                          Dust_band : Dust_pointer) : real;
      VAR Mass_density, temp1, temp2, temp, temp_density,
          bandwidth, width, volume : real;
      Begin
         temp:= last_mass/(1 + last_mass);
         Reduced_mass:= power(temp, 1/4);
         R_inner:=a*(1 - e)*(1 - reduced_mass)/(1 + Cloud_eccentricity);
         R_outer:=a*(1 + e)*(1 + reduced_mass)/(1 - Cloud_eccentricity);
         If (R_inner < 0.0) then R_inner:= 0.0;
         If (Dust_band = nil)
            then Collect_dust:= 0.0
            else begin
                    If (dust_band^.dust_present = false)
                       then temp_density:= 0.0
                       else temp_density:= dust_density;
                    If (last_mass < Crit_mass) or (dust_band^.gas_present = false)
                       then Mass_density:= temp_density
                       else Mass_density:= K * temp_density/(1 + Sqrt(Crit_mass/last_mass)*(K - 1));
                    If (dust_band^.outer_edge <= R_inner)
                       or (dust_band^.inner_edge >= R_outer)
                       then Collect_dust:= Collect_dust (R_inner, R_outer, reduced_mass,
			       last_mass, a, e, dust_density, crit_mass,
			       cloud_eccentricity, Dust_band^.next_band)
                       else begin
                               bandwidth:= (R_outer - R_inner);
                               temp1:= R_outer - Dust_band^.Outer_edge;
                               If (temp1 < 0) then temp1:= 0;
                               width:= bandwidth - temp1;
                               Temp2:= Dust_Band^.Inner_edge - R_inner;
                               If (temp2 < 0) then temp2:= 0;
                               width:= width - temp2;
                               temp:= 4 * Pi * Sqr(a) * Reduced_mass
                                      * (1 - e*(temp1 - temp2)/bandwidth);
                               volume:= temp * width;
                               Collect_dust:= volume * mass_density
                                              + Collect_dust (R_inner, R_outer, reduced_mass,
						   last_mass, a, e, dust_density, crit_mass,
						   cloud_eccentricity, Dust_band^.next_band);
                            end;
                 end;
      End;

   Function critical_limit (orbital_radius, eccentricity,
			    Stellar_luminosity_ratio : real) : real;
(*--------------------------------------------------------------------------*)
(*   Orbital radius is in AU, eccentricity is unitless, and the stellar     *)
(*  luminosity ratio is with respect to the sun.  The value returned is the *)
(*  mass at which the planet begins to accrete gas as well as dust, and is  *)
(*  in units of solar masses.                                               *)
(*--------------------------------------------------------------------------*)
      VAR temp, Perihelion_dist : real;
      Begin
         Perihelion_dist:= (orbital_radius - orbital_radius*eccentricity);
         Temp:= Perihelion_dist * Sqrt(Stellar_luminosity_ratio);
         Critical_limit:= B * power(temp, -0.75);
      End;


   Procedure Accrete_dust (VAR seed_mass, reduced_mass : real;
			   a, e, crit_mass, Stellar_mass_ratio,
			   cloud_eccentricity,
			   body_inner_bound, body_outer_bound : real);
      VAR Perihelion_dist, new_mass, temp_mass, dust_density,
	  R_inner, R_outer : real;
      Begin
         Dust_density:= Dust_density_coeff * Sqrt(Stellar_mass_ratio)*
            Exp(-alpha*power(a, 1/N));
(*         Crit_mass:= critical_limit (a, e, Stellar_luminosity_ratio);*)
         New_mass:= seed_mass;
         Repeat
            temp_mass:= new_mass;
            new_mass:= collect_dust (R_inner, R_outer, reduced_mass, new_mass,
		 a, e, dust_density, crit_mass, cloud_eccentricity, Dust_head);
          Until ((new_mass - temp_mass) < (0.0001 * temp_mass));
         Seed_Mass:= seed_mass + new_mass;
         Update_dust_lanes (R_inner, R_outer, seed_mass, crit_mass,
			body_inner_bound, body_outer_bound);
      End;

   Procedure Coalesce_planetesimals (VAR reduced_mass : real;
		a, e, mass, crit_mass,
		Stellar_mass_ratio, Stellar_luminosity_ratio,
		cloud_eccentricity,
		body_inner_bound, body_outer_bound : real);
      VAR node1, node2, node3 : planet_pointer;
          coalesced : boolean;
          temp, Dist1, Dist2, a3 : real;
      Begin
         Coalesced:= false;
         node1:= planet_head;
         While (node1 <> nil) do
            begin
               node2:= node1;
               temp:= node1^.a - a;
               If (temp > 0)
                  then begin
                          Dist1:= (a*(1 + e)*(1 + reduced_mass)) - a;  (* x aphelion   *)
                          reduced_mass:= power(node1^.mass/(1 + node1^.mass), 1/4);
                          Dist2:= node1^.a - (node1^.a*(1 - node1^.e)*(1 - reduced_mass));
                       end
                  else begin
                          Dist1:= a - (a*(1 - e)*(1 - reduced_mass));  (* x perihelion *)
                          reduced_mass:= power(node1^.mass/(1 + node1^.mass), 1/4);
                          Dist2:= (node1^.a*(1 + node1^.e)*(1 + reduced_mass)) - node1^.a;
                       end;
               If (Abs(temp) <= Abs(Dist1)) or (Abs(temp) <= Abs(Dist2))
                  then begin
{                          writeln(^G, 'SMASH!');}
                          writeln('SMASH!');
                          a3:= (node1^.mass + mass)/((node1^.mass/node1^.a) + (mass/a));
                          temp:= node1^.mass * sqrt(node1^.a) * sqrt(1 - sqr(node1^.e));
                          temp:= temp + (mass * sqrt(a) * sqrt(sqrt(1 - sqr(e))));
                          temp:= temp/((node1^.mass + mass) * sqrt(a3));
                          temp:= 1 - Sqr(temp);
                          If (temp < 0.0) or (temp >= 1.0)
                             then temp:= 0.0;
                          e:= Sqrt(temp);
                          temp:= node1^.mass + mass;
                          Accrete_dust (temp, reduced_mass, a3, e,
				Stellar_mass_ratio, Stellar_luminosity_ratio,
				cloud_eccentricity,
				body_inner_bound, body_outer_bound);
                          node1^.a:= a3;
                          node1^.e:= e;
                          node1^.mass:= temp;
                          node1:= nil;
                          coalesced:= true;
                       end
                  else Node1:= node1^.next_planet;
            end;
         If not coalesced
            then begin
                    New (node3);
                    node3^.a:= a;
                    node3^.e:= e;
                    If (mass >= crit_mass)
                       then node3^.gas_giant:= true
                       else node3^.gas_giant:= false;
                    node3^.mass:= mass;
                    If (Planet_head = nil)
                       then begin
                               Planet_head:= node3;
                               node3^.next_planet:= nil;
                            end
                       else begin
                               node1:= planet_head;
                               If (a < node1^.a)
                                  then begin
                                          node3^.next_planet:= node1;
                                          planet_head:= node3;
                                       end
                                  else If (planet_head^.next_planet = nil)
                                    then begin
                                            planet_head^.next_planet:= node3;
                                            node3^.next_planet:= nil;
                                         end
                                    else begin
                                            while (node1 <> nil) and (node1^.a < a)
                                               do begin
                                                     node2:= node1;
                                                     node1:= node1^.next_planet;
                                                  end;
                                            node3^.next_planet:= node1;
                                            node2^.next_planet:= node3;
                                         end;
                            end;
                 end;
      End;

   Function Distribute_planetary_masses (stellar_mass_ratio,
                                         Stellar_luminosity_ratio,
					 inner_dust, outer_dust : real) : planet_pointer;
      VAR a, e, mass, crit_mass, reduced_mass, cloud_eccentricity,
	       Planetesimal_inner_bound, Planetesimal_outer_bound : real;
      Begin
         Set_initial_conditions(inner_dust, outer_dust);
         While dust_left do
            Begin
{         Cloud_eccentricity:= Random_eccentricity;}
	       Cloud_eccentricity:= 0.2;
               mass:= protoplanet_mass;
	       Planetesimal_inner_bound:= Innermost_planet(stellar_mass_ratio);
	       Planetesimal_outer_bound:= Outermost_planet(stellar_mass_ratio);
               a:= Random_number (Planetesimal_inner_bound, Planetesimal_outer_bound);
               e:= Random_eccentricity;
               Crit_mass:= critical_limit (a, e, Stellar_luminosity_ratio);
               Accrete_dust (mass, reduced_mass, a, e, crit_mass,
			Stellar_mass_ratio, cloud_eccentricity,
			Planetesimal_inner_bound, Planetesimal_outer_bound);
               If (mass <> 0.0) and (mass <> protoplanet_mass)
                  then Coalesce_planetesimals (reduced_mass, a, e, mass, crit_mass,
			Stellar_mass_ratio, Stellar_luminosity_ratio,
			cloud_eccentricity,
			Planetesimal_inner_bound, Planetesimal_outer_bound);
            End;
	 Distribute_planetary_masses := planet_head;
      End;

   Function Distribute_moon_masses (Planetary_mass, Stellar_luminosity_ratio,
	planet_eccentricity,
	inner_dust, outer_dust : real) : planet_pointer;
      VAR a, e, mass, crit_mass, reduced_mass, cloud_eccentricity,
	       Planetesimal_inner_bound, Planetesimal_outer_bound : real;
      Begin
(*         Set_initial_conditions(inner_dust, outer_dust);
         While dust_left do
            Begin
	       Cloud_eccentricity:= 0.2;
               mass:= protomoon_mass;
	       Planetesimal_inner_bound:= Innermost_planet(planetary_mass);
	       Planetesimal_outer_bound:= Outermost_planet(planetary_mass);
               a:= Random_number (Planetesimal_inner_bound, Planetesimal_outer_bound);
               e:= Random_eccentricity;
               Crit_mass:= critical_limit (a, planet_eccentricity,
			Stellar_luminosity_ratio);
               Accrete_dust (mass, reduced_mass, a, e, crit_mass,
			Stellar_mass_ratio, cloud_eccentricity,
			Planetesimal_inner_bound, Planetesimal_outer_bound);
               If (mass <> 0.0) and (mass <> protoplanet_mass)
                  then Coalesce_planetesimals (reduced_mass, a, e, mass, crit_mass,
			planetary_mass, Stellar_luminosity_ratio,
			cloud_eccentricity,
			Planetesimal_inner_bound, Planetesimal_outer_bound);
            End;
	 Distribute_moon_masses := planet_head;*)
      End;


