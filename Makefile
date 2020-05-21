CC=g++
CFLAGS=--std=c++17
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=src/main.cpp src/map.cpp src/player.cpp src/enemy.cpp
PROG=ratslayer

make:
	$(CC) $(SOURCES) $(LFLAGS) $(CFLAGS) -ggdb -o $(PROG)

clean:
	rm $(PROG)
