#include<stdio.h>

int main(){
	int i,j,n,a[50],frame[10],no,k,avail,count=0;
	printf("\nENTER THE NUMBER OF PAGES:\n");
	scanf("%d",&n);
	printf("\nENTER THE PAGE NUMBER :\n");
	
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	printf("\nENTER THE NUMBER OF FRAMES :");
	scanf("%d",&no);
	
	for(i=0;i<no;i++){
		frame[i]= -1;
	}
	j=0;
	printf("\tpage number\t page frames\n");
	
	for(i=1;i<=n;i++){
		printf("%d\t\t",a[i]);
		avail=0;
		for(k=0;k<no;k++){
			if(frame[k]==a[i])
				avail=1;
		}
		if (avail==0){
			frame[j]=a[i];
			j=(j+1)%no;
			count++;
			for(k=0;k<no;k++)
				printf("%d\t",frame[k]);
		}
		printf("\n");
	}
	printf("Page Fault Is %d\n",count);
	return 0;
}


// OUTPUT:
// ENTER THE NUMBER OF PAGES:
// 5

// ENTER THE PAGE NUMBER :
// 4
// 1
// 2
// 3
// 4

// ENTER THE NUMBER OF FRAMES :5
// 	page number	 page frames
// 4		4	-1	-1	-1	-1	
// 1		4	1	-1	-1	-1	
// 2		4	1	2	-1	-1	
// 3		4	1	2	3	-1	
// 4		
// Page Fault Is 4
