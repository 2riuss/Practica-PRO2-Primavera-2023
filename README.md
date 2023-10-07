# Pràctica-PRO2-Primavera-2023

Repositori per penjar la meva pràctica de l'assignatura de PRO2.

La pràctica consisteix a programar una simulació del funcionament d'una arquitectura multiprocessador. [Especificacions de la pràctica](enunciado_practica.pdf).

L'entrada i sortida del programa ha de ser tal com es mostra en els [tests](tests).

També s'ha de generar una documentació de la pràctica amb doxygen. Es pot accedir a la documentació obrint amb google-chrome el fitxer documentation/html/index.html. La comanda `make doxygen` refà la documentació i l'obra a una pestanya nova.

Per a agilitzar la pràctica he utilitzat un [Makefile](Makefile). Així doncs, per a compilar el programa n'hi ha prou amb executar la comanda `make`. I per a executar els tests i compararlos amb kompare es pot fer amb les comandes `make test1`, `make test2` i `make test3` per a cada un dels tests.