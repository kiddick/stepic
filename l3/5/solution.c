/*
Разработать программу solution, которая при запуске себя "демонизирует" и остается в  памяти.
Перед закрытием стандартного потока вывода stdout унаследованного от родителя,
программа должна вывести в него Pid процесса-демона.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        chdir("/");
        setsid();
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        sleep(10);
    }
    else {
        fprintf(stdout, "%d\n", cpid);
        exit(EXIT_SUCCESS);
    }
}
