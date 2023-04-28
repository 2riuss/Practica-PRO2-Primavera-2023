OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

#G++ = g++-10

program.exe: clean program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o
	clear
	g++ -o program.exe program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o

program.o:
	clear
	g++ -c program.cc $(OPCIONS)

Cluster.o:
	clear
	g++ -c Cluster.cc $(OPCIONS)

Proceso.o:
	clear
	g++ -c Proceso.cc $(OPCIONS)

Area_Espera.o:
	clear
	g++ -c Area_Espera.cc $(OPCIONS)

Prioridad.o:
	clear
	g++ -c Prioridad.cc $(OPCIONS)

open:
	kate *.cc [^B]*.hh

test_program: program.exe
	./program.exe < ./entrega_intermedia/sample_intermedia.inp > test.txt

test_test: program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o
	g++ -c test.cc $(OPCIONS)
	g++ -o test.exe test.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o
	./test.exe

save: clean
	mkdir $(t)
	cp ./[!D]* ./$(t)
doxygen:
	doxygen
	google-chrome ./DOC/html/index.html

clean:
	rm -f *.o
	rm -f *.exe
