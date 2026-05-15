#include <stdio.h>

typedef struct {
    int id;
    int capacity;  // Execution time
    int period;    // Interval between arrivals
    int deadline;  // Absolute deadline (dynamic)
    int remaining; // Remaining execution time in current period
} Task;

int main() {
    int n, total_time;
   
    printf("Enter number of tasks: ");
    scanf("%d", &n);
   
    Task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter Capacity and Period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].capacity, &tasks[i].period);
        tasks[i].deadline = tasks[i].period; // Initial deadline
        tasks[i].remaining = tasks[i].capacity;
    }

    printf("Enter total simulation time: ");
    scanf("%d", &total_time);

    printf("\n--- Scheduling Log ---\n");

    for (int t = 0; t < total_time; t++) {
        int selected_task = -1;
        int min_deadline = 9999;

        // Check each task to see which has the earliest deadline and needs work
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                if (tasks[i].deadline < min_deadline) {
                    min_deadline = tasks[i].deadline;
                    selected_task = i;
                }
            }
        }

        if (selected_task != -1) {
            printf("Time %d: Task %d is running\n", t, tasks[selected_task].id);
            tasks[selected_task].remaining--;

            // Task finished its work for this period
            if (tasks[selected_task].remaining == 0) {
                tasks[selected_task].deadline += tasks[selected_task].period;
                tasks[selected_task].remaining = tasks[selected_task].capacity;
                // Note: We "reset" it for the next period immediately
            }
        } else {
            printf("Time %d: CPU Idle\n", t);
        }
    }

    return 0;
}