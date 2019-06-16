//Program to implement symbol table with suitable hashing
//Author: Nandagopal

#include<stdio.h>
#include<string.h>

typedef struct sd
{
	char label[20];
	int address;
}symdef;

int hash(char l[20],int max)
{
	int x1,x2,x,y;
	x1=l[0];
	x2=l[1];
	x=x1+x2;
	y=x%max;
	return y;
}
void main()
{
	char l[20];
	int a,h,i,ch,max;
	symdef s[20];
	printf("Enter the maximum number of elements in the symbol table ");
	scanf("%d",&max);
	for(i=0;i<max;i++)
	{
		strcpy(s[i].label,"NULL");
		s[i].address=0;
	}
	while(1)
	{
		printf("\nPress\n1. Insert a symbol\n2. Search for a symbol\n3. Exit\n");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("\nEnter the symbol ");
			scanf("%s",l);
			printf("\nEnter the address ");
			scanf("%d",&a);
			h=hash(l,max);
			if(s[h].address!=0)
				printf("\nSymbol already present");
			else
			{
				strcpy(s[h].label,l);
				s[h].address=a;
				printf("\nSymbol inserted");
			}
		}
		else if(ch==2)
		{
			printf("\nEnter the symbol ");
			scanf("%s",l);
			h=hash(l,max);
			if(s[h].address==0)
				printf("\nSymbol not found");
			else
				printf("\nSymbol: %s\nAddress: %d",l,s[h].address);
		}
		else if(ch==3)
			break;
		else
			printf("\nWrong input");
	}
}	
		
