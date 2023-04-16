all:	starform tests/progs/steltype-test

# User-tunables: the flags
CFLAGS := $(CFLAGS) -g -std=c99 -DLONG_RAND -Wall -Wextra
LDFLAGS := -g -lm

# Our sources. If you add one, add it here.
SOURCES := $(wildcard *.c)

OBJECTS := ${SOURCES:.c=.o}

.depend: $(wildcard *.c *.h)
	$(CC) -MM -E *.c *.h tests/progs/*.c tests/progs/*.h > $@

include .depend

starform: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/progs/steltype-test: tests/progs/steltype-test.o steltype.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o tests/progs/*.o starform tests/progs/steltype-test
