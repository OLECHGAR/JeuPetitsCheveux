#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#include "../headers/fonctions_jeu.h"
#include "../headers/fonctions_tubes.h"


/* affichache debut et fin de  jeu */
void affichage_debut()
{
    printf("\n............................................................\n");
    printf("\n...................                    .....................\n");
    printf("\n.................. LES PETITS CHEVAUX  .....................\n");
    printf("\n...................                    .....................\n");
    printf("\n............................................................\n");
    printf("\n\n");
}
void affichage_fin()
{
    printf("\n............................................................\n");
    printf("\n...................                    .....................\n");
    printf("\n.................. FIN PARTIE   .....................\n");
    printf("\n...................                    .....................\n");
    printf("\n............................................................\n");
    printf("\n\n");
}
/*initialisation du jeu  */
 void initialisation(int tab[N][NC],int nombreJoueur,int nombreChevaux)
{	int i,j;
	for(i=0 ; i<nombreJoueur ; i++)
	{
		for(j=0 ; j<nombreChevaux ; j++)
          {
	        tab[i][j]=0;}
    }
}	
/*remplir num fils */
void remplir(int *tab, int n)
{ int i ; 
	for (i=0 ; i<n ; i++)
	tab[i]=i;
	
	}
/*afficher_etat_jeu */
	
void afficher_etat_jeu(int tab[N][NC],int nombreJoueur,int nombreChevaux)
{
int i, j ;
printf ( "\n");
for( i =0; i<nombreJoueur ;i++)
{
 for(j=0;j<nombreChevaux;j++)
  {      printf("J[%d]-CV[%d]=%d\t", i,j,tab[i][j]);


  }
     printf ( "\n");

	}
}
/* fonction de()*/
int de()
{   int x;
	srand(time(NULL));
    x=1+rand()%6;
    return  x;
	}	
	
/** mise ajour etat du jeu **/

int enregistrer( int tab[N][NC],int i , int chv , int de ,int nombreJoueur,int nombreChevaux,int succes)
{    int x;
	x=tab[i][chv]+de ;
	if(x>succes)
	{ return 0;
		}
	else if(x==succes)
	{ return 1 ;
		}
	else
	{tab[i][chv]=tab[i][chv]+de;
	return 0;
		}	
	}
	/** numero de cheval qu'on veut deplacer **/
	int num_cheval(int nombreChevaux)
	{   int chv ;
		printf("le numero de cheval que vous souhaitez deplacer (0 , 1 ou 2 ...) :\n");
		label: scanf("%d",&chv);
		if(chv>nombreChevaux)
		{ printf("le numero de cheval que vous souhaitez deplacer ne corespends pas retaper votre numero de cheval  :\n");
		 goto label ;
	     }
		return chv ;
		} 
	/*******Fonction qui permet a chaque joeur de jouer  */
int jouer(int i, int nombreChevaux,int nombreJoueur, int numeroJoueur,int succes, int pipeAnn[][2], int pipePereFils[][2],int pipeFilsPere[2], int etat_jeu[N][NC])
{
    int pas;
    int chv;
    int controle;
     
    if (i==numeroJoueur)
    {
        pas = de();
        chv=num_cheval(nombreChevaux);
        int maj = enregistrer( etat_jeu,i ,chv ,pas , nombreJoueur, nombreChevaux,succes);
        printf("\n                                            ");
        printf("\n joueur %d |cheval %d |valeur dé = %d ", i,chv,pas);
        printf("\n********************************************\n");
        afficher_etat_jeu(etat_jeu,N,NC);
        if(maj == 1) 
        {pas = 0;
			}        
        
        envoiFilsFils(pas, i, pipeAnn);
        envoiFilsFils(chv, i, pipeAnn);
        envoiFilsFils(numeroJoueur, i, pipeAnn);

       int retour;
       retour= receptionFilsFils(i, nombreJoueur, pipeAnn);
        

        if (retour == 0)
        {
            controle = 1;
            printf(" GAGANT : joueur numero %d\n", i);
        }
        else if (retour == 6)
        {
            controle = 2;
        }
        else
        {
            controle = 0;
        }

    }
     else
    {   printf("\n***************** Joueur %d c'est pas mon toure *********************\n" , i);

       // int num = receptionFilsFils(i, nombreJoueur, pipeAnn);
        int jeu = receptionFilsFils(i, nombreJoueur, pipeAnn);
        int num=receptionFilsFils(i, nombreJoueur, pipeAnn);
        int cheval=receptionFilsFils(i, nombreJoueur, pipeAnn);
        
        envoiFilsFils(jeu, i, pipeAnn);
        envoiFilsFils(num, i, pipeAnn);
        envoiFilsFils(cheval, i, pipeAnn);

        
        if (jeu == 0)
        {

            printf(" PERDANT : joueur numero %d\n", i);
        }
       else
        {
         etat_jeu[num][cheval]=etat_jeu[num][cheval]+jeu;
        }
        

    }

    return controle;
}


