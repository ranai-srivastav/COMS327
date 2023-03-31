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

game: world map priority_queue linked_list game.cpp
	g++ world.o map.o priority_queue.o linked_list.o game.cpp -lncurses -o game


