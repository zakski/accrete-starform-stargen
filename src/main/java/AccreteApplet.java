
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/01/17
// Modified: 1997/02/09

// Copyright 1997 Ian Burrell

import java.applet.*;
import java.awt.*;
import java.util.*;

import iburrell.accrete.Accrete;
import iburrell.accrete.Planetismal;

import iburrell.accrete.gui.AppletFrame;

public class AccreteApplet extends Applet implements Runnable
{

    private boolean standalone;

    private Accrete gen = null;
    private Vector planets = null;
    
    public void init() {
        setBackground(Color.white);
        setForeground(Color.black);
        gen = new Accrete();
    }

    public void start() {
        run();
    }

    public void run() {
        planets = gen.DistributePlanets();
        repaint();
    }        
    
    public void paint(Graphics g) {
        DrawGrid(g);
        if (planets != null)
            DrawPlanets(g);
    }

    public boolean mouseDown(Event evt, int x, int y) {
        if (evt.clickCount >= 2) {
            start();
            repaint();
            return true;
        }
        return false;
    }
    
    
    private void DrawGrid(Graphics g) {
        int hscale = hscale();
        int vscale = vscale();
        int width = hscale * 3;
        int height = vscale * 2;

        g.setColor(Color.black);
        g.drawRect(0, 0, width, height);
        g.drawLine(0, vscale, width, vscale);

        int ticklen = vscale / 10;
        int ytick = height - ticklen;
        g.drawLine(1*hscale, height, 1*hscale, height - 2*ticklen);
        g.drawLine(2*hscale, height, 2*hscale, height - 2*ticklen);

        for (int i = 2; i < 10; i++) {
            int offset = (int)((double)hscale * log10((double)i));
            g.drawLine(offset, height, offset, ytick);
            g.drawLine(offset + hscale, height, offset + hscale, ytick);
            g.drawLine(offset + 2*hscale, height, offset + 2*hscale, ytick);
        }
        
    }

    private void DrawPlanets(Graphics g) {
        int hscale = hscale();
        int vscale = vscale();
        int rscale = hscale / 30;

        Enumeration e = planets.elements();
        
        while (e.hasMoreElements()) {
            Planetismal curr = (Planetismal)e.nextElement();
            double au = log10(curr.getOrbitalAxis());
            double rad = Math.pow(curr.getMassEarth(), 1.0/3.0);
            int r = (int)(rad * (double)rscale);
            int x0 = (int)(au * (double)hscale);
            int x = x0 + hscale - r;
            int y = vscale - r;
            if (curr.isGasGiant()) 
                g.drawOval(x, y, 2*r, 2*r);
            else
                g.fillOval(x, y, 2*r, 2*r);
        }
    }

    
    private int rscale() {
        return rscale(hscale(), vscale());
    }
    
    private int rscale(int hscale, int vscale) {
        return (hscale < vscale) ? hscale : vscale;
    }

    private int hscale() {
        int width = size().width;
        if ((width % 3) == 0)
            width--;
        return width / 3;
    }
    
    private int vscale() {
        int height = size().height;
        if ((height % 2) == 0)
            height--;
        return height / 2;
    }

    
    private static double log10(double a) {
        return Math.log(a) / Math.log(10.0);
    }


    public static void main(String[] args) {
        AccreteApplet app = new AccreteApplet();
        app.standalone = true;

        AppletFrame frame = new AppletFrame(app, 721, 241, "Accrete");
        
    }

}

