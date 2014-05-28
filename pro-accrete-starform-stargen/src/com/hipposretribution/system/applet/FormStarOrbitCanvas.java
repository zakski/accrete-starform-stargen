package com.hipposretribution.system.applet;

import processing.core.PApplet;

import com.hipposretribution.system.formstar.SolarConst;
import com.hipposretribution.system.formstar.SolarSystem;
import com.hipposretribution.system.formstar.planetoid.Planet;
import com.hippsoretribution.controlP5.drawable.Canvas;

public class FormStarOrbitCanvas extends Canvas {
	private SolarSystem sys;
	private float centreX;
	private float centreY;
	private float size;
	private double[] arrayX;
	private double[] arrayY;

	public FormStarOrbitCanvas(float nx, float ny, float length) {
		size = length;
		centreX = nx + size / 2;
		centreY = ny + size / 2;

		arrayX = new double[36];
		arrayY = new double[36];

	}

	public void setSystem(SolarSystem system) {
		sys = system;
	}

	private double log10(double x) {
		return Math.log(x) / Math.log(10.0);
	}

	/*
	 * Compute the screen position of a given orbital distance.
	 */
	private int computex(double r) {
		if (r <= 0.0)
			return 0;
		return (int) ((log10(r) + 1.1) * size / 3.25) / 2;
	}

	private void showOrbit(PApplet applet, Planet planet) {
		int j;
		double t; /* current time */
		double n = (2.0 * Math.PI) / planet.orbitPeriod; /* daily motion in radians/day */
		double M; /* mean anomaly */
		double E, E0, E1; /* eccentric anomaly */
		double v; /* true anomaly */
		double r; /* heliocentric distance; distance from primary */
		double x, y;
		double a_e = planet.axis * planet.ecc;
		double a_sqrt_1_minus_e2 = planet.axis * Math.sqrt(1.0 - planet.ecc * planet.ecc);

		for (j = 0; j < 36; j++) {
			t = j * planet.orbitPeriod / 36.0; /* current time */
			M = n * t; /* mean anomaly */

			E1 = M + planet.ecc * Math.sin(M) * (1.0 + planet.ecc * Math.cos(M));
			E0 = 0.0;
			while (Math.abs(E1 - E0) > 0.005) {
				E0 = E1;
				E1 = E0 - (E0 - planet.ecc * Math.sin(E0) - M) / (1.0 - planet.ecc * Math.cos(E0));
			}
			E = E1;

			x = planet.axis * Math.cos(E) - a_e;
			y = a_sqrt_1_minus_e2 * Math.sin(E);

			r = Math.sqrt(x * x + y * y);
			v = Math.atan2(y, x);

			arrayX[j] = computex(r) * Math.cos(v);
			arrayY[j] = computex(r) * Math.sin(v);
		}
		// draw the orbit
		for (j = 0; j < 35; j++) {
			applet.line(centreX + (int) arrayX[j], centreY + (int) arrayY[j], centreX + (int) arrayX[j + 1], centreY
					+ (int) arrayY[j + 1]);
		}
		applet.line(centreX + (int) arrayX[35], centreY + (int) arrayY[35], centreX + (int) arrayX[0], centreY
				+ (int) arrayY[0]);
	}

	private void showPlanet(PApplet applet, Planet planet) {
		int j = 0;
		// double t; /* current time */
		// double n = (2.0 * Math.PI) / p.orbitPeriod; /* daily motion in radians/day */
		double M = (2.0 * Math.PI) / planet.orbitPeriod; /* mean anomaly */
		double E, E0, E1; /* eccentric anomaly */
		double v; /* true anomaly */
		double r; /* heliocentric distance; distance from primary */
		float x, y;
		double a_e = planet.axis * planet.ecc;
		double a_sqrt_1_minus_e2 = planet.axis * Math.sqrt(1.0 - planet.ecc * planet.ecc);
		int dradius;

		// compute orbital locations
		// while (w > (2.0 * Math.PI))
		// w -= 2.0 * Math.PI;
		// t = 0.0; /* current time */
		// M = n * t; /* mean anomaly */

		E1 = M + planet.ecc * Math.sin(M) * (1.0 + planet.ecc * Math.cos(M));
		E0 = 0.0;
		while (Math.abs(E1 - E0) > 0.005) {
			E0 = E1;
			E1 = E0 - (E0 - planet.ecc * Math.sin(E0) - M) / (1.0 - planet.ecc * Math.cos(E0));
		}
		E = E1;

		x = (float) (planet.axis * Math.cos(E) - a_e);
		y = (float) (a_sqrt_1_minus_e2 * Math.sin(E));

		r = Math.sqrt(x * x + y * y);
		v = Math.atan2(y, x);

		x = (float) (computex(r) * Math.cos(v));
		y = (float) (computex(r) * Math.sin(v));

		dradius = (int) Math.log((planet.radius  / SolarConst.KM_PER_AU)) * 2;
		if (dradius < 1)
			dradius = 1;

		applet.ellipse(centreX - dradius + x, centreY - dradius + y, 2 * dradius, 2 * dradius);
	}

	@Override
	public void draw(PApplet applet) {
		if (sys == null)
			return;

//		applet.pushStyle();
//		applet.stroke(255);
//		applet.strokeWeight(2);
//		applet.noFill();
//		applet.rect(centreX - size/2 + 1, centreY - size/2 - 1, size, size);
//		applet.popStyle();
		
		applet.pushStyle();
		applet.fill(255);
		for (Planet planet = sys.innermost; planet != null; planet = planet.next) {
			applet.stroke(125);
			showOrbit(applet, planet);
			applet.noStroke();
			showPlanet(applet, planet);
		}
		applet.popStyle();
	}
}
