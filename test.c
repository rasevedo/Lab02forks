#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
 
//int total = 0;

/* 
void DoWorkInChild()
{
	total += 10;
	printf("%d\n",100294/23);	
}
 
*/
int main() {
	int pids[10];
	int i;
	unsigned int n = 10;
	for (i = 0; i < n; ++i) {
	  if ((pids[i] = fork()) < 0) {
	    perror("fork");
	    abort();
	  } else if (pids[i] == 0) {
	    //DoWorkInChild();
	    exit(0);
	  }
	}
 
	/* Wait for children to exit. */
	int status;
	pid_t pid;
	while (n > 0) {
	  pid = wait(&status);
	   printf("Proceso HijoB pid=%d! , ppid=%d \n", getpid(), getppid(), status);
	}
	//printf("%d\n", total);
 
	return 0;
}
