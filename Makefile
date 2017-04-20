SHELL = /bin/sh
FLAGS = -Wall
CC = g++

all:	TwoPipesTwoChildren TwoPipesThreeChildren

TwoPipesTwoChildren:     TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

TwoPipesThreeChildren:	TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp

clean:
	rm TwoPipesTwoChildren TwoPipesThreeChildren
