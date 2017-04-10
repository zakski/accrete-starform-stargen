# This is a makefile for the Microsoft QuickC version of "starform",
# a star system and planet generator

CC=qcl

# To make a version for debugging or tracing, uncomment this line:
#CFLAGS = /Zi

# To make a normal optimized version, uncomment this line:
CFLAGS = /Ox

# To make a codeview-debuggable executable, uncomment this line:
#LINKFLAGS = /CODEVIEW

# This line should always be uncommented:
OBJS = accrete.obj enviro.obj display.obj utils.obj

.c.o:
	$(CC) /c $(CFLAGS) $*.c

starform.exe: starform.obj $(OBJS)
	link $(LINKFLAGS) starform.obj $(OBJS);

accrete.o:	accrete.c const.h structs.h accrete.h utils.h data.h
data.o:		data.c data.h const.h
display.o:	display.c structs.h const.h propert.h enviro.h data.h
enviro.o:	enviro.c const.h structs.h utils.h data.h
gensys.o:	gensys.c const.h structs.h accrete.h utils.h data.h enviro.h \
		display.h steltype.h
propert.o:	propert.c propert.h elements.dat
starform.o:	starform.c const.h structs.h gensys.h accrete.h utils.h \
		data.h enviro.h display.h steltype.h propert.h
steltype.o:	steltype.c
utils.o:	utils.c const.h

