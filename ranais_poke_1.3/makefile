all: game

clean:
	rm *.o*
#	rm *.h.gch
	rm game

world.o: world.c
	gcc -Wall -Werror -g world.c -c

map.o: map.c
	gcc -Wall -Werror -g map.c -c

priority_queue.o: priority_queue.c
	gcc -Wall -Werror -g priority_queue.c -c

game: world.o map.o priority_queue.o
	gcc world.o map.o priority_queue.o game.c -o game


