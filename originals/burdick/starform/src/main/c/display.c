        #include        <stdio.h>
        #include        <math.h>
        
        #ifdef BSD
        #include        <strings.h>
        #else
        #include        <string.h>
        #endif
        
        #ifdef MSDOS
        #include        <stddef.h>
        #include        <malloc.h>
        #include        <stdlib.h>
        #include        <float.h>
        #endif
        
        #include        "structs.h"
        #include        "const.h"
        #include        "config.h"
        
        #define        MAX_EXP_DIGS        3
        #define        MAX_MAN_DIGS        20
        
        extern int flag_graphics, flag_lisp;
        
        #ifdef MOONS
        extern int flag_moons;
        #endif
        
        char OP[] = "(";
        char CP[] = ")";
        
        
        char *engineer_notation(d, p)
        double d;
        int p;
        {
                static char mansign;
                static char expsign;
                static char output[1+MAX_MAN_DIGS+1+1+MAX_EXP_DIGS+1];
                double mantissa;
                int exponent;
        
                mansign = '+';
                expsign = '+';
                if (p > MAX_MAN_DIGS)
                        p = MAX_MAN_DIGS;
                if (p < 3)
                        p = 3;
                --p;
                if (d < 0.0)
                {
                        mansign = '-';
                        d = -d;
                }
                if (d == 0.0)
                {
                        exponent = 0;
                        mantissa = 0;
                }
                else
                {
                        exponent = log10(d);
                        if (exponent == 0 && d < 1.0)        /* log10 sometimes lies */
                        {
                                --exponent;
                                --p;
                        }
                        if (exponent < 0)
                        {
                                expsign = '-';
                                --exponent;
                        }
                        mantissa = d / pow(10.0, (double) exponent);
                        if (exponent < 0)
                                exponent = -exponent;
                        while ((exponent % 3) != 0)
                        {
                                mantissa *= 10.0;
                                p--;
                                if (expsign == '-')
                                        ++exponent;
                                else
                                        --exponent;
                        }
                }
                sprintf(output, "%c%*.*lfe%c%*.*d", mansign, p, p, mantissa,
                        expsign, MAX_EXP_DIGS, MAX_EXP_DIGS, exponent);
                return (output);
        }
        
        void chart_system(sys)
        sys_pointer sys;
        {
        }
        
        void text_describe_system(sys)
        sys_pointer sys;
        {
             planet_pointer node1;
        #ifdef MOONS
             planet_pointer node2;
        #endif
             int counter1, counter2;
        
             printf("                         SYSTEM  CHARACTERISTICS\n");
             printf("Stellar mass: %4.2lf solar masses\n", sys->stell_mass_ratio);
             printf("Stellar luminosity: %4.2lf\n",sys->stell_luminosity_ratio);
             printf("Age: %5.3lf billion years  (%5.3lf billion left on main sequence)\n",
                     (sys->age /1.0E9),(sys->main_seq_life - sys->age) / 1.0E9);
             printf("Habitable ecosphere radius: %3.3lf AU\n",sys->r_ecosphere);
             printf("\n");
             printf("Planets present at:\n");
             for (node1=sys->inner_planet, counter1=1;
                  node1 != NULL;
                  node1=node1->next_planet, counter1++)
             {
                printf("%d\t%7.3lf \t AU\n", counter1, node1->a);
             }
             printf("\n\n\n");
             for (node1=sys->inner_planet, counter1=1;
                  node1 != NULL;
                  node1=node1->next_planet, counter1++)
             {
                  printf("Planet %d\t",counter1);
                  if (node1->gas_giant)
                       printf("*gas giant*\n");
                  else printf("\n");
                  if ((int)node1->day == (int)(node1->orb_period * 24.0))
                       printf("Planet is tidally locked with one face to star.\n");
                  if (node1->resonant_period)
                       printf("Planet's rotation is in a resonant spin lock with the star\n");
                  printf("   Distance from primary star:\t%5.3lf\tAU\n",node1->a);
                  printf("   Mass:\t\t\t%5.3lf\tEarth masses\n",node1->mass * SUN_MASS_IN_EARTH_MASSES);
                  if (!(node1->gas_giant))
                  {
                       printf("   Surface gravity:\t\t%4.2lf\tEarth gees\n",node1->surf_grav);
                       printf("   Surface pressure:\t\t%5.3lf\tEarth atmospheres",(node1->surf_pressure / 1000.0));
                       if ((node1->greenhouse_effect) && (node1->surf_pressure > 0.0))
                            printf("\tGREENHOUSE EFFECT\n");
                       else
                            printf("\n");
                       printf("   Surface temperature:\t\t%4.2lf\tdegrees Celcius\n",(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE));
                  }
                  printf("   Equatorial radius:\t\t%3.1lf\tKm\n",node1->radius);
                  printf("   Density:\t\t\t%5.3lf\tgrams/cc\n",node1->density);
                  printf("   Eccentricity of orbit:\t%5.3lf\n",node1->e);
                  printf("   Escape Velocity:\t\t%4.2lf\tKm/sec\n",node1->esc_velocity / CM_PER_KM);
                  printf("   Molecular weight retained:\t%4.2lf and above\n",node1->molec_weight);
                  printf("   Surface acceleration:\t%4.2lf\tcm/sec2\n",node1->surf_accel);
                  printf("   Axial tilt:\t\t\t%d\tdegrees\n",node1->axial_tilt);
                  printf("   Planetary albedo:\t\t%5.3lf\n",node1->albedo);
                  printf("   Length of year:\t\t%4.2lf\tdays\n",node1->orb_period);
                  printf("   Length of day:\t\t%4.2lf\thours\n",node1->day);
                  if (!(node1->gas_giant))
                  {
                       printf("   Boiling point of water:\t%3.1lf\tdegrees Celcius\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
                       printf("   Hydrosphere percentage:\t%4.2lf\n",(node1->hydrosphere * 100.0));
                       printf("   Cloud cover percentage:\t%4.2lf\n",(node1->cloud_cover * 100));
                       printf("   Ice cover percentage:\t%4.2lf\n",(node1->ice_cover * 100));
                  }
        #ifdef MOONS
                  if (flag_moons) {
                          printf("\tMOONS:\n");
                          printf("\t#\tmass\tdistance from planet\n");
                          printf("\t--------------------------------------\n");
                          for (node2=node1->first_moon, counter2=1;
                               node2 != NULL;
                               node2=node2->next_planet, counter2++)
                          {
                                  printf("\t%d\t%5.3lf\t%7.3lf AU\n", counter2, (node2->mass*SOLAR_MASS_IN_GRAMS/EARTH_MASS_IN_GRAMS), node2->a);
                          }
                  }
        #endif
                  printf("\n\n");
             }
        }
        
        void lisp_describe_system(sys)
        sys_pointer sys;
        {
                planet_pointer node1;
                int counter;
        
                printf("%splanetary-system\n", OP);
                printf(" %ssun\n", OP);
                printf("  %smass %s%s ; kg\n",
                        OP,
                        engineer_notation(sys->stell_mass_ratio * SOLAR_MASS_IN_GRAMS / 1000.0, 6),
                        CP);
                printf("  %sluminosity %s%s ; * SOL luminosity\n",
                        OP, engineer_notation(sys->stell_luminosity_ratio, 6), CP);
                printf("  %slifetime %s%s ; years\n",
                        OP, engineer_notation(sys->main_seq_life, 6), CP);
                printf("  %scurrent-age %s%s ; years\n",
                        OP, engineer_notation(sys->age, 6), CP);
                printf("  %secosphere-radius %s%s ; km\n",
                        OP, engineer_notation(sys->r_ecosphere * KM_PER_AU, 6), CP);
                printf(" %s\n", CP);
                for (node1=sys->inner_planet, counter=1;
                     node1 != NULL;
                     node1=node1->next_planet, counter++)
                {
                        printf(" %splanet ; #%d\n",
                                OP, counter);
                        printf("  ; boolean:\n");
                        printf("  %sis-gas-giant %d%s\n", OP, node1->gas_giant, CP);
                        printf("  ; orbital statistics:\n");
                        printf("  %smean-orbit-radius %s%s ; km\n",
                                OP, engineer_notation(node1->a * KM_PER_AU, 6), CP);
                        printf("  %sorbit-eccentricity %s%s\n",
                                OP, engineer_notation(node1->e, 6), CP);
                        printf("  %saxial-tilt %d%s ; degrees\n",
                                OP, node1->axial_tilt, CP);
                        printf("  %sorbital-period %s%s ; Earth days\n",
                                OP, engineer_notation(node1->orb_period, 6), CP);
                        printf("  %srotation-period %s%s ; Earth hours\n",
                                OP, engineer_notation(node1->day, 6), CP);
                        printf("  %sis-resonant %d%s\n", OP, node1->resonant_period, CP);
                        printf("  ; planetary measurements:\n");
                        printf("  %smass %s%s ; kg\n",
                                OP, engineer_notation(node1->mass * SOLAR_MASS_IN_GRAMS / 1000.0, 6), CP);
                        printf("  %sequatorial-radius %s%s ; km\n",
                                OP, engineer_notation(node1->radius, 6), CP);
                        printf("  %sdensity %s%s ; g/cm3\n",
                                OP, engineer_notation(node1->density, 6), CP);
                        printf("  ; planetary environment:\n");
                        printf("  %sescape-velocity %s%s ; km/sec\n",
                                OP, engineer_notation(node1->esc_velocity / CM_PER_KM, 6), CP);
                        printf("  %smin-molecular-weight-retained %s%s\n",
                                OP, engineer_notation(node1->molec_weight, 3), CP);
                        printf("  %ssurface-acceleration %s%s ; cm/sec2\n",
                                OP, engineer_notation(node1->surf_accel, 6), CP);
                        if (!node1->gas_giant)
                        {
                                printf("  %ssurface-gravity %s%s ; Earth gees\n",
                                        OP, engineer_notation(node1->surf_grav, 3), CP);
                                printf("  %sh2o-boils %s%s ; degrees celcius\n",
                                        OP,
                                        engineer_notation(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE, 3),
                                        CP);
                                printf("  %ssurface-pressure %s%s ; Earth atmospheres\n",
                                        OP, engineer_notation(node1->surf_pressure / 1000.0, 3), CP);
                                if (node1->greenhouse_effect && node1->surf_pressure > 0.0)
                                        printf("  %sgreenhouse 1%s\n", OP, CP);
                                else
                                        printf("  %sgreenhouse 0%s\n", OP, CP);
                                printf("  %ssurface-temperature %s%s ; degrees celcius\n",
                                        OP,
                                        engineer_notation(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE, 3),
                                        CP);
                                printf("  %shydrosphere %s%s\n",
                                        OP, engineer_notation(node1->hydrosphere, 3), CP);
                                printf("  %scloud-cover %s%s\n",
                                        OP, engineer_notation(node1->cloud_cover, 3), CP);
                                printf("  %sice-cover %s%s\n",
                                        OP, engineer_notation(node1->ice_cover, 3), CP);
                        }
                        printf("  %salbedo %s%s\n",
                                OP, engineer_notation(node1->albedo, 3), CP);
                        printf(" %s\n", CP);
                }
                printf("%s\n", CP);
        }
        
        void display_system(system)
        sys_pointer system;
        {
                if (flag_graphics)
                        chart_system(system);
                else if (flag_lisp)
                        lisp_describe_system(system);
                else
                        text_describe_system(system);
        }
        
