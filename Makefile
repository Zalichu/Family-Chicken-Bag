CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: walk2

walk2: walk2.cpp log.cpp anthonyR.cpp
	g++ $(CFLAGS) walk2.cpp anthonyR.cpp cleoR.cpp denningM.cpp emmanuelC.cpp mohammedB.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -owalk2

clean:
	rm -f walk2
	rm -f *.o

