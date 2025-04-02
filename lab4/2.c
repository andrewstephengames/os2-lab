#include <stdio.h>
#include "rsa.h"

int main ()
{
    int n, e, d;
    gen_key (&n, &e, &d);
    int secret_message = 0;
    printf ("Enter message: ");
    scanf ("%d", &secret_message);
    int encrypted_message = encrypt (secret_message, e, n);
    printf ("Encrypted message: %d", encrypted_message);
    int decrypted_message = decrypt (secret_message, e, n);
    printf ("Decrypted message: %d", decrypted_message);
    return 0;
}
