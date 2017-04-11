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
public class SystemDisplayText extends Panel 
{
    private Checkbox[] cb;
    private CheckboxGroup cg;
    private PlanetClassifier pc;
    private StarSystem ss;
    private Planet[] pArray;
    public void setSystem(StarSystem SS)
    {
    	Planet p;
    	int i;
    	
    	ss = SS;
    	sdp.setStar(ss.primary);
    	pd.setPlanet(ss.planets);
    	for (i=0; i<23; i++) cb[i].hide();
    	for (i=0, p=ss.planets; (i<23)&&(p!=null); i++, p=p.next_planet)
    	{
    		cb[i].show();
    	}
    	cg.setCurrent(cb[0]);
    }
	public SystemDisplayText(PlanetClassifier PC)
	{
		super();

		// 	You can add code anywhere in this method, except before the call to super().
		pc = PC;
		
		SuperCedeConstructor();   // Do not remove this line

		pArray = new Planet[23];
		cb = new Checkbox[23];
		cb[0] = checkbox1;
		cb[1] = checkbox2;
		cb[2] = checkbox3;
		cb[3] = checkbox4;
		cb[4] = checkbox5;
		cb[5] = checkbox6;
		cb[6] = checkbox7;
		cb[7] = checkbox8;
		cb[8] = checkbox9;
		cb[9] = checkbox10;
		cb[10] = checkbox11;
		cb[11] = checkbox12;
		cb[12] = checkbox13;
		cb[13] = checkbox14;
		cb[14] = checkbox15;
		cb[15] = checkbox16;
		cb[16] = checkbox17;
		cb[17] = checkbox18;
		cb[18] = checkbox19;
		cb[19] = checkbox20;
		cb[20] = checkbox21;
		cb[21] = checkbox22;
		cb[22] = checkbox23;
		cg = new CheckboxGroup();
		for (int i=0; i<23; i++)
		{
			cb[i].setCheckboxGroup(cg);
			cb[i].hide();
		}
	}
	public void flush()
	{
		sdp.flush();
		pd.flush();
		setFont(null);
		setForeground(Color.black);
		setBackground(Color.black);
		for (int i=0; i<23; i++)
		{
			cb[i].setCheckboxGroup(null);
			cb[i].hide();
			cb[i].disable();
			cb[i].removeNotify();
			cb[i]=null;
		}
		checkbox1=null;
		checkbox2=null;
		checkbox3=null;
		checkbox4=null;
		checkbox5=null;
		checkbox6=null;
		checkbox7=null;
		checkbox8=null;
		checkbox9=null;
		checkbox10=null;
		checkbox11=null;
		checkbox12=null;
		checkbox13=null;
		checkbox14=null;
		checkbox15=null;
		checkbox16=null;
		checkbox17=null;
		checkbox18=null;
		checkbox19=null;
		checkbox20=null;
		checkbox21=null;
		checkbox22=null;
		checkbox23=null;
		cg.setCurrent(cb[0]);
		cb=null;
		cg=null;
		ss=null;
		pc=null;
		pd=null;
		sdp=null;
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
		if (event.target instanceof Checkbox)
		{
			int i, j, pCount;
			Planet p;
			for (pCount=0, p=ss.planets; (pCount<23) && (p!=null); pArray[pCount++]=p, p=p.next_planet);
			for (i=0; i<(pCount-1); i++) for (j=i+1; j<pCount; j++)
			{
				if (pArray[j].a < pArray[i].a)
				{
					Planet temp = pArray[i];
					pArray[i] = pArray[j];
					pArray[j] = temp;
				}
			}
			for (i=0;i<pCount;i++)
			{
				if (event.target.equals(cb[i]))
				{
					pd.setPlanet(pArray[i]);
				}
			}
		}
		return super.action( event, arg );
	}

	// SuperCede Begin Methods
	// 	Do not remove the Begin and End markers.
	// 	The editor will rewrite the contents of this section each time the form is saved.
	private final void SuperCedeConstructor()
	{
		setLayout( null );
		setFont( new Font( "Helvetica", Font.PLAIN, 10 ));
		setForeground( Color.white);
		setBackground( Color.black);
		resize( (insets().left + insets().right + 600), (insets().top + insets().bottom + 220) );

		pd = new PlanetDisplay(pc);
		add( pd );
		pd.reshape( (insets().left + 140), (insets().top + 20), 460, 200 );

		sdp = new StarDisplayPanel();
		add( sdp );
		sdp.reshape( (insets().left + 0), (insets().top + 0), 140, 220 );

		checkbox1 = new Checkbox();
		checkbox1.setBackground( Color.black);
		add( checkbox1 );
		checkbox1.reshape( (insets().left + 140), (insets().top + 0), 20, 20 );

		checkbox2 = new Checkbox();
		checkbox2.setBackground( Color.black);
		add( checkbox2 );
		checkbox2.reshape( (insets().left + 160), (insets().top + 0), 20, 20 );

		checkbox3 = new Checkbox();
		checkbox3.setBackground( Color.black);
		add( checkbox3 );
		checkbox3.reshape( (insets().left + 180), (insets().top + 0), 20, 20 );

		checkbox4 = new Checkbox();
		checkbox4.setBackground( Color.black);
		add( checkbox4 );
		checkbox4.reshape( (insets().left + 200), (insets().top + 0), 20, 20 );

		checkbox5 = new Checkbox();
		checkbox5.setBackground( Color.black);
		add( checkbox5 );
		checkbox5.reshape( (insets().left + 220), (insets().top + 0), 20, 20 );

		checkbox6 = new Checkbox();
		checkbox6.setBackground( Color.black);
		add( checkbox6 );
		checkbox6.reshape( (insets().left + 240), (insets().top + 0), 20, 20 );

		checkbox7 = new Checkbox();
		checkbox7.setBackground( Color.black);
		add( checkbox7 );
		checkbox7.reshape( (insets().left + 260), (insets().top + 0), 20, 20 );

		checkbox8 = new Checkbox();
		checkbox8.setBackground( Color.black);
		add( checkbox8 );
		checkbox8.reshape( (insets().left + 280), (insets().top + 0), 20, 20 );

		checkbox9 = new Checkbox();
		checkbox9.setBackground( Color.black);
		add( checkbox9 );
		checkbox9.reshape( (insets().left + 300), (insets().top + 0), 20, 20 );

		checkbox10 = new Checkbox();
		checkbox10.setBackground( Color.black);
		add( checkbox10 );
		checkbox10.reshape( (insets().left + 320), (insets().top + 0), 20, 20 );

		checkbox11 = new Checkbox();
		checkbox11.setBackground( Color.black);
		add( checkbox11 );
		checkbox11.reshape( (insets().left + 340), (insets().top + 0), 20, 20 );

		checkbox12 = new Checkbox();
		checkbox12.setBackground( Color.black);
		add( checkbox12 );
		checkbox12.reshape( (insets().left + 360), (insets().top + 0), 20, 20 );

		checkbox13 = new Checkbox();
		checkbox13.setBackground( Color.black);
		add( checkbox13 );
		checkbox13.reshape( (insets().left + 380), (insets().top + 0), 20, 20 );

		checkbox14 = new Checkbox();
		checkbox14.setBackground( Color.black);
		add( checkbox14 );
		checkbox14.reshape( (insets().left + 400), (insets().top + 0), 20, 20 );

		checkbox15 = new Checkbox();
		checkbox15.setBackground( Color.black);
		add( checkbox15 );
		checkbox15.reshape( (insets().left + 420), (insets().top + 0), 20, 20 );

		checkbox16 = new Checkbox();
		checkbox16.setBackground( Color.black);
		add( checkbox16 );
		checkbox16.reshape( (insets().left + 440), (insets().top + 0), 20, 20 );

		checkbox17 = new Checkbox();
		checkbox17.setBackground( Color.black);
		add( checkbox17 );
		checkbox17.reshape( (insets().left + 460), (insets().top + 0), 20, 20 );

		checkbox18 = new Checkbox();
		checkbox18.setBackground( Color.black);
		add( checkbox18 );
		checkbox18.reshape( (insets().left + 480), (insets().top + 0), 20, 20 );

		checkbox19 = new Checkbox();
		checkbox19.setBackground( Color.black);
		add( checkbox19 );
		checkbox19.reshape( (insets().left + 500), (insets().top + 0), 20, 20 );

		checkbox20 = new Checkbox();
		checkbox20.setBackground( Color.black);
		add( checkbox20 );
		checkbox20.reshape( (insets().left + 520), (insets().top + 0), 20, 20 );

		checkbox21 = new Checkbox();
		checkbox21.setBackground( Color.black);
		add( checkbox21 );
		checkbox21.reshape( (insets().left + 540), (insets().top + 0), 20, 20 );

		checkbox22 = new Checkbox();
		checkbox22.setBackground( Color.black);
		add( checkbox22 );
		checkbox22.reshape( (insets().left + 560), (insets().top + 0), 20, 20 );

		checkbox23 = new Checkbox();
		checkbox23.setBackground( Color.black);
		add( checkbox23 );
		checkbox23.reshape( (insets().left + 580), (insets().top + 0), 20, 20 );
	}

	private final boolean SuperCedeEvent( Event event )
	{
		return super.handleEvent( event );
	}

	// SuperCede End Methods

	// SuperCede Begin Declarations
	// 	Do not remove the Begin and End markers.
	// 	The editor will rewrite the contents of this section each time the form is saved.
	PlanetDisplay pd;
	StarDisplayPanel sdp;
	Checkbox checkbox1;
	Checkbox checkbox2;
	Checkbox checkbox3;
	Checkbox checkbox4;
	Checkbox checkbox5;
	Checkbox checkbox6;
	Checkbox checkbox7;
	Checkbox checkbox8;
	Checkbox checkbox9;
	Checkbox checkbox10;
	Checkbox checkbox11;
	Checkbox checkbox12;
	Checkbox checkbox13;
	Checkbox checkbox14;
	Checkbox checkbox15;
	Checkbox checkbox16;
	Checkbox checkbox17;
	Checkbox checkbox18;
	Checkbox checkbox19;
	Checkbox checkbox20;
	Checkbox checkbox21;
	Checkbox checkbox22;
	Checkbox checkbox23;
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
// 600 220 655360 0 16777215 8421504
// 5 0 1 1 2 "SystemDisplayText" 0 0 0 2 2 0 T T F T F
// ""
// F F F F F F F F F F F F F
// 25
// {839BC533-F563-11CF-B16F-0020AFDA72B7} 140 600 20 220
//   3 "pd" 2 460 200 4 T T T 0 0 16777215  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "" T
// {839BC533-F563-11CF-B16F-0020AFDA72B7} 0 140 0 220
//   3 "sdp" 2 140 220 4 T T T 0 0 16777215  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "" T
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 140 160 0 20
//   "" F F 3 "checkbox1" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 160 180 0 20
//   "" F F 3 "checkbox2" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 180 200 0 20
//   "" F F 3 "checkbox3" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 200 220 0 20
//   "" F F 3 "checkbox4" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 220 240 0 20
//   "" F F 3 "checkbox5" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 240 260 0 20
//   "" F F 3 "checkbox6" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 260 280 0 20
//   "" F F 3 "checkbox7" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 280 300 0 20
//   "" F F 3 "checkbox8" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 300 320 0 20
//   "" F F 3 "checkbox9" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 320 340 0 20
//   "" F F 3 "checkbox10" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 340 360 0 20
//   "" F F 3 "checkbox11" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 360 380 0 20
//   "" F F 3 "checkbox12" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 380 400 0 20
//   "" F F 3 "checkbox13" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 400 420 0 20
//   "" F F 3 "checkbox14" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 420 440 0 20
//   "" F F 3 "checkbox15" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 440 460 0 20
//   "" F F 3 "checkbox16" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 460 480 0 20
//   "" F F 3 "checkbox17" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 480 500 0 20
//   "" F F 3 "checkbox18" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 500 520 0 20
//   "" F F 3 "checkbox19" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 520 540 0 20
//   "" F F 3 "checkbox20" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 540 560 0 20
//   "" F F 3 "checkbox21" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 560 580 0 20
//   "" F F 3 "checkbox22" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// {839BC52D-F563-11CF-B16F-0020AFDA72B7} 580 600 0 20
//   "" F F 3 "checkbox23" 2 20 20 4 T T T 0 0 0  "Dialog" 100000 0 400 0 F F F F F F F F F F F F F -1 -1 1 1 F F 0 0 0 0 0 0 0 0 0 "Checkbox" F
// 25 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
// SuperCede End Properties
