
#include <stdio.h>

int main() {
    int n, m;
    int allocation[10][10], max[10][10];
    int need[10][10], available[10];
    int finish[10] = {0}, safeSeq[10];
    int work[10], count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    if (n < 1 || n > 10 || m < 1 || m > 10) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
        if (available[j] < 0) {
            printf("Invalid input.\n");
            return 1;
        }
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (allocation[i][j] < 0 ||
                max[i][j] < allocation[i][j]) {
                printf("Invalid allocation or maximum.\n");
                return 1;
            }
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int possible = 1;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i < n - 1)
                printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    return 0;
}