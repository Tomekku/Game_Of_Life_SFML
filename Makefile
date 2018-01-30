LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:
	g++ src/*.cpp -o bin/Game_Of_life $(LIBS) -std=c++11 -g -w
