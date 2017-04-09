

#Makefile pour ASSH

OPT_FLAGS = -Wall -Werror

aash: main.c
	gcc -o assh main.c -std=c11 -g $(OPT_FLAGS)

