 #include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8


int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;


int totalItems;


sem_t empty;
sem_t full;


pthread_mutex_t mutex;


int produceItem(int item)
{
    return item;
}


void consumeItem(int item)
{
    printf("Consumed Item: %d\n", item);
}


void* producer(void* arg)
{
    int item;

    for (int i = 1; i <= totalItems; i++)
    {
        item = produceItem(i);

        
        sem_wait(&empty);

        
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Producer produced %d at position %d\n", item, in);

        in = (in + 1) % BUFFER_SIZE;

        
        pthread_mutex_unlock(&mutex);

        
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}


void* consumer(void* arg)
{
    int item;

    for (int i = 1; i <= totalItems; i++)
    {
        
        sem_wait(&full);

        
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed %d from position %d\n", item, out);

        out = (out + 1) % BUFFER_SIZE;

        
        pthread_mutex_unlock(&mutex);

        
        sem_post(&empty);

        consumeItem(item);

        sleep(1);
    }

    pthread_exit(NULL);
}


void initialize()
{
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);
}


void destroy()
{
    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);
}


int main()
{
    pthread_t producerThread;
    pthread_t consumerThread;

    printf("Enter number of items to produce: ");
    scanf("%d", &totalItems);

    
    initialize();

    
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

   
    destroy();

    printf("\nProducer-Consumer Execution Completed\n");

    return 0;
}

