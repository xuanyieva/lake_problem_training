/* LakeProblem_4Obj_1Const_Stoch.cpp

****This version is a monte carlo simulation for the natural flow given a manually specified control policy (e.g. ant_flow/vars)
which is loaded by the var.txt (Numbers * nDays).********
   
   Riddhi Singh, May, 2014
   The Pennsylvania State University
   rus197@psu.edu

   Adapted by Tori Ward, July 2014 
   Cornell University
   vlw27@cornell.edu
   
   Adapted by Xuan Yi, October 2014 
   Peking University
   xuanyi.eva@gmail.com

   A multi-objective represention of the lake model from Carpenter et al., 1999
   This simulation is designed for optimization with either Borg or the MOEA Framework.
   
   Stochasticity is introduced by:
   1. Natural variability around anthropogenic pollution flow, which is represented by an 
   SOW file.  SOW4.txt presents the known distribution (mean of 0.02 and log10(variance) of -5.5)
    and SOW6.txt presents a harsher distribution with a higher mean P level (0.03) 
    and more variability (log10(variance) of -5).  

	 Inputs 
   Parameters related to lake
      b : proportion of phosphorous retained in the lake each year    
      q : steepness of the sigmoid curve, large values give a steeper curve

   Parameters related to utility function
      delta   : discount rate
      alpha   : utility from pollution
      beta    : eutrophic cost

   State variables 
     lake_stateX : Phosphorous concentration at previous time step

   Decision Vector 
      ant_flow : anthropogenic pollution flow at previous time step ,=var (this was aval in R and MATLAB versions)

  Outputs
     Utility and discounted at a given time step
     utility : utility at every time step
     npv_util: discounted utility - this is also the objective function
     
     Updated lake_stateX 

 Objectives
 1. minimize the maximum Phosphorous averaged over all states of the world in a time period
 2. maximize expected benefit from pollution
 3. maximize Reliability
 4. maximize the probability of meeting an inertia constraint

Additional features:
1. Bounds for decision vector (0,0.1)
2. Precision - up to 3 digits
3. Annual control -100 total decision variables
*/


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;


//define input parameters;
#define PI      3.14159265358979323846
#define q 	    2
#define b 	    0.42
#define alpha   0.4
#define beta    0.08
#define delta   0.98
#define nDays   100
#define nSamples 100
#define Numbers 5

//define threshold
#define permit 0.5
#define reli_thes 0.85 //reliability>reli_thes
#define ine_thes -0.02 //why the change between steps should be >-0.02?


int nobjs=4;
int nvars=100;
int nconsts=1;
double nat_flowmat [10000][nDays]; //warning: 100*100  no stocha at first 




void lake_problem (double *vars,double *objs, double *consts)
{
 double * inter_objs1= new double [nDays];// intermediate of objective 1, time-vary (Phosphorous)
 double * inter_objs2= new double [nSamples]; //intermediate of objective 2, sample-vary(Benefit)
 double * inter_objs3= new double [nSamples]; //intermediate of objective 3, sample-vary(Reliability,Prob)
 double * inter_objs4= new double [nSamples]; //intermediate of objective 24 sample-vary(Interia, Prob)
 
 int i;
 int sample;
 
//initialization 
for (i=0;i<nDays;i++)
 {
     inter_objs1[i]=0.00;
 }
 
 for (sample=0;sample<nSamples;sample++)
  { 
     inter_objs2[sample]=0.00;
     inter_objs3[sample]=0.00;
	 inter_objs4[sample]=0.00;
  } 

//randomly choose 100 samples in 10000 natural flow samples;
  int lines[nSamples];
  srand (time(NULL));
 for (sample=0;sample <nSamples;sample++)
  {
     lines[sample] = rand()%10000;
  }
  int j=0;
 
       
   /*------------------------------------------------loop in each sample----------------------------------------------------------------------------*/  
for (sample=0;sample<nSamples;sample++)
  {
     double *nat_flow =new double [nDays];
	 double *ant_flow= new double [nDays];
	 double *lake_stateX=new double [nDays];
	 double *utility=new double [nDays]; //useless
	 double *benefit=new double [nDays];//in this section, the benefit(or objective) does not consider the environmental part

	 
	  //random select the nature flow from the nat_flowmat
     int index=lines[sample]; 
     for(i=0;i<nDays;i++)
	 {
        nat_flow[i]=nat_flowmat[index][i];
		
	 }
	 
      //initialization;
	 for (i=0;i<nDays;i++) 
	 {
	     lake_stateX[i]=0.00;
		 ant_flow[i]=vars[i]; //decision variable assignment
		 utility[i]=0.00;
		 benefit[i]=0.00;
	 } 
	 double intistateX=0.0;
      
      /*-------------------define the lake function-----------------------------------------------------*/
      for (i=0; i<nDays; i++)
	    {
	       if (i==0)
	        {
	          lake_stateX[i] = intistateX*(1-b)+pow(intistateX,q)/(1+pow(intistateX,q))+ant_flow[i]+nat_flow[i];
			  inter_objs1[i]=inter_objs1[i]+lake_stateX[i];  //average the sample's lake state each day.
			 }
	       else
	       {
	          lake_stateX[i] = lake_stateX[i-1]*(1-b)+(pow(lake_stateX[i-1], q))/(1+pow(lake_stateX[i-1],q))+ant_flow[i]+nat_flow[i];
			  inter_objs1[i]=inter_objs1[i]+lake_stateX[i];
	        }
			utility[i]=alpha*ant_flow[i]-beta*pow(lake_stateX[i],2);//useless in this model
			benefit[i]=alpha*ant_flow[i]; 
		}	 
		/*----------------------------lake function end ---------------------------------------------------*/
	 for (i=0;i<nDays;i++)
	    {
		   inter_objs2[sample]=inter_objs2[sample]+benefit[i]*pow(delta,i); //obj2.1 each sample's net benefit
		   if (lake_stateX[i]<permit)
		    inter_objs3[sample]++;         //obj3.1 < permit ,reliability
 
			   if(i>0)
			   {
			      if((vars[i]-vars[i-1])>ine_thes)
				  inter_objs4[sample]++;          //obj 4.1 > inertia threshold
				  }	 
	    }
	
	//clear memory	   
			   delete [] lake_stateX;
			   delete [] nat_flow;
			   delete [] ant_flow;
			   delete [] benefit;
			   delete [] utility;

	}

    double temper_objs1=-999;   //initialize the temper objectives
    double temper_objs2=0.0;
	double temper_objs3=0.0;
	double temper_objs4=0.0;
	
	
    for (i=0;i<nDays;i++)
    {
      inter_objs1[i]=inter_objs1[i]/nSamples;  // obj1.1 :mean samples' phosphorous
	 }
	for (i=0;i<nDays;i++)
	{
	  if(inter_objs1[i]>temper_objs1)
	   temper_objs1=inter_objs1[i];   //obj1.2 then find the maximum Phosphorous 
	 }
	   
	  for  (sample=0; sample<nSamples;sample++)
	  { 
	  temper_objs2=temper_objs2+inter_objs2[sample];
	  temper_objs3=temper_objs3+inter_objs3[sample];
	  temper_objs4=temper_objs4+inter_objs4[sample];
	  }
	  
	  objs[0]=temper_objs1;        //objective 1
	  temper_objs2=temper_objs2/nSamples; //obj2.2 mean benefit of the samples
	  objs[1]=temper_objs2;        //objective 2
	  
	  double reliability=temper_objs3/(nDays*nSamples); // obj3.2 probability
	  if (reliability>1)
	  exit(EXIT_FAILURE);
	  
	  objs[2]=reliability;               //objective 3
	  
	  if(reliability>reli_thes)  //constraint
	    { consts[0]=0.0;}
	  else
		{consts[0]=reli_thes-reliability;}
	  
	  
	  double pro_intertia_maintained=temper_objs4/((nSamples-1)*nDays); //obj 4.2
	  if (pro_intertia_maintained>1)
	  exit(EXIT_FAILURE);
	  else
	  objs[3]=pro_intertia_maintained;   //objective 4
	  
      objs[0]    =  objs[0];     //want to minimize phosphorous in the lake
    //  objs[1]    = -objs[1];     //want to maximize expected benefit from pollution
     // objs[2]    = -objs[2];     //want to maximize the probability of maintaining inertia (??warning will change when connect with borg)
     // objs[3]    = -objs[3];     //want to maximize reliability
	  
	  
	  delete [] inter_objs1;
	  delete [] inter_objs2;
	  delete [] inter_objs3;
	  delete [] inter_objs4;

	  
 }
	  
	   
	
int main(int argc, char* argv[]) 
{
  nvars=nDays;
  nobjs=4;
  nconsts=1;
  double *vars= new double [nvars];
  double *objs=new double [nobjs];
  double *consts=new double [nconsts];// or  double consts[nconsts]? 
  

  
    for(int i=0; i<10000;i++)
	{
	  for (int j=0;j<nDays;j++)
	  nat_flowmat[i][j]=0.0;
	 }
	 //read SOWs_Type6 file  and put the data into nat_flowmat, then rendom slect 
	 FILE *fp;
	 fp=fopen("SOWs_Type6.txt","r");
	 if(fp==NULL)
	 { perror("Error opening SOWs_Type6");}
	 
	 for(int i=0;i<10000;i++)
	 {
	 for (int j=0;j<nDays;j++)
	 {fscanf(fp,"%lf",&nat_flowmat[i][j]);} 
	 }
	 fclose (fp);
	 
     // read the control policy
	 double vars_mat[Numbers][nDays];
	 //manual specific vars
     FILE *myfile;
      myfile=fopen("var.txt","r");	 
	  if(myfile==NULL)
	    perror("Error opening var.txt");


	  for (int i=0;i<Numbers;i++)
	  {
	  for (int j=0;j<nDays;j++)
	  {
	    fscanf(myfile,"%lf",&vars_mat[i][j]);  //temporarily stored in var_mat
		}
	  }
	  fclose(myfile);

     FILE *output;
	 output=fopen("output.txt","w");
	 
	 
	 for (int i=0;i<Numbers;i++)
      {
          for (int j=0;j<nDays;j++) {
			  vars[j]=vars_mat[i][j];
			  } 
	 lake_problem(vars,objs,consts);
	 fprintf(output,"%f  %f   %f   %f\r\n",objs[0],objs[1],objs[2],objs[3]); 
	    //	  delete [] objs;
		//	 delete [] consts;
		//   delete [] vars;
		} 
		fclose(output);
		
		return 0;
}

