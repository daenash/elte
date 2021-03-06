#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char workTypes[][255] = {
    "festo",
    "burkolo-hideg",
    "burkolo-meleg",
    "villanyszerelo",
    "viz-gaz-futesszerelo",
    "konyhabutorkeszito",
    "lakberendezo"};

struct Date
{
    int year;
    int month;
    int day;
};

typedef struct Work
{
    // Munka azonosítója
    int id;

    // Munka típusa
    int type;

    // Munka határideje
    struct Date date;

    // Következő munka
    struct Work *next;

} Work_t;

typedef struct Order
{
    // Rendelés azonosítója
    int id;

    // Megrendelő neve
    char name[255];

    // Megrendelés címe
    char address[255];

    // Ház mérete
    int houseSize;

    // Munkák listája dátumokkal
    struct Work *works;

    // Következő rendelés
    struct Order *next;

} Order_t;

void printTypes()
{
    printf("\n");
    for (int x = 0; x < 7; x++)
    {
        printf("%i = %s\n", x, workTypes[x]);
    }
    printf("\n");
}

void readCommand(char **command)
{
    char commando[255];
    fgets(commando, 255, stdin);
    size_t len = strlen(commando);
    if (len > 0 && commando[len - 1] == '\n')
    {
        commando[--len] = '\0';
    }
    *command = commando;
}

void printOrder(struct Order *orderHead)
{
    printf("Megrendelés azonosítója: %i\n", orderHead->id);
    printf("- név: %s\n", orderHead->name);
    printf("- cím: %s\n", orderHead->address);
    printf("- házméret: %i négyzetméter\n", orderHead->houseSize);
    if (orderHead->works == NULL)
    {
        printf("- Nincs még megrendelt munka...\n");
    }
    else
    {
        printf("- Megrendelt munkák:\n");
        struct Work *workHead = orderHead->works;
        while (workHead != NULL)
        {
            char *type = workTypes[workHead->type];
            int year = workHead->date.year;
            int month = workHead->date.month;
            int day = workHead->date.day;
            printf("---- azonosító: %i, típus: %s, határidő: %i.%i.%i.\n", workHead->id, type, year, month, day);
            workHead = workHead->next;
        }
    }
    printf("\n");
}

// Push Order to the end of the linked list
void pushOrder(struct Order createdOrder, struct Order **orders)
{
    if (*orders == NULL)
    {
        *orders = (struct Order *)malloc(sizeof(Order_t));
        struct Order *actualOrder = *orders;
        *actualOrder = createdOrder;
        actualOrder->id = 1;
    }
    else
    {
        struct Order *actualOrder = *orders;
        while (actualOrder->next != NULL)
        {
            actualOrder = actualOrder->next;
        }
        actualOrder->next = (struct Order *)malloc(sizeof(Order_t));
        *actualOrder->next = createdOrder;
        actualOrder->next->id = actualOrder->id + 1;
    }
}

// Push Work to the end of the linked list
void pushWork(struct Work createdWork, struct Work **works)
{
    if (*works == NULL)
    {
        *works = (struct Work *)malloc(sizeof(Work_t));
        struct Work *actualWork = *works;
        *actualWork = createdWork;
        actualWork->id = 1;
    }
    else
    {
        struct Work *actualWork = *works;
        while (actualWork->next != NULL)
        {
            actualWork = actualWork->next;
        }
        actualWork->next = (struct Work *)malloc(sizeof(Work_t));
        *actualWork->next = createdWork;
        actualWork->next->id = actualWork->id + 1;
    }
}

// Remove work with ID
void removeWork(int id, struct Work **works)
{
    struct Work *head = *works;
    struct Work *actualElem = *works;
    struct Work *prevElem = NULL;

    bool isRemoved = false;

    while (actualElem != NULL && !isRemoved)
    {
        if (actualElem->id == id)
        {
            isRemoved = true;
            if (prevElem != NULL)
            {
                prevElem->next = actualElem->next;
                free(actualElem);
            }
            else
            {
                if (head->next != NULL)
                {
                    struct Work next = *(head->next);
                    free(head->next);
                    *head = next;
                    head->next = next.next;
                }
                else
                {
                    *works = NULL;
                }
            }
        }
        if (!isRemoved)
        {
            prevElem = actualElem;
            actualElem = actualElem->next;
        }
    }
}

void editItem(int id, struct Order **orders)
{

    struct Order *actualElem = *orders;
    bool isFound = false;
    while (actualElem != NULL && !isFound)
    {
        if (actualElem->id == id)
        {
            isFound = true;

            printf("\nA rendelés információi:\n");
            printOrder(actualElem);

            printf("\nSzerkesztési lehetőségek:\n");
            printf("1 -> Megrendelő neve\n");
            printf("2 -> Megrendelő címe\n");
            printf("3 -> Ház mérete\n");
            printf("4 -> Munka hozzáadása\n");
            printf("5 -> Munka törlése\n");

            printf("Parancs: ");
            char *command;
            char *input;
            readCommand(&command);

            if (command[0] == '1')
            {
                printf("Új név: ");
                readCommand(&input);
                strcpy(actualElem->name, input);
            }
            else if (command[0] == '2')
            {
                printf("Új cím: ");
                readCommand(&input);
                strcpy(actualElem->address, input);
            }
            else if (command[0] == '3')
            {
                printf("Új házméret: ");
                readCommand(&input);
                actualElem->houseSize = atoi(input);
            }
            else if (command[0] == '4')
            {
                struct Work createdWork;
                createdWork.next = NULL;
                printf("Új munka:\n");
                printf("-- típusa: ");
                readCommand(&input);
                createdWork.type = atoi(input);
                printf("-- Határidő éve: ");
                readCommand(&input);
                createdWork.date.year = atoi(input);
                printf("-- Határidő hónapja: ");
                readCommand(&input);
                createdWork.date.month = atoi(input);
                printf("-- Határidő napja: ");
                readCommand(&input);
                createdWork.date.day = atoi(input);

                pushWork(createdWork, &actualElem->works);
            }
            else if (command[0] == '5')
            {
                printf("Add meg a törölni kívánt munka azonosítóját: ");
                readCommand(&input);
                removeWork(atoi(input), &actualElem->works);
            }
            printf("\n");
        }

        actualElem = actualElem->next;
    }
}

// Remove element with ID
void removeOrder(int id, struct Order **orders)
{
    struct Order *head = *orders;
    struct Order *actualElem = *orders;
    struct Order *prevElem = NULL;

    bool isRemoved = false;

    while (actualElem != NULL && !isRemoved)
    {
        if (actualElem->id == id)
        {
            isRemoved = true;
            if (prevElem != NULL)
            {
                prevElem->next = actualElem->next;
                free(actualElem);
            }
            else
            {
                if (head->next != NULL)
                {
                    struct Order next = *(head->next);
                    free(head->next);
                    *head = next;
                    head->next = next.next;
                }
                else
                {
                    *orders = NULL;
                }
            }
        }
        if (!isRemoved)
        {
            prevElem = actualElem;
            actualElem = actualElem->next;
        }
    }
}

// Add item with data
void addItem(struct Order **orders)
{
    char *command;
    struct Order createdOrder;
    printf("\nRendelés hozzáadása:\n\n");

    printf("Megrendelő neve: ");
    readCommand(&command);

    strcpy(createdOrder.name, command);

    printf("Megrendelő címe: ");
    readCommand(&command);
    strcpy(createdOrder.address, command);

    printf("Házméret: ");
    readCommand(&command);
    createdOrder.houseSize = atoi(command);

    createdOrder.works = NULL;

    bool workLoop = true;
    int workCounter = 1;

    struct Work createdWork;

    printTypes();

    while (workLoop)
    {
        createdWork.next = NULL;

        printf("%i. munka:\n", workCounter);
        printf("-- típusa: ");
        readCommand(&command);
        createdWork.type = atoi(command);
        printf("-- Határidő éve: ");
        readCommand(&command);
        createdWork.date.year = atoi(command);
        printf("-- Határidő hónapja: ");
        readCommand(&command);
        createdWork.date.month = atoi(command);
        printf("-- Határidő napja: ");
        readCommand(&command);
        createdWork.date.day = atoi(command);

        pushWork(createdWork, &createdOrder.works);

        printf("\nÚj munka hozzáadása? (y/n)\n");
        readCommand(&command);

        if (command[0] == 'n')
        {
            workLoop = false;
        }
        printf("\n");
        workCounter++;
    }

    createdOrder.next = NULL;

    pushOrder(createdOrder, orders);
}

void snippetToWork(struct Work *work, char *buffer)
{
    int type = 0;
    struct Date date;
    char snippet[100];
    int char_pos = 0;

    for (int i = 0; i < strlen(buffer); i = i + 1)
    {
        if (buffer[i] == ',')
        {
            switch (type)
            {
            case 0:
                work->type = atoi(snippet);
                break;
            case 1:
                date.year = atoi(snippet);
                break;
            case 2:
                date.month = atoi(snippet);
                break;
            default:
                break;
            }
            type++;
            // Reset char position
            char_pos = 0;
            // Reset snippet
            memset(snippet, 0, 100);
        }
        else
        {
            snippet[char_pos] = buffer[i];
            char_pos++;
            if (i == strlen(buffer) - 1)
            {
                date.day = atoi(snippet);
                work->date = date;
                memset(snippet, 0, 100);
            }
        }
    }
}

// Sets the order data accordingly:
// 0 –> name
// 1 –> address
// 2 –> houseSize
// >2 -> create a new work and push it to the works linked list
void setOrderData(struct Order *order, char *snippet, int type)
{
    if (type == 0)
    {
        strcpy(order->name, snippet);
    }
    else if (type == 1)
    {
        strcpy(order->address, snippet);
    }
    else if (type == 2)
    {
        order->houseSize = atoi(snippet);
    }
    else if (type > 2)
    {
        struct Work createdWork;
        createdWork.next = NULL;
        snippetToWork(&createdWork, snippet);
        pushWork(createdWork, &(order->works));
    }
}

void readFromFile(struct Order **orders)
{
    FILE *fp;
    char buff[255];
    char *r;

    // The opened file
    fp = fopen("rendelesek.txt", "r");

    // If file is null -> exit
    if (fp == NULL)
    {
        printf("File read error");
        exit(EXIT_FAILURE);
    }

    // Read first line
    r = fgets(buff, 255, fp);

    // If empty -> exit
    if (strlen(buff) == 0)
    {
        printf("Err: File should not be empty!\n");
        return;
    }

    // Read lines
    while (r != NULL)
    {

        // Create the snippet where we store the already read string
        char snippet[255];

        // The actual type of the read string
        int type = 0;

        // The actual character's position in the snippet array
        int char_pos = 0;

        // Initializtaion of the actual order
        struct Order actualOrder;
        actualOrder.works = NULL;
        actualOrder.next = NULL;

        // Read line character by character
        for (int i = 0; i < strlen(buff); i = i + 1)
        {
            // Set the actual character
            char actual = buff[i];

            if (actual == ';')
            {
                // Set actual order data
                setOrderData(&actualOrder, snippet, type);

                // Set the next type
                type++;

                // Reset character position
                char_pos = 0;

                // Reset snippet
                memset(snippet, 0, 255);
            }
            else
            {
                // If not end of line
                if (actual != '\n')
                {
                    // Set the actual character
                    snippet[char_pos] = actual;

                    // Go to next character in snippet
                    char_pos++;
                }

                // If arrived to end of string -> process the last snippet
                if (i == strlen(buff) - 1)
                {
                    // Set actual order data
                    setOrderData(&actualOrder, snippet, type);

                    // Reset snippet
                    memset(snippet, 0, 255);
                }
            }
        }

        // Add actual order to orders list
        pushOrder(actualOrder, orders);

        // Read the next line
        r = fgets(buff, 255, fp);
    }
    // Close the file
    fclose(fp);
}

// Returns true if the command is valid
// Else returns false
bool isValid(char command[100])
{
    if (command[0] == '0' || command[0] == '1' || command[0] == '2' || command[0] == '3' || command[0] == '4')
    {
        return true;
    }
    return false;
}

// List the orders
void listOrders(struct Order **orders)
{
    struct Order *orderHead = *orders;

    if (orderHead == NULL)
    {
        printf("\nNincs még felvett rendelés\n\n");
        return;
    }

    printf("\nMegrendelések listája:\n\n");

    // Iterate while the head is not null
    while (orderHead != NULL)
    {
        printOrder(orderHead);
        orderHead = orderHead->next;
    }
}

void writeToFile(struct Order **orders)
{
    FILE *fp;
    char buff[255];
    char *r;

    // The opened file
    fp = fopen("rendelesek.txt", "w");

    // If file is null -> exit
    if (fp == NULL)
    {
        printf("File read error");
        exit(EXIT_FAILURE);
    }

    struct Order *actualOrder = *orders;
    bool isLast = false;

    while (actualOrder != NULL)
    {
        if (actualOrder->next == NULL)
        {
            isLast = true;
        }

        fputs(actualOrder->name, fp);
        fputs(";", fp);
        fputs(actualOrder->address, fp);
        fputs(";", fp);
        fprintf(fp, "%d", actualOrder->houseSize);

        if (actualOrder->works != NULL)
        {
            fputs(";", fp);

            struct Work *actualWork = actualOrder->works;
            bool isLastWork = false;

            while (actualWork != NULL)
            {
                fprintf(fp, "%d", actualWork->type);
                fputs(",", fp);
                fprintf(fp, "%d", actualWork->date.year);
                fputs(",", fp);
                fprintf(fp, "%d", actualWork->date.month);
                fputs(",", fp);
                fprintf(fp, "%d", actualWork->date.day);

                if (actualWork->next == NULL)
                {
                    isLastWork = true;
                }

                if (!isLastWork)
                {
                    fputs(";", fp);
                }

                actualWork = actualWork->next;
            }
        }

        if (!isLast)
        {
            fputs("\n", fp);
        }
        actualOrder = actualOrder->next;
    }

    fclose(fp);
}

// Examine the command and execute accordingly
void executeCommand(char command, bool *isQuit, struct Order **orders)
{
    char input[100];
    int id;
    switch (command)
    {
    case '0':
        *isQuit = true;
        writeToFile(orders);
        break;
    case '1':
        listOrders(orders);
        break;
    case '2':
        addItem(orders);
        break;
    case '3':
        printf("Szerkeszteni kívánt rendelés azonosítója: ");
        fgets(input, 100, stdin);
        id = atoi(input);
        if (id > 0)
        {
            editItem(id, orders);
        }
        break;
    case '4':
        printf("Törölni kívánt rendelés azonosítója: ");
        fgets(input, 100, stdin);
        id = atoi(input);
        if (id > 0)
        {
            removeOrder(id, orders);
        }
        break;
    default:
        break;
    }
}

struct Order *orders;

int main()
{
    readFromFile(&orders);

    printf("\nÜdv a \"Varázs-Lak Kft\" rendeléskezelő szoftverében.\n");
    printf("\n");
    printf("A kiadható parancsok:\n");
    printf("1 -> Rendelések listázása\n");
    printf("2 -> Új rendelés\n");
    printf("3 -> Rendelés módosítása\n");
    printf("4 -> Rendelés törlése\n");
    printf("0 -> Kilépés\n");
    printf("\n");
    bool isQuit = false;
    while (!isQuit)
    {
        char command[100];
        printf("Parancs: ");
        fgets(command, 100, stdin);
        if (isValid(command))
        {
            executeCommand(command[0], &isQuit, &orders);
        }
        else
        {
            printf("Not valid command\n");
        }
    }
    return 0;
}
