#ifndef STRUCTS
#define	STRUCTS

typedef struct planets_record  *planet_pointer;

typedef struct planets_record {
    double a;			/* semi-major axis of the orbit (in AU)*/
    double e;			/* eccentricity of the orbit	     */
    double mass;		/* mass (in solar masses)	     */
    int gas_giant;		/* TRUE if the planet is a gas giant */
    int orbit_zone;             /* the 'zone' of the planet          */
    double radius;		/* equatorial radius (in km)	     */
    double density;		/* density (in g/cc)		     */
    double orbital_period;	/* length of the local year (days)   */
    double day;			/* length of the local day (hours)   */
    int resonant_period;	/* TRUE if in resonant rotation   */
    int axial_tilt;		/* units of degrees		     */
    double escape_velocity;	/* units of cm/sec		     */
    double surface_accel;	/* units of cm/sec2		     */
    double surface_grav;	/* units of Earth gravities	     */
    double rms_velocity;	/* units of cm/sec		     */
    double molecule_weight;	/* smallest molecular weight retained*/
    double volatile_gas_inventory;
    double surface_pressure;	/* units of millibars (mb)	     */
    int greenhouse_effect;	/* runaway greenhouse effect?	*/
    double boil_point;		/* the boiling point of water (Kelvin)*/
    double albedo;		/* albedo of the planet		     */
    double surface_temp;	/* surface temperature in Kelvin     */
    double hydrosphere;		/* fraction of surface covered	     */
    double cloud_cover;		/* fraction of surface covered	     */
    double ice_cover;		/* fraction of surface covered	     */
    planet_pointer first_moon;
    planet_pointer next_planet;
} planets;

extern float anum;
extern planet_pointer planet_head;
extern double stellar_mass_ratio, stellar_luminosity_ratio, main_seq_life;
extern double age, r_ecosphere, r_greenhouse, radians_per_rotation;
extern int spin_resonance;

#endif