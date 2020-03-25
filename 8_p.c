#include<stdio.h>
#include<stdbool.h>
#include<math.h>
void init_queue(int arr[], int n);
void init_t(int arr[], int n);
bool check_completion(int R_BT[], int n);
int main(){
	bool complete = false;
	int n = 6; //number of processes -> 6 + 1 -> 1 for idle process
	int process[] = {1,2,3,4,5,6};
	int priority[] = {40, 30, 30, 35, 5, 10};
	int burst[] = {20, 25, 25, 15, 10, 10};
	int R_BT[] = {20, 25, 25, 15, 10, 10};
	int arrival[] = {0, 25, 30, 60, 100, 105};
	
	int competing_process[10];
	init_queue(competing_process, 10);
	int tq = 5; //time quantum

	int WT[n], TAT[n], CT[n], temp_ct[20];
	int pq[50], time=0, selected_process=0;
	int temp_ct_count=0;
	init_queue(pq, 50);
	init_t(WT,n);init_t(TAT,n);init_t(CT,n);init_t(temp_ct,20);
	while(complete != true){
		recheck:
		if(check_completion(R_BT, n)){
			complete=true;
			break;
		}
		for(int i=0; i<n; i++){ //repeat for each process R_BT
			//for p1 no priority check as none arrives at 0
			if(R_BT[i]==0){continue;}
			if(arrival[i] > time){time +=(arrival[i]-time); //printf(":IDLE:");
				break;}
			else if(R_BT[i] > tq){
				time += tq;
				R_BT[i] -= tq;
				//printf("--%d--",process[i]);
				goto recheck;
			}
			//else if(arrival[i] > time){time +=tq;printf("abcd");continue;}
			else{
				R_BT[i] = 0;
				time += tq;
				CT[i] = time;
				temp_ct[temp_ct_count] = process[i];
				temp_ct_count++;
			}
			//check priority
			//if process arrives time-10 upto time then compare priorities
			//if()
		}

	}
	for(int i=0; i<20 ;i++){
		//printf("%d ",temp_ct[i]);
	}
	//printf("\nCT\n");
	for(int i=0; i<n; i++){
		TAT[i] = CT[i]-arrival[i];
		WT[i] = TAT[i]-burst[i];
	}
	printf("%10s %10s %10s %10s","Process","TAT", "WT", "CT\n");
	int sum_wt=0;
	for(int i=0; i<n; i++){
		printf("%10d %10d %10d %10d\n",process[i], TAT[i], WT[i], CT[i]);
		sum_wt += WT[i];
	}
	printf("\n\n");
	for(int i=0; i<n; i++){
		printf("----P[%d]----", process[i]);
	}
	printf("\n");
	for(int i=0; i<n; i++){
		printf("         %d ",CT[i]);
	}
	printf("\n\n");
	printf("Avg. Waiting time: %.2f\n",sum_wt/(float)n);
	double CPU_RATE;
	double avg_wt;
	avg_wt = (sum_wt/(double)n);
	double avg_wtp;
	avg_wtp = (avg_wt/10)*100;
	CPU_RATE = pow(avg_wt,(double)n);
	//cpu rate
	printf("CPU utilization rate: %.2f\n",CPU_RATE);
	
	return 0;
}
bool check_completion(int R_BT[], int n){
	bool completed = true;
	for(int i=0; i<n; i++){
		if(R_BT[i]>0){
			completed = false;
		}
	}
	return completed;
}
void init_queue(int arr[], int n){
	for(int i=0; i<n; i++){arr[i]=-1;}
}
void init_t(int arr[], int n){
	for(int i=0; i<n; i++){arr[i]=0;}
}
