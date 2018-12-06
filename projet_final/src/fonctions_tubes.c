#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../headers/fonctions_tubes.h"

#define MAX 111
/*---------- Creation de N PIPE ----------- */

void creationPipe(int tube[][2],int n)
{int i;
	for (i=0;i<n;i++)
    pipe(tube[i]);
	
	}
	
/**fonctions fils **/

/*---------- Fermeture des descripteurs non utilisés par le fils----------- */
void closeDescripteurFils(int i, int processNumber,int pipeAnn[][2],int pipePereFils[][2],int pipeFilsPere[2])
{
    //fermeture descripteur anneau entre fils
    close(pipeAnn[i][0]);
   if(i==0){
       close(pipeAnn[processNumber-1][1]);
   }else{
       close(pipeAnn[i-1][1]);
   }
   // fermeture descripteur communication père Fils
   close(pipePereFils[i][1]);
   // fermeture descripteur communication Fils père
   close(pipeFilsPere[0]);
 
}
void closeDescripteurFilsFinal(int i, int processNumber, int pipeAnn[][2], int pipePereFils[][2], int pipeFilsPere[2])
{

    close(pipeAnn[i][1]);
    if (i == 0)
    {
        close(pipeAnn[processNumber - 1][0]);
    }
    else
    {
        close(pipeAnn[i - 1][0]);
    }

    close(pipePereFils[i][0]);

    close(pipeFilsPere[1]);
}

/*-------- Envoi et reception de l'information entre les fils ---------- */

void envoiFilsFils(int val, int i, int pipeAnn[][2])
{
    write(pipeAnn[i][1], &val, sizeof(int));
}

int receptionFilsFils(int i, int processNumber, int pipeAnn[][2])
{
    int val;
    if (i == 0)
    {
        read(pipeAnn[processNumber - 1][0], &val, sizeof(int));
    }
    else
    {
        read(pipeAnn[i - 1][0], &val, sizeof(int));
    }
    return val;
}

/* Fonction qui permet au fils de lire  ce qui est envoyé par le père */
int lectureDuPere(int i ,int pipePereFils[][2])
{
    int val;
    read(pipePereFils[i][0], &val, sizeof(int));
    return val;
}
/*----------  Ecriture du fils au père ----------*/
void ecritureFilsPere(int val, int pipeFilsPere[2])
{
    write(pipeFilsPere[1], &val, sizeof(int));
}

/**fonctions pere **/

/*----------Fermeture des descripteurs non utilisés par père----------- */
void closeDescripteurPere(int processNumber, int pipePereFils[][2], int pipeFilsPere[2])
{
    for (int i = 0; i < processNumber; i++)
    {
        close(pipePereFils[i][0]);
    }
    close(pipeFilsPere[1]);
}
/* Fonction qui permet au père de lire  ce qui est envoyé par le fils */
 int lectureDuFils(int pipeFilsPere[2])
{
    int val;

    read(pipeFilsPere[0], &val, sizeof(int));
    return val;
}
/* Fonction qui permet au père de lire  ce qui est envoyé par le fils */
 void ecriturePereFils(int val ,int i , int pipePereFils[][2])
{
    write(pipePereFils[i][1], &val, sizeof(int));
    
}
