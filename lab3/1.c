#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t client, cook, waiter;
int counter;
pthread_mutex_t lock;
int order_finished, order_sent;

void* client_job(void *arg);
void* cook_job(void *arg);
void* waiter_job(void *arg);
void error_on_thread_create (int error);

int main(void)
{
    int error;
    if (pthread_mutex_init(&lock, NULL) != 0) {
	printf("\n mutex init has failed\n");
	return 1;
    }
    error = pthread_create(&client, NULL, &client_job, NULL);
    error_on_thread_create(error);

    error = pthread_create(&cook, NULL, &cook_job, NULL);
    error_on_thread_create(error);

    error = pthread_create(&waiter, NULL, &waiter_job, NULL);
    error_on_thread_create(error);

    pthread_join(client, NULL);
    pthread_join(cook, NULL);
    pthread_join(waiter, NULL);
    pthread_mutex_destroy(&lock); 
    return 0;
}

void* client_job(void *arg) {
    pthread_mutex_lock(&lock);
    unsigned long i = 0;
    counter += 1;
    printf("\n Client is waiting for order ... \n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* cook_job(void *arg) {
    pthread_mutex_lock(&lock);
    unsigned long i = 0;
    counter += 1;
    printf("\n Cook job has started\n");
    for(i = 0; i < 0xFFFFFFFF; i++);
	order_finished = 1;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* waiter_job(void *arg) {
    pthread_mutex_lock(&lock);
    unsigned long i = 0;
    counter += 1;
    printf ("\n Waiter job has started\n");
    printf("Order number %d sent!\n", counter);
    if (order_finished) {
	printf ("Order received!\n");
	order_sent = 1;
	if (order_sent)
	    printf ("I have received my order, thank you!\n");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void error_on_thread_create (int error) {
    if (error != 0)
	printf("\nThread can't be created :[%s]", strerror(error));
}
