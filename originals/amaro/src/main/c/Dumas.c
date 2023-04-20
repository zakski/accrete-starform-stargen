// D.U.M.A.S Debug Utility for the Memory Allocation Subsystem
// Copyright © 1993, World Benders, Inc. All Rights Reserved.
//
// Just as Edmond Dantès disguised himself to catch the disloyal M. Danglars, so
// DUMAS disguises itself to catch dangling memory references. Like the disguised
// Comte de la Fere, who brought the two-timing milady deWinter to justice, so
// DUMAS seeks and punishes those who doubly deallocate. Where Dantès became
// the Count of Monte-Cristo, Sinbad the Sailor, Abbé Busoni, and Lord Wilmore,
// DUMAS becomes malloc, calloc, realloc and free. As Dantès was guarded in
// the Château d'If, so each allocated item is protected by a guard and a sentinel
// to detect corruption (overwriting from below) and a wall to protect against
// escaping (writing beyond the end of the item). And as Dantès' mentor kept a
// history, so does DUMAS.
//
// This version ought to be platform independant. There is code in here espcially
// for the Macintosh and for Windows-32, but the generic ANSI C code should work
// everywhere.
//
// $Id: Dumas.c,v 1.2 2003/12/31 19:36:44 brons Exp $

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __MWERKS__							// Define OS macro for Mac's
#define MACINTOSH 1
#endif

#ifdef THINK_C
#include <types.h>
#include <LoMem.h>
#define MACINTOSH 1
#endif

#ifdef WIN32
#include <windows.h>
#endif

#define IM_BEING_CALLED_FROM_DUMAS_ITSELF 1

//#include "MeetSpac.h"

#undef MEMORY_CHECK
#define MEMORY_CHECK 1
#include "Dumas.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

#define	MAX_DUMP	20

#ifdef MACINTOSH
#ifndef __POWERPC__
#define HISTORY_SIZE	128
#define DEFAULT_FLAGS	DUMAS_DO_HISTORY | DUMAS_ACTIVE
#else
#define HISTORY_SIZE	0
#define DEFAULT_FLAGS	DUMAS_ACTIVE
#endif
#else
	#define HISTORY_SIZE	0
	#define DEFAULT_FLAGS	DUMAS_ACTIVE
#endif

int		dumasFlags = DEFAULT_FLAGS;

//	4	0	0		Sentinel
//	4	1	4		Next
//	40	2	8		Name (default is __FILE__, procedure name if known)
//	4	12	48		Line (__LINE__)
//	4	13	52		Length
//	64	14	56		History
//	4	30	120		Guard
//	n	31	124		Data
//	4		n+124	Wall

//	The history field above is optional. On systems where we have the knowledge to
//	trace back up the call tree, HISTORY_SIZE is non-zero and dumasCallerName,
//	dumasCallHistory, and some routine to get the frame-pointer are used.

#define	ALLOCATED	0xAAAAAAAA
#define	DEALLOCATED	0xDDDDDDDD
#define	BEGINNING	0xBBBBBBBB
#define MIDDLE		0xCCCCCCCC
#define ENDING		0xEEEEEEEE

#define NAME_SIZE		40
#define COMPLAINT_SIZE	80

// The Château d'If structure, to keep track of each allocated chunk of memory.
// We record the name (either the routine's name as obtained by tracing back up the
// call frame stack or __FILE__) and line number (__LINE__) of the procureur of
// each chunk, and its length. A sentinel (a longword of 0xBBBBBBBB) is placed before
// the chunk, and a wall (four bytes of 0xEE) is placed after it. A guard (0xCCCCCCCC)
// is placed between the header and the data. If either the guard or sentinel becomes
// corrupted, we don't trust any of the rest of the structure as it was most probably
// corrupted from without by being overwritten.

typedef struct dumasDIf
{
	unsigned long	sentinel;				// Sentinel
	struct dumasDIf	*next;					// Next allocated item
	char			name[NAME_SIZE];		// Name of the procureur's routine or file
	long			line;					// Line number of allocation
	long			length;					// Length of the data portion
#if HISTORY_SIZE
	char			history[HISTORY_SIZE];	// Call history
#endif
	unsigned long	guard;					// Guard against corruption
	char			data[4];				// The data (variable size)
//	unsigned long	wall;					// Wall to keep it in. (4 bytes)
} dumasDIf;

// Dumas internal routines.

static void	dumasComplain (char *, char *, long, char *, long);
#define	BOOM(x) dumasComplain (x, segment->name, segment->line, callerName, lineNo)

// Routines that may crawl up the call frame stack.

static void *dumasAlloc (long requestedBytes, char *moduleName, long lineNo);
static void dumasCheckAndFree (void *oldptr, char *moduleName, long lineNo);
static int dumasCheckSegment (dumasDIf *, char *, long, int);

// Routines for crawling up the call-frame stack

#ifdef MACINTOSH
#ifndef __POWERPC__

static void dumasCallHistory (char *buffer, unsigned short maxLength, unsigned long *fp);

// This inline copies the value of A6 (the frame pointer) to D0. It is needed in
// order to get the caller's function name.

#ifdef THINK_C
	unsigned long *GetA6(void) = { 0x200E };	// move.l A6,D0
#else
	unsigned long *GetA6(void) = { 0x204E };	// move.l A6,A0

	#define	Declare_LoMem(type, name, address)	type (name) : (address)
	Declare_LoMem(Ptr, CurStackBase, 0x908);
	Declare_LoMem(Ptr, HeapEnd, 0x114);
#endif


static char *dumasCallerName (unsigned long *);
static unsigned short StoreString (const unsigned char *, unsigned short, unsigned short, char *);

#endif
#endif

// System specific routines

#ifdef MACINTOSH

#ifdef THINK_C
// A routine to ferret out the size that alloc cached

static int sizeof_ptr(void *ptr);

#endif

#endif

// Monte Cristo's hoard--a linked list off all memory that DUMAS has allocated.

dumasDIf *monteCristoHoard = NULL;			// It starts as barren as the isle
long	monteCristoCount = 0;				// But maintains a count, none the less.

// The following table is used to make the contents of the data portion printable.
// It is a table of 384 entries. Three Hundred and Eightyfour are used so that the
// table can be indexed by bo signed and unsigned chars. The first 128 entries and
// the last must be identical.
//
//	Control characters are replaced by a 'DOT', and nulls by a 'NOUGHT'

#ifdef MACINTOSH
#define DOT '•'
#define NOUGHT '◊'
#else
#define DOT '.'
#define NOUGHT '.'
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static unsigned char _dumasPrintable[] = {      
#ifdef MACINTOSH
         128,  129,  130,  131,  132,  133,  134,  135,	// The Macintosh character set 
         136,  137,  138,  139,  140,  141,  142,  143,	// has no C1 control characters
         144,  145,  146,  147,  148,  149,  150,  151,	// So these 32 are considered
         152,  153,  154,  155,  156,  157,  158,  159,	// to be printable
#else
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// In ISO Latin-1, 646, etc.
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// these codes are C1 controls
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// and as such, are considered
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// to be unprintable
#endif
         160,  161,  162,  163,  164,  165,  166,  167, 
         168,  169,  170,  171,  172,  173,  174,  175, 
         176,  177,  178,  179,  180,  181,  182,  183, 
         184,  185,  186,  187,  188,  189,  190,  191, 
         192,  193,  194,  195,  196,  197,  198,  199, 
         200,  201,  202,  203,  204,  205,  206,  207, 
         208,  209,  210,  211,  212,  213,  214,  215, 
         216,  217,  218,  219,  220,  221,  222,  223, 
         224,  225,  226,  227,  228,  229,  230,  231, 
         232,  233,  234,  235,  236,  237,  238,  239, 
         240,  241,  242,  243,  244,  245,  246,  247, 
         248,  249,  250,  251,  252,  253,  254,  DOT,	// We assume a 94 character set

// End of table entries for indexes -128 to -1. Now for the unsigned 256: 

      NOUGHT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT, 
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT, 
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT, 
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT, 
          32,   33,   34,   35,   36,   37,   38,   39, 
          40,   41,   42,   43,   44,   45,   46,   47, 
          48,   49,   50,   51,   52,   53,   54,   55, 
          56,   57,   58,   59,   60,   61,   62,   63, 
          64,   65,   66,   67,   68,   69,   70,   71,
          72,   73,   74,   75,   76,   77,   78,   79,
          80,   81,   82,   83,   84,   85,   86,   87,
          88,   89,   90,   91,   92,   93,   94,   95, 
          96,   97,   98,   99,  100,  101,  102,  103, 
         104,  105,  106,  107,  108,  109,  110,  111, 
         112,  113,  114,  115,  116,  117,  118,  119, 
         120,  121,  122,  123,  124,  125,  126,  127, 

#ifdef MACINTOSH
         128,  129,  130,  131,  132,  133,  134,  135,	// The Macintosh character set 
         136,  137,  138,  139,  140,  141,  142,  143,	// has no C1 control characters
         144,  145,  146,  147,  148,  149,  150,  151,	// So these 32 are considered
         152,  153,  154,  155,  156,  157,  158,  159,	// to be printable
#else
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// In ISO Latin-1, 646, etc.
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// these codes are C1 controls
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// and as such, are considered
         DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,  DOT,	// to be unprintable
#endif

         160,  161,  162,  163,  164,  165,  166,  167, 
         168,  169,  170,  171,  172,  173,  174,  175, 
         176,  177,  178,  179,  180,  181,  182,  183, 
         184,  185,  186,  187,  188,  189,  190,  191, 
         192,  193,  194,  195,  196,  197,  198,  199, 
         200,  201,  202,  203,  204,  205,  206,  207, 
         208,  209,  210,  211,  212,  213,  214,  215, 
         216,  217,  218,  219,  220,  221,  222,  223, 
         224,  225,  226,  227,  228,  229,  230,  231, 
         232,  233,  234,  235,  236,  237,  238,  239, 
         240,  241,  242,  243,  244,  245,  246,  247, 
         248,  249,  250,  251,  252,  253,  254,  DOT	// We assume a 94 character set
};

// Define a table that can tolerate indexs from -128 to 256, that is 128 into the 384

static char *dumasPrintable = (char *) &_dumasPrintable[128];

//////////////////////////////////////////////////////////////////////////////////
//
//	Dumas internal routines.
//

//	Issue a complaint about a problem found.
//	We are called with a complaint and the identities of the procureur and liberator

static void	dumasComplain (char *complaint,
							char *procureur_name, long procureur_line,
							char *liberator_name, long liberator_line)
{
	char	buffer[256];
	char	procureur[NAME_SIZE];
	char	liberator[NAME_SIZE];
	
	if (strlen (complaint) > COMPLAINT_SIZE)
		complaint [COMPLAINT_SIZE] = '\0';

// Take care that the procureur and liberator's names have not been overwritten.

	strncpy (procureur, procureur_name, NAME_SIZE-1);
	procureur[NAME_SIZE-1] = '\0';
		
	strncpy (liberator, liberator_name, NAME_SIZE-1);
	liberator[NAME_SIZE-1] = '\0';
		
// Format the complaint into the buffer

	*buffer = '\0';

	if (procureur && *procureur)
	{
		if (liberator_name && *liberator)
		{
			sprintf (buffer, "alloc: %s, (%ld), free: %s, (%ld): %s",
					 procureur,
					 procureur_line,
					 liberator,
					 liberator_line,
					 complaint);
		}
		else
		{
			sprintf (buffer, "alloc: %s, (%ld): %s",
					 procureur,
					 procureur_line,
					 complaint);
		}
	}
	else
	{
		if (liberator && *liberator)
		{
			sprintf (buffer, "free: %s, (%ld): %s",
					 liberator,
					 liberator_line,
					 complaint);
		}
		else
		{
			strcpy (buffer, complaint);
		}
	}	

// And now output the message and invoke the debugger

#ifdef MACINTOSH
//
// On the Macintosh, you pass the message when you invoke the debugger.
//
	CtoPstr (buffer);
	
	DebugStr ((unsigned char *) buffer);			// Invoke the debugger
#else
//
// Normally just output to stderr
//
	fputs (buffer, stderr);
	fflush (stderr);

#ifdef WIN32
	DebugBreak ();									// Signal WinDebug
#else
//
// And then do something grossly illegal in hopes we get caught.
//
{
	int i;
	
	i = (*((int *) NULL));						// Invoke the debugger, if any
}
#endif
#endif
}

//////////////////////////////////////////////////////////////////////////////////
//
//	Routines to do various types of checking and complaining.
//

//
//	Because of the way that the call frame is traced, this routine should always
//	be called by a routine that was called from outside Dumas. The caller will
//	be reported as being dumasCheckSegment's caller's caller.
//

static int dumasCheckSegment (dumasDIf *segment, char *moduleName, long lineNo, int dumping)
{
	char			*cptr;
	long			i;
	long			deserted = 0;
	long			poisoned = 0;
	char			*callerName = moduleName;
#if MACINTOSH
#ifndef __POWERPC__
	unsigned long	*fp;
#endif
#endif
	int				retval = TRUE;
#ifdef THINK_C
	long			the_size;
#endif

#if MACINTOSH
#ifndef __POWERPC__
	fp = GetA6();						// Get my stack frame
	if (fp)
	{
		fp = (unsigned long *) *fp;			//  and from that, the frame of my caller
		callerName = dumasCallerName (fp);	// Get the name of my caller's caller
	}
#endif
#endif

	if (segment->sentinel != BEGINNING)
	{
		BOOM ("The Dumas header has been undermined.");
		retval = FALSE;
	}
	else
	{
		if (segment->guard != MIDDLE)
		{
			BOOM ("The Dumas header has been overwritten.");
			retval = FALSE;
		}
		else
		{
			cptr = segment->data;
			for (i = 0; i < segment->length; cptr++, i++)
			{
				if (*cptr == (char) DEALLOCATED)
					poisoned += 1;
				if (*cptr == (char) ALLOCATED)
					deserted += 1;
			}
			
			if (poisoned == segment->length)
			{
				BOOM ("Item is poisoned.");
				retval = FALSE;
			}
				
			if (dumping && deserted == segment->length)
			{
				BOOM ("Item was never used.");
				retval = FALSE;
			}
													// Expect pointer beyond data
			for (i = 0; i < 4; i++)					// Check 4 bytes of guard longword
			{
				if (*cptr++ != (char) ENDING)
				{
					BOOM ("The data has been overrun.");
					retval = FALSE;
					break;
				}
			}
		}
	}
	
#ifdef THINK_C
	the_size = (segment->length + sizeof (dumasDIf));
	if (the_size < 15000
	 && sizeof_ptr(segment) != ((the_size + 1) & ~1))
	{
		BOOM ("Think C length clobbered.");
		retval = FALSE;
	}

#endif

	return retval;
}

//
//	Because of the way that the call frame is traced, this routine should always
//	be called by a routine that was called from outside Dumas. The caller will
//	be reported as being dumasAlloc's caller's caller.
//

static void *dumasAlloc (long requestedBytes, char *moduleName, long lineNo)
{
	dumasDIf		*segment;
	char			*cptr;
	int				i;
	char			*callerName = moduleName;
#if MACINTOSH
#ifndef __POWERPC__
	unsigned long	*fp;
#endif
#endif

	if (DUMAS_ACTIVE & dumasFlags)
	{

#if MACINTOSH
#ifndef __POWERPC__
		fp = GetA6();						// Get my stack frame
		if (fp)
		{
			fp = (unsigned long *) *fp;			//  and from that, the frame of my caller
			callerName = dumasCallerName (fp);	// Get the name of my caller's caller
		}
#endif
#endif
	
		if (DUMAS_VERIFY_ALLOCS & dumasFlags)
			dumasVerifyHoard ();
	
		if (0 == requestedBytes)
			dumasComplain ("Zero bytes requested.", callerName, lineNo, NULL, 0);
	
		segment = (dumasDIf *) malloc (requestedBytes + sizeof (dumasDIf));
	
		if (NULL == segment)
			return NULL;
		
		segment->next = monteCristoHoard;				// Link it into the hoard
		monteCristoHoard = segment;
		
		strncpy (segment->name, callerName, NAME_SIZE-1);	// Copy in the callerName
		segment->name[NAME_SIZE-1] = '\0';				// Paranoid termination
		
		segment->line = lineNo;							// Remember the line number
	
	#if HISTORY_SIZE
		*(segment->history) = '\0';
	
		if (DUMAS_DO_HISTORY & dumasFlags)
			dumasCallHistory (segment->history, sizeof(segment->history), fp);
	#endif
	
		segment->length = requestedBytes;				// And the requested length in bytes
		segment->sentinel = BEGINNING;					// Put in a sentinel longword
		segment->guard = MIDDLE;						// Put in a guard longword
		
		cptr = &segment->data[requestedBytes];			// Get a byte pointer beyond data
		for (i = 0; i < 4; i++)							// Copy 4 bytes of wall longword
		{
			*cptr++ = (char) ENDING;
		}
		
		monteCristoCount += 1;
	}
	else
	{
		segment = (dumasDIf *) malloc (requestedBytes + sizeof (dumasDIf));
	
		if (NULL == segment)
			return NULL;
	}
	
	return (void *) &segment->data;					// Return a pointer to the data
}

//
//	Because of the way that the call frame is traced, this routine should always
//	be called by a routine that was called from outside Dumas. The caller will
//	be reported as being dumasCheckAndFree's caller's caller.
//

static void dumasCheckAndFree (void *oldPtr, char *moduleName, long lineNo)
{
	dumasDIf		*segment;
	dumasDIf		*lastSegment = NULL;
	dumasDIf		*sptr;
	char			*cptr;
	long			i;
	char			*callerName = moduleName;
#if MACINTOSH
#ifndef __POWERPC__
	unsigned long	*fp;
#endif
#endif
#ifdef THINK_C
	long			the_size;
#endif

	if (DUMAS_ACTIVE & dumasFlags)
	{
#if MACINTOSH
#ifndef __POWERPC__
		fp = GetA6();						// Get my stack frame
		if (fp)
		{
			fp = (unsigned long *) *fp;			//  and from that, the frame of my caller
			callerName = dumasCallerName (fp);	// Get the name of my caller's caller
		}
	#endif
#endif

		if (DUMAS_VERIFY_FREES & dumasFlags)
			dumasVerifyHoard ();
	
		if (NULL == oldPtr)
			return;
			
		cptr = (char *) oldPtr;
		cptr -= (sizeof (dumasDIf) - 4);
		segment = (dumasDIf *) cptr;
		
		if (segment->sentinel != BEGINNING)
		{
			BOOM ("The Dumas header has been undermined.");
			return;
		}
		
		if (segment->guard != MIDDLE)
		{
			BOOM ("The Dumas data has been overwritten.");
			return;
		}
	
		cptr = &segment->data[segment->length];	// Get a byte pointer beyond data
		for (i = 0; i < 4; i++)					// Check 4 bytes of wall longword
		{
			if (*cptr++ != (char) ENDING)
			{
				BOOM ("The data has overrun.");
				break;
			}
		}
		
		i = 0;
		for (sptr = monteCristoHoard; sptr && sptr != segment; sptr = sptr->next)
		{
			if (i++ > monteCristoCount)
			{
				BOOM ("Too many things on the allocated list.");
				sptr = NULL;
			}
			lastSegment = sptr;
		}
		
		if (NULL == sptr)
		{
			BOOM ("Freed something not on the allocated list.");
			//
			// It would be interesting here to check to see if this dumasDIf
			// resembles a real dumasDIf. If it does, then it's a doubly-
			// deallocated dumasDIf that was not reused in the interim.
			//
			////jlb
		}
		else
		{
			cptr = segment->data;
			for (i = 0; i < segment->length; i++)
			{
				*cptr++ = (char) DEALLOCATED;
			}
			segment->data[segment->length - 1] = '\0';	// Zero-terminate it.
	
			if (lastSegment)
				lastSegment->next = segment -> next;
			else
				monteCristoHoard = segment -> next;
			monteCristoCount -= 1;
		}
	
#ifdef THINK_C
		the_size = (segment->length + sizeof (dumasDIf));
		if (the_size < 15000
		 && sizeof_ptr(segment) != ((the_size + 1) & ~1))
		{
			BOOM ("Think C length clobbered.");
			return;
		}
#endif
		free (segment);
	}
}

//	This routine packs in as much of the call history as possible into the history
//	field of the Château d'If structure. The result is a comma-seperated list of
//	routine names. The first item in the list is the routine that invoked DUMAS,
//	the second the routine tht called that one, and so on back to main(), or until
//	there is no more room in the buffer.

#ifdef MACINTOSH
#ifndef __POWERPC__
static void dumasCallHistory (char *buffer, unsigned short maxLength, unsigned long *fp)
{
	unsigned long	*a6;
	unsigned short	length;
	char			*the_name;
	char			*ptr;
	int				first = TRUE;
	
	ptr = buffer;
	
	for (a6 = fp;
		 a6 && *a6 && (Ptr) a6 <= CurStackBase && (Ptr) a6 > HeapEnd && maxLength > 1;
		 a6 = (unsigned long *) *a6)
	{
		if (first)
			first = FALSE;
		else
		{
			*ptr++ = ',';
			maxLength--;
		}
		the_name = dumasCallerName (a6);
		length = StoreString ((unsigned char *) the_name, strlen (the_name),
							  maxLength, ptr);
		maxLength -= length;
		ptr += length;
	}
}
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////
//
//	Dumas externally callable routines

void dumasCheckPtr (void *oldPtr, char *moduleName, long lineNo)
{
	dumasDIf	*segment;
	char		*cptr;

	if (DUMAS_ACTIVE & dumasFlags)
	{
		if (NULL == oldPtr)
			return;
			
		cptr = (char *) oldPtr;
		cptr -= (sizeof (dumasDIf) - 4);
		segment = (dumasDIf *) cptr;
		dumasCheckSegment (segment, moduleName, lineNo, FALSE);
	}
}

// Walk through the list of allocated memory--monte-Cristo's hoard--and list
// out everything that is in it. The hoard is counted.

void dumasDumpHoard ()
{
	long		i;
	dumasDIf	*segment;
	char		buffer[MAX_DUMP+1];
	int			max, j;

	if (DUMAS_ACTIVE & dumasFlags)
	{
		if (monteCristoCount)
			fprintf (stderr, "There should be %ld items:\n\n", monteCristoCount);
		
		i = 1;
		for (segment = monteCristoHoard; segment; segment = segment->next)
		{
			max = segment->length;
			if (max > MAX_DUMP)
				max = MAX_DUMP;
			
			for (j = 0; j < max; j++) 
			{
				buffer[j] = dumasPrintable[segment->data[j]];
			}
			buffer[max] = '\0';
			
			fprintf (stderr, "%4ld: Alloc: %s, line %4ld: size: %4ld: %s\n",
					 i++,
					 segment->name,
					 segment->line,
					 segment->length,
					 buffer);
	#if HISTORY_SIZE
			if (DUMAS_DO_HISTORY & dumasFlags)
				fprintf (stderr, "    History: %s\n",
						 segment->history);
	#endif
			dumasCheckSegment (segment, 0, 0, TRUE);
		}
	}
}

void dumasVerifyHoard ()
{
	dumasDIf	*segment;

	if (DUMAS_ACTIVE & dumasFlags)
	{
		for (segment = monteCristoHoard; segment; segment = segment->next)
		{
			dumasCheckSegment (segment, 0, 0, FALSE);
		}
	}
}

//
//	Dumas variants of the alloc/free routines
//

void dumasFree (void *oldPtr, char *moduleName, long lineNo)
{
	dumasCheckAndFree (oldPtr, moduleName, lineNo);
}

void *dumasMalloc (long requestedBytes, char *moduleName, long lineNo)
{
	void 	*ptr;
	char	*cptr;
	long	i;

	ptr = dumasAlloc (requestedBytes, moduleName, lineNo);

	if (NULL == ptr)
		return NULL;

	if (DUMAS_ACTIVE & dumasFlags)
	{
		cptr = ptr;
		for (i = 0; i < requestedBytes; i++)
		{
			*cptr++ = (char) ALLOCATED;
		}
	}

	return ptr;
}

void *dumasCalloc (long requestedItems, long itemSize, char *moduleName, long lineNo)
{
	long	requestedBytes = requestedItems * itemSize;
	void 	*ptr;
	char	*cptr;
	long	i;
	
	ptr = dumasAlloc (requestedBytes, moduleName, lineNo);

	if (NULL == ptr)
		return NULL;

	cptr = ptr;
	for (i = 0; i < requestedBytes; i++)
	{
		*cptr++ = (char) 0;
	}

	return ptr;
}

void *dumasRealloc (void *oldPtr, long requestedBytes, char *moduleName, long lineNo)
{
	void 	*ptr;
	char	*sptr;
	char	*dptr;
	long	i,
			max;
	
	dumasDIf	*segment;
	char		*cptr;

	cptr = (char *) oldPtr;
	cptr -= (sizeof (dumasDIf) - 4);
	segment = (dumasDIf *) cptr;
	if (!dumasCheckSegment (segment, moduleName, lineNo, FALSE))
		return (NULL);
	
	ptr = dumasAlloc (requestedBytes, moduleName, lineNo);

	if (NULL == ptr)
		return NULL;

	sptr = oldPtr;
	dptr = ptr;
	if (segment->length < requestedBytes)
		max = segment->length;
	else
		max = requestedBytes;

	for (i = 0; i < max; i++)
	{
		*dptr++ = *sptr++;
	}

	dumasCheckAndFree (oldPtr, moduleName, lineNo);
	oldPtr = ptr;

	return ptr;
}

#ifdef MEETING_SPACE_H
// DUMAS version of dup_string.
//
// This code is Meeting Space™ specific. The rest of DUMAS could easily be used in
// other applications.

char *dumasDupString (char *string, char *moduleName, long lineNo)
{
	long	requestedBytes = strlen(string)+1;
	char	*s;
  
	// NULL, "" -> NULL 
	if (string == 0 || *string == '\0')
		return 0;			//// Turn this around someday
  
	if (NULL == (s = dumasAlloc (requestedBytes, moduleName, lineNo)))
		abort ();

	strcpy (s, string);
	
	return s;
}
#endif

//////////////////////////////////////////////////////////////////////////////////
//
//	System-specific routines
//
//	For now, this consists of the Macintosh call-frame crawling and Think-C
//	stored length routines.

#ifdef THINK_C
//
//	Routine to get the allocation size of a block allocated by the Think C malloc,
//	alloc, calloc stuff. They store the negated length of the block (including the
//	size of the short that holds the length) in the short/word just before the
//	the address that the pointer they return points to.
//

static int	sizeof_ptr (void *ptr)
{
	return ((~((short *) ptr)[-1]) - sizeof (short));
}
#endif

#ifdef MACINTOSH
#ifndef __POWERPC__

// dumasCallerName gets the name of the caller of the routine whose stack frame is
// passed to it in the a6 parameter. It searches for the end of the routine. Just
// after the end should be the MacsBug name.

// This routine is based on GetCallerName from Martin Minow's Audit.c, which in
// turn was based on ShowStackChain.c by Greg Anderson.

static char	tempString[NAME_SIZE];

static char *dumasCallerName (unsigned long *a6)
{
	unsigned long				returnAddress;
	register unsigned short		*pc;
	short						maxSearch;
	unsigned short				length;
#define pcByte		((unsigned char *) pc)

	if (NULL == a6)
		return NULL;

	returnAddress = a6[1];			// Return address to the caller

	if (returnAddress == 0)
		return NULL;

	// First, look forwards for the symbollic name

	pc = (unsigned short *) returnAddress;
	*tempString = 0;
	for (maxSearch = 0; maxSearch < 0x4000; maxSearch++, pc++)
	{
		if (pc[0] == 0x4E56)			// link
			break;						// We've gone too far
		if (pc[0] == 0x4E75				// rts
		  || pc[0] == 0x4ED0			// jmp (a0)
		  || pc[0] == 0x4E74)			// rtd #N
		{
		  	if (pc[0] == 0x4E74)		// If rtd, skip over displacement
				pc++;
				
			pc++;						// Skip over return instruction
			
		 	if (pc[0] != 0x4E56)		// Link instruction means no name
		 	{
			 	// pc now points to the word following the RTS. Use the
			 	// MacsBug naming conventions to determine the function name,
			 	// if any. See Appendix D in the MacsBug User's Guide.
				
			 	 length = pcByte[0] & 0x7F;
			 	 if (length >= 0x20 && length <= 0x7F)
			 	 {
				 	// Fixed length format: first byte is in the range 0x20
				 	// through 0x7F, the high bit may or may not be set.

			 	 	if ((pcByte[1] & 0x80) != 0)
			 	 	{
			 	 		// Pascal 16-byte class name format. The string is
			 	 		// stored "method" "class" (each takes 8 bytes) --
			 	 		// MacsBug swaps the order and inserts a '.'
			 	 		// (Warning, this is untested.)

			 	 		BlockMove(&pcByte[8], &tempString[0], 8);
			 	 		BlockMove(&pcByte[0], &tempString[9], 8);
			 	 		tempString[8] = '.';
			 	 		tempString[9] &= ~0x80;
			 	 		tempString[10] &= ~0x80;
			 	 		tempString[17] = 0;
			 	 	}
			 	 	else
			 	 	{
			 	 		// Pascal 8 byte format.

			 	 		BlockMove(pcByte, tempString, 8);
			 	 		tempString[8] = 0;
			 	 	}
				}
				else if (pcByte[0] >= 0x80 && pcByte[0] <= 0x9F)
				{
					// Variable-length string format. If the length byte is
					// zero after removing the flag bit, the next byte has
					// the true (Str255) length.

					if (length == 0)
					{
						length = pcByte[1];
						StoreString(&pcByte[2], length, sizeof (tempString) - 1,
									tempString);
					}
					else
					{
						StoreString(&pcByte[1], length, sizeof (tempString) - 1,
									tempString);
					}
				}
				else
				{
					// Unknow format. Say so.
					
					return "<Unknown>";
				}
			}
			break;
		}
	}
	
	return tempString;
#undef pcByte
}

//
// Copy the source string to the destination, respecting the maximum size.
//
static unsigned short StoreString(const unsigned char *theString,
								  unsigned short stringLength,
								  unsigned short maxLength,
								  char *result)
{
	if (stringLength >= maxLength)
		stringLength = maxLength - 1;
		
	BlockMove(theString, result, stringLength);
	
	result[stringLength] = 0;
	return stringLength;
}

#endif
#endif
