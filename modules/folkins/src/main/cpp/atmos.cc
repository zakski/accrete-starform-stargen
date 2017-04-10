/*
  atmos.cc
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
  $RCSfile: atmos.cc,v $
    
  $Date: 2000/01/20 10:23:15 $
  $Revision: 2.0 $
          
  $Log: atmos.cc,v $
  Revision 2.0  2000/01/20 10:23:15  chrisc
  Start of MKS conversion

  Revision 1.1  2000/01/20 10:11:05  chrisc
  Initial revision

*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include <getopt.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>

#define XSTR_IOSTREAM
#define LEXER_IOSTREAM

#include <xstring.h>
#include <xstrvec.h>
#include <xfsplit.h>

#include "parsefrm.h"

Reactions ra, rs, rl;
AmountM   aa, as, al;

struct InitClass
{
  InitClass()
  {
    ra.add("2Br", "Br2", 1);
    ra.add("2Cl", "Cl2", 1);
    ra.add("2F",  "F2",  1);
    ra.add("2H",  "H2",  1);
    ra.add("2I",  "I2",  1);
    ra.add("2N",  "N2",  1);
    ra.add("2O",  "O2",  1);
  }
};

static InitClass init;

template <class T>
inline T
min(const T a, const T b)
{
  return (a < b ? a : b);
}

template <class T>
inline T
max(const T a, const T b)
{
  return (a > b ? a : b);
}


#ifdef TEST

void
dspAmount(const AmountM& aa)
{
  double tot = 0;
  for (AmountM::const_iterator p = aa.begin(); p != aa.end(); p++)
    tot += p->second * Substance[p->first].weight;
  
  for (AmountM::const_iterator p = aa.begin(); p != aa.end(); p++)
  {
    if (p->second > 0)
    {
      XString name = Substance[canonical(p->first)].name;
      XString what;
      if (canonical(name) == canonical(p->first))
	what = name;
      else
	what = name | " (" | p->first | ")";
      double wt = p->second * Substance[p->first].weight;
      if (wt*100/tot > 0.005)
	cout << xStrFormat("  %6.2f%% ", wt*100/tot) << what << endl;
    }
  }
}

struct option longopts[] =
{
  { "help",          no_argument,       NULL,    'h' },
  { "version",       no_argument,       NULL,    'V' },
  { "number",        no_argument,       NULL,    'n' },
  { "formula",       no_argument,       NULL,    'f' },
  { 0, 0, 0, 0 }
};

const char *shortopts = "hVl:n:N:t:f:z";

int
main(int argc, char **argv)
{
  double temp = 280;
  int num = 100;
  int span = 1000;
  int life = 8;
  int c;
  while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != EOF)
  {
    switch (c)
    {
      case 'h':
        break;
      case 'l':
	life=atoi(optarg);
	break;
      case 'V':
	cout << "$Revision: 2.0 $" << endl;
	break;
      case 't':
	temp = strtod(optarg, 0);
        break;
      case 'n':
        num = atoi(optarg);
        break;
      case 'N':
	span = atoi(optarg);
	break;
      case 'f':
        break;
      case 'z':
        break;
    }
  }

  ra.add("2H2+O2", "2H2O", 0.5);
  ra.add("H2O", "H2+O", (temp+0)/(temp+10000000));

  // ra.add("N2+O2","2NO", 0.1);
  // ra.add("N2+2O2","2NO2", 0.1);

  ra.add("H2+Cl2","2HCl", 0.9);
  ra.add("H2+F2","2HF", 0.9);
  ra.add("H2+Br2","2HBr", 0.9);
  ra.add("3H2+N2", "2NH3", 0.2);
  // ra.add("4H2O + N2","2NH3 + H2O + 3O", 0.2);
  ra.add("C + O2","CO2", 0.2);
  ra.add("2CO + O2","2CO2", 0.2);
  // ra.add("S + O2","SO2", 0.9);
  ra.add("H2 + S","H2S", 0.2);
  ra.add("2Na+Cl2","2NaCl", 0.8);
  ra.add("2K+Cl2","2KCl", 0.9);
  ra.add("2Rb+Cl2","2RbCl", 0.95);
  ra.add("2Cs+Cl2","2CsCl", 0.95);
  ra.add("2Fr+Cl2","2FrCl", 0.98);
  ra.add("2Ac+Cl2","2AcCl", 0.99);
  ra.add("2Na+F2","2NaF", 0.8);
  ra.add("2K+F2","2KF", 0.9);
  ra.add("2Rb+F2","2RbF", 0.95);
  ra.add("2Cs+F2","2CsF", 0.95);
  ra.add("2Fr+F2","2FrF", 0.98);
  ra.add("2Ac+F2","2AcF", 0.99);

  ra.add("CH4 + 2O2", "CO2 + 2H2O", (temp+0)/(temp+1000));
  ra.add("4NH3 + 3O2", "4N + 6H2O", (temp+0)/(temp+300));

  ra.add("NH3 + HCl", "NH4Cl", 0.2);
  ra.add("NH3 + HF", "NH4F", 0.2);
  ra.add("NH3 + HBr", "NH4Br", 0.2);

  // ra.add("Si+O2","SiO2", 0.15);
  // ra.add("Na + H2O","NaOH + H", 0.4);
  // ra.add("K + H2O","KOH + H", 0.45);
  // ra.add("Fe + O2","FeO2", 0.1);
  // ra.add("4Fe + 3O2","2Fe2O3", 0.5);
  // ra.add("Fe + 2H2O","FeO2 + 2H2", 0.1);
  // ra.add("2Fe + 3H2O","Fe2O3 + 3H2", 0.2);
  // ra.add("Mn + 2H2O","Mn(OH)2 + H2", 0.1);
  // ra.add("Ti + O2","TiO2", 0.5);

  ra.add("C + 2H2","CH4", 0.01);

  ra.add("2 NH3 + 2 H2S", "(NH4)2S + S", 0.1);
  ra.add("2 NH3 + H2S + 4H2O", "(NH4)2SO4 + 4H2", 0.1);

  ra.add("NH3 + H2O", "NH4OH", 0.5);

  ra.add("H2","0H2", 0.1);
  ra.add("He","0He", 0.1);

  ra.add("Ne", "0Ne", 0.1);

  ra.add("2Br", "Br2", 1);
  ra.add("2Cl", "Cl2", 1);
  ra.add("2F",  "F2",  1);
  ra.add("2H",  "H2",  1);
  ra.add("2I",  "I2",  1);
  ra.add("2N",  "N2",  1);
  ra.add("2O",  "O2",  1);

  aa = (getAmounts("solar") + getAmounts("universe")) * 1e6;
  // al = getAmounts("sea", 1e6);
  as = getAmounts("crust", 1e6);

  cout << "Atmosphere at start (mass %g):" << endl;
  dspAmount(aa);
  cout << endl;
  
  double aw = aa.weight();

  for (int year = 0; year < num; year++)
  {
    for (int i = 0; i < span; i++)
    {
      doReaction(ra, aa, 1);
      double amtH2O = al["H2O"];
      AmountM::iterator next;
      for (AmountM::iterator p = aa.begin(); p != aa.end(); p = next)
      {
	next = p;
	next++;
	XString name = p->first;
	EData &s = Substance[name];
	if (p->second > 0)
	{
	  if (temp < s.melt)
	  {
#ifdef TRACE
	    cout << "+++ g => s " << PadRight(name, 5) << " " << p->second
	         << endl;
#endif
	    as[name] += p->second;
	    aa.erase(p);
	  }
	  else if (temp < s.boil)
	  {
#ifdef TRACE
	    cout << "+++ g => l " << PadRight(name, 5) << " " << p->second
	         << endl;
#endif
	    al[name] += p->second;
	    aa.erase(p);
	  }
	  else if (amtH2O > 0)
	  {
	    double amt = min(p->second, amtH2O) * s.boil/temp;
#ifdef TRACE
	    cout << "+++ g =d l " << PadRight(name, 5) << " " << amt
	         << " (" << amt/p->second << "%)" << endl;
#endif
	    al[name] += amt;
	    p->second -= amt;
	  }
	}
      }
      amtH2O = al["H2O"];
      for (AmountM::iterator p = al.begin(); p != al.end(); p = next)
      {
	next = p;
	next++;
	XString name = p->first;
	EData &s = Substance[name];
	if (temp > s.boil && p->second > 0)
	{
	  double amt = min(p->second, amtH2O) * s.boil/temp;
#ifdef TRACE
	  cout << "+++ l => g " << PadRight(name, 5) << " " << amt
	       << " (" << amt/p->second << "%)" << endl;
#endif
	  aa[name] += amt;
	  p->second -= amt;
	}
	else
	{
	  double m = (temp - s.melt) / (s.boil - s.melt);
	  double amt = (m > 0 ? al[name] * pow(m, 3) : 0);
#ifdef TRACE
	  cout << "+++ l => g " << PadRight(name, 5) << " " << amt
	       << " (" << amt/p->second << "%)" << endl;
#endif
	  aa[name] += amt;
	  al[name] -= amt;
	}
      }
      double sC = as["C"];
      double aO = aa["O2"];
      double mm = min(sC, aO) * 0.01;
      if (mm > 0)
      {
#ifdef TRACE
	cout << "+++ C + O2 => CO2 " << mm << endl;
#endif
	aa["CO2"] += mm;
	as["C"]   -= mm;
	aa["O2"]  -= mm;
      }
    }
    if (year == life)
    {
      // ra.add("CO2", "C+O2", 0.1);
      ra.add("CO2 + H2O", "CH2Oorg + O2", 0.2);
      ra.add("2CH2Oorg", "C + CH4 + O2", 0.1);
    }

    cout << endl << "Year " << year << ": ";
    cout << 100*aa.weight()/aw << "% atmosphere left" << endl;

    cout << "Atmosphere:" << endl;
    dspAmount(aa);

    cout << "Liquid:" << endl;
    dspAmount(al);

    cout << "Solid:" << endl;
    dspAmount(as);

    cout.flush();
  }

  return 0;
}



#endif
