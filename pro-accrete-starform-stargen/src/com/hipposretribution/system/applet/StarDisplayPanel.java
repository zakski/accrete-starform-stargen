//package com.hipposretribution.system.applet;
//// 	You can add code anywhere in this file - except in the areas that are
//// 	written by the editor. You should not change the relative ordering of
//// 	the code. The constructor must precede the event handlers, which must
//// 	precede handleEvent(), and so on.
//// 	 
//// 	You can remove this comment block or replace it with another.
//
//import java.awt.Color;
//import java.awt.Event;
//import java.awt.Font;
//import java.awt.Graphics;
//import java.awt.Panel;
//
///**
// *
// * <p><strong><center>Copyright information</center></strong></p>
// * <p>This Java class is copyright 1998 by Carl Burke. All rights reserved.
// * Substantial sections of this code were previously distributed in
// * different form as part of 'starform' (copyright 1989 Matthew Burdick)<p>
// * <p>This software is provided absolutely free and without warranty,
// * including but not limited to the implied warranties of merchantability
// * and fitness for a purpose.  You may use this code for any legal purpose
// * provided that you do not charge for it; this implies that you <em>may</em>
// * use this code as a component of a commercial system as long as the additional
// * functionality of the commercial system is greater than what this code
// * provides and that the commercial system is not primarily intended as
// * a simulation of solar system formation.  In other words, if you want to
// * write a science-fiction computer game that uses the code in this package
// * to build objects which are used in the game, that's great and permitted;
// * if you use this code to make a kickass solar-system-builder, you are not
// * allowed to distribute that software except for free.
// * <p>You are allowed and encouraged to modify this software, provided that
// * this copyright notice remains intact.  This notice may be reformatted,
// * but not removed.
// * <p>If you do use this software, I and the contributing authors listed
// * under "Acknowledgements" would appreciate some recognition.  If you make
// * changes, I would appreciate it if you would pass those changes back to me
// * for possible inclusion in the master.  At the time this notice was prepared,
// * my email address is <a href="mailto:cburke@mitre.org">cburke@mitre.org</a> and the home page for this software is
// * <a href="http://www.geocities.com/Area51/6902/w_accr.html">http://www.geocities.com/Area51/6902/w_accr.html</a>.
// * <a name="ack"><strong><center>Acknowledgements</center></strong></a>
// * <p>Matt Burdick, the author of 'starform' (freeware copyright 1989);
// * much of the code (particularly planetary environments) was adapted from this.</p>
// * <p>Andrew Folkins, the author of 'accretion' (public domain) for the Amiga; I used chunks
// * of his code when creating my displays.</p>
// * <p>Ed Taychert of <a href="http://www.irony.com/">Irony Games</a>, for the algorithm he uses 
// * to classify terrestrial planets in his tabular CGI implementation of 'starform'.</p>
// * <p>Paul Schlyter, who provided information about 
// * <a href="http://spitfire.ausys.se/psr/comp/ppcomp.html">computing planetary positions</a>.</p>
// */
//public class StarDisplayPanel extends Panel
//{
//    private Star star;
//	public StarDisplayPanel()
//	{
//		super();
//
//		// 	You can add code anywhere in this method, except before the call to super().
//
//		SuperCedeConstructor();   // Do not remove this line
//	}
//	private String trimValue(double d)
//	{
//		String s = Double.toString(d);
//		int i = s.indexOf(".");
//		if ((i+2)<s.length())
//		{
//			s = s.substring(0, i+3);
//		}
//		return s;
//	}
//	public void setStar(Star s)
//	{
//		star = s;
//		repaint();
//	}
//    public void paint(Graphics g)
//    {
//    	g.setColor(Color.yellow);
//		g.drawString( "Stellar class:", (insets().left + 12), (insets().top + 115) );
//		g.drawString( "Mass:", (insets().left + 12), (insets().top + 131) );
//		g.drawString( "Magnitude:", (insets().left + 12), (insets().top + 147) );
//		g.drawString( "Emission:", (insets().left + 12), (insets().top + 163) );
//		g.drawString( "Age:", (insets().left + 12), (insets().top + 179) );
//		g.drawString( "Ecosphere:", (insets().left + 12), (insets().top + 195) );
//		g.drawString( "Greenhouse:", (insets().left + 12), (insets().top + 211) );
//		if (star==null) return;
//    	g.setColor(Color.white);
//		g.drawString( star.classCode(), (insets().left + 90), (insets().top + 115) );
//		g.drawString( trimValue(star.SM), (insets().left + 90), (insets().top + 131) );
//		g.drawString( trimValue(star.VM), (insets().left + 90), (insets().top + 147) );
//		g.drawString( trimValue(star.EM), (insets().left + 90), (insets().top + 163) );
//		g.drawString( trimValue(star.age/1.0E9)+" gy", (insets().left + 90), (insets().top + 179) );
//		g.drawString( trimValue(star.r_ecosphere), (insets().left + 90), (insets().top + 195) );
//		g.drawString( trimValue(star.r_greenhouse), (insets().left + 90), (insets().top + 211) );
//    }
//    public void flush()
//    {
//    	star=null;
//		hide();
//		disable();
//		removeNotify();
//    }
//    
//	public boolean handleEvent( Event event )
//	{
//		// 	Tests for custom events go here...
//
//		return SuperCedeEvent( event );   // Do not remove this line
//	}
//
//	public boolean action( Event event, Object arg )
//	{
//		return super.action( event, arg );
//	}
//
//
//
//	// SuperCede Begin Methods
//	// 	Do not remove the Begin and End markers.
//	// 	The editor will rewrite the contents of this section each time the form is saved.
//	private final void SuperCedeConstructor()
//	{
//		setLayout( null );
//		setFont( new Font( "Helvetica", Font.PLAIN, 10 ));
//		setForeground( Color.white);
//		setBackground( Color.black);
//		resize( (insets().left + insets().right + 140), (insets().top + insets().bottom + 220) );
//	}
//
//	private final boolean SuperCedeEvent( Event event )
//	{
//		return super.handleEvent( event );
//	}
//
//	// SuperCede End Methods
//
//	// SuperCede Begin Declarations
//	// 	Do not remove the Begin and End markers.
//	// 	The editor will rewrite the contents of this section each time the form is saved.
//	// SuperCede End Declarations
//}
//
