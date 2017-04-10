#ifndef _PARSEFRM_H
#define _PARSEFRM_H

/*
  parsefrm.h
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
  $RCSfile: parsefrm.h,v $
    
  $Date: 2000/01/20 10:23:15 $
  $Revision: 2.0 $
          
  $Log: parsefrm.h,v $
  Revision 2.0  2000/01/20 10:23:15  chrisc
  Start of MKS conversion

  Revision 1.1  2000/01/20 10:13:49  chrisc
  Initial revision

  Revision 1.4  2000/01/17 09:25:57  chrisc
  Add getAmounts, doReaction

  Revision 1.3  1999/12/03 13:12:01  chrisc
  Add const to other constant parameters

  Revision 1.2  1999/12/03 11:59:23  chrisc
  Make parameters const, add reaction classes

  Revision 1.1  1999/12/02 16:18:59  chrisc
  Initial revision

*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <getopt.h>

#if defined(cplusplus) || defined(_cplusplus) || defined(__cplusplus)

#include <iostream>
#include <vector>
#include <list>
#include <map>

#define XSTR_IOSTREAM
#define LEXER_IOSTREAM

#include <xstring.h>

#endif /* C++ */

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

#if defined(cplusplus) || defined(_cplusplus) || defined(__cplusplus)

struct EData
{
  int     n;
  XString sym;
  XString name;
  double  weight;
  double  melt;
  double  boil;
  double  tcrit;
  double  pcrit;

  EData()
  {
    n = 0;
    weight = 0;
    melt = 0;
    boil = 0;
    tcrit = 0;
    pcrit = 0;
  }
  EData(int an, const ElemData& e)
  {
    n = an;
    sym = e.b.symbol;
    name = e.b.name;
    weight = e.b.weight;
    melt = e.t.melt;
    boil = e.t.boil;
    tcrit = e.t.crit;
    pcrit = 1;
  }
  EData& operator= (const ElemData& e)
  {
    n = -1;
    sym = e.b.symbol;
    name = e.b.name;
    weight = e.b.weight;
    melt = e.t.melt;
    boil = e.t.boil;
    tcrit = e.t.crit;
    pcrit = 1;
  }
};

typedef map<XString,EData>   ElemM;


extern ElemM Substance;

template<class T=double>
class ElemMap
{
public:
  typedef map<XString,T>       Tmap;
  typedef Tmap::iterator       iterator;
  typedef Tmap::const_iterator const_iterator;
  ElemMap() {}
  inline T& operator[] (const XString& s)
  {
    return m[s];
  }
  inline iterator begin()
  {
    return m.begin();
  }
  inline iterator end()
  {
    return m.end();
  }
  inline iterator find(const XString& s)
  {
    return m.find(s);
  }
  inline void erase(iterator p)
  {
    m.erase(p);
  }
  inline const_iterator begin() const
  {
    return m.begin();
  }
  inline const_iterator end() const
  {
    return m.end();
  }
  inline const_iterator find(const XString& s) const
  {
    return m.find(s);
  }
  size_t size() const
  {
    return m.size();
  }
  ElemMap& operator += (const ElemMap& s)
  {
    for (const_iterator p = s.begin(); p != s.end(); p++)
      m[p->first] += p->second;
    return *this;
  }
  ElemMap& operator -= (const ElemMap& s)
  {
    for (const_iterator p = s.begin(); p != s.end(); p++)
      m[p->first] -= p->second;
    return *this;
  }
  ElemMap& operator *= (double num)
  {
    for (iterator p = m.begin(); p != m.end(); p++)
      p->second *= num;
    return *this;
  }
  ElemMap& operator /= (double num)
  {
    for (iterator p = m.begin(); p != m.end(); p++)
      p->second /= num;
    return *this;
  }
  friend ElemMap operator + (const ElemMap& a, const ElemMap& b)
  {
    ElemMap e = a;
    e += b;
    return e;
  }
  friend ElemMap operator - (const ElemMap& a, const ElemMap& b)
  {
    ElemMap e = a;
    e -= b;
    return e;
  }
  friend ElemMap operator * (const ElemMap& a, double num)
  {
    ElemMap e = a;
    e *= num;
    return e;
  }
  friend ElemMap operator / (const ElemMap& a, double num)
  {
    ElemMap e = a;
    e /= num;
    return e;
  }

  bool operator == (const ElemMap& a) const
  {
    for (const_iterator p = m.begin(); p != m.end(); p++)
    {
      const_iterator q = a.find(p->first);
      if (q == a.end() || q->second != p->second)
	return false;
    }
    return true;
  }
  bool operator != (const ElemMap& a) const
  {
    return !(*this == a);
  }
  T weight() const
  {
    T total = 0;
    for (const_iterator p = m.begin(); p != m.end(); p++)
      total += Substance[p->first].weight * p->second;
    return total;
  }
private:
  Tmap m;
};

typedef ElemMap<double>      AmountM;

struct Reaction
{
  AmountM in;
  AmountM out;
  double  str;
  Reaction() : str(0) {}
  Reaction(const char *istr, const char *ostr, double strength=1);
  double test(const AmountM& amount) const
  {
    double amt = 0;
    bool   ok  = false;
    for (AmountM::const_iterator p = in.begin(); p != in.end(); p++)
    {
      if (p->second <= 0)
	continue;
      AmountM::const_iterator q = amount.find(p->first);
      if (q == amount.end() || q->second <= 0)
      {
	amt = 0;
	break;
      }
      double a = q->second / p->second;
      if (!ok || a < amt)
      {
	amt = a;
	ok  = true;
      }
    }
    return amt;
  }
};

typedef vector<Reaction> ReactionV;

struct Reactions
{
  ReactionV r;
  int add(const char *istr, const char *ostr, double strength=1)
  {
    int n = r.size();
    r.push_back(Reaction(istr, ostr, strength));
    return n;
  }
  Reaction& operator[] (int n)
  {
    return r[n];
  }
  const Reaction& operator[] (int n) const
  {
    return r[n];
  }
  int find(const char *istr);
  size_t size() const
  {
    return r.size();
  }
};

struct Environment
{
  AmountM   amount;
  ReactionV react;
};

void mkcompound(const char *symbol, const char *name,
                double melt=DBL_MAX, double boil=DBL_MAX,
	        double tcrit=DBL_MAX, double pcrit=DBL_MAX);

XString canonical(const char *str, AmountM *ap=0, char **pp=0);

AmountM getAmounts(const XString& sim, double mass=1);
void doReaction(const Reactions& r, AmountM& a, int num=1);

inline void 
doReaction(AmountM& a, const Reactions& r, int num=1)
{
  doReaction(r, a, num);
}

#endif /* C++ */

#endif
