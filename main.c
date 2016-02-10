#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

static pid_t process_create(struct program_desc program);

int main (int argc, char **argv)
{
	printf("Ordonnanceur\n");
	process_create(programs[0]);
	
	return 0;
}

static pid_t process_create(struct program_desc program)
{
	pid_t pid = fork();
	
	switch (pid)
	{
		/* Si on a une erreur */
		case -1:
			perror("fork");
			return EXIT_FAILURE;
			break;

		/* Si on est dans le fils */
		case 0:
			execvp(program.file, program.args);
			break;

		/* Si on est dans le père */
		default:
			
			break;
    }
}