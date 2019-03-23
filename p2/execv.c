#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

#define BASH_EXEC "/usr/bin/bash"
#define LS_EXEC "/usr/bin/ls"

#define BSIZE 50

int main(int argc, char* argv[]){

  if(argc < 2) {
	  //if we do not have path in our program arguments from command line print help message and exit
	  printf("Usage: execv-example PATH \n eg. execv-example /usr/bin\n");
	  fflush(stdout);
	  return 0;
   }

    //this is a temp buffer used that will be used to build the argument
    char buffer[BSIZE];

    //get the buffer to be all NULLs
    bzero(buffer, BSIZE);

    //build the argument "ls -l /path/to/list/folders" and store it in buffer
    sprintf(buffer, "%s -l %s", LS_EXEC, argv[1]);
    //printf("buffer: %s\n", buffer);
    
    //build the argument vector
    char* args_to_bash[] = {BASH_EXEC, "-c", buffer, NULL};

    //execute the command
    if(execv(BASH_EXEC, args_to_bash) < 0){
	    printf("Something terrible happended!");
	    return 1;
    }

    return 0;
}
