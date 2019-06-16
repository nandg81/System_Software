#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* objcode(char str1[10])
{
	int n1,n2=0,l;
	static char str2[10];
	strcpy(str2,"0");
	
	n1=strlen(str1);
	l=6-n1;
	while(n2!=l)
	{
		strcat(str2,"0");
		n2=strlen(str2);
	}
	
	strcat(str2,str1);
	return str2;

}
char* pgname(char str1[10])
{
	int i,l;
	static char str2[6];
	l=strlen(str1);
	if(l==6)
		return str1;
	else if(l>6)
	{
		for(i=0;i<6;i++)
			str2[i]=str1[i];
		return str2;
	}
	else
	{
		for(i=0;i<l;i++)
			str2[i]=str1[i];
		for(i=l;i<6;i++)
			str2[i]=' ';
		return str2;
	}
}
		
		
		
void main()
{
	FILE *optab;FILE *symtab,*symtab2;FILE *ip;FILE *op;FILE *oc;
	int ctr,flag,flag2,i,l;
	char ad[20],ad2[20],endi[20],start[20],c2[20],c3[20],opc[20],syc[20],opc2[20],opc3[20],opr[20],val[20],x[50];
	op=fopen("op.txt","r");
	oc=fopen("octemp.txt","w");
	fscanf(op,"%s %s %s %s",start,syc,opc,opr);
	while(!feof(op))
		fscanf(op,"%s",endi);
	fclose(op);
	op=fopen("op.txt","r");
	fscanf(op,"%s %s %s %s",ad,syc,opc,opr);
	if(strcmp(opc,"START")==0)
	{		
		fprintf(oc,"H^%s^%s^",pgname(syc),objcode(opr));
		fprintf(oc,"%s",objcode(endi));
	}
	else
		fprintf(oc,"H^      ^00000000^%s",objcode(ad));
	ctr=0;
	do
	{
		flag=0;
		fscanf(op,"%s %s %s %s",ad,syc,opc,opr);
		optab=fopen("optab.txt","r");
		while(!feof(optab))		
		{
			fscanf(optab,"%s %s",opc3,c3);
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
					fscanf(symtab2,"%s %s",opc2,c2);
					if(strcmp(opr,opc2)==0)
					{
						strcpy(ad2,c2);
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
				strcpy(ad2,"0");
			if(ctr==0)
			{
				fprintf(oc,"\nT^%s^%s%s",objcode(ad),c3,ad2);
				ctr=ctr+1;
			}
			else if(ctr>0&&ctr<20)
			{
				fprintf(oc,"^%s%s",c3,ad2);
				ctr=ctr+1;
			}
			else
			{		
				fprintf(oc,"\nT^%s^%s%s",objcode(ad),c3,ad2);
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
	fprintf(oc,"\nE^%s",objcode(start));
	fclose(symtab2);
	fclose(oc);
	fclose(op);
	op=fopen("octemp.txt","r");
	oc=fopen("oc.txt","w");
	while(!feof(op))
	{
		fscanf(op,"%s",x);
		if(x[0]=='H')
		{
			fprintf(oc,"%s",x);
			if(strlen(x)<8)
				for(i=0;i<(8-strlen(x));i++)
					fprintf(oc," ");
		}
		else if(x[0]=='T')
		{
			fprintf(oc,"\n");
			l=0;
			for(i=0;i<=7;i++)
				fprintf(oc,"%c",x[i]);
			for(i=8;x[i]!='\0';i++)
				if(x[i]!='^')
					l++;
			if(l<10)
				fprintf(oc,"^0%d",l);
			else
				fprintf(oc,"^%d",l);
			for(i=8;x[i]!='\0';i++)
				fprintf(oc,"%c",x[i]);
			
		}
		else if(x[0]=='E')
			fprintf(oc,"\n%s",x);
		
		else
			fprintf(oc,"%s",x);
	}
}

