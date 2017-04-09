
/*
	AS-SHELL
	TP création d'un shell pour l'Année Spéciale
	Raphael Castanier
	IUT2 Grenoble 2017
*/

/*
	A faire:
	- processus en arrière plan et interruptions
	- interruptions CTRL-D
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // execvp, fork
#include <sys/wait.h> // wait
#include <errno.h> // errno
#include <signal.h> // sigaction
#include <sys/types.h> // pid_t


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


int findAmp(char* argv[])
{
	// retourne 1 si le dernier argument de argv se termine avec & et le retire de la chaine s'il est trouvé
	// retourne 0 sinon

	char* cour = 0; // argument courant
	char c = 0; // caractère courant
	int i = 0;

	// on parcourt argv jusquà tomber sur 0 (fin de chaine)
	while (argv[i] != 0)
	{
		cour = argv[i];
		i++;
	}
	
	i = 0;
	// on parcourt le dernier argument
	while (cour[i] != 0)
	{
		c = cour[i];
		i++;
	}

	if (c == '&') // si le caractère courant est &
	{
		cour[i] = 0; // on fait terminer la chaine au caractère & (il est remplacé par 0)
		return 1;
	}

	return 0;
}


void procedure()
{
	// procedure à lancer par sigaction lors d'une interruption par SIGCHLD

	// lance la fonction wait et affiche pour l'utilisateur le PID du fils qui s'est terminé

	pid_t ret;
	int status;
	ret = wait(&status);

	printf("SIGCHLD : Fils %i terminé avec le statut %i\n", ret, status);

}


int readLine(char* line, int lineSize)
{
	// teste le cas d'erreur en sortie de cette fonction et la fin de fichier
	
	printf("assh$ "); // prompt
		
	cmd = fgets(buffer, size, stdin); // lecture de la commande
		
	printf("Ligne lue : %s", cmd); // confirmation de lecture

	return 0;
}


int main(int argc, char const *argv[])
{
	char *cmd = NULL;
	int size = 50;
	pid_t p = 0;
	int ret = 0;


	const struct sigaction action; // gestion de SIGCHLD
	action.sa_handler = procedure;

	


	const int argcMax = 128; // nombre maximal de paramètres d'une commande
	char* argvCmd[argcMax]; // paramètres d'une commande

	
	while (1) // boucle infinie
	{
		
		printf("assh$ "); // prompt
		
		cmd = fgets(buffer, size, stdin); // lecture de la commande
		
		//printf("Ligne lue : %s", cmd); // confirmation de lecture

		splitArg(cmd, argcMax, argvCmd); // découpe de la commande

		if (strcmp(argvCmd[0], "exit") == 0) // commande de sortie
		{
			break;
		}

		//printf("Le dernier argument est & : %s\n", findAmp(argvCmd)?"oui":"non");
		



		p = fork(); // fork, le fils exécute, le père attend

		if (p==0) // processus fils qui exécute la commande
		{
			ret = execvp(argvCmd[0], argvCmd);
			perror("aash");
			return ret;
		}

		else // processus père attend le fils
		{

			if (findAmp(argvCmd)) // si le dernier argument est &, le processus doit etre exécuté en arrière plan
			{
				int i = sigaction(SIGCHLD, &action, NULL);
				printf("EXECUTION DU FILS EN COURS\n");
			}
			else // sinon il est exécuté normalement
			{
					wait(&ret); // le code de retour du fils va dans ret
					if (ret != 0) // si il y a eu une erreur lors de l'exécution
					{
						//printf("E père : code = %i \n", ret);
						//printf("E père : errno = %i \n", errno);
						//printf("La commande ne peut pas etre exécutée.\n");
						//exit(EXIT_FAILURE);
					}
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

