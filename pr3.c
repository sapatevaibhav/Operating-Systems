#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void SJF_Preemptive(Process processes[], int n);
void RoundRobin(Process processes[], int n, int timeQuantum);
void calculateWaitingTurnaroundTime(Process processes[], int n);

int main()
{
    int n, i, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &timeQuantum);

    printf("\n--- Shortest Job First (Preemptive) ---\n");
    SJF_Preemptive(processes, n);
    calculateWaitingTurnaroundTime(processes, n);

    printf("\n--- Round Robin ---\n");
    RoundRobin(processes, n, timeQuantum);
    calculateWaitingTurnaroundTime(processes, n);

    printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    return 0;
}

void SJF_Preemptive(Process processes[], int n)
{
    int currentTime = 0;
    int completed = 0;

    while (completed != n)
    {
        int shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime > 0)
            {
                if (shortest == -1 || processes[i].remainingTime < processes[shortest].remainingTime)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++;
        }
        else
        {
            processes[shortest].remainingTime--;
            currentTime++;
            if (processes[shortest].remainingTime == 0)
            {
                completed++;
                processes[shortest].turnaroundTime = currentTime - processes[shortest].arrivalTime;
            }
        }
    }
}

void RoundRobin(Process processes[], int n, int timeQuantum)
{
    int currentTime = 0;
    int completed = 0;
    int front = 0, rear = 0;
    Process *queue = (Process *)malloc(n * sizeof(Process));

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                queue[rear++] = processes[i];
            }
        }

        if (front == rear)
        {
            currentTime++;
        }
        else
        {
            Process current = queue[front];
            front = (front + 1) % n;
            if (current.remainingTime <= timeQuantum)
            {
                currentTime += current.remainingTime;
                current.remainingTime = 0;
                completed++;
                current.turnaroundTime = currentTime - current.arrivalTime;
            }
            else
            {
                currentTime += timeQuantum;
                current.remainingTime -= timeQuantum;
            }
        }
    }

    free(queue);
}

void calculateWaitingTurnaroundTime(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}
