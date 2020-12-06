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

* cautarea se face incepand de la cuvinte
* vrem sa punem primul cuvant care indeplineste criteriile:
	* nu este deja folosit
	* prima litera a acestuia este deja pe tabla
	* nu iese de pe tabla sau se suprapune cu alte cuinte

* retinem cuvintele scrise de jucatori pentru a fi mai usor de vazut
ce cuvinte au fost folosite
* pentru fiecare fuvant de lista de cuvinte *words*:
	* se verifica sa nu mai fi fost deja scris
	* i se cauta prima litera pe tabla
	* se verifica daca are loc
