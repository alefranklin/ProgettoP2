all: clean program.o

program.o: main.o map.o randomizer.o item.o character.o game.o entity.o
	g++ main.o map.o randomizer.o item.o character.o game.o entity.o -o program.o

main.o: main.cpp
	g++ -c main.cpp

map.o: map.cpp
	g++ -c map.cpp

randomizer.o: randomizer.cpp
	g++ -c randomizer.cpp

item.o: item.cpp
	g++ -c item.cpp

character.o: character.cpp
	g++ -c character.cpp

game.o: game.cpp
	g++ -c game.cpp

entity.o: entity.cpp
	g++ -c entity.cpp

clean:
	rm -rf *o