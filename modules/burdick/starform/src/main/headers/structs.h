typedef struct dust_record  *dust_pointer;
typedef struct planets_record  *planet_pointer;
typedef struct sys_record *sys_pointer;

typedef struct sys_record {
    double age;
    double stell_mass_ratio;
    double stell_luminosity_ratio;
    double main_seq_life;
    double r_ecosphere;
    double r_greenhouse;
    planet_pointer inner_planet;
} system;

typedef struct planets_record {
    double a;                        /* semi-major axis of the orbit (in AU)*/
    double e;                        /* eccentricity of the orbit             */
    double mass;                /* mass (in solar masses)             */
    int gas_giant;                /* TRUE if the planet is a gas giant */
    int orbit_zone;             /* the 'zone' of the planet          */
    double radius;                /* equatorial radius (in km)             */
    double density;                /* density (in g/cc)                     */
    double orb_period;           /* length of the local year (days)   */
    double day;                        /* length of the local day (hours)   */
    int resonant_period;        /* TRUE if in resonant rotation   */
    int axial_tilt;                /* units of degrees                     */
    double esc_velocity;        /* units of cm/sec                     */
    double surf_accel;          /* units of cm/sec2                     */
    double surf_grav;           /* units of Earth gravities             */
    double rms_velocity;        /* units of cm/sec                     */
    double molec_weight;        /* smallest molecular weight retained*/
    double volatile_gas_inventory;
    double surf_pressure;        /* units of millibars (mb)             */
    int greenhouse_effect;        /* runaway greenhouse effect?        */
    double boil_point;                /* the boiling point of water (Kelvin)*/
    double albedo;                /* albedo of the planet                     */
    double surf_temp;           /* surface temperature in Kelvin     */
    double hydrosphere;                /* fraction of surface covered             */
    double cloud_cover;                /* fraction of surface covered             */
    double ice_cover;                /* fraction of surface covered             */
#ifdef MOONS
    planet_pointer first_moon;
#endif
    planet_pointer next_planet;
    } planets;


typedef struct dust_record {
          double inner_edge;
          double outer_edge;
          int dust_present;
          int gas_present;
          dust_pointer next_band;
     } dust;

