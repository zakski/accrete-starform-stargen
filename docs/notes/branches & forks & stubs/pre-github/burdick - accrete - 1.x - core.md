# Matt Burdick Accrete Branch

## Up-to-Date Compile/Run Status

- Module: Yes, burdick-accrete
- Latest Version: Keel.1999.A
- Compiles:
  - On Mac: ???, written in C.
  - On Windows: Fails using gradle/Visualcpp.
  - On Linux (WSL2): Passes using gcc.
- Runs:
  - On Linux (WSL2): Runs successfully.

## Versions

### [ACCRETION](http://znark.com/create/accrete.html)

- Resource Name: 1994 - Matt Burdick - Accretion
- Author: Matt Burdick
- Poster/Publisher: Ian Burrell
- Language: Turbo Pascal
- Creation Year: 1988
- Source Year: 1994
- Parents: Fogg.1985
- Original Source: Acquired.
- Reproducibility: [Reproducible.](/docs/notes/build%20descriptions/1990s/1994%20-%20Burdick.1988.md)
- Burdick Version: 1.x
- Key: Burdick.1988

Mat Burdick's simulation reversed engineered from Dole and Fogg's papers. The main fork of source code that everyone
seems to of worked off.

This pretty close to being the original copy of Mat Burdick's first version, In that it is written in pascal which
apparently is his original language and the comments mention copyright 1988. However the fact that the source code was
found on Ian Burrell's website and the files were last modified in 1994 count against it being the very first
version. Additionally the zip file was also labelled accretion, which has never been a name that Burdick has called it.

Burdick could only partially reproduce Fogg's work, since the way that Fogg determined the atmosphere type is not
cleared marked out in his research paper.

Nevertheless, this codebase is the parent of the vast majority of variations that have any source code still extant.

#### Compile/Run Status
- Compiles:
  - On Mac: ???, written in Turbo Pascal.
  - On Windows: ???, written in Turbo Pascal.
  - On Linux (WSL2): ???, written in Turbo Pascal.
- Runs:
  - N/A

### [Accrete](https://groups.google.com/forum/#!topic/rec.arts.sf.science/2Xm6WP5n1F8)

- Resource Name: 1988 - Matt Budick - Accrete -  Steve Gilham Incomplete
- Author: Matt Burdick
- Poster/Publisher: Steve Gilham
- Language: C
- Creation Year: >= 1988
- Source Year: 1993
- Parent: Burdick.1988
- Original Source: Incomplete.
- Reproducibility: [Partially Reproducible](/docs/notes/build%20descriptions/1960s%20-%201980s/1988%20-%20Gilham.1988.md).
- Burdick Version: None
- Key: Gilham.1988

A version of Matt Burdick's code, ported by him to C from pascal. Was posted to a usernet newsgroup by Steve
Gilham. Whilst it does seem to date back to 1988, the end of Gilham's post was cut off in the Google Group archive, so
the code is incomplete.

#### Compile/Run Status
- Compiles:
    - On Mac: No, code is incomplete.
    - On Windows: No, code is incomplete.
    - On Linux (WSL2): No, code is incomplete.
- Runs:
    - N/A

### [ACCRETE](http://znark.com/create/files/accrete.zip)
- Resource Name: 1994 - Matt Burdick - Accrete
- Author: Mat Burdick
- Poster/Publisher: Ian Burell
- Language: C
- Creation Year: >= 1988
- Source Year: 1994
- Parents: Gilham.1988
- Original Source: Complete.
- Reproducibility: [Reproducible.](/docs/notes/build%20descriptions/1990s/1994%20-%20Burdick.1994.A.md)
- Burdick Version: 1.x
- Key: Burdick.1994.A

One of Mat Burdick's C versions which is commonly distributed as accrete.
 
This looks like the same major version as the incomplete code gilham supplied so it should make for an interesting 
comparison.  

#### Compile/Run Status
- Compiles:
  - On Mac: ???, written in C.
  - On Windows: Fails using Visualcpp.
  - On Linux (WSL2): Fails using gcc.
- Runs:
  - N/A

### [ACCRETE](http://reocities.com/CapeCanaveral/8191/usml.html)
- Resource Name: 1995 - Nyrath - Accrete
- Author: Matt Burdick
- Poster/Publisher: Nyrath the nearly wise
- Language: C
- Creation Year: >= 1988
- Source Year: 1995
- Parents: Burdick.1994.A
- Original Source: Acquired.
- Reproducibility: [Reproducible.](/docs/notes/build descriptions/1990s/1995%20-%20Nyrath.1995.md).
- Burdick Version: 1.x
- Key: Nyrath.1995

Nyrath, like Burrell and a few others, has a cached copy of Burdick's accrete program. This version is dated as been 
last modified later than Burrell's copy, so we have a potential version order between them.

#### Compile/Run Status
- Compiles:
  - On Mac: ???, written in C.
  - On Windows: Fails using gradle/Visualcpp.
  - On Linux (WSL2): Fails using gcc.
- Runs:
  - N/A

#### Compile/Run Status With Modification
- Compiles:
  - On Mac: ???, written in C.
  - On Windows: Fails using gradle/Visualcpp.
  - On Linux (WSL2): Passes using gcc.
- Runs:
  - On Linux (WSL2): Runs successfully.

### [Accrete](http://seegras.discordia.ch/Roleplay/Traveller/Software/Accrete.tgz)
- Resource Name: 1999 - Peter Keel - Accrete
- Author: Matt Burdick
- Poster/Publisher: Peter Keel
- Language: C
- Creation Year: >= 1988
- Source Year: 1999
- Parents: Nyrath.1995
- Original Source: Acquired.
- Reproducibility: [Reproducible](/docs/notes/build descriptions/1990s/1999%20-%20Keel.1999.A.md).
- Burdick Version: 1.x
- Key: Keel.1999.A

A version cached by Peter Keel on his traveller rpg site.

#### Compile/Run Status
- Compiles:
  - On Mac: ???, written in C.
  - On Windows: Fails using gradle/Visualcpp.
  - On Linux (WSL2): Passes using gcc.
- Runs:
  - On Linux (WSL2): Runs successfully.

## Follow Up
The main progression of the source code continues 
[here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/burdick%20-%20accrete%20-%203.x%20-%20starform.md) with Starform. Best guess is 
it actually splits off from this 1.x branch in the late 80s to early 90s from code that looks similar to the 
Burdick.1994.A variant.

Alternate progression of the source code continues
[here](/docs/notes/branches%20&%20forks%20&%20stubs/pre-github/webb.md), splitting off at Nyrath.1995.