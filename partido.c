// gcc LabOperativosV3.c -o LabOperativosV3 -pthread
// ./LabOperativosV3

#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */


int main (int argc, char **argv){
    int i;                        /*      loop variables          */
    key_t shmkey;                 /*      THE PORTERS LODGE      */
    int shmid;                    /*      shared memory id        */
    sem_t sem;                   /*      synch semaphore         */ /*shared */
    pid_t pid;                    /*      fork pid                */
    int p;                       //      shared variable THE BALL        *//*shared */
    unsigned int n = 10;               /*      SOCCER PLAYERS            */
    unsigned int value = 2;           /*      semaphore value         */
    int A = 0;
    int B = 0;
    /* initialize a shared variable in shared memory */
    shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    //p = (int ) shmat (shmid, NULL, 0);   / attach p to shared memory */
    p = 0;
    //printf ("p=%d is allocated in shared memory.\n\n", &p);
    printf ("shmkey for p = %d\n", shmkey);
    /*******


    /* initialize semaphores for shared processes */
    sem = *sem_open ("pSem", O_CREAT | O_EXCL, 0644, value); 
    /* name of semaphore is "pSem", semaphore is reached using this name */
    sem_unlink ("pSem");      
    /* unlink prevents the semaphore existing forever */
    /* if a crash occurs during the execution         */
    printf ("semaphores initialized.\n\n");


    /* fork child processes */
    for (i = 0; i < n; i++){
        pid = fork ();
        if (pid < 0)              /* check for error      */
            printf ("Fork error.\n");
        else if (pid == 0)
            break;                  /* child processes */
    }


    /******/
    /**   PARENT PROCESS   **/
    /******/
    if (pid != 0){
        /* wait for all children to exit */
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }

        printf ("\nTodos los hijos han finalizado.\n");

        /* shared memory detach */
        //shmdt (p);
        shmctl (shmid, IPC_RMID, 0);

        /* cleanup semaphores */
        //printf("sem_destroy return value:%d\n",sem_destroy (&sem));
        exit (0);
    }

   // /-------------------------------- CHILD PROCESS ---------------------------------/
    
    else{
        sem_wait (&sem);           /* P operation */
        printf ("El jugador (%d) intenta obtener la bola.\n",i);  
	srand(time(NULL));
	int nRandomNumber = rand()%((20+1)-5) + 5;
	printf("El jugador tardara %d segundos buscando el balon\n",nRandomNumber);
        sleep (nRandomNumber);
        p += 1;              /* Play with the ball */
        if(i%2){
            printf("El jugador (%d) del equipo A obtiene la bola y busca la cancha B\n",i);
            B += 1;
            
        }
        else{
            printf("El jugador (%d) del equipo B obtiene la bola y busca la cancha A\n",i);
            A += 1;
        }
        //printf ("  Child(%d) new value of *p=%d.\n", i, *p);
        printf("ID proceso hijo: %d\n", getpid());
        printf("ID proceso padre: %d\n", getppid());
        sem_post (&sem);           /* Libera valores */
        exit (0);
    }
}
