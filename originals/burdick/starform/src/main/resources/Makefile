# Makefile for "starform", a star system and planet generator
CC = /bin/cc
CFLAGS = -O
OBJS = starform.o accrete.o enviro.o display.o utils.o
LIBS = -lm
SHARFILES = README starform.mak Makefile starform.c accrete.c enviro.c display.c utils.c const.h structs.h config.h


.c:
        $(CC) $(CFLAGS) -c $@.c

starform: $(OBJS)
        $(CC) $(CFLAGS) -o starform $(OBJS) $(LIBS)
        @echo "starform made "

clean:
        rm -f *.o *.ln *.x

clobber:
        rm -f *.o *.ln *.x starform

lint:
        lint -abch starform.c accrete.c enviro.c display.c utils.c

shar: $(SHARFILES)
        shar -abcCs $(SHARFILES) >starform.shar

