# Starform (C)

port of Keris's starform code to modernish ansi C standards.

Also includes a partial? port to Standard ML. Not all that useful so I left it in the zip.

Lyons had the following goals:

1. To have a good quality, documented, readable, comprehensible implementation
   of Accrete, useful for personal study, expansion, testing, embedding, and
   in general playing.

2. To showcase a high-quality codebase that can be used to direct ports to
   other languages as well as embed or call from other languages.

3. To showcase modern C99 style and achieve an implementation that compiles
   without a lot of work under modern Unix operating systems, and Plan 9 (the
   supra-modern Unix).

## Basic Assumptions:

- see [previous](/docs/notes/build descriptions/2000s/2000%20-%20Keris.2000.B.md)

## Features
- see [previous](/docs/notes/build descriptions/2000s/2000%20-%20Keris.2000.B.md)

- General refactoring, including renaming functions, breaking large functions
  into smaller ones, narrowing interfaces and interdependencies, and refining
  code responsibilities

- Removing support for MS-DOS and other obscure/useless platforms I dislike.

- Making the code more "objecty," removing global variables, doing less
  up-front calculation in favor of lazier alternatives where possible.

- Making starform into libstarform and changing the original utility into
  a shell that simply calls this library.

## Limitations:
- see [previous](/docs/notes/build descriptions/2000s/2000%20-%20Keris.2000.B.md)

### In Recreation:
- Source Code is complete.

## Compilation
includes sys/time.h so it won't compile as is on windows

Netbeans project support

Includes Unit Tests.

see [here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/keris.md) for the status on Keris' latest code.