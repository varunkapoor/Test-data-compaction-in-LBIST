#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define PL 14875
#define NP 100002
#define CBLIMIT 200
#define FAIL_LIMIT 75000
#define PATT_LIMIT 10000

int test_merge(char*,char*);
char* merge(char*,char*);
int calc_care_bits(char*);
char mp[PL+1];

int main()
{
	long int i,j,k,l,temp;
	char patt1[PL+1],patt2[PL+1],patt_temp[PL+1];
	int index[NP],result,care_bits,r_num_merge;
	int num_fail,num_merge,patt_num=0;
	FILE *fps,*fpt, *fpt1;
	char *p,*p_r;
	FILE *fp_in,*fs_in;
	int arr_cb[NP][2];
	int count;
	char ch;
	int temp1;
	long int len=PL+1;
	fp_in = fopen("/design/LBIST/ip_file","r");
	fs_in = fopen("/design/LBIST/sort_inc_file","a+");
	for(i = 0;i < NP;i++)
	{
		arr_cb[i][0] = i;
		count = 0;
		while((ch = getc(fp_in)) != '\n')
		{
			if( ch == '1' || ch == '0')
			{
				count++;
			}
		}
		arr_cb[i][1] = count;
	}
	for(i = 0;i < NP-1; i++)
	{
		for(j = 0;j < NP-(i+1);j++)
		{
			if(arr_cb[j][1] > arr_cb[j+1][1])
			{
				temp1 = arr_cb[j][1];
				arr_cb[j][1] = arr_cb[j+1][1];
				arr_cb[j+1][1] = temp1;
				temp1 = arr_cb[j][0];
				arr_cb[j][0] = arr_cb[j+1][0];
				arr_cb[j+1][0] = temp1;
			}
		}
	}
	j=0;
	while(j<NP)
	{
		i=0;
		fseek(fp_in, ( arr_cb[j][0] )*len, SEEK_SET);
		while(i<len)
		{
			ch = getc(fp_in);
			fprintf(fs_in,"%c",ch);
			i++;
		}
		j++;
	}
	fclose(fp_in);
	fclose(fs_in);
	fps=fopen("/design/tdf_implement1/Temporary_for_Swapnil/LBIST/sort_inc_file","r");
	fpt=fopen("/design/tdf_implement1/Temporary_for_Swapnil/LBIST/new_op_inc","a");
	temp=PL+1;
	for(i=0;i<=NP-1;i++) /* initialize the index array to all zeroes */
	{
		index[i]=0;
	}
	for(j=0;j<=NP-1;j++) /* start of the outer loop (for pattern 1) */
	{	
		num_fail=0;
		num_merge=1;
		if(index[j]==0) /* check for availibility of 1st pattern */
		{
			index[j]=1;
			fseek(fps,j*temp,SEEK_SET);
			fscanf(fps,"%s",patt1);
			for(k=j+1;k<=NP-1;k++) /* start of inner loop (for pattern 2) */
			{
				if(index[k]==0) /* check for avalibility of 2nd pattern */
				{
					fseek(fps,k*temp,SEEK_SET);
					fscanf(fps,"%s",patt2)
					/* read the second pattern */
					result=test_merge(patt1,patt2);
					if(result==1)
					{
						p=merge(patt1,patt2);
						care_bits=calc_care_bits(p);
						if(care_bits>CBLIMIT)		
						{
							fprintf(fpt,"%d. %d %s %d\n", \
							patt_num,num_merge,patt1,care_bits);
							if (patt_num ==PATT_LIMIT)
							{
								exit(0);
							}
							break;
						}	
						else
						{
							num_merge++;
							index[k]=1;
							strcpy(patt1,p);
							care_bits=calc_care_bits(patt1);
							printf("j=%d ",j);
							patt_num++;
							continue;
						}
					}
					else
					{
						num_fail++;
						if(num_fail>FAIL_LIMIT)
						{		
							fprintf(fpt,"%d. %d %s %d\n", \
							patt_num,num_merge,patt1,care_bits);
							break;
						}
					}
				}
				else
				{
					printf("Loc is already merged");
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	fclose(fps);
	fclose(fpt);
}

int test_merge(char* p1,char* p2)
{
	while(*p1)
	{
		if(((*p1=='1')&&(*p2=='0'))||((*p1=='0')&&(*p2=='1')))
		return(0);
		p1++;
		p2++;
	}
	return(1);
}

char* merge(char* p1,char* p2)
{
	int I;
	printf("In merge fn");
	for(i=0;i<=PL-1;i++)
	{
		if(*p1=='1'||*p2=='1')
		mp[i]='1';
		else if(*p1=='0'||*p2=='0')
		mp[i]='0';
		else mp[i]='X';
		p1++;
		p2++;
	}
	mp[i]='\0';
	return(mp);
}


int calc_care_bits(char* pt)
{
	int cb=0;
	while(*pt)
	{
		if(*pt=='1'||*pt=='0')
		cb++;
		pt++;
	}
	printf("\n%d\n",cb);
	return(cb);
}
