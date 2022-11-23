ITEM = Node/Node.c
MAIN = Main.c
UTIL = Util/Util.c
LISTA = Lista/Lista.c
BINARY = Main
NAME = TAD_bignumbers

all:
	gcc -Wall -g $(ITEM) $(LISTA) $(UTIL) $(MAIN) -L. -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o

objlib:
	gcc -Wall -pedantic -Werror -Wextra -c -fPIC $(UTIL) $(ITEM)

lib:
	ar -rcs lib_util.a *.o