CFLAGS = -g # -DDEBUG

SRC = dole.c list.c planetstat.c main.c genstar.c
OBJ = $(SRC:.c=.o)
LIB = -lm

all:	mkstars

mkstars:	$(OBJ)
	gcc -g -o mkstars $(OBJ) $(LIB)

clean:
	rm -f $(OBJ) mkstars a.out *~

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
