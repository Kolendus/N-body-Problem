a.out: Planet_Scanner.o N-body.o main.o Gnuplot_Export.o
	$(CC) Planet_Scanner.o N-body.o main.o Gnuplot_Export.o -o a.out -lm

clean: Planet_Skaner.o N-body.o main.o Gnuplot_Eksport.o
	rm Planet_Scanner.o N-body.o main.o Gnuplot_Export.o

Planet_Scanner.o: Planet_Scanner.c Planet_Scanner.h
N-body.o: N-body.c N-body.h
main.o: main.c
Gnuplot_Export.o: Gnuplot_Export.c Gnuplot_Export.h
uklad: Planet_Scanner.o N-body.o main.o Gnuplot_Export.o
	$(CC) Planet_Scanner.o N-body.o main.o Gnuplot_Export.o -lm
	./a.out -i heliocent2 -o wynik -n 5 -s 50 -l 2147483647 -r 2
