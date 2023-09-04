#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __hpux
#include<dl.h>
#else
#include <dlfcn.h>
#endif

#include "VandP.h"
#include "dynamic_cs.h"
#include "fcompare.h"


char  * libDir=NULL;
char  * modelDir=NULL;
char  * compDir = NULL;
char  * calchepDir=NULL;
int   modelNum=0;
int ForceUG=0;

int  prepareWorkPlace(void)
{  char * command;
   struct stat buf;
   int err,len,mknew;

   if(!compDir) return  -1;   
   mknew=stat(compDir,&buf);
   len=strlen(compDir)+500;
   if(modelDir) len+=strlen(modelDir);
   command=malloc(len);  

   if(mknew) 
   { char * dir[3]={"tmp","results","models"};
     int i;
     if(mkdir(compDir, 00755)) return -3; 
     for(i=0;i<3;i++) 
     { 
        sprintf(command,"%s/%s",compDir,dir[i]);
        mkdir(command,00755);
     } 
     if(modelDir && modelNum)
     {
       sprintf(command,
       "for FILE in vars func prtcls lgrng extlib\n do\n"
       "  cp %s/\"$FILE\"%d.mdl %s/models/\"$FILE\"1.mdl\n" 
       "done\n", modelDir,modelNum,  compDir);  
       system(command);
     } else { free(command); return -2;} 
   } else 
   {   
     sprintf(command, "dName=%s\n"
     "for FILE in $dName/tmp/* $dName/results/*\n"
     "do\n"
     " if(test ! -d $FILE) then\n"
     "   rm -f $FILE\n"
     " fi\n" 
     "done\n",compDir);     
     system(command);
   } 
   free(command);
   return mknew;
}

char * pdg2name(int pdg)
{
  int i;
  if(pdg==0) return NULL;

  for(i=0;i<nModelParticles;i++)
  {          if(ModelPrtcls[i].NPDG==pdg) return ModelPrtcls[i].name;
     else  { if(ModelPrtcls[i].NPDG==-pdg) return ModelPrtcls[i].aname;}
  }   
  return NULL;
} 

// Return the name of the mass parameter for particle of given PDG code.
char *pdg2mass(int pdg)
{
  int i;
  if(pdg==0) return NULL;
  
  for (i=0; i<nModelParticles; i++)
  {
    if (ModelPrtcls[i].NPDG==pdg) return ModelPrtcls[i].mass;
    else if (ModelPrtcls[i].NPDG==-pdg) return ModelPrtcls[i].mass;
  }
  return NULL;
}

// Return the name of the width parameter for particle of given PDG code. 
char *pdg2width(int pdg)
{
  int i;
  if(pdg == 0) return NULL;
  
  for (i=0; i<nModelParticles; i++)
  {
    if (ModelPrtcls[i].NPDG==pdg) return ModelPrtcls[i].width;
    else if (ModelPrtcls[i].NPDG==-pdg) return ModelPrtcls[i].width;
  }
  return NULL;  
}


int  checkWorkPlace(void)
{
  char * n1=malloc(strlen(modelDir)+50);
  char * n2=malloc(strlen(compDir)+50);
  char *fList[5]= {"vars","prtcls","extlib","func","lgrng",};
  int i;
  for(i=0;i<5;i++)
  { sprintf(n1,"%s/%s%d.mdl",modelDir,fList[i],modelNum);
    sprintf(n2,"%s/models/%s1.mdl",compDir,fList[i]);
    if(fcompare(n1,n2)) break;
  }   
  free(n1);
  free(n2);
  if(i==5) return 0;
  if(modelDir && modelNum)
  { 
     char* command=malloc(strlen(modelDir)+strlen(compDir)+200);
     sprintf(command,
     "for FILE in vars func prtcls lgrng extlib\n do\n"
     "  cp %s/\"$FILE\"%d.mdl %s/models/\"$FILE\"1.mdl\n" 
     "done\n", modelDir,modelNum,  compDir);  
     system(command);
     free(command);
     delAllLib();
  }
  return 1;
}  

int  checkMtime(char * fname)
{ int i,L;
  time_t tt;
  struct stat buff;
  char * mf[4]={"vars","func","prtcls","lgrng"};
  char *mfname;
  if(modelDir==NULL) return 0;
  stat(fname,&buff); tt=buff.st_mtime;
  L=strlen(modelDir)+20;
  mfname=malloc(strlen(modelDir)+20); 
  
  for(i=0;i<4;i++)
  { sprintf(mfname,"%s/%s%d.mdl",modelDir,mf[i],modelNum);
    stat(mfname,&buff);
    if(buff.st_mtime > tt) break;
  }
  free(mfname);
  if(i<4) {unlink(fname); return 1;}
  return 0;
}

typedef struct  procRec 
{ struct procRec  * next;
  char * libname;
  numout * cc;
}  procRec;   

static  procRec* allProc=NULL;

static void* newSymbol(void*handle,char *name)
{
#ifdef __hpux
void * addr;
     if(shl_findsym((shl_t*)&handle,name,TYPE_UNDEFINED,&addr)) return NULL;
       else return addr;
#else
      return dlsym(handle, name);
#endif
}

static void dClose(void * handle)
{
#ifdef __hpux
       shl_unload(handle);
#else
       dlclose(handle);
#endif
}

REAL * varAddress(char *name)
{int i;
 for(i=0;i<nModelVars+nModelFunc;i++) if(!strcmp(name,varNames[i]))return varValues+i;
 return NULL;
}

int passParameters(numout*cc)
{
   int i;
   for(i=1;i<=cc->interface->nvar;i++) 
   { 
     if(cc->link[i]) 
     {
       cc->interface->va[i]=*(cc->link[i]);
     }
   }
   if(cc->interface->calcFunc()>0) { printf("cannot calculate constr\n"); return 1;}
   return 0;
}

void delAllLib(void)
{
  procRec* curProc=allProc;
  while(curProc)
  {  procRec*tmp=curProc;
     free(curProc->libname);
     free(curProc->cc->link);
     dClose(curProc->cc->handle);     
     free(curProc->cc);
     curProc=curProc->next;
     free(tmp);
  }
  allProc=NULL;
}

decayTableStr* decayTable=NULL;
static int nPrtcls_old=0; 
void cleanDecayTable(void)
 { int i,j;
   if(decayTable) for(i=0;i<nPrtcls_old;i++) for(j=0;j<2;j++) if(decayTable[i].pdList[j]) 
      cleanTxtList(decayTable[i].pdList[j]);    
   decayTable=realloc(decayTable, nModelParticles*sizeof(decayTableStr));
   nPrtcls_old=nModelParticles;
   for(i=0;i<nModelParticles;i++)
   { for(j=0;j<2;j++) decayTable[i].pdList[j]=NULL;
     decayTable[i].width=0;
     decayTable[i].status=0;
   }
}

int pTabPos(char * name)
{
  int i;
  for(i=0;i<nModelParticles;i++)
  { 
    if(!strcmp(name,ModelPrtcls[i].name )) return   i+1;
    if(!strcmp(name,ModelPrtcls[i].aname)) return -(i+1);
  }
  return 0;
}

double pMass(char * name)
{
  char *nm;
  int n=pTabPos(name);
  if(!n){printf("Wrong particle name '%s'\n",name); return 0;}
  nm=ModelPrtcls[abs(n)-1].mass;
  if(nm[0]=='0') return 0; else 
  { REAL *ma=varAddress(nm);
    return fabs(*ma);
  }
}

double pWidth(char *name, txtList * LL)
{
  txtList L,l,Lout;
  char libName[100];
  double sum=0,width;
  int i,i0,j,j0,nout;
  REAL Qstat;
  REAL*Q=NULL;

  for(i=0;i<nModelParticles;i++)
  { char *pnames[2]={ModelPrtcls[i].name,ModelPrtcls[i].aname};
    for(j=0;j<2;j++) if(strcmp(name,pnames[j])==0) 
    { 
      if(decayTable[i].status==1)
      {        
        if(LL) *LL=decayTable[i].pdList[j];
        return decayTable[i].width;
      } else if(decayTable[i].status==-1)
      { if(LL) *LL=NULL;
        return 0;
      }break;
    } if(j!=2) break;    
  }    

  i0=i,j0=j;
  if(i0==nModelParticles)
  { printf("%s out of model particles\n",name);
    if(LL) *LL=NULL;
    return 0;
  }  

  {  int pdg,pdg0,Len,decay[10];
     double br;
     pdg0=ModelPrtcls[i0].NPDG;
     if(j0) pdg0=-pdg0;
     for(i=1; allDecays(i,0,&pdg,&Len,decay,&width,&br) ;i++)
     {
        if(abs(pdg)==abs(pdg0))
        {  txtListStr*l,*L=NULL;
           l=malloc(sizeof(txtListStr));
           decayTable[i0].width=width;
           decayTable[i0].status=1;  
           for(j=1; allDecays(i,j,&pdg,&Len,decay,&width,&br) ;j++) if(br>0)
           { int k;
             char*ch;  
             l=malloc(sizeof(txtListStr));
             l->txt=malloc(100); 
             l->next=L;
             ch=pdg2name(pdg);   if(ch) sprintf(l->txt,"%E  %s -> ",br,ch); else sprintf(l->txt,"%E  #%d -> ",br,pdg);
             ch=pdg2name(decay[0]); if(ch)  sprintf(l->txt+strlen(l->txt),"%s",ch); else  sprintf(l->txt+strlen(l->txt),"#%d",decay[0]);
             for(k=1;k<Len;k++)
             { ch=pdg2name(decay[k]);
               if(ch)sprintf(l->txt+strlen(l->txt),", %s",ch); else sprintf(l->txt+strlen(l->txt),", #%d",decay[k]);
             }    
             L=l;
           }
           if(pdg0==pdg) 
           {  decayTable[i0].pdList[j0]=L; 
              if(strcmp(ModelPrtcls[i0].name,ModelPrtcls[i0].aname))
                           decayTable[i0].pdList[1-j0]=conBrList(L);
           } else 
           { decayTable[i0].pdList[1-j0]=L;
             if(strcmp(ModelPrtcls[i0].name,ModelPrtcls[i0].aname))
                           decayTable[i0].pdList[j0]=conBrList(L);
           }                
           if(LL) *LL=decayTable[i0].pdList[j0];
           return width;
        }
     }          
  }
  decayTable[i0].status=-1;
  if(Q==NULL) for(i=0;i<nModelVars;i++) if(strcmp(varNames[i],"Q")==0){ Q= varValues+i; break;}
  if(Q) { Qstat=*Q; setQforParticle(Q,name);}
    
  width=decay22List(name,&L);

  if(L) 
  {
    if(LL) *LL=L;
    decayTable[i0].pdList[j0]=L;
    if(strcmp(ModelPrtcls[i0].name,ModelPrtcls[i0].aname)) 
                 decayTable[i0].pdList[1-j0]=conBrList(L); 
    decayTable[i0].width=width;
    decayTable[i0].status=1;
    if(Q) {*Q=Qstat; calcMainFunc();}
    return width;
  }

  Lout=NULL;
  L= makeDecayList(name,3);
  massFilter(pMass(name),&L);
  gammaGluFilter(&L);
  if(L==NULL) 
  { L= makeDecayList(name,4);  
    massFilter(pMass(name),&L);
    gammaGluFilter(&L);
    nout=4;
  }  else nout=3;
      
  for(sum=0,l=L;l;l=l->next)  
  { numout* cc;
    int err=0;
    txtList newr;
    process2Lib(l->txt ,libName);
    cc=getMEcode(0,ForceUG,l->txt,NULL,"",libName);
    if(!cc) continue;
    if(nout==3) width=width13(cc, 1, &err); else width=width14(cc, &err);
    if(width >0)
    {
      sum+=width;
      newr=malloc(sizeof(txtListStr));
      newr->next=Lout;
      Lout=newr;
      newr->txt=malloc(strlen(l->txt)+20);
      sprintf(newr->txt,"%E  %s",width,l->txt);
    }
  }
  cleanTxtList(L); 
  if(Lout)
  for(L=Lout;L;L=L->next)
  { char buff[100];
    sscanf(L->txt,"%lf %[^\n]",&width,buff);
    sprintf(L->txt,"%E %s",width/sum,buff);  
  }   
  if(LL) *LL=Lout;
  decayTable[i0].pdList[j0]=Lout;
  if(strcmp(ModelPrtcls[i0].name,ModelPrtcls[i0].aname)) 
               decayTable[i0].pdList[1-j0]=conBrList(Lout);
  decayTable[i0].width=sum;
  decayTable[i0].status=1;
  if(Q) { *Q=Qstat; calcMainFunc();}
  return sum;
}

double aWidth(char *name) { return pWidth(name,NULL);}

static int pListEq(char * txt1, char * txt2)  
{  char buff[100];
   char rd1[10][10];
   char rd2[10][10];
   int n1,n2,i1,i2;
   char *ch;
    
   strcpy(buff,txt1); while((ch=strchr(buff,','))) ch[0]=' ';
   
   n1=sscanf(buff,"%s %s %s %s %s %s %s %s %s %s",
   rd1[0],rd1[1],rd1[2],rd1[3],rd1[4],rd1[5],rd1[6],rd1[7],rd1[8],rd1[9]); 
   
   strcpy(buff,txt2); while((ch=strchr(buff,','))) ch[0]=' ';
   
   n2=sscanf(buff,"%s %s %s %s %s %s %s %s %s %s",
   rd2[0],rd2[1],rd2[2],rd2[3],rd2[4],rd2[5],rd2[6],rd2[7],rd2[8],rd2[9]); 
   
   if(n1!=n2) return 0;
   for(i1=0;i1<n1;i1++)
   { for(i2=0;i2<n2;i2++) if(strcmp(rd1[i1],rd2[i2])==0){rd2[i2][0]=0; break;}
     if(i2==n2) return 0;
   } 
   return 1;
}      


static numout* loadLib(void* handle, char * lib)
{ numout * cc=malloc(sizeof(numout));
  char name[100];
  if(!handle) {free(cc); return NULL;}   
  cc->handle=handle;
  sprintf(name,"interface_%s",lib);
  cc->interface=newSymbol(handle, name);
  if(!cc->interface || cc->interface->nprc==0){free(cc); return NULL;}
  else
  {  int i;
     cc->init=0;
     cc->Q=NULL, cc->SC=NULL;
     cc->link=malloc(sizeof(double*)*(1+cc->interface->nvar));
     cc->link[0]=NULL;
     for(i=1;i<=cc->interface->nvar;i++) 
     { char *name=cc->interface->varName[i];
       cc->link[i]=varAddress(name);
if(cc->link==NULL) printf("No link for %s\n",name);       
       if(strcmp(name,"Q")==0) cc->Q=cc->interface->va+i; 
       else if(strcmp(name,"SC")==0) cc->SC=cc->interface->va+i;
     }  
     *(cc->interface->aWidth)=&aWidth;
  }
  return cc;
}

static void * dLoad(char * libName)
{
void *q;

if(access(libName,R_OK)) return NULL;

#ifdef __hpux
   return  shl_load(libName,0,0L);
#else
   q= dlopen(libName, RTLD_NOW);
   if(!q) printf("%s\n",dlerror()); 
   return q;
#endif
}

numout*getMEcode(int twidth,int Gauge, char*Process, char*excludeVirtual, char*excludeOut,char*lib)
{
   char *proclibf,*command;
   void * handle=NULL;
   int new=0;
   numout * cc;
   procRec*test;
   int Len;
   char * lib_;

   lib_=malloc(strlen(lib)+4);
   
   if(Gauge) sprintf(lib_,"%s_u",lib);    else  strcpy(lib_,lib); 
     
   for(test=allProc;test; test=test->next)
   { if(strcmp(lib_,test->libname)==0) return test->cc;}
   
   Len=strlen(compDir)+strlen(lib)+strlen(libDir)+300;
   proclibf=malloc(Len);

   if(Process) Len+=strlen(Process);
   if(excludeVirtual) Len+=strlen(excludeVirtual);
   if(excludeOut) Len+=strlen(excludeOut);
   command=malloc(Len);
 

   sprintf(proclibf,"%s/%s.so",libDir,lib_);

   if(access(proclibf,R_OK)==0 && checkMtime(proclibf)==0) handle=dLoad(proclibf);
   if(!handle)
   {  int i;
   
      for(i=0;Process[i]==' ';i++); if(Process[i]==0)
      {    
        free(command); free(proclibf); free(lib_); 
        return NULL;    
      }      
      if(!handle)
      {
        char options[20];
        char GaugeCh[4];
        int ret;  
        int delWorkDir;
        
        if(twidth) strcpy(options,"5[[{[{}");else strcpy(options,"");
        if(Gauge) strcpy(GaugeCh,"U"); else strcpy(GaugeCh,"F");
 
        delWorkDir=prepareWorkPlace();      

        sprintf(command,"cd %s; %s/sbin/newProcess %s %s \"%s\" %s \"%s\"",
                       compDir, calchepDir, lib_, libDir,options,GaugeCh,Process);
  
        if(excludeVirtual) sprintf(command+strlen(command)," \"%s\"",excludeVirtual);
        else  sprintf(command+strlen(command)," \"\"");            
        if(excludeOut) sprintf(command+strlen(command)," \"%s\"",excludeOut);       
        ret=system(command);
      
        if(ret<0 || WIFSIGNALED(ret)>0 ) exit(10);
        if(delWorkDir )cleanWorkPlace();
        
        if(ret==0) handle=dLoad(proclibf); else 
        { printf(" Can not compile %s \n", Process);
          free(command); free(proclibf); free(lib_);
          return NULL;
        } 
        if(!handle)
        { printf(" Can not load the compiled library %s \n",proclibf);
           free(command); free(proclibf); free(lib_);
          return NULL;
        }         
        new=1;   
      }
   }
   cc=loadLib(handle,lib_);
   if(!cc && new) dClose(handle);
   if(cc)
   {  test=(procRec*)malloc(sizeof(procRec));
      test->next=allProc; allProc=test;
      test->libname=(char*) malloc(strlen(lib_)+1);
      strcpy(test->libname,lib_);
      test->cc=cc;
   } else if(new) dClose(handle);  
    free(command); free(proclibf); free(lib_);
    return cc; 
}

int  findVal(char * name, double * val)
{
  int i;
  for(i=0;i<nModelVars+nModelFunc;i++)
  { 
    if(strcmp(name,varNames[i])) continue;
    *val=varValues[i] ;
    return 0;
  }
  return 2;
}

double  findValW(char*name)
{ double val;
  if(findVal(name,&val)) {printf(" %s not found\n",  name); return 0;}
  else return val;
}

int procInfo2(numout*cc,int nsub,char**name,REAL*mass)
{
  int i;
  int ntot=cc->interface->nin+cc->interface->nout;
    
  if(nsub<1 || nsub> cc->interface->nprc) return 2;

  if(name)for(i=0;i<ntot ;i++) 
  name[i]=(cc->interface->pinf)(nsub,i+1,NULL,NULL);

  if(mass)
  {  
    if(passParameters(cc)){ printf("cannot calculate constr\n"); return 4;}
    for(i=0;i<ntot ;i++) cc->interface->pinf(nsub,i+1,mass+i,NULL);     
  }
  return 0;
}

