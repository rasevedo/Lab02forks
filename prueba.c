#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    //pid_t p2id;
    

    pid = fork();
    //p2id = fork();
    

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
