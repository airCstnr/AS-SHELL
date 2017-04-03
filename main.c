
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char buffer[50];



int isSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

void printArg(const char* argv[])
{
	// affiche la chaine de caractères de argv
	// sur chaque ligne précédée du num de ligne
	//char* arg = NULL; // argument courant
	int i = 0;

	while (argv[i] != NULL)
	{
		// afficher ligne
		printf("%i : %s\n", i, argv[i]);
		i++;
	}
}


int main(int argc, char const *argv[])
{
	char *cmd = NULL, *wd = NULL;
	int size = 50;
	int sortie = 0;



	//wd = get_current_dir_name();

	/*
	while (!sortie)
	{
		//printf("assh:%s$ ", wd);
		printf("assh$ ");
		cmd = fgets(buffer, size, stdin);
		printf("Ligne lue : %s", cmd);

		int i;
		for (i = 0; i < size && cmd[i] != 0; i++)
		{
			if (isSpace(cmd[i]))
			{
				printf("%i : isSpace\n", cmd[i], cmd[i]);
			}
			else
			{
				printf("%i : %c\n", cmd[i], cmd[i]);
			}
		}

		if (strcmp(cmd, "exit\n") == 0)
		{
			sortie = 1;
		}
	}
	*/

	printArg(argv);

	printf("Au revoir! \n");
	return 0;
}

