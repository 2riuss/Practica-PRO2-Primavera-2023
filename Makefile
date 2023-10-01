OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

#G++ = g++-10

program.exe: program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o
	g++ -o program.exe program.o Cluster.o Procesador.o Proceso.o Area_Espera.o Prioridad.o

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

Cluster.o: Cluster.hh Cluster.cc
	g++ -c Cluster.cc $(OPCIONS)

Procesador.o: Procesador.hh Procesador.cc
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o: Proceso.hh Proceso.cc
	g++ -c Proceso.cc $(OPCIONS)

Area_Espera.o: Area_Espera.hh Area_Espera.cc
	g++ -c Area_Espera.cc $(OPCIONS)

Prioridad.o: Prioridad.hh Prioridad.cc
	g++ -c Prioridad.cc $(OPCIONS)

open:
	kate program.cc Cluster.hh Cluster.cc Procesador.hh Procesador.cc Area_Espera.hh Area_Espera.cc Prioridad.hh Prioridad.cc Proceso.hh Proceso.cc Makefile &

test2:
	./program.exe < ./sample.inp > test.txt
	kompare test.txt ./sample.cor &
	rm test.txt

test1:
	./program.exe < ./entrega_intermedia/sample_intermedia.inp > test.txt
	kompare test.txt ./entrega_intermedia/sample_intermedia.cor &
	rm test.txt

test0:
	./program.exe < ./test.inp > ./test.txt
	kompare test.txt ./test.cor &
	rm test.txt

tar:
	tar -cvf practica.tar [^t]*.cc *.hh Makefile

save: clean
	git add .
	git commit

doxygen:
	doxygen
	google-chrome ./html/index.html &

clean:
	rm -f *.o
