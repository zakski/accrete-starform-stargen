void display_system()
{
     planet_pointer node1;
     int counter;
     char word[(10)+1];
     
     printf("                         SYSTEM  CHARACTERISTICS\n");
     printf("Mass of central star (in solar masses): %4.2lf\n", stellar_mass_ratio);
     printf("Luminosity of central star (relative to the sun): %5.2lf\n",stellar_luminosity_ratio);
     printf("Total main sequence lifetime (in million yrs): %10.3lf\n", (main_seq_life / 1.0E6));
     printf("Current age of stellar system (in million yrs): %10.3lf\n",(age / 1.0E6));
     printf("Radius of habitable ecosphere (AU): %3.3lf\n",r_ecosphere);
     node1 = planet_head;
     counter = 1;
     while (node1 != NULL)
     {
          printf("Planet #%d:\n",counter);
          if (node1->gas_giant)
               printf("Gas giant...\n");
          if (node1->resonant_period)
               printf("In resonant period with primary.\n");
          printf("   Distance from primary star (in A.U.): %7.3lf\n",node1->a);
          printf("   Eccentricity of orbit: %5.3lf\n",node1->e);
          printf("   Mass (in Earth masses): %7.3lf\n",node1->mass * EARTH_MASSES_PER_SOLAR_MASS);
          printf("   Equatorial radius (in Km): %10.1lf\n",node1->radius);
          printf("   Density (in g/cc): %6.3lf\n",node1->density);
          printf("   Escape Velocity (in km/sec): %5.2lf\n",node1->escape_velocity / CM_PER_KM);
          printf("   Smallest molecular weight retained: %5.2lf\n",node1->molecule_weight);
          printf("   Surface acceleration (in cm/sec2): %6.2lf\n",node1->surface_accel);
          if (!(node1->gas_giant))
          {
               printf("   Surface Gravity (in Earth gees): %5.2lf\n",node1->surface_grav);
               printf("   Boiling point of water (celcius): %4.1lf\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
               printf("   Surface Pressure (in atmospheres): %5.3lf",(node1->surface_pressure / 1000.0));
               if ((node1->greenhouse_effect) && (node1->surface_pressure > 0.0))
                    printf("     RUNAWAY GREENHOUSE EFFECT\n");
               else
                    printf("\n");
               printf("   Surface temperature (Celcius): %4.2lf\n",(node1->surface_temp - KELVIN_CELCIUS_DIFFERENCE));
               printf("   Hydrosphere percentage: %6.2lf\n",(node1->hydrosphere * 100.0));
               printf("   Cloud cover percentage: %6.2lf\n",(node1->cloud_cover * 100));
               printf("   Ice cover percentage: %6.2lf\n",(node1->ice_cover * 100));
          }
          printf("   Axial tilt (in degrees): %d\n",node1->axial_tilt);
          printf("   Planetary albedo: %4.3lf\n",node1->albedo);
          printf("   Length of year (in days): %7.2lf\n",node1->orbital_period);
          printf("   Length of day (in hours): %7.2lf\n",node1->day);
          counter++;
          node1 = node1->next_planet;
     }
}
