#include<string.h>
#include<stdio.h>
#define NP 10
#define PL 425


int i;
int rand(void);
char* rand_fill(char*);
FILE *fps,*fpt;
char patt1[PL+1],*p_rand;

int main()
{
	fps=fopen("op_file","r");
	fpt=fopen("x_filled_patt","w");
	for (i=0;i<NP;i++)
	{
		fseek(fps,i*(PL+1),SEEK_SET);
		fscanf(fps,"%s",patt1);
		p_rand=rand_fill(patt1);
		fprintf(fpt,"%s\n",p_rand);
	}
}

char* rand_fill(char*p)
{
	char* q;
	int r;
	q=p;
	while(*q)
	{
		if(*q=='X')
		{	
			r=rand()%2;
			*q=48+r;
		}
		q++;	
	}
	return(p);
}