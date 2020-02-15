#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
// #include <wait.h>

// Üzenet felépítése
struct uzenet
{
    long mtype;
    char mtext[1024];
};

// A riasztásra figyelő változó
int riasztva = 0;

// Üzenet küldése
int kuld(int uzenetsor)
{
    const struct uzenet uz = {1, "Csapat útra kész!"};
    int status;
    status = msgsnd(uzenetsor, &uz, strlen(uz.mtext) + 1, 0);
    if (status < 0)
        perror("msgsnd");
    return 0;
}

// receiving a message.
int fogad(int uzenetsor)
{
    struct uzenet uz;
    int status;
    status = msgrcv(uzenetsor, &uz, 1024, 1, 0);

    if (status < 0)
        perror("msgsnd");
    else
        printf("Üzenet érkezett: %s\n", uz.mtext);
    return 0;
}

void riasztas(int signum)
{
    riasztva = 1;
}

int main(int argc, char *argv[])
{
    pid_t mobilCsapat;
    int fd[2];
    pipe(fd);
    int uzenetsor, status;
    key_t kulcs;

    kulcs = ftok("titkos_mehesz_kulcs", 1);
    uzenetsor = msgget(kulcs, 0600 | IPC_CREAT);
    if (uzenetsor < 0)
    {
        perror("msgget");
        return 1;
    }

    signal(SIGINT, riasztas);

    mobilCsapat = fork();
    if (mobilCsapat > 0)
    {
        // Főméhész process

        // Várunk amíg kitisztul az ég
        printf("Főméhész: Várunk amíg kitisztul az ég...\n");
        sleep(1);

        // Küldjük a jelzést
        kill(mobilCsapat, SIGINT);

        // Megvárjuk, míg visszaérkezik a jelzés
        pause();

        // Fogadjuk az üzenetet
        fogad(uzenetsor);

        // Méhészeti koordináták
        int coords[2] = {1, 2};

        printf("Főméhész:\n--PID:%d\n--csőbe küldjük: X: %i, Y: %i\n", getpid(), coords[0], coords[1]);

        // Beírjuk a csőbe a koordinátákat
        write(fd[1], coords, sizeof(coords));

        // Jelzünk a mobil csapatnak, hogy küldtük, olvashatják
        kill(mobilCsapat, SIGINT);

        // Megvárjuk, míg befejezik a dolgukat
        waitpid(mobilCsapat, &status, 0);
        return 0;
    }
    else if (mobilCsapat == 0)
    {
        // Mobil csapat process

        // Várunk amíg riasztás érkezik
        while (riasztva == 0)
            ;
        printf("Csapat: Riasztás történt\n");

        // Várunk amíg elkészül a csapat
        srand(time(0));
        int r = rand() % 3 + 1;
        printf("Csapat: idő amíg elkészülünk: %i másodperc\n", r);
        sleep(r);
        printf("Csapat: Készen állunk\n");

        // Elküldjük a főméhésznek, hogy készen állunk
        kuld(uzenetsor);

        // Jelzés a méhésznek, hogy elküldtük
        kill(getppid(), SIGINT);

        // Várunk amíg jelez a Főméhész, hogy olvashatunk
        pause();

        // Olvasunk a csőből
        int coords[2];
        read(fd[0], coords, sizeof(coords));

        printf("Csapat:\n--PID:%d\n--csövön érkezett: X: %i, Y: %i\n", getpid(), coords[0], coords[1]);

        exit(0);
    }
    else
    {
        perror("fork error");
        return 1;
    }

    return 0;
}
