#include<stdio.h> 

int main() { 
    int i,tbt=0,nop,ts=0,flag[20],rem[20]; 
    int from,wt[20],tt[20],b[20],twt=0,ttt=0; 
    int dur; 
    float awt, att; 
    printf("Enter no.of Processes: "); 
    scanf("%d",&nop); 
    printf("Enter the time slice: "); 
    scanf("%d",&ts); 
    printf("Enter the Burst times..\n"); 
    for(i=0;i<nop;i++) { 
        wt[i]=tt[i]=0;     
        printf("P%d\t:",i+1); 
        scanf("%d",&b[i]);  // Reading Burst Time 
        rem[i]=b[i];        
// Store the Burst Time in rem array      
        tbt+=b[i];          
        flag[i]=0;          
    } 
    from=0; 
    i=0; 
    // Total Burst Time 
    // used to check whether the process has remaining burst time or not 
    printf("\n\tGantt Chart"); 
    printf("\nProcessID \t From Time\tTo Time\n"); 
    while(from<tbt){ 
        if(!flag[i]){   //true only when process has burst time  
            if(rem[i]<=ts){ //burst time should be equal or less than time slice  
 
                dur=rem[i];  
                flag[i]=1;          
                // make the value false 
                tt[i]=dur+from;  
                wt[i]=tt[i]-b[i];  // subtract  
            } 
            else 
              dur=ts; 
            printf("%7d%15d%15d\n",i+1,from,from+dur); 
            rem[i]= rem[i]-dur;  
            from = from+dur;  
        } 
        i=(i+1)%nop;    
    } 
    for(i=0;i<nop;i++) { 
        twt+=wt[i]; 
        ttt+=tt[i]; 
    } 
    printf("\n\nProcess ID\tWaiting Time\tTurn Around Time"); 
    for(i=0;i<nop;i++) { 
        printf("\n\t%d\t\t%d\t\t%d",i+1,wt[i],tt[i]); 
    } 
    awt=(float)twt/(float)nop; 
    att=(float)ttt/(float)nop; 
    printf("\nTotal Waiting Time:%d",twt); 
    printf("\nTotal TurnAround Time:%d",ttt); 
    printf("\nAverage Waiting Time:%.2f",awt); 
    printf("\nAverage Turn Around Time:%.2f\n",att); 
    return 0; 
} 

// OUTPUT

// Enter no.of Processes: 3
// Enter the time slice: 2
// Enter the Burst times..
// P1   :5
// P2   :3
// P3   :1
//     Gantt Chart
// ProcessID       From Time       To Time
//       1              0              2
//       2              2              4
//       3              4              5
//       1              5              7
//       2              7              8
//       1              8             11


// Process ID      Waiting Time    Turn Around Time
//         1              6              11
//         2              5               8
//         3              4               5
// Total Waiting Time:15
// Total TurnAround Time:24
// Average Waiting Time:5.00
// Average Turn Around Time:8.00
