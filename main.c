#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct program_desc
{
	char *file;
	char *args[5];
};

struct program_desc programs[] = {
	{"firefox", {"http://google.fr", NULL}},
	{"gedit", {NULL}},
	{"xterm", {"toto.c", NULL}},
};

int main (int argc, char **argv)
{
	printf("Ordonnanceur\n");
	
	return 0;
}