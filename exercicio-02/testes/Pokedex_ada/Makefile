UTIL = pokemon.c
MAIN = Pokedex.c
BINARY = executavel

all:
	gcc -Wall -c $(UTIL) -o pokemon.o
	gcc -Wall $(MAIN) pokemon.o -o Pokedex

run:
	./Pokedex

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o Pokedex