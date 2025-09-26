#include<stdio.h>
int main()
{
    int i, nop, tbt = 0, twt = 0, ttt = 0;
    int b[20], wt[20], tt[20];
    float awt, att;

    printf("Enter no.of Processes: ");
    scanf("%d", &nop);

    printf("Enter the Burst times..\n");
    for(i = 0; i < nop; i++)
    {
        wt[i] = tt[i] = 0;
        printf("P%d\t:", i + 1);
        scanf("%d", &b[i]);
        tbt += b[i];
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
        printf("%7d%15d%15d\n", i+1, from, from + b[i]);
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
        printf("\n\t%d\t\t%d\t\t%d", i+1, wt[i], tt[i]);
    }

    awt = (float)twt / (float)nop;
    att = (float)ttt / (float)nop;

    printf("\nTotal Waiting Time:%d", twt);
    printf("\nTotal TurnAround Time:%d", ttt);
    printf("\nAverage Waiting Time:%.2f", awt);
    printf("\nAverage Turn Around Time:%.2f\n", att);

    return 0;
}

// OUTPUT
// Enter no.of Processes: 4
// Enter the Burst times..
// P1	:3
// P2	:5
// P3	:2
// P4	:7

// 	Gantt Chart
// ProcessID 	 From Time	To Time
//       1              0              3
//       2              3              8
//       3              8             10
//       4             10             17


// Process ID	Waiting Time	Turn Around Time
// 	1		0		3
// 	2		3		8
// 	3		8		10
// 	4		10		17
// Total Waiting Time:21
// Total TurnAround Time:38
// Average Waiting Time:5.25
// Average Turn Around Time:9.50
