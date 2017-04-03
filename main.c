
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

	int nb_arg = 20;
	char* arg[20];

	
	while (!sortie)
	{
		printf("assh$ ");
		cmd = fgets(buffer, size, stdin);
		printf("Ligne lue : %s", cmd);

		splitArg(cmd, nb_arg, arg);

		printArg(arg);

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

		if (strcmp(cmd, "exit\n") == 0)
		{
			sortie = 1;
		}
	}
	

	//printArg(argv);

	printf("Au revoir! \n");
	return 0;
}

