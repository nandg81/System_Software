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
int compare(char *str1, char *str2) {
  return (*str1 && *str1 == *str2) ? compare(++str1, ++str2) : *str1 - *str2;
}
typedef struct NODE
{
	char s[20];
	char v[20];
	struct NODE *link;
}node;
void main()
{
	node sym[30];
	node *ptr,*ptr1;
	FILE *optab;FILE *ip;FILE *op;FILE *oc;
	int l,locctr,locctrold,flag,flag2,i,c,ctr,f,j;
	char temp[20],ad2[20],x[20],start[20],opc[20],syc[20],c2[20],opc2[20],opr[20],lc[20],lc2[20];
	ip=fopen("ip1.txt","r");
	op=fopen("op1temp.txt","w");
	fscanf(ip,"%s %s %s",syc,opc,start);

	if(strcmp(opc,"START")==0)
	{	
		locctr=atoi(start);
		fprintf(op,"H^%s^%s",pgname(syc),objcode(start));
	}
	else
	{
		fprintf(op,"H^      ^00000000^%s",objcode(start));
		locctr=0;
	}
	ctr=0;c=0;
	printf("%d\n",locctr);
	do
	{
		sprintf(lc,"%d",locctr);
		fscanf(ip,"%s %s %s",syc,opc,opr);
		flag=0;
		if(syc[0]!='-')
		{
			for(i=0;i<c;i++)
			{
				if(strcmp(syc,sym[i].s)==0)
				{
					printf("%s",sym[i].s);
					flag=1;
					if(sym[i].v[0]=='*')
					{

						ctr=0;
						ptr=sym[i].link;
						printf("%s",ptr->v);						
						while(ptr->link!=NULL)
						{
							fprintf(op,"\nT^%s^%d",objcode(ptr->v),locctr);
							ptr=ptr->link;
							
						}
						strcpy(sym[i].v,lc);
						sym[i].link=NULL;
					}
					break;
				}
			}
			if(flag==0)
			{
				strcpy(sym[c].s,syc);
				strcpy(sym[c].v,lc);
				sym[c].link=NULL;				
				printf("%s %s\n",sym[c].s,sym[c].v);
				c++;			
			}
		}
		optab=fopen("optab.txt","r");
		flag=0;
		while(!feof(optab))		
		{
			fscanf(optab,"%s %s",opc2,c2);
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
			flag2=0;
			for(i=0;i<c;i++)
			{
				if(strcmp(opr,sym[i].s)==0)
				{
					flag2=1;
					if(strcmp(sym[i].v,"*")==0)
					{
						ptr=sym[i].link;
						while(ptr->link!=NULL)
							ptr=ptr->link;
						ptr1=(node*)malloc(sizeof(node));
						sprintf(lc2,"%d",locctr+1);
						strcpy(ptr1->v,lc2);
						ptr->link=ptr1;
						strcpy(ad2,"0000");	
					}
					else
					{
						//printf("\n%s",sym[i].v);
						strcpy(ad2,sym[i].v);
					}
					break;
				}
			}
			if(flag2==0)
			{
				
				strcpy(sym[c].s,opr);
				//sym[c].v[0]='*';
				printf("\n%s %s",sym[c].s,sym[c].v);				
				ptr1=(node*)malloc(sizeof(node));
				sym[c].link=ptr1;
				sprintf(lc2,"%d",locctr+1);
				strcpy(ptr1->v,lc2);				
				c++;
				strcpy(ad2,"0000");
			}
			if(ctr==0)
			{
				fprintf(op,"\nT^%s^%s%s",objcode(lc),c2,ad2);
				ctr=ctr+1;
			}
			else if(ctr>0&&ctr<20)
			{
				fprintf(op,"^%s%s",c2,ad2);
				ctr=ctr+1;
			}
			else
			{		
				fprintf(op,"\nT^%s^%s%s",objcode(lc),c2,ad2);
				ctr=1;
			}	
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
			locctr=locctr+atoi(opr);
		else if(strcmp(opc,"BYTE")==0)
			locctr=locctr+atoi(opr);
		else if(strcmp(opc,"END")==0)
			break;
		else
		{
			printf("Invalid operation code");
		}
	}while(!feof(ip));
	sprintf(lc,"%d",locctr);	
	fprintf(op,"\nE^%s",objcode(start));
	fclose(ip);
	fclose(op);
	op=fopen("op1temp.txt","r");
	oc=fopen("op1.txt","w");
	i=atoi(start);
	i=locctr-i;
	sprintf(temp,"%d",i);
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
		{
			fprintf(oc,"%s^",x);				
			fprintf(oc,"%s",objcode(temp));
		}

	}
	fclose(op);
	fclose(oc);
}
			
	
