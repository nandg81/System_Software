#include<stdio.h>
#include<string.h>

main()
{
	FILE *ip,*op,*m;
	char a[20],b[20],c[20];
	ip=fopen("mip.txt","r");
	op=fopen("dtab.txt","w");
	m=fopen("m.txt","w");

	while(!feof(ip))
	{
		fscanf(ip,"%s %s %s",a,b,c);	
		if(strcmp(b,"MACRO")==0)
		{
			fprintf(op,"%s %s\n",a,c);
			fprintf(m,"%s\n",a);
			printf("\nMacro: %s",a);
			while(strcmp(b,"MEND")!=0)
			{
				fscanf(ip,"%s %s %s",a,b,c);
				fprintf(op,"%s %s\n",b,c);
			}
		}
	}
	printf("\nPass 1 completed");
	fclose(ip);
	fclose(op);
	fclose(m);
}	
