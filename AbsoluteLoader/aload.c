#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	FILE *ip;
	char opc[20],syc[20],opc2[20],opr[20],start[20];
	int s,i,j,x;
	ip=fopen("oc.txt","r");
	fscanf(ip,"%s",syc);
	printf("Name of program: ");
	for(i=0;i<6;i++)
		printf("%c",syc[i+2]);
	printf("\nObject code byte\tMemory location\n");
	while(!feof(ip))
	{
		fscanf(ip,"%s",syc);
		if(syc[0]=='T')
		{
			for(i=0;i<6;i++)
			{
				start[i]=syc[i+2];	
			}
			s=12;
			x=atoi(start);
			j=0;
			for(i=s;i<strlen(syc);i++)
			{
				if(syc[i]=='^')
					i++;
				printf("%c%c\t\t\t%d\n",syc[i],syc[i+1],j+x);
				i++;
				j++;
			}
		}
	}
	
}
			
	
