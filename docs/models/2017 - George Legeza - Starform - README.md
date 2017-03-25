# Starform.NET
Starform.NET is an effort to port the Accrete/Starform/StarGen solar system generator to C# and .NET. Starform.NET is little more than a naive port of Jim Burrows' StarGen in its current form, but the ultimate goal is to create an accessible and useful tool for game developers, sci-fi writers, and anyone else who might have a need to quickly generate interesting planets and star systems.

## Just a Dash of Science
The original inspiration of the Accrete program (at least as far as I can tell) is the 1970 paper *Formation of Planetary Systems by Aggregation: A Computer Simulation* by Stephen H. Dole (Stephen H. Dole, Icarus, 13 494-509). A variety of authors have implemented the original simulation described by Dole in that paper, and many of the versions available online have expanded on it as well. 

Of course, science has moved on in the intervening years and the model described by Dole is much less complex than our current understanding of how stellar systems are formed. What this means in practical terms is that Starform.NET's output will hopefully be scientifically *plausible*, but far from scientifically *accurate*. The underlying model shouldn't be considered anything more than a convenient method of generating reasonable and interesting output.

## Long Term Plans
Since I'm far from being an expert (or even knowledgeable) on the topic of stellar evolution, I have no plans to improve the accretion model or mess around too much with the guts of the simulation. Instead, Starform.NET's long term development will focus on creating more usable output, better annotations for generated planets, and, eventually, an easier-to-use API to allow Starform.NET to be used as a library in other programs.

See the changes.txt file for an up-to-date list of current and planned updates and changes.

## Credits
Aside from porting the code from C to C#, none of the work on the accretion simulation is mine. Starform.NET's core is a direct port of [Jim Burrows' StarGen](http://www.eldacur.com/~brons/NerdCorner/StarGen/StarGen.html). The original readme and credits from that version are included in this repository as StarGen-ReadMe.txt and StarGen-Credits.txt. The StarGen-Credits.txt file contains a more complete history of all of the authors who have contributed to Accrete/Starform/StarGen as well as a bibliography for the papers and books used to design it.

The planet sprites used in the output are Master484's planet sprite set from [OpenGameArt.org](http://opengameart.org/content/pixel-planets).
