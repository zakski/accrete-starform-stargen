Welcome to StarGen. 

StarGen is a a random solar system generator, derived from the work of a
great number of people over the past three dozen years. (See Credits.txt for
details.) It's called StarGen because there are already enough versions that
call themselves starform to be confusing. StarGen's preferred output format
its Web pages.

There are 4 differen distributions available. All of them contain:

    ReadMe.txt                  The file you are reading
    Credits.txt                 The history of the program
    help						A folder/directory containing
	    Manual.html             The user's manual
	    Manual2-Building.html	Software Developer's Manual
	    WinStarGenHelp.html		Windows help
	ref							A folder containing
		*.gif and Key.html		Images etc used in generated HTML
		*.jpg					Images used in the Manual

To get more detailed documentation, feed the file Manual.html in the help
folder or directory to a Web browser or Help viewer that reads HTML files.

The Macintosh binary version (StarGen.sit) contains:

 	stargen						Mac OS X command line version
 	StarGen PPC                 Classic Mac version compiled for PPC
    StarGen 68K                 Classic Mac version for the original Mac

The Windows binary version (StarGen.zip) contains:
	WinStarGen.exe 				Clickable Windows version
	StarGen.exe 				DOS command-line version

The source distributions (StarGenSource.zip and StarGenSource.sit) contain:

    C sources                       The source code for the 
        *.c and *.h                 	program itself
    Makefile                        Make file for Unix/Mac OS X
    Macintosh-specific sources:		Specific sources for 
        mac_prefix.h StarGen.r 			the Mac version
        StarGen.prj			
    Windows project files:          Project files for
        StarGen.dsp StarGen.dsw 		Visual C on Windows
        Stargen.rc resource.h					

To build a Unix or Mac OS X version of StarGen, cd to the directory
containing the files listed above and type

    make

You may need to edit the Makefile if you are using a version of Unix or
the GNU development tools very different from the Mac OS X and GNU C and
make that I used for development and testing.

To build the Macintosh-native version you will need a copy of Code
Warrior from Metrowerks. The supplied StarGen.prj file was created with
version 2.1 of Code Warrior and so should work with any version from the
last 5 years.

To build on Windows you will nee Visual C or to use the GNU development
tools from the command line.

To get more detailed documentation on building StarGen, feed the file
Manual2-Building.html in the help folder or directory to a Web browser or
Help viewer that reads HTML files.

JimB. aka Brons
Jim Burrows
Eldacur Technologies
brons@eldacur.com
http://www.eldacur.com/~brons/
