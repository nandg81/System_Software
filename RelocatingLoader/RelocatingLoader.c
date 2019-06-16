#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	FILE *ip;
	char opc[20],mask[20],syc[20],opc2[20],opr[20],start[20];
	int s,i,j,x,len,add,count,temp1,temp2;
	ip=fopen("oc2.txt","r");
	fscanf(ip,"%s",syc);
	fscanf(ip,"%s",syc);
	printf("Enter the starting address ");
	scanf("%d",&add); 
	printf("Name of program: ");
	printf("%s",syc);
	printf("\nObject code\tMemory location\n");
	while(!feof(ip))
	{
		fscanf(ip,"%s",syc);
		if(strcmp(syc,"T")==0)
		{
			fscanf(ip,"%s",syc);
			x=atoi(syc);
			fscanf(ip,"%s",opc2);
			len=atoi(opc2);
			fscanf(ip,"%s",mask);
			printf("%s",mask);
			count=0;
			while(count<len&&(strcmp(syc,"E")!=0))
			{
				fscanf(ip,"%s",syc);
				if(strcmp(syc,"E")==0)
					break;				
				if(mask[count]=='1')
				{
					temp1=atoi(syc);
					temp1=temp1+add;
					sprintf(syc,"%d",temp1);
				}
				printf("\n%s\t\t\t%d",syc,add+x);
				x=x+3;
				count++;	
			}	
		}
	}
	
}
			
	
