        # This is a makefile for the Microsoft QuickC version of "starform",
        # a star system and planet generator
        
        # To make a version for debugging or tracing, uncomment this line:
        #CFLAGS = /Zi
        
        # To make a normal optimized version, uncomment this line:
        CFLAGS = /Ox
        
        # To make a codeview-debuggable executable, uncomment this line:
        #LINKFLAGS = /CODEVIEW
        
        # This line should always be uncommented:
        OBJS = accrete.obj enviro.obj display.obj utils.obj
        
        
        accrete.obj: accrete.c const.h structs.h config.h
                qcl /c $(CFLAGS) accrete.c
        
        enviro.obj: enviro.c const.h structs.h config.h
                qcl /c $(CFLAGS) enviro.c
        
        display.obj: display.c const.h structs.h config.h
                qcl /c $(CFLAGS) display.c
        
        utils.obj: utils.c const.h config.h
                qcl /c $(CFLAGS) utils.c config.h
        
        starform.obj: starform.c const.h structs.h config.h
                qcl /c $(CFLAGS) starform.c
        
        starform.exe: starform.obj $(OBJS)
                link $(LINKFLAGS) starform.obj $(OBJS);
        
