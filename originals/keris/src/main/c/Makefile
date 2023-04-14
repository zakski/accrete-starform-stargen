# Makefile for "starform", a star system and planet generator

# To make a version for debugging or tracing, uncomment this line:
#CFLAGS = -g

# For those machines in which the rand() function returns a long int, put
# a LONG_RAND flag into the CFLAGS line that you use.  For instance, uncomment 
# and use the next line for a normal version of the program:
CFLAGS = -O -DLONG_RAND

# To make a version for machines with rand() returning 16-bit numbers. 
# UNIX will barf on this. 
# CFLAGS = -O 

# These two lines should always be uncommented:
OBJS = accrete.o enviro.o display.o utils.o
LIBS = -lm


starform: starform.o $(OBJS)
	cc $(CFLAGS) -o starform starform.o $(OBJS) $(LIBS)

accrete.o: accrete.c const.h structs.h
	cc -c $(CFLAGS) accrete.c

enviro.o: enviro.c const.h structs.h
	cc -c $(CFLAGS) enviro.c

display.o: display.c const.h structs.h
	cc -c $(CFLAGS) display.c

utils.o: utils.c const.h
	cc -c $(CFLAGS) utils.c

starform.o: starform.c const.h structs.h
	cc -c $(CFLAGS) starform.c

clean:
	rm -f *.o

lint:
	lint -abchp starform.c accrete.c enviro.c display.c utils.c

SHARFILES = README starform.mak Makefile starform.c accrete.c enviro.c display.c utils.c const.h structs.h

shar: $(SHARFILES)
	shar -abcCs $(SHARFILES) >starform.shar

