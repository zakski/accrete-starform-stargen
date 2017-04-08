# Authors of Implementations

## Intro

This file contains a brief description of each examined implementations. Research papers, source code and/or more detailed readmes, if they exist, will be 
deposited into the model folder.

Initial model order will be according to the resource name.

## Implementations with Sources / Docs

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
- Burdick Version: n/a
- Key: Dole.1969

Stephen H. Dole wrote the original program and research paper that detailed the solar system formation simulation code. He was a prolific astronomy 
researcher and whilst I have not recovered his original source code; I have a reliable recreations of his original engine based on his papers that exist 
online, with the exception of the random number generator that he used as that would be machine dependent.

References are stored in accrete.bib.

###[ACRETE]

- Resource Name: 1970 - Stephen H. Dole - Computer Simulation of the Formation of Planetary Systems
- Author: Stephen H. Dole
- Poster/Publisher: Icarus
- Language: Most likely FORTRAN due to it being written for a IBM 7044.
- Creation Year: 1969
- Source Year: 1970
- Parents: n/a, the original
- Original Source: Research paper, but no code
- Reproducibility: Completely Reproducible.
- Burdick Version: n/a
- Key: Dole.1970

Stephen H. Dole presented the original research paper findings in Icarus in 1970. The program that used is basically identical to the one written for the 
Rand Corporation.

References are stored in 1.5 accrete.bib.

###[ACRETE](https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770006045.pdf)

- Resource Name: 1977 - Isaacmam & Sagan - Computer Simulations of Planetary Accretion Dynamics: Sensitivity to Initial Conditions
- Author: Richard Isaacman & Carl Sagan
- Poster/Publisher: Cornell University
- Language: Most likely FORTRAN due to it being written for a IBM 7044.
- Creation Year: 1977
- Source Year: 1977
- Parents: Dole.1969, Dole.1970
- Original Source: Research paper, but no code
- Reproducibility: Possibly Reproducible.
- Burdick Version: n/a
- Key: Sagan.1977

Programmed by J.Rice and provided to Sagan by Stephen H. Dole. Isaacman and Sagan modified the original to scrutinise the sensitivity of the starting 
conditions. They come to the conclusion that Acrete is either missing some essential physics of solar system cosmogony or that planetary systems similar to 
our own are only one variety out of many different possible planetary systems.

Most recreations of Accrete do not directly use this paper as their inspiration.

References are stored in 1.7 accrete.bib.

###[ACRETE](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Resource Name: 1984 - Steve Gilham - Acrete 
- Author: Steve Gilham
- Poster/Publisher: White Dwarf
- Language: Microsoft Basic
- Creation Year: 1984
- Source Year: 1984
- Parents: Dole.1969, Dole.1970
- Original Source: Located.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Gilham.1984

Gilham wrote a variant based on Dole's original paper in Icarus in the late '60s. It appeared in the gaming magazine White Dwarf issue 58/57 (UK/US) which was 
published in October 1984. He may have also released it on usenet, but such a post is missing from google groups.


###[Silicon Creation](http://www.academia.edu/download/31676329/fogg1985.pdf)

- Resource Name: 1985 - Martyn J. Fogg - Extra-Solar Planetary Systems A Microcomputer Simulation
- Author: Martyn J. Fogg
- Poster/Publisher: Journal of the British Interplanetary Society 
- Language: BBC Basic
- Creation Year: 1985
- Source Year: 1985
- Parents: Dole.1969, Dole.1970, Sagan.1977
- Original Source: Gone.
- Reproducibility: Partially Reproducible.
- Burdick Version: n/a
- Key: Fogg.1985

Martyn J. Fogg wrote a subsequent research paper that attempted to vary the mass of the star and build up information about the potential atmosphere of each 
planet in the generated system. 

Brian Davis reports that he wrote Fogg to request the source, and he replied that is was on a discarded machine in his 
garage, and even he wouldn't retrieve it, but write it from scratch again if the situation ever came up. Thus far no one seems to of replicated his planetary 
classification system.

References are stored in 2.0 accrete.bib.

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
- Burdick Version: None
- Key: Gilham.1988

A version of Matt Burdick's code, ported by him to C from pascal. Was posted to a usernet newsgroup by Steve Gilham. Whilst it does seem to date back to 1988, 
the end of Gilham's post was cut off in the Google Group archive, so the code is incomplete.

###[Starform](https://groups.google.com/forum/#!topic/rec.games.design/xp8edV1wyIE)

- Resource Name: 1993 - Matt Burdick & Sean Malloy - Starform
- Author: Matt Burdick
- Poster/Publisher: Sean Malloy
- Language: C
- Creation Year: >= 1988
- Source Year: 1993
- Parents: Burdick.1998
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: V3.1
- Key: Malloy.1993

More up-to-date version of Matt Burdick's code, ported to C from pascal. Was given to Ian Burrell by Sean Malloy. 

It has the complete source code, and seems to be a higher version than the one posted by Steve Gilham, however the name change suggests that there is at least 
one intermediate version between the two.
 
It was wrapped into a shar in 1993, but Malloy had been sitting on it for a while, so it is difficult to place its precise place in the timeline.

###[ACRETE](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Resource Name: 1993 - Steve Gilham - Acrete Psuedocode
- Author: Steve Gilham
- Poster/Publisher: Steve Gilham
- Language: Psuedocode
- Creation Year: 1993
- Source Year: 1993
- Parents: Gilham.1984
- Original Source: Located.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Gilham.1993

Gilham re-wrote his variant in psuedocode in response to a request on usenet in 1993.

###[ACCRETE](http://znark.com/create/files/accrete.zip)
- Resource Name: 1994 - Matt Burdick - Accrete
- Author: Mat Burdick
- Poster/Publisher: Ian Burell
- Language: C
- Creation Year: >= 1988
- Source Year: 1994
- Parents: Gilham.1988
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Burdick.1994.A

One of Mat Burdick's C versions which is commonly distributed as accrete.
 
This looks like The same major version as the incomplete code gilham supplied so it should make for an interesting comparison.  

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
- Burdick Version: n/a
- Key: Burdick.1988

Mat Burdick's simulation reversed engineered from Dole and Fogg's papers. The main fork of source code that everyone seems to of worked off.

This pretty close to being the original copy of Mat Burdick's first version, In that it is written in pascal which apparently is his original language and the 
comments mention copyright 1988. However the fact that the source code was found on Ian Burrell's website and the files were last modified in 1994 count 
against it being the very first version. Additionally the zip file was also labelled accretion, which has never been a name that Burdick has called it. 

Burdick could only partially reproduce Fogg's work, since the way that Fogg determined the atmosphere type is not cleared marked out in his research paper.

Nevertheless, this codebase is the parent of the vast majority of variations that have any source code still extant. 

###[Starform](http://znark.com/create/accrete.html)
- Resource Name: 1994 - Matt Burdick - Starform
- Author: Matt Burdick
- Poster/Publisher: Ian Burrell
- Language: C
- Creation Year: 1988
- Source Year: 1994
- Parents: Burdick.1994.A
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: V3.0
- Key: Burdick.1994.B

Mat Burdick's third iteration of his simulation reversed engineered from Dole and Fogg's papers. 

Like the other iterations this seems to be the main fork of source code that everyone seems to of worked off. Unfortunately I was unable 
to detect a site belonging to him that still hosted his source code so third party hosted copies will have to do.

Accrete2 and Starform are names given to this iteration fairly interchangeably.


###[ACCRETION](http://reocities.com/CapeCanaveral/8191/usml.html)
- Resource Name: 1995 - Andrew Folkins - Accretion
- Author: Andrew Folkins
- Poster/Publisher: Steve Dang
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Dole.1969, Dole.1970
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Folkins.1988

Andrew Folkins at some point published a version of accrete for the amiga, which was then modified by keris, unfortunately it was packed up in a shar which 
has a different last modified date than the wrapping header info, so I am uncertain about this version's exact date.

Like Steve Gilham, his line of code is at least initially distinct from Burdick's.

###[Starform](http://reocities.com/CapeCanaveral/8191/usml.html)
- Resource Name: 1995 - Matt Burdick - Starform
- Author: Matt Burdick
- Poster/Publisher: Steve Dang
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Burdick.1994.B
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: V3.0
- Key: Burdick.1995

Nyrath, like Burrell and a few others, has a cached copy of what I assume is one of the first gen iterations of Burdick's accrete program. This version is 
dated as been last modified later than Burrell's copy, so we have a potential version order between them.


###[ACCRETE](http://reocities.com/CapeCanaveral/8191/usml.html)
- Resource Name: 1995 - Nyrath - Accrete
- Author: Matt Burdick
- Poster/Publisher: Nyrath the nearly wise
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Burdick.1994.A
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Nyrath.1995

Nyrath, like Burrell and a few others, has a cached copy of what I assume is one of the first gen iterations of Burdick's accrete program. This version is 
dated as been last modified later than Burrell's copy, so we have a potential version order between them.

###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/hs3hTFtJdKY)

- Resource Name: 1995 - Steve Gilham - Acrete
- Author: Steve Gilham
- Poster/Publisher: Steve Gilham
- Language: C++
- Creation Year: <= 1995
- Source Year: 1995
- Parents: Gilham.1984, Gilham.1993
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
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
- Parents:  Burdick.1994.A / Nyrath.1995 / Burdick.1995
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Francis.1996

Erik Max Francis produced a slightly modified version of Burdick's code that prints it's output slightly differently. It seems to extends from the first 
generation code line but I am unsure as to which variant is the closest to being the actual parent.

###[ACCRETE2 mod 0](http://www.mu.org/~joe/traveller/archive/software/accrete2.zip)
- Resource Name: 1997 - Christopher E. Webb - Accrete2 Mod 0
- Author: Christopher E. Webb
- Poster/Publisher: Joseph Heck
- Language: C++
- Creation Year: <= 1997
- Source Year: 1997
- Parents:  Burdick.1994.A / Nyrath.1995
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Webb.1997.A

Christopher E. Webb seems to of modified a version of accrete to utilise and generate some traveller rpg specific values such a UWP.

###[ACCRETE2 mod 1](https://web.archive.org/web/19970709191550/http://www.mscomm.com/~cwebb/download/accrete2.zip)
- Resource Name: 1997 - Christopher E. Webb - Accrete2 Mod 1
- Author: Christopher E. Webb
- Poster/Publisher: Christopher E. Webb
- Language: C++
- Creation Year: <= 1997
- Source Year: 1997
- Parents:  Webb.1997.A
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Webb.1997.B

Christopher E. Webb developed an updated version of his code that uses traveller rpg information more substantially.

This copy was found on his website.

###[ACCRETE3](http://www.mu.org/~joe/traveller/archive/software/accrete3.zip)
- Resource Name: 1997 - Christopher E. Webb - Accrete3
- Author: Christopher E. Webb
- Poster/Publisher: Joseph Heck
- Language: C++
- Creation Year: <= 1997
- Source Year: 1997
- Parents:  Webb.1997.A
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Webb.1997.C

Christopher E. Webb developed an updated version of his code that uses traveller rpg information more substantially.

This copy was found on Joseph Heck's website with the label of Accrete3, but is labelled Accrete2 mod 1 in the readme just like the one on Webb's website.

###[ACCRETE](http://znark.com/create/accrete.html)
- Resource Name: 1997 - Ian Burrell - Accrete
- Author: Ian Burell
- Poster/Publisher: Ian Burrell
- Language: Java
- Creation Year: >= 1993
- Source Year: 1997
- Parents: Burdick.1988, Burdick.1994.A, Burdick.1994.B
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Burrell.1997

Ian Burrell's version, which given the information I have a available, seems to ported from some code provided by Sean Malloy.

Only the portion of Burdick's code relating to Dole's paper seems to of been ported to Java, but it has provided me the initial understanding of how 
accretion and Burdick's code works. 

Burrell's code is loosely based on Burdick's source code, but takes a much more rigid object-oriented approach.

###[STARFORM](http://www.reocities.com/Area51/6902/w_accr.html)

- Resource Name: 1998 - Carl Burke - Starform
- Author: Carl Burke
- Poster/Publisher: Carl Burke
- Language: Java
- Creation Year: >= 1995
- Source Year: 1998
- Parents: Burdick.1994.B or Malloy.1993 most likely, Folkins.1988 for displays
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: unsure
- Key: Burke.1998
 
 Carl Burke, like Ian Burell, wrote his own java applet version of starform/accrete. He also was aware of Ian Burell's work and wonder how much it influenced
 him.
 
 In any case, He has written several versions in Pascal, C, Modula-2, C++ as well Java, but only this java version seems to remain.

###[Accrete2](https://web.archive.org/web/20120201000000*/http://markjstock.org/progs/accrete2.tar.gz)
- Resource Name: 1998 - Mark J. Stock - Acrete2
- Author: Mark J. Stock
- Poster/Publisher: Mark J. Stock
- Language: C
- Creation Year: >= 1988
- Source Year: 1998
- Parents: Burdick.1995 ?
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: V3.0
- Key: Stock.1998

One of Mat Burdick's versions hacked about by Mark J. Stock. 

###[Accrete2](https://web.archive.org/web/20040905132355/http://firedrake.org/keris/stars/index.html)
- Resource Name: 1999 - Keris - Accretion v1
- Author: Chris "Keris" Croughton
- Poster/Publisher: Chris "Keris" Croughton
- Language: C
- Creation Year: >= 1988
- Source Year: 1999
- Parents: Folkins.1988
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Keris.1999

A version based on Andrew Folkins, hacked about by Keris, removing some of his optimisations and added gas accretion for normal planets to give some sort of 
atmosphere, it seems to work reasonably. The output formats are (of course) totally different from starform. 

###[Accrete](http://seegras.discordia.ch/Roleplay/Traveller/Software/Accrete.tgz)
- Resource Name: 1999 - Peter Keel - Accrete
- Author: Matt Burdick
- Poster/Publisher: Peter Keel
- Language: C
- Creation Year: >= 1988
- Source Year: 1999
- Parents: Burdick.1994.A / Nyrath.1995 / Burdick.1995
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Keel.1999.A

A version cached by Peter Keel on his traveller rpg site.


###[Starform](http://seegras.discordia.ch/Roleplay/Traveller/Software/StarForm.tgz)
- Resource Name: 1999 - Peter Keel - Starform
- Author: Matt Burdick
- Poster/Publisher: Peter Keel
- Language: C
- Creation Year: >= 1988
- Source Year: 1999
- Parents: Burdick.1995
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: V3.0
- Key: Keel.1999.B

A version cached by Peter Keel on his traveller rpg site.

###[Accrete2](https://web.archive.org/web/20040905132355/http://firedrake.org/keris/stars/index.html)
- Resource Name: 2000 - Keris - Accretion v2
- Author: Chris "Keris" Croughton
- Poster/Publisher: Chris "Keris" Croughton
- Language: C++
- Creation Year: >= 1988
- Source Year: 2000
- Parents: Keris.1999
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Keris.2000.A

This is Andrew Folkins' code again, but converted to C++. It's even more hacked about.

###[Starform](https://web.archive.org/web/20040905132355/http://firedrake.org/keris/stars/index.html)
- Resource Name: 2000 - Keris - Starform
- Author: Chris "Keris" Croughton
- Poster/Publisher: Chris "Keris" Croughton
- Language: C++
- Creation Year: >= 1988
- Source Year: 2000
- Parents: Keris.1999
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: V3.0
- Key: Keris.2000.B

This is Matt Burdick's original Starform code, hacked about by Keris with additions for atmospheric composition

###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Resource Name: 2001 - Jon Leech - Accrete
- Author: Jon Leech
- Poster/Publisher: Ian Burrell
- Language: C++
- Creation Year: <= 1992
- Source Year: 2001
- Parents: Dole.1969 / Dole.1970 / Larrison.????
- Original Source: Complete.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Leech.1992

Jon Leech ported code to C++ based on code written by Wales Larrison. He mentions an ftp site where his code is located, ftp.cs.unc.edu:pub/acrete.c, but it 
is no longer stored there. 
 
I have acquired a version of it from Ian Burrell's [website](http://znark.com/create/accrete.html), though I do not know if there have been any changes in 
the meantime.

###[Accrete](http://seegras.discordia.ch/Roleplay/Traveller/Software/Accrete.tgz)

- Resource Name: 2003 - Chuck Swiger - Accrete
- Author: Chuck Swiger
- Poster/Publisher: Chuck Swiger
- Language: C
- Creation Year: >= 1988
- Source Year: 2003
- Parents: Burdick.1994.A / Nyrath.1995 / Burdick.1995 / Keel.1999.A
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Swiger.2003
 
A version altered by Swiger to include psuedorandom number generation enhancements and convert to use ansi C.

###[Stargen](https://web.archive.org/web/20070221205935/http://home.comcast.net/~brons/NerdCorner/StarGen/StarGen.html)

- Resource Name: 2006 - Jim Burrows - StarGen
- Author: Jim Burrows
- Poster/Publisher: Jim Burrows
- Language: C++
- Creation Year: >= 1988
- Source Year: 2006
- Parents: Many
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Burrows.2006

A starform version altered by Burrows with bits and pieces added and modified and borrowed from Ian Burrell, C. Burke and Chris Croughton. StarGen is based 
mostly on Burdick's, but has borrowed from the others, most notably Keris's.
                              
###[Stargen](http://www.eldacur.com/~brons/NerdCorner/StarGen/StarGen.html)

- Resource Name: 2008 - Jim Burrows - StarGen
- Author: Jim Burrows
- Poster/Publisher: Jim Burrows
- Language: C++
- Creation Year: >= 2006
- Source Year: 2008
- Parents: Burrows.2006
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Burrows.2008

Updated version of the 2006 edition.
 
###[Accrete](https://github.com/sveco/AccreteSharp)

- Resource Name: 2012 - sveco - Accrete
- Author: sveco
- Poster/Publisher: sveco (github)
- Language: C#
- Creation Year: >= 2006
- Source Year: 2012
- Parents: Burke.1998
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Burrows.2008
  
port of Carl Burke's accrete to c#
 
###[Stargen](http://www.fedtrek.com/staff/omega13a/stargen_2013.zip)
- Resource Name: 2013 - Brandon Amaro - Stargen
- Author: Brandon Amaro (omega13a)
- Poster/Publisher: Brandon Amaro (omega13a)
- Language: C++
- Creation Year: >= 2008
- Source Year: 2013
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Amaro.2013
  
A snapshot of omega13a's version of Stargen that he put on his Star Trek fan site.

###[Accrete](https://github.com/calebrob6/accrete)

- Resource Name: 2013 - Caleb Robinson - Accrete
- Author: Caleb Robinson
- Poster/Publisher: Caleb Robinson (github)
- Language: Javascript
- Creation Year: >= 2003
- Source Year: 2013
- Parents: Swiger.2003
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Robinson.2013
  
port of Chuck Swiger's accrete to Javascript

 
###[Starform](https://github.com/fusiongyro/starform)

- Resource Name: 2013 - Daniel Lyons - Starform
- Author: Daniel Lyons
- Poster/Publisher: Daniel Lyons (github)
- Language: C
- Creation Year: >= 2000
- Source Year: 2013
- Parents:  Keris.2000.B
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Lyons.2013
   
port of Keris's starform code to modern ansi C standards. Technically last touched the core code in 2011.

###[Stargen](https://github.com/grahamreeds/StarGen)

- Resource Name: 2013 - Graham Reeds - Stargen
- Author: Graham Reeds
- Poster/Publisher: Graham Reeds (github)
- Language: C++
- Creation Year: >= 2008
- Source Year: 2013
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Amaro.2013
  
An expansion on burrow's code.

###[Accrete2](https://github.com/makhidkarun/accrete2)

- Resource Name: 2013 - Joseph Heck - Accrete2
- Author: Joseph Heck
- Poster/Publisher: Joseph Heck (github)
- Language: C
- Creation Year: <2013
- Source Year: 2013
- Parents: Burrell.1997, Burdick.1994.B, Burdick.1994.A, Burdick.1988 ?
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Heck.2013
  
A copy of a bunch of different version all in the same place, pretty sure this guys had a copy of Webb's code too.


###[Accrete](https://github.com/kennon/Accrete.js)
- Resource Name: 2013 - Kennon Ballou - Accrete
- Author: Kennon Ballou
- Poster/Publisher: Kennon Ballou (github)
- Language: Javascript
- Creation Year: >= 2012
- Source Year: 2013
- Parents: Anderson.2013
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Ballou.2013
  
fork of Mitch Anderson's port

###[Accrete](https://github.com/tmanderson/Accrete.js)

- Resource Name: 2013 - Mitch Anderson - Accrete
- Author: Mitch Anderson
- Poster/Publisher: Mitch Anderson (github)
- Language: Javascript
- Creation Year: >= 2012
- Source Year: 2013
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Anderson.2013
  
A port of burrow's code.

##[Accrete](https://github.com/pgremo/accrete)

- Resource Name: 2013 - pgremo - Accrete
- Author: pgremo
- Poster/Publisher: pgremo (github)
- Language: Javascript
- Creation Year: >= 2012
- Source Year: 2013
- Parents: Burrell.1997
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: pgremo.2013
  
A version based on Ian Burrell's java code.

###[Stargen](https://github.com/omega13a/stargen)
- Resource Name: 2014 - Brandon Amaro - Stargen
- Author: Brandon Amaro 
- Poster/Publisher: Brandon Amaro (github)
- Language: C++
- Creation Year: >= 2008
- Source Year: 2014
- Parents: Amaro.2013
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Amaro.2014
  
omega13a's version on github


###[Stargen](https://github.com/makhidkarun/stargen)

- Resource Name: 2014 - Joseph Heck - Stargen
- Author: Joseph Heck
- Poster/Publisher: Joseph Heck (github)
- Language: C++
- Creation Year: >= 2008
- Source Year: 2014
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Heck.2014
  
Joseph Heck copy of Burrow's code.

###[Accrete](https://github.com/kbingman/accrete)

- Resource Name: 2014 - Keith Bingman - Accrete
- Author: Keith Bingman
- Poster/Publisher: Keith Bingman (github)
- Language: Javascript
- Creation Year: >= 2008
- Source Year: 2014
- Parents: Swiger.2003 or possibly Robinson.2013
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Bingman.2014

May be his own version or undocumented fork.

###[Accrete](https://github.com/monolar/nim-accrete)
- Resource Name: 2015 - Andreas Marr - Accrete - Nim
- Author: Andreas Marr
- Poster/Publisher: Andreas Marr (github)
- Language: Nim
- Creation Year: >= 2014
- Source Year: 2015
- Parents: Dole.1969 / Sagan.1977
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Marr.2015.A

An Interesting standalone recreation of dole/sagan's versions in an obscure language.

###[Accrete](https://github.com/monolar/accrete-rb)

- Resource Name: 2015 - Andreas Marr - Accrete
- Author: Andreas Marr
- Poster/Publisher: Andreas Marr (github)
- Language: Ruby
- Creation Year: 2015
- Source Year: 2015
- Parents: Marr.2015.A
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Marr.2015.B

I Believe this to be a follow on from his previous stuf in a more mainstream language.

###[Accrete](https://github.com/kbingman/accretejs)

- Resource Name: 2015 - Keith Bingman - Accrete
- Author: Keith Bingman
- Poster/Publisher: Keith Bingman (github)
- Language: Javascript
- Creation Year: >= 2012
- Source Year: 2015
- Parents: Anderson.2013
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Bingman.2015

Fork of Anderson's work.

###[Accrete](https://github.com/zonkmachine/starsysgen)

- Resource Name: 2015 - Oskar Wallgren - Accrete
- Author: Oskar Wallgren
- Poster/Publisher: Oskar Wallgren (github)
- Language: C
- Creation Year: >= 2003
- Source Year: 2015
- Parents: Swiger.2003
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Wallgren.2015
  
copy of Chuck Swiger's accrete.

###[Stargen](https://github.com/Zomega/garnets)

- Resource Name: 2015 - Will Oursler - Stargen
- Author: Will Oursler
- Poster/Publisher: Will Oursler (github)
- Language: Python
- Creation Year: >= 2008
- Source Year: 2015
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Oursler.2015
  
A port of burrow's code.

###[Stargen](https://github.com/donggas90/ACCRETEPlus)

- Resource Name: 015- Jong-il Hong - Accrete
- Author: Jong-il Hong
- Poster/Publisher: Jong-il Hong (github)
- Language: C++
- Creation Year: >= 2011
- Source Year: 2015
- Parents:  Lyons.2013
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Hong.2015

A port of Lyons's code to C++

###[Accrete](https://bitbucket.org/dchapes/accrete)

- Resource Name: 2016 - Dave Chapeskie - Accrete
- Author: Dave Chapeskie
- Poster/Publisher: Dave Chapeskie (github)
- Language: C
- Creation Year: >= 1988
- Source Year: 2016
- Parents: Burrell.1997, Burdick.1994.B, Burdick.1994.A, Burdick.1988 ?
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Chapeskie.2016

Looks like copies of old code.

###[Accrete](https://github.com/StollD/Accrete)

- Resource Name: 2016 - Dorian Stoll - Accrete
- Author: Dorian Stoll
- Poster/Publisher: Dorian Stoll (github)
- Language: C#
- Creation Year: >= 2003
- Source Year: 2016
- Parents: Swiger.2003
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Stoll.2016
  
variant of Chuck Swiger's accrete.

###[Stargen](https://github.com/glegeza/StarformNET)

- Resource Name: 2017 - George Legeza - Starform
- Author: George Legeza
- Poster/Publisher: George Legeza (github)
- Language: C#
- Creation Year: >= 2008
- Source Year: 2017
- Parents: Burrows.2008
- Original Source: Acquired.
- Reproducibility: Reproducible.
- Burdick Version: n/a
- Key: Legeza.2017
  
A port of burrow's code.


## Missing Implementations

###ACCRETE 1a/1b

- Resource Name: n/a
- Author: Dave Allen
- Poster/Publisher: n/a
- Language: IBM Basic
- Creation Year: <= 1988
- Source Year: ????
- Parent: Dole.1969, Dole.1970 or Burdick.1988 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Allen.????

Dave Allen claims in usml to have written variations of Accrete, 1a to allow captured moons rather than coalesce straight away. The second one, 1b, an attempt
to simulate moon systems, as well as potentially an original version. 

I cannot currently find any source code of these programs online so his branches are considered to end with him and its hard to see how they fit into the big
picture. Most likely given other variations that I do have the source code for, it either comes from a direct recreation of Dole's paper or is based of one 
of Burdick's early recreations.


###[SYSTEM 2300](https://groups.google.com/forum/#!topic/rec.games.frp/uRaCg-xv6Ac)

- Resource Name: n/a
- Author: Burton Choinski
- Poster/Publisher: n/a
- Language: C
- Creation Year: 1990
- Source Year: n/a
- Parents: Dole.1969, Dole.1970 or Fogg.1985 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Choinski.????

Choinski wrote a variation on burdick's accrete/starform program for the 2300ad RPG. It uses a combination of the World Builder's Guid, the Director's guide 
and accrete. I cannot currently find any source code of this program online, so this branch is considered orphaned right now, since I don't know where it 
fits into the bigger picture.


###[ACRETE](https://groups.google.com/forum/#!topic/sci.astro/9WzlczI3cL0)

- Resource Name: n/a
- Author: Wales Larrison
- Poster/Publisher: n/a
- Language: C ?
- Creation Year: <= 1992
- Source Year: n/a
- Parents: Dole.1969 or Dole.1970 most likely
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Larrison.????

Jon Leech claims that Wales wrote a variation based on Dole's 1970 paper. I cannot currently find any source code of this program online, so this branch is 
considered orphaned right now, since I don't know where it fits into the bigger picture.

###ACRETE

- Resource Name: n/a
- Author: Matt Burdick
- Poster/Publisher: Joe Nowakowski
- Language: C ?
- Creation Year: >= 1988
- Source Year: 1991
- Parents: Burdick.1988
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Key: Burdick.????

published to comp.sources by Joe Nowakowski but missing in the archives.


###[Accrete2 / Starform](https://groups.google.com/forum/#!topic/sci.astro/Gq-4HLD9DYU)
- Resource Name: n/a
- Author: Matt Burdick
- Poster/Publisher: Philip Hodder
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Malloy.1993
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Burdick Version: V3.1
- Key: Hodder.????

A variant of the highest version of Burdick's code that we have source code for. Posted by Hodder, but no cached post lying around as far as I can see.


###[Accrete2 / Starform](https://groups.google.com/forum/#!topic/sci.astro/Gq-4HLD9DYU)
- Resource Name: n/a
- Author: Matt Burdick
- Poster/Publisher: n/a
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Malloy.1993
- Original Source: Missing.
- Reproducibility: Unreproducible.
- Burdick Version: V3.6
- Key: Burdick.????

Highest version known to exist of burdick's code. may have put it on an anonymous ftp site
