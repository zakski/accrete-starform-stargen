# Authors, Implementations and Interested Parties I have looked at thus far.

###[ACRETE - Dole](https://scholar.google.com/scholar?cluster=2649232823724285381&hl=en&as_sdt=0,5)
Stephen H. Dole wrote the original research paper that detailed the solar system formation simulation code. Whilst I have not recovered his original source 
code; I have reliably recreated his original engine based on his papers that exist online, with the exception of the random number generator that he 
used.

###[Silicon Creation (aka Starform) - Fogg](https://scholar.google.com/scholar?cluster=9385174980475541539&hl=en&as_sdt=0,5)
Martyn J. Fogg wrote a subsequent research paper that attempted to vary the mas of the star and build up information about the potential atmosphere of each 
planet in the generated system. Mat Burdick's implementation is based on this.


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

###Interested Parties
Das Mill, Brian Davi, Callum Finlayson