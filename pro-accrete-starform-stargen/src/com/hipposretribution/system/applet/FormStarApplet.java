package com.hipposretribution.system.applet;

import processing.core.PApplet;

import com.hippsoretribution.controlP5.events.input.keys.KeyStorage;
import com.hippsoretribution.controlP5.events.input.mouse.MousePointer;

public class FormStarApplet extends PApplet {

	private static final long serialVersionUID = -4940464770921011002L;

	private static final long holdTime = 5000;
	private KeyStorage keyStorage;
	FormStarGUI gui;

	public void setup() {
		size(764, 764, P2D);
		keyStorage = new KeyStorage(holdTime);

		gui = new FormStarGUI(this, new MousePointer(), keyStorage, true);
	}

	public void draw() {
		keyHeldHandle();
		background(0);
		fill(255);
	}

	protected void keyHeldHandle() {
		for (int key : keyStorage.keysDown()) {
			switch (key) {
			default:
		//		System.out.println("key \"" + KeyEvent.getKeyText(key) + "\" held");
			}
		}
	}


	public static void main(String args[]) {
		PApplet.main(new String[] { "com.hipposretribution.system.applet.FormStarApplet" });
	}
}
