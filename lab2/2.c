#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define LABEL_SIZE 256

int word_count = 0;
DIR *d;
char file_name[LABEL_SIZE];
char *separators = " \t\n\r,.!?;:\"()[]{}<>";
struct dirent *dir;
pthread_mutex_t lock;

char *specific_word = "int";

void *word_counter (void *vargp)
{
    char *current_filename = (char *)vargp;
    static int s = 0;
    ++s;
    FILE *current_file = fopen(file_name, "r");
    char *word = malloc (LABEL_SIZE + 1);
    if (!word) {
	fclose(current_file);
	fprintf (stderr, "Buy more RAM lol\n");
	return NULL;
    }
    char *token;
    if (current_file != NULL) {
        while (fgets (word, LABEL_SIZE, current_file) != NULL) {
	   token = strtok (word, separators);
	   while (token) {
		if (strstr (token, specific_word)) {
		    pthread_mutex_lock(&lock);
		    ++word_count;
		    printf ("Found occurance of %s in %s\n", specific_word, file_name);
		    pthread_mutex_unlock(&lock);
		}
		token = strtok (NULL, separators);
	   }
	}
    } else {
	fprintf (stderr, "Error upon opening file %s\n", file_name);
    }
    //printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++word_count);
    free(word);
    fclose(current_file);
    return NULL;
}
int main()
{
    pthread_t threads[256];
    int thread_id = 0;
    d = opendir(".");
    pthread_mutex_init(&lock, NULL);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
	    if (dir->d_name[0] == '.') continue;
	    strcpy(file_name, dir->d_name);
	    printf ("Current file: %s\n", file_name);
	    if (!file_name) continue;
	    pthread_create(&threads[thread_id++], NULL, word_counter, file_name);
        }
	closedir(d);
    }
    for (int i = 0; i < thread_id; ++i) {
	pthread_join (threads[i], NULL);
    }
    pthread_mutex_destroy (&lock);
    printf ("Number of occurances of \"%s\": %d in the current folder.\n", specific_word, word_count);
    return 0;
}
