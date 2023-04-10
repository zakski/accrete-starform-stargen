        #include        <stdio.h>
        #include        <math.h>
        #include        <sys/types.h>
        #include        <sys/timeb.h>
        
        #ifdef MSDOS
        #include        <stddef.h>
        #include        <malloc.h>
        #include        <stdlib.h>
        #include        <float.h>
        #endif
        
        #include        "const.h"
        #include        "structs.h"
        #include        "config.h"
        
        /*  These are all of the global variables used during accretion:  */
        system sys;
        
        unsigned flag_seed=FALSE;
        unsigned flag_verbose=FALSE;
        
        int flag_lisp = FALSE;
        int flag_graphics = FALSE;
        int resonance;
        
        #ifdef MOONS
        int flag_moons = FALSE;
        #endif
        
        /* externals from C library not elsewhere declared: */
        extern void srand();
        
        extern double random_number();
        extern double luminosity();
        extern double stell_dust_limit();
        extern double moon_dust_limit();
        extern planet_pointer dist_planetary_masses();
        extern int orb_zone();
        extern double empirical_density();
        extern double volume_density();
        extern double volume_radius();
        extern double kothari_radius();
        extern double period();
        extern double day_length();
        extern int inclination();
        extern double escape_vel();
        extern double accel();
        extern double rms_vel();
        extern double molecule_limit();
        extern double about();
        extern int grnhouse();
        extern double gravity();
        extern double vol_inventory();
        extern double pressure();
        extern double boiling_point();
        
        #ifdef MOONS
        extern planet_pointer dist_moon_masses();
        #endif
        
        
        void init()
        {
                struct timeb grap;
                unsigned seed;
        
                if (flag_seed)
                        seed = flag_seed;
                else {
                        ftime(&grap);
                        seed = (unsigned)((grap.time%100000)+grap.millitm);
                }
                (void)srand(seed);
                if (flag_lisp)
                        printf("(Accrete %s) ; seed: %u\n", "3.1", seed);
                else
                        printf("Accrete - V%s; seed= %u\n", "3.1", seed);
        }
        
        void generate_stellar_system()
        {
             planet_pointer planet;
             double dust_limit;
        
        #ifdef MOONS
                planet_pointer moon;
        #endif
        
             sys.stell_mass_ratio = random_number(0.6,1.3);
             sys.stell_luminosity_ratio = luminosity(sys.stell_mass_ratio);
             dust_limit = stell_dust_limit(sys.stell_mass_ratio);
             sys.inner_planet = dist_planetary_masses(sys.stell_mass_ratio,sys.stell_luminosity_ratio,0.0,dust_limit);
             sys.main_seq_life = 1.0E10 * (sys.stell_mass_ratio / sys.stell_luminosity_ratio);
             if ((sys.main_seq_life >= 6.0E9))
                  sys.age = random_number(1.0E9,6.0E9);
             else
                  sys.age = random_number(1.0E9,sys.main_seq_life);
             sys.r_ecosphere = sqrt(sys.stell_luminosity_ratio);
             sys.r_greenhouse = sys.r_ecosphere * GREENHOUSE_EFFECT_CONST;
             for (planet=sys.inner_planet; planet != NULL; planet = planet->next_planet)
             {
        #ifdef MOONS
                  if (flag_moons) {
                          dust_limit = moon_dust_limit(planet->mass, planet->a);
                          planet->first_moon = dist_moon_masses (planet->mass,
                                    sys.stell_luminosity_ratio,
                                    0.0, dust_limit);
                  }
        #endif
                  planet->orbit_zone = orb_zone(planet->a, sys.stell_luminosity_ratio);
                  if (planet->gas_giant)
                  {
                       planet->density = empirical_density(planet->mass,planet->a,planet->gas_giant, sys.r_ecosphere);
                       planet->radius = volume_radius(planet->mass,planet->density);
                  }
                  else
                  {
                       planet->radius = kothari_radius(planet->mass,planet->gas_giant,planet->orbit_zone);
                       planet->density = volume_density(planet->mass,planet->radius);
                  }
                  planet->orb_period = period(planet->a,planet->mass,sys.stell_mass_ratio);
                  planet->day = day_length(planet->mass,planet->radius,planet->e,
                                           planet->density, planet->a,
                                           planet->orb_period,planet->gas_giant,
                                           sys.stell_mass_ratio, sys.age);
                  planet->resonant_period = resonance;
                  planet->axial_tilt = inclination(planet->a);
                  planet->esc_velocity = escape_vel(planet->mass,planet->radius);
                  planet->surf_accel = accel(planet->mass,planet->radius);
                  planet->rms_velocity = rms_vel(MOL_NITROGEN,planet->a);
                  planet->molec_weight = molecule_limit(planet->mass,planet->radius);
                  if ((planet->gas_giant))
                  {
                       planet->surf_grav = INCREDIBLY_LARGE_NUMBER;
                       planet->greenhouse_effect = FALSE;
                       planet->volatile_gas_inventory = INCREDIBLY_LARGE_NUMBER;
                       planet->surf_pressure = INCREDIBLY_LARGE_NUMBER;
                       planet->boil_point = INCREDIBLY_LARGE_NUMBER;
                       planet->hydrosphere = INCREDIBLY_LARGE_NUMBER;
                       planet->albedo = about(GAS_GIANT_ALBEDO,0.1);
                       planet->surf_temp = INCREDIBLY_LARGE_NUMBER;
                  }
                  else
                  {
                       planet->surf_grav = gravity(planet->surf_accel);
                       planet->greenhouse_effect = grnhouse(planet->orbit_zone,planet->a,sys.r_greenhouse);
                       planet->volatile_gas_inventory = vol_inventory(planet->mass,planet->esc_velocity,planet->rms_velocity,sys.stell_mass_ratio,planet->orbit_zone,planet->greenhouse_effect);
                       planet->surf_pressure = pressure(planet->volatile_gas_inventory,planet->radius,planet->surf_grav);
                       if ((planet->surf_pressure == 0.0))
                            planet->boil_point = 0.0;
                       else
                            planet->boil_point = boiling_point(planet->surf_pressure);
                       iterate_surface_temp(&(planet), sys.r_ecosphere);
                  }
        #ifdef MOONS
             for (moon=planet->first_moon; moon != NULL; moon = moon->next_planet)
             {
             }
        #endif
           }
        }
        
        void
        usage (progname)
        char *progname;
        {
        
        #ifdef MOONS
                fprintf(stderr, "%s: Usage: %s [-l] [-g] [-m] [-s#] [-v#]\n",
                        progname, progname);
        #else
                fprintf(stderr, "%s: Usage: %s [-l] [-g] [-s#] [-v#]\n",
                        progname, progname);
        #endif
                fprintf(stderr, "\t -l = output lisp format\n");
                fprintf(stderr, "\t -g = output graphics format (unimplemented right now)\n");
        #ifdef MOONS
                fprintf(stderr, "\t -m = generate moons for each planet\n");
        #endif
                fprintf(stderr, "\t -s# = use # as the seed for the random number generator\n");
                fprintf(stderr, "\t -v# = set the verbosity level to # (default is 0)\n");
                exit (1);
        }
        
        main (argc, argv)
        int argc;
        char *argv[];
        {
                char *c, *progname;
                int skip;
        
                progname = argv[0];
                while (--argc > 0) {
                        if ((*++argv)[0] != '-')
                                usage(progname);
                        for (c = argv[0]+1, skip=FALSE; (*c != '\0') && (!(skip)); c++)
                                switch (*c)
                                {
                                case 'l':        /* set lisp output */
                                        ++flag_lisp;
                                        break;
                                case 'g':        /* display graphically */
                                        ++flag_graphics;
                                        break;
        #ifdef MOONS
                                case 'm':        /* generate moons for planets */
                                        ++flag_moons;
                                        break;
        #endif
                                case 's':        /* set random seed */
                                        flag_seed = (unsigned) atoi(&(*++c));
                                        skip = TRUE;
                                        break;
                                case 'v':        /* increment verbosity */
                                        flag_verbose = (unsigned) atoi(&(*++c));
                                        skip = TRUE;
                                        break;
                                default:
                                case '?':
                                        usage(progname);
                                }
                }
                init();
                generate_stellar_system();
                display_system(&sys);
                return(0);
        }
        