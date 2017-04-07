#
# Borland C++ IDE generated makefile
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LFLAGSDOS =  -LC:\BC45\LIB
IDE_BFLAGS = 
CDOSOptimized_lSizer =  -O-d -O -Ob -Oe -Os -Ol -Oc -k- -Z
LDOSOptimized_lSizer = 
RDOSOptimized_lSizer = 
BDOSOptimized_lSizer = 
CNATDOS_origaccrdexe = $(CDOSOptimized_lSizer)
LNATDOS_origaccrdexe = $(LDOSOptimized_lSizer)
RNATDOS_origaccrdexe = $(RDOSOptimized_lSizer)
BNATDOS_origaccrdexe = $(BDOSOptimized_lSizer)
CLATDOS_origaccrdexe =  -ml -f287 -A- -Og
LLATDOS_origaccrdexe =  -c -Tde
RLATDOS_origaccrdexe = 
BLATDOS_origaccrdexe = 
CEAT_origaccrdexe = $(CNATDOS_origaccrdexe) $(CLATDOS_origaccrdexe)
CNIEAT_origaccrdexe = -IC:\BC45\INCLUDE -D
LNIEAT_origaccrdexe = -x
LEAT_origaccrdexe = $(LNATDOS_origaccrdexe) $(LLATDOS_origaccrdexe)
REAT_origaccrdexe = $(RNATDOS_origaccrdexe) $(RLATDOS_origaccrdexe)
BEAT_origaccrdexe = $(BNATDOS_origaccrdexe) $(BLATDOS_origaccrdexe)
CNATDOS_accretedexe = $(CDOSOptimized_lSizer)
LNATDOS_accretedexe = $(LDOSOptimized_lSizer)
RNATDOS_accretedexe = $(RDOSOptimized_lSizer)
BNATDOS_accretedexe = $(BDOSOptimized_lSizer)
CLATDOS_accretedexe =  -ml -f287
LLATDOS_accretedexe =  -c -Tde
RLATDOS_accretedexe = 
BLATDOS_accretedexe = 
CEAT_accretedexe = $(CNATDOS_accretedexe) $(CLATDOS_accretedexe)
CNIEAT_accretedexe = -IC:\BC45\INCLUDE -D
LNIEAT_accretedexe = -x
LEAT_accretedexe = $(LNATDOS_accretedexe) $(LLATDOS_accretedexe)
REAT_accretedexe = $(RNATDOS_accretedexe) $(RLATDOS_accretedexe)
BEAT_accretedexe = $(BNATDOS_accretedexe) $(BLATDOS_accretedexe)

#
# Dependency List
#
Dep_accrete = \
   origaccr.exe\
   accrete.exe

accrete : BccDos.cfg $(Dep_accrete)
  echo MakeNode 

Dep_origaccrdexe = \
   enviro.obj\
   display.obj\
   accrete.obj\
   main.obj

origaccr.exe : $(Dep_origaccrdexe)
  $(TLINK)   @&&|
 /v $(IDE_LFLAGSDOS) $(LEAT_origaccrdexe) $(LNIEAT_origaccrdexe) +
C:\BC45\LIB\c0l.obj+
enviro.obj+
display.obj+
accrete.obj+
main.obj
$<,$*
C:\BC45\LIB\fp87.lib+
C:\BC45\LIB\mathl.lib+
C:\BC45\LIB\cl.lib

|

enviro.obj :  enviro.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_origaccrdexe) $(CNIEAT_origaccrdexe) -o$@ enviro.cpp
|

display.obj :  display.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_origaccrdexe) $(CNIEAT_origaccrdexe) -o$@ display.cpp
|

accrete.obj :  accrete.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_origaccrdexe) $(CNIEAT_origaccrdexe) -o$@ accrete.cpp
|

main.obj :  main.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_origaccrdexe) $(CNIEAT_origaccrdexe) -o$@ main.cpp
|

Dep_accretedexe = \
   dustband.obj\
   planet.obj\
   system.obj\
   main2.obj

accrete.exe : $(Dep_accretedexe)
  $(TLINK)   @&&|
 $(IDE_LFLAGSDOS) $(LEAT_accretedexe) $(LNIEAT_accretedexe) +
C:\BC45\LIB\c0l.obj+
dustband.obj+
planet.obj+
system.obj+
main2.obj
$<,$*
C:\BC45\LIB\fp87.lib+
C:\BC45\LIB\mathl.lib+
C:\BC45\LIB\cl.lib

|

dustband.obj :  dustband.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_accretedexe) $(CNIEAT_accretedexe) -o$@ dustband.cpp
|

planet.obj :  planet.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_accretedexe) $(CNIEAT_accretedexe) -o$@ planet.cpp
|

system.obj :  system.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_accretedexe) $(CNIEAT_accretedexe) -o$@ system.cpp
|

main2.obj :  main2.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_accretedexe) $(CNIEAT_accretedexe) -o$@ main2.cpp
|

# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-R
-v
-vi
-H
-H=accrete.csm
| $@


