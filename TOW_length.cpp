#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define snap 									10000
#define seed 									1

int main() {
	int i;
	int Np,Nm,np,nm;
	double r1,r2,lam;
	double Fc,Vc,Fsp,Fsm,Fdp,Fdm,gammam,gammap,gamma0p,gamma0m,pip,pim,Vfp,Vfm,Vbm,Vbp;
	double l1,l2,l3,l4,l0,k1=0,k2=0;
	double tau,x,t;

	srand((int)time(NULL));
	freopen("./run.txt","w",stdout);

	Np  = 1;		             	Nm  = 6;
	Fsp = 6;			       	Fsm = 1.1;
	Fdp = 3;    				Fdm = 0.75;
	pip = 5;    				pim = 1.6;
	Vfp = 1000;    		        	Vfm = 650;
	Vbp = 6;   				Vbm = 72;
	gamma0p = 1;				gamma0m = 0.27;

	if(seed==1){
		printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",Vfp,Vfm,gamma0p,gamma0m,Fsp,Fsm,Fdp,Fdm);
		printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",k1,k2,pip,pim,Vbp,Vbm);}

	np=0;nm=0;
    for(i = 0;i < snap;i++){
        r1 = rand()/(double)(RAND_MAX);
        r2 = rand()/(double)(RAND_MAX);
        if(r1 == 0)    r1 = r1 + 0.000001;

        if(nm == 0)                    Fc = 0;
        else{
            if((np*Fsp) >= (nm*Fsm))
                {lam = 1/(1 + (np*Fsp*Vbm)/(nm*Fsm*Vfp));
                Fc = lam*np*Fsp + (1-lam)*nm*Fsm;}
            else
                {lam = 1/(1 + (np*Fsp*Vfm)/(nm*Fsm*Vbp));
                Fc = lam*np*Fsp + (1-lam)*nm*Fsm;}}

         if(np != 0)                  gammap = gamma0p*exp(Fc/(np*Fdp));
         else                         gammap = 0;
         if(nm != 0)                  gammam = gamma0m*exp(Fc/(nm*Fdm));
         else                         gammam = 0;

        //printf("%lf\t%lf\t%lf\t%lf\n",lam,Fc,gammap,gammam);

        l1 = gammap*np;                               //plus motor unbind
        l2 = pip*(Np-np);                             //plus motor bind
        l3 = gammam*nm;                               //minus motor unbind
        l4 = pim*(Nm-nm);                             //minus motor bind
        l0 = l1 + l2 + l3 + l4;

        if((r2 >= 0.0) && (r2 < l1/l0))
            np--;
        if((r2 >= l1/l0) && (r2 < (l1+l2)/l0))
            np++;
        if((r2 >= (l1+l2)/l0) && (r2 < (l1+l2+l3)/l0))
            nm--;
        if((r2 >= (l1+l2+l3)/l0) && (r2 < (l1+l2+l3+l4)/l0))
            nm++;

        if(nm == 0&&np == 0)              Vc = 0;
        else{
            if((np*Fsp) >= (nm*Fsm))      Vc = (np*Fsp-nm*Fsm)/(np*Fsp/Vfp+ nm*Fsm/Vbm);
            else                      		 Vc = (np*Fsp-nm*Fsm)/(np*Fsp/Vbm+ nm*Fsm/Vfm);}
//again
        if(nm == 0)                    		Fc = 0;
        else{
            if((np*Fsp) >= (nm*Fsm))
                {lam = 1/(1 + (np*Fsp*Vbm)/(nm*Fsm*Vfp));
                Fc = lam*np*Fsp + (1-lam)*nm*Fsm;}
            else
                {lam = 1/(1+ (np*Fsp*Vfm)/(nm*Fsm*Vbp));
                Fc = lam*np*Fsp+ (1-lam)*nm*Fsm;}}
         if(np!= 0)                    	gammap = gamma0p*exp(Fc/(np*Fdp));
         else                        		gammap = 0;
         if(nm!= 0)                  		gammam = gamma0m*exp(Fc/(nm*Fdm));
         else                        		gammam = 0;
        l1 = gammap*np;l2 = pip*(Np-np);l3 = gammam*nm;l4 = pim*(Nm-nm);
        l0 = l1 + l2 + l3 + l4;

        tau = (1.0/l0)*log(1.0/r1);
        x = x + tau*Vc;
        t  = t + tau;

        printf("%lf\t%lf\n",t,x);


    }












}
