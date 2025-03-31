#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void)
{
    pid_t child_pid;
    printf ("Process id: %d; Parent process id: %d\n", (int) getpid(), (int) getppid());
    child_pid = fork();
    if (child_pid != 0) {
	printf ("Parent: child process id: %d\n", (int) child_pid);
    } else {
	printf ("Child: process id: %d\n", (int) getpid());
    }
    return 0;
}
