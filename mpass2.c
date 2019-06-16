#include<stdio.h>
#include<string.h>

main()
{
	FILE *ip,*op,*m,*p,*d2;
	char a[20],b[20],c[20],d[20],e[20],f[20],fp[20][20],ap[20][20];
	char *token1,*token2;
	int ctr=0,i;
	int flag;
	ip=fopen("mip.txt","r");
	op=fopen("mop.txt","w");
	
	while(!feof(ip))
	{
		fscanf(ip,"%s %s %s",a,b,c);
		if(strcmp(b,"MACRO")==0)
		{
			fscanf(ip,"%s %s %s",a,b,c);
			while(strcmp(b,"MEND")!=0)
				fscanf(ip,"%s %s %s",a,b,c);	
		}
		else
		{
			m=fopen("m.txt","r");
			flag=0;
			while(!feof(m))
			{						
				fscanf(m,"%s",d);
				if(strcmp(d,b)==0)
				{
					flag=1;
					break;
				}
			}
			fclose(m);
			if(flag==0)
			{
				fprintf(op,"\n%s %s %s",a,b,c);
				if(strcmp(b,"END")==0)
					break;
			}
			else
			{
				d2=fopen("dtab.txt","r");
				fscanf(d2,"%s %s",e,f);
				token1 = strtok(f, ","); 
				token2 = strtok(c, ","); 
				strcpy(fp[ctr],token1);
				printf("\nfp1%s",fp[ctr]);
				strcpy(ap[ctr],token2);
				printf("\nap1%s",ap[ctr]);
				ctr++;
				token1 = strtok(f, ","); 
				token2 = strtok(c, ","); 
				strcpy(fp[ctr],"&B");
				printf("\nfp2%s",fp[ctr]);
				strcpy(ap[ctr],"N2");
				printf("\nap2%s",ap[ctr]);
				ctr++;	
				
				while(!feof(d2))
				{
					fscanf(d2,"%s %s",e,f);
					for(i=0;i<=ctr;i++)
					{
						if(strcmp(f,fp[i])==0)
						{
							fprintf(op,"\n- %s %s",e,ap[i]);
							break;
						}
					}
				}
				fclose(d2);
			}
		}
	}
	fclose(ip);
	fclose(op);
}
				
