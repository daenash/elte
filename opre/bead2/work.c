#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> // for fd()
#include <signal.h>
#include <sys/msg.h>

int isReady = 0;

void handler(int signumber)
{
    if (signumber == SIGINT)
    {
        printf("KFT: Workers are ready\n");
        isReady = 1;
    }
}

int main()
{
    int fd[2];
    pipe(fd);

    int kulcs = ftok("kulcs", 1);
    int uzenetsor = msgget(kulcs, 0600 | IPC_CREAT);

    signal(SIGINT, handler);
    int status;
    pid_t workTeam = fork();

    if (workTeam > 0)
    {
        // Start of parent process
        printf("KFT: Check if workers ready\n");

        // Stop process, so child can send signal
        pause();

        // After signal received check if workers ready
        // And if not, return the function
        if (isReady == 0)
        {
            printf("KFT: Workers are not ready\n");
            exit(EXIT_SUCCESS);
        }

        int date[3] = {2019, 2, 12};

        printf("KFT: Send date through pipe\n");
        close(fd[0]);
        write(fd[1], date, sizeof(date));
        close(fd[1]);

        waitpid(workTeam, &status, 0);

        int type;
        status = msgrcv(uzenetsor, &type, sizeof(int), 0, 0);
        status = msgctl(uzenetsor, IPC_RMID, NULL);

        printf("%i\n", type);

        printf("Parent process ended\n");
    }
    else
    {
        // Start of child process
        printf("Worker Team: Worker team send ready signal\n");

        // Send ready signal (sigint)
        kill(getppid(), SIGINT);

        // Wait for 1 second
        sleep(1);

        int date[3];

        printf("Worker Team: Read data from pipe\n");
        close(fd[1]);
        read(fd[0], date, sizeof(date));
        close(fd[0]);

        printf("%i, %i, %i\n", date[0], date[1], date[2]);

        int type = 1;
        status = msgsnd(uzenetsor, &type, sizeof(int), 0);
    }
    return 0;
}