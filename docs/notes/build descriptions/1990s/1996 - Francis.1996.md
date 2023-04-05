# Accrete (C)

Erik Max Francis produced a slightly modified version of Burdick's code that prints it's output slightly differently. It
seems to extends from the first generation code line.

I am unsure as to which of Burdick.1994.A and Nyrath.1995 is the closest to being the actual parent. However I have a
strong opinion that it extends from Nyrath's original source.

## Basic Assumptions:

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

## Features

- see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)


## Limitations:

see [notes on Fogg's paper](/docs/notes/build%20descriptions/1960s%20-%201980s/1985%20-%20Extra-Solar%20Planetary%20Systems.md)

### In Recreation:
- Source Code is complete.

- Francis? made changes to output collision events and the like to stderr

- like Nyrath's version, the Earth's albedo was changed from 0.3 to 0.39

- like Nyrath's version, PI was removed

- surface accleration and greenhouse effect printouts are commented out

## Compilation
Source Code is written in C. As is, it may need modifications to run on modern systems. It has a makefile, but the
compiler may need to be persuaded as to what PI is. A switch was made to output the data as a file, rather than on
console.

In it's makefile, changes are made to use -msfloat, and gcc rather than cc.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/burdick%20-%20accrete%20-%201.x%20-%20core.md) for 
the status on Burdick's latest accrete code

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/burdick%20-%20accrete%20-%201.x%20-%20variants.md) 
for the status on variants of Burdick's accrete code