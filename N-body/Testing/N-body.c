#include <stdio.h>
#include "Planet_Skaner.h"
#include <stdlib.h>
#include <math.h>

/*static int n = 3;
static double krok_czasowy = 2;
static double dlugosc_symulacji = 25000;*/


int oblicz_pozycja(Planeta dane, int krok_czasowy, int dlugosc_symulacji, int n){

	double const G = 0.000000000066740831;
	double const EPS = 0.00000000000001;
	int i,j,p,b,x;
	double step = krok_czasowy * 3600; 
	double dt = step;
	i = 1;

	if((krok_czasowy*3600) > dlugosc_symulacji){
		return (-5);
	}
	
	for(x = 0; x < n; x++){           // trzeba czyscic przed
		dane[x].Ax = 0;	
		dane[x].Ay = 0;	
		dane[x].Az = 0;
	}

	while(step < dlugosc_symulacji){
		for(p = 0; p < n; p++){	
				for(j = 0; j < n; j++){
					if( p == j){
						//wykluczamy sytuacje x[i] - x[i];
					}
					else {
						double dx = dane[p].x[i-1]-dane[j].x[i-1];
						double dy = dane[p].y[i-1]-dane[j].y[i-1];
						double dz = dane[p].z[i-1]-dane[j].z[i-1];
						double distance = sqrtf(dx*dx + dy*dy + dz*dz) + EPS;
						double distanceto3 = distance * distance * distance;
						
						dane[p].Ax += -(G * dx * (dane[j].masa))/distanceto3; 
						dane[p].Ay += -(G * dy * (dane[j].masa))/distanceto3;
						dane[p].Az += -(G * dz * (dane[j].masa))/distanceto3;		
					}
				}
		}
			
		for(b = 0; b < n; b++){


			dane[b].x[i] = dane[b].x[i-1] + dane[b].Vx*dt + dane[b].Ax*dt*dt;
			//printf("\n Położenie x[%i] ---> %lf\n", i, dane[b].x[i]);
			
			dane[b].y[i] = dane[b].y[i-1] + dane[b].Vy*dt + dane[b].Ay*dt*dt;
			//printf("Położenie y[%i] ---> %lf\n", i, dane[b].y[i]);

			dane[b].z[i] = dane[b].z[i-1] + dane[b].Vz*dt + dane[b].Az*dt*dt;
			//printf("Położenie z[%i] ---> %lf\n", i, dane[b].z[i]);

			dane[b].Vx += dane[b].Ax*dt; 
			dane[b].Vy += dane[b].Ay*dt; 
			dane[b].Vz += dane[b].Az*dt; 
		}

		/*zeruje przyspieszenia*/
		for(x = 0; x < n; x++){
			dane[x].Ax = 0;	
			dane[x].Ay = 0;	
			dane[x].Az = 0;
		}

		step += dt;
		i++;
	}

	i = 0;

	return 0;
}
/*
int main(int argc, char **argv){
	Planeta dane = malloc (n * sizeof *dane); 
        Planeta *wsdane;
        char *in = argv[1];
        wczytaj_dane(in,dane);
	oblicz_pozycja(dane,krok_czasowy,dlugosc_symulacji,n);
	int i,c;
	int j = 1;
	for(c = 0; c <= 2; c++){
		for(i = 0; i < 4; i++){
			printf("Polozenie x ciała %i x[%i] = %lf\n", j, i, dane[c].x[i]);
		}
		j++;  
	}

	return 0;
}*/
		
