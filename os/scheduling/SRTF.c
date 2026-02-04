#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at, bt, ct;
    int tat, wt, rt;
    int remaining;
    bool started;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
        p[i].started = false;
    }
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    while (completed < n) {
        int idx = -1;
        int mn = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0 &&
                p[i].remaining < mn) {
                mn = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        if (!p[idx].started) {
            p[idx].rt = time - p[idx].at;
            p[idx].started = true;
        }
        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
            totalRT += p[idx].rt;
        }
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
