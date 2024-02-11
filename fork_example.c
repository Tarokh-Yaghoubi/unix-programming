
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXLINE     4096


int
main(void)
{

    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

    printf("%% ");      /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL) {

        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;       // replace new line with null

        if ((pid = fork()) < 0) {
        
            perror("fork error");
        
        } else if (pid == 0) {  // child
       
            execlp(buf, buf, (char *)0);
        
            printf("could not execute: %s\n", buf);
            exit(127);
        
        }

        // parent

        if ((pid = waitpid(pid, &status, 0)) < 0)
            perror("waitpid error");
        
        printf("%% ");

    }

    exit(0);

}


