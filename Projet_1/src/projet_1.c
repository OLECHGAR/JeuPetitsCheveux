#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 #include <sys/types.h>
#include <sys/wait.h>

#define N 5
#define MAX 554

int main() 
{
int i,j;	
char * x= "abc";    
char tmp[MAX];
//creation des tubes :

int TJ[N][2];

for (i=0;i<N;i++)
{ pipe(TJ[i]);
	}
	
//creation des fils :
	pid_t pid;
	for( j= 0; j < N; j++ )
	{
		pid=fork();
		switch(pid)
		{
		case 0:
				if(j==0)
			  {   
				  write(TJ[j][1],x,strlen(x)+1);
                 read(TJ[N-1][0],tmp,MAX);
                 printf("%d : %s \n",j,tmp);
			   }
			  else 
			  {
			  read(TJ[j-1][0],tmp,MAX);
              printf("%d : %s \n",j,tmp);
              write(TJ[j][1],tmp,strlen(tmp)+1);
			  }
			
			return 0 ;	
			break;
		case -1:
			fprintf(stderr,"erreur fork()");
			break;
                
		}
	}	
	return 0;
}



