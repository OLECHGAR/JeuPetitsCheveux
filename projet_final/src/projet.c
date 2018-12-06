#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../headers/fonctions_tubes.h"
#include "../headers/fonctions_jeu.h"


int main() 
{
 //tableau pour le stockage des pid des fils 
int numFils[N];
int etat_jeu[N][NC];
initialisation(etat_jeu,N,NC);
remplir(numFils,N);
//creation des tubes :

int TJ[N][2];
int TP[N][2];
creationPipe(TJ,N);
creationPipe(TP,N);
int readPere[2];
pipe(readPere);
	
//creation des fils :
	int j;
		int pid[N];
	int controle = 0;
    bool Fa = false;

    affichage_debut();
	
	for( j= 0; j< N; j++ )
	{
		
		switch(pid[j] = fork())
		{
		case -1:
		    /**--------Cas erreur fork----------*/
			fprintf(stderr,"erreur fork()");
			exit(-1);
		case 0:
		    /**--------Cas comportement fils*/
			  while (!Fa)
            {   closeDescripteurFils(j, N,TJ,TP,readPere);
                int numJoueur = lectureDuPere(j,TP);
                controle = jouer(j, NC,N,numJoueur,S, TJ, TP,readPere, etat_jeu);
                ecritureFilsPere(controle, readPere);
                if (controle == 1)
                {
                    Fa = true;
                    closeDescripteurFilsFinal(j, N, TJ, TP, readPere);
                }
            }
             afficher_etat_jeu(etat_jeu,N,NC);
            exit(0);	
			break;
			
	default :
	closeDescripteurPere(j, TP, readPere);

    int CP = 0;
    bool Fin = false;
    int compt = 0;
    while (!Fin)
    {
        ecriturePereFils(numFils[compt],j, TP);
        if (compt == (N - 1))
        {
            compt = 0;
        }
        else
        {
            compt += 1;
        }
        CP = lectureDuFils(readPere);
        if (CP == 1)
            Fin = true;
    }
   
		}
	}	
		
	return 0;
}




