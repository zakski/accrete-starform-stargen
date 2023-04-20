# Makefile for "stargen", a star system and planet generator

# Change the following if your C compiler isn't called 'gcc' (note that on Linux 
# the default compiler is gcc but it can still be run as cc).
CC=gcc

# And change this to your fvorite C compiler flags:
CFLAGS = -O -g -W -Wall -D_USE_LIBM_MATH_H

# We use a lot of long doubles and Mac OS X currently warns you that they're
# thinking about changing these from 64 to 128 bits. To suppress that warning:

CFLAGS += -Wno-long-double

# StarGen comes with a copy of World Benders' portable memory checker, Dumas
# If you're debugging StarGen, you may want to uncomment the following line:

#CFLAGS += -DMEMORY_CHECK=1

OBJDIR = obj
OBJS = main.o stargen.o accrete.o display.o Dumas.o enviro.o utils.o

LIBS = -lm

.c.o:
	$(CC) -c $(CFLAGS) $*.c

# on Amiga, I'm told this should be:
#   $(CC) -c $(CFLAGS) $*.c -o $*.o

all:	stargen

stargen: $(OBJS)
	$(CC) $(CFLAGS) -o stargen $(OBJS) $(LIBS)
	@echo "stargen made"

clean:
	rm -f $(OBJS) stargen

lint:
	lint -abchp accrete.c display.c Dumas.c enviro.c stargen.c utils.c main.c

KITFILES  = Credits.txt ReadMe.txt help
SRCFILES  = accrete.c display.c Dumas.c enviro.c stargen.c utils.c main.c \
            accrete.h const.h display.h Dumas.h enviro.h structs.h \
            types.h stargen.h utils.h \
            mac_prefix.h StarGen.r StarGen.prj Makefile \
            StarGen.dsw StarGen.dsp Stargen.rc resource.h

MACFILES    = StarGen\ 68K StarGen\ PPC stargen $(KITFILES) ref
OSXFILES    = stargen $(KITFILES) ref
WINEXEFILES = WinStarGen.exe StarGen.exe \
              mfc80u.dll msvcr80.dll \
              $(KITFILES) ref/*
SHARFILES   = $(KITFILES) $(SRCFILES) ref/*

zip:	$(SHARFILES) $(WINEXEFILES)
	mkdir new-html
	mv html html-safe
	mv new-html html
	zip StarGenSource.zip $(SHARFILES) html
	zip WinStarGen.zip $(WINEXEFILES) html
	zip MacStarGen.zip $(OSXFILES) html
	mv html new-html
	mv html-safe html
	rm -rf new-html

sit:	$(MACFILES) $(SHARFILES)
	mkdir new-html
	mv html html-safe
	mv new-html html
	stuff -o -n StarGenSource.sit $(MACFILES) $(SRCFILES) html
	stuff -o -n StarGen.sit $(MACFILES) html	
	mv html new-html
	mv html-safe html
	rm -rf new-html

rmarc:
	rm -f StarGenSource.zip WinStarGen.zip StarGenSource.sit StarGen.sit

accrete.o:	const.h structs.h accrete.h stargen.h utils.h Dumas.h
display.o:	const.h structs.h enviro.h display.h stargen.h
Dumas.o:	Dumas.h
enviro.o:	const.h structs.h enviro.h stargen.h utils.h
stargen.o:	const.h structs.h enviro.h display.h accrete.h stargen.h utils.h Dumas.h
utils.o:	const.h utils.h
stargen.o:	const.h structs.h enviro.h accrete.h stargen.h Dumas.h

