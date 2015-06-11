CXX=g++
CXXFLAGS=
LFLAGS=-lncurses
OBJS = sockets.o utils.o rumba.o ncurses-readstring-example.o ncurses-readstring.o ncurses-menu.o ncurses-menu-example.o rumba.o
all: mainRUMBA

mainRUMBA: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LFLAGS)

clean:
	rm -f *.o mainRUMBA

.PHONY: all clean
