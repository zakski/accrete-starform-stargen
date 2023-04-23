# Stargen (C/Fortran)

A snapshot of omega13a's version of Stargen that he put on his Star Trek fan site. It's based on a missing intermediate
stage published by a guy called Selden.

## Basic Assumptions:

- see [previous version](/docs/notes/build%20descriptions/2000s/2008%20-%20Burrows.2008.md).

## Features

- see [previous version](/docs/notes/build%20descriptions/2000s/2008%20-%20Burrows.2008.md).

- Substantially expanded the information included when writing Celestia SSC catalogs.
    - The gas giant oblateness algorithm was adapted from an example provided by Grant Hutchison on the Celestia Web
      Forum.
    - The gas giant/brown dwarf radius algorithm was adapted from Fig.4 of "Giant Planet Interior Structure and Thermal
      Evolution", Fortney et al. (2009)

- Replaced JimB's table of various star systems with a table of those mentioned in the Alliance-Union merchanter stories
  by C.J. Cherryh.

- The stellar mass-to-luminosity algorithm was replaced with a more sophisticated version adapted from values provided
  by Jenab6 in the discussion of the Wikipedia article on stellar mass/luminosities
  at http://en.wikipedia.org/wiki/Talk:Mass%E2%80%93luminosity_relation

- Fixed some bugs regarding moons.

- Have the none gas worlds be made out of some combination of iron, rock, and ice.

- Greatly improved the algorithm that determines the radius of gas giants.

- Added more stars to the catalogs

## Limitations:

- see [previous version](/docs/notes/build%20descriptions/2000s/2008%20-%20Burrows.2008.md).

- Removed limitation on stellar masses.

### In Recreation:

- Source Code is complete.

## Compilation

Compiles.

> All of these features are available when using make to build with
> Cygwin and gcc4 under Windows for invocation from a bash shell command
> line. No attempt has been made to provide a GUI(*) or to ensure
> compatibility with any other build environments, although building
> under Linux should work.

From the Readme.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/partly-github/amaro.md) for the status on Omega13a's latest
code.

## Runtime Options

- see [previous version](/docs/notes/build%20descriptions/2000s/2008%20-%20Burrows.2008.md).

- Reorganized and expanded the command-line option help text to include previously unmentioned options.

- Added options to vary a couple of Accrete parameters.

- Removed redundant options for selecting internal star system tables.
