#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty; 
sem_t full;  
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    int id = *((int *)pno);
    for(int i = 0; i < 5; i++) {
        item = rand() % 100;  // produce a random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("\nProducer %d produced %d at position %d", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{
    int item;
    int id = *((int *)cno);
    for(int i = 0; i < 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("\nConsumer %d consumed %d from position %d", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void main()
{
    pthread_t pro[5], con[5];
    int i, num_pro, num_con;
    int p[5], c[5];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    printf("\nEnter number of producers (max 5): ");
    scanf("%d", &num_pro);
    printf("Enter number of consumers (max 5): ");
    scanf("%d", &num_con);

    for(i = 0; i < num_pro; i++) {
        p[i] = i + 1;
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&p[i]);
    }
    for(i = 0; i < num_con; i++) {
        c[i] = i + 1;
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&c[i]);
    }

    for(i = 0; i < num_pro; i++)
        pthread_join(pro[i], NULL);
    for(i = 0; i < num_con; i++)
        pthread_join(con[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\n\nAll producer and consumer threads have finished.\n");
}
