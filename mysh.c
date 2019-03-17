#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define CMD_LEN 128
#define CMD_CT 9
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
		FILE *ifptr;
		char buff[255];
		
		ifptr = fopen(args[i], "r");

		if (ifptr == NULL) 
		{
		  fprintf(stderr, "cat: %s: No such file or directory\n", args[0]);
		  return;
		}

		c = fgetc(ifptr);
		while(c!=EOF)
		{
			printf("%c", c);
			c = fgetc(ifptr);
		}

		fclose(ifptr);
		
	}
}


void sh_cp(char **args, int argct)
{

	//if no arguments, print syntax error
	if(argct == 0)
	{
		fprintf(stderr, "cp: missing file operand\n");
		return;
	}
	else if(argct == 1)
	{

		fprintf(stderr, "cp: missing destination file operand after \'%s\'\n", args[0]);
		return;
	}
	else if(argct != 2)
	{
		printf("Please enter exactly 2 arguments");
		return;
	}
	

	FILE *ifptr, *ofptr;
	char c;



	//Attempt to open input file
	//If it fails to open, return error
	ifptr = fopen(args[0], "r");
	if (ifptr == NULL) 
	{
	  fprintf(stderr, "cp: cannot stat \'%s\': No such file or directory\n", args[0]);
	  return;
	}

	//TODO add multiple file copy support
	ofptr = fopen(args[1], "w");
	c = fgetc(ifptr);

	while(c!=EOF)
	{
		fprintf(ofptr,"%c", c);
		c = fgetc(ifptr);		
	}
	fclose(ofptr);
	fclose(ifptr);


		//Randomly got this error one time
		//Error occurs when attempting to cat a file copied to a different directory
		//a.out: malloc.c:2401: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
		//Aborted (core dumped)
}


void sh_rm(char **args, int argct)
{
	for (int i = 0; i < argct; ++i)
	{
		remove(args[i]);
	}
}

void sh_mkdir(char **args, int argct)
{

	if(!argct)
	{
		printf("mkdir: missing operand\n");
		return;
	}
	for (int i = 0; i < argct; ++i)
	{
		char command[2048] = "mkdir ";
		strcat(command, args[i]);
		system(command);

	}
}

void sh_rmdir(char **args, int argct)
{

	if(!argct)
	{
		printf("rmdir: missing operand\n");
		return;
	}
	for (int i = 0; i < argct; ++i)
	{
		char command[2048] = "rmdir ";
		strcat(command, args[i]);
		system(command);

	}
}

void sh_touch(char **args, int argct)
{
	if(!argct)
	{
		printf("touch: missing file operand\n");
		return;
	}
	FILE *fp;

	for (int i = 0; i < argct; ++i)
	{
		fp = fopen(args[i], "w+");
		fclose(fp);
	}

}

int sh_exit(char **args, int argct)
{

	if((argct == 0) && (argct != 1))
	{
		return 0;
	}



	//TODO logic to implement an exit code
	return 0;

}




int main()
{
	int EXIT_CODE=1;

	char command[CMD_LEN];
	char PS1[PS1_LEN];




	typedef struct pair
	{
		void* function;
		char* functionName;

	}pair;

	pair* objects = malloc(sizeof(pair) * CMD_CT);

	objects[0].command = &echo;

	char validcommands[][CMD_LEN] = {"echo", "PS1", "cat", "cp", "rm", "mkdir", "rmdir", "touch", "exit"};

	// /*assign everything to the objects array*/

	// //assume command is a char* that represents the command
	// for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
	//     if (!strcmp(objects[i].functionName, command))
	//         objects[i].function(arguments);
		

	//Create array to hold list of valid commands


	//Initialize PS1 to default value
	strcpy(PS1, "$ ");

	//Switch variable
	int sw;

	do 
	{

		//User IO code obtained from 
		//https://stackoverflow.com/questions/10112038/parsing-commands-shell-like-in-c

		//Print out the PS1 prompt
		printf("%s", PS1);

		//Create 2 arrays, one holding the original 
		//line and one holding the dynamic line (the one
		// that will be modified throughout the program)
		char *line = malloc(CMD_LEN);


		//Allocate space and then
		// copy contents of the line 
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
		// 	printf("Argument %i is %s\n", i, kwargs[i]);
		// }
		
		sw = isValidCommand(command, validcommands);



		//printf("Value of sw: ->%d<-\n", sw);

		switch(sw)
		{
			//empty command
			case -2:
				printf("No command entered. \n");
				continue;
			//invalid command
			case -1:
				printf("%s: Invalid Command, Not found\n",command );
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
				sh_rm(kwargs, argct);
				break;
			//mkdir
			case 5:
				sh_mkdir(kwargs, argct);
				break;
			//rmdir
			case 6:
				sh_rmdir(kwargs, argct);
				break;
			//touch
			case 7:
				sh_touch(kwargs, argct);
				break;
			//exit
			case 8:
				EXIT_CODE = sh_exit(kwargs, argct);
				break;

			default:
				printf("How the actual hell did you get here. \n STOP BREAKING MY CODE\n");


		}


		//Clear args, lines, and everything needed for the next step 
		for (int i = 0; i < argct; ++i)
		{
			free(kwargs[i]);
		}
		
		free(kwargs);
		free(line_s);

	}while(EXIT_CODE); //EXIT_CODE should remain 1 unless errors occur
					// which has not been implemented yet 

	return EXIT_CODE;
}
