

#Makefile pour ASSH

aash: main.c
	gcc -o assh main.c -std=c99 -g -Wall -Werror