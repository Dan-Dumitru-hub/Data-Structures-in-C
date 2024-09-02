#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256

typedef struct
{
	int x, y;
} TPct;


typedef int (*TFCond ) (void*);
int peaxa(void * pct){

  if(  ((TPct*)pct)->x *((TPct*)pct)->y ==0)
    return 1;
  return 0;
}

int invers(void * pct){

  if(  ((TPct*)pct)->x +((TPct*)pct)->y ==0)
    return 1;
  return 0;
}
int GenereazaCoadaPct(void* c, size_t N, int v1, int v2)
{
  	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1;
    	p.y = rand() % (v2-v1+1) + v1;

		if (!IntrQ(c, &p))
			return n;
		n++;
  	}
  	return n;
}

int GenereazaStivaPct(void* c, size_t N, int v1, int v2)
{
	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1;
    	p.y = rand() % (v2-v1+1) + v1;

		if (!Push(c, &p))
			return n;
		n++;
  	}
  	return n;
}

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
      PrelQ (a, AfiElem);       	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          /* afiseaza antetul */
	if (VidaS (a))
    	printf ("Stiva vida!");
  	else
      	Prel_B_V (a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiPct(void *a)
{
	printf("[%d %d] ", (*(TPct*)a).x, (*(TPct*)a).y);
	return 1;
}



void *copie(void *s){


  void * c=InitQ(DimES(s),MAX);
  void *stemp=InitS(DimES(s),MAX);
  void *el=malloc(DimES(s));
  while(!VidaS(s)){

    Pop(s,el);
    IntrQ(c,el);
    Push(stemp,el);

  }

  Suprapune(s,stemp);
  free(el);
  return c;
}


double f1c(void*c,TFCond fcond){

  int nr=0,nrcond=0;
  void *qtemp=InitQ(DimEQ(c),MAX);
  void *el=malloc(DimEQ(c));
  while(!VidaQ(c)){
    ExtrQ(c,el);
    if(fcond(el))
      nrcond++;
    nr++;
    IntrQ(qtemp,el);

  }

  ConcatQ(c,qtemp);
  if(nr==0)
    return -1;
  return (double)nrcond/nr*100;
}


void f2c(void*c,TFCond fcond){

 
  void *qtemp=InitQ(DimEQ(c),MAX);
  void *el=malloc(DimEQ(c));
  while(!VidaQ(c)){
    ExtrQ(c,el);
    if(!fcond(el))
     
    IntrQ(qtemp,el);

  }

  ConcatQ(c,qtemp);
  
}


double f1s(void*s,TFCond fcond){

  int nr=0,nrcond=0;
  void *qtemp=InitS(DimES(s),MAX);
  void *el=malloc(DimES(s));
  while(!VidaS(s)){
    //ExtrQ(c,el);
    Pop(s,el);


    if(fcond(el))
      nrcond++;
    nr++;
    Push(qtemp,el);

  }

  Rastoarna(s,qtemp);
  if(nr==0)
    return -1;
  return (double)nrcond/nr*100;
}

void f2s(void*s,TFCond fcond){

  void *qtemp=InitS(DimES(s),MAX);
  void *el=malloc(DimES(s));
  while(!VidaS(s)){
    //ExtrQ(c,el);
    Pop(s,el);


    if(!fcond(el))
     
    Push(qtemp,el);

  }

  Rastoarna(s,qtemp);
 
}

void * f3s(void*s,TFCond fcond){

  void *qtemp=InitS(DimES(s),MAX);
    void *qtemp1=InitS(DimES(s),MAX);

  void *el=malloc(DimES(s));
  while(!VidaS(s)){
    //ExtrQ(c,el);
    Pop(s,el);


    if(!fcond(el))
     
    Push(qtemp,el);
  else  Push(qtemp1,el);

  }

  Rastoarna(s,qtemp);
  return qtemp1;
 
}


void *f3c(void*c,TFCond fcond){

 
  void *qtemp=InitQ(DimEQ(c),MAX);
  void *qtemp1=InitQ(DimEQ(c),MAX);
  void *el=malloc(DimEQ(c));
  while(!VidaQ(c)){
    ExtrQ(c,el);
    if(!fcond(el))
     
    IntrQ(qtemp,el);
  else 
    IntrQ(qtemp1,el);

  }

  ConcatQ(c,qtemp);
  return qtemp1;
  
}



int main()
{
	void *c, *s,*cs;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPct),MAX);
	if (!c)
		return 1;

  	s = InitS(sizeof(TPct),MAX);
	if (!s)
	{
		DistrQ(&c);
		return 1;
	}

  	lgc = GenereazaCoadaPct(c, 8, -5, 5);
  	lgs = GenereazaStivaPct(s, 6, -14, 14);

	  printf("\nCoada cu %d puncte\n", lgc);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	printf("\n\nStiva cu %d puncte\n", lgs);
   	AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);
/*
cs=copie(s);
AfiQ("Elemente coada:\n", AfiPct, cs);*/



double proc=f1c(c,peaxa);
printf("\nproc =%f",proc);
  AfiQ("Elemente coada:\n", AfiPct, c);

double proc2=f1s(s,peaxa);
printf("\nproc2 =%f",proc2);
 AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);


f2s(s,peaxa);
 AfiS("Elemente stiva dupa f2s (baza -> varf):\n", AfiPct, s);


f2c(c,peaxa);
 AfiQ("Elemente dupa f2c coada:\n", AfiPct, c);


void *c1, *s1;

c1=f3c(c,invers);
 AfiQ("Elemente dupa f3c coada:\n", AfiPct, c);
  AfiQ("Elemente dupa f3c coada:\n", AfiPct, c1);

  s1=f3s(s,invers);
  AfiS("Elemente stiva dupa f3s (baza -> varf):\n", AfiPct, s);
  AfiS("Elemente stiva dupa f3s (baza -> varf):\n", AfiPct, s1);

 	/* apeluri functii */

	DistrS(&s);
  	DistrQ(&c);
  	return 0;
}
