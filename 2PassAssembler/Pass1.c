#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	FILE *optab;FILE *symtab,*symtab2;FILE *ip;FILE *op;
	int locctr,locctrold,c2,flag,i;
	char opc[20],syc[20],opc2[20],opr[20];
	symtab=fopen("symtab.txt","w");
	ip=fopen("ip.txt","r");
	op=fopen("op.txt","w");
	fscanf(ip,"%s %s %d",syc,opc,&i);
	if(strcmp(opc,"START")==0)
	{	
		locctr=i;
		fprintf(op,"%d %s %s %d\n",locctr,syc,opc,i);
	}
	else
		locctr=0;
	printf("%d\n",locctr);
	do
	{
		fscanf(ip,"%s %s %s",syc,opc,opr);
		if(strcmp(syc,"-")!=0)
		{
			fprintf(symtab,"%s %d\n",syc,locctr);
			printf("%s %d\n",syc,locctr);
		}
		else
		{
			flag=0;
			symtab2=fopen("symtab.txt","r");
			while(!feof(symtab2))		
			{
				fscanf(symtab2,"%s %d",opc2,&c2);
				if(strcmp(syc,opc2)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("Symbol already present");
				exit(0);
			}
			fclose(symtab2);
		}
		
		optab=fopen("optab.txt","r");
		flag=0;
		while(!feof(optab))		
		{
			fscanf(optab,"%s %d",opc2,&c2);
			if(strcmp(opc,opc2)==0)
			{
				flag=1;
				break;
			}
		}
		fclose(optab);
		locctrold=locctr;
		if(flag==1)
		{
			if(opc[0]=='+')
				locctr=locctr+4;
			else
				locctr=locctr+3;
		}
		else if(strcmp(opc,"WORD")==0)
			locctr=locctr+3;
		else if(strcmp(opc,"RESW")==0)
		{
			i=atoi(opr);	
			locctr=locctr+(3*i);
		}
		else if(strcmp(opc,"RESB")==0)
			locctr=locctr+opr;
		else if(strcmp(opc,"BYTE")==0)
			locctr=locctr+opr;
		else if(strcmp(opc,"END")==0)
			break;
		else
		{
			printf("Invalid operation code");
		}
		fprintf(op,"%d %s %s %s\n",locctrold,syc,opc,opr);
		printf("%d %s %s %s\n",locctrold,syc,opc,opr);
	}while(!feof(ip));
	fclose(symtab);
	fclose(ip);
	fclose(op);
}
			
	
