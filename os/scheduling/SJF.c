#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at, bt;
    int ct, tat, wt, rt;
    bool done;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = false;
    }

    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    while (completed < n) {
        int idx = -1;
        int mn = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].bt < mn) {
                mn = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].rt = time - p[idx].at;

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        totalTAT += p[idx].tat;
        totalWT += p[idx].wt;
        totalRT += p[idx].rt;

        p[idx].done = true;
        completed++;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
    printf("Average Response Time = %.2f\n", totalRT / n);

    return 0;
}
