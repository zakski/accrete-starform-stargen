// 	You can add code anywhere in this file - except in the areas that are
// 	written by the editor. You should not change the relative ordering of
// 	the code. The constructor must precede the event handlers, which must
// 	precede handleEvent(), and so on.
// 	 
// 	You can remove this comment block or replace it with another.

import java.awt.*;
import java.util.*;
import java.io.*;
import java.net.*;

/**
 *
 * <p><strong><center>Copyright information</center></strong></p>
 * <p>This Java class is copyright 1998 by Carl Burke. All rights reserved.
 * Substantial sections of this code were previously distributed in
 * different form as part of 'starform' (copyright 1989 Matthew Burdick)<p>
 * <p>This software is provided absolutely free and without warranty,
 * including but not limited to the implied warranties of merchantability
 * and fitness for a purpose.  You may use this code for any legal purpose
 * provided that you do not charge for it; this implies that you <em>may</em>
 * use this code as a component of a commercial system as long as the additional
 * functionality of the commercial system is greater than what this code
 * provides and that the commercial system is not primarily intended as
 * a simulation of solar system formation.  In other words, if you want to
 * write a science-fiction computer game that uses the code in this package
 * to build objects which are used in the game, that's great and permitted;
 * if you use this code to make a kickass solar-system-builder, you are not
 * allowed to distribute that software except for free.
 * <p>You are allowed and encouraged to modify this software, provided that
 * this copyright notice remains intact.  This notice may be reformatted,
 * but not removed.
 * <p>If you do use this software, I and the contributing authors listed
 * under "Acknowledgements" would appreciate some recognition.  If you make
 * changes, I would appreciate it if you would pass those changes back to me
 * for possible inclusion in the master.  At the time this notice was prepared,
 * my email address is <a href="mailto:cburke@mitre.org">cburke@mitre.org</a> and the home page for this software is
 * <a href="http://www.geocities.com/Area51/6902/w_accr.html">http://www.geocities.com/Area51/6902/w_accr.html</a>.
 * <a name="ack"><strong><center>Acknowledgements</center></strong></a>
 * <p>Matt Burdick, the author of 'starform' (freeware copyright 1989);
 * much of the code (particularly planetary environments) was adapted from this.</p>
 * <p>Andrew Folkins, the author of 'accretion' (public domain) for the Amiga; I used chunks
 * of his code when creating my displays.</p>
 * <p>Ed Taychert of <a href="http://www.irony.com/">Irony Games</a>, for the algorithm he uses 
 * to classify terrestrial planets in his tabular CGI implementation of 'starform'.</p>
 * <p>Paul Schlyter, who provided information about 
 * <a href="http://spitfire.ausys.se/psr/comp/ppcomp.html">computing planetary positions</a>.</p>
 */
public class SystemDisplayScale extends Panel
{
	private PlanetClassifier pc;
	private int titlearea;
    private Font ft;
    private FontMetrics fm;
    private StarSystem sys;
	private Planet[] pArray;
    public void setSystem(StarSystem SYS)
    {
    	sys = SYS;
    	repaint();
    }
	private double log10(double x)
	{
		return Math.log(x)/Math.log(10.0);
	}
	/*
 	* Compute the screen position of a given orbital distance.
 	*/
	private int computex(double r)
	{
   		if (r <= 0.0) return 0;
   		return(int)((log10(r) + 1.1) * bounds().width / 3.25);
	}
	private void DrawXAxis(Graphics g)
	{
	   	int i, x=0, y;
	   	double r;
	   	Rectangle rect = bounds();
	
	   	y = rect.height - 5;
	
	   	y -= fm.getMaxAdvance();
	   	g.drawString("Semi-Major Axis (Astronomical Units)", computex(0.5), y);
	
	   	y -= fm.getMaxAdvance();
	   	g.drawString("0.1", computex(0.1), y);
	   	g.drawString("1", computex(1.0), y);
	   	g.drawString("10", computex(10.0), y);
	   	g.drawString("100", computex(90.0), y);
	   	y -= 10;
	
	   	for (i = 1; i <= 10; i++)
	   	{
	      	r = i;
	      	x = computex(r);
	      	g.drawLine(x, y, x, y-5);
	      	x = computex(r / 10.0);
	      	g.drawLine(x, y, x, y-5);
	      	x = computex(r * 10.0);
	     	g.drawLine(x, y, x, y-5);
	   	}
  		g.drawLine(x, y-5, computex(0.1), y-5);
	}
	void DrawOrbitLimits(Graphics g,
	    double min, double r, double max, int offset, int height)
	{
	   	int x0, x1, x2, y;
	
	   	y = bounds().height - offset - titlearea;
	   	x0 = computex(min);
	   	x1 = computex(r);
	   	x2 = computex(max);
	
	   	g.drawLine(x0, y, x0, y+height);
	   	g.drawLine(x1, y, x1, y+height);
	   	g.drawLine(x2, y, x2, y+height);
	}
	private int sortPlanets()
	{
	   	Planet p;
	   	int i, j, k;
	   	
	   	for (i=0, p = sys.planets; p != null; p = p.next_planet, i++)
	   	{
	   		pArray[i] = p;
	   	}
	   	for (j=0; j<i-1; j++) for (k=j+1; k<i; k++)
	   	{
	   		if (pArray[k].radius > pArray[j].radius)
	   		{
	   			p = pArray[j];
	   			pArray[j] = pArray[k];
	   			pArray[k] = p;
	   		}
	   	}
	   	return i;
	}
	public void paint(Graphics g)
	{
	   	Planet p;
	   	int ch, cw;
		int i, j;
		
	   	Rectangle rect = bounds();
		if (sys==null) return;
		g.setFont(ft);
		fm = g.getFontMetrics();
	   	titlearea = 2*fm.getMaxAdvance() + 20;
		g.setColor(Color.white);
	   	if (sys.primary.nearest_planet() > 0.1)
	      	DrawOrbitLimits(g, sys.primary.nearest_planet(), sys.primary.r_ecosphere, sys.primary.farthest_planet(), 9, 2);
	   	// display planetary icons
		i = sortPlanets();
	   	ch = (bounds().height - titlearea)/2;
	   	for (j=0; j<i; j++)
	   	{
	      	int x, y, dradius;

	      	x = computex(pArray[j].a);
	      	y = ch;
	      	dradius = (int) (pArray[j].radius / 2500.0);
	      	if (dradius < 1) dradius = 1;
			g.drawImage(pc.planetImage(pArray[j]),
				x-dradius, y-dradius,
				2*dradius+1, 2*dradius+1,
				this);
	      	DrawOrbitLimits(g,
	          	pArray[j].a * (1.0 - pArray[j].e),
	          	pArray[j].a,
	          	pArray[j].a* (1.0 + pArray[j].e),
	          	15, 5);
	   	}
	   	DrawXAxis(g);
	}
	public SystemDisplayScale(PlanetClassifier p)
	{
		super();

		pc = p;
		ft = new Font("Helvetica", Font.PLAIN, 10);
		pArray = new Planet[50];
		setBackground(Color.black);
		
		SuperCedeConstructor();   // Do not remove this line
	}
	public void flush()
	{
		ft=null;
		fm=null;
		pc=null;
		sys=null;
		pArray=null;
		hide();
		disable();
		removeNotify();
	}
	
	public boolean handleEvent( Event event )
	{
		// 	Tests for custom events go here...

		return SuperCedeEvent( event );   // Do not remove this line
	}

	public boolean action( Event event, Object arg )
	{
		return super.action( event, arg );
	}

	// SuperCede Begin Methods
	// 	Do not remove the Begin and End markers.
	// 	The editor will rewrite the contents of this section each time the form is saved.
	private final void SuperCedeConstructor()
	{
		setLayout( null );
		resize( (insets().left + insets().right + 600), (insets().top + insets().bottom + 200) );
	}

	private final boolean SuperCedeEvent( Event event )
	{
		return super.handleEvent( event );
	}

	// SuperCede End Methods

	// SuperCede Begin Declarations
	// 	Do not remove the Begin and End markers.
	// 	The editor will rewrite the contents of this section each time the form is saved.
	// SuperCede End Declarations
}


// SuperCede Begin Properties
// 2
// 48
// 2 "Untitled" 100000 0 400 0 F F F "Dialog"
// 1213 200 F 11 8388736 8421440 F T T T F F 0 0 0 0
// 0 16777215
// 0
// 0
// 400 300 655360 0 2147483656 2147483653
// 5 0 0 0 0 "SystemDisplayScale" 0 0 0 2 2 0 T T F T T
// ""
// F F F F F F F F F F F F F
// 0
// 0
// SuperCede End Properties
