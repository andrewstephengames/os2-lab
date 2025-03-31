#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (void)
{
    char data = ' ';
    char *myfifo = "/tmp/myfifo";
    int fd = open (myfifo, O_RDWR);
    if (fd == 0) {
	perror ("Cannot open fifo");
	unlink(myfifo);
	exit(EXIT_FAILURE);
    }
    while (data != '#') {
	while (read (fd, &data, 1) && data != '#') {
	    fprintf (stderr, "%c", data);
	}
    }
    close (fd);
    unlink(myfifo);
    return 0;
}
