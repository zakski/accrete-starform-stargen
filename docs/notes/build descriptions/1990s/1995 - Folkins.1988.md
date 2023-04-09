# ACCRETION (C)

Folkins' program implements the accretion algorithm given by Dole. He's tried to simplify the computations a bit, these 
instances are noted in the code comments.

## Basic Assumptions:

- see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

## Features
- Generates a variety of primary stars, based on probability tables provided to Folkins by John Carr in 1988.

- Change from straight firing in planetesimals at random, to only doing that for the first 20 or so, then adds the rest
  around the remaining dust bands

- see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

## Limitations:

see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

### In Recreation:
- Source Code is complete.

### With the Model:

- Favored a simple Bodes-law style simulation rather than Dole's one.

## Compilation
This is C code is written as a port of the program for the amiga. So I'm not going to try to compile it.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/folkins.md) for the status on Folkins/Keris' latest 
code.