#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MESSAGE_SIZE 256

void writer (char *message, int count, FILE *stream)
{
    char new_message[MESSAGE_SIZE], corruption;
    for (; count > 0; count--) {
	size_t j = 0;
	strcpy(new_message, message);  
	for (int i = 0; i < strlen(message)/4; ++i) {
	    corruption = rand()%128;
	    if (corruption != '\n') {
		new_message[rand()%strlen(message)] = rand()%128;
	    }
	}
	fprintf (stream, "%s\n", new_message);
	fflush (stream);
	usleep(1e5);
    }
    strcpy (message, new_message);
}

void reader (FILE *stream)
{
    char buffer[1024];
    while (!feof(stream) && !ferror(stream) &&
	    fgets (buffer, sizeof(buffer), stream) != NULL)
	fputs (buffer, stdout);
}

int main (void)
{
    FILE *stream;
    char *buffer = malloc (sizeof(char)*MESSAGE_SIZE);
    strcpy (buffer, "Hello, World!");
    srand(clock());
    int fds[2];
    pipe(fds);
    if (fork() == (pid_t) 0) {
	stream = fdopen (fds[0], "r");
	reader (stream);
	close(fds[0]);
    } else {
	stream = fdopen (fds[1], "w");
	writer (buffer, 1, stream);
	if (fork() == (pid_t) 0) {
	    stream = fdopen (fds[0], "r");
	    reader (stream);
	    close(fds[0]);
	} else {
	    stream = fdopen (fds[1], "w");
	    writer (buffer, 1, stream);
	    if (fork() == (pid_t) 0) {
		stream = fdopen (fds[0], "r");
		reader (stream);
		close(fds[0]);
	    } else {
		stream = fdopen (fds[1], "w");
		writer (buffer, 1, stream);
	    }
	}
	close(fds[1]);
    }
    free(buffer);
    return 0;
}
