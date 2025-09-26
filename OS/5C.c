#include<stdio.h>
int main()
{
    int i, j, nop, tbt = 0, twt = 0, ttt = 0;
    int b[20], wt[20], tt[20], pid[20], temp;
    float awt, att;

    printf("Enter no.of Processes: ");
    scanf("%d", &nop);

    printf("Enter the Burst times..\n");
    for(i = 0; i < nop; i++)
    {
        printf("P%d\t:", i + 1);
        scanf("%d", &b[i]);
        pid[i] = i + 1;
        wt[i] = tt[i] = 0;
        tbt += b[i];
    }

    // Sort burst times and process IDs for SJF
    for(i = 0; i < nop - 1; i++)
    {
        for(j = i + 1; j < nop; j++)
        {
            if(b[i] > b[j])
            {
                temp = b[i]; b[i] = b[j]; b[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    wt[0] = 0;
    tt[0] = b[0];
    for(i = 1; i < nop; i++)
    {
        wt[i] = wt[i-1] + b[i-1];
        tt[i] = wt[i] + b[i];
    }

    printf("\n\tGantt Chart");
    printf("\nProcessID \t From Time\tTo Time\n");
    int from = 0;
    for(i = 0; i < nop; i++)
    {
        printf("%7d%15d%15d\n", pid[i], from, from + b[i]);
        from += b[i];
    }

    for(i = 0; i < nop; i++)
    {
        twt += wt[i];
        ttt += tt[i];
    }

    printf("\n\nProcess ID\tWaiting Time\tTurn Around Time");
    for(i = 0; i < nop; i++)
    {
        printf("\n\t%d\t\t%d\t\t%d", pid[i], wt[i], tt[i]);
    }

    awt = (float)twt / (float)nop;
    att = (float)ttt / (float)nop;

    printf("\nTotal Waiting Time:%d", twt);
    printf("\nTotal TurnAround Time:%d", ttt);
    printf("\nAverage Waiting Time:%.2f", awt);
    printf("\nAverage Turn Around Time:%.2f\n", att);

    return 0;
}

