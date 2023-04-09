#ifndef _ELEM_H
#define _ELEM_H

/*
  elem.h
  Copyright Chris Croughton, 1999
  Internet: chris@keris.demon.co.uk

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met (see file LICENSE for more explanation):
 
     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
 
     2. Modifications of the source code must, in addition to the above,
        include a statement that the code has been modified and by whom,
        and have relevant contact information.
 
     3. Redistributions in binary form must reproduce the above
        copyright notice, this list of conditions and the following
        disclaimer in the documentation and/or other materials provided
        with the distribution.  Note that this does not apply when the
        binary forms part of a completed work such as an executable
        program of which it is a minor part and from which it cannot be
        extracted in a usable form (for instance linked to form an
        executable binary image).
 
     4. The name of the author may not be used to endorse or promote
        products derived from this software without specific prior
        written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

/*
  $RCSfile: elem.h,v $
    
  $Date: 2000/01/20 10:23:15 $
  $Revision: 2.0 $
          
  $Log: elem.h,v $
  Revision 2.0  2000/01/20 10:23:15  chrisc
  Start of MKS conversion

  Revision 1.1  2000/01/20 10:13:49  chrisc
  Initial revision

  Revision 1.1  1999/11/29 13:21:57  chrisc
  Initial revision

*/

#ifdef PROP_GEN
typedef XString     StrType;
typedef struct ElemBasics  Basics;
typedef struct ElemThermal Thermal;
typedef struct ElemAbund   Abund;
typedef struct ElemData    Data;
#else
typedef const char *StrType;
#endif

struct ElemBasics
{
  StrType symbol;
  StrType name;
  double  weight;
};

struct ElemThermal
{
  double melt;
  double boil;
  double crit;
  double supercond;
};

struct ElemAbund
{
  double universe;
  double solar;
  double meteorite;
  double crustal;
  double sea;
  double stream;
  double human;
};

struct ElemData
{
  ElemBasics  b;
  ElemThermal t;
  ElemAbund   a;
  ElemAbund   m;
};

#endif

