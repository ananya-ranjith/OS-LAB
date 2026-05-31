
#include <stdio.h>


struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};


void fcfs(struct Process p[], int n) {
    int i;


    p[0].waiting_time = 0;


    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }


    for (i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}


void display(struct Process p[], int n, char name[]) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\n%s Queue:\n", name);
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n",
               p[i].id,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n_sys, n_user, i;


    printf("Enter number of System Processes: ");
    scanf("%d", &n_sys);

    struct Process sys[n_sys];

    for (i = 0; i < n_sys; i++) {
        sys[i].id = i + 1;
        printf("Enter burst time for System Process P%d: ", sys[i].id);
        scanf("%d", &sys[i].burst_time);
    }


    printf("\nEnter number of User Processes: ");
    scanf("%d", &n_user);

    struct Process user[n_user];

    for (i = 0; i < n_user; i++) {
        user[i].id = i + 1;
        printf("Enter burst time for User Process P%d: ", user[i].id);
        scanf("%d", &user[i].burst_time);
    }


    fcfs(sys, n_sys);
    fcfs(user, n_user);


    int total_sys_time = 0;
    for (i = 0; i < n_sys; i++) {
        total_sys_time += sys[i].burst_time;
    }

    for (i = 0; i < n_user; i++) {
        user[i].waiting_time += total_sys_time;
        user[i].turnaround_time = user[i].waiting_time + user[i].burst_time;
    }


    printf("\n===== Multi-Level Queue Scheduling =====\n");

    display(sys, n_sys, "System (Higher Priority)");
    display(user, n_user, "User (Lower Priority)");

    return 0;
}
