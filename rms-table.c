#include <stdio.h>

struct Process {
    int id, period, burst, remaining, next_arrival;
};

int main() {
    int n, time, hyper = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        printf("Process %d (Burst Time, Period): ", i+1);
        scanf("%d %d", &p[i].burst, &p[i].period);

        p[i].remaining = p[i].burst;
        p[i].next_arrival = 0;
        p[i].id = i + 1;

        if(p[i].period > hyper)
            hyper = p[i].period;
    }

    printf("\nRMS Scheduling Table:\n");
    printf("Time\tRunning\t");

    for(int i = 0; i < n; i++)
        printf("P%d_rem\t", p[i].id);

    printf("\n--------------------------------------------------\n");

    for(time = 0; time < hyper * 2; time++) {

        int highest = -1;

        for(int i = 0; i < n; i++) {

            if(time == p[i].next_arrival) {
                p[i].remaining = p[i].burst;
                p[i].next_arrival += p[i].period;
            }

            if(p[i].remaining > 0) {
                if(highest == -1 || p[i].period < p[highest].period)
                    highest = i;
            }
        }

        printf("%d\t", time);

        if(highest != -1) {
            printf("P%d\t", p[highest].id);
            p[highest].remaining--;
        } else {
            printf("Idle\t");
        }

        for(int i = 0; i < n; i++)
            printf("%d\t", p[i].remaining);

        printf("\n");
    }

    return 0;
}