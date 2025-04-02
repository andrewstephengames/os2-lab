#include <stdio.h>
#include <pthread.h>
#include <linux/futex.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdatomic.h>

#define NUM 5

int futex_addr;
atomic_int free_spots = NUM;

int futex(int* uaddr, int op, int val);
void* park_car (void *arg);
void *exit_car (void *arg);

int main()
{
    pthread_t parkers[NUM], exit_thread;
    for (int i = 0; i < NUM; i++) {
	pthread_create(&parkers[i], NULL, park_car ,(void *)i);
    }
    pthread_create (&exit_thread, NULL, exit_car, NULL);
    for (int i = 0; i < NUM; i++) {
	pthread_join (parkers[i], NULL);
    }
    pthread_join (exit_thread, NULL);
    return 0;
}

int futex(int* uaddr, int op, int val)
{
    return syscall(SYS_futex, uaddr, op, val, NULL, NULL, 0);
}

void* park_car (void *arg)
{
    int parker = (int) arg;
    while (1) {
	if (atomic_load (&free_spots) > 0) {
	    atomic_fetch_sub (&free_spots, 1);
	    printf ("Parker %d found a free spot. Spots left: %d\n", parker, atomic_load(&free_spots));
	    break;
	} else {
	    printf ("Parker %d is waiting for a free spot...\n", parker);
	    futex(&futex_addr, FUTEX_WAIT, 0);
	}
	usleep(5e5);
    }
    return NULL;
}

void *exit_car (void *arg)
{
    while (1) {
	usleep(2);
	atomic_fetch_add(&free_spots, 1);
	printf ("A parker left the parking lot. Available spots: %d\n", atomic_load(&free_spots));
	futex (&futex_addr, FUTEX_WAKE, 1);
	if (atomic_load(&free_spots) >= NUM) {
	    break;
	}
    }
    return NULL;
}
