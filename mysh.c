#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define CMD_LEN 128
#define CMD_CT 8
#define PS1_LEN 128
#define CMD_SIZE 20



//Checks command against validcommands, returns an integer 
//representing the index in the commands array where the 
//command is found 
int isValidCommand(char command[], char validcommands[][CMD_LEN])
{
	if(strlen(command) == 0)
	{
		//-2 signifies no command entered
		return -2;
	}
	for (int i = 0; i < CMD_CT; ++i)
	{

		//printf("Comparing ->%s<- to ->%s<-\n", command, validcommands[i]);
		if(!(strcmp(command, validcommands[i]))) 
			{
				//printf("Found at %d\n", i);
				//Return index if found
				return i;
			}
	}

	//Return -1 if invalid command is entered. 
	return -1;
}

/////////////////////
// Shell Functions //
/////////////////////

void sh_echo(char **kwargs, int argct)
{

	int nl = 1;
	//printf("->%d<- args entered\n", argct);
	for (int i = 0; i < argct; ++i)
	{
		if(strcmp(kwargs[i], "-n") == 0)
		{
			nl = 0;
			continue;
		}
				printf("%s ", kwargs[i]);
	}

	if(nl) printf("\n");
}

void sh_ps1(char **args, int argct, char PS1[])
{	

	//If no arguments passed, do nothing. 
	if(!argct) return;


	//Clear PS1
	PS1[0] = '\0';

	for (int i = 0; i < argct; ++i)
	{
		strcat(PS1, args[i]);
		strcat(PS1, " ");
	}

	return;
}

void sh_cat(char **args, int argct)
{

	char c;

	for (int i = 0; i < argct; ++i)
	{

		//https://www.tutorialspoint.com/cprogramming/c_file_io.htm
		//https://www.cs.bu.edu/teaching/c/file-io/intro/
		FILE *ifp;
		char buff[255];
		
		ifp = fopen(args[i], "r");

		if (ifp == NULL) 
		{
		  fprintf(stderr, "cat: %s: No such file or directory\n", args[0]);
		  return;
		}

		c = fgetc(ifp);
		while(c!=EOF)
		{
			printf("%c", c);
			c = fgetc(ifp);
		}

		fclose(ifp);
		
	}
}


void sh_cp(char **args, int argct)
{
	

}


// void sh_rm(char **args, int argct)
// {

// }

void sh_mkdir(char **args, int argct)
{
	for (int i = 0; i < argct; ++i)
	{
		char command[2048] = "mkdir ";
		strcat(command, args[i]);
		system(command);

	}
}

void sh_rmdir(char **args, int argct)
{
	for (int i = 0; i < argct; ++i)
	{
		char command[2048] = "rmdir ";
		strcat(command, args[i]);
		system(command);

	}
}

int sh_exit(char **args, int argct)
{

	if(argct == 0)
	{
		return 0;
	}

	
	return 0;

}


int main()
{
	int EXIT_CODE=1;

	char command[CMD_LEN];
	char PS1[PS1_LEN];
	

	//Create array to hold list of valid commands
	char validcommands[][CMD_LEN] = {"echo", "PS1", "cat", "cp", "rm", "mkdir", "rmdir", "exit"};


	//Initialize PS1 to default value
	strcpy(PS1, "$ ");

	//Switch variable
	int sw;

	do 
	{

		//Print out the PS1 prompt
		printf("%s", PS1);

		//Create 2 arrays, one holding the original 
		//line and one holding the dynamic line (the one
		// that will be modified throughout the program)
		char *line = malloc(CMD_LEN);
		
		//Set all elements of array to null, to avoid any
		//stray values floating around
		//memset(&line[0], ' ', sizeof(line));

		//Allocate space and then
		// Copy contents of the line 
		// into a static copy
		char *line_s = malloc(CMD_LEN);
		strcpy(line_s, line);

		//memset(&command[0], '\0', sizeof(command));

		//Actually get the input from the user 
		fgets(line, CMD_LEN, stdin);

		char command[CMD_SIZE];

		//Read input from line, match to formatter
		//and place in command
		sscanf(line, "%20s ", command);

		line = strchr(line, ' ');

		//Debug to ensure that command value is correct 
		//printf("Command value: %s\n", command);


		//Dynamically allocate memory for arg and kwargs

		int argct = 0;

		//Allocate dynamic memory on heap 
		//and pointer on stack 
		char **kwargs = malloc(sizeof(char *));
		while(1) 
		{
		    char arg[20];
		    if(line && (sscanf(++line, "%20s", arg) == 1))
		    {
		    	//Allocate memory for 20 pointers 
		    	kwargs[argct] = malloc(sizeof(char)*20); 
		    	strncpy(kwargs[argct], arg, 20);

		    	argct++;

		    	kwargs = realloc(kwargs, sizeof(char *) * argct+1);
		    	line = strchr(line, ' ');
		    }
		    else
		    {
		    	break;
		    }
		}


		//At this point, the command is stored in the 
		//command array, and the args are stored in a 2d array
		// in kwargs

		// for (int i = 0; i < argct; ++i)
		// {
		// 	free(kwargs[i]);
		// }
		
		// free(kwargs);
		// free(line_s);
		
		

		// for (int i = 0; i < argct; ++i)
		// {
		// 	printf("Argument %i is %s\n", i, kwargs[i]);
		// }
		
		if((sw = isValidCommand(command, validcommands)) == -1)
		{
			printf("%s: Invalid Command, Not found\n",command );
			continue;
		}



		//printf("Value of sw: ->%d<-\n", sw);

		switch(sw)
		{
			//empty command
			case -2:
				printf("No command entered. \n");
				continue;


			//echo
			case 0:
				sh_echo(kwargs, argct);
				break;
			//PS1	
			case 1:
				sh_ps1(kwargs, argct, PS1);
				break;
			//cat
			case 2:
				sh_cat(kwargs, argct);
				break;
			//cp
			case 3:
				sh_cp(kwargs, argct);
				break;
			//rm
			case 4:
				break;
			//mkdir
			case 5:
				sh_mkdir(kwargs, argct);
				break;
			//rmdir
			case 6:
				break;
			//exit
			case 7:
				EXIT_CODE = sh_exit(kwargs, argct);
				break;

			default:
				printf("How tf did you get her\n");


		}

	}while(EXIT_CODE); //EXIT_CODE should remain 1 unless errors occur
					// which has not been implemented yet 

	return EXIT_CODE;
}
