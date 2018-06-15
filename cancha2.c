#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>


int main()
{
    int pidA[5];   //fork pid de TeamA //No estoy seguro si asi funciona
    int pidB[5];   //fork pid de TeamB //No estoy seguro si asi funciona
    pid_t pid;
    int *ball;      //variable compartida para balon
    int *canchaA;   //variable compartida para canchaA
    int *canchaB;   //variable compartida para canchaB
    int i;		//variable de loop
    unsigned int n = 5; //contador de fork
    sem_t *sem;    //syncroniza el semaforo
    unsigned int value; //valor del semaforo
    //int n=10;
    //pid_t p2id;
    //pid = fork();


    ball = (int *) shmat (shmid, NULL, 0);  //junta ball con una memoria compartida
    *ball = 0;

    canchaA = (int *) shmat (shmid, NULL, 0);  
    *canchaA = 0; 

    canchaB = (int *) shmat (shmid, NULL, 0);  
    *canchaB = 0;


    //Inicializar el semaforo
    sem = sem_open ("pBall", O_CREAT | O_EXCL, 0644, value);   //Semaforo para tomar ball
    sem = sem_open ("pGolCanchaA", O_CREAT | O_EXCL, 0644, value); //Semaforo de gol canchaA
    sem = sem_open ("pGOlCanchaB", O_CREAT | O_EXCL, 0644, value); //Semaforo de gol canchaB



        for (i = 0; i < n; ++i) {
          pidA[i] = fork();
	  if (pidA[i] == 0) {
	    printf("Soy el proceso hijoA! \n");
            printf("Proceso HijoA pid=%d! , ppid=%d \n", getpid(), getppid());
            sleep(1);
            //printf("Listo \n");
	  } 
          else if (pidA[i] > 0) {
	        printf("Soy el proceso padre! \n");
        	printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        	//printf("Proceso PAdre pid=%d! \n", getpid());   
        	waitpid(pidA[i], NULL, 0);//espera el ultimo hijo  
	  }
             
	      if (pidB[i] == 0){
                printf("Soy el proceso hijoB! \n");
                printf("Proceso HijoB pid=%d! , ppid=%d \n", getpid(), getppid());
                sleep(1);
                //printf("Listo \n");
	      }
              else if (pidB > 0){
              	printf("Soy el proceso padre! \n");
        	printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        	//printf("Proceso PAdre pid=%d! \n", getpid());   
        	waitpid(pidB[i], NULL, 0);//espera el ultimo hijo
              }
              else{
              	printf("fork failed\n");
                exit(1);
              }
           }
           else{
             printf("fork failed\n");
    	     exit(1);
           }
    }
    printf("Jugadores listos \n");
    return 0; 
}
   
////////////////////////////////////////////////////////////////////////////////////////

/*
    for (i = 0; i < n; ++i) {
          pids[i] = fork();
	  if (pids[i] < 0) {
	    fprintf(stderr, "Fork Failed"); //manda en el standard error que fallo
            return 1;
	  } 
          else if (pids[i] == 0) {
	    printf("Soy el proceso hijo! \n");
            printf("Proceso Hijo pid=%d! , ppid=%d \n", getpid(), getppid());
            sleep(1);
            //printf("Listo \n");
            exit(0);
	  }
          else {
          	printf("Soy el proceso padre! \n");
        	printf("Proceso Padre pid=%d! , ppid=%d \n", getpid(), getppid());
        	//printf("Proceso PAdre pid=%d! \n", getpid());   
        	waitpid(pids[i], NULL, 0);//espera el ultimo hijo  
       		 
          }
	        
    }

    printf("Jugadores listos \n");
    return 0; 
}
*/


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
