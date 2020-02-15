#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>
#include <time.h>

void signalHandler(int signalNumber)
{
}

char *boszitol(int number)
{
    if (number == 1)
    {
        return "kalács";
    }
    if (number == 0)
    {
        return "sütemény";
    }
    return "Húha hát ezt nem tudom micsoda";
}

int generateNumber(int lower, int upper)
{
    srand(time(0));
    return (rand() % (upper - lower + 1)) + lower;
}

int main()
{
    // Pipe file descriptor
    int jancsiPipe[2];
    int juliskaPipe[2];
    // Open pipe
    pipe(jancsiPipe);
    pipe(juliskaPipe);

    // process ID's
    pid_t jancsi, juliska;

    signal(SIGINT, signalHandler);

    jancsi = fork();
    if (jancsi > 0)
    {
        juliska = fork();
        if (juliska > 0)
        {
            // Fő process
            printf("\n-- A vasorrú bába várja a gyerekeket.\n");
            printf("Vasorrú: Muhahahaha!\n");

            // Várunk, amíg Jancsi kopog
            pause();

            // Írunk Jancsinak a csőbe
            printf("Vasorrú: Szia Jancsi, adok neked valamit\n");
            int toJancsi = generateNumber(0, 1);
            write(jancsiPipe[1], &toJancsi, sizeof(int));

            // Várunk, amíg Juliska kopog
            pause();

            // Írunk Juliskának a csőbe
            printf("Vasorrú: Szia Juliska, adok neked valamit\n");
            int toJuliska = generateNumber(0, 1);
            write(juliskaPipe[1], &toJuliska, sizeof(int));

            // Várunk egy kicsit
            sleep(2);
            printf("\n-- Fogságba esnek a gyerekek\n");
            printf("Vasorrú: MUHHAHAHHAHAHA! fogságba estetek!\n");
            printf("Vasorrú: Juliska, irány dolgozni!\n");

            // Feladatok juliskának
            int feladat1 = 0;
            int feladat2 = 1;
            int feladat3 = 2;
            // Első feladat küldése csövön
            write(juliskaPipe[1], &feladat1, sizeof(int));
            kill(juliska, SIGINT);
            // Várunk míg végez
            pause();
            // Második feladat küldése csövön
            write(juliskaPipe[1], &feladat2, sizeof(int));
            // Várunk míg végez
            pause();
            // Harmadik feladat küldése csövön
            write(juliskaPipe[1], &feladat3, sizeof(int));
            // Várunk míg végez
            pause();

            printf("Itt a vége, fuss el véle!\n\n");
        }
        else
        {
            // Juliska process
            sleep(3);
            printf("Juliska: Juliska vagyok, kipp-kopp\n");
            // Küldünk jelzést a vasorrúnak
            kill(getppid(), SIGINT);
            // Várunk egy kicsit, amíg ad kalácsot vagy süteményt csövön
            sleep(1);
            // Olvassuk ki a csőből mit kaptunk
            int fromBoszi;
            read(juliskaPipe[0], &fromBoszi, sizeof(int));
            // Dekódoljuk, hogy ez micsoda valójában
            char *b = boszitol(fromBoszi);
            printf("Juliska: De jó, %s!\n", b);

            // Várunk amíg a bába nem küldi a feladatokat
            pause();

            // Olvassuk ki a csőből a feladatot
            read(juliskaPipe[0], &fromBoszi, sizeof(int));
            printf("Dolgozási: %i\n", fromBoszi);
            // Szóljunk a vasorrúnak, hogy jöhet a következő
            kill(getppid(), SIGINT);
            sleep(1);
            // Olvassuk ki a csőből a feladatot
            read(juliskaPipe[0], &fromBoszi, sizeof(int));
            printf("Dolgozási: %i\n", fromBoszi);
            // Szóljunk a vasorrúnak, hogy jöhet a következő
            kill(getppid(), SIGINT);
            sleep(1);
            // Olvassuk ki a csőből a feladatot
            read(juliskaPipe[0], &fromBoszi, sizeof(int));
            printf("Dolgozási: %i\n", fromBoszi);
            // Szóljunk a vasorrúnak, hogy kész lettünk
            // kill(getppid(), SIGINT);
        }
    }
    else
    {
        // Jancsi process
        sleep(1);
        printf("Jancsi: Jancsi vagyok, kipp-kopp\n");
        // Küldünk jelzést a vasorrúnak
        kill(getppid(), SIGINT);
        // Várunk egy kicsit, amíg ad kalácsot vagy süteményt csövön
        sleep(1);
        // Olvassuk ki a csőből mit kaptunk
        int fromBoszi;
        read(jancsiPipe[0], &fromBoszi, sizeof(int));
        // Dekódoljuk, hogy ez micsoda valójában
        char *b = boszitol(fromBoszi);
        printf("Jancsi: De jó, %s!\n", b);
        pause();
    }

    return 0;
}