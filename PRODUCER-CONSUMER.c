#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 2
int mutex=1;
int full=0;
int empty=BUFFER_SIZE;
int buffer[BUFFER_SIZE];
int in=0,out=0;
int wait(int s) {
    return --s;
}
int signal(int s) {
    return ++s;
}
void producer() {
    if ((mutex==1) && (empty!=0)) {
        mutex=wait(mutex);
        empty=wait(empty);
        int item=rand()%100;
        buffer[in]=item;
        printf("Produced: %d\n", item);
        in=(in + 1)%BUFFER_SIZE;
        mutex=signal(mutex);
        full=signal(full);
    } else {
        printf("Buffer overflow\n");
    }
}
void consumer() {
    if ((mutex==1) && (full!=0)) {
        mutex=wait(mutex);
        full=wait(full);
        int item=buffer[out];
        printf("Consumed: %d\n", item);
        out=(out + 1) % BUFFER_SIZE;
        mutex=signal(mutex);
        empty=signal(empty);
    } else {
        printf("Buffer underflow\n");
    }
}
int main() {
    int choice;
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}




