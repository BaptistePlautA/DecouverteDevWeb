exe: fonctions.o
	@echo "\nCompilation de l'executable\n"
	gcc -Wall main.c fonctions.o -o projet
	@echo "\nRend le fichier exécutable\n"
	chmod +x projet CYMeteo.sh AffichageExclu.sh

fonctions.o: fonctions.c fonctions.h
	@echo "\nCompilation des fonctions\n"
	gcc -c fonctions.c -o fonctions.o

all: clean exe #Exécute les sections clean et exe à la suite.

clean:
	@echo "\nTout est effacé\n"
	rm -f *.o
