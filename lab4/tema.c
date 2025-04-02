#include <stdlib.h>
#include <stdio.h>
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
    gen_key (&n, &e, &d);
    int secret_message = 0;
    printf ("Enter message: ");
    scanf ("%d", &secret_message);
    int encrypted_message = encrypt (secret_message, e, n);
    printf ("Encrypted message: %d\n", encrypted_message);
    int decrypted_message = decrypt (secret_message, e, n);
    printf ("Decrypted message: %d\n", decrypted_message);
}

int main (void)
{
    exercise1();
    exercise2();
    return 0;
}
