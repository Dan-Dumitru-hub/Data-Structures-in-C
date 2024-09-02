#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"
#include <math.h>

#define MAX 256

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf("%s", antet); /* afiseaza antetul */
	if (VidaQ(a))
		printf("Coada vida!");
	else
		PrelQ(a, AfiElem); /* afiseaza elementele in ordinea introducerii */
	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf("%s", antet); /* afiseaza antetul */
	if (VidaS(a))
		printf("Stiva vida!");
	else
		Prel_B_V(a, AfiElem); /* afiseaza elementele in ordinea introducerii */
	printf("\n");
}

int AfiStr(void *a)
{
	printf("%s ", (char *)a);
	return 1;
}

int AfiNr(void *a)
{
	printf("%d ", *((int *)a));
	return 1;
}

int isOperator(char *token)
{
	return strcmp(token, "^") == 0 || strcmp(token, "/") == 0 || strcmp(token, "*") == 0 || strcmp(token, "+") == 0 || strcmp(token, "-") == 0;
}

/*
* tokens -> array of tokens
* size -> number of tokens
*/

int pow1(int r1,int r2){

	for(int i=0;i<r2-1;i++){
		r1*=r1;
	}
	return r1;
}
int evaluateExp(char **tokens, int size)
{
	void *s = InitS(10, MAX);
	
	int r = 0;
	char *op1 = malloc(20), *op2 = malloc(20);

	for (int i = 0; i < size; i++)
	{
		char *token = tokens[i];
		//printf("token%s",token);
		// TODO
		if(!isOperator(token)){
			//printf("token%s",token);
			Push(s,token);
		}
		else{
			

			Pop(s,op2);

			Pop(s,op1);
			int val1=atoi(op1);
			//printf("val1%d",val1);

			int val2=atoi(op2);
			//printf("val2%d",val2);
			

			if(strcmp(token,"+")==0){
				r=val1+val2;
				//printf("r+%d",r);
			}
			if(strcmp(token,"-")==0){
				r=val1-val2;
			}
			if(strcmp(token,"*")==0){
				r=val1*val2;
					//printf("r*%d",r);
			}
			if(strcmp(token,"/")==0 ){
				r=val1/val2;
			}
			if(strcmp(token,"^")==0){
				r=pow1(val1,val2);
			}

			char str[4];
			sprintf(str, "%d", r);
			Push(s,str);

		}


	}
	char str1[4];
	Pop(s,str1);
	r=atoi(str1);

	return r;
}

void evaluateExpressions()
{
	FILE *f;
	size_t len = 0;
	char delim[] = " \n";
	char *expression = NULL;
	int expected[] = {28, 36, 9, 16, 31, 170, 267, 62, 39, 1310, 24, 59, 32, 4, 28};

	f = fopen("expression.txt", "rt");
	if (f == NULL)
		return;

	int index = 0;
	while (getline(&expression, &len, f) != -1)
	{
		printf("Expression: %s", expression);
		char *token = strtok(expression, delim);
		char **tokens = calloc(20, sizeof(char *));
		int nofTokens = 0;
		while (token != NULL)
		{
			tokens[nofTokens] = token;
			nofTokens++;
			token = strtok(NULL, delim);
		}

		int result = evaluateExp(tokens, nofTokens);

		if (result == expected[index])
			printf("[CORRECT] ");
		else
			printf("[WRONG] ");
		printf("Result: %d", result);
		if (result == expected[index])
			printf("\n");
		else
			printf(", expected %d\n", expected[index]);
		printf("--------------------------\n");
		index++;
	}

	fclose(f);
}


void sortQueue(void *q, int size)
{
	
	

    for (int i = 1; i <= size; i++)
    {
       
          int min_index = -1;
    int min_val = 999;
    int n = NrEQ(q);;
    int poz=n-i;
    for (int i=0; i<=poz; i++)
    {
       
    	
    	int curr1;

    	ExtrQ(q,&curr1);
    	
        if ((curr1) <= min_val )
        {
            min_index = i;
            min_val = (curr1);
        }
     
        IntrQ(q,&curr1);
                     
    }

    for (int i=0; i<n-poz-1; i++)
    {
       
    	
    	int curr1;

    	ExtrQ(q,&curr1);
    	
     
        IntrQ(q,&curr1);
                     
    }
    
    for (int i = 0; i < size; i++)
    {
        
        int curr1;
    	ExtrQ(q,&curr1);
    	
        if (i != min_index)
            IntrQ(q,&curr1);
        else
            min_val = (curr1);
    }
    IntrQ(q,&min_val);
     


    }


}



int main()
{
	// Ex 1
	printf("=========== EX 1 ===========\n");
	evaluateExpressions();
	printf("\n");

	// Ex 2
	printf("=========== EX 2 ===========\n");

	int nrElem = 10;
	void *c = InitQ(sizeof(int), MAX);
	srand(time(NULL));
	for (int i = 0; i < nrElem; i++)
	{
		int x = rand() % 100;
		IntrQ(c, &x);
	}
	AfiQ("Queue before sorting: ", AfiNr, c);
	sortQueue(c, nrElem);
	AfiQ("Queue after sorting: ", AfiNr, c);

	return 0;
}
