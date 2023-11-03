// Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) and Round Robin with different arrival time.
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct Process
{
    int id, arrival_time, burst_time, remaining_burst_time;
} Process;

Process processes[MAX_PROCESSES];
int ready_queue[MAX_PROCESSES];
int head = 0, tail = 0;
int current_time = 0;

void sort_processes_by_arrival_time()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        for (int j = i + 1; j < MAX_PROCESSES; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void add_to_ready_queue(int process_id)
{
    ready_queue[tail++] = process_id;
}

int remove_from_ready_queue()
{
    return ready_queue[head++];
}
void schedule_processes_using_SJF_preemptive(int total_processes)
{
    int completion_time[MAX_PROCESSES], waiting_time[MAX_PROCESSES], turnaround_time[MAX_PROCESSES];

    for (int i = 0; i < total_processes; i++)
    {
        completion_time[i] = 0;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    int remaining_processes = total_processes;
    int current_process = -1;
    int shortest_job_id = -1;

    while (remaining_processes > 0)
    {

        for (int i = 0; i < total_processes; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0)
            {
                if (current_process == -1 || processes[i].remaining_burst_time < processes[current_process].remaining_burst_time)
                {
                    current_process = i;
                }
            }
        }

        if (current_process == -1)
        {
            current_time++;
        }
        else
        {

            processes[current_process].remaining_burst_time--;
            current_time++;

            if (processes[current_process].remaining_burst_time == 0)
            {
                completion_time[current_process] = current_time;
                turnaround_time[current_process] = completion_time[current_process] - processes[current_process].arrival_time;
                waiting_time[current_process] = turnaround_time[current_process] - processes[current_process].burst_time;
                remaining_processes--;
                current_process = -1;
            }
        }
    }

    printf("SJF Schedule:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for (int i = 0; i < total_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, turnaround_time[i], waiting_time[i], completion_time[i]);
    }
    float avg_waiting_time = 0.0;
    float avg_turnaround_time = 0.0;
    for (int i = 0; i < total_processes; i++)
    {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= total_processes;
    avg_turnaround_time /= total_processes;

    printf("\nAverage waiting time: %f\nAverage turnaround time: %f\n", avg_waiting_time, avg_turnaround_time);
}
void schedule_processes_using_RR(int time_quantum, int total_processes)
{

    int completion_time[MAX_PROCESSES] = {0};
    int waiting_time[MAX_PROCESSES] = {0};
    int turnaround_time[MAX_PROCESSES] = {0};
    int remaining_burst_time[MAX_PROCESSES];
    int current_time = 0;
    for (int i = 0; i < total_processes; i++)
    {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int current_process = 0;

    while (true)
    {

        int remaining_processes = 0;
        for (int i = 0; i < total_processes; i++)
        {
            if (remaining_burst_time[i] > 0)
            {
                remaining_processes++;
            }
        }
        if (remaining_processes == 0)
        {
            break;
        }

        int execute_time = (remaining_burst_time[current_process] < time_quantum)
                               ? remaining_burst_time[current_process]
                               : time_quantum;
        remaining_burst_time[current_process] -= execute_time;
        current_time += execute_time;

        if (remaining_burst_time[current_process] == 0)
        {
            completion_time[current_process] = current_time;
            turnaround_time[current_process] = completion_time[current_process] - processes[current_process].arrival_time;
            waiting_time[current_process] = turnaround_time[current_process] - processes[current_process].burst_time;
        }

        current_process = (current_process + 1) % total_processes;
    }

    printf("Round Robin Schedule:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for (int i = 0; i < total_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, turnaround_time[i], waiting_time[i], completion_time[i]);
    }

    float avg_waiting_time = 0.0;
    float avg_turnaround_time = 0.0;
    for (int i = 0; i < total_processes; i++)
    {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= total_processes;
    avg_turnaround_time /= total_processes;

    printf("\nAverage waiting time: %f\nAverage turnaround time: %f\n", avg_waiting_time, avg_turnaround_time);
}

int main()
{
    printf("Enter the number of processes: ");
    int pcs;
    scanf("%d", &pcs);
    printf("Enter id, arrival time, burst time for each process\n");

    for (int i = 0; i < pcs; i++)
    {
        printf("For process %d : ", i);
        scanf("%d%d%d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_burst_time = processes[i].burst_time;
        add_to_ready_queue(processes[i].id);
        printf("\n");
    }

    schedule_processes_using_SJF_preemptive(pcs);

    head = 0;
    tail = 0;

    for (int i = 0; i < pcs; i++)
    {
        processes[i].remaining_burst_time = processes[i].burst_time;
        add_to_ready_queue(processes[i].id);
    }

    schedule_processes_using_RR(2, pcs);

    return 0;
}
