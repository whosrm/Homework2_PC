# Tema 2 PC

Ceva joc de *scrabble*

## Compizitie

* Fisierul principal se numeste *scrabble.c*, este compilat implicit de make
* in functie de sistemul de operare se leaga o librarie din util/
* header-ul pentru librarie se afla tot in util/

## Task-uri

Pentru aflarea task-ului se citeste o linie de la tastatura si se extrage numarul task-ului.

### Task0

Doar face tabla de joc, goala, adica o matrice de 15x15, alocata static, plina
cu '.'

### Task1

Citind cate o linie:

* prima data se afla numarul de linii
* pentru fiecare linie:
	* se extrag coordonatele: 2 numere;
	* directia: 1 numar(0 sau 1)
	* cuvantul ce trebuie scris
	* in fucntie de directie se scrie cuvantul pe tabla incepand de la coordonatele cerute

### Task2

Asemanator cu task-ul 1, dar:

* pnetru fiecare linie retinem doar cuvantul
* calculam scorul pentru cuvantul respectiv, fara scorul bonus.

*Scorul* se calculeaza in functie de literele cuvantului:

* am retunut valorile fiecarei litere intr-un vector, dupa cum ne-au fost date
* pentru fiecare litera se calculeaza valoare din vector:
```litera - 'A'```

### Task3

* se calculeaza putnajul fiecarui cuvant ca la task-ul 2
* se cauta daca cuvantul contine sirul XX si sau **se termina** cu YY
* daca contine XX se cauta daca literele cuvantului se suprapun cu valori de 1
din matricea de bonus
* daca cuvantul **se termina** cu YY, se cauta literele care se suprapun cu valorile
de 2 din matricea de bonus
* la sfarsit punctajul cuvantului este inmultit cu 2 respectiv cu 3 ridicat la 
numarul de caractere care s-au suprapus cu valorile respective din matricea bonus

### Task4

* se citesc datele si se trec cuvintele in matrice ca la task-ul 1
* incepem sa cautam pe fiecare linie pana gasim un cuvant, sau doar o litera
* pentru fiecare litera gasita vedem daca putem scrie la dreapta sau sub ea
* daca nu putem, trecem la urmatoarea litera sau pe urmatoarea linie
* daca putem, calculam spatiul pe care il avem pana la urmatoarea litera
sau pana la marginea placii
* cautam in lista de cuvinte un cuvant care sa inceapa cu litera noastra si 
sa nu depaseasca lungimea disponibila

### Proble Task4

* pentru anumite(mai toate) cazuri, gaseste alte cuvinte.
