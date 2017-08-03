
// Author: Ian Burrell  <iburrell@leland.stanford.edu>
// Created: 1997/02/09
// Modified: 

// Copyright 1997 Ian Burrell

package iburrell.accrete;

import java.io.*;

/**
 *
 * Stores the data for a band of dust of gas.  Contains the inner and
 * outer edge, and whether it has dust or gas present.  Has a pointer
 * to maintain the list of bands.
 *
 * The list of DustBands is maintained by the Accrete class; the
 * internals are exposed for manipulation.
 *
 */
class DustBand
{
    
    double inner;       // inner edge (in AU)
    double outer;       // outer edge (in AU)
    boolean dust;       // dust present
    boolean gas;        // gas present
    DustBand next;

    DustBand(double inner_limit, double outer_limit) {
        this(inner_limit, outer_limit, true, true);
    }
    DustBand(double inner_limit, double outer_limit,
             boolean dust_present, boolean gas_present) {
        inner = inner_limit;
        outer = outer_limit;
        dust = dust_present;
        gas = gas_present;
        next = null;
    }

    void Print(PrintStream out) {
        out.println(inner + " " + outer + " " + dust + " " + gas);
    }
    
}


