{$R-}    {Range checking off}
{$B+}    {Boolean complete evaluation on}
{$S+}    {Stack checking on}
{$I+}    {I/O checking on}
{$N-}    {No numeric coprocessor}
{$M 65500,16384,655360} {Turbo 3 default stack and heap}

Program Stellar_System_Formation_Simulation;

(*----------------------------------------------------------------------*)
(* Copywrite (C) 1988 Matthew Burdick					*)
(* This code may be freely distributed.					*)
(*----------------------------------------------------------------------*)

(*----------------------------------------------------------------------*)
(*                           BIBLIOGRAPHY                               *)
(*  Dole, Stephen H.  "Formation of Planetary Systems by Aggregation:   *)
(*      a Computer Simulation"  October 1969,  Rand Corporation Paper   *)
(*      P-4226, (H31 .R188  #4226 in main lib)                          *)
(*----------------------------------------------------------------------*)

{Uses
  Crt,
  Printer;}

CONST
      eccentricity_coeff = 0.077;   (* Dole's was 0.077         *)
      Protoplanet_mass = 1.0E-15;   (* Units of solar masses    *)
      Solar_mass_in_grams = 1.989E33;  (* Units of grams        *)
      Earth_mass_in_grams = 5.977E27;  (* Units of grams        *)
      Earth_radius = 6.378E6;       (* Units of cm              *)
      Earth_radius_in_km = 6378.0;  (* Units of km              *)
      Earth_acceleration = 981.0;   (* Units of cm/sec2         *)
      Earth_axial_tilt = 23.4;      (* Units of degrees         *)
      Earth_exosphere_temp = 1273.0;(* Units of degrees Kelvin  *)
      Earth_masses_per_solar_mass = 332775.64;
      Earth_effective_temp = 255.0; (* Units of degrees Kelvin  *)
      Earth_albedo = 0.3;
      Earth_area_covered_per_kg_of_cloud = 1.839E-8; { Km2/kg }
      Earth_water_mass_per_area = 3.83E15; { grams per square km }
      Earth_surface_pressure_in_millibars = 1000.0;
      Earth_convection_factor = 0.43; (* from Hart, eq.20         *)
      Freezing_point_of_water = 273.0; (* Units of degrees Kelvin *)
      Days_in_a_year = 365.256;     (* Earth days per Earth year  *)
{         gas_retention_threshold = 6.0;}(* ratio of esc vel to RMS vel *)
      gas_retention_threshold = 5.0;(* ratio of esc vel to RMS vel *)
      gas_giant_albedo = 0.5;       (* albedo of a gas giant      *)
      cloud_albedo = 0.52;
      airless_rocky_albedo = 0.07;
      rocky_albedo = 0.15;
      water_albedo = 0.04;
      airless_ice_albedo = 0.5;
      ice_albedo = 0.7;
      Seconds_per_hour = 3600.0;
      cm_per_AU = 1.495978707E13;   (* number of cm in an AU    *)
      cm_per_km = 1.0E5;            (* number of cm in a km     *)
      cm_per_meter = 100.0;
      millibars_per_bar = 1000.0;
      Kelvin_Celcius_difference = 273.0;
      Grav_constant = 6.672E-8;     (* units of dyne cm2/gram2  *)
      greenhouse_effect_const = 0.93; (* affects inner radius.. *)
      Molar_gas_const = 8314.41;    (* units: g*m2/(sec2*K*mol) *)
      K = 50.0;                     (* K = gas/dust ratio       *)
      B = 1.2E-5;                   (* Used in Crit_mass calc   *)
      Dust_density_coeff = 2.0E-3;  (* A in Dole's paper        *)
      Alpha = 5;                    (* Used in density calcs    *)
      N = 3;                        (* Used in density calcs    *)
      j = 1.46E-19;                 (* Used in day-length calcs (cm2/sec2 g) *)
      incredibly_large_number = 9.9999E37;
(*  Now for a few molecular weights (used for RMS velocity calcs):     *)
(*  This table is from Dole's book "Habitable Planets for Man", p. 38  *)
      atomic_hydrogen = 1.0;           { H   }
      molecular_hydrogen = 2.0;        { H2  }
      helium = 4.0;                    { He  }
      atomic_nitrogen = 14.0;          { N   }
      atomic_oxygen = 16.0;            { O   }
      methane = 16.0;                  { CH4 }
      ammonia = 17.0;                  { NH3 }
      water_vapor = 18.0;              { H2O }
      neon = 20.2;                     { Ne  }
      molecular_nitrogen = 28.0;       { N2  }
      carbon_monoxide = 28.0;          { CO  }
      nitric_oxide = 30.0;             { NO  }
      molecular_oxygen = 32.0;         { O2  }
      hydrogen_sulphide = 34.1;        { H2S }
      argon = 39.9;                    { Ar  }
      carbon_dioxide = 44.0;           { CO2 }
      nitrous_oxide = 44.0;            { N2O }
      nitrogen_dioxide = 46.0;         { NO2 }
      ozone = 48.0;                    { O3  }
      sulphur_dioxide = 64.1;          { SO2 }
      sulphur_trioxide = 80.1;         { SO3 }
      krypton = 83.8;                  { Kr  }
      xenon = 131.3;                   { Xe  }

   TYPE Dust_pointer = ^Dust_bands;
        Dust_bands = Record
                        Inner_edge   : real;
                        Outer_edge   : real;
                        Dust_present : boolean;
                        Gas_present  : boolean;
                        Next_band    : Dust_pointer;
                     End;
        Planet_pointer = ^Planets;
(*	Moon_pointer = ^Moons;*)
        Planets = Record
                     a : real;               { semi-major axis of the orbit (in AU)}
                     e : real;               { eccentricity of the orbit         }
                     mass : real;            { mass (in solar masses)            }
                     gas_giant : boolean;    { TRUE if the planet is a gas giant }
                     orbit_zone : integer;   { the 'zone' of the planet          }
                     radius : real;          { equatorial radius (in km)         }
                     density : real;         { density (in g/cc)                 }
                     orbital_period : real;  { length of the local year (days)   }
                     day : real;             { length of the local day (hours)   }
                     resonant_period : boolean; { TRUE if in resonant rotation   }
                     axial_tilt : integer;   { units of degrees                  }
                     escape_velocity : real; { units of cm/sec                   }
                     surface_accel : real;   { units of cm/sec2                  }
                     surface_grav : real;    { units of Earth gravities          }
                     RMS_velocity : real;    { units of cm/sec                   }
                     molecule_weight : real; { smallest molecular weight retained}
                     volatile_gas_inventory : real;
                     surface_pressure : real;{ units of millibars (mb)           }
                     greenhouse_effect : boolean; { runaway greenhouse effect?   }
                     boil_point : real;      { the boiling point of water (Kelvin)}
                     albedo : real;          { albedo of the planet              }
                     surface_temp : real;    { surface temperature in Kelvin     }
                     hydrosphere : real;     { fraction of surface covered       }
                     cloud_cover : real;     { fraction of surface covered       }
                     ice_cover : real;
{                     atmosphere : integer;   { 9 different types numbered 0 -> 8 }
                     first_moon : planet_pointer;
                     next_planet : planet_pointer;
                  End;
(*        Moons = Record
		   a : real;
		   e : real;
		   mass : real;
		   radius : real;
		   density : real;
		   orbital_period : real;
		   day : real;
		   resonant_period : boolean;
		   escape_velocity : real;
                   surface_accel : real;
		   surface_grav : real;
		   RMS_velocity : real;
		   molecule_weight : real;
		   albedo : real;
                   next_moon : moon_pointer;
		End;*)

(*  These are all of the global variables used during accretion:  *)
   VAR Dust_head : Dust_pointer;
       Planet_head : planet_pointer;
       Dust_left : boolean;

   VAR stellar_mass_ratio, stellar_luminosity_ratio, Main_seq_life,
          age, r_ecosphere, r_greenhouse : real;
       radians_per_rotation : real;
       spin_resonance : boolean;

{$I utils.pas}
{$I accrete.pas}
{$I display.pas}
{$I enviro.pas}

   Procedure init;
      Begin
         randomize;
      End;

   Procedure Generate_stellar_system;
      VAR planet : planet_pointer;
      Begin
         radians_per_rotation:= 2 * pi;
         Stellar_mass_ratio:= Random_number (0.6, 1.3);
         Stellar_luminosity_ratio:= luminosity (stellar_mass_ratio);
         planet := Distribute_planetary_masses (Stellar_mass_ratio, Stellar_luminosity_ratio,
		0.0, Stellar_dust_limit(Stellar_mass_ratio));
         Main_seq_life:= 1.0E10*(stellar_mass_ratio / stellar_luminosity_ratio);
         If (Main_seq_life >= 6E9)
            then Age:= random_number (1E9, 6E9)
            else Age:= random_number (1E9, main_seq_life);
         R_ecosphere:= Sqrt(stellar_luminosity_ratio);
         R_greenhouse:= R_ecosphere * greenhouse_effect_const;
         while (planet <> nil)
          do begin
(*		planet^.first_moon:= Distribute_moon_masses (planet^.mass,
			Stellar_luminosity_ratio, planet^.e,
			0.0, planet_dust_limit(planet^.mass));*)
                planet^.orbit_zone:= Orbital_zone (planet^.a);
                if (planet^.gas_giant)
                   then begin
                           planet^.density:= empirical_density (planet^.mass, planet^.a,
                                                              planet^.gas_giant);
                           planet^.radius:= volume_radius (planet^.mass, planet^.density);
                        end
                   else begin
                           planet^.radius:= Kothari_radius (planet^.mass, planet^.a,
                                           planet^.gas_giant, planet^.orbit_zone);
                           planet^.density:= Volume_density (planet^.mass, planet^.radius);
                        end;
                planet^.orbital_period:= Period (planet^.a, planet^.mass, Stellar_mass_ratio);
                planet^.day:= Day_length (planet^.mass, planet^.radius, planet^.orbital_period,
                                         planet^.e, planet^.gas_giant);
                planet^.resonant_period:= spin_resonance;
                planet^.axial_tilt:= inclination(planet^.a);
                planet^.escape_velocity:= Escape_vel (planet^.mass, planet^.radius);
                planet^.surface_accel:= Acceleration (planet^.mass, planet^.radius);
                planet^.RMS_velocity:= RMS_vel (molecular_nitrogen, planet^.a);
                planet^.molecule_weight:= Molecule_limit(planet^.a, planet^.mass,
                                         planet^.radius);
                if (planet^.gas_giant)
                   then begin
                           planet^.surface_grav:= incredibly_large_number;
                           planet^.greenhouse_effect:= false;
                           planet^.volatile_gas_inventory:= incredibly_large_number;
                           planet^.surface_pressure:= incredibly_large_number;
                           planet^.boil_point:= incredibly_large_number;
                           planet^.hydrosphere:= incredibly_large_number;
                           planet^.albedo:= about(gas_giant_albedo, 0.1);
                           planet^.surface_temp:= incredibly_large_number;
                        end
                   else begin
                           planet^.surface_grav:= gravity(planet^.surface_accel);
                           planet^.greenhouse_effect:= greenhouse(planet^.orbit_zone, planet^.a,
                                                      R_greenhouse);
                           planet^.volatile_gas_inventory:= Vol_Inventory(planet^.mass,
                                 planet^.escape_velocity, planet^.RMS_velocity,
                                 stellar_mass_ratio, planet^.orbit_zone,
                                 planet^.greenhouse_effect);
                           planet^.surface_pressure:= Pressure(planet^.volatile_gas_inventory,
                                 planet^.radius, planet^.surface_grav);
                           If (planet^.surface_pressure = 0.0)
                              then planet^.boil_point:= 0.0
                              else planet^.boil_point:= boiling_point(planet^.surface_pressure);
                           determine_albedo_and_surface_temp(planet);
                        end;
{                planet^.atmosphere:= Atmosphere_type(planet^.surface_pressure, age,
                                    planet^.gas_giant);}
                planet:= planet^.next_planet;
             end;
         Display_system;
      End;

   Begin
      Init;
      Generate_Stellar_system;
   End.

