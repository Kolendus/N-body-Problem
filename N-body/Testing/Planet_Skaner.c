#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//static int n = 3;
//static int nkrok = 120;

typedef struct e{
	double masa;
	double *x;
	double *y;
	double *z;
	double Vx;
	double Vy;
	double Vz;
	double Ax;
	double Ay;
	double Az;
}*Planeta; 


int sprawdz_dane (char *nazwa_pliku_wej, int n){

	FILE *in = fopen(nazwa_pliku_wej, "r");	
	int nr_linii = 1;
	int prev_space = 0;
	int nr_arg = 0;
	int c;
		while((c=fgetc(in)) != EOF){
			if(isdigit(c) == 0 && isspace(c) == 0 && c != '\n' && c != '.' && c != '-' && c != 'e' && c != '+'){
				fprintf(stderr, "Nieprawidlowy format argumentu numer: %i w linii: %i \n ", nr_arg+1, nr_linii);
				fclose(in);
				return (-3);
			}else if(c == '-' && nr_arg == 0){
				fprintf(stderr, "Masa ciała w linii %i nie może byc ujemna! \n", nr_linii);
				return -6;
			}else if(isspace(c) != 0 && c != '\n' && prev_space == 1){
				;
			}else if(isspace(c) != 0 && c != '\n'){
				prev_space = 1;
				nr_arg++;
			}else if(c == '\n' && nr_arg < 6 && nr_arg != 0) {
				fprintf(stderr, "Za mało argumentów w linii -- %i\n" , nr_linii);
				fclose(in);
				return (-1);
			}else if(c == '\n' && nr_arg > 6){
				fprintf(stderr, "Za dużo argumentów w linii -- %i\n", nr_linii);
				fclose(in);
				return (-2);
			}else if (c == '\n'){
				nr_arg = 0;
				nr_linii++;
			}else if(c == '.'){
				;
			}else
			prev_space = 0;
			}
		nr_linii--;
		if ( n != nr_linii){
			fprintf(stderr, " Liczba planet podanych przy ./a.out %i różni się od liczby planet w pliku %i\n", n, nr_linii);
		return -10;
		}
	fclose(in);
	return 0;
}

int wczytaj_dane(char *nazwa_pliku_wej, Planeta dane, int n, int nkrok){
	
	int i,j;

	FILE *in = fopen(nazwa_pliku_wej, "r");
	
	if(in == NULL){
		fprintf(stderr, "Podany plik %s z danymi nie istnieje\n", nazwa_pliku_wej);
		fclose(in);
		return (-10);
	}

	fclose(in);
	
	if(sprawdz_dane(nazwa_pliku_wej,n) != 0) {
		return sprawdz_dane(nazwa_pliku_wej,n);
	}
	FILE *in2 = fopen(nazwa_pliku_wej, "r");
	
	/*alokuje pamiec na tablice w kolejnych strukturach*/
	for(i = 0; i < n; i++){	
		dane[i].x = malloc( (nkrok*15) * sizeof (dane[i].x));
		dane[i].y = malloc( (nkrok*15) * sizeof (dane[i].y));
		dane[i].z = malloc( (nkrok*15) * sizeof (dane[i].z));
		
	}
	
	for(j = 0, i = 0; fscanf(in2, "%lf %lf %lf %lf %lf %lf %lf\n", &dane[i].masa, &dane[i].x[j], &dane[i].y[j], &dane[i].z[j], &dane[i].Vx, &dane[i].Vy, &dane[i].Vz) != EOF; i++){;}
		
	fclose(in2);
	return 0;	
}

int main(int argc, char **argv){

	int i;
	int n = 10000;
	for(i=0;i<=50;i++)
	{
		char t[20] = "testj/test";
		char xd[5];
		sprintf(xd, "%i", i);
		char x[] = ".txt";
		strcat(t,xd);
		strcat(t,x);
		
		Planeta dane = malloc (n * sizeof *dane); 
//		sprawdz_dane(in,n);
		wczytaj_dane(t,dane,n,10);
		printf("Test %i zaliczony\n", i);
		free(dane);
	}
	return 0;
}


