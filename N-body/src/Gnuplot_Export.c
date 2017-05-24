#include <stdio.h>
#include <stdlib.h>
#include "Planet_Scanner.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

int zapisz_w_gnuplot (Planeta dane, char *nazwa_pliku_wyj, int n, int nkrok, double radius)
{
		
	double min_x,min_y,min_z;
	double max_x,max_y,max_z;

	int i,j;

	min_x = dane[0].x[0];
	min_y = dane[0].y[0];
	min_z = dane[0].z[0];
	max_x = dane[0].x[0];
	max_y = dane[0].y[0];
	max_z = dane[0].z[0];
	
	/*Znajdujemy skrajne położenia x,y,z w pliku wynikowym*/
	for(j=0;j<n;j++)
	{
		for(i=0;i<nkrok;i++)
		{
			min_x = min(min_x,dane[j].x[i]);
			min_y = min(min_y,dane[j].y[i]);
			min_z = min(min_z,dane[j].z[i]);

			max_x = max(max_x,dane[j].x[i]);
			max_y = max(max_y,dane[j].y[i]);
			max_z = max(max_z,dane[j].z[i]);
		}
	}
		

	if(min_x == max_x) max_x+= 1.0;
	if(min_y == max_y) max_y+= 1.0;
	if(min_z == max_z) max_z+= 1.0;


	FILE *in2d = fopen("cen2D.gs","w");
	FILE *in3d = fopen("cen3D.gs","w");


	/*tworzymy script2D.gs*/
	fprintf(in2d,"do for [i=0:%i] {\n",nkrok);
	fprintf(in2d,"		set xrange[%lf:%lf]\n",min_x,max_x);
	fprintf(in2d,"		set yrange[%lf:%lf]\n",min_y,max_y);
	fprintf(in2d,"		set zrange[%lf:%lf]\n",min_z,max_z);
	fprintf(in2d,"		plot '%s' every ::i::i+%i u 1:2:3 pt 7 ps %lf\n",nazwa_pliku_wyj,n,radius);
	fprintf(in2d,"	}\n");

	/*tworzymy script3D.gs*/
	fprintf(in3d,"do for [i=0:%i] {\n",nkrok);
	fprintf(in3d,"		set xrange[%lf:%lf]\n",min_x,max_x);
	fprintf(in3d,"		set yrange[%lf:%lf]\n",min_y,max_y);
	fprintf(in3d,"		set zrange[%lf:%lf]\n",min_z,max_z);
	fprintf(in3d,"		splot '%s' every ::i::i+%i u 1:2:3 pt 7 ps %lf\n",nazwa_pliku_wyj,n,radius);
	fprintf(in3d,"	}\n");

	fclose(in2d);
	fclose(in3d);

	return 0;
	
}



int zapisz_plik(char *nazwa_pliku_wyj, Planeta dane, int n, double radius, int nkrok)
{

        FILE *out = fopen(nazwa_pliku_wyj,"w");

        int i,j;
        
	/*Wpisujemy dane do pliku*/
	for(j=0;j<nkrok;j++)
        {
                for(i=0;i<n;i++)
                {
                        fprintf(out,"%lf ",dane[i].x[j]);
                        fprintf(out,"%lf ",dane[i].y[j]);
                        fprintf(out,"%lf\n",dane[i].z[j]);
                }
        }

        fclose(out);

        zapisz_w_gnuplot(dane, nazwa_pliku_wyj, n, nkrok, radius);

        return 0;
}
