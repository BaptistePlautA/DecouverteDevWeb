exe: fonctionsBE.o
	@echo "\nCompilation de l'executable\n"
	gcc -Wall main.c fonctionsBE.o -o BE -lm
fonctions.o: fonctions.c fonctions.h
	@echo "\nCompilation des fonctions\n"
	gcc -c fonctionsBE.c -o fonctionsBE.o
all: clean exe #Exécute les sections clean et exe à la suite.
clean:
	@echo "\nTout est effacé\n"
	rm -f *.o
