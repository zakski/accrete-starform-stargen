/*
  tides.cc
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
  $RCSfile$
    
  $Date$
  $Revision$
          
  $Log$
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

#include <xstring.h>
#include <xstrvec.h>
#include <fsplit.h>

#include "const.h"

double
tide(double r, double m, double d)
{
  double r0 = d - r;
  double r1 = d + r;
  double t0 = G * m / (r0 * r0);
  double t1 = G * m / (r1 * r1);
  return t0 - t1;
}

// returns (s/t2)2 / s = s/t4
// braking 1/t2

double
tidalbraking(double r, double m, double R, double M)
{
  double t = tide(r, M, R);
  return Me/m * pow(t, 2) / r;
}


// m/s3 . s . 1/m . m2 . 1/s6 = m2 / s8

double
gsbraking(double r, double m, double d)
{
  double pr = 2.0 + 2e-2 / sqrt(m);
  double rel_mass = pow(r, 3);
  double b = r * rel_mass * r * pow(m, pr) / pow(d, 6);
  return b;
}



// Orbital velocity
// acc = GM/r2 = v2/r = w2r
// v = sqrt(GM/r)
// w = sqrt(GM/r3)

double
orbvel(double m, double r)
{
  return sqrt(G * m / r);
}

double
ovdiff(double r, double m, double d)
{
  double r0 = d - r;
  double r1 = d + r;
  double t0 = orbvel(r0, m);
  double t1 = orbvel(r1, m);
  return t1 - t0;
}

double
calcb(double m, double r, double M, double d)
{
  double t = tide(r, M, d);
  return Gy * pow(t, 2) / r / m;
}

// calc  = s.m.s-6
//       = m.s-5
// dv.da = s.t-1 . s.t-2
//       = s2.t-3
//       = m.r-2 . sqrt(m.r-1)
// sf    = Rp . Mp-1 . Ms2 . Ro-6
//       = m.s-5
// dw    = t-2

double
braking(double m, double r, double M, double d)
{
  double b = 
    (r / 6422000.0)  *
    (Me / m)         *
    pow(M/Msol, 2.0) *
    pow(AU / d, 6.0) *
    1.3E-6;
  return b;
}

struct UnitT
{
  const char *name;
  double      value;
};

UnitT Unit[] =
{
  { "Msol", Msol },
  { "sol",  Msol },
  { "Me",   Me   },
  { "AU",   AU   },
  { "km",   1000 },
  { "Re",   Re   },
  { "kg",   1    },
  { 0, 0 }
};

double
unit(const char *p, double def)
{
  if (p && *p)
  {
    for (int i = 0; Unit[i].value > 0; i++)
    {
      if (strcasecmp(Unit[i].name, p) == 0)
	return Unit[i].value;
    }
  }
  return def;
}


struct option longopts[] =
{
  { "help",          no_argument,       NULL,    'h' },
  { "radius",        required_argument, NULL,    'r' },
  { "distance",      required_argument, NULL,    'd' },
  { "mass",          required_argument, NULL,    'm' },
  { "primary",       required_argument, NULL,    'M' },
  { 0, 0, 0, 0 }
};

const char *shortopts = "hr:d:m:M:R:";

int
main(int argc, char **argv)
{
  double M = Msol;
  double m = Me;
  double d = 1 * AU;
  double r = Re;
  char *p;
  int c;
  while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != EOF)
  {
    switch (c)
    {
      case 'h':
	break;
      case 'M':
	M = strtod(optarg, &p);
	M *= unit(p, Msol);
	break;
      case 'm':
	m = strtod(optarg, &p);
	m *= unit(p, Me);
	break;
      case 'd':
      case 'R':
	d = strtod(optarg, &p);
	d *= unit(p, AU);
	break;
      case 'r':
	r = strtod(optarg, &p);
	r *= unit(p, Re);
	break;
    }
  }

  double fudge = braking(Me, Re, Msol, AU) / calcb(Me, Re, Msol, AU);
  double cb = calcb(m, r, M, d);
  
  printf("\n");
  printf("Planet %g Me, radius %.0f km, %.0f km from mass %g Me\n",
         m/Me, r / 1000, d / 1000, M/Me);
  printf("braking        %g rad/sec/Gy\n", cb * fudge);
  printf("Calc. braking  %g rad/sec/Gy\n", braking(m, r, M, d));
  printf("Fudge factor   %g\n", fudge);
  printf("\n");
  return 0;
}


