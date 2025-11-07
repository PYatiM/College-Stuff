#include <stdio.h>
#include <stdlib.h>

int main() {
    int Max[10][10], need[10][10], alloc[10][10], avail[10];
    int completed[10], safeSequence[10];
    int p, r, i, j, process, count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    // Initialize completed array
    for (i = 0; i < p; i++)
        completed[i] = 0;

    // Input Max matrix
    printf("\nEnter the Max matrix for each process:\n");
    for (i = 0; i < p; i++) {
        printf("For process %d: ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &Max[i][j]);
    }

    // Input Allocation matrix
    printf("\nEnter the Allocation matrix for each process:\n");
    for (i = 0; i < p; i++) {
        printf("For process %d: ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    }

    // Input Available resources
    printf("\nEnter the Available resources:\n");
    for (i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix = Max - Allocation
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            need[i][j] = Max[i][j] - alloc[i][j];
        }
    }

    // Main loop to find safe sequence or detect deadlock
    do {
        process = -1;

        for (i = 0; i < p; i++) {
            if (!completed[i]) {
                int can_run = 1;
                for (j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        can_run = 0;
                        break;
                    }
                }

                if (can_run) {
                    process = i;
                    break;
                }
            }
        }

        if (process != -1) {
            printf("\nProcess %d runs to completion!\n", process + 1);
            safeSequence[count++] = process + 1;
            completed[process] = 1;

            for (j = 0; j < r; j++) {
                avail[j] += alloc[process][j];
                alloc[process][j] = 0;
                Max[process][j] = 0;
            }
        }
    } while (count < p && process != -1);

    if (count == p) {
        printf("\n✅ The system is in a SAFE state.\nSafe sequence: < ");
        for (i = 0; i < p; i++)
            printf("P%d ", safeSequence[i] - 1);
        printf(">\n");
    } else {
        printf("\n❌ The system is in an UNSAFE state.\n");
        printf("Deadlocked processes: ");
        for (i = 0; i < p; i++) {
            if (!completed[i])
                printf("P%d ", i);
        }
        printf("\n");
    }

    return 0;
}
