exe: PROJET.o
	@echo "\nCompilation de l'executable\n"
	gcc main.c PROJET.o -o img
	@echo "\nRend le fichier exécutable\n"
	chmod u+x img

PROJET.o: RecupDonnees.c PROJET.h
	@echo "\nCompilation des fonctions\n"
	gcc -c RecupDonnees.c -o PROJET.o

all: clean

clean:
	@echo "\nTout est effacé\n"
	rm -f *.o

