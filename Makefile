OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

#G++ = g++-10

program.exe: clean program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o
	g++ -o program.exe program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o

program.o:
	g++ -c program.cc $(OPCIONS)

Cluster.o:
	g++ -c Cluster.cc $(OPCIONS)

Procesador.o:
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o:
	g++ -c Proceso.cc $(OPCIONS)

Area_Espera.o:
	g++ -c Area_Espera.cc $(OPCIONS)

Prioridad.o:
	g++ -c Prioridad.cc $(OPCIONS)

open:
	kate *.cc [^B]*.hh Makefile &

test2:
	./program.exe < ./sample.inp > test.txt
	kompare test.txt ./sample.cor &

test1:
	./program.exe < ./entrega_intermedia/sample_intermedia.inp > test.txt
	kompare test.txt ./entrega_intermedia/sample_intermedia.cor &

test0:
	./program.exe < ./test.inp > ./test.txt
	kompare test.txt ./test.cor &

tar:
	tar -cvf practica.tar [^t]*.cc *.hh Makefile

save: clean
	git add *
	git commit
doxygen:
	doxygen
	google-chrome ./html/index.html &

clean:
	rm -f *.o
	rm -f *.exe
