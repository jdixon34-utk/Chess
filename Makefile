CXX = g++
CXXFLAGS = -std=c++11 -Wall -O
OBJFILES = src/board.o src/game.o src/main.o src/move.o src/search.o

all: Chess

Chess: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o Chess $(OBJFILES)

clean:
	$(RM) -f Chess $(OBJFILES)
