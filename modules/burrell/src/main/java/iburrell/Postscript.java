package iburrell;
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/01/15
// Modified: 1997/02/09

// Copyright 1997 Ian Burrell

import java.io.*;

public class Postscript
{

    int page = 0;
    double base = 50.0;
    double xscale = 1.0;
    double yscale = 1.0;
    double xoff = 0.0;
    double yoff = 0.0;
    static final double width = 450;

    PrintStream out;

    public Postscript(String psfile) {
        try {
            out = new PrintStream(new FileOutputStream(psfile));
        }
        catch (IOException e) {
            System.err.println(e);
        }
    }
    public Postscript(PrintStream output) {
        out = output;
    }

    protected void begin(int numpage) {
        out.println("%!PS-Adobe-2.1");
        out.println("%%Pages: " + numpage);
        out.println("%%EndComments");
        out.println("/Helvetica findfont 12 scalefont setfont");
        out.println("0 setlinewidth");
        out.println("newpath");
        out.println("%%EndProlog");
        beginpage();
    }

    protected void end() {
        out.println("%%Trailer");
        out.println("end");
    }

    protected void beginpage() {
        beginpage(++page);
    }
    
    protected void beginpage(int pg) {
        out.println("%%Page: " + pg + " " + pg);
        out.println((xoff+base) + " " + yoff+base + " translate");
        out.println(xscale + " " + yscale + " " + " scale");
        out.println("/Helvetica findfont " + 9/xscale + " scalefont setfont");
        out.println("0 setlinewidth");
    }

    protected void showpage() {
        out.println("showpage");
    }

    protected void window(double x1, double y1, double x2, double y2) {
        double xspan = x2 - x1;
        double yspan = y2 - y1;
        xscale = width / xspan;
        yscale = width / yspan;
        xoff = -xscale * x1;
        yoff = -yscale * y1;
    }

    protected void circle(double x, double y, double radius, boolean fill) {
        out.print(x + " " + y + " " + radius + " 0 360 arc ");
        String type = fill ? "fill" : "stroke";
        out.println(type);
    }

    protected void line(double x1, double y1, double x2, double y2) {
        out.print(x1 + " " + y1 + " moveto ");
        out.print(x2 + " " + y2 + " lineto stroke");
        out.println();
    }

    protected void text(double x, double y, String s) {
        out.println(x + " " + y + " moveto (" + s + ") show newpath");
    }

}
