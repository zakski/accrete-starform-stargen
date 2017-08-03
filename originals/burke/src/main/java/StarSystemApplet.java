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
 * This class provides the applet shell within which the simulation does
 * its thing.
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
public class StarSystemApplet extends java.applet.Applet
{
	private SystemDisplayText sdpPanel;
	private SystemDisplayScale sdsPanel;
	private SystemDisplayFlat sdfPanel;
	private StarSystem ss;
	private PlanetClassifier pc;
	private long randomSeed;
	private String currentSeed;
	public void init()
	{
	    // 	You can add code anywhere in this method.

	    SuperCedeInit();   // Do not remove this line
	    setBackground(Color.black);
	    pc = new PlanetClassifier(this);
	    sdpPanel = new SystemDisplayText(pc);
	    add(sdpPanel);
	    sdpPanel.move(0,30);
	    sdsPanel = new SystemDisplayScale(pc);
	    add(sdsPanel);
	    sdsPanel.move(0,250);
	    sdfPanel = new SystemDisplayFlat(pc);
	    add(sdfPanel);
	    sdfPanel.move(0,450);
	    randomSeed = AccreteObject.cr.nextLong();
	    AccreteObject.cr.setSeed(randomSeed);
	    currentSeed = Long.toString(randomSeed, 16);
	    textField1.setText(Long.toString(randomSeed, 16));
	}
	// in SuperCede, either as a stand-alone graphical applet or in the applet viewer,
	// I need to handle removeNotify() etc for all my components or I lose an incredible
	// amount (>10%) in system resources every time I start and exit the program.
	// However, this code crashes Netscape _hard_ when the applet exits (maybe because
	// of the call to System.exit(), but I haven't tested it yet.
	// removing gc and runfinalization keeps netscape from crashing,
	// but there are some other spurious problems; I'll just drop this
	// routine for use in a browser.
	
	public void destroy()
	{
	    if (pc!=null) pc.flush();
	    ss=null;
	    sdpPanel.flush();
	    sdsPanel.flush();
	    sdfPanel.flush();
	    BuildButton.hide();BuildButton.disable();BuildButton.removeNotify();BuildButton=null;
	    button1.hide();button1.disable();button1.removeNotify();button1=null;
	    textField1.hide();textField1.disable();textField1.removeNotify();textField1=null;
	    hide();
	    disable();
	    removeNotify();
	    //System.gc();  // makes Netscape unstable
	    //System.runFinalization();  // makes Netscape unstable
	    //System.exit( 0 );
	}
	
	public void paint(Graphics g)
	{
	    g.setColor(Color.yellow);
	    g.drawString("Seed:", (insets().left + 219), (insets().top + 20));
	    g.setColor(Color.white);
	    g.drawString(currentSeed, (insets().left + 262), (insets().top + 20));
	}
	public boolean handleEvent( Event event )
	{
	    // 	Tests for custom events go here...

	    return SuperCedeEvent( event );   // Do not remove this line
	}

	public boolean action( Event event, Object arg )
	{
	    if (event.target instanceof Button)
	    {
		String label = (String) arg;
		if (label.startsWith( "Make" ))
		{
		    AccreteObject.cr.setSeed(randomSeed);
		    ss = new StarSystem();
		    sdsPanel.setSystem(ss);
		    sdpPanel.setSystem(ss);
		    sdfPanel.setSystem(ss);
		    randomSeed = AccreteObject.cr.nextLong();
		    currentSeed = Long.toString(randomSeed, 16);
		    AccreteObject.cr.setSeed(randomSeed);
		    textField1.setText(Long.toString(randomSeed, 16));
		    repaint();
		    return true;
		}
		if (label.startsWith( "Set" ))
		{
		    try
		    {
			randomSeed = Long.parseLong(textField1.getText(), 16);
			AccreteObject.cr.setSeed(randomSeed);
			currentSeed = Long.toString(randomSeed, 16);
			repaint();
		    }
		    catch (NumberFormatException nfe)
		    {
			textField1.setText("????????");
		    }
		    return true;
		}
	    }
	    return super.action( event, arg );
	}

	public void start()
	{
	    // 	You can add code anywhere in this method.

	    SuperCedeStart();   // Do not remove this line
	}

	public void stop()
	{
	    // 	You can add code anywhere in this method.

	    SuperCedeStop();   // Do not remove this line
	}

	// SuperCede Begin Methods
	// 	Do not remove the Begin and End markers.
	// 	The editor will rewrite the contents of this section each time the form is saved.
	private final void SuperCedeInit()
	{
	    setLayout( null );
	    setForeground( new Color( 255, 255, 255 ));
	    setBackground( new Color( 0, 0, 0 ));
	    addNotify();
	    resize( (insets().left + insets().right + 600), (insets().top + insets().bottom + 730) );

	    BuildButton = new Button( "Make a new solar system" );
	    BuildButton.setForeground( new Color( 255, 255, 255 ));
	    BuildButton.setBackground( new Color( 128, 128, 128 ));
	    add( BuildButton );
	    BuildButton.reshape( (insets().left + 0), (insets().top + 0), 200, 30 );

	    textField1 = new TextField( "" );
	    textField1.setEditable( true );
	    add( textField1 );
	    textField1.reshape( (insets().left + 475), (insets().top + 0), 125, 30 );

	    button1 = new Button( "Set Seed" );
	    add( button1 );
	    button1.reshape( (insets().left + 399), (insets().top + 0), 74, 30 );

	    super.init();
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
	Button BuildButton;
	TextField textField1;
	Button button1;
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
// 600 730 0 0 16777215 0
// 1 0 1 1 0 "StarSystemApplet" 0 0 0 2 2 0 T T F T F
// ""
// F F F F F F F F F F F F F
// 3
// {839BC52C-F563-11CF-B16F-0020AFDA72B7} 0 200 0 30
//   "Make a new solar system" F 3 "BuildButton" 2 200 30 4 T T F 0 16777215 8421504  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "" F
// {839BC52A-F563-11CF-B16F-0020AFDA72B7} 475 600 0 30
//   "" F F "" 3 "textField1" 2 125 30 4 T T T 0 0 16777215  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "" T
// {839BC52C-F563-11CF-B16F-0020AFDA72B7} 399 473 0 30
//   "Set Seed" F 3 "button1" 2 74 30 4 T T T 0 0 16777215  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "" T
// 3 0 1 2
// SuperCede End Properties
