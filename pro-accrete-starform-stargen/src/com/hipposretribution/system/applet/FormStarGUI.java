//package com.hipposretribution.system.applet;
//
//import java.util.Random;
//
//import processing.core.PVector;
//
//import com.hipposretribution.controlP5.ControlP5Base;
//import com.hipposretribution.controlP5.elements.drawable.controllers.Group;
//import com.hipposretribution.controlP5.elements.drawable.controllers.Tab;
//import com.hipposretribution.controlP5.elements.drawable.controllers.press.Button;
//import com.hipposretribution.controlP5.elements.drawable.controllers.text.TextField;
//import com.hipposretribution.controlP5.events.callback.ControlEvent;
//import com.hipposretribution.controlP5.events.callback.ControlListener;
//import com.hipposretribution.controlP5.events.input.keys.KeyStorage;
//import com.hipposretribution.controlP5.events.input.mouse.MousePointer;
//import com.hipposretribution.system.formstar.SolarSystem;
//import com.hipposretribution.system.formstar.SystemGen;
//
//public class FormStarGUI implements ControlListener {
//
//	private ControlP5Base cp5;
//	private TextField seedText;
//	private FormStarApplet parent;
//	private Button timeButton;
//	private Button randomButton;
//	private Random randomSeed;
//	private SolarSystem solarSystem;
//
//	// private FormStarOrbitCanvas orbitCanvas;
//
//	public FormStarGUI(FormStarApplet applet, MousePointer pointer, KeyStorage storage, boolean shorts) {
//		parent = applet;
//		cp5 = new ControlP5Base(applet, pointer, storage);
//		randomSeed = new Random();
//
//		if (shorts) {
//			cp5.enableShortcuts();
//		}
//
//		addGlobals();
//	}
//
//	private void addGlobals() {
//		Tab tab = cp5.getTab("global");
//
//		seedText = new TextField(cp5, "seed");
//		seedText.setPosition(parent.width - 5 - parent.textWidth("8888888888888888"), 1);
//		seedText.setSize((int) parent.textWidth("8888888888888888"), 20);
//		seedText.setInputFilter(ControlP5Base.INTEGER);
//		seedText.setLabelVisible(false);
//		seedText.setAutoClear(false);
//		seedText.keepFocus(true);
//		seedText.moveTo(tab);
//		seedText.addListener(this);
//
//		timeButton = new Button(cp5, "time");
//		timeButton.setCaptionLabel("Set Time");
//		timeButton.setPosition(PVector.sub(seedText.getPosition(), new PVector(82, 0, 0)));
//		timeButton.setSize(80, 20).getCaptionLabel().align(ControlP5Base.CENTER, ControlP5Base.CENTER);
//		timeButton.moveTo(tab);
//		timeButton.addListener(this);
//
//		randomButton = new Button(cp5, "random");
//		randomButton.setCaptionLabel("Set Random");
//		randomButton.setPosition(PVector.sub(timeButton.getPosition(), new PVector(82, 0, 0)));
//		randomButton.setSize(80, 20).getCaptionLabel().align(ControlP5Base.CENTER, ControlP5Base.CENTER);
//		randomButton.moveTo(tab);
//		randomButton.addListener(this);
//
//		// orbitCanvas = new FormStarOrbitCanvas(0, parent.height - 200, 200);
//		// cp5.addCanvas(orbitCanvas);
//		// // orbitCanvas.moveTo(tab);
//	}
//
//	@Override
//	public void controlEvent(ControlEvent event) {
//		switch (event.getName()) {
//		case "time":
//			seedText.setText(Long.toString(System.currentTimeMillis()));
//			break;
//		case "random":
//			seedText.setText(Long.toString(randomSeed.nextLong()));
//			break;
//		case "seed":
//			Long seed = null;
//			try {
//				seed = Long.parseLong(seedText.getText());
//				generateSystem(seed);
//			} catch (NumberFormatException e) {
//				seedText.clear();
//			}
//			break;
//		}
//	}
//
//	private void generateSystem(Long seed) {
//		solarSystem = SystemGen.generate(new Random(seed), false, false);
//
//		Group g1 = cp5.addGroup("g1");
//		g1.disableCollapse();
//		g1.setPosition(100, 100).setBackgroundHeight(100).setBackgroundColor(parent.color(255, 50));
//
//		cp5.addBang("A-1").setPosition(10, 20).setSize(80, 20).setGroup(g1);
//
//		cp5.addBang("A-2").setPosition(50, 20).setSize(80, 20).setGroup(g1);
//
//		Group g2 = cp5.addGroup("g2").setPosition(300, 100).setWidth(300).activateEvent(true)
//				.setBackgroundColor(parent.color(255, 80)).setBackgroundHeight(100).setLabel("Hello World.");
//
//		cp5.addSlider("S-1").setPosition(80, 10).setSize(180, 9).setGroup(g2);
//
//		cp5.addSlider("S-2").setPosition(80, 20).setSize(180, 9).setGroup(g2);
//
//		cp5.addRadioButton("radio").setPosition(10, 10).setSize(20, 9).addItem("black", 0).addItem("red", 1)
//				.addItem("green", 2).addItem("blue", 3).addItem("grey", 4).setGroup(g2);
//
//		// // By default all controllers are stored inside Tab 'default'
//		// // add a second tab with name 'extra'
//		//
//		// cp5.addTab("extra");
//		// cp5.addTab("1");
//		// // .setColorBackground(parent.color(0, 160, 100))
//		// // .setColorActive(parent.color(255, 128, 0));
//		//
//		// // if you want to receive a controlEvent when
//		// // a tab is clicked, use activeEvent(true)
//		//
//		// //cp5.getTab("default").setLabel("my default tab").setId(1);
//		//
//		// cp5.getTab("extra").activateEvent(true).setId(2);
//		//
//		// // create a few controllers
//		//
//		// cp5.addButton("button").setBroadcast(false).setPosition(100, 100).setSize(80, 40).setValue(1)
//		// .setBroadcast(true).getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER);
//		//
//		// cp5.addButton("buttonValue").setBroadcast(false).setPosition(220, 100).setSize(80, 40).setValue(2)
//		// .setBroadcast(true).getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER);
//		//
//		// cp5.addSlider("slider").setBroadcast(false).setRange(100, 200).setValue(128).setPosition(100, 160)
//		// .setSize(200, 20).setBroadcast(true);
//		//
//		// cp5.addSlider("sliderValue").setBroadcast(false).setRange(0, 255).setValue(128).setPosition(100,
//		// 200)
//		// .setSize(200, 20).setBroadcast(true);
//		//
//		// // arrange controller in separate tabs
//		//
//		// cp5.getController("sliderValue").moveTo("extra");
//		// cp5.getController("slider").moveTo("global");
//		// // orbitCanvas.setSystem(solarSystem);
//	}
//}
