# ACRETE (C++)

Steve wrote a port of his original basic code to c++. Like his original basic code, its pretty interesting to see code
that has not evolved along the burdick branch.

## Basic Assumptions:

- see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

## Features
- Generates a variety of primary stars, based on some probability of their occurrence and bounded by the max and minimum
  mass that was estimated to potentially harbour planets in a stable system at the time..

- see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)


## Limitations:

see [notes on Dole's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1969%20-%20Formation%20of%20Planetary%20Systems%20by%20Aggregation.md)

### In Recreation:
- Source Code is complete.
- 
- Includes its own random number generator

### With the Model:
- I don't think there are any changes to Dole's accretion model. It's all in the one file so it's hard to be sure.

## Compilation
This is pre-ISO C++, so cannot be compiled by gcc/visualcpp as is. It needs a changes from a void returning main method,
to an int one.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/gilham.md) for the status on Gilham's latest code