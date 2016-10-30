all:
	gcc -c Player.c
	gcc -c Game.c
	gcc -c rpg.c
	gcc Player.o Game.o rpg.o -o rpg
clean:
	rm *.o rpg