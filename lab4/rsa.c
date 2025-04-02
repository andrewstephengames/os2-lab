#include <stdlib.h>
#include <time.h>

int gcd (int a, int b)
{
    while (a != b) {
	if (a > b) a -= b;
	else if (b > a) b -= a;
    }
    return a;
}

int imod (int e, int phi)
{
    int t1 = 0, t2 = 1, r1 = phi, r2 = e;
    while (r2 > 0) {
	int q = r1/r2;
	int t = t1 - q*t2;
	int r = r1 - q*t2;
	t1 = t2;
        t2 = t;
        r1 = r2;
        r2 = r;
    }
    if (r1 > 1) {
	return -1;
    }
    if (r1 < 0) {
	t1 += phi;
    }
    return t1;
}

int prime (int n)
{
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n%2 == 0) return 0;
    for (int d = 3; d*d < n; d += 2) {
	if (n%d == 0) return 0;
    }
    return 1;
}

int find_prime (void)
{
    int n;
    while (1) {
	n = rand()%100 + 1;
	if (prime(n)) {
	    return n;
	}
    }
}

int gen_key (int *n, int *e, int *d)
{
    srand(clock());
    int p = find_prime();
    int q = find_prime();
    *n = p*q;
    int phi = (p-1) * (q-1);
    int ee = 2;
    while (gcd(ee, phi) != 1) {
	ee++;
    }
    *e = ee;
    *d = imod (*e, phi);
}

int encrypt (int message, int e, int n)
{
    int secret_message = 1;
    for (int i = 0; i < e; ++i) {
	secret_message = (secret_message*message)%n;
    }
    return secret_message;
}

int decrypt (int message, int d, int n)
{
    int secret_message = 1;
    for (int i = 0; i < d; ++i) {
	secret_message = (secret_message*message)%n;
    }
    return secret_message;
}
