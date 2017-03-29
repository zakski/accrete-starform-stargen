
The program is one I wrote based on Dole's original paper in _Icarus_ in the
late '60s.  I'm afraid I don't have it available in machine readable form here
(it lives on my PC at home, but my e-mail address is at work) : this is partly
to avoid any contention about whether it is company property as written on
their equipment...

It appeared in the gaming magazine _White Dwarf_ issue 57 (which is about 9
years ago now & probably isn't much help) written in Basic.

The algorithm is roughly

Over cells at 0.1 AU separation up to about 50 AU, representing rings of
material in the protoplanetary disk, set up inital gas & dust densities

Introduce a small particle which will  accrete all the material whose orbit it
crosses + band of width (apse length)*(planet mass/star mass)**0.25 on either
side.  If the mass is large enough to hold helium, accrete the gas too.  keep
iterating this until the mass stabilises.

Add another particle.  If two particle orbits overlap in radius, then collide
them, conserving angular momentum & let the accumulation accrete more material
until it stabilises.

Continue until the dust is exhausted.

Unfortunately I don't have the magic numbers to hand.  Since this has
caused some interest, I'll look the code out.