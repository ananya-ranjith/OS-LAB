#include <stdio.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main() {

    int n, i, j;
    int c_time = 0;
    int total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n], temp;

    for(i = 0; i < n; i++) {
        printf("Enter AT and BT for process %d: ", i+1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }


    for(i = 0; i < n; i++) {

        if(c_time < p[i].at)
            c_time = p[i].at;

        p[i].ct = c_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        c_time = p[i].ct;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage WT = %.2f", (float)total_wt/n);
    printf("\nAverage TAT = %.2f\n", (float)total_tat/n);

    return 0;
}
