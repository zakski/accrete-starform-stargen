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

public class SystemDisplayFlat extends Panel 
{
	private PlanetClassifier pc;
	private StarSystem sys;
	private double[] X, Y;
	private int ch, cw; // location of center
	public SystemDisplayFlat(PlanetClassifier PC)
	{
		super();

		// 	You can add code anywhere in this method, except before the call to super().
		pc = PC;
		X = new double[36];
		Y = new double[36];
		
		SuperCedeConstructor();   // Do not remove this line
	}
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
   		return(int)((log10(r) + 1.1) * bounds().width / 3.25)/2;
	}
	private void showEllipse(Graphics g, Planet p, double w)
	{
	    int j;
	    double t;   /* current time */
	    double n = (2.0 * Math.PI) / p.orb_period;   /* daily motion in radians/day */
	    double M;  /* mean anomaly */
	    double E, E0, E1; /* eccentric anomaly */
	    double v;         /* true anomaly */
	    double r;         /* heliocentric distance; distance from primary */
	    double x, y;
	    double a_e = p.a*p.e;
	    double a_sqrt_1_minus_e2 = p.a*Math.sqrt(1.0 - p.e*p.e);
		
		// compute orbital locations
		while (w>(2.0*Math.PI)) w-=2.0*Math.PI;
	    for (j=0;j<36;j++)
	    {
	        t = j*p.orb_period/36.0;   /* current time */
	        M = n * t;  /* mean anomaly */
	
	        E1 = M + p.e * Math.sin(M) * (1.0 + p.e * Math.cos(M));
	        E0 = 0.0;
	        while (Math.abs(E1-E0) > 0.005)
	        {
	            E0 = E1;
	            E1 = E0 - (E0 - p.e * Math.sin(E0) - M) / (1.0 - p.e * Math.cos(E0));
	        }
	        E = E1;
	    
	        x = p.a * Math.cos(E) - a_e;
	        y = a_sqrt_1_minus_e2 * Math.sin(E);
	
	        r = Math.sqrt(x*x + y*y);
	        v = Math.atan2(y, x);
	
	        X[j] = computex(r) * Math.cos(v+w);
	        Y[j] = computex(r) * Math.sin(v+w);
	    }
	    // draw the orbit
	    for (j=0; j<35; j++)
	    {
	    	g.drawLine(cw+(int)X[j], ch+(int)Y[j], cw+(int)X[j+1], ch+(int)Y[j+1]);
	    }
	    g.drawLine(cw+(int)X[35], ch+(int)Y[35], cw+(int)X[0], ch+(int)Y[0]);
	}
	private void showPlanet(Graphics g, Planet p, double w)
	{
	    int j=0;
	    double t;   /* current time */
	    double n = (2.0 * Math.PI) / p.orb_period;   /* daily motion in radians/day */
	    double M;  /* mean anomaly */
	    double E, E0, E1; /* eccentric anomaly */
	    double v;         /* true anomaly */
	    double r;         /* heliocentric distance; distance from primary */
	    double x, y;
	    double a_e = p.a*p.e;
	    double a_sqrt_1_minus_e2 = p.a*Math.sqrt(1.0 - p.e*p.e);
		int dradius;
		
		// compute orbital locations
		while (w>(2.0*Math.PI)) w-=2.0*Math.PI;
	        t = 0.0;   /* current time */
	        M = n * t;  /* mean anomaly */
	
	        E1 = M + p.e * Math.sin(M) * (1.0 + p.e * Math.cos(M));
	        E0 = 0.0;
	        while (Math.abs(E1-E0) > 0.005)
	        {
	            E0 = E1;
	            E1 = E0 - (E0 - p.e * Math.sin(E0) - M) / (1.0 - p.e * Math.cos(E0));
	        }
	        E = E1;
	    
	        x = p.a * Math.cos(E) - a_e;
	        y = a_sqrt_1_minus_e2 * Math.sin(E);
	
	        r = Math.sqrt(x*x + y*y);
	        v = Math.atan2(y, x);
	
	        X[0] = computex(r) * Math.cos(v+w);
	        Y[0] = computex(r) * Math.sin(v+w);
      	dradius = (int) Math.log(p.radius/100.0)*2;
      	if (dradius < 1) dradius = 1;
		g.drawImage(pc.planetImage(p),
			cw-dradius+(int)X[j], ch-dradius+(int)Y[j],
			2*dradius+1, 2*dradius+1,
			this);
	}
	public void paint(Graphics g)
	{
	   	Planet p;
		double w;
		boolean showBright = true;
		
		if (sys==null) return;
		g.setColor(Color.white);

	   	// display planetary orbits	
	   	ch = bounds().height/2;
	   	cw = bounds().width/2;
	   	for (w=0.0, p = sys.planets; p != null; p = p.next_planet, w+=1.0)
	   	{
	      	int x, y, dradius;
	
			if (showBright)
			{
				g.setColor(Color.white);
				showBright = false;
			}
			else
			{
				g.setColor(Color.lightGray);
				showBright = true;
			}
	      	x = computex(p.a);
	      	y = ch;
	      	showEllipse(g, p, w);
	   	}
	   	for (w=0.0, p = sys.planets; p != null; p = p.next_planet, w+=1.0)
	   	{
	      	int x, y, dradius;
	
	      	x = computex(p.a);
	      	y = ch;
	      	showPlanet(g, p, w);
	   	}
	}
	public void flush()
	{
		pc=null;
		sys=null;
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
		setFont( new Font( "Helvetica", Font.PLAIN, 10 ));
		setForeground( new Color( 255, 255, 255 ));
		setBackground( new Color( 0, 0, 0 ));
		resize( (insets().left + insets().right + 300), (insets().top + insets().bottom + 300) );
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
// 2 "Untitled" 100000 0 400 0 F F F "Helvetica"
// 1213 200 F 11 8388736 8421440 F T T T F F 0 0 0 0
// 0 16777215
// 0
// 0
// 300 300 655360 0 16777215 0
// 5 0 1 1 2 "SystemDisplayFlat" 0 0 0 2 2 0 T T F T F
// ""
// F F F F F F F F F F F F F
// 0
// 0
// SuperCede End Properties
