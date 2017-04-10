# makefile for Accrete C++ using Dole's algorithm
#
# $Id: makefile,v 2.7 2000/02/21 11:37:06 chrisc Exp $
#
# $Log: makefile,v $
# Revision 2.7  2000/02/21 11:37:06  chrisc
# More changes to cin and cout rules, added Id and Log RCS comments
#

CFLAGS = -g # -DDEBUG

SRC = dole.cc planetstat.cc genstar.cc parsefrm.cc
ARC = $(SRC) \
      main.cc \
      tides.cc \
      atmos.cc \
      const.h system.h parsefrm.h elem.h elem.ch \
      makefile README CHANGES \
      findhab classify \
      RCS/*
OBJ = $(SRC:.cc=.o)
LIB = -lXLIB -lm

EXE = mkstars atmos

.cc.o:
	g++ -g -c $<

all:	$(EXE)

mkstars:	main.o $(OBJ)
	g++ -g -o mkstars main.o $(OBJ) $(LIB)

atmos:	atmos.cc parsefrm.o
	g++ -o atmos -g -DTEST atmos.cc parsefrm.o $(LIB)
	
clean:
	@-rm -f *.o $(EXE) atmos mkstars a.out *~ core

distclean: clean

arc:
	tar cvf - $(ARC) | gzip > $(HOME)/keris/stars/doleplus.tgz
	rm -f $(HOME)/keris/stars/doleplus.zip
	zip -9 $(HOME)/keris/stars/doleplus.zip $(ARC)

dist:	cin arc cout

cin:
	@-for a in RCS/*; do \
	  if rcsdiff -w -c $$a > 1 2>1; \
	  then \
	    ci -q -u $$a; \
	  else \
	    cat 1; \
	    ci -u $$a; \
	  fi; \
	  rm 1; \
	done

cout:
	@-for a in RCS/*; do \
	  co -l -q $$a < /dev/null; \
	done
	

ci:
	@-for a in RCS/*; do \
	  if rcsdiff -w -c $$a > 1 2>1; \
	  then \
	    rm 1; \
	  else \
	    cat 1; \
	    ci $$a; \
	    co -l $$a < /dev/null; \
	  fi; \
	done

atmos.o:	atmos.cc parsefrm.h
dole.o:		dole.cc system.h const.h
genstar.o:	genstar.cc system.h
humidity.o:	humidity.cc
main.o:		main.cc system.h const.h
parsefrm.o:	parsefrm.cc parsefrm.h elem.ch
planetstat.o:	planetstat.cc system.h const.h parsefrm.h

