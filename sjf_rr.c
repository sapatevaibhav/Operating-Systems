// Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) and Round Robin with different arrival time.

#include <stdio.h>
#include <stdbool.h>

    struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

void SJF(struct Process processes[], int n)
{
    int completion_time[n];
    int waiting_time[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
            {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int total_time = processes[0].arrival_time;
    for (int i = 0; i < n; i++)
    {
        if (total_time < processes[i].arrival_time)
        {
            total_time = processes[i].arrival_time;
        }
        total_time += processes[i].burst_time;
        completion_time[i] = total_time;
        waiting_time[i] = total_time - processes[i].arrival_time - processes[i].burst_time;
        processes[i].turnaround_time = total_time - processes[i].arrival_time;
        processes[i].waiting_time = waiting_time[i];
    }

    float total_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, waiting_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
}

void RR(struct Process processes[], int n, int time_quantum)
{
    int total_time = 0;
    int remaining_processes = n;
    int current_process = 0;

    while (remaining_processes > 0)
    {
        if (processes[current_process].remaining_time > 0)
        {
            int execute_time = (processes[current_process].remaining_time < time_quantum)
                                   ? processes[current_process].remaining_time
                                   : time_quantum;

            processes[current_process].remaining_time -= execute_time;
            total_time += execute_time;

            if (processes[current_process].remaining_time == 0)
            {
                remaining_processes--;
                processes[current_process].turnaround_time = total_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
            }

            do
            {
                current_process = (current_process + 1) % n;
            } while (processes[current_process].remaining_time == 0);
        }
        else
        {
            do
            {
                current_process = (current_process + 1) % n;
            } while (processes[current_process].remaining_time == 0);
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage wait time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main()
{
    int choice, n, time_quantum;
    printf("Choose scheduling algorithm:\n");
    printf("1. Shortest Job First (SJF)\n");
    printf("2. Round Robin (RR)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    if (choice == 1)
    {
        printf("Shortest Job First (SJF) Scheduling:\n");
        SJF(processes, n);
    }
    else if (choice == 2)
    {
        printf("Enter the time quantum: ");
        scanf("%d", &time_quantum);
        printf("Round Robin (RR) Scheduling:\n");
        RR(processes, n, time_quantum);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
