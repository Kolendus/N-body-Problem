#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "Planet_Scanner.h"
#include "N-body.h"
#include "Gnuplot_Export.h"




int sprawdz_wejscie(int argc, char *argv[], int *n, double *krok_czasowy, double *dlugosc_symulacji, char **in, char **out ,double *radius)
{
	int i,c;

	int isgood = 1;

	/*sczytujemy argumenty wywołania*/	
	while ((c = getopt (argc, argv, "n:s:l:i:o:r:h")) != -1)
	{
		switch (c)
		{
			case 'n':
				*n = atoi(optarg);
				break;

			case 's':
				*krok_czasowy = atof(optarg);
				break;

			case 'l':
				*dlugosc_symulacji = atof(optarg);
		
					if(*dlugosc_symulacji > 2147483647){
					printf("Krok czasowy nie może być większy od zakresu in = 2147483647\n");
					return -10;
					}

				break;

			case 'i':
				*in = optarg;
				break;

			case 'o':
				*out = optarg;
				break;

			case 'r':
				*radius = atof(optarg);
				break;

			case 'h':

				printf("------------------------------------------------------------------\n");				
				printf("Uruchom z argumentami:\n");
				printf("-i\t <plik wejsciowy>\n");
				printf("-o\t <plik wyjsciowy>\n");
				printf("-n\t <liczba planet>\n");
				printf("-s\t <krok czasowy>\n");
				printf("-l\t <dlugosc symulacji>\n");
				printf("-r\t <promien>\n\n");
				printf("Przykladowe wywolanie programu:\n");
				printf("./a.out -i wejscie.txt -o wyjscie.txt -n 10 -s 1 -l 25000 -r 1\n");
				printf("------------------------------------------------------------------\n");	
				return -1;

		}
	}
	
	/*Błędy w przypadku braku jednego z argumentów*/
	if(strcmp(*in,"") == 0) printf("Nie podano pliku wejsciowego!\n");
	if(strcmp(*out,"") == 0)  printf("Nie podano pliku wyjsciowego!\n");
	if(*n == 0) printf("Nie podano liczby planet!\n");
	if(*krok_czasowy == 0) printf("Nie podano kroku czasowego!\n");
	if(*dlugosc_symulacji == 0) printf("Nie podano czasu symulacji\n");

	if( strcmp(*in,"") == 0 || strcmp(*out,"") == 0 || *n == 0 || *krok_czasowy == 0 || *dlugosc_symulacji == 0){
		isgood = 0;
	}

	/*Sprawdzenie danych wejściowych*/
	if(*krok_czasowy * 3600 > *dlugosc_symulacji){
		printf("Krok czasowy > dlugosc symulacji\n");
		return -5;

	}else if(*krok_czasowy < 1){
		printf("Krok czasowy < 1\n");
		return -7;

	}else if( *n < 0){
		printf("Liczba ciał nie może być ujemna! \n");
		return -8;
	}
	
	if(isgood == 1)
	{
		printf("Plik wejsciowy: %s\n",*in); 
		printf("Plik wyjsciowy: %s\n",*out); 
		printf("Liczba planet: %i\n",*n); 
		printf("Krok czasowy: %lf\n",*krok_czasowy); 
		printf("Dlugosc symulacji: %lf\n",*dlugosc_symulacji);
		printf("Promien: %lf\n",*radius);
		return 0;
	}

	printf("\nUruchom z -h aby uzyskać pomoc!\n");

	return -1;
}

int main(int argc, char **argv) {
       
	int n = 0;
	double krok_czasowy = 0;
	double dlugosc_symulacji = 0;
	char *in = "";
	char *out = "";
	double radius = 1;

	if(sprawdz_wejscie(argc,argv,&n,&krok_czasowy,&dlugosc_symulacji,&in,&out,&radius) != 0)
		return -10;
	
	Planeta dane = malloc ( n * sizeof *dane);  

        if(wczytaj_dane(in,dane,n, (dlugosc_symulacji/(krok_czasowy*3600))) != 0)
		return -20;

	if(oblicz_pozycja(dane,krok_czasowy,dlugosc_symulacji,n) != 0)
		return -30;
	
	if(zapisz_plik (out,dane,n,radius, (dlugosc_symulacji/(krok_czasowy*3600))) != 0)
		return -40;

	free(dane);

	return 0;
}
