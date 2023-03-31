all: game

clean:
	rm *.o*
	rm game

world: world.cpp
	g++ -Wall -Werror -g world.cpp -c

map: map.cpp
	g++ -Wall -Werror -g map.cpp -c

priority_queue: priority_queue.cpp
	g++ -Wall -Werror -g priority_queue.cpp -c

linked_list: linked_list.cpp
	g++ -Wall -Werror -g linked_list.cpp -c

FileIO: FileIO.cpp
	g++ -Wall -Werror -g FileIO.cpp -c

IO_pokemon: IO_pokemon.cpp
	g++ -Wall -Werror -g IO_pokemon.cpp -c

IO_moves: IO_moves.cpp
	g++ -Wall -Werror -g IO_moves.cpp -c

IO_pokemon_moves: IO_pokemon_moves.cpp
	g++ -Wall -Werror -g IO_pokemon_moves.cpp -c

pokemon: pokemon.cpp
	g++ -Wall -Werror -g pokemon.cpp -c

game: world map priority_queue linked_list IO_pokemon IO_moves IO_pokemon_moves pokemon game.cpp
	g++ world.o map.o priority_queue.o linked_list.o IO_pokemon.o IO_moves.o IO_pokemon_moves.o pokemon.o IO_miscl.cpp game.cpp -lncurses -g -o game


