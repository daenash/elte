#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //fork
#include <sys/wait.h> //waitpid
#include <errno.h>

int main()
{
   int status;
   int notacommonvalue = 1;
   printf("The value is %i before forking \n", notacommonvalue);

   // returns process ID
   //forks make a copy of variables
   // pid_t -> int
   pid_t child = fork();

   // fork returns -1 if failed
   if (child < 0)
   {
      perror("The fork calling was not succesful\n");
      exit(1);
   }

   //the parent process, it can see the returning value of fork - the child variable!

   // a fork utáni első utasítással indul a gyerek folyamat
   if (child > 0)
   {
      // A fork 0-t ad vissza a child processen
      waitpid(child, &status, 0);
      //waits the end of child process PID number=child, the returning value will be in status
      //0 means, it really waits for the end of child process - the same as wait(&status)
      printf("The value is %i in parent process (remain the original) \n", notacommonvalue);
   }
   else //child process
   {
      notacommonvalue = 5; //it changes the value of the copy of the variable
      printf("The value is %i in child process \n", notacommonvalue);
   }
   return 0;
}