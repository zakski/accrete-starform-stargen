# Starform (C)

This is Matt Burdick's original Starform code, hacked about by Keris with additions for atmospheric composition

## Basic Assumptions:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

## Features
- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

- day/night and maximum/minimum temperatures for rocky (not gas giant) worlds. The algorithm was stolen shamelessly from
  Stephen Kimmel's "World Builder" BASIC program, and then hacked about until it gave the sort of results keris' other
  simulations produce.

- Added stuff to list what materials are liquid on the planets' surface and what gasses might be in the atmosphere (if any).

-  ad-hoc moon generation stuff, if you define 'MOON' when compiling (add '-DMOON' to the CFLAGS variable in the makefile) then you'll
   get moons generated as well. 

- cut-down star generation from Keris' dabblings with Folkins code.

## Limitations:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

- temperature calculations for day/night max/min temps for rocky planets may not be scientfic.

- materials / gasses in atmosphere is complete guess work.

- moon generation is not scientifically based

### In Recreation:
- Source Code is complete.

## Compilation
Converted to use ANSI C function prototypes, and have a header file for each module containing the exported functions 
and variables.

Made more modular, so that modules are not using data from modules that call them (and hopefully not calling functions 
'upward' either).

Put the 'main' function as the only thing in starform.c, so that (hopefully) all the other modules can be called by 
other programs.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/partly-github/keris.md) for the status on Keris' latest code.