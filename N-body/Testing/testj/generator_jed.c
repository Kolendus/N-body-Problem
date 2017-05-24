#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){

	srand(time(NULL));
	int i;
	for(int i=0;i<1000;i++)
	{
		char t[20] = "test";
		char xd[5];
		sprintf(xd, "%i", i);
		char x[] = ".txt";
		strcat(t,xd);
		strcat(t,x);
		printf("%s\n",t);
		FILE * in = fopen(t,"w");

		int j;
		for(j=0;j<10000;j++)
		{
			fprintf(in,"%lf ", rand()%10000000*1.233213213213);

			fprintf(in,"%lf ", rand()%10000000*1.233213213213);
			fprintf(in,"%lf ", rand()%10000000*1.233213213213);
			fprintf(in,"%lf ", rand()%10000000*1.233213213213);

			fprintf(in,"%lf ", rand()%10000000*1.233213213213);
			fprintf(in,"%lf ", rand()%10000000*1.233213213213);
			fprintf(in,"%lf\n", rand()%10000000*1.233213213213);
		}
		fclose(in);
	}
	return 0;
}
