#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NB_PROC 10

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

struct process_entry
{
	pid_t pid; 			/* PID du processus*/
	struct timeval time_sched; 	/* Temps passé dans l'ordonnanceur*/
	struct timeval time_exec; 	/* Temps total alloué sur le processeur*/
	char *file;			/* nom de l'exécutable du preocessus */
	int exit_status;		/* Code d'erreur retourné par le processus */
};

static pid_t process_create(struct program_desc program);
static void process_add(pid_t pid, char* file);
static void process_remove(struct process_entry *entry);
static int process_exited(struct process_entry *entry);
static void scheduler_run(void);

struct process_entry liste[10];
int listeSize = 0;

int main (int argc, char **argv)
{
	printf("Ordonnanceur\n");
	process_create(programs[0]);
	process_create(programs[1]);
	scheduler_run();
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
			process_add(pid, program.file);
			break;
    }
}


static void process_add(pid_t pid, char* file)
{
	struct process_entry p = {pid, *file};
	liste[listeSize] = p;
	listeSize++;
}


static void process_remove(struct process_entry *entry)
{
	int i;
	for(i=0 ; i < NB_PROC-1 ; i++)
	{
		entry[i] = entry[i+1];
	}
	struct process_entry empty;
	entry[NB_PROC-1] = empty;
	listeSize--;
}


static int process_exited(struct process_entry *entry)
{
	int statut = 1;
	waitpid(entry->pid, &statut, WNOHANG);
	entry->exit_status = statut;
	return statut;
}

static void scheduler_run(void)
{
	int continuer = 1;
	int i;
	while (continuer == 1)
	{
		for(i=0 ; i <= listeSize ; i++)
		{
			int retour = process_exited(&liste[i]);
			if (retour == 0)
				process_remove(&liste[i]);
		}
		if (listeSize == 0)
			continuer = 0;
	}
}