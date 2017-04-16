#include "system.h"

int dust_bands::dustAvailable(double inside_range, double outside_range)
{
	dust_bands* current_dust_band;
	int dust_here;

	current_dust_band = this;
//	current_dust_band = dust_head;
	while ((current_dust_band != NULL) && (current_dust_band->outerEdge < inside_range))
		current_dust_band = current_dust_band->next_band;

	dust_here=(current_dust_band==NULL) ? FALSE : (current_dust_band->isDustPresent);

	while ((current_dust_band != NULL)
		&& (current_dust_band->innerEdge < outside_range))
	{
		dust_here = dust_here || current_dust_band->isDustPresent;
		current_dust_band = current_dust_band->next_band;
	}

	return(dust_here);
}