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
 * This class will display information about a planet, given a PlanetClassifier
 * to handle textual and graphical representations.
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
public class PlanetDisplay extends Panel 
{
    private PlanetClassifier pc;
    private Planet p;
    public void setPlanet(Planet P)
    {
	p = P;
	repaint();
    }
    public PlanetDisplay(PlanetClassifier PC)
    {
	super();

	// 	You can add code anywhere in this method, except before the call to super().
	pc = PC;
	
	SuperCedeConstructor();   // Do not remove this line
    }
    private String trimValue(double d)
    {
	String s = Double.toString(d);
	int i = s.indexOf(".");
	if (i<0) return s;
	if ((i+2)<s.length())
	{
		s = s.substring(0, i+3);
	}
	return s;
    }
    public void paint(Graphics g)
    {
	g.setColor(Color.yellow);
	// column 1
	g.drawString( "Semi-major axis:", (insets().left + 142), (insets().top + 23) );
	g.drawString( "Eccentricity", (insets().left + 142), (insets().top + 42) );
	g.drawString( "Mass", (insets().left + 142), (insets().top + 61) );
	g.drawString( "Radius", (insets().left + 142), (insets().top + 80) );
	g.drawString( "Density", (insets().left + 142), (insets().top + 99) );
	g.drawString( "Year", (insets().left + 142), (insets().top + 118) );
	g.drawString( "Day", (insets().left + 142), (insets().top + 137) );
	g.drawString( "Axial tilt", (insets().left + 142), (insets().top + 156) );
	g.drawString( "Surface gravity", (insets().left + 142), (insets().top + 175) );
	// column 2
	g.drawString( "Surface temp:", (insets().left + 311), (insets().top + 24) );
	g.drawString( "Surface pressure", (insets().left + 311), (insets().top + 43) );
	g.drawString( "Boiling point", (insets().left + 311), (insets().top + 62) );
	g.drawString( "Avg deg > freezing", (insets().left + 311), (insets().top + 81) );
	g.drawString( "% water", (insets().left + 311), (insets().top + 100) );
	g.drawString( "% ice", (insets().left + 311), (insets().top + 119) );
	g.drawString( "% rock", (insets().left + 311), (insets().top + 138) );
	g.drawString( "% cloud", (insets().left + 311), (insets().top + 157) );
	g.drawString( "Albedo", (insets().left + 311), (insets().top + 176) );

	if (p!=null)
	{
	    g.drawImage(pc.planetImage(p), 0, 0, /*100, 100,*/ this);
	    g.setColor(Color.white);
	    g.drawString(pc.planetType(p), (insets().left + 14), (insets().top + 120) );
	    g.drawString((p.gas_giant ? "Gas giant" : "Rocky"), (insets().left + 14), (insets().top + 137) );
	    g.drawString((!p.gas_giant && p.greenhouse_effect ? "Greenhouse" : ""), (insets().left + 14), (insets().top + 154) );
	    g.drawString((!p.gas_giant && p.temp_unstable ? "Chaotic temp" : "Stable temp"), (insets().left + 14), (insets().top + 171) );
	    g.drawString(((p.resonant_period != 0) ? "Spin lock" : ""), (insets().left + 14), (insets().top + 188) );
	    g.drawString(trimValue(p.a), (insets().left + 240), (insets().top + 24) );
	    g.drawString(trimValue(p.e), (insets().left + 240), (insets().top + 43) );
	    g.drawString(trimValue(p.mass), (insets().left + 240), (insets().top + 62) );
	    g.drawString(trimValue(p.radius), (insets().left + 240), (insets().top + 81) );
	    g.drawString(trimValue(p.density), (insets().left + 240), (insets().top + 100) );
	    g.drawString(trimValue(p.orb_period), (insets().left + 240), (insets().top + 119) );
	    g.drawString(trimValue(p.day), (insets().left + 240), (insets().top + 138) );
	    g.drawString(trimValue(p.axial_tilt), (insets().left + 240), (insets().top + 157) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.surf_grav)), (insets().left + 240), (insets().top + 176) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.surf_temp)), (insets().left + 401), (insets().top + 24) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.surf_pressure)), (insets().left + 401), (insets().top + 43) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.boil_point)), (insets().left + 401), (insets().top + 62) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.surf_temp-273.15)), (insets().left + 401), (insets().top + 81) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.hydrosphere*100)), (insets().left + 401), (insets().top + 100) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.ice_cover*100)), (insets().left + 401), (insets().top + 119) );
	    double rock_fraction = 1.0-p.hydrosphere;
	    rock_fraction -= rock_fraction*p.ice_cover; // assume ice evenly distributed on land and water
	    g.drawString((p.gas_giant ? "NA" : trimValue(rock_fraction*100)), (insets().left + 401), (insets().top + 138) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.cloud_cover*100)), (insets().left + 401), (insets().top + 157) );
	    g.drawString((p.gas_giant ? "NA" : trimValue(p.albedo)), (insets().left + 401), (insets().top + 176) );
	}
    }
    public void flush()
    {
	pc=null;
	p=null;
	setFont(null);
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
	resize( (insets().left + insets().right + 460), (insets().top + insets().bottom + 200) );
    }

    private final boolean SuperCedeEvent( Event event )
    {
	return super.handleEvent( event );
    }

    private final void SuperCedeStart()
    {
    }

    private final void SuperCedeStop()
    {
    }
    // SuperCede End Methods

    // SuperCede Begin Declarations
    // 	Do not remove the Begin and End markers.
    // 	The editor will rewrite the contents of this section each time the form is saved.
    // SuperCede End Declarations
}

