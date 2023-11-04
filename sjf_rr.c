// Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) and Round Robin with different arrival time.
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct Process
{
    int id, arrival_time, bt, rt;
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
void schedule_processes_using_SJF_preemptive(int tp)
{
    int ct[MAX_PROCESSES], wt[MAX_PROCESSES], tat[MAX_PROCESSES];

    for (int i = 0; i < tp; i++)
    {
        ct[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    int rp = tp;
    int cp = -1;
    int shortest_job_id = -1;

    while (rp > 0)
    {

        for (int i = 0; i < tp; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].rt > 0)
            {
                if (cp == -1 || processes[i].rt < processes[cp].rt)
                {
                    cp = i;
                }
            }
        }

        if (cp == -1)
        {
            current_time++;
        }
        else
        {

            processes[cp].rt--;
            current_time++;

            if (processes[cp].rt == 0)
            {
                ct[cp] = current_time;
                tat[cp] = ct[cp] - processes[cp].arrival_time;
                wt[cp] = tat[cp] - processes[cp].bt;
                rp--;
                cp = -1;
            }
        }
    }

    printf("SJF Schedule:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for (int i = 0; i < tp; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].bt, tat[i], wt[i], ct[i]);
    }
    float avg_wt = 0.0;
    float avg_tat = 0.0;
    for (int i = 0; i < tp; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= tp;
    avg_tat /= tp;

    printf("\nAverage waiting time: %f\nAverage turnaround time: %f\n", avg_wt, avg_tat);
}
void schedule_processes_using_RR(int time_quantum, int tp)
{

    int ct[MAX_PROCESSES] = {0};
    int wt[MAX_PROCESSES] = {0};
    int tat[MAX_PROCESSES] = {0};
    int rt[MAX_PROCESSES];
    int current_time = 0;
    for (int i = 0; i < tp; i++)
    {
        rt[i] = processes[i].bt;
    }

    int cp = 0;

    while (true)
    {

        int rp = 0;
        for (int i = 0; i < tp; i++)
        {
            if (rt[i] > 0)
            {
                rp++;
            }
        }
        if (rp == 0)
        {
            break;
        }

        int execute_time = (rt[cp] < time_quantum)
                               ? rt[cp]
                               : time_quantum;
        rt[cp] -= execute_time;
        current_time += execute_time;

        if (rt[cp] == 0)
        {
            ct[cp] = current_time;
            tat[cp] = ct[cp] - processes[cp].arrival_time;
            wt[cp] = tat[cp] - processes[cp].bt;
        }

        cp = (cp + 1) % tp;
    }

    printf("\nRound Robin Schedule:\n");
    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for (int i = 0; i < tp; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].bt, tat[i], wt[i], ct[i]);
    }

    float avg_wt = 0.0;
    float avg_tat = 0.0;
    for (int i = 0; i < tp; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= tp;
    avg_tat /= tp;

    printf("\nAverage waiting time: %f\nAverage turnaround time: %f\n", avg_wt, avg_tat);
}

int main()
{
    printf("Enter the number of processes: ");
    int pcs, tq;
    scanf("%d", &pcs);
    printf("Enter id, arrival time, burst time for each process\n");

    for (int i = 0; i < pcs; i++)
    {
        printf("For process %d : ", i);
        scanf("%d%d%d", &processes[i].id, &processes[i].arrival_time, &processes[i].bt);
        processes[i].rt = processes[i].bt;
        add_to_ready_queue(processes[i].id);
    }
    printf("Enter the time Quantum for RR: ");
    scanf("%d", &tq);
    schedule_processes_using_SJF_preemptive(pcs);

    head = 0;
    tail = 0;

    for (int i = 0; i < pcs; i++)
    {
        processes[i].rt = processes[i].bt;
        add_to_ready_queue(processes[i].id);
    }

    schedule_processes_using_RR(tq, pcs);

    return 0;
}
