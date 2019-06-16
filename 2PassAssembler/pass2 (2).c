#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	FILE *optab;FILE *symtab,*symtab2;FILE *ip;FILE *op;FILE *oc;
	int start,ctr,c2,c3,flag,flag2,ad,ad2,i,l;
	char opc[20],syc[20],opc2[20],opc3[20],opr[20],val[20];
	op=fopen("op.txt","r");
	oc=fopen("oc.txt","w");
	fscanf(op,"%d %s %s %s",&start,syc,opc,opr);
	while(!feof(op))
		fscanf(op,"%d %s %s %s",&ad,syc,opc,opr);
	fclose(op);
	op=fopen("op.txt","r");
	l=ad-start+3;
	fscanf(op,"%d %s %s %s",&ad,syc,opc,opr);
	if(strcmp(opc,"START")==0)
		fprintf(oc,"H%s00%s00%d",syc,opr,l);
	else
		fprintf(oc,"H%s00000000%d",syc,l);
	ctr=0;
	do
	{
		flag=0;
		fscanf(op,"%d %s %s %s",&ad,syc,opc,opr);
		optab=fopen("optab.txt","r");
		while(!feof(optab))		
		{
			fscanf(optab,"%s %d",opc3,&c3);
			if(strcmp(opc,opc3)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			if(strcmp(opr,"-")!=0)
			{
				flag2=0;
				symtab2=fopen("symtab.txt","r");
				while(!feof(symtab2))		
				{
					fscanf(symtab2,"%s %d",opc2,&c2);
					if(strcmp(opr,opc2)==0)
					{
						ad2=c2;
						flag2=1;
						break;
					}
				}
				if(flag2==0)
				{
					printf("Invalid symbol %s",opr);
					exit(0);
				}
			}
			else
				ad2=0;
			if(ctr==0)
			{
				fprintf(oc,"\nT%d%d%d",ad,c3,ad2);
				ctr=ctr+1;
			}
			else if(ctr>0&&ctr<20)
			{
				fprintf(oc,"%d%d",c3,ad2);
				ctr=ctr+1;
			}
			else
			{		
				fprintf(oc,"\nT%d%d%d",ad,c3,ad2);
				ctr=1;
			}
		}
		else
		{
				if((strcmp(opc,"RESW")==0)||(strcmp(opc,"RESB")==0))
					ctr=0;
				else if(strcmp(opc,"BYTE")==0)
				{
					for(i=0;opr[i]!='\0';i++)
						fprintf(oc,"%d",opr[i]);
					ctr=ctr+1;
				}
		}
	}while(!feof(op));
	fprintf(oc,"\nE%d",start);
	fclose(symtab2);
	fclose(oc);
	fclose(op);
}
			
	
