#include<stdio.h>
#include<conio.h>
int main()
{
	int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
	printf("Enter total process (max20):");
	scanf("%d",&n);
	printf("\n Enter process burst time\n");
	for(i=0;i<n;i++)
	{
		printf("P[%d]:",i+1);
		scanf("%d",&bt[i]);
	}
	wt[0]=0;		//wt. time for first process 0
	for(i=1;i<n;i++)
	{
		wt[i]=0;
		for(j=0;j<i;j++)
			wt[i]+=bt[j];
	}
	printf("\n Process\t\t Burst Time \t Waiting Time \t Turnaround Time");
	for(i=0;i<n;i++)
	{
		tat[i]=bt[i]+wt[i];
		avwt+=wt[i];
		avtat+=tat[i];
		printf("nP[%d]\t\t %d \t\t %d \t\t %d",i+1,bt[i],wt[i],tat[i]);
	}
	avwt/=i;
	avtat/=i;
	printf("\n\n Avarage waiting time:%d",avwt);
	printf("\n Average turnaround time:%d",avtat);
	getch();
}
