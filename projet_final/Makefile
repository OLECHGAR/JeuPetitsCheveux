	CC=gcc -Wall -c

projet : projet.o fonctions_tubes.o fonctions_jeu.o
	gcc -o ./bin/projet projet.o fonctions_tubes.o fonctions_jeu.o 
	
fonctions_tubes.o : ./src/fonctions_tubes.c ./headers/fonctions_tubes.h
	$(CC) ./src/fonctions_tubes.c
	
fonctions_jeu.o : ./src/fonctions_jeu.c ./headers/fonctions_jeu.h
	$(CC) ./src/fonctions_jeu.c	
	
projet.o : ./src/projet.c ./headers/fonctions_tubes.h ./headers/fonctions_jeu.h
	$(CC) ./src/projet.c

clean :
	rm -f *.o projet
