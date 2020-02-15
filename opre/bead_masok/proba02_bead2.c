#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>


struct user {
    char name[50];
    char email[50];
    char phoneNum[50];
    char line[20];
    int people;
    char date[50];
};

struct applicant {
    char name[50];
    int fee;
    char line[20];
};

int counter;
struct user userp[20];

void readFile() {
    FILE *fp;
    fp = fopen("data.bin", "rb");
    if(!fp){
	    printf("nem jo a fajl");
	    exit(1);
    }

    fread(&counter, sizeof (int), sizeof (int), fp);
    fread(userp, sizeof (struct user), sizeof (struct user)*counter, fp);
   
    fclose(fp);
//size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
    
}

void writeFile() {
    FILE *fp;

    fp = fopen("data.bin", "wb");
    if(!fp){
	    printf("nem jo a fajl");
	    exit(1);
    }
   // fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
    fwrite(&counter, sizeof (int), sizeof (int), fp);
    fwrite(userp, sizeof (struct user), sizeof (struct user)*counter, fp);
    fclose(fp); 
}


void newUser(){
    char buffer[256];
    printf("\n Add meg a neved!\n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256); //ssize_t read(int fildes, void *buf, size_t nbytes);
    strcpy(userp[counter].name, buffer);
    //memset(&buffer[0], 0, sizeof(buffer));

    printf("\n Add meg az e-mail cimed!\n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256); 
    strcpy(userp[counter].email, buffer);

    printf("\n Add meg a telefonszamod!\n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256); 
    strcpy(userp[counter].phoneNum, buffer);

    int boolean = 0;
    do{
        printf("\n Add meg melyik turara szeretnel menni (1:Parlament, 2:Hosok tere ,3:Var)\n");
        memset(&buffer[0], 0, sizeof(buffer));
        read(1, buffer, 256); 
        if(1 == atoi(buffer)){
            strcpy(userp[counter].line, "Parlament");
            boolean = 1;
        }else if(2 == atoi(buffer)){
            strcpy(userp[counter].line, "Hosok tere");
            boolean = 1;
        }else if(3 == atoi(buffer)){
            strcpy(userp[counter].line, "Var");
            boolean = 1;
        }else{
            printf("Rossz utvonalat adott meg!");
        }
    }while(boolean == 0);

    printf("\n Hany resztvevot szeretnel regisztralni?\n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    userp[counter].people = atoi(buffer);    

    char* c_time_string;
    time_t current_time;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    strcpy(userp[counter].date, c_time_string);

    printf("\n Sikeres regisztralas! \n\n");
    counter++;
    writeFile();
}

void editUser(){
    char buffer[256];
    printf("\n Add meg a modositani kivant ember e-mail cimet! \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    int num = -1;
    int i;
    for (i = 0; i < counter; i++) {
        if(strcmp(userp[i].email,buffer) == 0){
            num = i;
            break;
        }
    }
    if (num == -1) {
        printf("Nincs ilyen e-mail cim!\n");
        exit(1);
    }

    printf("\n Szeretned modositani a nevet? (1-igen,0-nem) \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    if(1 == atoi(buffer)){
        printf("\n Add meg a modositott nevet!\n");
        memset(&buffer[0], 0, sizeof(buffer));
        read(1, buffer, 256);
        strcpy(userp[num].name, buffer);
    }
    printf("\n Szeretned modositani az e-mailt? (1-igen,0-nem) \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    if(1 == atoi(buffer)){
        printf("\n Add meg a modositott e-mailt!\n");
        memset(&buffer[0], 0, sizeof(buffer));
        read(1, buffer, 256);
        strcpy(userp[num].email, buffer);
    }

    printf("\n Szeretned modositani a telefonszamot? (1-igen,0-nem) \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    if(1 == atoi(buffer)){
        printf("\n Add meg a modositott telefonszamot!\n");
        memset(&buffer[0], 0, sizeof(buffer));
        read(1, buffer, 256);
        strcpy(userp[num].phoneNum, buffer);
    }
    printf("\n Szeretned modositani a hozott emberek szamat? (1-igen,0-nem) \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    if(1 == atoi(buffer)){
        printf("\n Add meg az emberek szamat!\n");
        memset(&buffer[0], 0, sizeof(buffer));
        read(1, buffer, 256);
        userp[num].people = atoi(buffer);
    }
    writeFile();
}

void deleteUser(){
    char buffer[256];
    printf("\n Add meg a torolni kivant ember e-mail cimet! \n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    int num = -1;
    int i;
    for (i = 0; i < counter; i++) {
        if(strcmp(userp[i].email,buffer) == 0){
            num = i;
            break;
        }
    }
    if (num == -1) {
        printf("Nincs ilyen e-mail cim!\n");
        exit(1);
    }
    printf("\n Biztosan torolni szeretned a(az) %s nevu szemelyt? (1-igen, 0-nem)\n",userp[num].name);
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    if(1 == atoi(buffer)){
        for ( i = num ; i < counter - 1 ; i++ ){
            userp[i] = userp[i+1];
        }        
    }
    counter--;
    printf("\nTorolve \n");
    writeFile();
}


void listUsers(){
    printf("\n Jelentkezettek listaja: \n");
    int i;
    for (i = 0; i < counter; i++) {
        printf("Neve: %s email cime: %s telefonszama: %s utvonal: %s hozott emberek szama: %d regisztracio datuma: %s\n\n", userp[i].name, userp[i].email, userp[i].phoneNum, userp[i].line, userp[i].people, userp[i].date);
    }
}


void listLineUsers(){
    char buffer[256];
    printf("\n Add meg melyik turarol szeretned listazni az embereket (1:Parlament, 2:Hosok tere ,3:Var)\n");
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    char name[50];
    int boolean = 0;
    int i;
    if(1 == atoi(buffer)){
        strcpy(name, "Parlament");
        boolean = 1;
    }else if(2 == atoi(buffer)){
        strcpy(name, "Hosok tere");
        boolean = 1;
    }else if(3 == atoi(buffer)){
        strcpy(name, "Var");
        boolean = 1;
    }else{
        printf("Rossz utvonalat adott meg!");
    }
    if(boolean == 1){
        for(i = 0; i < counter ; i++ ){
            if(strcmp(userp[i].line,name) == 0){
                printf("Neve: %s email cime: %s telefonszama: %s utvonal: %s hozott emberek szama: %d regisztracio datuma: %s\n\n", userp[i].name, userp[i].email, userp[i].phoneNum, userp[i].line, userp[i].people, userp[i].date);   
            }
        }
    }
}

void menuPrint(){
    printf("Mit szeretne csinalni?\n 1-Új jelentkezo \n 2-Jelentkezo modositasa \n 3-Jelentkezo torlese\n 4-Jelentkezok listazasa \n 5-Utvonalra jelentkezok listazasa \n 6-Túra indítása \n 0-Kilepes \n");
    
}

void handler(int signumber){
  printf("Varom az adatokat\n");
} 

void executeEvent() {
    int i;
    int applic = 0;
    printf("Add meg melyik turara szeretnel menni (1:Parlament, 2:Hosok tere ,3:Var)\n");    
    char buffer[256];
    memset(&buffer[0], 0, sizeof(buffer));
    read(1, buffer, 256);
    char lineUs[256];
    memset(&lineUs[0], 0, sizeof(lineUs));
    for (i = 0; i < counter; i++) {
        if(1 == atoi(buffer) && strcmp(userp[i].line,"Parlament") == 0){
            applic += userp[i].people;
            applic += 1;
            strcpy(lineUs, "Parlament");
        }else if(2 == atoi(buffer) && strcmp(userp[i].line,"Hosok tere") == 0){
            applic += userp[i].people;
            applic += 1;
            strcpy(lineUs, "Hosok tere");
        }else if(3 == atoi(buffer) && strcmp(userp[i].line,"Var") == 0){
            applic += userp[i].people;
            applic += 1;
            strcpy(lineUs, "Var");
        }
    }

    if (applic > 2){
        int pipefd[2];
        pid_t pid;
        struct applicant applicant[20];
        signal(SIGTERM,handler);
        int i = 0;
        int fee_p = 5000;
        if (pipe(pipefd) == -1) {
            perror("Hiba a pipe nyitaskor!");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid == -1) {
            perror("Fork hiba");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // child process     
            kill(getppid(),SIGTERM); 
            sleep(1);

            printf("\n");
            printf("Utaslista: ");
            printf("\n");
            for (i = 0; i < counter; i++) {
                if(strcmp(userp[i].line,lineUs) == 0){
                    read(pipefd[0],applicant[0].name,sizeof(userp[i].name));
                    printf("%s",applicant[0].name);
                }
            }

            read(pipefd[0],&applicant[0].fee,sizeof(int));
            printf("Dij: %d",applicant[0].fee);
            printf("\n");

            read(pipefd[0],applicant[0].line,sizeof(lineUs));
            printf("Utvonal: %s",applicant[0].line);
            printf("\n");

            kill(getppid(),SIGTERM); 
            sleep(1);
            
            applicant[0].fee *= applic;
            printf("%d Ft beszedve",applicant[0].fee);
            printf("\n");
            applic *=5;
            printf("%d liter sor vetelezve",applic);
            printf("\n");

            kill(getppid(),SIGTERM); 
            sleep(1);
            write(pipefd[1], &applicant[0].fee, sizeof(applicant[0].fee));
            write(pipefd[1], &applic, sizeof(applic));

            pause();

            printf("Indulhat a tura");
            kill(getppid(),SIGTERM); 
            sleep(3);


            close(pipefd[0]); // finally we close the used read end
        } else { // szulo process 
        
            pause(); 

            for (i = 0; i < counter; i++) {
                if(strcmp(userp[i].line,lineUs) == 0){
                    write(pipefd[1], &userp[i].name, sizeof(userp[i].name));
                }
            }
            fflush(NULL); 

            write(pipefd[1], &fee_p, sizeof(int));        
            write(pipefd[1], &lineUs, sizeof(lineUs));

            pause();
        
            int quantity = 0;
            int f= 0;
            read(pipefd[0],&f,sizeof(f));
            printf("Megkaptam a fizetett osszeget: %d Ft",f);
            printf("\n");
            read(pipefd[0],&quantity,sizeof(quantity));
            printf("Megkaptam a vetelezett sor mennyiseget: %d liter",quantity);
            close(pipefd[1]);
            printf("\n");
        
            kill(0,SIGTERM); 
            pause();

            printf("Veget ert a tura");
            printf("\n");
            printf("\n");
            sleep(3);
            menuPrint();
        }   
    }else{
        printf("Nincs eleg jelentkezo");
        menuPrint();
    }
}

void menu() {
    int key = -1;
    menuPrint();
    do {
        scanf("%d", &key);
        switch (key) {
	        case 0: exit(0);
                break;
            case 1: newUser();
                key = 0;
                menuPrint();
                break;
            case 2: editUser();
                key = 0;
                menuPrint();
                break;
            case 3: deleteUser();
                key = 0;
                menuPrint();
                break;
            case 4: listUsers();
                key = 0;               
                menuPrint();
                break;
            case 5: listLineUsers();
                key = 0;
                menuPrint();
                break;
            case 6: executeEvent();
                key = 0;
                break;
	    }
   } while(0 == 0);
}

int main() {
    setbuf(stdout, NULL);
    readFile();
    menu();

    return 0;
}
