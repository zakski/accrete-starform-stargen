(*----------------------------------------------------------------------*)
(* Copywrite (C) 1988 Matthew Burdick					*)
(* This code may be freely distributed.					*)
(*----------------------------------------------------------------------*)
   Procedure Display_system;
      VAR node1 : planet_pointer;
          counter : integer;
          word : string[10];
      Begin
{         sound (2000);}
{         ClrScr;}
         Writeln ('                         SYSTEM  CHARACTERISTICS');
         Str(stellar_mass_ratio:4:2,word);
         writeln ('Mass of central star (in solar masses): ',word);
         Str(stellar_luminosity_ratio:5:2,word);
         writeln ('Luminosity of central star (relative to the sun): ', word);
         str(main_seq_life/1.0E6:10:3,word);
         writeln ('Total main sequence lifetime (in million yrs): ', word);
         str(age/1.0E6:10:3,word);
         writeln ('Current age of stellar system (in million yrs): ',word);
         str(r_ecosphere:3:3,word);
         Writeln ('Radius of habitable ecosphere (AU): ',word);
{         nosound;}
{         repeat until keypressed;}
         node1:= planet_head;
         counter:= 1;
         while (node1 <> nil)
          do begin
                writeln ('Planet #',counter,':');
                If (node1^.gas_giant)
                   then writeln ('Gas giant...');
                If (node1^.resonant_period)
                   then writeln ('In resonant period with primary.');
                str(node1^.a:7:3,word);
                Writeln ('   Distance from primary star (in A.U.): ',word);
                str(node1^.e:5:3,word);
                writeln ('   Eccentricity of orbit: ',word);
                str(node1^.mass*Earth_masses_per_solar_mass:7:3,word);
                writeln ('   Mass (in Earth masses): ',word);
                str(node1^.radius:10:1,word);
                writeln ('   Equatorial radius (in Km): ',word);
                str(node1^.density:6:3,word);
                writeln ('   Density (in g/cc): ',word);
                str(node1^.escape_velocity/cm_per_km:5:2, word);
                writeln ('   Escape Velocity (in km/sec): ',word);
                str(node1^.molecule_weight:5:2, word);
                writeln ('   Smallest molecular weight retained: ',word);
                str(node1^.surface_accel:6:2, word);
                writeln ('   Surface acceleration (in cm/sec2): ',word);
                If not(node1^.gas_giant)
                   then begin
                           str(node1^.surface_grav:5:2, word);
                           writeln ('   Surface Gravity (in Earth gees): ',word);
                           str((node1^.boil_point - Kelvin_Celcius_difference):4:1, word);
                           writeln ('   Boiling point of water (celcius): ',word);
                           str((node1^.surface_pressure / 1000.0):5:3, word);
                           write ('   Surface Pressure (in atmospheres): ',word);
                           if ((node1^.greenhouse_effect) and (node1^.surface_pressure > 0.0))
                              then writeln( '     RUNAWAY GREENHOUSE EFFECT')
                              else writeln(' ');
                           str((node1^.surface_temp - Kelvin_Celcius_difference):4:2, word);
                           writeln ('   Surface temperature (Celcius): ',word);
                           str((node1^.hydrosphere * 100.0):6:2, word);
                           writeln ('   Hydrosphere percentage: ',word);
                           str((node1^.cloud_cover * 100):6:2, word);
                           writeln ('   Cloud cover percentage: ',word);
                           str((node1^.ice_cover * 100):6:2, word);
                           writeln ('   Ice cover percentage: ',word);
                        end;
                writeln ('   Axial tilt (in degrees): ',node1^.axial_tilt);
                str(node1^.albedo:4:3, word);
                writeln ('   Planetary albedo: ',word);
{                CASE (node1^.atmosphere) of
                   0 : writeln ( '   No appreciable atmosphere.');
                   1 : writeln ( '   Nitrogen/Oxygen atmosphere.');
                   2 : writeln ( '   Carbon dioxide/Nitrogen atmosphere with trace elements.');
                   3 : writeln ( '   Nitrogen and Hydrocarbon atmosphere.');
                   4 : writeln ( '   Methane and Nitrogen atmosphere.');
                   5 : writeln ( '   Nitrogen/Carbon dioxide/Methane atmosphere.');
                   6 : writeln ( '   Highly oxidised Sulphur/Nitrogen dioxide atmosphere.');
                   7 : writeln ( '   Helium and sublimated frozen gasses atmosphere.');
                   8 : writeln ( '   Gas giant atmosphere.');
                end;}
                str(node1^.orbital_period:7:2, word);
                writeln ('   Length of year (in days): ',word);
                str(node1^.day:7:2, word);
                writeln ('   Length of day (in hours): ',word);

                counter:= counter + 1;
                node1:= node1^.next_planet;
             end;
      End;

