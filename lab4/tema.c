#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"
#include "rsa.h"

#define N 9

void exercise1 (void)
{
    int v[] = {10, -20, 30, 9, 7, 8, 11, 5, -2, 100};
    printf("Values: ");
    for (int i = 0; i < N; ++i) {
	printf ("%d ", v[i]);
    }
    printf("\n");
    printf ("Values greater than %d: %d\n", MIN_VAL, vect_gt (v, N, MIN_VAL));
    printf ("Values greater than %d: %d\n", MAX_VAL, vect_gt (v, N, MAX_VAL));
}

void exercise2 (void)
{
    int n, e, d;
    gen_key(&n, &e, &d);
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) { // Parent process (sender)
        close(pipefd[0]); // Close read end
        
        int secret_message;
        printf("Enter message: ");
        scanf("%d", &secret_message);
        
        int encrypted_message = encrypt(secret_message, e, n);
        write(pipefd[1], &encrypted_message, sizeof(encrypted_message));
        close(pipefd[1]);
        
        wait(NULL); // Wait for child
    } else { // Child process (receiver)
        close(pipefd[1]); // Close write end
        
        int encrypted_message;
        read(pipefd[0], &encrypted_message, sizeof(encrypted_message));
        close(pipefd[0]);
        
        int decrypted_message = decrypt(encrypted_message, d, n);
        printf("Encrypted message received: %d\n", encrypted_message);
        printf("Decrypted message: %d\n", decrypted_message);
        
        exit(0);
    }
    /*
    int n, e, d;
    gen_key (&n, &e, &d);
    int secret_message = 0;
    printf ("Enter message: ");
    scanf ("%d", &secret_message);
    int encrypted_message = encrypt (secret_message, e, n);
    printf ("Encrypted message: %d\n", encrypted_message);
    int decrypted_message = decrypt (secret_message, e, n);
    printf ("Decrypted message: %d\n", decrypted_message);
    */
}

int main (void)
{
    exercise1();
    exercise2();
    return 0;
}
