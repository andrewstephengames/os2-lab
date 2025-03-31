#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void writer (const char *message, int count, FILE *stream)
{
    char new_message[255];
    char helper_string[255];
    for (; count > 0; count--) {
	size_t j = 0;
	strcpy(new_message, message);  
	size_t message_size = strlen(message);
	for (int i = 0; i < message_size; ++i) {
	    if (strchr("aeiouAEIOU", message[i])) {
		new_message[j++] = 'p';
		new_message[j++] = message[i];
		new_message[j++] = 'p';
	    } else {
		new_message[j++] = message[i];
	    }
	}
	new_message[j] = '\0';
	fprintf (stream, "%s\n", new_message);
	fflush (stream);
	sleep(1);
    }
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
    char buffer[255];
    strcpy (buffer, "Hello, World!");
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if (pid == (pid_t) 0) {
	close (fds[1]);
	stream = fdopen (fds[0], "r");
	reader (stream);
	close (fds[0]);
    } else {
	close (fds[0]);
	stream = fdopen (fds[1], "w");
	writer (buffer, 3, stream);
	close (fds[1]);
    }
    return 0;
}
