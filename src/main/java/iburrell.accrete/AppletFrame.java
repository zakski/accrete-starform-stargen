
package iburrell.gui;

import java.applet.*;
import java.awt.*;
import java.awt.Image;
import java.net.URL;
import java.util.Enumeration;


public class AppletFrame extends ExitableFrame
implements AppletStub, AppletContext
{

    public AppletFrame(Applet applet, int width, int height, String title)
    {
        super(title);

        this.resize(width, height);
        this.add("Center", applet);

        applet.setStub(this);

        applet.init();
        this.show();
        applet.start();
    }

    public AppletFrame(Applet a, int x, int y) {
        this(a, x, y, a.getClass().getName());
    }
    
    // AppletStub methods
    public boolean isActive() { return true; }
    public URL getDocumentBase() { return null; }
    public URL getCodeBase() { return null; }
    public String getParameter(String name) { return ""; }
    public AppletContext getAppletContext() { return this; }
    public void appletResize(int width, int height) {}

    // AppletContext methods
    public AudioClip getAudioClip(URL url) { return null; }
    public Image getImage(URL url) { return null; }
    public Applet getApplet(String name) { return null; }
    public Enumeration getApplets() { return null; }
    public void showDocument(URL url) { }
    public void showDocument(URL url, String target) { }
    public void showStatus(String status) { }

}
