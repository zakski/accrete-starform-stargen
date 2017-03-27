# Authors of Implementations

## Intro

This file contains a brief description of each examined implementations. Research papers, models or more detailed readmes, if they exist, will be deposited 
into the folder containing this file.

## Implementations

###[ACRETE](http://www.rand.org/content/dam/rand/pubs/papers/2005/P4226.pdf)

- Resource Name: 1969 - Stephen H. Dole - Formation of Planetary Systems by Aggregation A Computer Simulation
- Author: Stephen H. Dole
- Poster/Publisher: The Rand Corporation
- Language: Most likely FORTRAN due to it being written for a IBM 7044.
- Creation Year: 1969
- Source Year: 1969
- Parents: n/a, the original
- Original Source: Research paper, but no code
- Reproducibility: Completely Reproducible.
- Key: Dole.1969

Stephen H. Dole wrote the original program and research paper that detailed the solar system formation simulation code. He was a prolific astronomy 
researcher and whilst I have not recovered his original source code; I have a reliable recreations of his original engine based on his papers that exist 
online, with the exception of the random number generator that he used as that would be machine dependent.

###[ACRETE](https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770006045.pdf)

- Resource Name: 1977 - Isaacmam & Sagan - Computer Simulations of Planetary Accretion Dynamics Sensitivity to Initial Conditions
- Author: Richard Isaacman & Carl Sagan
- Poster/Publisher: Cornell University
- Language: Most likely FORTRAN due to it being written for a IBM 7044.
- Creation Year: 1977
- Source Year: 1977
- Parents: Dole.1969
- Original Source: Research paper, but no code
- Reproducibility: Possibly Reproducible.
- Key: Sagan.1977

Programmed by J.Rice and provided to Sagan by Stephen H. Dole. Isaacman and Sagan modified the original to scrutinise the sensitivity of the starting 
conditions. They come to the conclusion that Acrete is either missing some essential physics of solar system cosmogony or that planetary systems similar to 
our own are only one variety out of many different possible planetary systems.

Most recreations of Accrete do not directly use this paper as their inspiration.

###[ACRETE](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Resource Name: 1984 - Steve Gilham - Acrete 
- Author: Steve Gilham
- Poster/Publisher: White Dwarf
- Language: Microsoft Basic
- Creation Year: 1984
- Source Year: 1984
- Parents: Dole.1969
- Original Source: Located.
- Reproducibility: Reproducible.
- Key: Gilham.1984

Steve wrote a variant based on Dole's original paper in Icarus in the late '60s. It appeared in the gaming magazine White Dwarf issue 58/57 (UK/US) which was 
published in October 1984. He may have also released it on usenet, but such a post is missing from google groups.


###[Silicon Creation](http://www.academia.edu/download/31676329/fogg1985.pdf)

- Resource Name: 1985 - Martyn J. Fogg - Extra-Solar Planetary Systems A Microcomputer Simulation
- Author: Martyn J. Fogg
- Poster/Publisher: Journal of the British Interplanetary Society 
- Language: BBC Basic
- Creation Year: 1985
- Source Year: 1985
- Parents: Dole.1969, Sagan.1977
- Original Source: Gone.
- Reproducibility: Partially Reproducible.
- Key: Fogg.1985

Martyn J. Fogg wrote a subsequent research paper that attempted to vary the mass of the star and build up information about the potential atmosphere of each 
planet in the generated system. Brian Davis reports that he wrote Fogg to request the source, and he replied that is was on a discarded machine in his 
garage, and even he wouldn't retrieve it, but write it from scratch again if the situation ever came up. Thus far no one seems to of replicated his planetary 
classification system.

###[ACCRETION](http://znark.com/create/accrete.html)

- Resource Name: 1994 - Matt Burdick - Accretion
- Author: Matt Burdick
- Poster/Publisher: Ian Burrell
- Language: Turbo Pascal
- Creation Year: 1988
- Source Year: 1994
- Parents: Fogg.1985
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Key: Burdick.1988

This pretty close to being the original copy of Mat Burdick's version, In that it is written in pascal which apparently is his original language and the 
comments mention copyright 1988. However the fact that the source code was found on Ian Burrell's website and the files were last modified in 1994 count 
against it being the very first version. Additionally the zip file was also labelled accretion, which has never been a name that Burdick has called it. 

Burdick could only partially reproduce Fogg's work, since the way that Fogg determined the atmosphere type is not cleared marked out in his research paper.

Nether the less, this codebase is the parent of the vast majority of variations that have any source code still extant. 

###ACCRETE 1a/1b

- Resource Name: n/a
- Author: Dave Allen
- Poster/Publisher: n/a
- Language: IBM Basic
- Creation Year: <= 1988
- Source Year: ????
- Parent: Dole.1969 or Burdick.1988 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Allen.????

Dave Allen claims in usml to have written variations of Accrete, 1a to allow captured moons rather than coalesce straight away. The second one, 1b, an attempt
to simulate moon systems, as well as potentially an original version. 

I cannot currently find any source code of these programs online so his branches are considered to end with him and its hard to see how they fit into the big
picture. Most likely given other variations that I do have the source code for, it either comes from a direct recreation of Dole's paper or is based of one 
of Burdick's early recreations.

###[Accrete](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Resource Name: 1988 - Matt Budick - Accrete -  Steve Gilham Incomplete
- Author: Matt Burdick
- Poster/Publisher: Steve Gilham
- Language: C
- Creation Year: >= 1988
- Source Year: 1993
- Parent: Burdick.1988
- Original Source: Incomplete.
- Reproducibility: Partially Reproducible.
- Key: Gilham.1993

A version of Matt Burdick's code, ported by him to C from pascal. Was posted to a usernet newsgroup by Steve Gilham. Whilst it does seem to date back to 1988, 
the end of Gilham's post was cut off in the Google Group archive, so the code is incomplete.

###[SYSTEM 2300](https://groups.google.com/forum/#!topic/rec.games.frp/uRaCg-xv6Ac)

- Resource Name: n/a
- Author: Burton Choinski
- Poster/Publisher: n/a
- Language: C
- Creation Year: 1990
- Source Year: n/a
- Parents: Dole.1969 or Fogg.1985 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Choinski.????

Burton wrote a variation on burdick's accrete/starform program for the 2300ad RPG. It uses a combination of the World Builder's Guid, the Director's guide 
and accrete. I cannot currently find any source code of this program online, so this branch is considered orphaned right now, since I don't know where it 
fits into the bigger picture.


###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Resource Name: n/a
- Author: Wales Larrison
- Poster/Publisher: n/a
- Language: C ?
- Creation Year: <= 1992
- Source Year: n/a
- Parents: Dole.1969 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Larrison.????

Jon Leech claims that Wales wrote a variation based on Dole's 1970 paper. I cannot currently find any source code of this program online, so this branch is 
considered orphaned right now, since I don't know where it fits into the bigger picture.

###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Resource Name: 2001 - Jon Leech - Accrete
- Author: Jon Leech
- Poster/Publisher: Ian Burrell
- Language: C++
- Creation Year: <= 1992
- Source Year: 2001
- Parents: Dole.1969 / Larrison.????
- Original Source: Complete.
- Reproducibility: Reproducible.
- Key: Leech.1992


Jon Leech ported code to C++ based on code written by Wales Larrison. He mentions an ftp site where his code is located, ftp.cs.unc.edu:pub/acrete.c, but it 
is no longer stored there. 
 
I have acquired a version of it from Ian Burrell's [website](http://znark.com/create/accrete.html), though I do not know if there have been any changes in 
the meantime.

###[Starform](https://groups.google.com/forum/#!topic/rec.games.design/xp8edV1wyIE)

- Resource Name: 1993 - Matt Burdick & Sean Malloy - Starform
- Author: Matt Burdick
- Poster/Publisher: Sean Malloy
- Language: C
- Creation Year: <= 1993
- Source Year: 1993
- Parents: Burdick.1988 / Gilham.1993
- Original Source: Complete.
- Reproducibility: Reproducible.
- Key: Malloy.1993

More up-to-date version of Matt Burdick's code, ported to C from pascal. Was given to Ian Burrell by Sean Malloy. 

It has the complete source code, and seems to be a higher version than the one posted by Steve Gilham, however the name change suggests that there is at least 
one intermediate version between the two. 

###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/hs3hTFtJdKY)

- Resource Name: 1995 - Steve Gilham - Acrete
- Author: Steve Gilham
- Poster/Publisher: Steve Gilham
- Language: C++
- Creation Year: <= 1995
- Source Year: 1995
- Parents: Gilham.1984
- Original Source: Complete.
- Reproducibility: Reproducible.
- Key: Gilham.1995

Steve wrote a port of his original basic code to c++. Like his original basic code, its pretty interesting to see code that has not evolved along the burdick
branch.

###[Accrete](https://groups.google.com/forum/#!topic/rec.arts.sf.science/MqgYTuIf13w)

- Resource Name: 1996 - Erik Max Francis - Accrete
- Author: Erik Max Francis
- Poster/Publisher: Erik Max Francis
- Language: C
- Creation Year: <= 1996
- Source Year: 1996
- Parents:  Burdick.1988 / Gilham.1993
- Original Source: Complete.
- Reproducibility: Reproducible.
- Key: Francis.1996

Erik Max Francis produced a slightly modified version of Burdick's code that prints it's output slightly differently.

###[ACCRETE - Burrell](http://znark.com/create/accrete.html)
- Resource Name: 1997 - Ian Burell - Accrete
- Author: Ian Burell
- Poster/Publisher: Ian Burell
- Language: Java
- Creation Year: >= 1993
- Source Year: 1997
- Parents: Malloy.1993
- Original Source: Complete.
- Reproducibility: Reproducible.
- Key: Burrell.1997

Ian Burrell's version, which given the information I hava available, seems to ported from some code provided by Sean Malloy.

Only the portion of Burdik's code relating to Dole's paper seems to of been ported to Java, but it has provided me the initial understanding of how 
accretion and burdick's code works. 

Burell's code is loosely based on Burdick's source code, but takes a much more rigid object-oriented approach.

###[ACCRETE2 - Burdick](http://znark.com/create/accrete.html)
One of Mat Burdick's versions which apparently is commonly distributed as accrete. Burdick's code base has the distinction of being the most widely used 
version of accrete and pretty much all of other authors have worked on forks of this. See "Starform - Burdick" for more info.
 
###STARFORM - Burdick
 Mat Burdick's simulation reversed engineered from Dole and Fogg's papers. The main fork of source code that everyone seems to of worked off. Unfortunately I was unable 
 to detect a site belonging to him that still hosted his source code so [Ian Burrell's hosted copy](http://znark.com/create/accrete.html) and the [USML 
 Geocities' archive](http://reocities.com/CapeCanaveral/8191/usmlarchive.html) will have to do.


###[STARFORM - Burke](http://www.reocities.com/Area51/6902/w_accr.html)
Carl Burke has written a another Java Applet based on Burdick's code, and also added some in-depth simulation changes. I have looked over the code that 
covers the accretion process, but not any of his other changes.

###[Accretion - Folkins](http://reocities.com/CapeCanaveral/8191/usmlarchive.html)
Andrew Folkins at some point published a port of burdick's code for the amiga, which was then modified by keris, unfortunately it is packed up in a shar 
which I had to manually extract the source files from, so precise information about when he last modified each file has been lost. He is the first to 
suggest a number of improvements on how to get the runtime down, and I am currently in the process of adding his planetismal insertion strategies as an option. 

###[Accretion V1/V2/Starform - Chris "Keris" Croughton](https://web.archive.org/web/20150814073537/http://firedrake.org/keris/)
Chris "Keris" Croughton is now deceased and his site and source code is now only accessible via the wayback machine.
	Chris builds upon mat's version and this is used as the basis of StarGen and several other forks. His main contributions are 
	improving the code's structure, adding various atmosphere bits and bobs and improved star code. He has also build upon a
	version made by Andrew Folkins.
#### V1
A version based on Andrew Folkins, hacked about by Keris, removing some of his optimisations and added gas accretion for normal planets to give some sort of 
atmosphere, it seems to work reasonably. The output formats are (of course) totally different from starform. 
#### V2
A version based on Andrew Folkins, hacked about by Keris, to now use C++. 
#### Starform
A version based on Burdick's code, hacked about by Keris. 