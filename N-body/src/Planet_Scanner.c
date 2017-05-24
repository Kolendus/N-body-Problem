#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*Bazowa struktura na dane*/
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
		return (-12);
	}

	fclose(in);
	
	/*sprawdzam dane*/
	if(sprawdz_dane(nazwa_pliku_wej,n) != 0) {
		return (-11);
	}
	
	FILE *in2 = fopen(nazwa_pliku_wej, "r");
	
	/*alokuje pamiec na tablice w kolejnych strukturach*/
	for(i = 0; i < n; i++){	
		dane[i].x = malloc( (nkrok*15) * sizeof (dane[i].x));
		dane[i].y = malloc( (nkrok*15) * sizeof (dane[i].y));
		dane[i].z = malloc( (nkrok*15) * sizeof (dane[i].z));
		
	}

	/*wczytuje dane do struktury*/	
	for(j = 0, i = 0; fscanf(in2, "%lf %lf %lf %lf %lf %lf %lf\n", &dane[i].masa, &dane[i].x[j], &dane[i].y[j], &dane[i].z[j], &dane[i].Vx, &dane[i].Vy, &dane[i].Vz) != EOF; i++){;}
		
	fclose(in2);

	return 0;	
}

