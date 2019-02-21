#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//code obtained from 
//https://stackoverflow.com/questions/10112038/parsing-commands-shell-like-in-c

int main(int argc, char const *argv[])
{
    while (1) 
        {
            printf("$ ");
            char *line = malloc(128); // we need to be able to increase the pointer
            char *origLine = line;
            fgets(line, 128, stdin);


            char command[20];
            sscanf(line, "%20s ", command);

            line = strchr(line, ' ');

            printf("The Command is: %s\n", command);

            unsigned argumentsCount = 0;
            char **arguments = malloc(sizeof(char *));

            while (1)
            {
                char arg[20];
                if (line && (sscanf(++line, "%20s", arg) == 1))
                {
                    arguments[argumentsCount] = malloc(sizeof(char) * 20);
                    strncpy(arguments[argumentsCount], arg, 20);

                    argumentsCount++;

                    arguments = realloc(arguments, sizeof(char *) * argumentsCount + 1);
                    line = strchr(line, ' ');
                }
                else {
                    break;
                }
            }

            for (int i = 0; i < argumentsCount; i++) 
            {
                printf("Argument %i is: %s\n", i, arguments[i]);
            }

            for (int i = 0; i < argumentsCount; i++) 
            {
                free(arguments[i]);
            }

            free(arguments);
            free(origLine);
        }
    return 0;
}