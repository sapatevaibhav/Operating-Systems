#include <stdio.h>

struct Process
{
    char name[3];
    int arrival_time, burst_time, wait_time, turnaround_time, remaining_time;
};

int main()
{
    int num_processes, quantum, total_wait_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    struct Process processes[num_processes];

    for (int i = 0; i < num_processes; i++)
    {
        printf("Enter process name, arrival time, and burst time for process %d: ", i + 1);
        scanf("%s %d %d", processes[i].name, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int total_remaining_time = 0, current_time = 0;

    // Initialize the total_remaining_time variable
    for (int i = 0; i < num_processes; i++)
    {
        total_remaining_time += processes[i].remaining_time;
    }

    do
    {
        for (int i = 0; i < num_processes; i++)
        {
            struct Process *p = &processes[i];
            if (p->remaining_time > 0)
            {
                int execute_time = (p->remaining_time > quantum) ? quantum : p->remaining_time;
                p->remaining_time -= execute_time;
                current_time += execute_time;

                total_remaining_time -= execute_time;

                if (p->remaining_time == 0)
                {
                    p->turnaround_time = current_time - p->arrival_time;
                    p->wait_time = p->turnaround_time - p->burst_time;
                }
            }
        }
    } while (total_remaining_time > 0);

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\n", processes[i].name, processes[i].arrival_time, processes[i].burst_time, processes[i].wait_time, processes[i].turnaround_time);

        total_wait_time += processes[i].wait_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Average wait time: %.2f\n", (float)total_wait_time / num_processes);
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time / num_processes);

    return 0;
}
