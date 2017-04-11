
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1996/12/09
// Modified: 1996/12/09

// Copyright 1996 Ian Burrell

package iburrell.accrete.gui;

import java.awt.*;

public class ExitableFrame extends Frame
{

    public ExitableFrame() {
        super();
    }

    public ExitableFrame(String t) {
        super(t);
    }

    public boolean handleEvent(Event e) {
        if (e.id == Event.WINDOW_DESTROY)
            System.exit(0);
        return super.handleEvent(e);
    }

}

