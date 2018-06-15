#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int total = 0;

void DoWorkChild(){
	total += 10;
}


int main()
{
    int pids[10]; 
    pid_t pid;
    int i;
    int Ball;
    int A;
    int B;
    unsigned int n = 10; 
    //int n=10;
    //pid_t p2id;
    

    //pid = fork();
    //p2id = fork();
    
    p = 0;

    for (i = 0; i < n; ++i) {
          pids[i] = fork();
	  if (pids[i] < 0) {
	    fprintf(stderr, "Fork Failed"); //manda en el standard error que fallo

            return 1;
	  } 



          else if (pids[i] == 0) {
	    //printf("Soy el proceso hijo! \n");
            int nRandomNumber = rand()%((20+1)-5) + 5;
            DoWorkChild();
            printf("Proceso Hijo pid=%d! , ppid=%d \n", getpid(), getppid());
            sleep(1);
            //printf("Listo \n");
            if(i%2){
            	printf("El jugador del equipoA(%d) \n",i);
            	//B += 1;    
            }
            else{
            	printf("El jugador del equipoB(%d) \n",i);
            	//A += 1;
            }
            printf ("El jugador (%d) intenta obtener la bola.\n",i);
            printf("El jugador tardara %d segundos buscando el balon\n",nRandomNumber);
            
            sleep(nRandomNumber);
	    
            exit(0);
	  }
          else {
          	printf("Soy el proceso padre! \n");
        	printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        	//printf("Proceso PAdre pid=%d! \n", getpid());   
        

        	waitpid(pids[i], NULL, 0);//espera el ultimo hijo  
  
       		printf("Child Complete \n"); 
          }
       //return 0;   
    }
     
}

/*
    if (pid != 0){
    	printf("Soy el proceso padre! \n");
        printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        //printf("Proceso PAdre pid=%d! \n", getpid());   
        

        waitpid(pid, NULL, 0);//espera el ultimo hijo  
  
        printf("Child Complete \n");   
    }
    

    if( pid < 0 ){ //revisa si es negativo
        fprintf(stderr, "Fork Failed"); //manda en el standard error que fallo
        return 1;

    }
    else if( pid == 0 ){ //Es el proceso hijo

        //execlp("/bin/ls", "ls", NULL);

          printf("Soy el proceso hijo! \n");
          //printf("Proceso Hijo pid=%d! \n", getpid());
           printf("Proceso Hijo pid=%d! , ppid=%d \n", getpid(), getppid());


           sleep(1);
           printf("Listo \n");              
    }
    else{ //Mayor que 0. Es el proceso padre.

	  printf("Soy el proceso padre! \n");
          printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        //printf("Proceso PAdre pid=%d! \n", getpid());   
        

        waitpid(pid, NULL, 0);//espera el ultimo hijo  

          
        //wait(NULL);//el proceso padre espera que el hijo termina para continuar
          //wait siempre espera por el ultimo hijo creado

        printf("Child Complete \n");
    }
    return 0;

}    
*/
