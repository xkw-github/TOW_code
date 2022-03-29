#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#define pause_x				30								//11.5
#define pause_t				0.16							//0.23
#define reverse_x			30								//11.5


int main() {
	int i,j,k,num=0;
	double t[30000],x[30000],x0,t0;
	double txt[50000];
	double run_plus=0,run_minus=0,plus=0,minus=0;
	double run[300000]={0},tau[300000]={0};
	freopen("./output.txt","w",stdout);
	FILE *fp;
	fp=fopen("./run.txt","r");
	i=0;
	while(fscanf(fp, "%lf", &txt[i]) != EOF)
				{i++;
				if(i>13)		break;}
	double l1=txt[0],l2=txt[1],l3=txt[2],l4=txt[3],l5=txt[4],l6=txt[5],l7=txt[6];
	double l8=txt[7],l9=txt[8],l10=txt[9],l11=txt[10],l12=txt[11],l13=txt[12],l14=txt[13];



	for(k=0;k<200;k++){
		i=0;
		while(fscanf(fp, "%lf", &txt[i]) != EOF)
			{i++;
			if(i>=20000)		break;}
		for(i=0;i<20000;i++){
			t[i]=txt[2*i];x[i]=txt[2*i+1];}
		for(i=1;i<20000;i++){
			if((x[i]-x[i-1])*(x[i+1]-x[i]) > 0){
				run[num]+=x[i]-x[i-1];tau[num]+=t[i]-t[i-1];
				x0+=x[i]-x[i-1];t0+=t[i]-t[i-1];
				if(t0>pause_t){
					if(fabs(x0)<pause_x){
						if(tau[num]>t0)		{run[num]-=x0;tau[num]-=t0;}
						run[num+1]=x0;tau[num+1]=t0;
						num=num+2;}																						//record pause
				x0=0;t0=0;}
			}
			else{
				if(fabs(run[num])<=reverse_x && tau[num]<pause_t){
					num--;
					run[num]+=run[num+1];tau[num]+=tau[num+1];
					run[num+1]=0;tau[num+1]=0;
				}
				else
					num++;}
		}
	if(num>200000) break;
	}

	for(i=0;i<=num;i++){
		if(run[i]>pause_x	){			run_plus+=run[i];plus++;}
		if(run[i]<-pause_x	){		run_minus+=run[i];minus++;}}

	double long_s=0,long_t=0,short_s=0,short_t=0;
	double long_velcoity_plus,short_velcoity_plus,long_velcoity_minus,short_velcoity_minus;
	long_s=0;long_t=0;short_s=0;short_t=0;
	for(i=1;i<num;i++){
		if(run[i]>0){
			if(run[i]>500 && run[i]<1000){														long_s+=fabs(run[i]);long_t+=tau[i];}
			if(run[i]>pause_x  && run[i]<100 ){											short_s+=fabs(run[i]);short_t+=tau[i];}}}
	long_velcoity_plus=long_s/long_t;short_velcoity_plus=short_s/short_t;
	long_s=0;long_t=0;short_s=0;short_t=0;
	for(i=1;i<num;i++){
		if(run[i]<0){
			if(run[i]<-500 && run[i]>-1000){														long_s+=fabs(run[i]);long_t+=tau[i];}
			if(run[i]<-pause_x  && run[i]>-100 ){											short_s+=fabs(run[i]);short_t+=tau[i];}}}
	long_velcoity_minus=long_s/long_t;short_velcoity_minus=short_s/short_t;


	printf("Vfp=%.0f\t\tVfm=%.0f\ngamma0p=%.2f\tgamma0m=%.2f\n",l1,l2,l3,l4);
	printf("Fsp=%.1f\t\tFsm=%.1f\nFdp=%.2f\t\tFdm=%.2f\n",l5,l6,l7,l8);
	printf("pip=%.2f\t\tpim=%.2f\nVbp=%.0f\t\tVbm=%.0f\n\n",l11,l12,l13,l14);
	printf("plus velocity of short run =%lf\nminus velocity of short run=%lf\n",short_velcoity_plus,short_velcoity_minus);
	printf("plus velocity of long  run =%lf\nminus velocity of long  run=%lf\n\n",long_velcoity_plus,long_velcoity_minus);

	printf("runlength  plus=%lf\nrunlength minus=%lf\n\n",run_plus/plus,run_minus/minus);


}
