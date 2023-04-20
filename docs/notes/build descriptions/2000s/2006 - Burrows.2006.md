# Stargen (C)

A starform version altered by Burrows with bits and pieces added and modified and borrowed from Ian Burrell, C. Burke 
and Chris Croughton. StarGen is based mostly on Burdick's, but has borrowed from the others, most notably Keris's.

## Basic Assumptions:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

- see [Keris' variant of Starform](/docs/notes/build descriptions/2000s/2000%20-%20Keris.2000.B.md).

## Features
- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

- see [Keris' variant of Starform](/docs/notes/build descriptions/2000s/2000%20-%20Keris.2000.B.md).

- numerous graphical options

- ability to pick a star to build a system for

- ability to set seed 

- ability to build n systems.

## Limitations:

- A lot more psuedo-scientific code that the best guess models that Dole and Fogg came up with.

### In Recreation:
- Source Code is complete.

## Compilation
Compiles.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/burrows.md) for the status on Burrows' latest code.

## Runtime Options
info based on ui page, [here](/http://fast-times.eldacur.com/StarGen/RunStarGen.html)

### Catalog
Your first choice of options is whether you want to use a real star (or set of stars) to build your system(s) around. In 
the top row there is a menu offering three Catalog options: None, Dole and SolStation. If you select None, then you can 
either specify the stellar mass to use, or leave it to StarGen to generate a random mass. On the other hand, if you 
choose either Dole or SolStation, then a second menu will appear, allowing you to choose stars from the corresponding 
catalog. This will also disable the ability to specify a stellar mass.

The Dole catalog consists of 15 stars listed by Stephen Dole in his book Habitable Planets for Man, upon which many 
elements of StarGen are based. These are the nearby stars that he suggested were most likely to have planets that could 
support human life. You can either choose an individual star from this catalog or generate a system for every star in 
the catalog.

So, suppose you want to create a setting for a game or science fiction story, or just want to explore the possibilities 
of life in the nearby universe. You might select Dole and All in the two menus in the top row. This will make -d appear 
in the text box at the bottom. Pressing the stargen button in the lower left is the same as issuing the command 
“stargen -d” in a command line environment. Try that now, remembering that you can get back to this page by using the 
Back button on your browser.

When you do so, this page should be replaced by one similar to the one shown in the picture to the right. The number and 
type of planets in each system will be different from the picture, but each system in the Dole catalog should be 
represented. Not only will the planets be different from the ones I generated for the picture, but if you come back to 
this page and issue the very same command, the results should be different from the results you got the first time. This
is fine if you are exploring the possibilities of StarGen and the Dole catalog, but if you are doing this to generate a 
game world or fictional setting, you will probably want to be able to come back to the same system. This is what the Set 
random number seed field is for.

### Set random number seed
In order to create the systems, StarGen uses a pseudo-random number generator, which is a function that produces a 
series of numbers that are not obviously related to each other. Since a mathematical formula is used, the sequence is 
the same each time it is calculated. The function actually takes one number and produces the next one in the 
sequence. You can specify the first number used for a system. If you don't, the program picks one based on the time of 
day in seconds.

So, say you want a reproducible set of systems. Select Dole and All again, this time put a number like 42 in the Set 
random number seed box. Press the stargen button. This should produce a set of systems that you can come back to again a
nd again. It is the equivalent of using the “stargen -d -s42”.

### Stellar Mass
If you have not chosen a Catalog, you can instead enter a Specific Stellar Mass to be used for all the stars you 
generate. Please note that stellar mass in StarGen is limited to the range from 0.2 to 1.5 solar masses. This is because 
of the assumptions made years ago by the folks at the Rand Corporation who constructed the original model. They were 
interested in understanding the possible distribution of habitable planets among the stars. Because of this, they ruled 
out stars that are two large, which will not have a stable temperature long enough for life to evolve and stars that are 
two small and so will have a habitable zone so close to the star that the planet's rotation will be slowed to a stop.

There is a second limitation regarding mass inherent in the basic StarGen model. The way StarGen creates a solar system
is by simulating the formation of planets in an "accretion disc", a ring of gas and dust thought to surround newly
formed stars. The model that the Accrete program upon which StarGen is based generates the initial disk based uses to 
initially distribute the mass around a star results in a disk that seldom generates large enough planets close enough in 
to very small stars to be within the habitable zone. As a result, I have never seen a habitable planet generated around
a star with a mass of less than about .63 solar masses.

I have considered raising the 0.2 solar mass limitation, but I am considering changes to StarGen that might allow 
suitable planets to show up around these smaller stars. The observations of actual extra-solar planets resulted in the surprising discovery that gas giants are often see far closer to their stars than previous theory or StarGen's model would allow. One possibility that has been suggested is that these planets formed further out but had their orbits disrupted, resulting in them falling to a lower orbit. It I put logic in to simulate that, suitable earth-sized planets may migrate close enough to these smaller stars. Until then masses in the 0.2 to 0.625 range are probably not useful.

### Atmosphere Model
If you want a little more detail to flesh the planets in your setting out, you could try adding in the atmosphere 
model. (Technically, the model is still "experimental", but it has been a feature for years and should not go away, 
though it may be changed. No need to hesitate to use it.) This changes both the thumbnail display and the full planet 
descriptions. The thumbnails will include descriptions of whether the atmosphere is breathable or poisonous and so on.

In the main descriptions, it turns this:

Molecular weight retained 	5.2 and above 	N, O, CH4, NH3, H2O, Ne, N2, CO...

into this:

Molecular weight retained 	5.2 and above 	N, O, CH4, NH3, H2O, Ne, N2, CO...
Nitrogen  	87.8%  	1602 mb  	(ipp: 1547) 	 
Oxygen  	11.1%  	202 mb  	(ipp: 195) 	 
Argon  	1.0%  	19 mb  	(ipp: 18)

The presence of the Inspired Partial Pressure figure allows StarGen to make some judgments about the breathability of 
the atmosphere.

### Repeat Count
Now suppose the game or story you want to create a setting for takes place in particular star system and you have some 
particular requirement, like a high-gravity world, or a cold one. This is what the Repeat count field is for. You can 
generate several versions of the same system and then choose the one you need. To see this, choose Dole and instead of 
All, pick a specific star from the second menu, say Tau Ceti. This will change the options listed in the text box at the
bottom to -D4 (4 is Tau Ceti. If you pick another star the number will be different.)

Hitting the stargen button at this point will generate just a single system. Adding a specific seed will make this 
reproducible, but if the result isn't what you're looking for you need to keep trying different seeds until you find
what you're looking for. Try this now: set the seed to 42, and the Repeat count to 10. This time you'll get 10 versions 
of Tau Ceti.

### Filter
The problem with just doing this is that if you're looking for a particular type of planet, you'll have to wade through
a lot of systems, most without habitable planets. To make this easier you can select Only systems with habitable worlds 
from the menu in the second line. This will change the command line options to “stargen -D4 -s42 -n10 -H”, and greatly 
reduce the number of systems generated. Try it. This should produce only 1 or 2 thumbnails. At the bottom of the page
will be a table summarizing the results. It will look something like this:

#### Summary
- Earthlike planets 	0
- Breathable atmospheres 	2
- Breathable g range 	0.78 - 0.81
- Terrestrial g range 	0.81 - 0.81
- Breathable pressure range 	303.55 - 365.29
- Breathable temp range 	-26.7 C - -7.9 C

Now that only habitable planets will be listed, you can afford to generate more systems without filling up the disk and 
the Thumbnails page with tons of useless systems. So, let's pump the count up to something like 200. This will give us 
options of “stargen -D4 -s42 -n200 -H”. Consulting the summary we can see that a small cool star like Tau Ceti tends to 
create smaller colder worlds. So, if we want larger or warmer planets we may want to use a different star, say Delta 
Pavonis:

#### Tau Ceti Systems
- -D4 -s42 -n200 -H Summary
- Earthlike planets 	2
- Breathable atmospheres 	43
- Breathable g range 	0.74 - 1.19
- Terrestrial g range 	0.74 - 1.09
- Breathable pressure range 	220.13 - 3375.09
- Breathable temp range 	-26.7 C - -1.0 C

#### Delta Pavonis Systems
-D11 -s42 -n200 -H Summary
Earthlike planets 	6
Breathable atmospheres 	63
Breathable g range 	0.75 - 1.29
Terrestrial g range 	0.75 - 1.29
Breathable pressure range 	201.39 - 4388.83
Breathable temp range 	-27.6 C - +5.2 C

Systems with two planets with breathable atmospheres are even more rare, but are dramatically quite interesting. We 
therefore have an option that is useful in searching for them. The Filter can also be set to Only systems with 2
habitable worlds. If you do so with the Catalog set to Dole	and All the random number seed to 5, the Repeat count to 100 
and check Only systems with 2 habitable worlds and optionally Use experimental atmosphere model (this last isn't 
required as both habitability filters imply the gas model) the options become "-d -s5 -n100 -g -2", and the results 
should look like this:

#### System 42 - Eta Cassiopeiae A
- 8 Planets (size proportional to Sqrt(Radius))
- Sun 	Rock 	Rock 	Terrestrial 	Terrestrial 	GasDwarf 	Jovian 	Sub-Jovian 	Jovian 	See
- Key
- #3 	Terrestrial: Low-G, Cold, Few clouds, Thin atmosphere (O2, N2 - breathable)
- #4 	Terrestrial: Cold, Few clouds, Thick atmosphere (N2, He, O2 - breathable)

Summary

- Earthlike planets 	42
- Breathable atmospheres 	259
- Breathable g range 	0.73 - 1.27
- Terrestrial g range 	0.73 - 1.27
- Breathable pressure range 	193.16 - 4275.93
- Breathable temp range 	-28.1 C - +8.1 C
- Breathable illumination range 	0.50 - 1.24
- Terrestrial illumination range 	0.50 - 1.24

As you can see, this has reduced more than 250 habitable systems to just the one that has at least 2 planets with 
breathable atmospheres according to the gas model. Notice that the system is part of a binary star system. I'm not 
entirely certain why, but this tends to be the case. Most systems with 2 habitable planets are in binary pairs. I think 
this is because the accretion disc is narrower and more even in thickness.

### Moons
This piece of code is the most experimental feature available from this page. It is incomplete, under active development 
and produces impossible results. It is accessible here at this point solely so that a couple of people who have 
collaborated with me on StarGen can view the output of my latest attempt at moons. This option is under development and 
may change radically without notice. Regard it as an undocumented alpha test feature.

### CSV File Output
This option causes the output to be written to a Comma Separated Values (CSV) text file that can be loaded into a 
spreadsheet such as Microsoft's Excel, or a database program. All of StarGen's data for each planet and moon is 
dumped. This option is intended for use by a couple of people who are using StarGen data as input into their own 
simulations.

### SVG Graphic File Output
This option causes the thumbnail graphics to be replaced by a black and white Scalable Vector Graphics (SVG) file that 
somewhat resembles the diagrams that were output by the FORTRAN version of accrete 3 decades ago. This was requested by 
a StarGen user who is very familiar with the Dole and Fogg era versions of Accrete. The output can be viewed only in 
some browsers (for example Firefox and Opera), and should look something like this:

