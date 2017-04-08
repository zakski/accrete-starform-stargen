import java.awt.*;
import java.awt.image.*;
import java.applet.*;
import java.util.*;
import java.io.*;
import java.net.*;

/**
 * Given a Planet object, a PlanetClassifier will supply descriptive
 * text and a graphical image representing the planet.  You need one
 * PlanetClassifier for each classification scheme you want to implement.
 * Override the methods of this class to change the scheme, or reimplement
 * the class to produce general behavior instead of the hard-wired stuff here.
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
public class PlanetClassifier implements ImageObserver
{
    private Image[] planetImages;
    private Image[] loadingImages;
    private Image[] stockImages;
    private Image[] workingImages;

    /**
     * Constructor.
     * @param context Applet within which this classifier exists.
     */
    public PlanetClassifier(Applet context)
    {
    	int i;
    	
    	planetImages = new Image[10];
    	loadingImages = new Image[10];
    	stockImages = new Image[10];
    	workingImages = new Image[10];
	// create the stock images
	for (i=0; i<10; i++)
	{
	    stockImages[i] = context.createImage(100,100);
	    Graphics wg = stockImages[i].getGraphics();
	    wg.setColor(Color.black);
	    wg.fillRect(0, 0, 100, 100);
	    wg.setColor(Color.gray);
	    wg.fillOval(0, 0, 100, 100);
	    wg.dispose();
	    planetImages[i] = stockImages[i];
	}
    	// set up the image loading process
	loadingImages[0] = context.getImage(context.getDocumentBase(), "Mercury.jpg");
	loadingImages[1] = context.getImage(context.getDocumentBase(), "Venus.jpg");
	loadingImages[2] = context.getImage(context.getDocumentBase(), "Earth.jpg");
	loadingImages[3] = context.getImage(context.getDocumentBase(), "Mars.jpg");
	loadingImages[4] = context.getImage(context.getDocumentBase(), "Jupiter.jpg");
	loadingImages[5] = context.getImage(context.getDocumentBase(), "Uranus.jpg");
	loadingImages[6] = context.getImage(context.getDocumentBase(), "Neptune.jpg");
	loadingImages[7] = context.getImage(context.getDocumentBase(), "Callisto.jpg");
	loadingImages[8] = context.getImage(context.getDocumentBase(), "Europa.jpg");
	loadingImages[9] = context.getImage(context.getDocumentBase(), "Other.jpg");
	// start the images loading
	for (i=0; i<10; i++)
	{
	    workingImages[i] = context.createImage(1,1);
	    Graphics wg = workingImages[i].getGraphics();
	    wg.drawImage(loadingImages[i], 0, 0, this);
	    wg.dispose();
	}
    }
    public void flush()
    {
    	planetImages[0].flush();
    	planetImages[1].flush();
    	planetImages[2].flush();
    	planetImages[3].flush();
    	planetImages[4].flush();
    	planetImages[5].flush();
    	planetImages[6].flush();
    	planetImages[7].flush();
    	planetImages[8].flush();
    	planetImages[9].flush();
    	planetImages = null;
    }
    public boolean imageUpdate(Image img, int infoflags, int x, int y, int width, int height)
    {
	int i;
	if ((infoflags & ImageObserver.ALLBITS) != 0)
	{
	    for (i=0; i<10; i++)
	    {
		if (img == loadingImages[i])
		{
		    planetImages[i] = loadingImages[i];
		    loadingImages[i] = null;
		    workingImages[i].flush();
		    stockImages[i].flush();
		    workingImages[i] = null;
		    stockImages[i] = null;
		    return false;
		}
	    }
	}
	return true;
    }

    /**
     * Returns an image representing the planet in general terms.
     * @param p Planet object to be described
     * @returns Image representation
     */
    public Image planetImage(Planet p)
    {
    	if (p.mass < 0.01) return planetImages[9];
    	if (p.gas_giant)
    	{
    		if (p.mass < 50.0) return planetImages[6];
    		else return planetImages[4];
    	}
    	else
    	{
	    // try Irony Games classification scheme first, then backfill
	    /*
		Irony Games classification system:
	    T classification:
		mass > .4
		0.65 < a < 1.35 (* r_ecosphere)
		avg deg > freezing > -45
		50 < surf_press < 8000
		not gas giant - allows hydrogen to escape
		ice cover and/or water cover > 0
	    E classification:
		age > 2.7 gy (age of star)
		0.8 < a < 1.2 (*r_ecosphere)
		day < 96 hr
		350 < surf_press < 2600
		-1 < avg deg>freezing < 30
		helium escapes, but not nitrogen
		water cover > 0, rock cover > 0
	     */
	    if ((p.mass > 0.4) &&
		(p.a > 0.65*p.r_ecosphere) &&
		(p.a < 1.35*p.r_ecosphere) &&
		(p.surf_temp > (273.15-45.0)) &&
		(p.surf_pressure > 0.05) &&
		(p.surf_pressure < 8000.0) &&
		((p.ice_cover > 0.0) || (p.hydrosphere > 0.0))
		) return planetImages[2];
	    if (p.ice_cover > 0.95) return planetImages[8];
		if (p.surf_temp < 100.0) return planetImages[7];
	    if (p.surf_pressure <0.01)
	    {
		if (p.surf_temp < 273.0) return planetImages[3];
		return planetImages[0];
	    }
	    else if (p.surf_pressure > 10000.0)
	    {
		if (p.surf_temp > 273.0) return planetImages[1];
		else return planetImages[5];
	    }
	    else
	    {
		if (p.surf_temp > (((p.boil_point-273.0)/2.0) + 273.0)) return planetImages[1];
		if (p.surf_temp < 273.0) return planetImages[3];
		return planetImages[2];
	    }
        }
    }

    /**
     * Returns a string describing the planet in general terms.
     * @param p Planet object to be described
     * @returns Constant string description
     */
    public String planetType(Planet p)
    {
    	if (p.mass < 0.01) return "Asteroidal";
    	if (p.gas_giant)
    	{
	    if (p.mass < 50.0) return "Small gas giant";
	    else if (p.mass > 1000.0) return "Brown dwarf";
	    else return "Large gas giant";
    	}
    	else
    	{
	    if ((p.age > 2.7) &&
		(p.a > 0.8*p.r_ecosphere) &&
		(p.a < 1.2*p.r_ecosphere) &&
		(p.day < 96.0) &&
		(p.surf_temp > (273.15-1.0)) &&
		(p.surf_temp < (273.15+30.0)) &&
		(p.surf_pressure > 0.36) &&
		(p.surf_pressure < 2600.0) &&
		((p.ice_cover+p.hydrosphere < 1.0) && (p.hydrosphere > 0.0))
		) return "Habitable";
	    if ((p.mass > 0.4) &&
		(p.a > 0.65*p.r_ecosphere) &&
		(p.a < 1.35*p.r_ecosphere) &&
		(p.surf_temp > (273.15-45.0)) &&
		(p.surf_pressure > 0.05) &&
		(p.surf_pressure < 8000.0) &&
		((p.ice_cover > 0.0) || (p.hydrosphere > 0.0))
		) return "Marginally habitable";
	    if (p.ice_cover > 0.95) return "Iceworld";
		if (p.surf_temp < 100.0) return "Frigid airless rock";
	    if (p.surf_pressure <0.01)
	    {
		if (p.surf_temp < 273.0) return "Cold airless rock";
		return "Hot airless rock";
	    }
	    else if (p.surf_pressure > 10000.0)
	    {
		if (p.surf_temp > 273.0) return "Hot, dense atmosphere";
		else return "Cold, dense atmosphere";
	    }
	    else
	    {
		if (p.surf_temp > (((p.boil_point-273.0)/2.0) + 273.0)) return "Hot terrestrial";
		if (p.surf_temp < 273.0) return "Frozen terrestrial";
		return "Terrestrial";
	    }
        }
    }
}

