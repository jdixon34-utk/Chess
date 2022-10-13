CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJFILES = src/board.o src/game.o src/main.o src/move.o

all: Chess

Chess: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -O -o Chess $(OBJFILES)

clean:
	$(RM) -f Chess $(OBJFILES)
