/**-- main.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

/*-- se completeaza cu definitiile functiilor implementate --*/

int f1(TArb root)
{
   
    if (root == NULL)
        return 0;
  
  

if (root->st != NULL && root->dr!=NULL && root->st->info < root->info && root->dr->info<root->info)

        return 1+f1(root->st)+f1(root->dr);
    return f1(root->st)+f1(root->dr);
}


void sumaaux(TArb root,int *r,int lvl){
if (root == NULL)
        return ;
if(lvl%2==0){
	r[lvl]+=root->info;
}

sumaaux(root->st,r,lvl+1);
sumaaux(root->dr,r,lvl+1);


}

int *f2(TArb root){

	int *r=calloc(NrNiv(root),sizeof(int));


sumaaux(root,r,0);

return r;

}





int f3(TArb root)
{
    if (root == NULL)
        return 999;
  
    int res = root->info;
    int lres = f3(root->st);
    int rres = f3(root->dr);
    if (lres < res)
        res = lres;
    if (rres < res)
        res = rres;
    return res;
}



int bonus(TArb root1 , TArb root2){


  if (root1 == NULL && root2 == NULL) {
    return 1;
  }
  
  if (root1 != NULL && root2 != NULL) {
    return (
            bonus(root1->st, root2->st) ||
            bonus(root1->dr, root2->dr) ||
            bonus(root1->st, root2->dr) ||
            bonus(root1->dr, root2->st));
  }

  return 0;
}

void RSD(TArb a)
{
	if(!a) {printf("-"); return;}
	if(!a->st && !a->dr) {printf(" %d ", a->info); return;}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

int main ()
{
	TArb arb;

	randomize();

	arb = ConstrAA (5, random(16), -50, 50);
	AfiArb (arb);
	printf ("noduri: %i   niveluri: %i\n",
	NrNoduri(arb), NrNiv(arb));
	RSD(arb);

	/*-- se completeaza cu apelurile functiilor implementate --*/



		printf("\nf1 da %d\n",f1(arb));
		

int *r=calloc(NrNiv(arb),sizeof(int));
r=f2(arb);
for(int i=0;i<NrNiv(arb);i++){
	printf("f2 da %d ",r[i]);
}
		
		printf("\nf3 da %d",f3(arb));

printf("\nbonus da %d",bonus(arb,arb));

	DistrArb (&arb);
	printf ("\n");


	return 0;
}
