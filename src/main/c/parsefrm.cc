/*
  parsefrm.cc
  Copyright Chris Croughton 1998
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
  $RCSfile: parsefrm.cc,v $
    
  $Date: 2000/01/20 10:23:15 $
  $Revision: 2.0 $
          
  $Log: parsefrm.cc,v $
  Revision 2.0  2000/01/20 10:23:15  chrisc
  Start of MKS conversion

  Revision 1.1  2000/01/20 10:13:49  chrisc
  Initial revision

  Revision 1.6  2000/01/17 09:24:02  chrisc
  Add getAmounts, lots of test changes

  Revision 1.5  1999/12/03 13:10:43  chrisc
  Auto-initialise objects, modify displays

  Revision 1.4  1999/12/03 11:58:52  chrisc
  Add code to do reactions

  Revision 1.3  1999/12/02 16:17:17  chrisc
  Remove classes and types to parsefrm.h, parse complete formulae

  Revision 1.2  1999/12/02 10:56:05  chrisc
  Added many compounds, critical pressure as well as temperature

  Revision 1.1  1999/11/29 13:22:29  chrisc
  Initial revision

*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <float.h>
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
#include <lexer.h>

#include "parsefrm.h"

#define arraysize(x) (sizeof(x)/sizeof(x[0]))

#define CCP(x) ((const char*)(x))

#define Na (1.0/1.66053873e-27)

static ElemData elem_def[] =
{
#include "elem.ch"
};

static int elem_sort[] =
{
  0x0000, 0x0109, 0x1209, 0x0108, 0x0208, 0x0D08, 0x0E08, 0x0F08, 0x1008, 0x1108, 
  0x1208, 0x0107, 0x0207, 0x0D07, 0x0E07, 0x0F07, 0x1007, 0x1107, 0x1207, 0x0106, 
  0x0206, 0x0306, 0x0406, 0x0506, 0x0606, 0x0706, 0x0806, 0x0906, 0x0A06, 0x0B06, 
  0x0C06, 0x0D06, 0x0E06, 0x0F06, 0x1006, 0x1106, 0x1206, 0x0105, 0x0205, 0x0305, 
  0x0405, 0x0505, 0x0605, 0x0705, 0x0805, 0x0905, 0x0A05, 0x0B05, 0x0C05, 0x0D05, 
  0x0E05, 0x0F05, 0x1005, 0x1105, 0x1205, 0x0104, 0x0204, 0x0214, 0x0224, 0x0234, 
  0x0244, 0x0254, 0x0264, 0x0274, 0x0284, 0x0294, 0x02A4, 0x02B4, 0x02C4, 0x02D4, 
  0x02E4, 0x0304, 0x0404, 0x0504, 0x0604, 0x0704, 0x0804, 0x0904, 0x0A04, 0x0B04, 
  0x0C04, 0x0D04, 0x0E04, 0x0F04, 0x1004, 0x1104, 0x1204, 0x0103, 0x0203, 0x0213, 
  0x0223, 0x0233, 0x0243, 0x0253, 0x0263, 0x0273, 0x0283, 0x0293, 0x02A3, 0x02B3, 
  0x02C3, 0x02D3, 0x02E3, 0x0303, 0x0403, 0x0503, 0x0603, 0x0703, 0x0803, 0x0903, 
  0x0A03, 0x0B03, 0x0C03, 0x0D03, 0x0E03, 0x0F03, 0x1003, 0x1103, 0x1203, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
};

typedef map<int, XString>  ElemSortM;

ElemM Substance;

XString
canonical(const char *str, AmountM *ap=0, char **pp=0)
{
  bool temp = (ap == 0);
  if (temp)
    ap = new AmountM;
  AmountM& a = *ap;
  char *p = (char *)str;
  while (*p)
  {
    if (isupper(*p))
    {
      XString sym = *p++;
      while (islower(*p))
	sym |= *p++;
      double num = (isdigit(*p) ? strtod(p, &p) : 1);
      if (&a)
	a[sym] += num;
    }
    else if (*p == '(')
    {
      AmountM amt;
      canonical(p+1, &amt, &p);
      if (*p == ')')
	p++;
      double num = (isdigit(*p) ? strtod(p, &p) : 1);
      if (&a)
      {
	amt *= num;
	a += amt;
      }
    }
    else if (strchr("_-./", *p))
    {
      p++;
    }
    else
      break;
  }
  XString out;
  if (pp)
  {
    *pp = p;
  }
  else
  {
#if 0
    ElemSortM part;
    for (AmountM::iterator p = a.m.begin(); p != a.m.end(); p++)
    {
      int amount = (int)p->second;
      int n = elem_sort[Substance[p->first].n];
      part[n] = (amount > 1 ? p->first | amount : p->first);
    }
    for (ElemSortM::iterator p = part.begin(); p != part.end(); p++)
      out |= p->second;
#else
    for (AmountM::iterator p = a.begin(); p != a.end(); p++)
    {
      int amount = (int)p->second;
      out |= (amount > 1 ? p->first | amount : p->first);
    }
#endif
  }
  if (temp)
    delete ap;
  return out;
}


double
getWeight(const char *str, AmountM *ap=0, char **pp=0)
{
  AmountM amt;
  double wt = 0;
  canonical(str, &amt);
  for (AmountM::iterator p = amt.begin(); p != amt.end(); p++)
  {
    ElemM::iterator ep = Substance.find(p->first);
    if (ep != Substance.end())
      wt += ep->second.weight * p->second;
  }
  if (ap)
    *ap += amt;
  return wt;
}

EData
compound(const char *symbol, const char *name, AmountM *amt=0,
         double melt=0, double boil=0, double tcrit=0, double pcrit = 0)
{
  EData e;
  if (Substance.find(symbol) == Substance.end())
  {
    e.n = -1;
    e.sym = canonical(symbol);
    e.name = name;
    e.weight = getWeight(symbol, amt);
    e.melt = melt;
    e.boil = boil;
    e.tcrit = tcrit;
    e.pcrit = pcrit;
  }
  else
  {
    e = Substance[symbol];
    if (amt > 0)
      getWeight(symbol, amt);
  }
  return e;
}

void
mkcompound(const char *symbol, const char *name,
           double melt=DBL_MAX, double boil=DBL_MAX,
	   double tcrit=DBL_MAX, double pcrit=DBL_MAX)
{
  EData e = compound(symbol, name, 0, melt, boil, tcrit, pcrit);
  Substance[e.sym] = e;
}

struct Initialise
{
Initialise()
{
  for (int i = 0; i < arraysize(elem_def); i++)
  {
    XString sym = elem_def[i].b.symbol;
    if (sym)
      Substance[sym] = EData(i, elem_def[i]);
  }
  mkcompound("Ar",     "Argon",                    83.25,  87.25, 150.8,  48.7);
  mkcompound("BF3",    "Boron trifluoride",       146.45, 173.25, 260.8,  49.9);
  mkcompound("Br2",    "Bromine",                 265.95, 331.85, 584,   103.4);
  mkcompound("ClNO",   "Nitrosyl chloride",       213.45, 267.65, 440,    91.2);
  mkcompound("Cl2",    "Chlorine",                172.15, 238.65, 417,    77);
  mkcompound("Cl3P",   "Phosphorus trichloride",  160.95, 348.95, 563,    77);
  mkcompound("Cl4Si",  "Silicon tetrachloride",   204.25, 330.35, 507,    37.5);
  // mkcompound("D2",  "Deuterium",                18.65,  23.65, 38.4,   16.6);
  // mkcompound("D2O", "Deuterium oxide",         276.95, 374.55, 644,   216.6);
  mkcompound("F2",     "Fluorine",                 53.45,  84.95, 144.3,  52.2);
  mkcompound("F3N",    "Nitrogen trifluoride",     66.35, 144.05, 234,    45.3);
  mkcompound("F4Si",   "Silicon tetrafluoride",   182.95, 186.95, 259,    37.2);
  mkcompound("F6S",    "Sulphur hexafluoride",    222.45, 209.25, 318.7,  37.6);
  mkcompound("HBr",    "Hydrogen bromide",        187.05, 206.05, 363.2,  85.5);
  mkcompound("HCl",    "Hydrogen chloride",       158.95, 188.05, 324.6,  83.1);
  mkcompound("HF",     "Hydrogen fluoride",       189.95, 292.65, 461,    64.8);
  mkcompound("HI",     "Hydrogen iodide",         222.35, 237.55, 424,    83.1);
  mkcompound("H2",     "Hydrogen",                 13.95,  20.35,  33.2,  13);
  mkcompound("H2O",    "Water",                   273.15, 373.15, 647.3, 220.5);
  mkcompound("H2S",    "Hydrogen sulphide",       187.55, 212.75, 373.2,  89.4);
  mkcompound("H3N",    "Ammonia",                 195.35, 239.65, 405.6, 112.8);
  mkcompound("H4N2",   "Hydrazine",               274.65, 386.65, 653,   146.9);
  mkcompound("I2",     "Iodine",                  386.75, 457.45, 819,   116.5);
  mkcompound("Kr",     "Krypton",                 115.75, 119.75, 209.4,  55);
  mkcompound("NO",     "Nitric oxide",            109.45, 121.35, 180,    64.8);
  mkcompound("NO2",    "Nitrogen dioxide",        261.85, 294.25, 431.4, 101.3);
  mkcompound("N2",     "Nitrogen",                 63.25,  77.35, 126.2,  33.9);
  mkcompound("N2O",    "Nitrous oxide",           182.25, 184.65, 309.6,  72.4);
  mkcompound("Ne",     "Neon",                     24.45, 26.95,   44.4,  27.6);
  mkcompound("O2",     "Oxygen",                   54.35, 90.15,  154.6,  50.5);
  mkcompound("O2S",    "Sulphur dioxide",         197.65, 262.95, 430.8,  78.8);
  mkcompound("O3",     "Ozone",                    80.5,  161.3,  261.0,  55.0);
  mkcompound("O3S",    "Sulphur trioxide",        289.95, 317.95, 491,    82.1);
  mkcompound("Xe",     "Xenon",                   161.25, 164.95, 289.7,  58.4);
  mkcompound("CBrF3",  "Trifluorobromomethane",   273.15, 213.95, 340.2,  39.7);
  mkcompound("CClF3",  "Chlorotrifluoromethane",   91.95, 191.65, 302,    39.2);
  mkcompound("CCl2F2", "Dichlorodifluoromethane", 115.35, 243.35, 385,    41.2);
  mkcompound("CCl2O",  "Phosgene",                144.95, 280.75, 455,    56.7);
  mkcompound("CCl3F",  "Trichlorofluoromethane",  161.95, 296.95, 471.2,  44.1);
  mkcompound("CCl4",   "Carbon tetrachloride",    249.95, 349.65, 556.4,  45.6);
  mkcompound("CF4",    "Carbon tetrafluoride",     86.35, 145.15, 227.6,  37.4);
  mkcompound("CO",     "Carbon monoxide",          68.05,  81.65, 132.9,  35);
  mkcompound("COS",    "Carbonyl sulphide",       134.25, 222.85, 375,    58.8);
  mkcompound("CO2",    "Carbon dioxide",          216.55, 194.65, 304.2,  73.8);
  mkcompound("CS2",    "Carbon disulphide",       161.25, 319.35, 552,    79);
  mkcompound("CHClF2", "Chlorodifluoromethane",   112.95, 232.35, 369.2,  49.8);
  mkcompound("CHCl2F", "Dichlorofluoromethane",   137.95, 281.95, 451.6,  51.7);
  mkcompound("CHCl3",  "Chloroform",              209.55, 334.25, 536.4,  54.7);
  mkcompound("CHN",    "Hydrogen cyanide",        259.85, 298.85, 456.8,  53.9);
  mkcompound("CH2Br2", "Dibromomethane",          220.55, 369.95, 583,    71.9);
  mkcompound("CH2Cl2", "Dichloromethane",         178.05, 312.95, 510,    60.8);
  mkcompound("CH2O",   "Formaldehyde",            155.95, 253.95, 408,    65.9);
  mkcompound("CH2O2",  "Formic acid",             281.45, 373.75, 580,    65.9);
  mkcompound("CH3Br",  "Methyl bromide",          179.45, 276.65, 464,    86.1);
  mkcompound("CH3Cl",  "Methyl chloride",         175.35, 248.85, 416.3,  66.8);
  mkcompound("CH3F",   "Methyl fluoride",         131.35, 194.75, 317.8,  58.8);
  mkcompound("CH3I",   "Methyl iodide",           206.65, 315.55, 528,    65.9);
  mkcompound("CH3NO2", "Nitromethane",            244.55, 374.35, 588,    63.1);
  mkcompound("CH4",    "Methane",                  90.65, 111.65, 190.6,  46);
  mkcompound("CH4O",   "Methanol",                175.45, 337.75, 512.6,  81);
  mkcompound("CH4S",   "Methyl mercaptan",        149.95, 279.05, 470,    72.3);
  mkcompound("CH5N",   "Methyl amine",            179.65, 266.75, 430,    74.6);
  mkcompound("CH6N2",  "Methyl hydrazine",        273.15, 363.95, 567,    80.4);
  mkcompound("C2ClF5", "Chloropentafluoromethane", 166.95, 233.95, 353.2, 31.6);
  mkcompound("C2Cl2F4","tetrafluoroethane",       178.95, 276.95, 418.6,  33);
  mkcompound("C2Cl3F3","trifluoroethane",         238.15, 320.65, 487.2,  34.1);
  mkcompound("C2Cl4",  "Tetrachloroethylene",     250.95, 394.25, 620,    44.6);
  mkcompound("C2Cl4F2","Tetrachlorodifluoroethane", 297.95, 364.65, 551,  44.6);
  mkcompound("C2F4",   "Tetrafluoroethylene",     130.65, 197.45, 306.4,  39.4);
  mkcompound("C2F6",   "Hexafluoroethylene",      172.35, 194.85, 292.8,  39.4);
  mkcompound("C2N2",   "Cyanogen",                245.25, 252.45, 400,    59.8);
  mkcompound("CH2Cl3", "Trichloroethylene",       156.75, 360.35, 571,    49.1);
  mkcompound("C2HF3O2",  "Trifluoroacetic acid",  257.85, 345.55, 491.3,  32.6);
  mkcompound("C2H3ClF2", "chlorodifluoroethane",  141.95, 263.35, 410.2,  41.2);
  mkcompound("C2H3N",  "Acetonitrile",            229.25, 354.75, 548,    48.3);
  mkcompound("C2H4O2", "Acetic acid",             289.75, 391.05, 594.4,  57.9);
  mkcompound("C2H6",   "Ethane",                   89.85, 184.45, 305.4,  48.8);
  mkcompound("C2H6O",  "Dimethyl ether",          131.65, 248.45, 400,    53.7);
  mkcompound("C2H6O",  "Ethanol",                 159.05, 351.45, 516.2,  63.8);
  mkcompound("C2H6O2", "Ethylene glycol",         260.15, 470.35, 645,    77);
  mkcompound("C2H6S",  "Ethyl mercaptan",         125.25, 308.15, 499,    54.9);
  mkcompound("C2H6S",  "Dimethyl sulphide",       174.85, 310.45, 503,    55.3);
  mkcompound("C2H7N",  "Ethyl amine",             191.95, 289.65, 456,    56.2);
  mkcompound("C2H7N",  "Dimethyl amine",          180.95, 279.95, 437.6,  53.1);
  mkcompound("C2H7NO", "Mono ethanolamine",       283.45, 443.45, 614,    44.6);
  mkcompound("C2H8N2", "Ethylene diamine",        283.95, 390.35, 593,    62.8);
  mkcompound("C3H3N",  "Acrylonitrile",           189.45, 350.45, 536,    35.5);
  mkcompound("C3H5N",  "Propionitrile",           180.45, 370.45, 564.4,  41.8);
  mkcompound("C3H6O",  "Acetone",                 178.15, 329.35, 508.1,  47);
  mkcompound("C3H8O",  "Isopropyl alcohol",       184.65, 355.35, 508.3,  47.6);
  mkcompound("C3H8O",  "Methyl ethyl ether",      133.95, 280.45, 437.8,  44);
  mkcompound("C3H8S",  "Methyl ethyl sulphide",   167.15, 339.75, 533,    42.6);
  mkcompound("C3H9N",  "n-Propyl amine",          189.95, 321.75, 497,    47.4);
  mkcompound("C3H9N",  "Iso-propyl amine",        177.85, 305.55, 476,    50.7);
  mkcompound("C3H9N",  "Trimethyl amine",         155.95, 276.05, 433.2,  40.7);
  mkcompound("C4H2O3", "Maleic anhydride",        325.95, 472.75, 433.2,  40.7);
  mkcompound("C4H6O3", "Acetic anhydride",        198.95, 411.95, 569,    46.8);
  mkcompound("C4H10O", "Isobutanol",              165.15, 380.95, 547.7,  43);
  mkcompound("C4H10S", "Diethyl sulphide",        169.15, 365.25, 557,    39.6);
  mkcompound("C4H11N", "Diethyl amine",           223.35, 328.55, 496.6,  37.1);
  mkcompound("C5H10O2","n-Valeric acid",          238.95, 458.65, 651,    38.5);
  mkcompound("C6H14",  "n-Hexane",                177.75, 341.85, 507.4,  29.7);
  mkcompound("C7H8",   "Toluene",                 177.95, 383.75, 591.7,  41.1);
  mkcompound("C21H42", "n-hexadecyl cyclopentane",273.15, 636.95, 791,     9.7);

  mkcompound("(BiO)4UO2(AsO4)2", "Bismuth Uranyl");
  mkcompound("(Mn)(Mn)2O4", "Manganese Oxide");
  mkcompound("(UO2)6SO4(OH)10", "Uranyl Sulfate");
  mkcompound("Ag2Hg3", "Silver Mercury (silver amalgam)");
  mkcompound("Ag2S", "Silver Sulfide");
  mkcompound("Ag3AsS3", "Silver Arsenic Sulfide");
  mkcompound("Ag3Sb", "Silver Antimonide");
  mkcompound("Ag3SbS3", "Silver Antimony Sulfide");
  mkcompound("Ag5SbS4", "Silver Antimony Sulfide");
  mkcompound("AgAuTe4", "Silver Gold Telluride");
  mkcompound("AgCl", "Silver Chloride");
  mkcompound("AgSbS2", "Silver Antimony Sulfide");
  mkcompound("Al2PO4(OH)3", "Aluminum Phosphate Hydroxide");
  mkcompound("Al2SiO5", "Aluminum Silicate");
  mkcompound("Al3(PO4)2(OH)3", "Aluminum Phosphate");
  mkcompound("AlPO4", "Aluminum Phosphate");
  mkcompound("AlSi2O5OH", "Aluminum Silicate Hydroxide");
  mkcompound("As2S3", "Arsenic Sulfide");
  mkcompound("AsS", "Arsenic Sulfide");
  mkcompound("AuTe2", "Gold Telluride");
  mkcompound("Ba(UO2)2(PO4)2", "Barium Uranyl");
  mkcompound("BaAl2Si3O10", "Barium Aluminum Silicate");
  mkcompound("BaAl2Si6O16", "barium aluminum silicate");
  mkcompound("BaCO3", "Barium Carbonate");
  mkcompound("BaSi2O5", "Barium Silicate");
  mkcompound("BaSO4", "Barium Sulfate");
  mkcompound("BaTiSi3O9", "Barium Titanium Silicate");
  mkcompound("Be2SiO4", "Beryllium silicate");
  mkcompound("Be3Al2(SiO3)6", "Beryllium Aluminum Silicate");
  mkcompound("BeAl2O4", "Beryllium Aluminum Oxide");
  mkcompound("BeAlSiO4OH", "Beryllium Aluminum Silicate Hydroxide");
  mkcompound("BeMgAl4O8", "Beryllium Magnesium Aluminum Oxide");
  mkcompound("Bi2S3", "Bismuth Sulfide");
  mkcompound("C2H17O5Si46O92", "Silicon Oxide with organic compounds");
  mkcompound("Ca(UO2)2(PO4)2", "Calcium Uranyl");
  mkcompound("Ca(UO2)2(VO4)2", "Calcium Uranyl");
  mkcompound("Ca(UO2)2Si2O7", "Calcium Uranyl Silicate");
  mkcompound("Ca(UO2)3(PO4)2(OH)2", "Calcium Uranyl");
  mkcompound("Ca(VO)Si4O10(H2O)4", "Calcium Vanadium Silicate");
  mkcompound("Ca2Al2Si3O10(OH)2", "Calcium aluminum silicate");
  mkcompound("Ca2Al3(SiO4)3(OH)", "Calcium Aluminum Silicate Hydroxide");
  mkcompound("Ca2B5SiO9(OH)5", "Calcium Boro-silicate Hydroxide");
  mkcompound("Ca2Fe(PO4)2", "Calcium Iron Phosphate");
  mkcompound("Ca2Fe2Si5O14OH", "Calcium iron silicate");
  mkcompound("Ca2Mg5Si8O22(OH)2", "Calcium Magnesium Silicate");
  mkcompound("Ca2Mn7Si10O28(OH)2", "Calcium Manganese");
  mkcompound("Ca2Si3O7(OH)2", "calcium silicate");
  mkcompound("Ca2ZnSi2O7", "Calcium Zinc Silicate");
  mkcompound("Ca3Al2(SiO4)3", "Calcium Aluminum Silicate");
  mkcompound("Ca3Cr2(SiO4)3", "Calcium Chromium Silicate");
  mkcompound("Ca3Fe2(SiO4)3", "Calcium iron silicate");
  mkcompound("Ca3PbZn4(SiO4)4", "Calcium Lead Zinc Silicate");
  mkcompound("Ca3Si(CO3)(SO4)(OH)6", "Calcium Silicon");
  mkcompound("Ca4B4(BO4)(SiO4)3(OH)3", "Calcium");
  mkcompound("Ca6Al2(SO4)3(OH)12", "Calcium Aluminum");
  mkcompound("CaAl2Si2O8", "Calcium aluminum silicate");
  mkcompound("CaAl2Si3O10", "calcium aluminum silicate");
  mkcompound("CaAl2Si4O12", "calcium aluminum silicate");
  mkcompound("CaAl2Si6O16", "Calcium Aluminum Silicate");
  mkcompound("CaAl2Si6O16", "calcium aluminum silicate");
  mkcompound("CaAl2Si7O18", "calcium aluminum silicate");
  mkcompound("CaAl3PO4SO4(OH)6", "Calcium Aluminum Phosphate Sulfate");
  mkcompound("CaB2Si2O8", "Calcium boron silicate");
  mkcompound("CaB3O4(OH)3", "Calcium Borate Hydroxide");
  mkcompound("CaBSiO4(OH)", "Calcium Boron Silicate Hydroxide");
  mkcompound("CaC2O4", "Calcium Oxalate");
  mkcompound("CaCO3", "Calcium Carbonate");
  mkcompound("CaCuAsO4(OH)", "Calcium Copper Arsenate Hydroxide");
  mkcompound("CaF2", "Calcium Fluoride");
  mkcompound("CaFe(CO3)2", "Calcium Iron Carbonate");
  mkcompound("CaFe3OSi2O7(OH)", "Calcium Iron Silicate Hydroxide");
  mkcompound("CaFeSi2O6", "Calcium Iron Silicate");
  mkcompound("CaMg(CO3)2", "Calcium Magnesium Carbonate");
  mkcompound("CaMgB6O11", "Calcium Magnesium Borate");
  mkcompound("CaMgSi2O6", "Calcium Magnesium Silicate");
  mkcompound("CaMoO4", "Calcium Molybdenate");
  mkcompound("CaSi2O4(OH)2", "calcium silicate");
  mkcompound("CaSiO3", "Calcium Silicate");
  mkcompound("CaSO4", "Calcium Sulfate");
  mkcompound("CaTiSiO5", "Calcium Titanium Silicate");
  mkcompound("CaWO4", "Calcium Tungstate");
  mkcompound("CaY2Be2Si2O10", "Calcium Yttrium Beryllium Silicate");
  mkcompound("CaZnSiO4", "Calcium Zinc Silicate");
  mkcompound("CdS", "Cadmium Sulfide");
  mkcompound("Co3(AsO4)2", "Cobalt Arsenate");
  mkcompound("Co3S4", "Cobalt Sulfide");
  mkcompound("CoAs3", "Cobalt Arsenide");
  mkcompound("CoCO3", "Cobalt Carbonate");
  mkcompound("Cu(UO2)2(AsO4)2", "Copper Uranyl");
  mkcompound("Cu(UO2)2(PO4)2", "Copper Uranyl Phosphate");
  mkcompound("Cu(UO2)2(PO4)2", "Copper Uranyl");
  mkcompound("Cu(UO2)2Si2O7", "Copper Uranyl Silicate");
  mkcompound("Cu12As4S13", "Copper Arsenic Sulfide");
  mkcompound("Cu12Sb4S13", "Copper Antimony Sulfide");
  mkcompound("Cu18Al2(AsO4)3(SO4)3(OH)27", "Copper");
  mkcompound("Cu19(NO3)2Cl4(OH)32", "Copper Nitrate");
  mkcompound("Cu19SO4Cl4(OH)32", "Copper Sulfate");
  mkcompound("Cu2(CO3)(OH)2", "Copper Carbonate Hydroxide");
  mkcompound("Cu2AsO4(OH)", "Copper Arsenate Hydroxide");
  mkcompound("Cu2Cl(OH)3", "Copper chloride hydroxide");
  mkcompound("Cu2Pb5CO3(SO4)3(OH)6", "Copper Lead Carbonate Sulfate");
  mkcompound("Cu2PO4(OH)", "Copper Phosphate Hydroxide");
  mkcompound("Cu2S", "Copper Sulfide");
  mkcompound("Cu3(CO3)2(OH)2", "Copper Carbonate Hydroxide");
  mkcompound("Cu3As", "Copper Arsenide");
  mkcompound("Cu3AsO4(OH)3", "Copper Arsenate Hydroxide");
  mkcompound("Cu3AsS4", "Copper Arsenic Sulfide");
  mkcompound("Cu3PO4(OH)3", "Copper Phosphate Hydroxide");
  mkcompound("Cu3SO4(OH)4", "Copper Sulfate Hydroxide");
  mkcompound("Cu4Al2SO4(OH)12", "Copper Aluminum");
  mkcompound("Cu4SO4(OH)6", "Copper Sulfate Hydroxide");
  mkcompound("Cu5(PO4)2(OH)4", "Copper Phosphate Hydroxide");
  mkcompound("Cu5(SiO3)4(OH)2", "Copper Silicate Hydroxide");
  mkcompound("Cu5FeS4", "Copper Iron Sulfide");
  mkcompound("Cu6Al(SO4)Cl(OH)12", "Copper Aluminum");
  mkcompound("Cu8Si8O22(OH)4", "Copper Silicate");
  mkcompound("Cu9S5", "Copper Sulfide");
  mkcompound("CuAl6(PO4)4(OH)8", "Copper Aluminum");
  mkcompound("CuFe2S3", "Copper Iron Sulfide");
  mkcompound("CuFeS2", "Copper Iron Sulfide");
  mkcompound("CuPb2Cl2(OH)4", "Copper Lead Chloride Hydroxide");
  mkcompound("CuPbSbS3", "Copper lead antimony sulfide");
  mkcompound("CuS", "Copper Sulfide");
  mkcompound("CuSiO3", "copper silicate");
  mkcompound("CuSiO3", "copper silicate");
  mkcompound("CuSO4", "Copper Sulfate");
  mkcompound("Fe2(TeO3)3", "Iron Tellurite");
  mkcompound("Fe24(AlO6)(PO4)17(OH)12", "Iron Aluminum");
  mkcompound("Fe2Al9Si4O22(OH)2", "Iron Aluminum Silicate Hydroxide");
  mkcompound("Fe3(PO4)2", "Iron Phosphate");
  mkcompound("Fe3Al2(SiO4)3", "Iron Aluminum Silicate");
  mkcompound("Fe5(PO4)3(OH)5", "Iron Phosphate");
  mkcompound("Fe6(PO4)4(OH)5", "Iron Phosphate");
  mkcompound("FeAl2(PO4)2(OH)2", "Iron Aluminum");
  mkcompound("FeAs2", "Iron Arsenide");
  mkcompound("FeAsO4-2H4O", "Zinc Arsenate");
  mkcompound("FeAsS", "Iron Arsenide Sulfide");
  mkcompound("FeCO3", "Iron Carbonate");
  mkcompound("FePb3Sn4Sb2S14", "Iron Lead Tin Antimony Sulfide");
  mkcompound("FePO4", "Iron Phosphate");
  mkcompound("FeS2", "Iron Sulfide");
  mkcompound("FeSb2S4", "Iron Antimony Sulfide");
  mkcompound("FeSO4", "Iron Sulfate");
  mkcompound("FeWO4", "Iron tungstate");
  mkcompound("HgS", "Mercury Sulfide");
  mkcompound("Ir3Fe", "Iridium Iron");
  mkcompound("K2(UO2)2(SiO3)2(OH)2", "Potassium Uranyl");
  mkcompound("K2(UO2)2(VO4)2", "Potassium Uranyl");
  mkcompound("K2Ca2Mg(SO4)4", "Potassium Calcium");
  mkcompound("K2Ca4Al2Be4Si24O60", "Potassium Calcium");
  mkcompound("K2Mg(SO4)2", "Potassium Magnesium");
  mkcompound("K4(UO2)6(SO4)3OH10", "Potassium Uranyl");
  mkcompound("KAlSi2O6", "Potassium Aluminum Silicate");
  mkcompound("KAlSi3O8", "Potasium Aluminum Silicate");
  mkcompound("KAlSi3O8", "Potassium aluminum silicate");
  mkcompound("KCaAl3Si5O16", "potassium calcium");
  mkcompound("KCl", "Potassium Chloride");
  mkcompound("KMg3AlSi3O10(OH)2", "Potassium magnesium aluminum");
  mkcompound("KMgCl3", "Potassium Magnesium Chloride");
  mkcompound("KNO3", "Potassium Nitrate");
  mkcompound("LiAlSi2O6", "Lithium Aluminum Silicate");
  mkcompound("LiAlSiO4", "Lithium Aluminum silicate");
  mkcompound("Mg(UO2)2Si2O7", "Magnesium Uranyl");
  mkcompound("Mg2Al4Si5O18", "Magnesium Aluminum Silicate");
  mkcompound("Mg2CO3(OH)2", "Magnesium Carbonate");
  mkcompound("Mg3Al2(SiO4)3", "Magnesium Aluminum Silicate");
  mkcompound("Mg3B7O13Cl", "Magnesium Borate Chloride");
  mkcompound("Mg3Si4O10(OH)2", "Magnesium Silicate Hydroxide");
  mkcompound("Mg5(CO3)4(OH)2", "Magnesium Carbonate");
  mkcompound("Mg6Cr2CO3(OH)16", "Magnesium Chromium");
  mkcompound("MgAlBO4", "Magnesium Aluminum Borate");
  mkcompound("MgCO3", "Magnesium Carbonate");
  mkcompound("MgSiO3", "Magnesium Silicate");
  mkcompound("MgSO4", "Magnesium Sulfate");
  mkcompound("Mn3Al2(SiO4)3", "Manganese Aluminum Silicate");
  mkcompound("MnBO2(OH)", "Manganese Borate Hydroxide");
  mkcompound("MnCO3", "Manganese Carbonate");
  mkcompound("MnPO4", "Manganese Phosphate");
  mkcompound("MnWO4", "Manganese tungstate");
  mkcompound("MoS2", "Molybdenum Sulfide");
  mkcompound("Na22K(SO4)9(CO3)2Cl", "Sodium Potassium Sulfate Carbonate");
  mkcompound("Na2Al2Si3O10", "sodium aluminum silicate");
  mkcompound("Na2B4O6(OH)2", "Sodium Borate Hydroxide");
  mkcompound("Na2B4O7", "sodium borate");
  mkcompound("Na2Ca(CO3)2", "Sodium Calcium Carbonate");
  mkcompound("Na2Ca(SO4)2", "Sodium Calcium Sulfate");
  mkcompound("Na2Ca2Al6Si9O30", "sodium calcium");
  mkcompound("Na2CaUO2(CO3)3", "Sodium Calcium Uranyl");
  mkcompound("Na2Mg(SO4)2", "Sodium Magnesium Sulfate");
  mkcompound("Na2SO4", "Sodium Sulfate");
  mkcompound("Na2Ti2Si2O9", "Sodium Titanium Silicate");
  mkcompound("Na2Zr(SiO3)3", "Sodium Zirconium");
  mkcompound("Na2ZrSi6O15", "Sodium Zirconium Silicate");
  mkcompound("Na3(FeMg)4FeSi8O22(OH)2", "Sodium Iron Magnesium");
  mkcompound("Na3(HCO3)(CO3)", "Sodium Bicarbonate");
  mkcompound("Na3AlF6", "Sodium Aluminum Fluoride");
  mkcompound("Na4Al3(SiO4)3Cl", "Sodium Aluminum Silicate Chloride");
  mkcompound("Na7CaAl6Si6O24(CO3)2", "Sodium Calcium Aluminum Silicate");
  mkcompound("NaAl3(PO4)2(OH)4", "Sodium Aluminum Phosphate Hydroxide");
  mkcompound("NaAl3(PO4)2(OH)4", "Sodium Aluminum");
  mkcompound("NaAlSi2O6", "Sodium Aluminum Silicate");
  mkcompound("NaAlSi2O6", "Sodium Aluminum Silicate");
  mkcompound("NaAlSi3O8", "Sodium aluminum silicate");
  mkcompound("NaBeSi3O7(OH)", "Sodium Beryllium Silicate Hydroxide");
  mkcompound("NaCa2Al5Si13O36", "sodium calcium");
  mkcompound("NaCa2Al5Si5O20", "sodium calcium aluminum");
  mkcompound("NaCa2Si3O8(OH)", "Sodium Calcium Silicate Hydroxide");
  mkcompound("NaCa3UO2SO4(CO3)3F", "Sodium Calcium");
  mkcompound("NaCaB5O6(OH)6", "Sodium Calcium Borate");
  mkcompound("NaCl", "Sodium Chloride");
  mkcompound("NaFe9(PO4)6(OH)10", "Sodium Iron");
  mkcompound("NaFeSi2O6", "Sodium Iron Silicate");
  mkcompound("NaHCO3", "Sodium Bicarbonate");
  mkcompound("NaNO3", "Sodium Nitrate");
  mkcompound("NH4B5O6(OH)4", "Ammonium Borate Hydroxide");
  mkcompound("NH4Cl", "Ammonium Chloride");
  mkcompound("Ni3(AsO4)2", "Nickel Arsenate");
  mkcompound("NiAs", "Nickel Arsenide");
  mkcompound("NiS", "Nickel Sulfide");
  mkcompound("Pb21Cu20Cl42(OH)40", "Lead Copper Chloride Hydroxide");
  mkcompound("Pb26Cu24Ag10Cl62(OH)48", "Lead Copper");
  mkcompound("Pb2Al4(CO3)4(OH)8", "Lead Aluminum");
  mkcompound("Pb2CO3Cl2", "Lead Carbonate Chloride");
  mkcompound("Pb2Cu(AsO4)(SO4)OH", "Lead Copper Arsenate Sulfate");
  mkcompound("Pb2Cu(PO4)(SO4)OH", "Lead Copper Phosphate Sulfate");
  mkcompound("Pb3Ca2(AsO4)3Cl", "Lead Calcium Arsenate Chloride");
  mkcompound("Pb3Cl4F(OH)2", "Lead Chloride Fluoride Hydroxide");
  mkcompound("Pb4Fe(AsO4)2Cl4", "Lead Iron Arsenate Chloride");
  mkcompound("Pb4FeSb6S14", "Lead Iron Antimony Sulfide");
  mkcompound("Pb4SO4(CO3)2(OH)2", "Lead Sulfate Carbonate Hydroxide");
  mkcompound("Pb5(AsO4)3Cl", "Lead Chloroarsenate");
  mkcompound("Pb5(PO4)3Cl", "Lead Chlorophosphate");
  mkcompound("Pb5(VO4)3Cl", "Lead Chlorovanadate");
  mkcompound("Pb5Cu4Cl10(OH)8", "Lead Copper Chloride");
  mkcompound("Pb5Sb4S11", "Lead Antimony Sulfide");
  mkcompound("Pb9As4S15", "Lead Arsenic Sulfide");
  mkcompound("Pb9Sb22S42", "Lead Antimony Sulfide");
  mkcompound("PbClOH", "Lead Chloride Hydroxide");
  mkcompound("PbCO3", "Lead Carbonate");
  mkcompound("PbCrO4", "Lead Chromate");
  mkcompound("PbCu(VO4)(OH)", "Lead Copper Vanadinate Hydroxide");
  mkcompound("PbCuSO4(OH)2", "Lead Copper Sulfate Hydroxide");
  mkcompound("PbFe3AsO4SO4(OH)6", "Lead Iron Arsenate Sulfate");
  mkcompound("PbMoO4", "Lead Molybdate");
  mkcompound("PbO2", "Lead Oxide");
  mkcompound("PbS", "Lead Sulfide");
  mkcompound("PbSO4", "Lead Sulfate");
  mkcompound("PbZn(VO4)(OH)", "Lead Zinc Vanadate Hydroxide");
  mkcompound("Sb2OS2", "Antimony Oxysulfide");
  mkcompound("Sb2S3", "Antimony Sulfide");
  mkcompound("Sb3O6(OH)", "Antimony Oxide Hydroxide");
  mkcompound("SbAs", "Antimony Arsenic");
  mkcompound("SiC", "Silicon Carbide");
  mkcompound("SiO2", "Silicon dioxide");
  mkcompound("SiO2", "Silicon Dioxide");
  mkcompound("SnO2", "Tin Oxide");
  mkcompound("SrAl3PO4SO4(OH)6", "Strontium Aluminum Phosphate Sulfate");
  mkcompound("SrCO3", "Strontium Carbonate");
  mkcompound("SrSO4", "Strontium Sulfate");
  mkcompound("TiO2", "Titanium Oxide");
  mkcompound("YPO4", "Yttrium Phosphate");
  mkcompound("Zn2(PO4)(OH)", "Zinc Phosphate Hydroxide");
  mkcompound("Zn2AsO4(OH)", "Zinc Arsenate Hydroxide");
  mkcompound("Zn2SiO4", "Zinc Silicate");
  mkcompound("Zn3(AsO4)2", "Zinc Arsenate");
  mkcompound("Zn3(PO4)2", "Zinc Phosphate");
  mkcompound("Zn4Si2O7(OH)2", "Zinc Silicate");
  mkcompound("Zn5(CO3)2(OH)6", "Zinc Carbonate Hydroxide");
  mkcompound("Zn8Cu4(TeO3)3(OH)18", "Zinc Copper Tellurite Hydroxide");
  mkcompound("ZnAl2O4", "Zinc Aluminum Oxide");
  mkcompound("ZnCO3", "Zinc carbonate");
  mkcompound("ZrSiO4", "Zirconium Silicate");
  mkcompound("NaCl", "Salt");
  mkcompound("SiO2", "Quartz");
  mkcompound("C6H12O6", "Glucose");
  mkcompound("CH2Oorg", "Organic Carbohydrate");
  
  mkcompound("(NH4)2S", "Ammonium Sulphide");
  mkcompound("(NH4)2SO4", "Ammonium Sulphate");
  mkcompound("NH4OH", "Ammonium Hydroxide", 273-72, 273+36);
}
};

static Initialise init;

AmountM
parseFormula(Lexer& l, bool single = false, XString end = "")
{
  AmountM amt;
  
  l.FpNum = 1;
  l.CcNum = 0;
  l.NumLt = 0;
  l.NumSg = 0;
  l.CStrn = 0;
  l.CChar = 0;
  l.CComm = 0;
  l.CppCm = 1;
  l.AsmCm = 0;
  l.AlNum = 1;
  l.IgnSp = 1;
  l.IgnNl = 1;
  l.IgnCm = 1;
  l.SetPunct("-> => ==");
  l.SetIdentChars("_-./()");
  l.SetStartChars("");

  XString tok;
  int     type;
  while ((type = l.GetToken(tok)) != Lexer::TOK_END && tok != end)
  {
    EData e;
    switch (type)
    {
      case Lexer::TOK_IDENT:
	if (Substance.find(canonical(tok)) == Substance.end())
	  mkcompound(canonical(tok), tok);
	amt[canonical(tok)]++;
	break;
      case Lexer::TOK_NUMBER:
	{
	  double  n = strtod(tok, 0);
	  AmountM a = parseFormula(l, true);
	  a *= n;
	  amt += a;
	}
	break;
      default:
	if (tok == "[")
	{
	  AmountM a = parseFormula(l, false, "]");
	  amt += a;
	}
	else if (tok == "{")
	{
	  AmountM a = parseFormula(l, false, "}");
	  amt += a;
	}
	else if (tok == "=>" || tok == "==" || tok == ">" || tok == ">>")
	{
	  l.PutToken(tok);
	  single = true;
	}
	else
	  continue;
	break;
    }
    if (single)
      break;
  }
  return amt;
}

AmountM
parseFormula(const char *str)
{
  Lexer l(str);
  return parseFormula(l);
}

Reaction::Reaction(const char *istr, const char *ostr, double strength=1)
{
  in  = parseFormula(istr);
  out = parseFormula(ostr);
  str = (strength > 1 ? 1 : strength);
}

int
Reactions::find(const char *istr)
{
  AmountM a = parseFormula(istr);
  for (int i = 0; i < r.size(); i++)
    if (a == r[i].in)
      return i;
  return -1;
}

AmountM
getAmounts(const XString& sim, double mass)
{
  AmountM a;
  AmountM b;
  double totmass = 0;
  for (int i = 0; i < arraysize(elem_def); i++)
  {
    XString sym = elem_def[i].b.symbol;
    if (sym)
    {
      double amt;
      if (sim == "land" || sim == "crust")
	amt = elem_def[i].a.crustal;
      else if (sim == "sea")
	amt = elem_def[i].a.sea;
      else if (sim == "meteorite")
	amt = elem_def[i].a.meteorite;
      else if (sim == "stream")
	amt = elem_def[i].a.stream;
      else if (sim == "solar")
	amt = elem_def[i].a.solar;
      else if (sim == "universe")
	amt = elem_def[i].a.universe;
      else if (sim == "human")
	amt = elem_def[i].a.human;
      a[sym] = amt;
      totmass += amt * elem_def[i].b.weight;
    }
  }
  double na = Na * mass / totmass;
  for (AmountM::iterator p = a.begin(); p != a.end(); p++)
  {
    double amt = floor(na * p->second);
    if (amt >= 1)
      b[p->first] = amt;
  }
  return b;
}

void
doReaction(const Reactions& r, AmountM& a, int num=1)
{
  AmountM last;
  int nr = r.size();
  if (num <= 0)
    num = 1000;
  while (num-- > 0 && a != last)
  {
    last = a;
    for (int i = 0; i < nr; i++)
    {
      double amt = floor(r[i].test(a) * r[i].str);
      if (amt > 0)
      {
	a += (r[i].out - r[i].in) * amt;
      }
    }
  }
}

#ifdef TEST_PARSEFRM

void
dsp(const EData& e)
{
  if (e.name == "" || e.sym == "")
  {
    cout << "???" << endl;
    return;
  }
  if (e.melt > 0 && e.boil > 0 && e.tcrit > 0 && e.pcrit > 0)
  {
    cout << xStrFormat("Symbol: %-12s   Name: %-24s\n"
	"    wt %-6.2f   melt %6.1fK   boil %6.1fK  "
	"tcrit %6.1fK   pcrit %5.1f bar\n",
	CCP(e.sym), CCP(e.name), e.weight, e.melt, e.boil,
	e.tcrit, e.pcrit);
  }
  else if (e.melt > 0 && e.boil > 0 && e.tcrit > 0)
  {
    cout << xStrFormat("Symbol: %-12s   Name: %-24s\n"
	"    wt %-6.2f   melt %6.1fK   boil %6.1fK  "
	"tcrit %6.1fK\n",
	CCP(e.sym), CCP(e.name), e.weight, e.melt, e.boil,
	e.tcrit);
  }
  else if (e.melt > 0 && e.boil > 0)
  {
    cout << xStrFormat("Symbol: %-12s   Name: %-24s\n"
	"    wt %-6.2f   melt %6.1fK   boil %6.1fK\n",
	CCP(e.sym), CCP(e.name), e.weight, e.melt, e.boil);
  }
  else if (e.melt > 0)
  {
    cout << xStrFormat("Symbol: %-12s   Name: %-24s    wt %-6.2f   melt %6.1fK\n",
	CCP(e.sym), CCP(e.name), e.weight, e.melt);
  }
  else
  {
    cout << xStrFormat("Symbol: %-12s   Name: %-24s    wt %-6.2f\n",
	CCP(e.sym), CCP(e.name), e.weight);
  }
  AmountM amt;
  double wt = compound(e.sym, e.name, &amt).weight;
  if (wt != e.weight)
    cout << "Weight = " << wt << endl;
  if (amt.size() > 1)
  {
    for (AmountM::iterator p = amt.begin(); p != amt.end(); p++)
      cout << xStrFormat("%-8s %g\n", CCP(p->first), p->second);
  }
}

ostream&
dspfrm(const AmountM& a, bool nl = false)
{
  bool start = true;
  double tot = 0;
  for (AmountM::const_iterator p = a.begin(); p != a.end(); p++)
    tot += p->second * Substance[p->first].weight;
  for (AmountM::const_iterator p = a.begin(); p != a.end(); p++)
  {
    XString name = Substance[canonical(p->first)].name;
    if (p->second >= 0.1)
    {
      XString what;
      if (canonical(name) == canonical(p->first))
	what = name;
      else
	what = name | " (" | p->first | ")";
      if (nl)
      {
	double wt = p->second * Substance[p->first].weight;
	if (wt*100/tot > 0.005)
	  cout << xStrFormat("%6.2f%% ", wt*100/tot) << what << endl;
      }
      else
      {
	if (!start)
	  cout << " + ";
	if (p->second != 1)
	  cout << p->second << " " << what;
	else
	  cout << what;
      }
      start = false;
    }
  }
  return cout;
}

int
parseFile(FILE *fp, Reactions& r)
{
  char buff[256];
  int n = 0;
  while (fgets(buff, sizeof(buff), fp) != NULL)
  {
    strtok(buff, "#\r\n");
    char *p = strtok(buff, "=>");
    char *ap = NULL;
    char *bp = NULL;
    double amt = 0;
    if (p)
    {
      ap = p;
      p = strtok(NULL, "=>");
    }
    if (p)
    {
      bp = p;
      p = strtok(NULL, "=>");
    }
    if (p)
    {
      amt = strtod(p, 0);
    }
    if (ap && bp && amt > 0)
      n = r.add(ap, bp, amt);
    AmountM ael, bel;
    for (AmountM::iterator p = r[n].in.begin(); p != r[n].in.end(); p++)
    {
      AmountM el;
      canonical(p->first, &el);
      el *= p->second;
      ael += el;
    }
    if (r[n].out.size() > 0)
    {
      for (AmountM::iterator p = r[n].out.begin(); p != r[n].out.end(); p++)
      {
	AmountM el;
	canonical(p->first, &el);
	el *= p->second;
	bel += el;
      }
      AmountM diff = ael - bel;
      bool bad = false;
      for (AmountM::iterator p = diff.begin(); p != diff.end(); p++)
      {
	if (fabs(p->second) > 1e-6)
	{
	  bad = true;
	  cout << xStrFormat("%-5s LHS %-8.4g  RHS %.4g", 
	      CCP(p->first), ael[p->first], bel[p->first]) << endl;
	}
      }
      if (bad)
      {
	dspfrm(r[n].in);
	cout << " => ";
	dspfrm(r[n].out);
	cout << endl << endl;
      }
    }
  }
  return n;
}

struct option longopts[] =
{
  { "help",          no_argument,       NULL,    'h' },
  { "version",       no_argument,       NULL,    'V' },
  { "number",        no_argument,       NULL,    'n' },
  { "formula",       no_argument,       NULL,    'f' },
  { 0, 0, 0, 0 }
};

const char *shortopts = "hVn:N:f:z";

int
main(int argc, char **argv)
{
  XString sim;
  XString frm;
  int num = 100;
  int nn = 1;
  bool display = false;
  int c;
  while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != EOF)
  {
    switch (c)
    {
      case 'h':
	break;
      case 'V':
        break;
      case 'n':
	num = atoi(optarg);
	break;
      case 'N':
	nn = atoi(optarg);
	break;
      case 'f':
	frm = optarg;
	break;
      case 'z':
	display = true;
	break;
    }
  }
  for (int i = optind; i < argc; i++)
  {
    sim = optarg;
  }

#include "tmp/3"

  Reactions r;
  int nr = 0;
  nr = r.add("2H", "H2", 1);
  nr = r.add("2O", "O2", 1);
  nr = r.add("2N", "N2", 1);
  nr = r.add("2H2+O2", "2H2O", 0.9);

  // nr = r.add("N2+O2", "2NO", 0.1);
  // nr = r.add("N2+2O2", "2NO2", 0.1);
  // nr = r.add("NO+H2O", "H2NO2", 0.2);
  // nr = r.add("NO2+H2O", "H2NO3", 0.2);

  // nr = r.add("C + O2", "CO2", 0.2);
  // nr = r.add("6 CO2 + 6H2O", "C6H12O6 + 6 O2", 0.2);
  // nr = r.add("C6H12O6 + 6O2", "6 CO2 + 6H2O", 0.1);

  if (frm)
  {
    FILE *fp = fopen(frm, "r");
    if (fp)
    {
      nr = parseFile(fp, r);
      fclose(fp);
    }
  }
  
  if (sim)
  {
    AmountM a = getAmounts(sim, 1);
    AmountM last;
    for (int n = 0; n < num; n++)
    {
      cout << "----------------- " << n << " -----------------" << endl;
      dspfrm(a/1000000, true);
      cout << endl << endl;
      doReaction(r, a, nn);
      if (a == last)
      {
	cout << endl << "------ Terminated after " << n 
	     << " iteration" << (n==1 ? "" : "s") << endl;
	break;
      }
      last = a;
    }
    if (display)
    {
      cout << endl;
      for (int i = 0; i < nr; i++)
      {
	dspfrm(r[i].in) << "\t";
	dspfrm(r[i].out) << "\t";
	cout << r[i].str << endl;
      }
    }
    exit(1);
  }

  char buff[256];
  while (fgets(buff, sizeof(buff), stdin) != NULL)
  {
    AmountM a, ael;
    AmountM b, bel;
    XString tok;
    Lexer l(buff);
    a = parseFormula(l);
    l.GetToken(tok);
    if (tok == "=>" || tok == "==" || tok == ">" || tok == ">>")
      b = parseFormula(l);
    for (AmountM::iterator p = a.begin(); p != a.end(); p++)
    {
      AmountM el;
      canonical(p->first, &el);
      el *= p->second;
      ael += el;
    }
    if (b.size() > 0)
    {
      for (AmountM::iterator p = b.begin(); p != b.end(); p++)
      {
	AmountM el;
	canonical(p->first, &el);
	el *= p->second;
	bel += el;
      }
      AmountM diff = ael - bel;
      bool bad = false;
      for (AmountM::iterator p = diff.begin(); p != diff.end(); p++)
      {
	bad = true;
	if (fabs(p->second) > 1e-6)
	  cout << xStrFormat("%-5s LHS %-8.4g  RHS %.4g", 
	      CCP(p->first), ael[p->first], bel[p->first]) << endl;
      }
      if (bad)
      {
	dspfrm(a);
	cout << " => ";
	dspfrm(b);
	cout << endl << endl;
      }
    }
    else
    {
      for (int n = 0; n < 100; n++)
      {
	for (int i = 0; i <= nr; i++)
	{
	  double amt = floor(r[i].test(a) * r[i].str);
	  if (amt > 0)
	  {
	    a += (r[i].out - r[i].in) * amt;
	  }
	}
	dspfrm(a, true);
	cout << endl << endl;
      }
    }
  }
  // for (ElemM::iterator p = Substance.begin(); p != Substance.end(); p++)
  //   dsp(p->second);
  return 0;
}

#endif
