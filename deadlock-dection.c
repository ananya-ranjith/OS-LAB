#include <stdio.h>

int main() {
    int n, m;

    // n = number of processes
    // m = number of resource types

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    int finish[n];

    
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    
    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

   
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    
    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int work[m];

    
    for(int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int found;

    
    do {
        found = 0;

        for(int i = 0; i < n; i++) {

            
            if(finish[i] == 0) {

                int canExecute = 1;

                
                for(int j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

               
                if(canExecute) {

                    
                    for(int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    finish[i] = 1;
                    found = 1;

                    printf("\nProcess P%d executed successfully.", i);
                }
            }
        }

    } while(found);

    
    int deadlock = 0;

    printf("\n\nDeadlocked Processes: ");

    for(int i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("None");
        printf("\nSystem is NOT in deadlock.");
    } else {
        printf("\nSystem IS in deadlock.");
    }

    return 0;
}