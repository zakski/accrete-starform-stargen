
/************************************************************

Created: Monday, December 2, 1991 at 4:27 PM
 Types.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved.

************************************************************/


#ifndef __TYPES__
#define __TYPES__

#if THINK_C

	#ifndef NULL
	#define NULL			((void *) 0)
	#endif
	
	#define nil				NULL
	
	typedef struct { short man[4]; } comp;
	typedef struct { short exp[1], man[4]; } extended80;
	typedef struct { short exp[2], man[4]; } extended96;
	typedef extended80 __extended;	//  <-- this line is magic
	typedef __extended extended;
	
	typedef void *ProcPtr;

#endif /* THINK_C */

#if __SC__ && !defined(__STDC__) && defined(__cplusplus)

	class __machdl HandleObject {};
	class __pasobj PascalObject {};

#endif /* __SC__ */


#ifndef SystemSevenOrLater
#define SystemSevenOrLater 0
#endif

#ifndef SystemSixOrLater
#define SystemSixOrLater SystemSevenOrLater
#endif

#ifndef NULL
#define NULL 0
#endif
#ifndef nil
#define nil 0
#endif

#define noErr 0			/*All is well*/

typedef unsigned char Byte;
typedef char SignedByte;
typedef char *Ptr;
typedef Ptr *Handle;	/*  pointer to a master pointer */

typedef long Fixed;		/* fixed point arithmatic type */
typedef Fixed *FixedPtr;
typedef long Fract;
typedef Fract *FractPtr;

#if THINK_CPLUS
#ifdef mc68881
struct extended80 {
	short w[5];
};

#else
typedef extended extended80;

#endif /* mc68881 */
#endif /* THINK_CPLUS */

enum {false,true};
typedef unsigned char Boolean;

enum {v,h};
typedef unsigned char VHSelect;


#if !THINK_C
typedef long (*ProcPtr)();
#endif
typedef ProcPtr *ProcHandle;

typedef unsigned char Str255[256],Str63[64],Str32[33],Str31[32],Str27[28],Str15[16],*StringPtr,**StringHandle;

#ifdef __cplusplus
inline unsigned char & Length(StringPtr string) { return (*string); }
#else
#define Length(string) (*(unsigned char *)(string))
#endif

typedef const unsigned char *ConstStr255Param;
typedef ConstStr255Param ConstStr63Param,ConstStr32Param,ConstStr31Param,
 ConstStr27Param,ConstStr15Param;

typedef short OSErr;	/* error code */
typedef unsigned long OSType;
typedef OSType *OSTypePtr;
typedef unsigned long ResType;
typedef ResType *ResTypePtr;
typedef unsigned char Style;
typedef short ScriptCode;
typedef short LangCode;


struct Point {
 short v;
 short h;
};

typedef struct Point Point;
typedef Point *PointPtr;

struct Rect {
 short top;
 short left;
 short bottom;
 short right;
};

typedef struct Rect Rect;
typedef Rect *RectPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal void Debugger(void)
 = 0xA9FF; 
pascal void DebugStr(ConstStr255Param aStr)
 = 0xABFF; 
void debugstr(char *aStr); 
pascal void SysBreak(void)
 = {0x303C,0xFE16,0xA9C9}; 
pascal void SysBreakStr(ConstStr255Param debugStr)
 = {0x303C,0xFE15,0xA9C9}; 
pascal void SysBreakFunc(ConstStr255Param debugFunc)
 = {0x303C,0xFE14,0xA9C9}; 


#ifdef __cplusplus
}
#endif

#endif
