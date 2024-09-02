#include "lista2.h"
typedef struct celula
{
  char *nume;
  int varsta;
  float nota;              /* adresa element extern */
  struct celula *pre, *urm;  /* legaturi spre celulele vecine */
} TCelula1, *TPers;

void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}
void AfiP(void * ax)
{
	printf("%f ", *(float*)ax);
}

void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;

  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;
	 	*ax = x;
		InsDupa(s->pre, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}


int isin(int v[],int i,int n){
	for (int j=0;j<n;j++)
		if(v[j]==i)
			return 1;
	return 0;


}
int size1(TLDI s){
	int i=0;
	TLDI p;
	for(p=s->urm; p != s ; p = p->urm){
		i++;}
		return i;
}

int f1(TLDI s){

	int i=-1;

	int n=0;
	TLDI p;
	int v[size1(s)];
	
	for(p=s->urm; p != s ; p = p->urm){
		i++;
		v[i]=*(int*)p->info;
		


	}
	n=++i;
	//printf("n=%d",n);
if(n%2==0){
	for( i=0;i<n/2;i++){
		
		for (int j=n/2;j<n;j++ ){

			if(!isin(v,v[j],n/2))
				return 0;
		}

	}}
	else{
		for( i=0;i<n/2;i++){
		
		for (int j=n/2+1;j<n;j++ ){
			//printf("%d %d \n",v[i],v[j]);
			if(!isin(v,v[j],n/2))
				return 0;
		}

	}



	}



	return 1;
}



TPers InitPers()
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{
	TPers aux = (TPers)malloc(sizeof(TCelula1));
    if (!aux) return NULL;

	aux->pre = aux->urm = aux;
    aux->nota = 0;
    aux->varsta=0;
    aux->nume=NULL;

	return aux;     /* rezultatul este adresa santinelei sau NULL */
}
int InsDupaP(TPers a, int x,float y,char*z)  /* inserare dupa celula cu adresa a -> 1/0 */
{
	TPers aux = (TPers)malloc(sizeof(TCelula1));
	if(!aux) return 0;
	aux->varsta = x;
	//aux->nume=z;
	aux->nume=(char*)malloc(sizeof(char)*30);
	strcpy(aux->nume,z);
	aux->nota=y;
	aux->pre = a;
	aux->urm = a->urm;
	a->urm->pre = aux;
	a->urm = aux;
    return 1;
}

void CitirePers(TPers s, int* lg)
{
	int *ax, x;
	 char arrays[12];
	char *z=arrays;
	float y;
 	char ch;
 	

  	printf("\nse citesc valori pt TPers, cu ordinea nume nota varsta ;\n");
	for(*lg = 0;  ; )

  	{


  		scanf("%s", z);
  		if(strcmp(z,"gata")==0)
  			break;

  		printf("\nnume este %s\n",z);
        scanf("%f", &y) ;
       printf(" nota este%f\n",y);
        scanf("%d", &x) ;
       printf(" varsta este%d\n",x);
		
		InsDupaP(s->pre, x,y,z);
		//printf("el %s,%d,%f",s->pre->nume,s->pre->varsta,s->pre->nota);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

void AfisareP(TPers s, void (*afiEl)(void *))
    /* afisare lista */
{
	TPers p;
	printf("\nLista: ");
	if(s->urm == s)
	{
		printf("vida\n");
		return;
	}
	for(p = s->urm; p != s; p = p->urm)
		printf("nume:%s %d %f",p->nume,p->varsta,p->nota);
	printf("\n");
}


TPers f2(TPers s ){
TPers p;
TPers x=InitPers();;
for(p = s->urm; p != s; p = p->urm){
if(p->nota != p->urm->nota)
	
InsDupaP(x, p->varsta,p->nota,p->nume);


}

return x;
}

int main()
{
	TLDI s;
	TPers x;
	int lg;

	for(; ; )
	{
		s = InitLDI();
		CitireLDI(s, &lg);
		AfisareLDI(s, AfiInt);

		/* apeluri functii */

		printf("f1 da %d",f1(s));


		x=InitPers();
		CitirePers(x, &lg);
		AfisareP(x, AfiP);

		TPers Y = f2(x);
		AfisareP(Y, AfiP);



		DistrLDI(&s);

		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 1;
}
