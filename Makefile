OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
SOURCES = $(addprefix ./code/, program.cc Cluster.cc Procesador.cc Proceso.cc Area_Espera.cc Prioridad.cc)
OBJECTS = $(SOURCES:./code/%.cc=./obj/%.o)
HEADERS = $(wildcard ./code/*.hh)

program.exe: $(OBJECTS)
	g++ -o program.exe $^

./obj/%.o: ./code/%.cc $(HEADERS)
	@mkdir -p ./obj
	g++ $(OPCIONS) -c $< -I ./code -o $@

test%: program.exe		# aviable tests are {test1, test2, test3}
	./program.exe < ./tests/$@.inp > ./test.txt
	kompare test.txt ./tests/$@.cor
	rm test.txt

tar:
	tar -cvf practica.tar $(SOURCES) $(HEADERS) Makefile

doxygen:
	doxygen
	google-chrome ./documentation/html/index.html &

clean:
	rm -rf obj
	rm -f practica.tar