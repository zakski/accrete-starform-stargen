// D.U.M.A.S Debug Utility for the Memory Allocation Subsystem
// Copyright © 1993, World Benders, Inc. All Rights Reserved.
//

#if MEMORY_CHECK

// Routines that replace standard alloc/free routines

void *dumasMalloc (long reqestedBytes, char *moduleName, long lineNo);
void *dumasCalloc (long requestedItems, long itemSize, char *moduleName, long lineNo);
void *dumasRealloc (void *oldPtr, long requestedBytes, char *moduleName, long lineNo);
void dumasFree (void *vptr, char *moduleName, long lineNo);

// Externally callable verification routines.

void dumasCheckPtr (void *oldPtr, char *moduleName, long lineNo);
void dumasDumpHoard (void);
void dumasVerifyHoard (void);

// The following routine is Meeting Spaceª specific...

#ifdef MEETING_SPACE_H
char *dumasDupString (char *string, char *moduleName, long lineNo);
#endif

#ifndef IM_BEING_CALLED_FROM_DUMAS_ITSELF
#ifdef MACINTOSH
#define malloc(x)		dumasMalloc (x, NULL, __LINE__)
#define calloc(x,y)		dumasCalloc (x, y, NULL, __LINE__)
#define realloc(x,y)	dumasRealloc (x, y, NULL, __LINE__)
#define free(x)			dumasFree (x, NULL, __LINE__)

#define dup_string(x)	dumasDupString (x, NULL, __LINE__)

#else

#define malloc(x)		dumasMalloc (x, __FILE__, __LINE__)
#define calloc(x,y)		dumasCalloc (x, y, __FILE__, __LINE__)
#define realloc(x,y)	dumasRealloc (x, y, __FILE__, __LINE__)
#define free(x)			dumasFree (x, __FILE__, __LINE__)

#define dup_string(x)	dumasDupString (x, __FILE__, __LINE__)

#endif
#endif

extern long		monteCristoCount;
extern int		dumasFlags;

#define DUMAS_ACTIVE			0x01
#define DUMAS_VERIFY_FREES		0x02
#define DUMAS_VERIFY_ALLOCS		0x04
#define DUMAS_DO_HISTORY		0x08

#endif
