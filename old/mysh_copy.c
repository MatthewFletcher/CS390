#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>

#define CMD_LEN 128
#define CMD_CT 8
#define PS1_LEN 128





int isValidCommand(char command[], char validcommands[][CMD_LEN])
{

	char temp[CMD_LEN];
	const char sepchar[2] = " ";
	char *token;
	

	printf("here\n");
	strcpy(temp, command);
	printf("here1\n");
	token = strtok(temp, sepchar);
	printf("here2\n");
	printf("token => ->%s<-\n", token);



	if(strlen(token) == 0)
		return -2;

	for (int i = 0; i < CMD_CT; ++i)
	{
		printf("loop %d\n", i);

		//printf("Comparing ->%s<- to ->%s<-\n", token, validcommands[i]);
		if(!(strcmp(token, validcommands[i]))) 
			{
				//printf("Found at %d\n", i);
				return i;
			}
	}

	return -1;
}


//Functions
void echo(char command[])
{
	printf("%s\n", command);
}

char ps1(char PS1[])
{
	

	return *PS1;
}


int main(int argc, char *argv[])
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
		//Clear array holding command
		memset(&command[0], '\0', sizeof(command));
		
		printf("%s", PS1);

		//Initialize index counter
		char *command = NULL;
		ssize_t bufsize = 0;
		getline(&command, &bufsize, stdin);

		//Remove New Line char
		//https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
		char *pos;
		if ((pos=strchr(command, '\n')) != NULL)
		    *pos = '\0';
		else
		    continue;

		//Print command to check proper syntax
		printf("Requested command ->%s<-\n", command);

		
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
				continue;


			//echo
			case 0:
				echo(command);
				break;
			//PS1	
			case 1:
				ps1(command);
				break;
			//cat
			case 2:
				break;
			//cp
			case 3:
				break;
			//rm
			case 4:
				break;
			//mkdir
			case 5:
				break;
			//rmdir
			case 6:
				break;
			//exit
			case 7:
				break;

			default:
				printf("How tf did you get her\n");


		}

	}while(EXIT_CODE);
	return EXIT_CODE;
}
