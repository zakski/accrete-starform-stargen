#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdbool.h>

typedef struct planet_s
{
  double      a;		/* semi-major axis of the orbit (in AU) */
  double      e;		/* eccentricity of the orbit         */
  double      mass;		/* mass (in solar masses)            */
  bool        gas_giant;	/* true if the planet is a gas giant */
  int         orbit_zone;	/* the 'zone' of the planet          */
  double      radius;		/* equatorial radius (in km)         */
  double      density;		/* density (in g/cc)                 */
  double      orb_period;	/* length of the local year (days)   */
  double      day;		/* length of the local day (hours)   */
  bool        resonant_period;	/* true if in resonant rotation      */
  int         axial_tilt;	/* units of degrees                  */
  double      esc_velocity;	/* units of cm/sec                   */
  double      surf_accel;	/* units of cm/sec2                  */
  double      surf_grav;	/* units of Earth gravities          */
  double      rms_velocity;	/* units of cm/sec                   */
  double      molec_weight;	/* smallest molecular weight retained */
  double      volatile_gas_inventory;
  double      surf_pressure;	/* units of millibars (mb)           */
  int         greenhouse_effect;	/* runaway greenhouse effect?   */
  double      boil_point;	/* the boiling point of water (Kelvin) */
  double      albedo;		/* albedo of the planet              */
  double      surf_temp;	/* surface temperature in Kelvin     */
  double      hydrosphere;	/* fraction of surface covered       */
  double      cloud_cover;	/* fraction of surface covered       */
  double      ice_cover;	/* fraction of surface covered       */
  struct planet_s* first_moon;
  struct planet_s* next_planet;
} planet;

typedef struct 
{
  bool make_moon;
  bool verbose;
} flags;

#endif
