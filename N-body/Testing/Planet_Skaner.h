#include <stdio.h>
#include <stdlib.h>

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
} *Planeta; 

int wczytaj_dane(char *nazwa_pliku_wej, Planeta dane, int n, int nkrok);

int sprawdz_dane(char *nazwa_pliku_wej);
