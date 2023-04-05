/* planet.c */
/* planet generating program */
/* Copyright 1997 Torben AE. Mogensen */

/* The program generates planet maps based on recursive spatial subdivision */
/* of a box containing the globe. The output is a colour PPM bitmap. */

/* Usage: planet [options] */
/* options: */
/*   -s seed	       Specifies seed as number between 0.0 and 1.0 */
/*   -w width	       Specifies width in pixels, default = 800 */
/*   -h height	       Specifies height in pixels, default = 600 */
/*   -m magnification  Specifies magnification, default = 1.0 */
/*   -o output-file    Specifies output file, default = stdout */
/*   -l longitude      Specifies longitude of centre in degrees, default = 0.0 */
/*   -L latitude       Specifies latitude of centre in degrees, default = 0.0 */
/*   -G gridsize       Specifies vertical gridsize in degrees, default = 0.0 (no grid) */
/*   -g gridsize       Specifies horisontal gridsize in degrees, default = 0.0 (no grid) */
/*   -i init_alt       Specifies initial altitude (default = -0.015) */
/*   -c		       Colour depends on latitude (default: only altitude) */
/*   -pprojection      Specifies projection: m = Mercator (default) */
/*					     p = Peters */
/*					     s = Stereographic */
/*					     o = Orthographic */
/*					     g = Gnomic */
/*					     a = Area preserving azimuthal */
/*                                           c = Conical (conformal) */
/*					     f = Find match, see below */

/* With the -pf option a map must be given on standard input. */
/* This map is 9 lines of 27 characters. The characters are:  */
/*    . : very strong preference for water (value=8)	      */
/*    , : strong preference for water (value=4)		      */
/*    : : preference for water (value=2)		      */
/*    ; : weak preference for water (value=1)		      */
/*    - : don't care (value=0)				      */
/*    * : weak preference for land (value=1)		      */
/*    o : preference for land (value=2)			      */
/*    O : strong preference for land (value=4)		      */
/*    @ : very strong preference for land (value=8)	      */
/*							      */
/* The program tries seeds starting from the specified and    */
/* successively outputs the seed (and rotation) of the best   */
/* current match, together with a small map of this.	      */
/* This is all ascii, no bitmap is produced.		      */


/* Some colour constants are needed: BLACK, WHITE, BLUE0, BLUE1 (a range for sea) /*
/* LAND0, LAND1 should give a range where LAND0 is green (used for low land) */
/* and LAND1 is brown or yellow (used for high land). All integer numbers */
/* between LAND0 and LAND1 are assumed to be on this scale. */
/* The colours may optionally be modified according to latitude to move the */
/* icecaps lower closer to the poles, with a corresponding change in land colours. */

/* The Mercator map at magnification 1 is scaled to fit the Width */
/* it uses the full height (it could extend infinitely) */
/* The orthographic projections are scaled so the full view would use the */
/* full Height. Areas outside the globe are coloured black. */
/* Stereographic and gnomic projections use the same scale as orthographic */
/* in the center of the picture, but distorts scale away from the center. */

/* It is assumed that pixels are square */
/* I have included a procedure that will print the maps as ppm */
/* bitmaps (portable pixel map) on standard output. */

/* I have tried to avoid using machine specific features, so it should */
/* be easy to port the program to any machine. Beware, though that due */
/* to different precision on different machines, the same seed numbers */
/* can yield very different planets. */
/* The primitive user interface is a result of portability concerns */

#include <stdio.h>
#include <errno.h>
#include <math.h>

#define BLACK 0
#define BLUE0 1
#define BLUE1 9
#define LAND0 10
#define LAND1 18
#define WHITE 19

/* these three values can be changed to change world characteristica */

#define Dda0 .2 /* initial altitude variation (suggest 0.2) */
#define Ddda .85  /* rate of decrease of altitude variation (suggest .85) */

#define Da0 2.0	 /* initial scale (size of box) */
#define DEG2RAD 0.017453292 /* pi/180 */
#define PI 3.1415926535897

double M  = -.015;  /* initial altitude (slightly below sea level) (suggest -.015) */
int Depth; /* depth of subdivisions */

double t1,t2,t3;
double r1,r2,r3,r4,r5,r6,r7,r8; /* seeds */
double longi,lat,scale;
int latic = 0; /* flag for latitude based colour */

int Width = 800, Height = 600;

unsigned char **col;
int cl0[60][10];

int rtable[] = {0,   0,	 0,  0,	 0,  0,	 0,  0,	 0,  0,	  0, 16, 32, 48, 64, 80, 96,112,128, 255};
int gtable[] = {0,   0, 16, 32, 48, 64, 80, 96,112,128, 255,240,224,208,192,176,160,144,128, 255};
int btable[] = {0, 255,255,255,255,255,255,255,255,255,	  0,  4,  8, 12, 16, 20, 24, 28, 32, 255};

main(ac,av)
int ac;
char **av;
{
  void printppm();
  int i,j,k,l,c,view, planet0();
  int BACK = BLACK;
  double x,y,z,x1,y1,z1,zz, k1, y2, ymax, ymin;
  double scale1, vgrid, hgrid;
  double rand2(), log2(), planet1();
  double theta1, theta2, cos2, cla, sla, clo, slo;
  int errcount, best;
  int water = 0, land = 0;
  double rseed, increment = 0.000000001;
  FILE *outfile;
  char filename[256];

  t1 = exp(log(2.)/3.);	   /* dimension of box = (scale,t1*scale,t2*scale) */
  t2 = exp(2.*log(2.)/3.); /* so halving will keep the same relative scale */
  t3 = t2/2.;		   /* like A4 paper (but in 3 dimensions) */

  longi = 0.0;
  lat = 0.0;
  scale = 1.0;
  rseed = 0.123;
  view = 'm';
  vgrid = hgrid = 0.0;
  outfile = stdout;
  
  for (i = 1; i<ac; i++) {
    if (av[i][0] == '-') {
      switch (av[i][1]) {
	case 's' : sscanf(av[++i],"%lf",&rseed);
		   break;
	case 'w' : sscanf(av[++i],"%d",&Width);
		   break;
	case 'h' : sscanf(av[++i],"%d",&Height);
		   break;
	case 'm' : sscanf(av[++i],"%lf",&scale);
		   break;
	case 'o' : sscanf(av[++i],"%s",filename);
		   outfile = fopen(filename,"w");
		   if (outfile == NULL) {
		     fprintf(stderr,
			     "Could not open output file %s, error code = %d\n",
			     filename,errno);
		     exit(0);
		   }
		   break;
	case 'l' : sscanf(av[++i],"%lf",&longi);
		   break;
	case 'L' : sscanf(av[++i],"%lf",&lat);
		   break;
	case 'g' : sscanf(av[++i],"%lf",&vgrid);
		   break;
	case 'G' : sscanf(av[++i],"%lf",&hgrid);
		   break;
	case 'c' : latic = 1;
		   break;
	case 'b' : if (BACK == BLACK) BACK = WHITE; else BACK = BLACK;
		   break;
	case 'i' : sscanf(av[++i],"%lf",&M);
		   break;
	case 'p' : switch (view = av[i][2]) {
		     case 'm' : 
		     case 'p' : 
		     case 's' :
		     case 'o' :
		     case 'g' :
		     case 'a' :
		     case 'c' :
		     case 'f' : break;
		     default: fprintf(stderr,"Unknown projection: %s\n",av[i]);
			      exit(0);
		   }
		   break;
	default: fprintf(stderr,"Unknown option: %s\n",av[i]);
		 exit(0);
      }
    }
    else {
      fprintf(stderr,"Wrong option: %s\n\n",av[i]);
      fprintf(stderr,"Usage: planet [options]\n\n");
      fprintf(stderr,"options:\n");
      fprintf(stderr,"	-s seed		  Specifies seed as number between 0.0 and 1.0\n");
      fprintf(stderr,"	-w width	  Specifies width in pixels, default = 800\n");
      fprintf(stderr,"	-h height	  Specifies height in pixels, default = 600\n");
      fprintf(stderr,"	-m magnification  Specifies magnification, default = 1.0\n");
      fprintf(stderr,"	-o output-file	  Specifies output file, default = stdout\n");
      fprintf(stderr,"	-l longitude	  Specifies longitude of centre in degrees, default = 0.0\n");
      fprintf(stderr,"	-L latitude	  Specifies latitude of centre in degrees, default = 0.0\n");
      fprintf(stderr,"	-g gridsize	  Specifies vertical gridsize in degrees, default = 0.0 (no grid)\n");
      fprintf(stderr,"	-G gridsize	  Specifies horisontal gridsize in degrees, default = 0.0 (no grid)\n");
      fprintf(stderr,"	-c		  Colour depends on latitude (default: only altitude)\n");
      fprintf(stderr,"	-b		  Reverse background colour (default: black)\n");
      fprintf(stderr,"	-i init_alt	  Specifies initial altitude (default = -0.015)\n");
      fprintf(stderr,"	-pprojection	  Specifies projection: m = Mercator (default)\n");
      fprintf(stderr,"						p = Peters\n");
      fprintf(stderr,"						s = Stereographic\n");
      fprintf(stderr,"						o = Orthographic\n");
      fprintf(stderr,"						g = Gnomic\n");
      fprintf(stderr,"						a = Area preserving azimuthal\n");
      fprintf(stderr,"						c = Conical (conformal)\n");
      fprintf(stderr,"						f = Find match, see manual\n");
      exit(0);
    }
  }

  if (longi>180) longi -= 360;
  longi = longi*DEG2RAD;
  lat = lat*DEG2RAD;

  sla = sin(lat); cla = cos(lat);
  slo = sin(longi); clo = cos(longi);

  col = (unsigned char**)calloc(Width,sizeof(unsigned char*));
  for (i=0; i<Width; i++) col[i] = (unsigned char*)calloc(Height,sizeof(unsigned char));

  if (view == 'c') {
    if (lat == 0) view = 'm';
        /* Conical approaches mercator when lat -> 0 */
 /*   if (abs(lat) >= PI) view = 's'; */
        /* Conical approaches stereo when lat -> +/- 90 */
  }
  
  if (view == 'f') { /* read map */
    rseed;
    Width = 27; Height = 9;
    best = 5000;
    for (j = 0; j < Height; j++) {
      for(i = 0; i < Width ; i++) {
	c = getchar();
	switch (c) {
	  case '.': cl0[i][j] = -8;
		    break;
	  case ',': cl0[i][j] = -4;
		    break;
	  case ':': cl0[i][j] = -2;
		    break;
	  case ';': cl0[i][j] = -1;
		    break;
	  case '-': cl0[i][j] = 0;
		    break;
	  case '*': cl0[i][j] = 1;
		    break;
	  case 'o': cl0[i][j] = 2;
		    break;
	  case 'O': cl0[i][j] = 4;
		    break;
	  case '@': cl0[i][j] = 8;
		    break;
	  default: printf("Wrong map symbol: %c\n",c);
	}
      }
      c = getchar(); if (c!='\n') printf("Wrong map format: %c\n",c);
    }
  }

  Depth = 3*((int)(log2(scale*Height)))+3;


retry:

  r1 = rseed;

  r1 = rand2(r1,r1);
  r2 = rand2(r1,r1);
  r3 = rand2(r1,r2);
  r4 = rand2(r2,r3);
  r5 = rand2(r4,r3);
  r6 = rand2(r4,r5);
  r7 = rand2(r6,r5);
  r8 = rand2(r6,r7);

  switch (view) {

    case 'm': /* Mercator projection */
      y = sin(lat);
      y = (1.0+y)/(1.0-y);
      y = 0.5*log(y);
      k = (int)(0.5*y*Width*scale/PI);
      for (j = 0; j < Height; j++) {
	y = PI*(2.0*(j-k)-Height)/Width/scale;
	y = exp(2.*y);
	y = (y-1.)/(y+1.);
	scale1 = scale*Width/Height/sqrt(1.0-y*y)/PI;
	cos2 = sqrt(1.0-y*y);
	Depth = 3*((int)(log2(scale1*Height)))+3;
	for (i = 0; i < Width ; i++) {
	  theta1 = longi-0.5*PI+PI*(2.0*i-Width)/Width/scale;
	  col[i][j] = planet0(cos(theta1)*cos2,y,-sin(theta1)*cos2);
	}
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  y = (1.0+y)/(1.0-y);
	  y = 0.5*log(y);
	  j = Height/2+(int)(0.5*y*Width*scale/PI)+k;
	  if (j>=0 && j<Height) for (i = 0; i < Width ; i++) col[i][j] = BLACK;
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta1 = 0.0; theta1>-360.0; theta1-=vgrid);
	for (theta1 = theta1; theta1<360.0; theta1+=vgrid) {
	  i = (int)(0.5*Width*(1.0+scale*(DEG2RAD*theta1-longi)/PI));
	  if (i>=0 && i<Width) for (j = 0; j < Height; j++) col[i][j] = BLACK;
	}
      }
      break;

    case 'p': /* Peters projection (area preserving cylindrical) */
      y = 2.0*sin(lat);
      k = (int)(0.5*y*Width*scale/PI);
      for (j = 0; j < Height; j++) {
	y = 0.5*PI*(2.0*(j-k)-Height)/Width/scale;
	if (fabs(y)>1.0) for (i = 0; i < Width ; i++) col[i][j] = BACK;
	else {
	  scale1 = scale*Width/Height/sqrt(1.0-y*y)/PI;
	  cos2 = sqrt(1.0-y*y);
	  Depth = 3*((int)(log2(scale1*Height)))+3;
	  for (i = 0; i < Width ; i++) {
	    theta1 = longi-0.5*PI+PI*(2.0*i-Width)/Width/scale;
	    col[i][j] = planet0(cos(theta1)*cos2,y,-sin(theta1)*cos2);
	    if (col[i][j] < LAND0) water++; else land++;
	  }
	}
      }
      fprintf(stderr,"water percentage: %d\n",100*water/(water+land));
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = 2.0*sin(DEG2RAD*theta1);
	  j = Height/2+(int)(0.5*y*Width*scale/PI)+k;
	  if (j>=0 && j<Height) for (i = 0; i < Width ; i++) col[i][j] = BLACK;
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta1 = 0.0; theta1>-360.0; theta1-=vgrid);
	for (theta1 = theta1; theta1<360.0; theta1+=vgrid) {
	  i = (int)(0.5*Width*(1.0+scale*(DEG2RAD*theta1-longi)/PI));
	  if (i>=0 && i<Width) for (j = 0; j < Height; j++) col[i][j] = BLACK;
	}
      }
      break;

    case 's': /* Stereographic projection */
      ymin = 2.0;
      ymax = -2.0;
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale;
	  z = x*x+y*y;
	  zz = 0.25*(4.0+z);
	  x = x/zz;
	  y = y/zz;
	  z = (1.0-0.25*z)/zz;
	  x1 = clo*x+slo*sla*y+slo*cla*z;
	  y1 = cla*y-sla*z;
	  z1 = -slo*x+clo*sla*y+clo*cla*z;
	  if (y1 < ymin) ymin = y1;
	  if (y1 > ymax) ymax = y1;
	  col[i][j] = planet0(x1,y1,z1);
	}
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(1-y*y);
	    for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	      x = sin(theta2)*zz;
	      z = cos(theta2)*zz;
	      x1 = clo*x+slo*z;
	      y1 = slo*sla*x+cla*y-clo*sla*z;
	      z1 = -slo*cla*x+sla*y+clo*cla*z;
	      if (fabs(z1)<1.0){
		i = 0.5*(Height*scale*2.0*x1*(1+z1)/(1.0-z1*z1)+Width);
		j = 0.5*(Height*scale*2.0*y1*(1+z1)/(1.0-z1*z1)+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	  y = sin(theta2);
	  if (ymin <= y && y <= ymax) {
	    for (theta1 = 0.0; theta1<360.0; theta1+=vgrid) {
	      x = sin(DEG2RAD*theta1)*cos(theta2);
	      z = cos(DEG2RAD*theta1)*cos(theta2);
	      x1 = clo*x+slo*z;
	      y1 = slo*sla*x+cla*y-clo*sla*z;
	      z1 = -slo*cla*x+sla*y+clo*cla*z;
	      if (fabs(z1)<1.0){
		i = 0.5*(Height*scale*2.0*x1*(1+z1)/(1-z1*z1)+Width);
		j = 0.5*(Height*scale*2.0*y1*(1+z1)/(1-z1*z1)+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      break;

    case 'o': /* Orthographic projection */
      ymin = 2.0;
      ymax = -2.0;
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale;
	  if (x*x+y*y>1.0) col[i][j] = BACK;
	  else {
	    z = sqrt(1.0-x*x-y*y);
	    x1 = clo*x+slo*sla*y+slo*cla*z;
	    y1 = cla*y-sla*z;
	    z1 = -slo*x+clo*sla*y+clo*cla*z;
	    if (y1 < ymin) ymin = y1;
	    if (y1 > ymax) ymax = y1;
	    col[i][j] = planet0(x1,y1,z1);
	  }
	}
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(1-y*y);
	    for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	      x = sin(theta2)*zz;
	      z = cos(theta2)*zz;
	      x1 = clo*x+slo*z;
	      y1 = slo*sla*x+cla*y-clo*sla*z;
	      z1 = -slo*cla*x+sla*y+clo*cla*z;
	      if (0.0>=z1){
		i = 0.5*(Height*scale*x1+Width);
		j = 0.5*(Height*scale*y1+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	  y = sin(theta2);
	  if (ymin <= y && y <= ymax) {
	    for (theta1 = 0.0; theta1<360.0; theta1+=vgrid) {
	      x = sin(DEG2RAD*theta1)*cos(theta2);
	      z = cos(DEG2RAD*theta1)*cos(theta2);
	      x1 = clo*x+slo*z;
	      y1 = slo*sla*x+cla*y-clo*sla*z;
	      z1 = -slo*cla*x+sla*y+clo*cla*z;
	      if (0.0>=z1){
		i = 0.5*(Height*scale*x1+Width);
		j = 0.5*(Height*scale*y1+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      break;

    case 'g': /* Gnomic projection */
      ymin = 2.0;
      ymax = -2.0;
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale;
	  zz = sqrt(1.0/(1.0+x*x+y*y));
	  x = x*zz;
	  y = y*zz;
	  z = sqrt(1.0-x*x-y*y);
	  x1 = clo*x+slo*sla*y+slo*cla*z;
	  y1 = cla*y-sla*z;
	  z1 = -slo*x+clo*sla*y+clo*cla*z;
	  if (y1 < ymin) ymin = y1;
	  if (y1 > ymax) ymax = y1;
	  col[i][j] = planet0(x1,y1,z1);
	}
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(1-y*y);
	    for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	      x = sin(theta2)*zz;
	      z = cos(theta2)*zz;
	      x1 = clo*x-slo*z;
	      y1 = slo*sla*x+cla*y+clo*sla*z;
	      z1 = slo*cla*x-sla*y+clo*cla*z;
	      if (z1!=0.0){
		i = 0.5*(Height*scale*x1/z1+Width);
		j = 0.5*(Height*scale*y1/z1+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	  y = sin(theta2);
	  if (ymin <= y && y <= ymax) {
	    for (theta1 = 0.0; theta1<360.0; theta1+=vgrid) {
	      x = sin(DEG2RAD*theta1)*cos(theta2);
	      z = cos(DEG2RAD*theta1)*cos(theta2);
	      x1 = clo*x-slo*z;
	      y1 = slo*sla*x+cla*y+clo*sla*z;
	      z1 = slo*cla*x-sla*y+clo*cla*z;
	      if (z1!=0.0){
		i = 0.5*(Height*scale*x1/z1+Width);
		j = 0.5*(Height*scale*y1/z1+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      break;

    case 'a': /* Area preserving azimuthal projection */
      ymin = 2.0;
      ymax = -2.0;
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale;
	  zz = x*x+y*y;
	  z = 1.0-0.5*zz;
	  if (z<-1.0) col[i][j] = BACK;
	  else {
	    zz = sqrt(1.0-0.25*zz);
	    x = x*zz;
	    y = y*zz;
	    x1 = clo*x+slo*sla*y+slo*cla*z;
	    y1 = cla*y-sla*z;
	    z1 = -slo*x+clo*sla*y+clo*cla*z;
	    if (y1 < ymin) ymin = y1;
	    if (y1 > ymax) ymax = y1;
	    col[i][j] = planet0(x1,y1,z1);
	  }
	}
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(1-y*y);
	    for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	      x = sin(theta2)*zz;
	      z = cos(theta2)*zz;
	      x1 = clo*x-slo*z;
	      y1 = slo*sla*x+cla*y+clo*sla*z;
	      z1 = slo*cla*x-sla*y+clo*cla*z;
	      if (z1!=-1.0){
		i = 0.5*(Height*scale*x1/sqrt(0.5+0.5*z1)+Width);
		j = 0.5*(Height*scale*y1/sqrt(0.5+0.5*z1)+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
	  y = sin(theta2);
	  if (ymin <= y && y <= ymax) {
	    for (theta1 = 0.0; theta1<360.0; theta1+=vgrid) {
	      x = sin(DEG2RAD*theta1)*cos(theta2);
	      z = cos(DEG2RAD*theta1)*cos(theta2);
	      x1 = clo*x-slo*z;
	      y1 = slo*sla*x+cla*y+clo*sla*z;
	      z1 = slo*cla*x-sla*y+clo*cla*z;
	      if (z1!=-1.0){
		i = 0.5*(Height*scale*x1/sqrt(0.5+0.5*z1)+Width);
		j = 0.5*(Height*scale*y1/sqrt(0.5+0.5*z1)+Height);
		if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	      }
	    }
	  }
	}
      }
      break;

    case 'c': /* Conical projection (conformal) */
     if (lat>0) {
      k1 = 1.0/sin(lat);
      c = k1*k1;
      y2 = sqrt(c*(1.0-sin(lat/k1))/(1.0+sin(lat/k1)));
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale+y2;
	  zz = x*x+y*y;
	  if (zz==0.0) theta1 = 0.0; else theta1 = k1*atan2(x,y);
	  if (theta1<-PI || theta1>PI) col[i][j] = BACK;
	   else {
	    theta1 += longi-0.5*PI; /* theta1 is longitude */
	    theta2 = k1*asin((zz-c)/(zz+c));
	                            /* theta2 is latitude */
	    if (theta2 > 0.5*PI || theta2 < -0.5*PI) col[i][j] = BACK;
	    else {
	      cos2 = cos(theta2);
	      y = sin(theta2);
	      if (y < ymin) ymin = y;
	      if (y > ymax) ymax = y;
	      col[i][j] = planet0(cos(theta1)*cos2,y,-sin(theta1)*cos2);
	    }
	  }
        }
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(c*(1.0+sin(DEG2RAD*theta1/k1))
		       /(1.0-sin(DEG2RAD*theta1/k1)));
	    for (theta2=-PI+longi; theta2<PI+longi; theta2+=0.5/Width/scale) {
	      z1 = theta2-longi;
	      x1 = zz*sin(z1/k1);
	      y1 = zz*cos(z1/k1);
	      i = 0.5*(Height*scale*x1+Width);
	      j = 0.5*(Height*scale*(y1-y2)+Height);
	      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta1=-0.5*PI; theta1<0.5*PI; theta1+=0.5/Width/scale) {
	  y = sin(theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(c*(1.0+sin(theta1/k1))
		       /(1.0-sin(theta1/k1)));
	    for (theta2 = 0.0; theta2>-180.0+longi/DEG2RAD; theta2-=vgrid);
	    for (theta2 = theta2; theta2<180.0+longi/DEG2RAD; theta2+=vgrid) {
	      z1 = DEG2RAD*theta2-longi;
	      x1 = zz*sin(z1/k1);
	      y1 = zz*cos(z1/k1);
	      i = 0.5*(Height*scale*x1+Width);
	      j = 0.5*(Height*scale*(y1-y2)+Height);
	      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	    }
	  }
	}
      }
     }
     else {
      k1 = 1.0/sin(lat);
      c = k1*k1;
      y2 = sqrt(c*(1.0-sin(lat/k1))/(1.0+sin(lat/k1)));
      for (j = 0; j < Height; j++) {
	for (i = 0; i < Width ; i++) {
	  x = (2.0*i-Width)/Height/scale;
	  y = (2.0*j-Height)/Height/scale-y2;
	  zz = x*x+y*y;
	  if (zz==0.0) theta1 = 0.0; else theta1 = -k1*atan2(x,-y);
	  if (theta1<-PI || theta1>PI) col[i][j] = BACK;
	   else {
	    theta1 += longi-0.5*PI; /* theta1 is longitude */
	    theta2 = k1*asin((zz-c)/(zz+c));
	                            /* theta2 is latitude */
	    if (theta2 > 0.5*PI || theta2 < -0.5*PI) col[i][j] = BACK;
	    else {
	      cos2 = cos(theta2);
	      y = sin(theta2);
	      if (y < ymin) ymin = y;
	      if (y > ymax) ymax = y;
	      col[i][j] = planet0(cos(theta1)*cos2,y,-sin(theta1)*cos2);
	    }
	  }
        }
      }
      if (hgrid != 0.0) { /* draw horisontal gridlines */
	for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
	for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
	  y = sin(DEG2RAD*theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(c*(1.0+sin(DEG2RAD*theta1/k1))
		       /(1.0-sin(DEG2RAD*theta1/k1)));
	    for (theta2=-PI+longi; theta2<PI+longi; theta2+=0.5/Width/scale) {
	      z1 = theta2-longi;
	      x1 = -zz*sin(z1/k1);
	      y1 = -zz*cos(z1/k1);
	      i = 0.5*(Height*scale*x1+Width);
	      j = 0.5*(Height*scale*(y1+y2)+Height);
	      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	    }
	  }
	}
      }
      if (vgrid != 0.0) { /* draw vertical gridlines */
	for (theta1=-0.5*PI; theta1<0.5*PI; theta1+=0.5/Width/scale) {
	  y = sin(theta1);
	  if (ymin <= y && y <= ymax) {
	    zz = sqrt(c*(1.0+sin(theta1/k1))
		       /(1.0-sin(theta1/k1)));
	    for (theta2 = 0.0; theta2>-180.0+longi/DEG2RAD; theta2-=vgrid);
	    for (theta2 = theta2; theta2<180.0+longi/DEG2RAD; theta2+=vgrid) {
	      z1 = DEG2RAD*theta2-longi;
	      x1 = -zz*sin(z1/k1);
	      y1 = -zz*cos(z1/k1);
	      i = 0.5*(Height*scale*x1+Width);
	      j = 0.5*(Height*scale*(y1+y2)+Height);
	      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
	    }
	  }
	}
      }
     }
     break;

    case 'f': /* Search */
      for (j = 0; j < Height; j++) {
	y = PI*1.7*(2.0*j-Height+1)/Width;
	y = exp(2.*y);
	y = (y-1.)/(y+1.);
	scale1 = Width/Height/sqrt(1.0-y*y)/PI;
	cos2 = sqrt(1.0-y*y);
	Depth = 3*((int)(log2(scale1*Height)))+6;
	for (i = 0; i < Width ; i++) {
	  theta1 = -0.5*PI+PI*(2.0*i-Width)/Width;
	  c = 128+1000*planet1(cos(theta1)*cos2,y,-sin(theta1)*cos2);
	  if (c<0) c = 0;
	  if (c>255) c = 255;
	  col[i][j] = c;
	}
      }
      for (k=0; k<Width; k++) {
	for (l=-20; l<=20; l+=2) {
	  errcount = 0;
	  for(i = 0; i < Width ; i++)
	    for (j = 0; j < Height; j++) {
	      if (cl0[i][j]<0 && col[(i+k)%Width][j] > 128-l)
		errcount-=cl0[i][j];
	      if (cl0[i][j]>0 && col[(i+k)%Width][j] <= 128-l)
		errcount+=cl0[i][j];
	    }

	  if (errcount < best) {
	    printf("Errors: %d, seed: %.16f, rotate = %.1f, initial altitude = %.3f\n",
		   errcount,rseed,(360.0*k)/Width,M+l/1000.0);
	    best = errcount;
	    for (j = 0; j < Height; j++) {
	      for(i = 0; i < Width ; i++)
		if (col[(i+k)%Width][j] <= 128-l) putchar('.');
		else putchar('O');
	      putchar('\n');
	    }
	    fflush(stdout);
	  }
	}
      }
      rseed += increment;
      goto retry;
  }

  /* plot picture */
  printppm(outfile);
  exit(0);
}

/* int planet0(x,z,y) */
int planet0(x,y,z)
double x,y,z;
{
  double alt, planet1();
  int colour;

  alt = planet1(x,y,z);

      /* calculate colour */
  if (alt <=0.) { /* if below sea level then */
    if (latic && z*z+alt >= 0.98)
      colour = WHITE;	 /* white if close to poles */
    else {
      colour = BLUE1+(int)((BLUE1-BLUE0+1)*(10*alt));	/* blue scale otherwise */
      if (colour<BLUE0) colour = BLUE0;
    }
  }
  else {
    if (latic) alt += 0.10204*z*z;  /* altitude adjusted with latitude */
    if (alt >= 0.1) /* if high then */
      colour = WHITE;	  /* white */
    else {
      colour = LAND0+(int)((LAND1-LAND0+1)*(10*alt));
	    /* else green to brown scale */
    }
  }
  return(colour);
}

double planet1(x,y,z)
double x,y,z;
{
  double planet();

  return(planet(M,M,M,M,M,M,M,M,
		     /* initial altitude is M on all corners of box */
		r1,r2,r3,r4,r5,r6,r7,r8,
		     /* same seed set is used in every call */
		-1.,-t1,-t2,
		     /* bottom left closest corner: (-1,-2^(1/3),-2^(2/3)) */
		x,y,z,
		     /* coordinates of point we want colour of */
		Depth,Da0,Dda0));
		     /* subdivision depth, initial scale and variance */
}


double planet(a,b,c,d,e,f,g,h, as,bs,cs,ds,es,fs,gs,hs,
       ax,ay,az, x,y,z, level, scale, dalt)
double a,b,c,d,e,f,g,h;		/* altitudes of the eight corners */
double as,bs,cs,ds,es,fs,gs,hs; /* seeds of the eight corners */
double ax,ay,az;		/* bottom left closest corner */
double x,y,z, scale, dalt;	/* goal point, scale and variance */
int level;
{
  double ae,bf,cg,dh,aes,bfs,cgs,dhs,rand2();

  if (level == 0)
    return((a+b+c+d+e+f+g+h)/8);
  else { /* subdivide over longest axis */
    aes = rand2(as,es); bfs = rand2(bs,fs); /* find seeds for new points */
    cgs = rand2(cs,gs); dhs = rand2(ds,hs);
    ae = (a+e+dalt*aes)/2.; bf = (b+f+dalt*bfs)/2.; /* find altitudes */
    cg = (c+g+dalt*cgs)/2.; dh = (d+h+dalt*dhs)/2.; /* as mean+variation */
	/* find which halfbox goal point is in and continue in that */
    if (az+scale*t3 >= z)
      return(planet(a,ae,bf,b,d,dh,cg,c, as,aes,bfs,bs,ds,dhs,cgs,cs,
		    az,ax,ay, z,x,y, level-1, scale*t3, dalt*Ddda));
    else
      return(planet(ae,e,f,bf,dh,h,g,cg, aes,es,fs,bfs,dhs,hs,gs,cgs,
		    az+scale*t3,ax,ay, z,x,y, level-1, scale*t3, dalt*Ddda));
  }
}


double rand2(p,q) /* random number generator taking two seeds */
double p,q;	  /* rand2(p,q) = rand2(q,p) is important     */
{
  double r;
  r = (p+3.14159265)*(q+3.14159265);
  return(2.*(r-(int)r)-1.);
}

void printppm(outfile) /* prints picture in PPM (portable pixel map) format */
FILE *outfile;
{
  int i,j;

  fprintf(outfile,"P6\n");
  fprintf(outfile,"#fractal planet image\n");
  fprintf(outfile,"%d %d 255\n",Width,Height);
 
  for (j=0; j<Height; j++)
    for (i=0; i<Width; i++) {
      putc(rtable[col[i][j]],outfile);
      putc(gtable[col[i][j]],outfile);
      putc(btable[col[i][j]],outfile);
    }
  fclose(outfile);
}
      
double log2(x)
double x;
{ return(log(x)/log(2.0)); }
