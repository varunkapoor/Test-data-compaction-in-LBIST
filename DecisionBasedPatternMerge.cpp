#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#define NP 10000
#define PL 14875
#define PATT_LIMIT 500000

using namespace std;
FILE *f,*fg;
char mp[PL+1];

/* function to test whether two patterns are mergeable or not
	Note :  Two test vectors are merge-able only if the strings of the two vectors do not have different fixed values at a particular index.

		For eg: test vectors A and B are merge-able whereas vectors A and C are not.
		A = “11XX01XX0”   B= “110XXXX1X” C= “1001XXXXX"
*/

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

// Function two merge two patterns

char* merge(char* p1,char* p2)
{
	int i;
	printf("In merge fn");
	for(i=0;i<PL;i++)
	{
		if(*p1=='1'||*p2=='1')
			mp[i]='1';
		else if(*p1=='0'||*p2=='0')
			mp[i]='0';
		else
			mp[i]='X';
		p1++;
		p2++;
	}
	mp[i]='\0';
	return(mp);
}

// Function to check the number of carebits in a Pattern

bool check_care_bits(string s,int cbl)
{
	int cb=0;
	int i = 0;
	while(s[i] != '\0')
	{
		if(s[i]=='1'|| s[i]=='0')
		cb++;
		i++;
	}
	if(cb > cbl)
		return 0;
	else
		return(1);
}

int main()
{
	f = fopen("/design/tdf_implement1/Temporary_for_Swapnil/LBIST/10k_pat","r");
	fg = fopen("OUTPUT_FILE_C1_10k.txt","w");
	int pml,sl,cbl,patt_lim;
	bool start = 1;
	int i,j=0,k,w,a,h;
	char patt1[PL+1], patt2[PL+1];
	char *patt3,*patt_c,*p;
	stack<string> pat;
	stack<int> loc;
	stack<int> max_loc;
	string s,max;
	bool marked[NP+1];
	for(i = 0; i <= NP ; i++)
	{
		marked[i] = 0;
	}
	cout<<"Pattern Merge Limit : ";
	cin>>pml;
	cout<<endl<<"Search Limit : ";
	cin>>sl;
	cout<<"Care bit limit : ";
	cin>>cbl;
	for(i = 0 ;i < NP; i++)
	{
		start = 1;
		while( !loc.empty() )
			loc.pop();
		while( !pat.empty() )
			pat.pop();
		while( !max_loc.empty() )
			max_loc.pop();
		if(marked[i] == 0)
		{
			marked[i] = 1;
			loc.push(i);
			fseek(f,i*(PL+1),SEEK_SET);
			fscanf(f,"%s",patt1);
			pat.push(patt1);
			max = pat.top();
			j=0;
			patt_lim = 0;
			while( !loc.empty() && patt_lim < PATT_LIMIT)
			{
				h = loc.top();
				loc.pop();
				s.clear();
				if(!start)
				{
					pat.pop();
					s = pat.top();
					for(k = 0;s[k] != '\0'; k++)
					{
						patt1[k] = s[k];
					}
				}
				start = 0;
				j = h+1;
				if( j+sl <NP)
					w = j+sl;
				else
					w = NP;
				while( (j<w) && (loc.size() < pml) && (j<NP) )
				{
					patt_lim++;
					if( marked[j] == 0)
					{
						fseek(f,j*(PL+1),SEEK_SET);
						fscanf(f,"%s",patt2);
						if( test_merge(patt1,patt2) )
						{
							loc.push(j);
							if(pat.size()!=0)
							{
								s = pat.top();
								for(k=0;s[k]!='\0';k++)
								{
									patt1[k] = s[k];
								}
								patt1[k] = '\0';
							}
							patt3 = merge(patt1,patt2);
							if( (sl+j) >= NP)
								w = NP;
							else
								w = sl + j;
							for(k=0;k<PL;k++)
							{
								patt1[k] = patt3[k];
							}
							patt1[k] = '\0';
							pat.push(patt1);
							s = pat.top();
						}
					}
					j++;
				}
				if(loc.size() > max_loc.size())
				{
					max_loc = loc;
					max = pat.top();
				}		
				if(loc.size() >= pml )
				{
					while(!loc.empty())
					loc.pop();
				}
			}
			for(k=0;max[k]!='\0';k++)
			{
				fprintf(fg,"%c",max[k]);
			}
			fprintf(fg,"\n");
			while( !max_loc.empty() )
			{
				marked[max_loc.top()] = 1;
				max_loc.pop();
			}
		}
		fclose(f);
		fclose(fg);
	}
}