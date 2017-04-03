
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // execvp, fork
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait


char buffer[50];



int isSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}



void printArg(char* argv[])
{
	// affiche la chaine de caractères de argv
	// sur chaque ligne précédée du num de ligne
	int i = 0;

	while (argv[i] != NULL)
	{
		printf("%i : %s\n", i, argv[i]);
		i++;
	}
}



void splitArg(char* line, int argcMax, char* argv[])
{
	// prend la chaine line et remplit le tableau argv de taille argcMax cases
	// ne doit pas remplir plus de argcMax cases, sinon renvoie une erreur
	// dernière case est NULL
	// passe tous les caractères de line en revue, il conserve le caractère courant et le précédant

	// cas 1 : caractère précédent est espace et caractère courant non
	// alors caractère courant est nouveau mot

	// cas 2 : caractère courant est espace et caractère précédent non
	// alors caractère courant est fin d'un mot, on le remplace par 0

	char cour, prec; // caractère courant et caractère précédent
	cour = ' ';
	prec = 0;

	int i = 0;
	int argc = 0; // nombre d'arguments

	while (line[i] != 0) // on est pas en bout de chaine
	{
		prec = cour;
		cour = line[i];

		if (!isSpace(cour) && isSpace(prec)) // nouveau mot
		{
			argv[argc] = &line[i];
			argc++;
		}
		else if (!isSpace(prec) && isSpace(cour)) // fin de mot
		{
			line[i] = 0;
		}

		i++;

		if (argc >= argcMax) // on dépasse la taille de argv
		{
			exit(EXIT_FAILURE);
		}
	}

	argv[argc] = 0; // la dernière case est null
}





int main(int argc, char const *argv[])
{
	char *cmd = NULL;
	int size = 50;
	int sortie = 0;
	pid_t p = 0;
	int ret = 0;

	const int argcMax = 128;
	char* argvCmd[argcMax];

	
	while (1)
	{
		
		printf("assh$ "); // prompt
		
		cmd = fgets(buffer, size, stdin); // lecture de la commande
		
		//printf("Ligne lue : %s", cmd); // confirmation

		splitArg(cmd, argcMax, argvCmd); // découpe de la commande

		if (strcmp(argvCmd[0], "exit") == 0) // commande de sortie
		{
			break;
		}


		p = fork(); // fork, le fils exécute, le père attend

		if (p==0) // processus fils qui exécute la commande
		{
			return execvp(argvCmd[0], argvCmd);
		}

		else // processus père attend le fils
		{
			wait(&ret); // le code de retour du père va dans ret
			if (ret != 0) // si il y a eu une erreur lors de l'exécution
			{
				printf("La commande ne peut pas etre exécutée.\n");
				//exit(EXIT_FAILURE);
			}
		}





		//printArg(argvCmd); 

		// int i;
		// for (i = 0; i < size && cmd[i] != 0; i++)
		// {
		// 	if (isSpace(cmd[i]))
		// 	{
		// 		printf("%i : isSpace\n", cmd[i]);
		// 	}
		// 	else
		// 	{
		// 		printf("%i : %c\n", cmd[i], cmd[i]);
		// 	}
		// }

	}
	

	//printArg(argv);

	printf("Au revoir! \n");
	return 0;
}

