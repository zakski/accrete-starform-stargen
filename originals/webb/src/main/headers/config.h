        /*
         * For machines on which the rand() function returns a long int (32 bits).
         * Suns, for instance:
         */
        #define LONG_RAND
        
        /*
         * For Berkeley-based C compilers.  Many Berkeley-ish machines, such as Suns,
         * HP-UX machines, and Apollos are compatible enough with SYSV that this flag
         * is not needed.  If your machine has '/usr/include/strings.h' rather than
         * 'string.h', you need this defined.
         */
        /*#define BSD*/
        
        
        /*
         * This flags does not work yet:
         */
        /*#define MOONS*/
        
