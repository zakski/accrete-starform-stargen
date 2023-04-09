# Accrete2 (C++)

A second version based on Andrew Folkins' code, further hacked about by Keris.

## Basic Assumptions:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

## Features
- Generates a variety of primary stars, initially based on probability tables provided to Folkins by John Carr in 1988.
  Since converted by Keris to MKS units, and additional characteristics added.

- Rudimentary moon and tide calculations.

- Added Star / Planetary classifications

- Adds in functions from Fogg's paper

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

## Limitations:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

- need to check scentific backing for lunar/tidal/star classification/planetary classification.

### In Recreation:
- Source Code is complete.

## Compilation
Does not compile as is. Compilers seem to miss <xstring.h> and seem to find several undefined identifiers. Could be the 
versions I'm using are too modern to work without modification.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/folkins.md) for the status on Folkins/Keris' latest 
code.