#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 #include <sys/types.h>
#include <sys/wait.h>

#define N 5
#define MAX 554
#define A 4

int main() 
{
int i,j;
 
int jeu=1;
char tmp[MAX];
char m[MAX]="c'est ton tour ";
char n[MAX]="j'ai joue";

int numFils[N];
//creation des tubes :

int TJ[N][2];
int TP[N][2];
int readPere[2];
pipe(readPere);
for (i=0;i<N;i++)
{ pipe(TJ[i]);
	}
	for (i=0;i<N;i++)
{ pipe(TP[i]);
	}
	
//creation des fils :
	for( j= 0; j < N; j++ )
	{
		
		switch(numFils[j]=fork())
		{
		case 0:
				if(j==0)
			  {  
				  close(TJ[j][0]);
				  close(TJ[N-1][1]); 
				  close(TP[i][1]);
                  close(readPere[0]);
				 read(TP[0][0],tmp,MAX);
				 printf("message du fils ,j'ai recu ton message pere : %s\n",tmp );
				 write(readPere[1],n,strlen(n)+1);
				 jeu ++ ;
				 write(TJ[j][1],&jeu,sizeof(jeu));
                 read(TJ[N-1][0],&jeu,sizeof(jeu));
                 printf("%d : %s \n",j,tmp);
                 
                 if(jeu==A)
                 {	  	
			 printf ("************************** joueur %d: j'ai gange *************\n", getpid()) ;
					  			   //fermeture final des tubes
    
                close(TJ[0][1]);
                 close(TJ[N - 1][0]);
                 close(TP[i][0]);
                 
                 close(readPere[1]);
                 
		        for(int i=1 ; i<N ;i++)
		        {
				 close(TJ[i][1]);
                 close(TJ[i - 1][0]);
                 close(TP[i][0]);
                 }

					 }
					 }
                 
			   
			  else 
			  {
				  close(TJ[j][0]);
                 close(TJ[i-1][1]);
				  close(TP[i][1]);
                  close(readPere[0]);
                                        

			  read(TP[j][0],tmp,MAX);
			  printf("message du %s\n",tmp );
			  write(readPere[1],n,strlen(n)+1);
			  read(TJ[j-1][0],&jeu,sizeof(jeu));
              printf("%d : %s \n",j,tmp);
              jeu ++ ;
              write(TJ[j][1],&jeu,sizeof(jeu));
              if(jeu==A)
                 {	  	
			   printf ("************************** joueur %d: j'ai gange **************************\n", getpid()) ;
			   //fermeture final des tubes
			     close(TJ[0][1]);
                 close(TJ[N - 1][0]);
                 close(TP[i][0]);
                 
                 close(readPere[1]);
                 
		        for(int i=1 ; i<N ;i++)
		        {
				 close(TJ[i][1]);
                 close(TJ[i - 1][0]);
                 close(TP[i][0]);
                 }

					 }
                 
			  }
			
			return 0 ;	
			break;
		case -1:
			fprintf(stderr,"erreur fork()");
			break;
		default : 
      printf ("** pere %d: a cree processus %d **\n ", getpid(),numFils[j]) ;
      				 write(TP[j][1],m,strlen(m)+1);
         			  read(readPere[0],tmp,MAX);
         			  printf("Pere j'ai recu ton message : %s\n",tmp);
         
		}
		}
		
	return 0;
}




