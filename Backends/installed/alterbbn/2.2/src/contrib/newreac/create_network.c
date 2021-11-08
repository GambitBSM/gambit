#include "include_network.h"


int main(int argc,char** argv)
{
	int AMAX;
	char winvn_name[100];
	char reaclib_name[100];
	int keep;
	
	if(argc<4) 
  	{ 
    		printf(" This program needs 3 parameters:\n"
           	"   name of the WINVN file\n"
           	"   name of the REACLIB database file\n"
           	"   maximal atomic mass (A) kept\n"
           	"  + optional parameter: 0=keep all elements (default), 1=remove rarest isotopes, 2=intermediate\n");
      		exit(1); 
  	} 
	else 
  	{
  		sscanf(argv[1],"%s",winvn_name);
  		sscanf(argv[2],"%s",reaclib_name);
  		sscanf(argv[3],"%d",&AMAX);
  		if(argc>4) sscanf(argv[4],"%d",&keep); else keep=0;
  	}

	if(AMAX>65) printf("Since A>65, \"#define LARGE\" should be uncommented in include_network.h to avoid memory problems.\n"); 
	if(AMAX>65) printf("In case of segmentation fault, please increase the stack size with \"ulimit -s unlimited\"\n");
 
#include "exclusions.h"  	
  	 	
	char nuclist[NELEMENTS][6],nuclist_temp[NELEMENTS][6]; /* Name of the elements */
	double Am[NELEMENTS],Am_temp[NELEMENTS]; /* Atomic number A */
    double Zm[NELEMENTS],Zm_temp[NELEMENTS]; /* Charge number Z */
    double Dm[NELEMENTS],Dm_temp[NELEMENTS]; /* mass excess DeltaM in MeV */
    double spin[NELEMENTS],spin_temp[NELEMENTS]; /* spin */
    
	int nnuc;
	int ie,je;
	
	for(ie=0;ie<NELEMENTS;ie++) 
	{
		Am_temp[ie]=Zm_temp[ie]=Dm_temp[ie]=spin_temp[ie]=Am[ie]=Zm[ie]=Dm[ie]=spin[ie]=0.;
		strcpy(nuclist_temp[ie],"");
		strcpy(nuclist[ie],"");
	}
	
	char dummy[100];
	
	/*-------- REACLIB winvn file ------------*/
	
	FILE *winvn;
	
	winvn=fopen(winvn_name,"r");

	fscanf(winvn,"%s",dummy);
	fscanf(winvn,"%s",dummy);

	do
	{
		fscanf(winvn,"%s",dummy);
	}
	while(strcmp(dummy,"n"));

	nnuc=0;
	
	do
	{
		nnuc++;
		
		strncpy(nuclist_temp[nnuc],dummy,5);
		remove_spaces(nuclist_temp[nnuc]);
		*nuclist_temp[nnuc]=toupper(*nuclist_temp[nnuc]);
		if(!strncmp(nuclist_temp[nnuc],"N",5)) sprintf(nuclist_temp[nnuc],"n");
		if(!strncmp(nuclist_temp[nnuc],"P",5)) sprintf(nuclist_temp[nnuc],"p");
		if(!strncmp(nuclist_temp[nnuc],"D",5)) sprintf(nuclist_temp[nnuc],"H2");
		if(!strncmp(nuclist_temp[nnuc],"T",5)) sprintf(nuclist_temp[nnuc],"H3");
	
		fscanf(winvn,"%lf",&Am_temp[nnuc]);
		
		fscanf(winvn,"%lf",&Zm_temp[nnuc]);
		
		fscanf(winvn,"%s",dummy);
		fscanf(winvn,"%lf",&spin_temp[nnuc]);
		
		fscanf(winvn,"%lf",&Dm_temp[nnuc]);
		
		for(ie=1;ie<=24;ie++) fscanf(winvn,"%s",dummy);
		
		if(Am_temp[nnuc]>AMAX) nnuc--;
		else if(keep==1)
		{		
			ie=0;
			while(strncmp(remove[ie],nuclist_temp[nnuc],5)&&ie<removesize) ie++;
			if(ie!=removesize) nnuc--;
		}
		else if(keep==2)
		{		
			ie=0;
			while(strncmp(removeinterm[ie],nuclist_temp[nnuc],5)&&ie<removesizeinterm) ie++;
			if(ie!=removesizeinterm) nnuc--;
		}
	}
	while(EOF != fscanf(winvn,"%s",dummy) && strncmp(dummy,"</",2));
	
	fclose(winvn);
	
	/* Order by nuclear mass A */
	quicksort(nuclist_temp,Am_temp,Zm_temp,Dm_temp,spin_temp,0,nnuc);
	
	/* In the following, the additional elements are added to the elements present in AlterBBN v2.1 */
    const char nuclist_origin[NNUCMAX+1][6] = {"","n","p","H2","H3","He3","He4","Li6","Li7","Be7","Li8","B8","Be9","B10","B11",
    "C11","B12","C12","N12","C13","N13","C14","N14","O14","N15","O15","O16"};

    const double Am_origin[NNUCMAX+1] = {0.,1.,1.,2.,3.,3.,4.,6.,7.,7.,8.,8.,9.,10.,11.,11.,12.,12.,12.,13.,13.,14.,14.,14.,15.,15.,16.}; /* Atomic number A */

    const double Zm_origin[NNUCMAX+1] = {0.,0.,1.,1.,1.,2.,2.,3.,3.,4.,3.,5.,4.,5.,5.,6.,5.,6.,7.,6.,7.,6.,7.,8.,7.,8.,8.}; /* Charge number Z */

    const double Dm_origin[NNUCMAX+1] = {0.,8.071388,7.289028,13.135825,14.949915,14.931325,2.424931,14.0864,14.9078,15.7696,20.9464,22.9212,11.34758,12.05086,8.6680,10.6506,13.3690,0.,17.3382,3.125036,5.3455,3.019916,2.863440,8.006521,0.101439,2.8554,-4.737036}; /* mass excess DeltaM in MeV */

	const double spin_origin[NNUCMAX+1] = {0.,0.5,0.5,1.,0.5,0.5,0.,1.,1.5,1.5,2.,2.,1.5,3.,1.5,1.5,1.,0.,1.,0.5,0.5,0.,1.,0.,0.5,0.5,0.};

	
	for(ie=0;ie<=NNUCMAX;ie++) strncpy(nuclist[ie],nuclist_origin[ie],5);
		
	for(ie=1;ie<=NNUCMAX;ie++)
	{
		je=1;
		
		while(strncmp(nuclist[ie],nuclist_temp[je],5)&&je<=nnuc) je++;
		
		if(je<=nnuc)
		{
			Am[ie]=Am_temp[je];
			Zm[ie]=Zm_temp[je];
			Dm[ie]=Dm_temp[je];
			spin[ie]=spin_temp[je];
			
			Am_temp[je]=Zm_temp[je]=Dm_temp[je]=spin_temp[je]=0.;
		}
		else
		{
			Am[ie]=Am_origin[ie];
			Zm[ie]=Zm_origin[ie];
			Dm[ie]=Dm_origin[ie];
			spin[ie]=spin_origin[ie];			
		}
		
	}
	
	ie=NNUCMAX+1;
	for(je=0;je<=nnuc;je++)
	{
		if(!(Am_temp[je]==0.&&Zm_temp[je]==0.&&Dm_temp[je]==0.&&spin_temp[je]==0.))
		{
			strncpy(nuclist[ie],nuclist_temp[je],5);
			Am[ie]=Am_temp[je];
			Zm[ie]=Zm_temp[je];
			Dm[ie]=Dm_temp[je];
			spin[ie]=spin_temp[je];
			ie++;
		}		
	}
	
	nnuc=ie-1;
	
#ifdef DEBUG
	for(ie=1;ie<=nnuc;ie++) printf("%d     %s    %d    %d    %f    %f\n",ie,nuclist[ie],(int)(Am[ie]),(int)(Zm[ie]),Dm[ie],spin[ie]);
	sleep(10);
#endif

	/*-------- REACLIB result file ------------*/

	char n1[6],n2[6],n3[6],n4[6],n5[6],n6[6],label[5],reverse[2],achar[14];
	double Q,a[7];
	int type,fail,temp;
	
	int numnuc_temp[NREAC][6],reac_temp[NREAC][6],reactype_temp[NREAC];
	double Qf_temp[NREAC],Qr_temp[NREAC],af_temp[NREAC][7],ar_temp[NREAC][7],Crev_temp[NREAC];
	
	for(ie=0;ie<NREAC;ie++) 
	{
		Qf_temp[ie]=Qr_temp[ie]=0.;		
		for(je=0;je<6;je++) numnuc_temp[ie][je]=reac_temp[ie][je]=0;
		for(je=0;je<7;je++) af_temp[ie][je]=ar_temp[ie][je]=0;
	}

	FILE *reaclib;
	
	reaclib=fopen(reaclib_name,"r");
	
	int nreac_temp=1;
	
	while((EOF != fscanf(reaclib,"%ld",&type)))
	{		
		fscanf(reaclib,"%6c",dummy);

		fscanf(reaclib,"%5c",dummy);
		strncpy(n1,dummy,5);
		remove_spaces(n1);
		
		fscanf(reaclib,"%5c",dummy);
		strncpy(n2,dummy,5);
		remove_spaces(n2);

		fscanf(reaclib,"%5c",dummy);
		strncpy(n3,dummy,5);
		remove_spaces(n3);

		fscanf(reaclib,"%5c",dummy);
		strncpy(n4,dummy,5);
		remove_spaces(n4);

		fscanf(reaclib,"%5c",dummy);
		strncpy(n5,dummy,5);
		remove_spaces(n5);

		fscanf(reaclib,"%5c",dummy);
		strncpy(n6,dummy,5);
		remove_spaces(n6);

		fscanf(reaclib,"%8c",dummy);

		fscanf(reaclib,"%4c",label);
		remove_spaces(label);

		fscanf(reaclib,"%1c",dummy);

		fscanf(reaclib,"%1c",reverse);
		remove_spaces(reverse);

		fscanf(reaclib,"%lf",&Q);

		for(ie=0;ie<7;ie++) fscanf(reaclib,"%lf",&a[ie]);
		
		*n1=toupper(*n1);
		if(!strncmp(n1,"N",5)) sprintf(n1,"n");
		if(!strncmp(n1,"P",5)) sprintf(n1,"p");
		if(!strncmp(n1,"D",5)) sprintf(n1,"H2");
		if(!strncmp(n1,"T",5)) sprintf(n1,"H3");

		*n2=toupper(*n2);
		if(!strncmp(n2,"N",5)) sprintf(n2,"n");
		if(!strncmp(n2,"P",5)) sprintf(n2,"p");
		if(!strncmp(n2,"D",5)) sprintf(n2,"H2");
		if(!strncmp(n2,"T",5)) sprintf(n2,"H3");

		*n3=toupper(*n3);
		if(!strncmp(n3,"N",5)) sprintf(n3,"n");
		if(!strncmp(n3,"P",5)) sprintf(n3,"p");
		if(!strncmp(n3,"D",5)) sprintf(n3,"H2");
		if(!strncmp(n3,"T",5)) sprintf(n3,"H3");

		*n4=toupper(*n4);
		if(!strncmp(n4,"N",5)) sprintf(n4,"n");
		if(!strncmp(n4,"P",5)) sprintf(n4,"p");
		if(!strncmp(n4,"D",5)) sprintf(n4,"H2");
		if(!strncmp(n4,"T",5)) sprintf(n4,"H3");

		*n5=toupper(*n5);
		if(!strncmp(n5,"N",5)) sprintf(n5,"n");
		if(!strncmp(n5,"P",5)) sprintf(n5,"p");
		if(!strncmp(n5,"D",5)) sprintf(n5,"H2");
		if(!strncmp(n5,"T",5)) sprintf(n5,"H3");

		*n6=toupper(*n6);
		if(!strncmp(n6,"N",5)) sprintf(n6,"n");
		if(!strncmp(n6,"P",5)) sprintf(n6,"p");
		if(!strncmp(n6,"D",5)) sprintf(n6,"H2");
		if(!strncmp(n6,"T",5)) sprintf(n6,"H3");
		
#ifdef DEBUG
		switch(type)
		{
			case 1: printf("%s -> %s               label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,label,reverse,Q,a[0]); break;
			case 2: printf("%s -> %s %s            label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,label,reverse,Q,a[0]); break;
			case 3: printf("%s -> %s %s %s         label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,label,reverse,Q,a[0]); break;
			case 4: printf("%s %s -> %s            label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,label,reverse,Q,a[0]); break;
			case 5: printf("%s %s -> %s %s         label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,label,reverse,Q,a[0]); break;
			case 6: printf("%s %s -> %s %s %s      label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,n5,label,reverse,Q,a[0]); break;
			case 7: printf("%s %s -> %s %s %s %s   label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,n5,n6,label,reverse,Q,a[0]); break;
			case 8: printf("%s %s %s -> %s         label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,label,reverse,Q,a[0]); break;
			case 9: printf("%s %s %s -> %s %s      label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,n5,label,reverse,Q,a[0]); break;
			case 10: printf("%s %s %s %s -> %s %s   label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,n5,n6,label,reverse,Q,a[0]); break;
			case 11: printf("%s -> %s %s %s %s      label: %s       reverse: %s        Q=%f   a0=%f\n",n1,n2,n3,n4,n5,label,reverse,Q,a[0]); break;
		}
#endif
		
		switch(type) /* Read in the REACLIB reaction type */
		{
			case 1: /* 1 -> 1 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=0;
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=0;
				reac_temp[nreac_temp][5]=find_element(n2,nuclist,nnuc);

				numnuc_temp[nreac_temp][0]=1;
				numnuc_temp[nreac_temp][1]=0;
				numnuc_temp[nreac_temp][2]=0;
				numnuc_temp[nreac_temp][3]=0;
				numnuc_temp[nreac_temp][4]=0;
				numnuc_temp[nreac_temp][5]=1;	
				
				break;			
			}
			case 2: /* 1 -> 2 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=0;
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n3,nuclist,nnuc);

				if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=0;
					
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=2;
				}
				else
				{

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
				
				break;		
			}

			case 3: /* 1 -> 3 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=0;
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][4]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n4,nuclist,nnuc);

				if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][4]=0;
									
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=3;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=2;
				}
				else
				{

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
				
				break;		
			}

			case 4: /* 2 -> 1 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=0;
				reac_temp[nreac_temp][5]=find_element(n3,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				else
				{

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				
				break;		
			}		

			case 5: /* 2 -> 2 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n4,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				
				if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=0;

					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=2;
				}
				else
				{
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
				
				break;		
			}		

			case 6: /* 2 -> 3 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=0;
				reac_temp[nreac_temp][3]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][4]=find_element(n4,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n5,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
				}
				
				if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][4]=0;
									
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=3;
				}
				else if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=2;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=1;
				}
				else
				{

					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}				
				break;		
			}	

			case 7: /* 2 -> 4 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][3]=find_element(n4,nuclist,nnuc);
				reac_temp[nreac_temp][4]=find_element(n5,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n6,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=0;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
				}
				
				if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=reac_temp[nreac_temp][4]=0;
									
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=4;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=2;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=3;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=3;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=2;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3])
				{
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][3]=2;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
				else
				{
					reac_temp[nreac_temp][0]=-1;
					/* 2 -> 4 different elements not kept */
				}
				
				break;		
			}	

			case 8: /* 3 -> 1 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=0;
				reac_temp[nreac_temp][5]=find_element(n4,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1]&&reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2]=0;
									
					numnuc_temp[nreac_temp][0]=3;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=2;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=1;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=1;
				}
				
				break;		
			}
						
			case 9: /* 3 -> 2 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][3]=0;
				reac_temp[nreac_temp][4]=find_element(n4,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n5,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1]&&reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2]=0;
									
					numnuc_temp[nreac_temp][0]=3;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=2;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=1;
					numnuc_temp[nreac_temp][3]=0;
				}

				if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=0;

					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=2;
				}
				else
				{
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}

				
				break;		
			}

			case 10: /* 4 -> 2 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][2]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][3]=find_element(n4,nuclist,nnuc);
				reac_temp[nreac_temp][4]=find_element(n5,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n6,nuclist,nnuc);

				if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1]&&reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2]&&reac_temp[nreac_temp][3]==reac_temp[nreac_temp][3])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
									
					numnuc_temp[nreac_temp][0]=4;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1]&&reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
									
					numnuc_temp[nreac_temp][0]=3;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1]&&reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
									
					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=2;
					numnuc_temp[nreac_temp][2]=0;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][0]==reac_temp[nreac_temp][1])
				{
					reac_temp[nreac_temp][1]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=0;
									
					numnuc_temp[nreac_temp][0]=2;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=1;
					numnuc_temp[nreac_temp][3]=0;
				}
				
				else if(reac_temp[nreac_temp][1]==reac_temp[nreac_temp][2])
				{
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=2;
					numnuc_temp[nreac_temp][2]=1;
					numnuc_temp[nreac_temp][3]=0;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3])
				{
					reac_temp[nreac_temp][3]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=1;
					numnuc_temp[nreac_temp][2]=2;
					numnuc_temp[nreac_temp][3]=0;
				}
				else
				{
					numnuc_temp[nreac_temp][0]=-1;
					/* 4 -> 2 different elements not kept */
				}

				if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=0;

					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=2;
				}
				else
				{
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
	
				break;		
			}
			
			case 11: /* 1 -> 4 */
			{
				reac_temp[nreac_temp][0]=find_element(n1,nuclist,nnuc);
				reac_temp[nreac_temp][1]=0;
				reac_temp[nreac_temp][2]=find_element(n2,nuclist,nnuc);
				reac_temp[nreac_temp][3]=find_element(n3,nuclist,nnuc);
				reac_temp[nreac_temp][4]=find_element(n4,nuclist,nnuc);
				reac_temp[nreac_temp][5]=find_element(n5,nuclist,nnuc);

				if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=reac_temp[nreac_temp][4]=0;
					
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=0;
					numnuc_temp[nreac_temp][5]=4;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=2;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4]&&reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=3;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3]&&reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][2]=reac_temp[nreac_temp][3]=0;
					
					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=0;
					numnuc_temp[nreac_temp][4]=3;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][4]==reac_temp[nreac_temp][5])
				{
					reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=2;
				}
				else if(reac_temp[nreac_temp][3]==reac_temp[nreac_temp][4])
				{
					reac_temp[nreac_temp][3]=reac_temp[nreac_temp][2];
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=1;
					numnuc_temp[nreac_temp][4]=2;
					numnuc_temp[nreac_temp][5]=1;
				}
				else if(reac_temp[nreac_temp][2]==reac_temp[nreac_temp][3])
				{
					reac_temp[nreac_temp][2]=0;

					numnuc_temp[nreac_temp][0]=1;
					numnuc_temp[nreac_temp][1]=0;
					numnuc_temp[nreac_temp][3]=2;
					numnuc_temp[nreac_temp][4]=1;
					numnuc_temp[nreac_temp][5]=1;
				}
				else
				{
					reac_temp[nreac_temp][0]=-1;
					/* 1 -> 4 different elements not kept */
				}
				
				break;		
			}		
		}
		
		/* reorder incoming nuclei */
		if(reac_temp[nreac_temp][1]>0&&reac_temp[nreac_temp][2]>0&&reac_temp[nreac_temp][1]<reac_temp[nreac_temp][2])
		{
				temp=reac_temp[nreac_temp][2];
				reac_temp[nreac_temp][2]=reac_temp[nreac_temp][1];
				reac_temp[nreac_temp][1]=temp;

				temp=numnuc_temp[nreac_temp][2];
				numnuc_temp[nreac_temp][2]=numnuc_temp[nreac_temp][1];
				numnuc_temp[nreac_temp][1]=temp;
		}
		
		if(reac_temp[nreac_temp][0]>0&&reac_temp[nreac_temp][1]>0&&reac_temp[nreac_temp][0]<reac_temp[nreac_temp][1])
		{
				temp=reac_temp[nreac_temp][1];
				reac_temp[nreac_temp][1]=reac_temp[nreac_temp][0];
				reac_temp[nreac_temp][0]=temp;

				temp=numnuc_temp[nreac_temp][1];
				numnuc_temp[nreac_temp][1]=numnuc_temp[nreac_temp][0];
				numnuc_temp[nreac_temp][0]=temp;
		}
		
		/* reorder outgoing nuclei */
		if(reac_temp[nreac_temp][3]>0&&reac_temp[nreac_temp][4]>0&&reac_temp[nreac_temp][3]>reac_temp[nreac_temp][4])
		{
				temp=reac_temp[nreac_temp][4];
				reac_temp[nreac_temp][4]=reac_temp[nreac_temp][3];
				reac_temp[nreac_temp][3]=temp;

				temp=numnuc_temp[nreac_temp][4];
				numnuc_temp[nreac_temp][4]=numnuc_temp[nreac_temp][3];
				numnuc_temp[nreac_temp][3]=temp;
		}
		
		if(reac_temp[nreac_temp][4]>0&&reac_temp[nreac_temp][5]>0&&reac_temp[nreac_temp][4]>reac_temp[nreac_temp][5])
		{
				temp=reac_temp[nreac_temp][5];
				reac_temp[nreac_temp][5]=reac_temp[nreac_temp][4];
				reac_temp[nreac_temp][4]=temp;

				temp=numnuc_temp[nreac_temp][5];
				numnuc_temp[nreac_temp][5]=numnuc_temp[nreac_temp][4];
				numnuc_temp[nreac_temp][4]=temp;
		}
		
		fail=0;
		if(reac_temp[nreac_temp][0]==0||numnuc_temp[nreac_temp][0]==0) fail++;
		for(ie=0;ie<=5;ie++) if(reac_temp[nreac_temp][ie]==-1) fail++;
		if(Q<0.) fail++; /* Only keep if Q positive */


		if(fail==0) /* Fill in the tables */
		{
			ie=1;
				
			while(ie<nreac_temp&&!(reac_temp[nreac_temp][0]==reac_temp[ie][0]&&reac_temp[nreac_temp][1]==reac_temp[ie][1]&&reac_temp[nreac_temp][2]==reac_temp[ie][2]&&reac_temp[nreac_temp][3]==reac_temp[ie][3]&&reac_temp[nreac_temp][4]==reac_temp[ie][4]&&reac_temp[nreac_temp][5]==reac_temp[ie][5])) ie++;
			
			if(ie==nreac_temp) // if new rate
			{
				double r1,r2,r3,r4,r5;
				r1=rate(27.,a);
				r2=rate(10.,a);
				r3=rate(1.,a);
				r4=rate(0.1,a);
				r5=rate(0.01,a);
				
				if(r1>1.e-30||r2>1.e-30||r3>1.e-30||r4>1.e-30||r5>1.e-30) // Check that the rates are not too small nor too large
				{
					Qf_temp[nreac_temp]=Q/K9_to_MeV;
					for(je=0;je<7;je++) af_temp[nreac_temp][je]=a[je];
			
					nreac_temp++;
				}
			}			
		}
	}
			
	nreac_temp--;
	
	
	for(ie=1;ie<=nreac_temp;ie++) /* Remove double reactions */
	{
			je=1;
			while(je<ie&&!(reac_temp[je][0]==reac_temp[ie][0]&&reac_temp[je][1]==reac_temp[ie][1]&&reac_temp[je][2]==reac_temp[ie][2]&&reac_temp[je][3]==reac_temp[ie][3]&&reac_temp[je][4]==reac_temp[ie][4]&&reac_temp[je][5]==reac_temp[ie][5])) je++;
			
			if(je<ie)
			{
#ifdef DEBUG
				printf("%d removed\n",ie);
#endif

				for(je=ie;je<=nreac_temp-1;je++)
				{
					int ke;
					
					for(ke=0;ke<6;ke++)
					{
						reac_temp[je][ke]=reac_temp[je+1][ke];
						numnuc_temp[je][ke]=numnuc_temp[je+1][ke];
					}
					
					Qf_temp[je]=Qf_temp[je+1];
					Qr_temp[je]=Qr_temp[je+1];
			
					for(ke=0;ke<7;ke++)
					{
						af_temp[je][ke]=af_temp[je+1][ke];
						ar_temp[je][ke]=ar_temp[je+1][ke];
					}	
				}
			
				nreac_temp--;
				ie--;
			}
	}
	
	for(ie=1;ie<=nreac_temp;ie++) // Compute reactype, Crev and set Qf and Qr to 0 for decays
	{
		reactype_temp[ie]=find_type(numnuc_temp[ie]);
		
		Crev_temp[ie]=(factorial(numnuc_temp[ie][3])*factorial(numnuc_temp[ie][4])*factorial(numnuc_temp[ie][5]))/(factorial(numnuc_temp[ie][0])*factorial(numnuc_temp[ie][1])*factorial(numnuc_temp[ie][2]))
		*(pow(2.*spin[reac_temp[ie][0]]+1.,numnuc_temp[ie][0])*pow(2.*spin[reac_temp[ie][1]]+1.,numnuc_temp[ie][1])*pow(2.*spin[reac_temp[ie][2]]+1.,numnuc_temp[ie][2]))/(pow(2.*spin[reac_temp[ie][3]]+1.,numnuc_temp[ie][3])*pow(2.*spin[reac_temp[ie][4]]+1.,numnuc_temp[ie][4])*pow(2.*spin[reac_temp[ie][5]]+1.,numnuc_temp[ie][5]))
		*pow((pow(Am[reac_temp[ie][0]]+Dm[reac_temp[ie][0]]/M_u,numnuc_temp[ie][0])*pow(Am[reac_temp[ie][1]]+Dm[reac_temp[ie][1]]/M_u,numnuc_temp[ie][1])*pow(Am[reac_temp[ie][2]]+Dm[reac_temp[ie][2]]/M_u,numnuc_temp[ie][2]))/(pow(Am[reac_temp[ie][3]]+Dm[reac_temp[ie][3]]/M_u,numnuc_temp[ie][3])*pow(Am[reac_temp[ie][4]]+Dm[reac_temp[ie][4]]/M_u,numnuc_temp[ie][4])*pow(Am[reac_temp[ie][5]]+Dm[reac_temp[ie][5]]/M_u,numnuc_temp[ie][5])),1.5);
	
		if(numnuc_temp[ie][0]==1&&numnuc_temp[ie][1]==0&&numnuc_temp[ie][2]==0) Crev_temp[ie]=0.; /* No Crev_temp for decays */
		if(numnuc_temp[ie][0]==1&&numnuc_temp[ie][1]==0&&numnuc_temp[ie][2]==0) Qf_temp[ie]=Qr_temp[ie]=0.; /* No Q for decays */
	}

#ifdef DEBUG	
	for(ie=1;ie<=nreac_temp;ie++) 
	{
		printf("%d / type %d:  (%d)%s  (%d)%s  (%d)%s -> (%d)%s  (%d)%s  (%d)%s     Crev_temp=%f     Q=%f\n",ie,reactype_temp[ie],numnuc_temp[ie][0],nuclist[reac_temp[ie][0]],numnuc_temp[ie][1],nuclist[reac_temp[ie][1]],numnuc_temp[ie][2],nuclist[reac_temp[ie][2]],numnuc_temp[ie][3],nuclist[reac_temp[ie][3]],numnuc_temp[ie][4],nuclist[reac_temp[ie][4]],numnuc_temp[ie][5],nuclist[reac_temp[ie][5]],Crev_temp[ie],Qf_temp[ie]);
	}
#endif
	
	fclose(reaclib);
	
	/* In the following, the additional reactions are added to the reactions present in AlterBBN v2.1 */

    double reacparam_orig[NNUCREACMAX+1][10] =
    {
    {0,0,0,0,0,0,0,0,0.,0.},                   // none
    {1,100001,1,0,0,0,0,2,0.,0.},              // n -> p
    {2,100001,4,0,0,0,0,5,0.,0.},              // H3 -> e- + v + He3
    {3,100002,10,0,0,0,0,6,0.,0.},             // Li8 -> e- + v + 2 He4
    {4,100001,16,0,0,0,0,17,0.,0.},            // B12 -> e- + v + C12
    {5,100001,21,0,0,0,0,22,0.,0.},            // C14 -> e- + v + N14
    {6,100002,11,0,0,0,0,6,0.,0.},             // B8 -> e+ + v + 2 He4
    {7,100001,15,0,0,0,0,14,0.,0.},            // C11 -> e+ + v + B11
    {8,100001,18,0,0,0,0,17,0.,0.},            // N12 -> e+ + v + C12
    {9,100001,20,0,0,0,0,19,0.,0.},            // N13 -> e+ + v + C13
    {10,100001,23,0,0,0,0,22,0.,0.},           // O14 -> e+ + v + N14
    {11,100001,25,0,0,0,0,24,0.,0.},           // O15 -> e+ + v + N15
    {12,110001,2,1,0,0,0,3,0.477,25.815},      // H + n -> g + H2
    {13,110001,3,1,0,0,0,4,1.65,72.612},       // H2 + n -> g + H3
    {14,110001,5,1,0,0,0,6,2.63,238.794},      // He3 + n -> g + He4
    {15,110001,7,1,0,0,0,8,1.20,84.132},       // Li6 + n -> g + Li7
    {16,110011,5,1,0,0,2,4,1.001,8.863},       // He3 + n -> p + H3
    {17,110011,9,1,0,0,2,8,1.001,19.080},      // Be7 + n -> p + Li7
    {18,110011,7,1,0,0,4,6,1.068,55.503},      // Li6 + n -> He4 + H3
    {19,110002,9,1,0,0,0,6,4.68,220.382},      // Be7 + n -> He4 + He4
    {20,110001,3,2,0,0,0,5,1.65,63.749},       // H2 + p -> g + He3
    {21,110001,4,2,0,0,0,6,2.63,229.931},      // H3 + p -> g + He4
    {22,110001,7,2,0,0,0,9,1.20,65.053},       // Li6 + p -> g + Be7
    {23,110011,7,2,0,0,5,6,1.067,46.640},      // Li6 + p -> He4 + He3
    {24,110002,8,2,0,0,0,6,4.68,201.302},      // Li7 + p -> He4 + He4
    {25,110001,6,3,0,0,0,7,1.55,17.109},       // H2 + He4 -> g + Li6
    {26,110001,6,4,0,0,0,8,1.13,28.629},       // H3 + He4 -> g + Li7
    {27,110001,6,5,0,0,0,9,1.13,18.412},       // He3 + He4 -> g + Be7
    {28,200011,3,0,0,0,1,5,1.73,37.934},       // 2 H2 -> n + He3
    {29,200011,3,0,0,0,2,4,1.73,46.798},       // 2 H2 -> p + H3
    {30,110011,4,3,0,0,1,6,5.51,204.116},      // H3 + H2 -> n + He4
    {31,110011,5,3,0,0,2,6,5.51,212.979},      // He3 + H2 -> p + He4
    {32,200021,5,0,0,0,2,6,3.35,149.229},      // 2 He3 -> 2 p + He4
    {33,110012,8,3,0,0,1,6,9.81,175.487},      // Li7 + H2 -> n + He4 + He4
    {34,110012,9,3,0,0,2,6,9.83,194.566},      // Be7 + H2 -> p + He4 + He4
    {35,110001,5,4,0,0,0,7,2.47,183.290},      // He3 + H3 -> g + Li6
    {36,110011,7,3,0,0,1,9,2.52,39.237},       // Li6 + H2 -> n + Be7
    {37,110011,7,3,0,0,2,8,2.52,58.317},       // Li6 + H2 -> p + Li7
    {38,110011,5,4,0,0,3,6,1.59,166.181},      // He3 + H3 -> H2 + He4
    {39,200021,4,0,0,0,1,6,3.34,131.503},      // 2 H3 -> 2n + He4
    {40,110111,5,4,0,1,2,6,3.34,140.366},      // He3 + H3 -> n + p + He4
    {41,110011,8,4,0,0,1,12,3.55,121.136},     // Li7 + H3 -> n + Be9
    {42,110011,9,4,0,0,2,12,3.55,140.215},     // Be7 + H3 -> p + Be9
    {43,110011,8,5,0,0,2,12,3.55,129.999},     // Li7 + He3 -> p + Be9
    {44,110001,8,1,0,0,0,10,1.33,23.589},      // Li7 + n -> g + Li8
    {45,110001,13,1,0,0,0,14,3.07,132.920},    // B10 + n -> g + B11
    {46,110001,14,1,0,0,0,16,2.37,39.111},     // B11 + n -> g + B12
    {47,110011,15,1,0,0,2,14,1.001,32.086},    // C11 + n -> p + B11
    {48,110011,13,1,0,0,6,8,0.755,32.371},     // B10 + n -> He4 + Li7
    {49,110001,9,2,0,0,0,11,1.32,1.595},       // Be7 + p -> g + B8
    {50,110001,12,2,0,0,0,13,0.986,76.424},    // Be9 + p -> g + B10
    {51,110001,13,2,0,0,0,15,3.07,100.834},    // B10 + p -> g + C11
    {52,110001,14,2,0,0,0,17,7.10,185.173},    // B11 + p -> g + C12
    {53,110001,15,2,0,0,0,18,2.37,6.979},      // C11 + p -> g + N12
    {54,110011,16,2,0,0,1,17,3.00,146.061},    // B12 + p -> n + C12
    {55,110011,12,2,0,0,6,7,0.618,24.663},     // Be9 + p -> He4 + Li6
    {56,110011,13,2,0,0,6,9,0.754,13.291},     // B10 + p -> He4 + Be7
    {57,110011,16,2,0,0,6,12,0.291,79.903},    // B12 + p -> He4 + Be9
    {58,110001,7,6,0,0,0,13,1.60,51.761},      // Li6 + He4 -> g + B10
    {59,110001,8,6,0,0,0,14,4.07,100.549},     // Li7 + He4 -> g + B11
    {60,110001,9,6,0,0,0,15,4.07,87.543},      // Be7 + He4 -> g + C11
    {61,110011,11,6,0,0,2,15,3.07,85.948},     // B8 + He4 -> p + C11
    {62,110011,10,6,0,0,1,14,3.07,76.960},     // Li8 + He4 -> n + B11
    {63,110011,12,6,0,0,1,17,10.28,66.158},    // Be9 + He4 -> n + C12
    {64,110011,12,3,0,0,1,13,2.06,50.609},     // Be9 + H2 -> n + B10
    {65,110011,13,3,0,0,2,14,6.42,107.105},    // B10 + H2 -> p + B11
    {66,110011,14,3,0,0,1,17,14.85,159.357},   // B11 + H2 -> n + C12
    {67,210001,6,1,0,0,0,12,0.600,18.262},     // 2 He4 + n -> g + Be9
    {68,300001,6,0,0,0,0,17,2.06,84.420},      // 3 He4 -> g + C12
    {69,110012,10,2,0,0,1,6,3.54,177.713},     // Li8 + p -> n + He4 + He4
    {70,110012,11,1,0,0,2,6,3.55,218.787},     // B8 + n -> p + He4 + He4
    {71,110012,12,2,0,0,3,6,0.796,7.554},      // Be9 + p -> H2 + He4 + He4
    {72,110003,14,2,0,0,0,6,3.45,100.753},     // B11 + p -> 2 He4 + He4
    {73,110003,15,1,0,0,0,6,3.46,132.838},     // C11 + n -> 2 He4 + He4
    {74,110001,17,1,0,0,0,19,0.898,57.400},    // C12 + n -> g + C13
    {75,110001,19,1,0,0,0,21,3.62,94.884},     // C13 + n -> g + C14
    {76,110001,22,1,0,0,0,24,2.74,125.715},    // N14 + n -> g + N15
    {77,110011,20,1,0,0,2,19,1.001,34.846},    // N13 + n -> p + C13
    {78,110011,22,1,0,0,2,21,3.00,7.263},      // N14 + n -> p + C14
    {79,110011,25,1,0,0,2,24,1.001,41.037},    // O15 + n -> p + N15
    {80,110011,25,1,0,0,6,17,0.707,98.659},    // O15 + n -> He4 + C12
    {81,110001,17,2,0,0,0,20,0.896,22.554},    // C12 + p -> g + N13
    {82,110001,19,2,0,0,0,22,1.21,87.621},     // C13 + p -> g + N14
    {83,110001,21,2,0,0,0,24,0.912,118.452},   // C14 + p -> g + N15
    {84,110001,20,2,0,0,0,23,3.62,53.705},     // N13 + p -> g + O14
    {85,110001,22,2,0,0,0,25,2.73,84.678},     // N14 + p -> g + O15
    {86,110011,24,2,0,0,0,26,3.67,140.733},    // N15 + p -> g + O16
    {87,110011,24,2,0,0,6,17,0.706,57.622},	   // N15 + p -> He4 + C12
    {88,110001,17,6,0,0,0,26,5.20,83.111},     // C12 + He4 -> g + O16
    {89,110011,13,6,0,0,2,19,9.35,47.134},     // B10 + He4 -> p + C13
    {90,110011,14,6,0,0,2,21,11.03,9.098},     // B11 + He4 -> p + C14
    {91,110011,15,6,0,0,2,22,3.68,33.921},     // C11 + He4 -> p + N14
    {92,110011,18,6,0,0,2,25,4.25,111.620},    // N12 + He4 -> p + O15
    {93,110011,20,6,0,0,2,26,5.80,60.557},     // N13 + He4 -> p + O16
    {94,110011,13,6,0,0,1,20,9.34,12.288},     // B10 + He4 -> n + N13
    {95,110011,14,6,0,0,1,22,3.67,1.835},      // B11 + He4 -> n + N14
    {96,110011,16,6,0,0,1,24,4.25,88.439},     // B12 + He4 -> n + N15
    {97,110011,19,6,0,0,1,26,5.79,25.711},     // C13 + He4 -> n + O16
    {98,110011,14,3,0,0,2,16,4.96,13.296},     // B11 + H2 -> p + B12
    {99,110011,17,3,0,0,2,19,1.88,31.585},     // C12 + H2 -> p + C13
    {100,110011,19,3,0,0,2,21,7.58,69.069}     // C13 + H2 -> p + C14
    };

	int numnuc_orig[NREAC][6];
	int nreac;
	int numnuc[NREAC][6],reac[NREAC][6],reactype[NREAC];
	double Qf[NREAC],af[NREAC][7],Crev[NREAC];
	
	for(ie=0;ie<=NNUCREACMAX;ie++)
	{
		reactype[ie]=(int)reacparam_orig[ie][1];
		type_to_numbers(reactype[ie],numnuc[ie]);
		for(je=0;je<6;je++) reac[ie][je]=(int)reacparam_orig[ie][2+je];
		Crev[ie]=reacparam_orig[ie][8];
		Qf[ie]=reacparam_orig[ie][9];
		for(je=0;je<7;je++) af[ie][je]=0.;
	}
	
	nreac=NNUCREACMAX;
	
	for(je=1;je<=nreac_temp;je++)
	{
		ie=1;
		while(!(reactype[ie]==reactype_temp[je]&&reac[ie][0]==reac_temp[je][0]&&reac[ie][1]==reac_temp[je][1]&&reac[ie][2]==reac_temp[je][2]&&reac[ie][3]==reac_temp[je][3]&&reac[ie][4]==reac_temp[je][4]&&reac[ie][5]==reac_temp[je][5])&&ie<=NNUCREACMAX) ie++;
		
		if(ie>NNUCREACMAX)
		{
			nreac++;
			reactype[nreac]=reactype_temp[je];
			for(ie=0;ie<6;ie++) reac[nreac][ie]=reac_temp[je][ie];
			for(ie=0;ie<6;ie++) numnuc[nreac][ie]=numnuc_temp[je][ie];
			Crev[nreac]=Crev_temp[je];
			Qf[nreac]=Qf_temp[je];
			for(ie=0;ie<7;ie++) af[nreac][ie]=af_temp[je][ie];
		}
		else if(af[ie][0]==0.)
		{
			int ke=ie;
			for(ie=0;ie<7;ie++) af[ke][ie]=af_temp[je][ie];
		}
	}

	quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,101,nreac);

	/*--------------------*/

	FILE *numbers;
	
	numbers=fopen("numbers.h","w");

	fprintf(numbers,"#define NNUCMAX %d\n\n",nnuc);
	
	fprintf(numbers,"#define NNUCREACMAX %d\n\n",nreac);

	fclose(numbers);

	/*--------------------*/
	
	FILE *nuclei;
	
	nuclei=fopen("bbn.h","w");	
	
	fprintf(nuclei,"    /* Nuclides: %d=%s",1,nuclist[1]);
	for(ie=2;ie<=nnuc;ie++) fprintf(nuclei,", %d=%s",ie,nuclist[ie]);
	fprintf(nuclei," */\n\n");
	
	fprintf(nuclei,"	const char name[NNUCMAX+1][6] = {\"\"");
	for(ie=1;ie<=nnuc;ie++) fprintf(nuclei,",\"%s\"",nuclist[ie]);
	fprintf(nuclei,"};\n\n");
	
	fprintf(nuclei,"	const double Am[NNUCMAX+1] = {0.");
	for(ie=1;ie<=nnuc;ie++) fprintf(nuclei,",%d.",(int)(Am[ie]));
	fprintf(nuclei,"};\n\n");

	fprintf(nuclei,"	const double Zm[NNUCMAX+1] = {0.");
	for(ie=1;ie<=nnuc;ie++) fprintf(nuclei,",%d.",(int)(Zm[ie]));
	fprintf(nuclei,"};\n\n");

	fprintf(nuclei,"	const double Dm[NNUCMAX+1] = {0.");
	for(ie=1;ie<=nnuc;ie++) fprintf(nuclei,",%f",Dm[ie]);
	fprintf(nuclei,"};\n\n");

	fprintf(nuclei,"	const double spin[NNUCMAX+1] = {0.");
	for(ie=1;ie<=nnuc;ie++) fprintf(nuclei,",%.1f",spin[ie]);
	fprintf(nuclei,"};\n\n");

	fprintf(nuclei,"	const double reacparam[NNUCREACMAX+1][10] =\n");
	fprintf(nuclei,"    {\n");
	fprintf(nuclei,"// type: #n1#n2#n3#n4#n5#n6\n"
					"// n1: incoming nuclide number\n"
					"// n2: incoming light nuclide number\n"
					"// n3: incoming lightest nuclide number\n"
					"// n4: outgoing lightest nuclide number\n"
					"// n5: outgoing light nuclide number\n"
					"// n6: outgoing nuclide number\n"
					"// rev: reverse reaction coefficient\n"
					"// q: energy release in reaction in 10**9 Kelvin (K = ev/k_B)\n\n"
					"// reac# type n1 n2 n3 n4 n5 n6 rev q\n\n");
	fprintf(nuclei,"    {0,0,0,0,0,0,0,0,0.,0.},\t\t// none\n");
	for(ie=1;ie<=nreac;ie++)
	{
		fprintf(nuclei,"    {%d,%d,%d,%d,%d,%d,%d,%d,%.5e,%.5e}",ie,reactype[ie],reac[ie][0],reac[ie][1],reac[ie][2],reac[ie][3],reac[ie][4],reac[ie][5],Crev[ie],Qf[ie]);
		if(ie==nreac) fprintf(nuclei,"\t\t// "); else fprintf(nuclei,",\t\t// ");
		for(je=0;je<3;je++)
		{
			if(je>0&&numnuc[ie][je]>0) fprintf(nuclei,"+ ",nuclist[reac[ie][je]]);
			if(numnuc[ie][je]==1) fprintf(nuclei,"%s ",nuclist[reac[ie][je]]);
			else if(numnuc[ie][je]>1) fprintf(nuclei,"%d %s ",numnuc[ie][je],nuclist[reac[ie][je]]);
		}
		fprintf(nuclei,"->");
		for(je=3;je<6;je++)
		{
			if(je>3&&numnuc[ie][je-1]>0&&numnuc[ie][je]>0) fprintf(nuclei," +",nuclist[reac[ie][je]]);
			if(numnuc[ie][je]==1) fprintf(nuclei," %s",nuclist[reac[ie][je]]);
			else if(numnuc[ie][je]>1) fprintf(nuclei," %d %s",numnuc[ie][je],nuclist[reac[ie][je]]);
		}
		fprintf(nuclei,"\n");
	}
	fprintf(nuclei,"    };\n");
	
	fclose(nuclei);
		
	/*--------------------*/
	
	FILE *network;
	network=fopen("bbnrate.h","w");

		fprintf(network,"	const double af[NNUCREACMAX+1][7] =\n");
		fprintf(network,"	{\n");
		fprintf(network,"	{0.,0.,0.,0.,0.,0.,0.},\n");
	
	for(ie=1;ie<=nreac;ie++)
	{
		fprintf(network,"	{");
		for(je=0;je<7;je++) if(je==6) fprintf(network,"%.5e}",af[ie][je]); else fprintf(network,"%.5e,",af[ie][je]);
		
		if(ie==nreac) fprintf(nuclei,"\t\t// %d: ",ie); else fprintf(nuclei,",\t\t// %d: ",ie);
		for(je=0;je<3;je++)
		{
			if(je>0&&numnuc[ie][je]>0) fprintf(nuclei,"+ ",nuclist[reac[ie][je]]);
			if(numnuc[ie][je]==1) fprintf(nuclei,"%s ",nuclist[reac[ie][je]]);
			else if(numnuc[ie][je]>1) fprintf(nuclei,"%d %s ",numnuc[ie][je],nuclist[reac[ie][je]]);
		}
		fprintf(nuclei,"->");
		for(je=3;je<6;je++)
		{
			if(je>3&&numnuc[ie][je-1]>0&&numnuc[ie][je]>0) fprintf(nuclei," +",nuclist[reac[ie][je]]);
			if(numnuc[ie][je]==1) fprintf(nuclei," %s",nuclist[reac[ie][je]]);
			else if(numnuc[ie][je]>1) fprintf(nuclei," %d %s",numnuc[ie][je],nuclist[reac[ie][je]]);
		}
		fprintf(nuclei,"\n");
	}
	fprintf(nuclei,"	};\n");
		
	fclose(network);

	return 1;
}


/*----------------------------------------------------*/

void remove_spaces(char str[]) 
{ 
    int ie,count; 
  
	count=0;
    for (ie = 0; str[ie]; ie++) 
    {
		if (str[ie] != ' ') str[count++] = str[ie];
    }
    str[count] = '\0';
    
    return;
} 

/*----------------------------------------------------*/

int find_element(char str[], char list[][6], int nnuc) 
{ 
    int ie=0;
    int test=1;
    
    while(test&&(ie<=nnuc))
    {
		ie++;
		if(!strncmp(str,list[ie],5)) test=0;
	}
    
    if(ie>nnuc) return -1; else return ie;
}

/*----------------------------------------------------*/

int find_type(int number[]) 
{
	int type=0;
	int ie;
	
	for(ie=0;ie<6;ie++) type+=pow(10,ie)*number[5-ie];
    
    return type;
}

/*----------------------------------------------------*/

void type_to_numbers(int type, int rn[]) 
{
	rn[5]=type%10;
	rn[4]=(type%100-rn[5])/10;
	rn[3]=(type%1000-10*rn[4]-rn[5])/100;
	rn[2]=(type%10000-100*rn[3]-10*rn[4]-rn[5])/1000;
	rn[1]=(type%100000-1000*rn[2]-100*rn[3]-10*rn[4]-rn[5])/10000;
	rn[0]=(type-10000*rn[1]-1000*rn[2]-100*rn[3]-10*rn[4]-rn[5])/100000;
    
    return;
}

/*----------------------------------------------------*/

double factorial(int n)
{
	if(n==0) return 1.;
	if(n==1) return 1.;
	if(n==2) return 2.;
	if(n==3) return 6.;
	if(n==4) return 24.;
	
	return n*factorial(n-1); 
}

/*----------------------------------------------------*/

double rate(double T9, double af[])
{
	int je;
	double temp=af[0];
	
	for(je=1;je<=5;je++) temp+=af[je]*pow(T9,(2.*je-5.)/3.);
	
	temp+=af[6]*log(T9);
	
	return exp(temp);	
}

/*--------------------------------------------------------------*/
/*------ Quicksort algorithm to sort the isotopes by mass ------*/
/*--------------------------------------------------------------*/
 
void swap_quicksort(char nuclist[][6], double Am[], double Zm[], double Dm[], double spin[], int ie, int je) 
{
	char nuclist_temp[NELEMENTS][6];
	double temp;
	char tmp[6];
	
	int ke;
	
	strncpy(tmp,nuclist[ie],5);
	strncpy(nuclist[ie],nuclist[je],5);
	strncpy(nuclist[je],tmp,5);
	
	temp=Am[ie];
	Am[ie]=Am[je];
	Am[je]=temp;
	
	temp=Zm[ie];
	Zm[ie]=Zm[je];
	Zm[je]=temp;
	
	temp=Dm[ie];
	Dm[ie]=Dm[je];
	Dm[je]=temp;

	temp=spin[ie];
	spin[ie]=spin[je];
	spin[je]=temp;
	
	return;
}

int random_quicksort(int ie, int je) 
{
    return ie + rand()%(je-ie+1);
}

void quicksort(char nuclist[][6], double Am[], double Zm[], double Dm[], double spin[], int left, int right)
{
	int last=left;
	int ie;

	if (left >= right) return;

	swap_quicksort(nuclist,Am,Zm,Dm,spin,left,random_quicksort(left,right));
	
	for (ie = left+1;ie<=right;ie++) 
	{
		if(((int)Am[ie] < (int)Am[left]) || (((int)Am[ie] == (int)Am[left])&&((int)Zm[ie] < (int)Zm[left]))) swap_quicksort(nuclist,Am,Zm,Dm,spin,++last,ie);
	}
	
	swap_quicksort(nuclist,Am,Zm,Dm,spin,left,last);
	quicksort(nuclist,Am,Zm,Dm,spin,left,last-1);
	quicksort(nuclist,Am,Zm,Dm,spin,last+1,right);
	
	return;
}

/*--------------------------------------------------------------*/
/*---- Quicksort algorithm to sort the reactions by numbering ----*/
/*--------------------------------------------------------------*/
 
void swap_quicksort_reac(int reac[][6], int numnuc[][6], double Crev[], double Qf[], int reactype[], double af[][7], int ie, int je)
{
	int tempint;
	double temp;
	
	int ke;
	
	tempint=reactype[ie];
	reactype[ie]=reactype[je];
	reactype[je]=tempint;

	temp=Crev[ie];
	Crev[ie]=Crev[je];
	Crev[je]=temp;
	
	temp=Qf[ie];
	Qf[ie]=Qf[je];
	Qf[je]=temp;

	for(ke=0;ke<6;ke++) 
	{
		tempint=reac[ie][ke];
		reac[ie][ke]=reac[je][ke];
		reac[je][ke]=tempint;
	}

	for(ke=0;ke<6;ke++) 
	{
		tempint=numnuc[ie][ke];
		numnuc[ie][ke]=numnuc[je][ke];
		numnuc[je][ke]=tempint;
	}

	for(ke=0;ke<7;ke++) 
	{
		temp=af[ie][ke];
		af[ie][ke]=af[je][ke];
		af[je][ke]=temp;
	}
	
	return;
}

void quicksort_reac(int reac[][6], int numnuc[][6], double Crev[], double Qf[], int reactype[], double af[][7], int left, int right)
{
	int last=left;
	int ie;

	if (left >= right) return;

	swap_quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,left,random_quicksort(left,right));
	
	for (ie = left+1;ie<=right;ie++) 
	{
		if( (reac[ie][0]<reac[left][0]) || 
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]<numnuc[left][0]) || 
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]==numnuc[left][0] && reac[ie][1]<reac[left][1]) || 
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]==numnuc[left][0] && reac[ie][1]==reac[left][1] && reac[ie][2]<reac[left][2]) ||
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]==numnuc[left][0] && reac[ie][1]==reac[left][1] && reac[ie][2]==reac[left][2] && reac[ie][5]<reac[left][5]) ||
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]==numnuc[left][0] && reac[ie][1]==reac[left][1] && reac[ie][2]==reac[left][2] && reac[ie][5]==reac[left][5] && reac[ie][4]<reac[left][4]) ||
		(reac[ie][0]==reac[left][0] && numnuc[ie][0]==numnuc[left][0] && reac[ie][1]==reac[left][1] && reac[ie][2]==reac[left][2] && reac[ie][5]==reac[left][5] && reac[ie][4]==reac[left][4] && reac[ie][3]<reac[left][3])
		) swap_quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,++last,ie);
	}
	
	swap_quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,left,last);
	quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,left,last-1);
	quicksort_reac(reac,numnuc,Crev,Qf,reactype,af,last+1,right);
	
	return;
}
