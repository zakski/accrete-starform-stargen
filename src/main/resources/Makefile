# Makefile for "starform", a star system and planet generator

# Change the following if your C compiler isn't called 'cc' (note that on Linux the default compiler is gcc but it can still be run as cc).
CC=g++

# For those machines in which the rand() function returns a long int, and for
# some reason RAND_MAX isn't defined in the standard headers, put a LONG_RAND
# flag into the CFLAGS line that you use.  For instance, uncomment and use the
# next line for a normal version of the program:
CFLAGS = -g -O -DLONG_RAND -Wall -DMOON

# To make a normal version for machines with rand() returning 16-bit numbers,
# or with RAND_MAX defined in standard headers (as ANSI/ISO C says it should):
#CFLAGS = -O

# These next lines must always be uncommented:
OBJS = accrete.o enviro.o display.o utils.o steltype.o propert.o \
       gensys.o data.o
LIBS = -lm

# rule to make a .o file from a .c file
.c.o:
	$(CC) -c $(CFLAGS) $*.c

# Targets:

all:	starform

starform: starform.o $(OBJS)
	$(CC) $(CFLAGS) -o starform starform.o $(OBJS) $(LIBS)
	@echo "starform made"

clean:
	rm -f *.o starform

lint:
	lint -abchp starform.c accrete.c enviro.c display.c utils.c

SHARFILES = README INSTALL EXAMPLE TODO starform.mak Makefile \
            accrete.c   data.h      enviro.h    propert.h   structs.h \
	    accrete.h   display.c   gensys.c    starform.c  utils.c \
	    const.h     display.h   gensys.h    steltype.c  utils.h \
	    data.c      enviro.c    propert.c   steltype.h  elements.dat


shar:	$(SHARFILES)
	shar -abcCs $(SHARFILES) >starform.shar

tar:	$(SHARFILES)
	tar cvf starform.tar $(SHARFILES)

tgz:	$(SHARFILES)
	tar cvf - $(SHARFILES) | gzip > starform.tgz

zip:	$(SHARFILES)
	zip starform.zip $(SHARFILES)

rmarc:
	rm -f starform.shar starform.tar starform.tgz starform.zip

# Dependencies

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

