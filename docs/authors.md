# Authors of Implementations

## Intro

This file contains a brief description of each examined implementations. Research papers, models or more detailed readmes, if they exist, will be deposited 
into the folder containing this file.

## Implementations

###[ACRETE](https://scholar.google.com/scholar?cluster=2649232823724285381&hl=en&as_sdt=0,5)

- Author: Stephen H. Dole
- Language: Most likely FORTRAN due to it being written for a IBM 7044.
- Year: 1969
- Parent: n/a, the original
- Original Source: Research paper, but no code
- Reproducibility: Completely Reproducible.

Stephen H. Dole wrote the original program and research paper that detailed the solar system formation simulation code. He was a prolific astronomy 
researcher and whilst I have not recovered his original source code; I have a reliable recreations of his original engine based on his papers that exist 
online, with the exception of the random number generator that he used as that would be machine dependent.

###[ACRETE](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8))

- Author: Steve Gilham
- Language: Microsoft Basic
- Year: 1984
- Parent: Dole.1969
- Original Source: Located.
- Reproducibility: Reproducible.

Steve wrote a variant based on Dole's original paper in Icarus in the late '60s. It appeared in the gaming magazine White Dwarf issue 58/57 (UK/US) which was 
published in October 1984. He may have also released it on usenet, but such a post is missing from google groups.


###[Silicon Creation](https://scholar.google.com/scholar?cluster=9385174980475541539&hl=en&as_sdt=0,5)

- Author: Martyn J. Fogg
- Language: BBC Basic
- Year: 1985
- Parent: Dole.1969
- Original Source: Gone.
- Reproducibility: Partially Reproducible.

Martyn J. Fogg wrote a subsequent research paper that attempted to vary the mass of the star and build up information about the potential atmosphere of each 
planet in the generated system. Brian Davis reports that he wrote Fogg to request the source, and he replied that is was on a discarded machine in his 
garage, and even he wouldn't retrieve it, but write it from scratch again if the situation ever came up. Thus far no one seems to of replicated his planetary 
classification system.

###[ACCRETE 1a/1b](https://scholar.google.com/scholar?cluster=9385174980475541539&hl=en&as_sdt=0,5)

- Author: Dave Allen
- Language: IBM Basic
- Year: 1988
- Parent: Dole.1969 or Fogg.1985 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.

Dave Allen claims in usml to have written variations of Accrete, 1a to allow captured moons rather than coalesce straight away. The second one, 1b, an attempt
to simulate moon systems, as well as potentially an original version. I cannot currently find any source code of these programs online so his branches are
considered to end with him and its hard to see how they fit into the big picture.

###[Accrete](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Author: Matt Burdick / Steve Gilham
- Language: C
- Year: 1988 <= x <= 1993
- Parent: Fogg.1985
- Original Source: Incomplete.
- Reproducibility: Partially Reproducible.

A version of Matt Burdick's code, ported to C from pascal. Was posted to a usernet newsgroup by Steve Gilham. Whilst it does seem to date back to 1988, his 
posts were cut off, so the code is incomplete.

###[SYSTEM 2300](https://groups.google.com/forum/#!topic/rec.games.frp/uRaCg-xv6Ac)

- Author: Burton Choinski
- Language: C
- Year: 1990
- Parent: Dole.1969 or Fogg.1985 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.

Burton wrote a variation on burdick's accrete/starform program for the 2300ad RPG. It uses a combination of the World Builder's Guid, the Director's guide 
and accrete. I cannot currently find any source code of this program online, so this branch is considered orphaned right now, since I don't know where it 
fits into the bigger picture.


###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Author: Wales Larrison
- Language: C ?
- Year: <= 1992 ?
- Parent: Dole.1969
- Original Source: Missing.
- Reproducibility: Unreproducible.


Jon Leech claims that Wales wrote a variation based on Dole's 1970 paper. I cannot currently find any source code of this program online, so this branch is 
considered orphaned right now, since I don't know where it fits into the bigger picture.

###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Author: Jon Leech
- Language: C++
- Year: <= 1992
- Parent: Dole.1969 / Larrison.????
- Original Source: Missing.
- Reproducibility: Unreproducible.


Jon Leech ported code to C++ based on code written by Wales Larrison. He mentions an ftp site where his code is located, though I have acquired some version 
of it from Ian Burrel's website.

###[Starform](https://groups.google.com/forum/#!topic/rec.games.design/xp8edV1wyIE)

- Author: Matt Burdick / Sean Malloy 
- Language: C
- Year: <= 1993
- Parent: Burdick.(1988 <= x <= 1993)
- Original Source: Complete.
- Reproducibility: Reproducible.

More up-to-date version of Matt Burdick's code, ported to C from pascal. Was given to Ian Burrell by Sean Malloy. Seems to be more feature complete than the 
one uploaded by Steve Gilham.

###[ACRETE](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Author: Steve Gilham
- Language: C++
- Year: 1995
- Parent: Gilham.1984
- Original Source: Complete.
- Reproducibility: Reproducible.

Steve wrote a port of his original basic code to c++. Like his original basic code, its pretty interesting to see code that has not evolved along the burdick
branch.

###[Accrete](https://groups.google.com/forum/#!topic/rec.arts.sf.science/MqgYTuIf13w)

- Author: Matt Burdick / Erik Max Francis
- Language: C
- Year: 1996
- Parent: Burdick.(<= 1993)
- Original Source: Complete.
- Reproducibility: Reproducible.

Erik Max Francis produced a slightly modified version of Burdick's code that prints it's output slightly differently.

###[ACCRETE - Burrell](http://znark.com/create/accrete.html)
Ian Burrell's version, partially completed and written in java, has provided me the initial understanding of how accretion works. His code is loosely based 
on Burdick's source code, but takes a much more object-oriented approach.

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


###UNPROCESSED
Jon Leech wrote an alternative version, which I have included for the sake of completeness. [source code](http://znark.com/create/accrete.html), [mailing list](
http://www.cs.cmu.edu/afs/cs/usr/mnr/st/std096)

Mat Burdick wrote a version in turbo pascal.
