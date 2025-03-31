#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 10
#define INTEREST_RATE 0.007f
#define MONTHS 12
#define YEARS 10

pthread_mutex_t lock;

void *money_deposit(void *vargp)
{
    size_t money = (size_t) vargp;
    static float new_money = 0;
    static int s = 0;
    ++s;
    pthread_mutex_lock(&lock);
    // 0.007/12
    new_money += money * pow((float) 1 + INTEREST_RATE/MONTHS, MONTHS*YEARS);
    printf("Money in the bank after %d years at an interest rate of %.1f%% per %d months: %.3f\n", YEARS, INTEREST_RATE*100, MONTHS, new_money);
    pthread_mutex_unlock(&lock);
}
int main()
{
    size_t deposited_money = 1000;
    pthread_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++)
	pthread_create(&threads[i], NULL, money_deposit, (void *)deposited_money);
    for (int i = 0; i < THREAD_COUNT; i++)
	pthread_join(threads[i], NULL);
    pthread_exit(NULL);
    return 0;
}
