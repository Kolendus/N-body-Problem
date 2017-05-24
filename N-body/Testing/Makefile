a.out: Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o
	$(CC) Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o -o a.out -lm

clean: Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o
	rm Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o

Planet_Skaner.o: Planet_Skaner.c Planet_Skaner.h
N-body.o: N-body.c N-body.h
main.o: main.c
Gnuplot_Eksport.o: Gnuplot_Eksport.c Gnuplot_Eksport.h

test_planet: Planet_Skaner.c
	cc Planet_Skaner.c
	./a.out

test_all: Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o
	$(CC) Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o -o a.out -lm
	./a.out


